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

#include "log.h"
#include "fmt.h"
#include "nanocoap.h"

#include "net/gcoap.h"
// #include "/home/bar/projekte/htw/RIOT/sys/net/application_layer/gcoap/gcoap.c"

// prototypes
void debugPrintf(char* text);

static ssize_t _riot_board_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len);
static ssize_t _riot_foo_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len);
static ssize_t _riot_value_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len);

// from monica
static ssize_t _riot_gcoap_info_handler(coap_pkt_t* pkt, uint8_t *buf, size_t len);
static ssize_t _riot_gcoap_init_handler(coap_pkt_t* pkt, uint8_t *buf, size_t len);
static ssize_t _riot_gcoap_obs_handler(coap_pkt_t* pkt, uint8_t *buf, size_t len);
int coap_init(void);
// end


/* internal value that can be read/written via CoAP */
static uint8_t internal_value = 0;

int debug = 0;


/* must be sorted by path (alphabetically) */
const coap_resource_t coap_resources[] = {
    COAP_WELL_KNOWN_CORE_DEFAULT_HANDLER,
    { "/riot/board",        COAP_GET, _riot_board_handler },
    { "/riot/gcoap/info",   COAP_GET, _riot_gcoap_info_handler },
    { "/riot/gcoap/init",   COAP_GET, _riot_gcoap_init_handler },
    { "/riot/gcoap/obs",    COAP_GET, _riot_gcoap_obs_handler },
    { "/riot/foo",          COAP_GET, _riot_foo_handler },
    { "/riot/value",        COAP_GET, _riot_value_handler },
};

const unsigned coap_resources_numof = sizeof(coap_resources) / sizeof(coap_resources[0]);

// from monica
static gcoap_listener_t _listener = {
    (coap_resource_t *)&coap_resources[0],
    sizeof(coap_resources) / sizeof(coap_resources[0]),
    NULL
};





// functions

static ssize_t _riot_gcoap_info_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len)
{
    printf("\n--- Enter info handler --- \n");

    int ret = 0;

    // initalize gcoap response
    ret = gcoap_resp_init(pkt, buf, len, COAP_CODE_CONTENT);
    printf("[CoAP] Info: %i\n", ret);

    // set answer
    char infoStr[] = "--- GCOAP INFO HANDLER ---";
    pkt->payload = (uint8_t *)infoStr;
    size_t payload_len = strlen("--- GCOAP INFO HANDLER ---");

    return gcoap_finish(pkt, payload_len, COAP_FORMAT_JSON);
}

static ssize_t _riot_gcoap_init_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len)
{
    printf("\n--- Enter init handler --- \n");

    int ret = 0;
    int resourceNumber = 3;



    // detect observe option with gcoap bib
    // step 1: check if resource is already been observed
    // ------
    // init with given arguments, cause these are the values of the resource
    ret = gcoap_obs_init(pkt, buf, len, &coap_resources[resourceNumber]);

    if(ret == GCOAP_OBS_INIT_ERR)
        printf("ERR: gcoap observe init did not work\n");
    else if(ret == GCOAP_OBS_INIT_UNUSED)
        printf("No observer for this resource\n");
    else {
        printf("Resource [%s]:\n", coap_resources[resourceNumber].path);

        // step 2: create own payload and set it as payload in the package pointer
        // ------
        uint8_t* tmpPayload = (uint8_t*)"observe";
        buf = tmpPayload;
        len = strlen("observe");
        printf("new payload: %s\n", pkt->payload);

        // step 3: update the packet for the payload
        // ------
        ret = gcoap_finish(pkt, 8, COAP_FORMAT_NONE); // 8 cause tmpPayloads size is 7, don't know how strlen works
        if(ret < 0)
            printf("ERR: gcoap_finish did not work!\n");

        // step 4 (final): send observe message
        // ------
        // FIX: does not work so far
        ret = gcoap_obs_send(buf, len, &coap_resources[resourceNumber]); //Adress of observe resource
        if(ret == 0)
            printf("ERR: cannot send!\n");
        else 
            return 0;
    }
    // end
    

    // initalize gcoap response
    ret = gcoap_resp_init(pkt, buf, len, COAP_CODE_CONTENT);

    // set answer
    char infoStr[] = "\n--- GCOAP INIT HANDLER ---";
    pkt->payload = (uint8_t *)infoStr;
    size_t payload_len = strlen("\n--- GCOAP INIT HANDLER ---");

    return gcoap_finish(pkt, payload_len, COAP_FORMAT_JSON);
}


static ssize_t _riot_gcoap_obs_handler(coap_pkt_t *pkt, uint8_t *buf, size_t len)
{
    printf("\n--- Enter OBS handler --- \n");

    // variables
    int ret = 0;
    int resourceNumber = 4;

    // allocate buffer
    debugPrintf("\ntest0");
    uint8_t* tmpBuffer = malloc(sizeof(coap_pkt_t));
    size_t tmpBufferSize = sizeof(coap_pkt_t);

    // create obs notification
    coap_pkt_t obsNotification;


    // ------
    // step 1: check if resource is already been observed
    debugPrintf("\ntest1");
    ret = gcoap_obs_init(&obsNotification, tmpBuffer, tmpBufferSize, &coap_resources[resourceNumber]);

    if(ret == GCOAP_OBS_INIT_ERR){
        printf("STOP: ERR: gcoap observe init did not work\n");
        return 0;
    }
    else if(ret == GCOAP_OBS_INIT_UNUSED){
        printf("STOP: No observer for this resource\n");

        // initalize gcoap response
        ret = gcoap_resp_init(pkt, buf, len, COAP_CODE_CONTENT);
        char infoStr[] = "--- no observer ---";
        pkt->payload = (uint8_t *)infoStr;
        size_t payload_len = strlen("--- no observer ---");
        
        free(tmpBuffer);

        return gcoap_finish(pkt, payload_len, COAP_FORMAT_JSON);
    }

    // ------
    // step 2: create own payload and set it as payload in the package pointer
    debugPrintf("\ntest2");
    obsNotification.payload = (uint8_t*)"OBS";
    obsNotification.payload_len = sizeof("OBS");

    // ------
    // step 3: update the packet for the payload
    debugPrintf("\ntest3");
    ret = gcoap_finish(&obsNotification, obsNotification.payload_len, COAP_FORMAT_NONE); // 8 cause tmpPayloads size is 7, don't know how strlen works
    if(ret < 0)
        printf("ERR: gcoap_finish did not work!\n");

    // ------
    // step 4 (final): send observe message
    debugPrintf("\ntest4");
    ret = gcoap_obs_send(tmpBuffer, tmpBufferSize, &coap_resources[resourceNumber]); //Adress of observe resource
    if(ret == 0)
        printf("ERR: cannot send!\n");


    free(tmpBuffer);
    return 0;//gcoap_finish(pkt, payload_len, COAP_FORMAT_JSON);
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


    // the normal simple reply at the end
    printf("return\n");
    return coap_reply_simple(pkt, COAP_CODE_205, buf, len,
            COAP_FORMAT_TEXT, (uint8_t*)"simple reply", strlen("simple reply"));
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

void debugPrintf(char* text){
    if(debug == 1)
        printf("%s", text);

    return;
}