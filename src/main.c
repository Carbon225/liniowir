#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/watchdog.h"
#include "hardware/i2c.h"

#include "motors.h"
#include "sensors.h"
#include "imu.h"
#include "bootsel_button.h"

// #define DEBUG

#define DISABLE_WITH_BUTTON 0
#define DISABLE_IN_THE_AIR 1

#define SENSOR_OVERSAMPLING 3
#define SENSOR_THRESHOLD 400

int wrap_idx(int idx)
{
    return (idx + APP_NUM_SENSORS) % APP_NUM_SENSORS;
}

static float get_centroid_around_direction(int direction_idx, const uint32_t *pulse_lengths_us)
{
    float left = pulse_lengths_us[wrap_idx(direction_idx + 1)];
    float center = pulse_lengths_us[direction_idx];
    float right = pulse_lengths_us[wrap_idx(direction_idx - 1)];
    if (left < SENSOR_THRESHOLD && center < SENSOR_THRESHOLD && right < SENSOR_THRESHOLD)
    {
        return 1e6f;
    }
    return (left * 1.0f + center * 0.0f + right * (-1.0f)) / (left + center + right);
}

static void decide_direction(float *x, float *y, const uint32_t *pulse_lengths_us)
{
    static int last_direction_idx = 20;
    static float last_direction_angle = (float) M_PI_2;

    int left_idx = last_direction_idx;
    int right_idx = last_direction_idx;
    float new_centroid = 1e6f;

    for (int i = 0; i < APP_NUM_SENSORS / 2 - 2; i++)
    {
        float left_centroid = get_centroid_around_direction(left_idx, pulse_lengths_us);
        float right_centroid = get_centroid_around_direction(right_idx, pulse_lengths_us);

        if (left_centroid < 1e5f)
        {
            new_centroid = left_centroid;
            break;
        }

        if (right_centroid < 1e5f)
        {
            new_centroid = right_centroid;
            break;
        }

        left_idx = wrap_idx(left_idx + 1);
        right_idx = wrap_idx(right_idx - 1);
    }

    if (new_centroid > 1e5f)
    {
        new_centroid = 0.0f;
    }

    last_direction_angle += new_centroid / APP_NUM_SENSORS * 2.0f * ((float) M_PI) * 0.4f;
    while (last_direction_angle > ((float) M_PI))
    {
        last_direction_angle -= ((float) M_PI) * 2.0f;
    }
    while (last_direction_angle < -((float) M_PI))
    {
        last_direction_angle += ((float) M_PI) * 2.0f;
    }

    last_direction_idx = (int) roundf(last_direction_angle / ((float) M_PI) / 2.0f * APP_NUM_SENSORS + 14.5f);

    float cx = 0.0f;
    float cy = 0.0f;
    float weight_sum = 0.0f;

    for (int i = 0; i < APP_NUM_SENSORS; i++)
    {
        float angle = (i - 14.5f) / APP_NUM_SENSORS * 2 * ((float) M_PI);
        cx += cosf(angle) * pulse_lengths_us[i];
        cy += sinf(angle) * pulse_lengths_us[i];
        weight_sum += pulse_lengths_us[i];
    }

    if (weight_sum > 0.0f)
    {
        cx /= weight_sum;
        cy /= weight_sum;
    }

    float angle = last_direction_angle;

    float cxx = cx * cosf(-(angle - ((float) M_PI_2))) - cy * sinf(-(angle - ((float) M_PI_2)));

    *x = cosf(angle) * 0.4f + cxx * cosf(angle - ((float) M_PI_2)) * 0.5f;
    *y = sinf(angle) * 0.4f + cxx * sinf(angle - ((float) M_PI_2)) * 0.5f;
}

int main()
{
#ifndef DEBUG
    watchdog_enable(8000, 1);
#endif

    stdio_init_all();

#ifdef DEBUG
    while (!stdio_usb_connected())
    {
        sleep_ms(10);
    }
#endif

    if (watchdog_caused_reboot())
    {
        printf("Watchdog caused reboot\n");
    }

    i2c_init(i2c_default, 400000);
    gpio_set_function(0, GPIO_FUNC_I2C);
    gpio_set_function(1, GPIO_FUNC_I2C);

    motors_init();
    sensors_init();
    imu_init();

    uint32_t pulse_lengths_us_1[APP_NUM_SENSORS] = {0};
    uint32_t pulse_lengths_us[APP_NUM_SENSORS] = {0};

    float x = 0.0f;
    float y = 0.0f;

    printf("Waiting for button press...\n");

    while (!bootsel_button_get())
    {
        sleep_ms(10);
        watchdog_update();
    }

    while (bootsel_button_get())
    {
        sleep_ms(10);
        watchdog_update();
    }

    printf("Button pressed!\n");

    for (int i = 0; i < 20; i++)
    {
        sleep_ms(50);
        watchdog_update();
    }

    for (;;)
    {
        watchdog_update();

#if DISABLE_WITH_BUTTON
        if (bootsel_button_get())
        {
            printf("Stopping...\n");
            motors_set(0.0f, 0.0f, 0.0f);
            for (int i = 0; i < 20; i++)
            {
                sleep_ms(50);
                watchdog_update();
            }
            for (;;);
        }
#endif

        imu_data_t imu_data;
        imu_read(&imu_data);

        for (int i = 0; i < APP_NUM_SENSORS; i++)
        {
            pulse_lengths_us[i] = 0;
        }
        for (int i = 0; i < SENSOR_OVERSAMPLING; i++)
        {
            sensors_read(pulse_lengths_us_1);
            for (int j = 0; j < APP_NUM_SENSORS; j++)
            {
                if (pulse_lengths_us_1[j] > pulse_lengths_us[j])
                {
                    pulse_lengths_us[j] = pulse_lengths_us_1[j];
                }
            }
        }

#if DISABLE_IN_THE_AIR
        bool in_the_air = true;
        for (int i = 0; i < APP_NUM_SENSORS; i++)
        {
            if (pulse_lengths_us[i] < 1000)
            {
                in_the_air = false;
                break;
            }
        }
        if (in_the_air)
        {
            printf("Stopping...\n");
            motors_set(0.0f, 0.0f, 0.0f);
            for (int i = 0; i < 20; i++)
            {
                sleep_ms(50);
                watchdog_update();
            }
            for (;;);
        }
#endif

#ifdef DEBUG
        printf("\n");
        printf("Gyr:\n %f\n %f\n %f\n", imu_data.gx, imu_data.gy, imu_data.gz);
        printf("Acc:\n %f\n %f\n %f\n", imu_data.ax, imu_data.ay, imu_data.az);
        printf("Mag:\n %f\n %f\n %f\n", imu_data.mx, imu_data.my, imu_data.mz);
        printf("RPY:\n %f\n %f\n %f\n", imu_data.roll, imu_data.pitch, imu_data.yaw);
        printf("\n");
#endif

        float yaw_err = 180.0f - imu_data.yaw;
        float turn_cmd = yaw_err * 0.01f;

        decide_direction(&x, &y, pulse_lengths_us);
        motors_set(x, y, turn_cmd);

#ifdef DEBUG
        printf("x: %f\ty: %f\n", x, y);
        printf("Pulse lengths:\n");
        for (int i = 0; i < APP_NUM_SENSORS; i++)
        {
            printf(" %d: %u us\n", i, pulse_lengths_us[i]);
        }
        printf("\n");
        sleep_ms(100);
#endif
    }

    return 0;
}
