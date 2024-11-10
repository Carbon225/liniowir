#include "imu.h"

#include <vector>

#include "pico/stdlib.h"

#include "mpu9250/mpu9250.h"
#include "fusion/mahony.h"

#define USE_MAGNETOMETER 0

typedef struct
{
    MPU9250 mpu;
    Mahony fusion;
} imu_impl_t;

static imu_impl_t *impl;
static uint32_t last_update_time = 0;

extern "C" void imu_init()
{
    impl = new imu_impl_t {};
    impl->mpu.configure();
}

extern "C" void imu_read(imu_data_t *data)
{
    uint32_t now = time_us_32();

    if (last_update_time == 0)
    {
        last_update_time = now;
    }

    float dt = (now - last_update_time) * 1e-6f;
    last_update_time = now;

    std::vector<double> data_raw = impl->mpu.readGyroAccMag();

    data->gx = data_raw[0];
    data->gy = data_raw[1];
    data->gz = data_raw[2];

    data->ax = data_raw[3];
    data->ay = data_raw[4];
    data->az = data_raw[5];

    data->mx = data_raw[6];
    data->my = data_raw[7];
    data->mz = data_raw[8];

#if USE_MAGNETOMETER
    impl->fusion.update(
        data->gx, data->gy, data->gz,
        data->ax, data->ay, data->az,
        data->mx, data->my, data->mz,
        dt);
#else
    impl->fusion.updateIMU(
        data->gx, data->gy, data->gz,
        data->ax, data->ay, data->az,
        dt);
#endif

    data->roll = impl->fusion.getRoll();
    data->pitch = impl->fusion.getPitch();
    data->yaw = impl->fusion.getYaw();
}
