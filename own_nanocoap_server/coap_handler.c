/*
 * Copyright (C) 2016 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fmt.h"
#include "nanocoap.h"

#include "net/gcoap.h"
#include "/home/bar/projekte/htw/RIOT/sys/net/application_layer/gcoap/gcoap.c"


/* internal value that can be read/written via CoAP */
static uint8_t internal_value = 0;

static ssize_t _riot_board_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len)
{
    return coap_reply_simple(pkt, COAP_CODE_205, buf, len,
            COAP_FORMAT_TEXT, (uint8_t*)RIOT_BOARD, strlen(RIOT_BOARD));
}

// own handler
static ssize_t _riot_foo_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len)
{
    printf("\nOWN HANDLER\n");
    int ret = 0;

    // detect observe option
    if(coap_has_observe(pkt))
        printf("coap has observe option\n\n");
    else
        printf("No observe option\n\n");
    
    // print coap option array
    printf("payload length: %i\n", pkt->payload_len);
    printf("payload: %s\n", pkt->payload);

    // handling resources and observe ===
    // create a resource
    coap_resource_t* resource = NULL;
    resource->path = "coap://localhost:5683/riot/foo";
    resource->handler = NULL;

    // detect observe option with gcoap bib
    // step 1: check if resource is already been observed
    ret = gcoap_obs_init(pkt, buf, 5 /*random*/, resource);
    if(ret == GCOAP_OBS_INIT_ERR)
        printf("ERR: gcoap observe init did not work");
    printf("observe init response: %i\n", ret);

    // step 2: create own payload and set it as payload in the package pointer
    uint8_t* tmpPayload = (uint8_t*)"asdf";
    pkt->payload = tmpPayload;
    printf("new payload: %s\n", pkt->payload);

    // step 3: update the packet for the payload
    ret = gcoap_finish(pkt, 4 /*cause tmpPayloads size is 3, don't know how strlen works*/, COAP_FORMAT_NONE);
    if(ret < 0)
        printf("ERR: gcoap_finish did not work!\n");

    // step 4 (final): send observe message
    // FIX: does not work so far
    ret = gcoap_obs_send(buf, len, resource);
    if(ret == 0)
        printf("ERR: cannot send!\n");

    // the normal simple reply at the end
    printf("return\n");
    return coap_reply_simple(pkt, COAP_CODE_205, buf, len,
            COAP_FORMAT_TEXT, (uint8_t*)"simple reply", strlen("simple reply"));
}

static ssize_t _riot_value_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len)
{
    ssize_t p = 0;
    char rsp[16];
    unsigned code = COAP_CODE_EMPTY;

    /* read coap method type in packet */
    unsigned method_flag = coap_method2flag(coap_get_code_detail(pkt));

    switch(method_flag) {
    case COAP_GET:
        /* write the response buffer with the internal value */
        p += fmt_u32_dec(rsp, internal_value);
        code = COAP_CODE_205;
        break;
    case COAP_PUT:
    case COAP_POST:
    {
        /* convert the payload to an integer and update the internal value */
        char payload[16] = { 0 };
        memcpy(payload, (char*)pkt->payload, pkt->payload_len);
        internal_value = strtol(payload, NULL, 10);
        code = COAP_CODE_CHANGED;
    }
    }

    return coap_reply_simple(pkt, code, buf, len,
            COAP_FORMAT_TEXT, (uint8_t*)rsp, p);
}

/* must be sorted by path (alphabetically) */
const coap_resource_t coap_resources[] = {
    COAP_WELL_KNOWN_CORE_DEFAULT_HANDLER,
    { "/riot/board", COAP_GET, _riot_board_handler },
    { "/riot/foo", COAP_GET, _riot_foo_handler },
    { "/riot/value", COAP_GET | COAP_PUT | COAP_POST, _riot_value_handler },
};

const unsigned coap_resources_numof = sizeof(coap_resources) / sizeof(coap_resources[0]);
