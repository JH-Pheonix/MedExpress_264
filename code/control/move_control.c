#include "move_control.h"

static vuint8 move_mode = 1;

void move_control(move_dir_enum Dir_now, float motor_vel, float turn_diff)
{
    if (Dir_now == DIR_FORWARD && move_mode == 0)
    {
        motor_set_pwm(&motor3, motor_vel - turn_diff);
        motor_set_pwm(&motor4, -motor_vel - turn_diff);
    }
    if (Dir_now == DIR_BACKWARD && move_mode == 0)
    {
        motor_set_pwm(&motor3, -motor_vel - turn_diff);
        motor_set_pwm(&motor4, motor_vel - turn_diff);
    }
    if (Dir_now == DIR_LEFT && move_mode == 0)
    {
        motor_set_pwm(&motor1, -motor_vel - turn_diff);
        motor_set_pwm(&motor2, motor_vel - turn_diff);
    }
    if (Dir_now == DIR_RIGHT && move_mode == 0)
    {
        motor_set_pwm(&motor1, motor_vel - turn_diff);
        motor_set_pwm(&motor2, -motor_vel - turn_diff);
    }

    if (Dir_now == DIR_FORWARD && move_mode == 1)
    {
        motor_set_pwm(&motor3, motor_vel - turn_diff);
        motor_set_pwm(&motor4, -motor_vel - turn_diff); // front

        motor_set_pwm(&motor1, -motor_vel - turn_diff);
        motor_set_pwm(&motor2, motor_vel - turn_diff); // left
    }
    if (Dir_now == DIR_BACKWARD && move_mode == 1)
    {
        motor_set_pwm(&motor3, -motor_vel - turn_diff);
        motor_set_pwm(&motor4, motor_vel - turn_diff); // back

        motor_set_pwm(&motor1, motor_vel - turn_diff);
        motor_set_pwm(&motor2, -motor_vel - turn_diff); // right
    }
    if (Dir_now == DIR_LEFT && move_mode == 1)
    {
        motor_set_pwm(&motor1, -motor_vel - turn_diff);
        motor_set_pwm(&motor2, motor_vel - turn_diff); // left

        motor_set_pwm(&motor3, -motor_vel - turn_diff);
        motor_set_pwm(&motor4, motor_vel - turn_diff); // back
    }
    if (Dir_now == DIR_RIGHT && move_mode == 1)
    {
        motor_set_pwm(&motor1, motor_vel - turn_diff);
        motor_set_pwm(&motor2, -motor_vel - turn_diff); // right

        motor_set_pwm(&motor3, motor_vel - turn_diff);
        motor_set_pwm(&motor4, -motor_vel - turn_diff); // front
    }
}

void move_reset(void)
{
    motor_set_pwm(&motor1, 0);
    motor_set_pwm(&motor2, 0);
    motor_set_pwm(&motor3, 0);
    motor_set_pwm(&motor4, 0);
}