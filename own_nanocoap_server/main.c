/*
 * Copyright (C) 2016 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       CoAP example server application (using nanocoap)
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @}
 */

#include <stdio.h>

#include "/home/bar/projekte/htw/RIOT/sys/include/net/gcoap.h"

#include "nanocoap.h"
#include "nanocoap_sock.h"
//#include "net/gcoap.h"
//#include "/home/bar/projekte/htw/RIOT/sys/net/application_layer/gcoap/gcoap.c"

#include "xtimer.h"

#define COAP_INBUF_SIZE (256U)

#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

/* import "ifconfig" shell command, used for printing addresses */
extern int _netif_config(int argc, char **argv);

int main(void)
{

    puts("RIOT nanocoap example application");

    /*
    printf("===================================\n");
    puts("\n---\nOWN NANOSERVER\n---\n");

    // test if gcoap functions can be used
    kernel_pid_t value = gcoap_init();
    printf("KERNEL_PID: %i\n\n", value);
    
    // tmp vars
    coap_pkt_t* arg1 = NULL;
    uint8_t* arg2 = NULL;
    size_t arg3 = 5;
    const coap_resource_t* arg4 = NULL;

    printf("Codes: ");
    printf("OK: %i\n", GCOAP_OBS_INIT_OK);
    printf("ERR: %i\n", GCOAP_OBS_INIT_ERR);
    printf("UNUSED: %i\n\n", GCOAP_OBS_INIT_UNUSED);
    
    printf("GCOAP_RESP_INIT: %i\n\n", gcoap_obs_init(arg1, arg2, arg3, arg4));
    

    printf("===================================\n");
    */

    /* nanocoap_server uses gnrc sock which uses gnrc which needs a msg queue */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    puts("Waiting for address autoconfiguration...");
    xtimer_sleep(3);

    /* print network addresses */
    puts("Configured network interfaces:");
    _netif_config(0, NULL);

    /* initialize nanocoap server instance */
    uint8_t buf[COAP_INBUF_SIZE];
    sock_udp_ep_t local = { .port=COAP_PORT, .family=AF_INET6 };
    nanocoap_server(&local, buf, sizeof(buf));

    /* should be never reached */
    return 0;
}
