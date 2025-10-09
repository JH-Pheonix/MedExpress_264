#ifndef _CONTROL_ADJUST_CONTROL_H_
#define _CONTROL_ADJUST_CONTROL_H_

#include "zf_common_typedef.h"
#include "init.h"
#include "signal.h"
#include "move_control.h"
#include "attitude.h"

void adjust_position(vuint8 bed_now, float speed, float tar_x, float tar_y, float ok_area);
void adjust_angle(float tar_angle, float speed, float ok_angle);
void adjust_control(vuint8 bed_now, float speed);

#endif