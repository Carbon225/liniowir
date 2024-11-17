#include "motoron_c.h"

#include "Motoron.h"

#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define MAX_SPEED (800)

#define NUM_MOTORS 3
#define BAT_REF_MV (3700 * 3)
#define LOGIC_MV 3300

static uint32_t g_vin_mv = 0;

extern "C" void motoron_init(motoron_t *motoron)
{
    MotoronI2C *mc = new MotoronI2C();
    motoron->impl = (void*) mc;
    mc->reinitialize();
    mc->disableCrc();
    mc->clearResetFlag();

    for (int i = 0; i < NUM_MOTORS; i++)
    {
        mc->setMaxAcceleration(i + 1, 400);
        mc->setMaxDeceleration(i + 1, 400);
    }

    g_vin_mv = mc->getVinVoltageMv(LOGIC_MV, MotoronVinSenseType::Motoron256);
}

extern "C" void motoron_set_speed(motoron_t *motoron, uint8_t motor, int16_t speed)
{
    MotoronI2C *mc = (MotoronI2C*) motoron->impl;
    speed = CLAMP(speed, -MAX_SPEED, MAX_SPEED);
    mc->setSpeedNow(motor, speed);
}

extern "C" float motoron_voltage_compensate_value(float value)
{
    return value * (((float) BAT_REF_MV) / ((float) g_vin_mv));
}
