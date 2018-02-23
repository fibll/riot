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
// #include "/home/bar/projekte/htw/RIOT/sys/net/application_layer/gcoap/gcoap.c"

// prototypes
static ssize_t _riot_board_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len);
static ssize_t _riot_foo_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len);
static ssize_t _riot_resource_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len);
static ssize_t _riot_value_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len);

// from monica
static ssize_t _riot_info_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len);
int coap_init(void);
// end


/* internal value that can be read/written via CoAP */
static uint8_t internal_value = 0;

// observe resource
//const coap_resource_t observe_resource = { "/riot/resource", COAP_GET, _riot_resource_handler };



/* must be sorted by path (alphabetically) */
const coap_resource_t coap_resources[] = {
    COAP_WELL_KNOWN_CORE_DEFAULT_HANDLER,
    { "/riot/board",    COAP_GET, _riot_board_handler },
    { "/riot/info",     COAP_GET, _riot_info_handler },
    { "/riot/foo",      COAP_GET, _riot_foo_handler },
    { "/riot/resource", COAP_GET, _riot_resource_handler },    
    { "/riot/value",    COAP_GET, _riot_value_handler },
};

const unsigned coap_resources_numof = sizeof(coap_resources) / sizeof(coap_resources[0]);

// from monica
static gcoap_listener_t _listener = {
    (coap_resource_t *)&coap_resources[0],
    sizeof(coap_resources) / sizeof(coap_resources[0]),
    NULL
};





// functions

static ssize_t _riot_info_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len)
{
    printf("\n--- Enter info handler --- \n");

    int ret = 0;

    // LOG_DEBUG("[CoAP] info_handler\n");
    printf("gcoap_resp_init: %i\n", gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT));




    // detect observe option with gcoap bib
    // step 1: check if resource is already been observed
    // ------

    /*
    // init with given arguments, cause these are the values of the resource
    ret = gcoap_obs_init(pkt, buf, len, &coap_resources[3]);
    if(ret == GCOAP_OBS_INIT_ERR)
        printf("ERR: gcoap observe init did not work\n");
    else if(ret == GCOAP_OBS_INIT_UNUSED){
        printf("No observer for this resource\n");
        return coap_reply_simple(pkt, COAP_CODE_205, buf, len,
            COAP_FORMAT_TEXT, (uint8_t*)"uncomplete reply", strlen("uncomplete reply"));
        }
    else
        printf("observe init response: %i\n", ret);
    */





    // set answer
    char infoStr[] = "--- INFO HANDLER ---";
    pkt->payload = (uint8_t *)infoStr;
    size_t payload_len = strlen("--- INFO HANDLER ---");

    return gcoap_finish(pkt, payload_len, COAP_FORMAT_JSON);
}







// ==================================================================================
// ==================================================================================
// ==================================================================================
// ==================================================================================



static ssize_t _riot_board_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len)
{
    printf("\n--- Enter riot board handler --- \n");

    return coap_reply_simple(pkt, COAP_CODE_205, buf, len,
            COAP_FORMAT_TEXT, (uint8_t*)RIOT_BOARD, strlen(RIOT_BOARD));
}

// own handler
static ssize_t _riot_foo_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len)
{
    printf("\n--- Enter riot foo handler --- \n");

    printf("Number of resources: %i", coap_resources_numof);

    printf("\n=== OWN HANDLER ===========================================\n");

    // detect observe option ===
    if(coap_has_observe(pkt))
        printf("coap has observe option\n\n");
    else
        printf("No observe option\n\n");
    
    // print coap option array ===
    if(pkt->payload_len <= 0)
        printf("No payload\n\n");
    else {
        printf("payload length: %i\n", pkt->payload_len);
        printf("payload: %s\n", pkt->payload);
    }

    // handling resources and observe ===
    // create a resource
    //coap_resource_t* resource = NULL;
    /*
    coap_handler_t* resourceHandler();
    coap_pkt_t* resourcePkt;
    resourceHandler->pkt = resourcePkt;
    */

    /*
    resource->path = "coap://localhost:5683/riot/ressource";
    resource->handler = NULL;
    resource->methods = COAP_GET;


    // detect observe option with gcoap bib

    // step 1: check if resource is already been observed
    // ------
    // riot-os.org:
    // Call gcoap_obs_init() to initialize the notification for a resource. Test the return value, which may indicate there is not an observer for the resource. If so, you are done.
    ret = gcoap_obs_init(pkt, buf, 5, resource);
    // 5 -> random
    if(ret == GCOAP_OBS_INIT_ERR)
        printf("ERR: gcoap observe init did not work\n");
    else if(ret == GCOAP_OBS_INIT_UNUSED)
        printf("No observer for this resource\n");
    else
        printf("observe init response: %i\n", ret);

    // step 2: create own payload and set it as payload in the package pointer
    // ------
    // riot-os.org: 
    // Write the notification payload, starting at the updated payload pointer in the coap_pkt_t.
    uint8_t* tmpPayload = (uint8_t*)"observe";
    pkt->payload = tmpPayload;
    printf("new payload: %s\n", pkt->payload);

    // step 3: update the packet for the payload
    // ------
    // riot-os.org: 
    // Call gcoap_finish(), which updates the packet for the payload.
    ret = gcoap_finish(pkt, 4 , COAP_FORMAT_NONE);
    // 4 -> cause tmpPayloads size is 3, don't know how strlen works
    if(ret < 0)
        printf("ERR: gcoap_finish did not work!\n");

    // step 4 (final): send observe message
    // ------
    // riot-os.org: Finally, call gcoap_obs_send() for the resource.
    // FIX: does not work so far
    ret = gcoap_obs_send(buf, len, resource);
    if(ret == 0)
        printf("ERR: cannot send!\n");

    */





    // the normal simple reply at the end
    printf("return\n");
    return coap_reply_simple(pkt, COAP_CODE_205, buf, len,
            COAP_FORMAT_TEXT, (uint8_t*)"simple reply", strlen("simple reply"));
}

// observe resource handler
static ssize_t _riot_resource_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len){
 
    printf("\n--- Enter riot resource handler --- \n");

    int ret = 0;


    printf("\n=== observeable resource handler ===========================================\n");

    // detect observe option ===
    if(coap_has_observe(pkt))
        printf("coap has observe option\n\n");
    else
        printf("No observe option\n\n");

    printf("chosen coap_resource url: %s", coap_resources[3].path);


    // detect observe option with gcoap bib
    // step 1: check if resource is already been observed
    // ------

    // init with given arguments, cause these are the values of the resource
    ret = gcoap_obs_init(pkt, buf, len, &coap_resources[3] /*Adress of observe resource*/);
    if(ret == GCOAP_OBS_INIT_ERR)
        printf("ERR: gcoap observe init did not work\n");
    else if(ret == GCOAP_OBS_INIT_UNUSED){
        printf("No observer for this resource\n");
        return coap_reply_simple(pkt, COAP_CODE_205, buf, len,
            COAP_FORMAT_TEXT, (uint8_t*)"uncomplete reply", strlen("uncomplete reply"));
        }
    else
        printf("observe init response: %i\n", ret);

    // step 2: create own payload and set it as payload in the package pointer
    // ------
    uint8_t* tmpPayload = (uint8_t*)"observe";
    pkt->payload = tmpPayload;
    printf("new payload: %s\n", pkt->payload);

    // step 3: update the packet for the payload
    // ------
    ret = gcoap_finish(pkt, 4 /*cause tmpPayloads size is 3, don't know how strlen works*/, COAP_FORMAT_NONE);
    if(ret < 0)
        printf("ERR: gcoap_finish did not work!\n");

    // step 4 (final): send observe message
    // ------
    // FIX: does not work so far
    ret = gcoap_obs_send(buf, len, &coap_resources[3] /*Adress of observe resource*/);
    if(ret == 0)
        printf("ERR: cannot send!\n");
 
 
    return coap_reply_simple(pkt, COAP_CODE_205, buf, len,
        COAP_FORMAT_TEXT, (uint8_t*)"resource reply", strlen("resource reply"));
}

static ssize_t _riot_value_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len)
{
    printf("\n--- Enter riot value handler --- \n");

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


/**
 * @brief start CoAP thread
 *
 * @return PID of CoAP thread
 */
int coap_init(void)
{
    gcoap_register_listener(&_listener);
    return 0;
}