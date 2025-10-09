#include "move_control.h"

static vuint8 move_mode = 1;
static move_state_t move_state = {0};

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

void move_by_distance(float target_pos, move_axis_enum axis, float speed)
{
    // 这个函数主要用于发布走的方向，然后调用move_to_distance函数
    if (axis == DIR_X && target_pos > move_state.current_distance)
    {
        move_to_distance(target_pos - move_state.current_distance, DIR_FORWARD, speed);
    }
    else if (axis == DIR_X && target_pos <= move_state.current_distance)
    {
        move_to_distance(move_state.current_distance - target_pos, DIR_BACKWARD, speed);
    }
    else if (axis == DIR_Y && target_pos > move_state.current_distance)
    {
        move_to_distance(target_pos - move_state.current_distance, DIR_LEFT, speed);
    }
    else if (axis == DIR_Y && target_pos <= move_state.current_distance)
    {
        move_to_distance(move_state.current_distance - target_pos, DIR_RIGHT, speed);
    }
}

void move_to_distance(float target_distance, move_dir_enum direction, float speed)
{
    // 这个函数是用于发布move命令的，然后move_to_distance_update会去执行
    // 保存运动状态
    move_state.target_distance = target_distance;
    move_state.direction = direction;
    move_state.current_distance = 0;
    move_state.is_running = 1; // 1表示有活干，0表示没活干
}

void move_to_distance_update()
{
    if (move_state.is_running == 0)
        return;
    // 更新距离和状态
    switch (move_state.direction)
    {
    case DIR_FORWARD:
    case DIR_BACKWARD:
        float delta_dis = ins_cal_dis(encoder_get_data(&encoder_x));
        move_state.current_distance += delta_dis;
        move_state.curr_pos.x += delta_dis;
        encoder_reset(&encoder_x);
        break;

    case DIR_LEFT:
    case DIR_RIGHT:
        float delta_dis = ins_cal_dis(encoder_get_data(&encoder_y));
        move_state.current_distance += delta_dis;
        move_state.curr_pos.y += delta_dis;
        encoder_reset(&encoder_y);
        break;
    }

    if (move_state.current_distance >= move_state.target_distance)
    {
        // 停止运动
        move_reset();
        move_state.is_running = 0;
    }

    // 启动匀速运动
    move_control(move_state.direction, move_state.speed, 0);
}

int nurse_x = 1000, midroad_x = 4200;
int bed_y1 = -1500, bed_y3 = 1500, bed_x = 5200;
int obstacl_y_L = -1500, obstacl_y_R = 1500;

void move_to_point(int st_point, int ed_point, float speed)
{
    // 这个函数用于从起点走到终点，调用move_by_distance函数
    // 相当于之前的path work
    if (st_point == 0 && ed_point == 4)
    {
        move_by_distance(nurse_x, DIR_X, speed);
    }
    if ((st_point == 0 || st_point == 4) && ed_point == 1)
    {
        move_by_distance(obstacl_y_L, DIR_Y, speed);
        move_by_distance(midroad_x, DIR_X, speed);
        move_by_distance(bed_y1, DIR_Y, speed);
        move_by_distance(bed_x, DIR_X, speed);
    }
    if ((st_point == 0 || st_point == 4) && ed_point == 3)
    {
        move_by_distance(obstacl_y_R, DIR_Y, speed);
        move_by_distance(midroad_x, DIR_X, speed);
        move_by_distance(bed_y3, DIR_Y, speed);
        move_by_distance(bed_x, DIR_X, speed);
    }
    if (st_point == 3 && ed_point == 0)
    {
        move_by_distance(midroad_x, DIR_X, speed);
        move_by_distance(obstacl_y_R, DIR_Y, speed); // input of obstacle
        move_by_distance(0, DIR_X, speed);
        move_by_distance(0, DIR_Y, speed);
    }
    if (st_point == 1 && ed_point == 0)
    {
        move_by_distance(midroad_x, DIR_X, speed);
        move_by_distance(obstacl_y_L, DIR_Y, speed); // input of obstacle
        move_by_distance(0, DIR_X, speed);
        move_by_distance(0, DIR_Y, speed);
    }
    if (st_point == 1 && ed_point == 3)
    {
        move_by_distance(midroad_x, DIR_X, speed);
        move_by_distance(bed_y3, DIR_Y, speed);
        move_by_distance(bed_x, DIR_X, speed);
    }
    if (st_point == 3 && ed_point == 1)
    {
        move_by_distance(midroad_x, DIR_X, speed);
        move_by_distance(bed_y1, DIR_Y, speed);
        move_by_distance(bed_x, DIR_X, speed);
    }
}

void move_reset(void)
{
    motor_set_pwm(&motor1, 0);
    motor_set_pwm(&motor2, 0);
    motor_set_pwm(&motor3, 0);
    motor_set_pwm(&motor4, 0);
}