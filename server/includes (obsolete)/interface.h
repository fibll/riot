/**
 * RIoT Project Seminar Add-On
 * Interface
 * 
 * Tis file contains only the prototype for the locker main function.
 * RIoT don't need to know whats happend behind the curtain.
 * 
 * @date 2017/11/18
 */
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

void locker_main(unsigned char *string, void (*fp)(char *out));

#endif
/* EOF */