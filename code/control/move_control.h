#ifndef _CONTROL_move_control_H
#define _CONTROL_move_control_H

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
void move_reset(void);

#endif