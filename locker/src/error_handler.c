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
 * last update: 12/10/2017
 *
 * @}
 */
#include <stdio.h>
#include "error_handler.h"

void printERRmsg(error_t e)
{
  fprintf(stderr, "ERROR!\r\n");

  switch (e)
  {
  case INVALID_COMMAND:
  case INVALID_PARM_COUNT:
    fprintf(stderr, "Usage: sgipo <function> <port with leading P> <pin>\r\n");
    fprintf(stderr, "Port eq. to PA, PB, ...\r\n");
    fprintf(stderr, "pin should be an integer\r\n");
    fprintf(stderr, "For more information enter 'sgpio -h'\r\n\r\n");
    break;

  case INIT_FAILURE:
    fprintf(stderr, "Init failure\r\n\r\n");
    break;

  default:
    fprintf(stderr, "General error!\r\n");
    break;
  }
}
