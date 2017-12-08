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
#include <ctype.h>
#include <stdlib.h>
#include "gpio.h"
#include "locker.h"
#include "error_handler.h"

#define LOW 0

static void sgpioHelp(void)
{
  printf("sgipo <function> <Port & Pin>\r\n");
  printf("Functions are:\r\n");
  printf("\t-i ... initialisation of port and pin\rn");
  printf("\t-h ... help\r\n");
  printf("\t-s ... set pin high or low, depending on curent status\r\n");
  printf("\t-o ... set pin high\r\n");
  printf("\t-l ... set pin low\r\n");
  printf("This program suports only one function per command.\r\n");
  printf("\r\n");
  printf("port and pin -> two chars and one integer eg. PA04\r\n");
}

/*
 *
 */
static int SetGPIO(int argc, char **argv)
{
  if (2 > argc || 3 < argc)
  {
    printERRmsg(INVALID_PARM_COUNT);
    return INVALID_PARM_COUNT;
  }

  int cmdPos = 1, address = 0, number = 0;
  gpio_t pin;

  /* possible cmd order: -h PB2 or PA02 -i */
  for (int i = 1; argc > i; i++)
  {
    char c = argv[i][0];
    if ('-' == c)
    {
      cmdPos = i;
    }
    else
    {
      /* parse port */
      if ('P' != c)
      {
        printERRmsg(INVALID_COMMAND);
        return INVALID_COMMAND;
      }

      c = argv[i][1];
      if (isdigit(c))
      {
        address = atoi(&c);
      }
      else
      {
        switch (c)
        {
        case 'A':
          address = 0;
          break;

        case 'B':
          address = 1;
          break;

        case 'C':
          address = 2;
          break;

        default:
          printERRmsg(INVALID_COMMAND);
          return INVALID_COMMAND;
        } // end switch

      } // end inner if

      /* pars pin */
      number = atoi(&argv[i][2]);

    } // end outer if

  } // end for

  pin = GPIO_PIN(address, number);
  switch ((unsigned int)argv[cmdPos][1])
  {
  case 'h':
    sgpioHelp();
    break;

  case 'i':
    if (-1 == gpio_init(pin, GPIO_OUT))
      printERRmsg(INIT_FAILURE);
    break;

  case 'o':
    gpio_set(pin);
    break;

  case 'l':
    gpio_clear(pin);
    break;

  case 's':
    if (LOW == gpio_read(pin))
      gpio_set(pin);
    else
      gpio_clear(pin);
    break;

  default:
    printERRmsg(INVALID_COMMAND);
    break;
  }

  return 0;
}

const shell_command_t shellCommandTable[] = {
    // cmd    description  function
    {"sgpio", "set pins", SetGPIO},
    {NULL, NULL, NULL} // Empty command to terminate the list
};

shell_command_t *getShellCommandTable(void)
{
  return (shell_command_t *)shellCommandTable;
}