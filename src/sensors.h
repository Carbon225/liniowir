#ifndef _APP_SENSORS_H_
#define _APP_SENSORS_H_

#include <stdint.h>

#define APP_NUM_SENSORS 24

void sensors_init(void);

void sensors_read(uint32_t *pulse_lengths_us);

void sensors_read_oversampled(uint32_t *pulse_lengths_us, int oversampling);

void sensors_calibrate(void);

void sensors_apply_calibration(uint32_t *values_in, uint32_t *values_out);

#endif
