#include "picow_access_point.h"

#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/ip4_addr.h"
#include "lwip/apps/mdns.h"
#include "lwip/init.h"
#include "lwip/apps/httpd.h"

#include "dhcpserver/dhcpserver.h"
#include "dnsserver/dnsserver.h"

#if LWIP_MDNS_RESPONDER
static void srv_txt(struct mdns_service *service, void *txt_userdata)
{
    err_t res;
    LWIP_UNUSED_ARG(txt_userdata);

    res = mdns_resp_add_service_txtitem(service, "path=/", 6);
    LWIP_ERROR("mdns add service txt failed\n", (res == ERR_OK), return);
}
#endif

static ip_addr_t bind_ip;
static ip4_addr_t bind_mask;
static dhcp_server_t dhcp_server;
static dns_server_t dns_server;

void picow_access_point_start(void)
{
    if (cyw43_arch_init())
    {
        panic("cyw43_arch_init failed\n");
    }

    const char *const ap_name = "liniowir";
    const char *const password = "panzervor";

    cyw43_arch_enable_ap_mode(ap_name, password, CYW43_AUTH_WPA2_AES_PSK);

    const char *const hostname = "liniowir";
    netif_set_hostname(&cyw43_state.netif[CYW43_ITF_AP], hostname);

#if LWIP_MDNS_RESPONDER
    mdns_resp_init();
    printf("mdns host name %s.local\n", hostname);
#if LWIP_VERSION_MAJOR >= 2 && LWIP_VERSION_MINOR >= 2
    mdns_resp_add_netif(&cyw43_state.netif[CYW43_ITF_AP], hostname);
    mdns_resp_add_service(&cyw43_state.netif[CYW43_ITF_AP], "picow_httpd", "_http", DNSSD_PROTO_TCP, 80, srv_txt, NULL);
#else
    mdns_resp_add_netif(&cyw43_state.netif[CYW43_ITF_AP], hostname, 60);
    mdns_resp_add_service(&cyw43_state.netif[CYW43_ITF_AP], "picow_httpd", "_http", DNSSD_PROTO_TCP, 80, 60, srv_txt, NULL);
#endif
#endif

    IP4_ADDR(ip_2_ip4(&bind_ip), 192, 168, 4, 1);
    IP4_ADDR(ip_2_ip4(&bind_mask), 255, 255, 255, 0);

    dhcp_server_init(&dhcp_server, &bind_ip, &bind_mask);
    dns_server_init(&dns_server, &bind_ip);
}
