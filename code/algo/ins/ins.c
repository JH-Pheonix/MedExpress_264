#include "ins.h"

float ins_cal_dis(vint16 encoder_cnt)
{
    float speed = encoder_cnt / 1024.0 * (60 * 3.1415926) * 11000.0 / 500.0 / 200.0 * 183.0;
    return speed * INS_UPDATE_T / 1000.0;
}