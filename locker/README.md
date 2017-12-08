# Locker Add-On for RIoT-OS

## 1. General Information

This addon is for [RIoT-OS][1] _**TODO MODULE NAME**_

### 1.1 Directories and Files

* README.md
* Makefile
* main.c
* locker.c
* error_handler.c
* includes/
  * locker.h
  * error_handler.h

### 1.2 Installation

1. Copy the folder `locker` in _**TODO MODULE PATH**_
1. add `#include "interface.h"` _**TODO MODULE FILE**_
1. add function _**TODO**_

## 2. File Descriptions

### 2.1 locker.h

### 2.2 locker.c

## 3. The Creation Process

### 3.1 Introduction

The locker module receive the encrypted key and send it to the server (connected computer). The server interpret the command and send the lock/unlock or the not valid command to the locker module.
To implement new commands we use the description of the RIoT Tutorial [Creating your first RIoT project][2]. There are many possibilities how to handle new commands [(rev 3.2)] (#3.2-possible-implementations). We will use version 3, it is simple to implement and easy to understand by the user.


### 3.2 Possible implementations

The Plan is:

* init pins and ports
* set pin high or low, depending on curent status
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

### temp ideas

```c
#include "/home/tobi/RIOT/drivers/include/periph/gpio.h"
gpio_t PApin = GPIO_PIN(PB,2); // GPIO_PIN(Port Abkürzung, Pin)
gpio_init(PApin, GPIO_OUT);
gpio_set(PApin); // high
gpio_clear(PApin); // low
```

* die Funktion shell_run blockiert aktiv
  * 1x in shell_run
  * 1x in read_line
* --> neue Kommandos müssen in sys/shell/commands integriert werden oder neue shell tabelle anlegen

## Links

1. [RIoT-OS in world wide web](https://riot-os.org/ "RIoT Homepage")
1. [RIoT-OS GitHub Download Section](https://github.com/RIOT-OS "RIoT Download")
1. [RIoT-OS GitHub Wiki](https://github.com/RIOT-OS/RIOT/wiki "RIoT official wiki")
1. [RIoT-OS HTW Dresden Wiki (ger)](https://www2.htw-dresden.de/~wiki_sn/index.php/RIOT "RIoT HTW Dresden Wiki (ger)")
1. [RIoT-OS board description for SAM R21 Xplained Pro](https://github.com/RIOT-OS/RIOT/wiki/Board:-Samr21-xpro "RIoT  board description for SAM R21 Xplained Pro")
1. [RIoT-OS API GPIO access functions](http://riot-os.org/api/group__drivers__periph__gpio.html "RIoT API GPIO access functions")

[1]: https://riot-os.org/ "RIoT Homepage"
[2]: https://github.com/RIOT-OS/RIOT/wiki/Creating-your-first-RIOT-project "RIoT Tutorial for implementation of new shell commands"

## Title

### Place 1

Hello, this is some text to fill in this, [here](#place-2), is a link to the second place.

### 3.5 Place 2

Place one has the fun times of linking here, but I can also link back [here](#place-1).
