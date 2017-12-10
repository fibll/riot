# Server Add-On for RIoT-OS

## 1. General Information

This addon is for [RIoT-OS][1] _**TODO MODULE NAME**_

### 1.1 Directories and Files

* README.md
* includes/
  * interface.h
* src/
  * keyboard_main.c

### 1.2 Installation

1. Copy the folder `keyboard` in _**TODO MODULE PATH**_
1. add `#include "interface.h"` into _**TODO MODULE FILE**_
1. add function _**TODO**_

## 2. File Descriptions

### 2.1 interface.h

## 3. Creation Process

### idea

```c
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
 * @brief       Server interface
 *
 * @author      Simon Retsch   <sxxxxx@informatik.htw-dresden.de>
 * @author      Tobias Ehrlich <s72851@informatik.htw-dresden.de>
 *
 * @}
 */
// --- sys includes ---------------------------------------
#include <inttypes.h>
#include <string.h>

// --- user includes --------------------------------------
#include "../includes/errorPS.h"
#include "../includes/pwDB.h"
#include "../includes/filehandler.h"

// --- defines --------------------------------------------
#define DATABASENAME "locker"

// --- functios -------------------------------------------
/**
 * Server main function handles incoming strings, checks if they match to a
 * password and send an open instruction to a locker.
 * 
 * @param[in] unsigned char pointer to received string
 * @param[in] void function pointer to serial communication function 
 *       // TODO Alternative in der interface.h ein define setzten
 * 
 * last update: 12/10/2017
 */
void server_main(char *string, void (*fp)(char *out))
{
  if (NULL == string)
  {
    printERRmsg(EMPTY_STRING);
    return;
  }
  char buf[MAX_PASSWORD_LEN];
  errorPS_t ret;
  size_t stringLen = strlen(string);

  // 1. check string length
  if (MAX_PASSWORD_LEN < stringLen + 1 || MIN_PASSWORD_LEN > stringLen)
  {
    printERRmsg(WRONG_PASWD_LEN);
    return;
  }

  // 2. check wether a database is available
  ret = checkForDatabase(DATABASENAME);
  if (OK != ret)
  {
    /* a failure can occur: 
     * - if the program has no write permission 
     * - if DB not available
     */
    printERRmsg(ret);
    return;
  }

  // 3. copy string in local buffer
  strncpy(buf, string, stringLen);
  buf[stringLen + 1] = 0x0;

  // 4. check password
  ret = check_pw(buf, DATABASENAME);

  // 5. send (un)lock or error command
  if (OK != ret)
  {
    printERRmsg(ret);
    // TODO send ERROR msg to Keyboard
    return;
  }
  else
  {
    // TODO send (un)lock cmd
    // +++\n
    // atp1 1
    // & OK msg to Keyboard
  }

  // 6. clean buffer
  memset(buf, 0x0, MAX_PASSWORD_LEN);
}
/* EOF */
```

* copy Makefile from ethos
* add INCLUDES and BIN to Makefile
* catch received data and handle it in our function

## Links

1. [RIoT-OS in world wide web](https://riot-os.org/ "RIoT Homepage")
1. [RIoT-OS GitHub Download Section](https://github.com/RIOT-OS "RIoT Download")
1. [RIoT-OS GitHub Wiki](https://github.com/RIOT-OS/RIOT/wiki "RIoT official wiki")
1. [RIoT-OS HTW Dresden Wiki (ger)](https://www2.htw-dresden.de/~wiki_sn/index.php/RIOT "RIoT HTW Dresden Wiki (ger)")

[1]: https://riot-os.org/ "RIoT Homepage"