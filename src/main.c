#include <stdio.h>
#include <math.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/watchdog.h"

#include "motors.h"
#include "sensors.h"

#define DEBUG

#define LED_PIN (PICO_DEFAULT_LED_PIN)

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

    uint32_t pulse_lengths_us[APP_NUM_SENSORS];

    for (;;)
    {
        motors_set(0.0f, 0.0f, 0.0f);

        sensors_read(pulse_lengths_us);
        printf("Pulse lengths:\n");
        for (int i = 0; i < APP_NUM_SENSORS; i++)
        {
            printf("  %u us\n", (pulse_lengths_us[i] < 500) ? 1 : 0);
        }
        printf("\n");
        sleep_ms(100);
    }

    return 0;
}
