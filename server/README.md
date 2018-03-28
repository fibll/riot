# Server Add-On for RIoT-OS

Last update: 03/28/2018
## 1. General Information

This addon extent ethos application for [RIoT-OS][1]

### 1.2 Installation

1. Copy the folder `server` into the _RIOT/dist/tools_ directory.
1. Enter the directory and run _make all_.

### 1.3 Usage

This extended ethos script will be called automatically by locker-libcoap addon.
After initialization of the connection to the RIoT module, the permanently implemented GPIO pin is activated or deactivated. Finally ethos will shut down its connection.

To change any pin or update the pin library you have to update the `serverHandler()` function in the serverHandler.c file. Please note that all defined GPIO pins are currently activated or deactivated by calling the script.

## 2. File Descriptions

### 2.1 Directories and Files

* ethos.c
* LICENSE
* main.c
* Makefile
* README.md
* serverHandler.c
* start_network.sh
* includes/
  * serverHandler.h

### 2.1 Server Handler Header and Source File

```c
int serverHandler();
```

The server handler function prepares the string for the GPIO command which is send via ethos to the module.

### 2.3 Main File

* Line 669 was updated  with `return serverHandler();`
* everything below will be ignored after returning

## 3. Creation Process

### 3.1 Introduction

Originally, the server should receive an encrypted string from the module using the keyboard.
Since we only have two modules and cannot access the router directly with Coap, we have to send a command to the router via ethos script to open the lock.

In the following section you will find a scratch of the original server function.

### 3.2 Scratch of Original Server Funktion

```c
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

  // 2. check whether a database is available
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
```

### TODO

* add a possibility to activate several pins independent 

## Links

1. [RIoT-OS in world wide web](https://riot-os.org/ "RIoT Homepage")
1. [RIoT-OS GitHub Download Section](https://github.com/RIOT-OS "RIoT Download")
1. [RIoT-OS GitHub Wiki](https://github.com/RIOT-OS/RIOT/wiki "RIoT official wiki")
1. [RIoT-OS HTW Dresden Wiki (ger)](https://www2.htw-dresden.de/~wiki_sn/index.php/RIOT "RIoT HTW Dresden Wiki (ger)")

[1]: https://riot-os.org/ "RIoT Homepage"