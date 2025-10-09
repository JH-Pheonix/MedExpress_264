#include "main_control.h"

int qrcode = 13;
car_pos_t car_pos[2] = {0}; // 记录车身姿态和激光测距数据

void main_control()
{
    move_to_point(0, 4, 1000);

    // waiting for data

    move_to_point(4, qrcode / 10, 1000);
    // 第一次调整
    adjust_position(qrcode / 10, 1000, car_pos[0].front, car_pos[0].side, 0.05);
    adjust_angle(car_pos[0].yaw, 500, 2);

    // 第二次调整
    adjust_position(qrcode / 10, 1000, car_pos[0].front, car_pos[0].side, 0.05);
    adjust_angle(car_pos[0].yaw, 500, 2);
}