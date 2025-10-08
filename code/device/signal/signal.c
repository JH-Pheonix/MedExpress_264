#include "signal.h"

signal_message_t signal_data;

static inline void discard_bytes(signal_obj_t *signal, int n)
{
    if (n <= 0)
        return;
    if (n >= signal->data_cnt)
    {
        signal->data_cnt = 0;
        return;
    }
    memmove(signal->rx_buf, signal->rx_buf + n, signal->data_cnt - n);
    signal->data_cnt -= n;
}

static void parse_payload(signal_obj_t *signal_obj, signal_message_t *signal_data, vuint8 *payload)
{
    switch (signal_data->cmd)
    {
    case 0x02:
    {
        signal_obj->receive_flag = 1;
        if (signal_data->len == 6)
        {
            // 大端模式：高字节在前，低字节在后
            signal_data->left_dis = (payload[0] << 8) | payload[1];
            signal_data->front_dis = (payload[2] << 8) | payload[3];
            signal_data->right_dis = (payload[4] << 8) | payload[5];
        }
        break;
    }
    default:
        break;
    }
}

// 信号板驱动
signal_obj_t signal_uart_init(uart_index_enum uartn, uart_rx_pin_enum rx_pin, uart_tx_pin_enum tx_pin, vuint32 baud)
{
    signal_obj_t signal;
    signal.uartn = uartn;

    memset(signal.rx_buf, 0, SIGNAL_RX_BUF_SIZE);
    signal.data_cnt = 0;
    signal.receive_flag = 0;

    uart_init(uartn, baud, tx_pin, rx_pin);
    uart_rx_interrupt(uartn, 1); // 使能串口接收中断

    return signal;
}

void signal_uart_handler(signal_obj_t *signal)
{
    vuint8 receive_data;
    if (uart_query_byte(signal->uartn, &receive_data))
    {
        if (receive_data == 0xA5 && signal->rx_buf[0] != 0xA5)
        {
            signal->data_cnt = 0;
        }

        if (signal->data_cnt < SIGNAL_RX_BUF_SIZE)
        {
            signal->rx_buf[signal->data_cnt++] = receive_data;
        }
        else
        {
            // 缓冲区溢出，重置状态
            signal->data_cnt = 0;
            return;
        }

        // 尝试解析尽可能多的完整帧（处理粘包）
        while (signal->data_cnt >= 4) // 最短帧为 header(1)+cmd(1)+len(1)+checksum(1)
        {
            // 确保头是 0xA5
            if (signal->rx_buf[0] != 0xA5)
            {
                // 在缓冲区中寻找下一个 0xA5 并把它移动到开头
                int idx = -1;
                for (int i = 1; i < signal->data_cnt; i++)
                {
                    if (signal->rx_buf[i] == 0xA5)
                    {
                        idx = i;
                        break;
                    }
                }

                if (idx == -1)
                {
                    // 未找到，清空缓冲区
                    signal->data_cnt = 0;
                    break;
                }

                // 将剩余数据左移
                discard_bytes(signal, idx);

                if (signal->data_cnt < 4)
                    break; // 数据不足以构成最短帧，等待更多字节
            }

            vuint8 len = signal->rx_buf[2];
            if (len > SIGNAL_PAYLOAD_MAX)
            {
                // 非法长度，丢弃首字节继续解析
                discard_bytes(signal, 1);
                continue;
            }

            vuint8 need = 4 + len; // header + cmd + len + payload(len) + checksum
            if (need > SIGNAL_RX_BUF_SIZE)
            {
                // 不可能的情况，重置
                signal->data_cnt = 0;
                break;
            }

            if (signal->data_cnt < need)
            {
                // 不够完整帧，等待更多字节
                break;
            }

            // 计算校验和值（对 bytes[0..need-2] 求和）
            vuint8 checksum = 0;
            for (vuint8 i = 0; i < (need - 1); i++)
            {
                checksum += signal->rx_buf[i];
            }

            if (checksum == signal->rx_buf[need - 1])
            {
                signal_data.cmd = signal->rx_buf[1];
                signal_data.len = len;

                parse_payload(signal, &signal_data, &signal->rx_buf[3]);

                // 移除已解析的帧
                if (signal->data_cnt > need)
                {
                    // 使用 discard_bytes 将已解析的部分一次性移除
                    discard_bytes(signal, need);
                    // 继续尝试解析下一个帧（如果有）
                    continue;
                }
                else
                {
                    // 刚好解析完所有字节
                    signal->data_cnt = 0;
                    break;
                }
            }
            else
            {
                // 校验失败，丢弃首字节继续解析
                discard_bytes(signal, 1);
                continue;
            }
        }
    }
}

signal_message_t signal_pop_data(signal_obj_t *signal)
{
    signal->receive_flag = 0;
    return signal_data;
}