#ifndef _APP_IMU_H_
#define _APP_IMU_H_

typedef struct
{
    float ax;
    float ay;
    float az;

    float gx;
    float gy;
    float gz;

    float mx;
    float my;
    float mz;

    float roll;
    float pitch;
    float yaw;
} imu_data_t;

#ifdef __cplusplus
extern "C" {
#endif

void imu_init();

void imu_read(imu_data_t *data);

#ifdef __cplusplus
}
#endif

#endif
