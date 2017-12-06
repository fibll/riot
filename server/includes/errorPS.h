/**
 * RIoT Project Seminar Add-On
 * Error types and messages 
 * 
 * @date 2017/11/18
 */
#ifndef __ERROR_H__
#define __ERROR_H__

typedef enum ERROR {
  GENERAL_FAILURE = -10,
  EMPTY_STRING,
  WRONG_PASWD_LEN,
  NO_DB_ACCESS,
  INVALID_HASH,
  INVALID_PWD,
  FAIL = 0,
  OK
} errorPS_t;

void printERRmsg(errorPS_t e);
#endif
/* EOF */