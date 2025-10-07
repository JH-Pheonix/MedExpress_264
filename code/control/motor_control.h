#ifndef _CONTROL_MOTOR_CONTROL_H
#define _CONTROL_MOTOR_CONTROL_H

#include "zf_common_typedef.h"
#include "init.h"
#include "motor.h"

typedef enum
{
    DIR_FORWARD = 0,
    DIR_BACKWARD,
    DIR_LEFT,
    DIR_RIGHT,
} move_dir_enum;

void move_control(move_dir_enum Dir_now, float motor_vel, float turn_diff);
void motor_reset(void);

#endif