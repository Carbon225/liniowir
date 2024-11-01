#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/watchdog.h"

#include "motors.h"
#include "sensors.h"

#define DEBUG

#define LED_PIN (PICO_DEFAULT_LED_PIN)

static void decide_direction(float *x, float *y, const uint32_t *pulse_lengths_us)
{
    static int last_direction_idx = 20;
    int left_idx = last_direction_idx;
    int right_idx = last_direction_idx;
    for (int i = 0; i < APP_NUM_SENSORS / 2 - 1; i++)
    {
        int left_state = pulse_lengths_us[left_idx] > 500 ? 1 : 0;
        int right_state = pulse_lengths_us[right_idx] > 500 ? 1 : 0;

        if (left_state)
        {
            last_direction_idx = left_idx;
            break;
        }

        if (right_state)
        {
            last_direction_idx = right_idx;
            break;
        }

        left_idx = (left_idx + 1) % APP_NUM_SENSORS;
        right_idx--;
        if (right_idx < 0)
        {
            right_idx = APP_NUM_SENSORS - 1;
        }
    }

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

    float angle = (last_direction_idx - 14.5f) / APP_NUM_SENSORS * 2 * ((float) M_PI);

    float cxx = cx * cosf(-(angle - ((float) M_PI_2))) - cy * sinf(-(angle - ((float) M_PI_2)));

    *x = cosf(angle) * 0.4f + cxx * cosf(angle - ((float) M_PI_2)) * 0.7f;
    *y = sinf(angle) * 0.4f + cxx * sinf(angle - ((float) M_PI_2)) * 0.7f;
}

int main()
{
    // watchdog_enable(100, 1);

    stdio_init_all();

    if (watchdog_caused_reboot())
    {
        printf("Watchdog caused reboot\n");
    }

    motors_init();
    sensors_init();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    uint32_t pulse_lengths_us_1[APP_NUM_SENSORS] = {0};
    uint32_t pulse_lengths_us[APP_NUM_SENSORS] = {0};

    float x = 0.0f;
    float y = 0.0f;

    for (;;)
    {
        // sensors_read(pulse_lengths_us);
        for (int i = 0; i < APP_NUM_SENSORS; i++)
        {
            pulse_lengths_us[i] = 0;
        }
        for (int i = 0; i < 10; i++)
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
        decide_direction(&x, &y, pulse_lengths_us);
        motors_set(x, y, 0.0f);
        // printf("x: %f\ty: %f\n", x, y);
        // printf("Pulse lengths:\n");
        // for (int i = 0; i < APP_NUM_SENSORS; i++)
        // {
        //     printf(" %d: %u us\n", i, pulse_lengths_us[i]);
        // }
        // printf("\n");
        // sleep_ms(100);
    }

    return 0;
}
