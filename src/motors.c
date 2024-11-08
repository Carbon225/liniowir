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
    motoron_init(&motoron);
}

void motors_set(float x, float y, float theta)
{
    theta = CLAMP(theta, -0.3f, 0.3f);

    float norm = sqrtf(x * x + y * y);
    float scale = norm > 1.f ? 1.f / norm : 1.f;
    x *= scale;
    y *= scale;

    float m1 = -theta - x;
    float m2 = -theta + 0.5f * x + sinf(M_PI / 3.f) * y;
    float m3 = -theta + 0.5f * x - sinf(M_PI / 3.f) * y;

    CLAMP(m1, -1.f, 1.f);
    CLAMP(m2, -1.f, 1.f);
    CLAMP(m3, -1.f, 1.f);

    motoron_set_speed(&motoron, 1, -m1 * MAX_SPEED);
    motoron_set_speed(&motoron, 2, -m2 * MAX_SPEED);
    motoron_set_speed(&motoron, 3, -m3 * MAX_SPEED);
}
