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

#include "nanocoap.h"
#include "nanocoap_sock.h"

#include "xtimer.h"


// from monica
// standard
 #include <inttypes.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
// riot
#include "board.h"
#include "log.h"
#include "msg.h"
#include "net/af.h"
#include "net/gnrc/ipv6.h"
#include "net/gnrc/netapi.h"
#include "net/gnrc/netif.h"
#include "periph/gpio.h"
#include "shell.h"
#include "xtimer.h"


// gpio stuff
#include "periph/gpio.h"


#define COAP_INBUF_SIZE (256U)

#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

/* import "ifconfig" shell command, used for printing addresses */
extern int _netif_config(int argc, char **argv);

// from monica
extern int coap_init(void);
extern int createObsMessage(int resourceNumber);
// extern int check(int num);

// prototypes
void ISR_SW0(void);
// extern int createObsMessage(int resourceNumber);


int main(void)
{
    int ret = 0;

    puts("RIOT nanocoap example application");

    
    printf("===================================\n");
    puts("\n---\nOWN NANOSERVER\n---\n");

    // printf("MAIN: ");
    // ret = check(100);
    // printf("return of check: %i\n", ret);

    // init sw0
    ret = gpio_init_int(GPIO_PIN(PA,28), GPIO_IN_PU, GPIO_FALLING, (gpio_cb_t)ISR_SW0, NULL);
    if(ret < 0)
        printf("ERR: gpio init int did not work\n");


    // from monica 
    // start coap thread (causing the double handling of resources, together with the nanocoap handling)
    LOG_INFO(".. init coap\n");
    if(coap_init() < 0) {
        return 1;
    }
    // end

    // usual stuff

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

void ISR_SW0(void){
    printf("\nISR called\n");
    
    int ret = -1;
    
    ret = createObsMessage(4);
    
    if(ret < 0)
        printf("createObsMessage did not work!\n");

    debugPrintf("\n --- test msg --- \n");
}