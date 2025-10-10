#include "test.h"

void test_motor()
{
    while (1)
    {
        motor_set_pwm(&motor1, 1000);
        lcd_show_char(0, 1, '1');
        system_delay_ms(2000);
        motor_set_pwm(&motor1, 0);
        motor_set_pwm(&motor2, 1000);
        lcd_show_char(0, 1, '2');
        system_delay_ms(2000);
        motor_set_pwm(&motor2, 0);
        motor_set_pwm(&motor3, 1000);
        lcd_show_char(0, 1, '3');
        system_delay_ms(2000);
        motor_set_pwm(&motor3, 0);
        motor_set_pwm(&motor4, 1000);
        lcd_show_char(0, 1, '4');
        system_delay_ms(2000);
        motor_set_pwm(&motor4, 0);
    }
}

void test_move_dir()
{
    while (1)
    {
        move_reset();
        move_control(DIR_FORWARD, 2000, 0);
        lcd_clear();
        lcd_show_string(0, 0, "FORWARD");
        system_delay_ms(10000);

        move_reset();
        move_control(DIR_BACKWARD, 2000, 0);
        lcd_clear();
        lcd_show_string(0, 0, "BACKWARD");
        system_delay_ms(10000);

        move_reset();
        move_control(DIR_LEFT, 2000, 0);
        lcd_clear();
        lcd_show_string(0, 0, "LEFT");
        system_delay_ms(10000);

        move_reset();
        move_control(DIR_RIGHT, 2000, 0);
        lcd_clear();
        lcd_show_string(0, 0, "RIGHT");
        system_delay_ms(10000);
    }
}

void test_lcd()
{
    lcd_clear();
    lcd_show_string(0, 0, "TEST!");
}

void test_stp23l()
{
    while (1)
    {
        stp23l_frame_t lidar_frame;
        stp23l_pop_frame(&lidar_front, &lidar_frame);
        // lcd_show_uint(0, 1, lidar_frame.points[11].distance, 8);
        printf("Lidar Front: %d, ", lidar_frame.points[11].distance);

        stp23l_pop_frame(&lidar_left, &lidar_frame);
        lcd_show_uint(0, 2, lidar_frame.points[11].distance, 8);
        // printf("Lidar Left: %d, ", lidar_frame.points[11].distance);

        stp23l_pop_frame(&lidar_right, &lidar_frame);
        lcd_show_uint(0, 3, lidar_frame.points[11].distance, 8);
        // printf("Lidar Right: %d\n", lidar_frame.points[11].distance);

        system_delay_ms(100);
    }
}

void test_encoder()
{
    while (1)
    {
        lcd_show_int(0, 1, encoder_get_data(&encoder_x), 8);
        // printf("Encoder X: %d, ", encoder_get_data(&encoder_x));

        lcd_show_int(0, 2, encoder_get_data(&encoder_y), 8);
        // printf("Encoder Y: %d\n", encoder_get_data(&encoder_y));

        system_delay_ms(100);
    }
}

void test_servo()
{
    while (1)
    {
        servo_set_angle(&servo_left, 90);
        servo_set_angle(&servo_right, 90);
        system_delay_ms(1000);

        servo_set_angle(&servo_left, 180);
        servo_set_angle(&servo_right, 0);
        system_delay_ms(1000);
    }
}

void test_emm42()
{
    while (1)
    {
        // 伸出
        emm42_position_mode_cmd(&emm42_1, 0, 1, 1500, 240, 5.5 * 3200, 0, 0);
        emm42_send_cmd(&emm42_1);
        system_delay_ms(2000);

        // 收回
        emm42_position_mode_cmd(&emm42_1, 0, 0, 1500, 240, 5.5 * 3200, 0, 0);
        emm42_send_cmd(&emm42_1);
        system_delay_ms(2000);
    }
}

void test_imu()
{
    imu_data_t imu_data;
    while (1)
    {
        imu_data = imu_get_tmp_data();
        lcd_show_float(0, 1, imu_data.accel_x, 3, 3);
        lcd_show_float(0, 2, imu_data.accel_y, 3, 3);
        lcd_show_float(0, 3, imu_data.accel_z, 3, 3);

        lcd_show_float(8, 1, imu_data.gyro_x, 3, 3);
        lcd_show_float(8, 2, imu_data.gyro_y, 3, 3);
        lcd_show_float(8, 3, imu_data.gyro_z, 3, 3);

        lcd_show_float(0, 4, attitude_get_pitch(), 3, 3);
        lcd_show_float(0, 5, attitude_get_roll(), 3, 3);
        lcd_show_float(0, 6, attitude_get_yaw(), 3, 3);

        system_delay_ms(100);
    }
}

vuint32 cnt = 0;
void test_signal()
{
    signal_message_t msg;
    while (1)
    {
        msg = signal_pop_data(&signal_dev);
        lcd_show_int(0, 1, msg.front_dis, 8);
        lcd_show_int(0, 2, msg.left_dis, 8);
        lcd_show_int(0, 3, msg.right_dis, 8);
        system_delay_ms(10);
    }
}

void test_maixcam()
{
    maixcam_message_t msg;
    while (1)
    {
        msg = maixcam_pop_data(&maixcam1);
        // 将uint64转化为string显示
        char buf[20];
        sprintf(buf, "%llu", msg.data);
        lcd_show_string(0, 1, buf);

        system_delay_ms(100);
    }
}

void test_asrpro()
{
    while (1)
    {
        asrpro_set_status(&asrpro1, 1);
        lcd_clear();
        lcd_show_string(0, 1, "one");
        system_delay_ms(5000);
        asrpro_set_status(&asrpro1, 2);
        lcd_clear();
        lcd_show_string(0, 1, "two");
        system_delay_ms(5000);
        asrpro_set_status(&asrpro1, 3);
        lcd_clear();
        lcd_show_string(0, 1, "three");
        system_delay_ms(5000);
    }
}