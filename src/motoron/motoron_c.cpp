#include "motoron_c.h"

#include "Motoron.h"

#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define MAX_SPEED (800)

#define NUM_MOTORS 3
#define BAT_REF_MV (3700 * 3)
#define USE_COMPENSATION 1
#define LOGIC_MV 3300

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
}

extern "C" void motoron_set_speed(motoron_t *motoron, uint8_t motor, int16_t speed)
{
    MotoronI2C *mc = (MotoronI2C*) motoron->impl;

#if USE_COMPENSATION
    uint32_t vin_mv = mc->getVinVoltageMv(LOGIC_MV, MotoronVinSenseType::Motoron256);
    uint32_t speed32 = speed;
    speed32 = speed32 * BAT_REF_MV / vin_mv;
    speed = speed32;
#endif

    speed = CLAMP(speed, -MAX_SPEED, MAX_SPEED);

    mc->setSpeedNow(motor, speed);
}
