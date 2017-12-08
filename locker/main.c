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
 * @file        main interface of locker addon
 * @brief       Example to set gpio Pins
 *
 * @author      Simon <sxxx@informatik.htw-dresden.de>
 * @author      Tobias Ehrlich <s72851@informatik.htw-dresden.de>
 *
 * @}
 */
#include <stdio.h>
#include "msg.h"
#include "locker.h"

#define MAIN_QUEUE_SIZE (8)

static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

int main(void)
{
  /* we need a message queue for the thread running the shell in order to
   * receive potentially fast incoming networking packets */
  msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
  puts("RIOT border router example application with locker extention");

  /* start shell */
  puts("All up, running the shell now");
  char line_buf[SHELL_DEFAULT_BUFSIZE];
  shell_run(getShellCommandTable(), line_buf, SHELL_DEFAULT_BUFSIZE);

  /* should be never reached */
  return 0;
}