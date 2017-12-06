# Locker Add-On for RIoT-OS

## 1. General Information

This addon is for [RIoT-OS][1] _**TODO MODULE NAME**_

### 1.1 Directories and Files

* README.md
* includes/
  * interface.h
* src/
  * locker_main.c

### 1.2 Installation

1. Copy the folder `locker` in _**TODO MODULE PATH**_
1. add `#include "interface.h"` _**TODO MODULE FILE**_
1. add function _**TODO**_

## 2. File Descriptions

### 2.1 interface.h

## Links

1. [RIoT-OS in world wide web](https://riot-os.org/ "RIoT Homepage")
1. [RIoT-OS GitHub Download Section](https://github.com/RIOT-OS "RIoT Download")
1. [RIoT-OS GitHub Wiki](https://github.com/RIOT-OS/RIOT/wiki "RIoT official wiki")
1. [RIoT-OS HTW Dresden Wiki (ger)](https://www2.htw-dresden.de/~wiki_sn/index.php/RIOT "RIoT HTW Dresden Wiki (ger)")

[1]: https://riot-os.org/ "RIoT Homepage"

### temp ideas

```c
#include "/home/tobi/RIOT/drivers/include/periph/gpio.h"
gpio_t PApin = GPIO_PIN(PB,2); // GPIO_PIN(Port Abkürzung, Pin)
gpio_init(PApin, GPIO_OUT);
gpio_set(PApin); // high
gpio_clear(PApin); // low
```

die Funktion shell_run blockiert aktiv
1x in shell_run
1x in read_line

<https://github.com/RIOT-OS/RIOT/wiki/Board:-Samr21-xpro>
<http://riot-os.org/api/group__drivers__periph__gpio.html>

neue Kommandos müssen in sys/shell/commands integriert werden
<https://github.com/RIOT-OS/RIOT/wiki/Creating-your-first-RIOT-project>