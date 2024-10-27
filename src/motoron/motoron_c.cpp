#include "motoron_c.h"

#include "Motoron.h"

#define NUM_MOTORS 3

extern "C" void motoron_init(motoron_t *motoron)
{
    MotoronI2C *mc = new MotoronI2C();
    motoron->impl = (void*) mc;
    mc->reinitialize();
    mc->disableCrc();
    mc->clearResetFlag();

    for (int i = 0; i < NUM_MOTORS; i++)
    {
        mc->setMaxAcceleration(i + 1, 100);
        mc->setMaxDeceleration(i + 1, 100);
    }
}

extern "C" void motoron_set_speed(motoron_t *motoron, uint8_t motor, int16_t speed)
{
    MotoronI2C *mc = (MotoronI2C*) motoron->impl;
    mc->setSpeed(motor, speed);
}
