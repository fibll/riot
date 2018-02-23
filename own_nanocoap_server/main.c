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








// own stuff
// prototypes
//static ssize_t _riot_bar_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len);



/* internal value that can be read/written via CoAP */
//static uint8_t internal_value = 0;


// put to the top
/* must be sorted by path (alphabetically) */
/*
coap_resource_t gcoap_resources = 
    { "/riot/bar", COAP_GET, _riot_bar_handler };
*/
// own stuff end


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