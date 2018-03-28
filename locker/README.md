# Locker Add-On for RIOT-OS

Last update: 12/10/2017

## 1. General Information

This addon is for [RIOT-OS][1]

### 1.2 Installation

1. Copy the folder `locker` into the _RIOT/examples_ directory.
1. Enter the directory and run _make all_ and as superuser _make flash_.

### 1.3 Usage

**CAUTION!**

_Read the board documentation at first before you change any pin!
Incorrect handling may cause permanent damage to your micro controller!_

Command: 

* `sgipo <function> <port with leading P> <pin>`

Functions are:

* `-i` ... initialisation of port and pin
* `-h` ... help
* `-s` ... set pin high or low, depending on current status
* `-o` ... set pin high
* `-l` ... set pin low

This program supports only one function per command.

Port with leading '_P_ ' and

* ... one char eq. to PA, PB, ... or pa, pb, ...
* ... or one integer eq. to P1, P2, ... or p1, p2, ...

Pin as integer value

## 2. File Descriptions

### 2.1 Directories and Files

* README.md
* Makefile
* main.c
* src/
  * locker.c
  * error_handler.c
  * Makefile
* includes/
  * locker.h
  * error_handler.h

### 2.2 Makefile(s)

The Makefile in the root directory is basically the same as the Makefile in the directory _gnrc_border_router_. The lines _INCLUDES_ and _BIN_ were added to compile header and source files in the subdirectories.

```Makefile
INCLUDES += -I$(CURDIR)/includes -I$(RIOTBASE)/drivers/include/periph
```

```Makefile
BIN_DIRS += src
BIN_USEMODULE += src
BIN_USEMODULE += locker
```

The Makefile in the src folder contains only the root Makefile in RIOT root directory.

### 2.3 Main Source File

The _main.c_ file is the same like in _gnrc_border_router_. To add special shell commands, the function `getShellCommandTable()` was added to shell starter. This function returns a pointer to the shell command table [(see in section 2.4)](#24-locker-header-and-source-file).

```c
shell_run(getShellCommandTable(), line_buf, SHELL_DEFAULT_BUFSIZE);
```

### 2.4 Locker Header and Source File

```c
static void sgpioHelp(void)
```

```c
static int parsePort(char *argv)
```

```c
int parsePin(char *argv)
```

```c
static int SetGPIO(int argc, char **argv)
```

```c
const shell_command_t shellCommandTable[]
```

```c
shell_command_t *getShellCommandTable(void)
```

### 2.5 Error Handler Header and Source File

```c
typedef enum ERROR {
  GENERAL_FAILURE    = -5,
  INVALID_PARM_COUNT = -4,
  INVALID_COMMAND    = -3,
  INIT_FAILURE       = -2
} error_t;
```

```c
void printERRmsg(error_t e);
```

## 3. The Creation Process

### 3.1 Introduction

The locker module receive the encrypted key and send it to the server (connected computer). The server interpret the command and send the lock/unlock or the not valid command to the locker module.

RIOT's shell function _shell_run_ blocks the thread twice active, once in `shell_run` and once in `read_line`. This means that we need to implement our own locker locking or unlocking command.

To implement new commands, we use the description of the RIOT Tutorial[Creating your first RIOT project][2]. There are different ways to handle new commands, three are described in [section 3.2](#32-possible-implementations). We have opted for version 3, which is easy to implement and easy for the user to understand. But because of the different boards, we have to adjust the pin port part and split it into two arguments.

### 3.2 Possible implementations

* init pins and ports
* set pin high or low, depending on current status
* set pin only high
* set pin only low
* function combinations are not available
* Param Version 1:

      -i ... init (function)
      -h ... help (function)
      -s ... set  (function) high or low
      -o ... on   (function) high
      -l ... low  (function)
      -e ... port (ext) -> two chars -> how to check for valid board cmd?
      -p ... pin -> one integer value -> how to check for valid board cmd?

* Param Version 3:

      -i  ... init (function)
      -h  ... help (function)
      -s  ... set  (function) high or low
      -o  ... on   (function) high
      -l  ... low  (function)
      non ... port and pin -> two chars and one integer -> how to check for valid board cmd?

* Param Version4:
  * function starts a new loop and waits for specific commands

        (eg. PA0 on, PA1 of, .., PB0 xx, PB1 xx, ..)

  * advantage: there are more commands with one send command possible but not usual
* Param Version 4:
  * we create for every board specific commands in shell command table (very complex)

### TODO

* add missing GPIO functions
* add EEPROM writing and reading function
* add function to init pins which are connected with locker
* add missing descriptions in Source files and README.md

## Links

1. [RIOT-OS in world wide web](https://riot-os.org/ "RIOT Homepage")
1. [RIOT-OS GitHub Download Section](https://github.com/RIOT-OS "RIOT Download")
1. [RIOT-OS GitHub Wiki](https://github.com/RIOT-OS/RIOT/wiki "RIOT official wiki")
1. [RIOT-OS HTW Dresden Wiki (ger)](https://www2.htw-dresden.de/~wiki_sn/index.php/RIOT "RIOT HTW Dresden Wiki (ger)")
1. [RIOT-OS board description for SAM R21 Xplained Pro](https://github.com/RIOT-OS/RIOT/wiki/Board:-Samr21-xpro "RIOT  board description for SAM R21 Xplained Pro")
1. [RIOT-OS API GPIO access functions](http://riot-os.org/api/group__drivers__periph__gpio.html "RIOT API GPIO access functions")

[1]: https://riot-os.org/ "RIOT Homepage"
[2]: https://github.com/RIOT-OS/RIOT/wiki/Creating-your-first-RIOT-project "RIOT Tutorial for implementation of new shell commands"
