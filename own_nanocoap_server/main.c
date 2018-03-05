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

//#include "/home/bar/projekte/htw/RIOT/sys/include/net/gcoap.h"

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

#define COAP_INBUF_SIZE (256U)

#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

/* import "ifconfig" shell command, used for printing addresses */
extern int _netif_config(int argc, char **argv);

// from monica
extern int coap_init(void);


int main(void)
{

    puts("RIOT nanocoap example application");

    
    printf("===================================\n");
    puts("\n---\nOWN NANOSERVER\n---\n");


    // from monica 
    // start coap thread
    LOG_INFO(".. init coap\n");
    if(coap_init() < 0) {
        return 1;
    }
    // end




    // must be in main?

    // coap obs stuff
    /*
    // detect observe option with gcoap bib
    // step 1: check if resource is already been observed
    // ------
    // init with given arguments, cause these are the values of the resource
    ret = gcoap_obs_init(pkt, buf, len, &coap_resources[3]);
    if(ret == GCOAP_OBS_INIT_ERR)
        LOG_DEBUG("ERR: gcoap observe init did not work\n");
    else if(ret == GCOAP_OBS_INIT_UNUSED)
        LOG_DEBUG("No observer for this resource\n");
    else
        LOG_DEBUG("Observe init response: %i\n", ret);

    // step 2: create own payload and set it as payload in the package pointer
    // ------
    uint8_t* tmpPayload = (uint8_t*)"observe";
    pkt->payload = tmpPayload;
    LOG_DEBUG("new payload: %s\n", pkt->payload);

    // step 3: update the packet for the payload
    // ------
    ret = gcoap_finish(pkt, 4, COAP_FORMAT_NONE); // 4 cause tmpPayloads size is 3, don't know how strlen works
    if(ret < 0)
        LOG_DEBUG("ERR: gcoap_finish did not work!\n");

    // step 4 (final): send observe message
    // ------
    // FIX: does not work so far
    ret = gcoap_obs_send(buf, len, &coap_resources[3]); //Adress of observe resource
    if(ret == 0)
        LOG_DEBUG("ERR: cannot send!\n");
    // end
    */









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