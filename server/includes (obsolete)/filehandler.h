/**
 * RIoT Project Seminar Add-On
 * File Handler 
 * 
 * @date 2017/11/18
 */
#include <stddef.h>
#include "errorPS.h"

#ifndef __FILEHANDLER_H__
#define __FILEHANDLER_H__

errorPS_t checkForDatabase(const char *filename);
errorPS_t readFromFile(const char *filename, void *buf, size_t size, int counter);
errorPS_t closeFile(void);

#endif
/* EOF */