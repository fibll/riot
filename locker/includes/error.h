/**
 * RIoT Project Seminar Add-On
 * Error types and messages * 
 * 
 * @date 2017/11/18
 */
#pragma once

typedef enum ERROR {
  GENERAL_FAILURE = -5,
  EMPTY_STRING,
  INVALID_PWD
} error_t;

void printERRmsg(error_t e);