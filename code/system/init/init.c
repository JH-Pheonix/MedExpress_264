#include "init.h"
#include "test.h"

#define PIT_KEY_T 10
#define PIT_ATTITUDE_T 2
#define PIT_CONTROL_T 10

motor_obj_t motor1, motor2, motor3, motor4;
encoder_obj_t encoder_x, encoder_y;
stp23l_obj_t lidar_left, lidar_right, lidar_front;
servo_obj_t servo_left, servo_right;

maixcam_obj_t maixcam1;

asrpro_obj_t asrpro1;

emm42_obj_t emm42_1;

MAX30102_obj_t MAX30102;
signal_obj_t signal_dev;

void system_init(void)
{
    // lcd
    lcd_init();
    test_lcd();

    motor1 = motor_init(ATOM2_CH4_P33_12, P33_13, 10000, 0, 1);
    motor2 = motor_init(ATOM0_CH5_P32_4, P23_1, 10000, 0, 1);
    motor3 = motor_init(ATOM0_CH0_P21_2, P21_3, 10000, 0, 1);
    motor4 = motor_init(ATOM0_CH2_P21_4, P21_5, 10000, 0, 1);

    // test_motor();
    // test_move_dir();

    encoder_x = encoder_init(TIM5_ENCODER, TIM5_ENCODER_CH1_P10_3, TIM5_ENCODER_CH2_P10_1);
    encoder_y = encoder_init(TIM2_ENCODER, TIM2_ENCODER_CH1_P33_7, TIM2_ENCODER_CH2_P33_6);
    // test_encoder();

    servo_left = servo_init(ATOM1_CH2_P33_11, 50, 180, 0.5, 2.5, 180);
    servo_right = servo_init(ATOM0_CH1_P33_9, 50, 0, 0.5, 2.5, 180); // 50Hz, 0.5ms~2.5ms, 360度
    // test_servo();

    emm42_1 = emm42_init(UART_3, UART3_RX_P15_7, UART3_TX_P15_6, 115200, EMM42_CHKSUM_CONST_6B);
    // test_emm42();

    signal_dev = signal_uart_init(UART_2, UART2_RX_P10_6, UART2_TX_P10_5, 115200);
    test_signal();
    // MAX30102 = MAX30102_init(P13_0, P14_6, MODE_HR_ONLY);

    // lidar_left = stp23l_init(UART_8, UART8_RX_P33_6, UART8_TX_P33_7, 230400);
    // lidar_front = stp23l_init(UART_6, UART6_RX_P23_1, UART6_TX_P22_0, 230400);

    // maixcam1 = maixcam_uart_init(UART_10, UART10_RX_P13_1, UART10_TX_P00_8, 115200);

    // asrpro1 = asrpro_init(UART_2, UART2_RX_P33_8, UART2_TX_P33_9, 9600);

    imu_init(IMU_DEVICE_963RA);
    attitude_init(ATTITUDE_EKF);
    pit_ms_init(CCU60_CH1, PIT_ATTITUDE_T);
    pit_enable(CCU60_CH1);
    // test_imu();

    // key_init_rewrite(KEY_NUM); // 初始化按键
    // pit_ms_init(CCU60_CH0, PIT_KEY_T);
    // pit_enable(CCU60_CH0);

    // control_init();
    // pit_ms_init(CCU61_CH0, PIT_CONTROL_T);
    // pit_enable(CCU61_CH0);

    // pit_ms_init(CCU61_CH1, 10);
    // pit_enable(CCU61_CH1);
}