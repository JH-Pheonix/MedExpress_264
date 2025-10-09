#ifndef _CONTROL_move_control_H
#define _CONTROL_move_control_H

#include "zf_common_typedef.h"
#include "init.h"
#include "motor.h"
#include "common.h"

typedef enum
{
    DIR_FORWARD = 0,
    DIR_BACKWARD,
    DIR_LEFT,
    DIR_RIGHT,
} move_dir_enum;

typedef enum
{
    DIR_X,
    DIR_Y
} move_axis_enum;

typedef struct
{
    point_2d curr_pos;       // 当前坐标
    float target_distance;   // 目标距离（米）
    float current_distance;  // 当前已走距离（米）
    move_dir_enum direction; // 运动方向
    vuint16 speed;           // 电机 base 速度
    vuint8 is_running;       // 运行状态标志
} move_state_t;

void move_control(move_dir_enum Dir_now, float motor_vel, float turn_diff);
void move_by_distance(float target_pos, move_axis_enum axis, float speed);
void move_to_distance(float target_distance, move_dir_enum direction, float speed);
void move_to_distance_update();
void move_to_point(int st_point, int ed_point, float speed);
void move_reset(void);

#endif