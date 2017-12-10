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
#ifndef __ERRORHANDLER_H__
#define __ERRORHANDLER_H__

typedef enum ERROR {
  GENERAL_FAILURE = -5,
  INVALID_PARM_COUNT,
  INVALID_COMMAND,
  INIT_FAILURE
} error_t;

void printERRmsg(error_t e);

#endif
// EOF