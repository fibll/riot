/**
 * RIoT Project Seminar Add-On
 * pwDB – Password Database
 * 
 * @date 2017/11/18
 */
// --- user includes --------------------------------------
#include "errorPS.h"

#ifndef __PWDB_H__
#define __PWDB_H__

#define MIN_PASSWORD_LEN 8
#define MAX_PASSWORD_LEN 20

errorPS_t check_pw(const char *string, const char *dbName);

#endif
/* EOF */