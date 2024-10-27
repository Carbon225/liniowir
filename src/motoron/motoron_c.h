#ifndef MOTORON_C_H
#define MOTORON_C_H

#ifdef __cplusplus
#include <cstdint>
extern "C"
{
#else
#include <stdint.h>
#endif

typedef struct
{
    void *impl;
} motoron_t;

void motoron_init(motoron_t *motoron);

void motoron_set_speed(motoron_t *motoron, uint8_t motor, int16_t speed);

#ifdef __cplusplus
}
#endif

#endif
