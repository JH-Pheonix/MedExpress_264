#include "adjust_control.h"

void adjust_position(vuint8 bed_now, float speed, float tar_x, float tar_y, float ok_area)
{
    // 通过tof位置调整位置，要调用两次，调整一次之后调整朝向然后再调整一次
    signal_message_t signal = signal_pop_data(&signal_dev);

    switch (bed_now)
    {
    case 1:
        while (fabs(signal.left_dis - tar_y) > ok_area)
        {
            if (signal.left_dis > tar_y)
                move_control(DIR_RIGHT, speed, 0);
            else
                move_control(DIR_LEFT, speed, 0);

            signal = signal_pop_data(&signal_dev);
        }

        while (fabs(signal.front_dis - tar_x) > ok_area)
        {
            if (signal.front_dis > tar_x)
                move_control(DIR_BACKWARD, speed, 0);
            else
                move_control(DIR_FORWARD, speed, 0);

            signal = signal_pop_data(&signal_dev);
        }

        break;
    case 3:
        while (fabs(signal.right_dis - tar_y) > ok_area)
        {
            if (signal.right_dis > tar_y)
                move_control(DIR_RIGHT, speed, 0);
            else
                move_control(DIR_LEFT, speed, 0);

            signal = signal_pop_data(&signal_dev);
        }

        while (fabs(signal.front_dis - tar_x) > ok_area)
        {
            if (signal.front_dis > tar_x)
                move_control(DIR_BACKWARD, speed, 0);
            else
                move_control(DIR_FORWARD, speed, 0);

            signal = signal_pop_data(&signal_dev);
        }

        break;
    default:
        break;
    }
}

void adjust_angle(float tar_angle, float speed, float ok_angle)
{
    // 通过tof位置调整角度
    signal_message_t signal = signal_pop_data(&signal_dev);
    float current_angle = attitude_get_yaw();

    while (fabs(current_angle - tar_angle) > ok_angle)
    {
        if (current_angle > tar_angle)
            move_control(DIR_LEFT, speed, 0);
        else
            move_control(DIR_RIGHT, speed, 0);

        signal = signal_pop_data(&signal_dev);
        current_angle = attitude_get_yaw();
    }
}

void adjust_control(vuint8 bed_now)
{
    adjust_position(bed_now, , TARGET_X, TARGET_Y, OK_AREA);
    adjust_angle(TARGET_ANGLE, DEFAULT_SPEED, OK_ANGLE);
}