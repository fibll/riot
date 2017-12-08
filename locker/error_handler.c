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
 * @author      Simon <sxxx@informatik.htw-dresden.de>
 * @author      Tobias Ehrlich <s72851@informatik.htw-dresden.de>
 *
 * @}
 */
#include <stdio.h>
#include "error_handler.h"

void printERRmsg(error_t e)
{
  switch (e)
  {
  case INVALID_PARM_COUNT:
    fprintf(stderr, "usage: sgipo <function> <Port & Pin>\r\n");
    fprintf(stderr, "Port eg PA or PB\r\n");
    fprintf(stderr, "Pin should be a integer\r\n");
    break;

  default:
    fprintf(stderr, "general error\r\n");
    break;
  }
}
