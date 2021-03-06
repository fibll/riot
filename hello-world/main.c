/*
 * Copyright (C) 2014 Freie Universität Berlin
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
 * @brief       Hello World application
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <unistd.h>
//#include "vectors_kinetis.h"

void Isr_sw0(void);

int main(void)
{
    //int pressed = 0;

    printf("\n\n\n\n");
    puts("Hello out there!");

    printf("Board: %s\n", RIOT_BOARD);
    printf("Featured MCU: %s\n", RIOT_MCU);

    while(1)
    {
        ;
    }

    // should never be reached
    return 0;
}

void Isr_sw0(void)
{
    printf("SW0 pressed\n");
}
