#include "picow_httpd.h"

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "lwip/ip4_addr.h"
#include "lwip/apps/mdns.h"
#include "lwip/init.h"
#include "lwip/apps/httpd.h"

#include "FreeRTOS.h"
#include "task.h"

void httpd_init(void);

static absolute_time_t wifi_connected_time;
static bool led_on = false;

static const char *cgi_handler_test(__unused int iIndex, __unused int iNumParams, char *pcParam[], __unused char *pcValue[])
{
    if (!strcmp(pcParam[0], "test"))
    {
        return "/test.shtml";
    }
    else if (strcmp(pcParam[0], "toggleled") == 0)
    {
        led_on = !led_on;
        cyw43_gpio_set(&cyw43_state, 0, led_on);
    }
    return "/index.shtml";
}

static tCGI cgi_handlers[] = {
    {"/", cgi_handler_test},
    {"/index.shtml", cgi_handler_test},
};

// Note that the buffer size is limited by LWIP_HTTPD_MAX_TAG_INSERT_LEN, so use LWIP_HTTPD_SSI_MULTIPART to return larger amounts of data
static u16_t ssi_example_ssi_handler(int iIndex, char *pcInsert, int iInsertLen
#if LWIP_HTTPD_SSI_MULTIPART
                                     ,
                                     uint16_t current_tag_part, uint16_t *next_tag_part
#endif
)
{
    size_t printed;
    switch (iIndex)
    {
    case 0:
    { /* "status" */
        printed = snprintf(pcInsert, iInsertLen, "Pass");
        break;
    }
    case 1:
    { /* "welcome" */
        printed = snprintf(pcInsert, iInsertLen, "Hello from Pico");
        break;
    }
    case 2:
    { /* "uptime" */
        uint64_t uptime_s = absolute_time_diff_us(wifi_connected_time, get_absolute_time()) / 1e6;
        printed = snprintf(pcInsert, iInsertLen, "%" PRIu64, uptime_s);
        break;
    }
    case 3:
    { // "ledstate"
        printed = snprintf(pcInsert, iInsertLen, "%s", led_on ? "ON" : "OFF");
        break;
    }
#if LWIP_HTTPD_SSI_MULTIPART
    case 4:
    { /* "table" */
        printed = snprintf(pcInsert, iInsertLen, "<tr><td>This is table row number %d</td></tr>", current_tag_part + 1);
        // Leave "next_tag_part" unchanged to indicate that all data has been returned for this tag
        if (current_tag_part < 9)
        {
            *next_tag_part = current_tag_part + 1;
        }
        break;
    }
#endif
    default:
    { /* unknown tag */
        printed = 0;
        break;
    }
    }
    return (u16_t)printed;
}

// Be aware of LWIP_HTTPD_MAX_TAG_NAME_LEN
static const char *ssi_tags[] = {
    "status",
    "welcome",
    "uptime",
    "ledstate",
    "table",
};

void picow_httpd_start(void)
{
    wifi_connected_time = get_absolute_time();

    printf("Running httpd at %s\n", ip4addr_ntoa(netif_ip4_addr(netif_list)));
    httpd_init();

    http_set_cgi_handlers(cgi_handlers, LWIP_ARRAYSIZE(cgi_handlers));
    http_set_ssi_handler(ssi_example_ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}
