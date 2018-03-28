/*
 * Copyright (C) 2017 HTW Dresden
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
 * @brief       Example to set gpio Pins
 *
 * @author      Simon Retsch   <sxxxxx@informatik.htw-dresden.de>
 * @author      Tobias Ehrlich <s72851@informatik.htw-dresden.de>
 * 
 * last update: 03/12/2017
 *
 * @}
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>

#include <netdb.h>

#include <termios.h>

 #define SUCCESS 0
 #define FAILURE -1
 #define DEBUG 0

int serverHandler() {
    char inbuf[9000];
    sprintf(inbuf,"sgipo -s PB 2\n");
    ssize_t res = sizeof(inbuf);

#if (DEBUG)
    fprintf(stderr,"I AM THE COMMANDO!\n");
    fprintf(stderr,"K = %s",inbuf);
#endif
    /*
     * - write the header and lock the access to the module (write only)
     * - writes the message
     * - open the accesspoint again (read only)
     */  
    char delim = LINE_FRAME_DELIMITER;
    char head[] = {LINE_FRAME_DELIMITER, LINE_ESC_CHAR, (LINE_FRAME_TYPE_TEXT ^ 0x20)};
    checked_write(serial_fd, head, sizeof(head));
    _write_escaped(serial_fd, inbuf, res);
    checked_write(serial_fd, &delim, 1);

#if (DEBUG)
    fprintf(stderr,"\nAnd? Was it a hit?\n");
#endif

    return SUCCESS;
}