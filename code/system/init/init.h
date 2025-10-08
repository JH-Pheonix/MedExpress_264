#ifndef _SYSTEM_INIT_H_
#define _SYSTEM_INIT_H_

#include "imu.h"
#include "motor.h"
#include "key.h"
#include "lcd.h"
#include "attitude.h"
#include "stp23l.h"
#include "maixcam.h"
#include "asrpro.h"
#include "emm42.h"
#include "servo.h"
#include "encoder.h"
#include "MAX30102.h"
#include "signal.h"

void system_init(void);

extern motor_obj_t motor1, motor2, motor3, motor4;
extern encoder_obj_t encoder_x, encoder_y;
extern stp23l_obj_t lidar_left, lidar_right, lidar_front;
extern servo_obj_t servo_left, servo_right;
extern maixcam_obj_t maixcam1;
extern asrpro_obj_t asrpro1;
extern emm42_obj_t emm42_1;
extern MAX30102_obj_t MAX30102;
extern signal_obj_t signal_dev;

#endif