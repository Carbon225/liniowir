#include "picow_httpd.h"

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "lwip/ip4_addr.h"
#include "lwip/apps/mdns.h"
#include "lwip/init.h"
#include "lwip/apps/httpd.h"

#include "FreeRTOS.h"
#include "task.h"

#include "liniowir.h"

void httpd_init(void);

static absolute_time_t wifi_connected_time;

static const char *cgi_handler_api(__unused int iIndex, __unused int iNumParams, char *pcParam[], __unused char *pcValue[])
{
    if (!strcmp(pcParam[0], "start"))
    {
        liniowir_set_enabled(true);
    }
    else if (!strcmp(pcParam[0], "stop"))
    {
        liniowir_set_enabled(false);
    }
    return "/index.shtml";
}

static tCGI cgi_handlers[] = {
    {"/api", cgi_handler_api},
};

// Note that the buffer size is limited by LWIP_HTTPD_MAX_TAG_INSERT_LEN, so use LWIP_HTTPD_SSI_MULTIPART to return larger amounts of data
static u16_t ssi_example_ssi_handler(int iIndex, char *pcInsert, int iInsertLen
#if LWIP_HTTPD_SSI_MULTIPART
                                     ,
                                     __unused uint16_t current_tag_part, __unused uint16_t *next_tag_part
#endif
)
{
    size_t printed;
    switch (iIndex)
    {
    case 0:
    { /* "uptime" */
        uint64_t uptime_s = absolute_time_diff_us(wifi_connected_time, get_absolute_time()) / 1e6;
        printed = snprintf(pcInsert, iInsertLen, "%" PRIu64, uptime_s);
        break;
    }
    case 1:
    { /* "forward_speed" */
        printed = snprintf(pcInsert, iInsertLen, "%.3f", liniowir_get_forward_speed());
        break;
    }
    case 2:
    { /* "centering_speed" */
        printed = snprintf(pcInsert, iInsertLen, "%.3f", liniowir_get_centering_speed());
        break;
    }
    case 3:
    { /* "rotation_kp" */
        printed = snprintf(pcInsert, iInsertLen, "%.3f", liniowir_get_rotation_kp());
        break;
    }
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
    "uptime",
    "fsp",
    "csp",
    "rkp",
};

void picow_httpd_start(void)
{
    wifi_connected_time = get_absolute_time();

    printf("Running httpd at %s\n", ip4addr_ntoa(netif_ip4_addr(netif_list)));
    httpd_init();

    http_set_cgi_handlers(cgi_handlers, LWIP_ARRAYSIZE(cgi_handlers));
    http_set_ssi_handler(ssi_example_ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}
