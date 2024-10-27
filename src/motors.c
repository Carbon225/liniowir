#include "motors.h"

#include "math.h"

#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"

#include "motoron/motoron_c.h"

#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define MAX_SPEED (800)

static motoron_t motoron;

void motors_init(void)
{
    i2c_init(i2c_default, 400000);
    gpio_set_function(0, GPIO_FUNC_I2C);
    gpio_set_function(1, GPIO_FUNC_I2C);

    motoron_init(&motoron);
}

void motors_set(float x, float y, float theta)
{
    float m1, m2, m3;

    m1 = -theta - x;
    m2 = -theta + 0.5f * x + sinf(M_PI / 3.f) * y;
    m3 = -theta + 0.5f * x - sinf(M_PI / 3.f) * y;

    CLAMP(m1, -1.f, 1.f);
    CLAMP(m2, -1.f, 1.f);
    CLAMP(m3, -1.f, 1.f);

    motoron_set_speed(&motoron, 1, -m1 * MAX_SPEED);
    motoron_set_speed(&motoron, 2, -m2 * MAX_SPEED);
    motoron_set_speed(&motoron, 3, -m3 * MAX_SPEED);
}
