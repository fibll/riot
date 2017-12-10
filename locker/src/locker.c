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
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "gpio.h"
#include "locker.h"
#include "error_handler.h"

#define LOW 0

/*
 * sgpio help function
 */
static void sgpioHelp(void)
{
  puts("sgipo <function> <port with leading P> <pin>");
  puts("");
  puts("CAUTION!");
  puts("\tRead the board documentation at first!");
  puts("\tIncorrect handling may cause permanent damage to your microcontroller!");
  puts("");
  puts("Functions are:");
  puts("\t-i ... initialisation of port and pin");
  puts("\t-h ... help");
  puts("\t-s ... set pin high or low, depending on current status");
  puts("\t-o ... set pin high");
  puts("\t-l ... set pin low");
  puts("\tThis program supports only one function per command.");
  puts("");
  puts("port with leading 'P' and");
  puts("\t... one char eq. to PA, PB, ... or pa, pb, ...");
  puts("\t... or one integer eq. to P1, P2, ... or p1, p2, ...");
  puts("");
  puts("pin as integer value");
  puts("");
}

/*
 * parse port function
 * @param[in] char pointer to argument
 */
static int parsePort(char *argv)
{
  /* if first letter not a 'P' or 'p' */
  if (2 > strlen(argv) || ('p' != argv[0] && 'P' != argv[0]))
  {
    return INVALID_COMMAND;
  }

  int x = 0;
  for (int i = 1; isalnum(argv[i]) && x < INT_MAX; i++)
  {
    if (isdigit(argv[i])) /* if port is eq. to P1, P2, ... */
      x = x * 10 + (argv[i] - '0');

    if (islower(argv[i])) /* if port is eq. to Pa, Pb, ... */
      x = x * 10 + (argv[i] - 'a');

    if (isupper(argv[i])) /* if port is eq. to PA, PB, ... */
      x = x * 10 + (argv[i] - 'A');
  }
  return x;
}

/*
 * parse pin function
 * @param[in] char pointer to argument
 */
int parsePin(char *argv)
{
  int x = 0;
  while (isdigit(argv[0]) && x < INT_MAX)
  {
    x = x * 10 + (argv[0] - '0');
    argv++;
  }
  return x;
}

/*
 * SetGPIO command function
 * - checks number of arguments
 * - pars arguments
 * - runs command
 * 
 * @param[in] int argc, number of arguments (min 1)
 * @param[in] char double pointer argv, arguments (argv[0] = shell command)
 */
static int SetGPIO(int argc, char **argv)
{
  if (2 > argc || 4 < argc)
  {
    printERRmsg(INVALID_PARM_COUNT);
    return INVALID_PARM_COUNT;
  }

  int address = INVALID_COMMAND,
      number = INVALID_COMMAND;
  char function = 0x0;

  /* parsing arguments
     possible cmd order: <function> <pin> or <pin> <function> */
  for (int i = 1; argc > i; i++)
  {
    if ('-' == (unsigned int)argv[i][0]) /* parse function */
    {
      function = argv[i][1];
    }
    else if (isalpha(argv[i][0])) /* parse port */
    {
      address = parsePort(argv[i]);
    }
    else /* pars pin */
    {
      number = parsePin(argv[i]);
    }
  }

  /* if function help is called, print lines and return */
  if ('h' == function)
  {
    sgpioHelp();
    return 0;
  }

  /* otherwise check whether both address parts are set */
  if (INVALID_COMMAND == address || INVALID_COMMAND == number)
  {
    printERRmsg(INVALID_COMMAND);
    return INVALID_COMMAND;
  }

  gpio_t pin = GPIO_PIN(address, number);
  switch (function)
  {
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

/*
 * module shell command table
 */
const shell_command_t shellCommandTable[] = {
    // cmd    description  function
    {"sgpio", "set pins", SetGPIO},
    {NULL, NULL, NULL} // Empty command to terminate the list
};

/*
 * @param[out] pointer to module shell command table
 */
shell_command_t *getShellCommandTable(void)
{
  return (shell_command_t *)shellCommandTable;
}