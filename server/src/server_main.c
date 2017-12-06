/**
 * RIoT Project Seminar Add-On
 * server_main – main interface function
 * 
 * @date 2017/11/18
 */
// --- sys includes ---------------------------------------
#include <inttypes.h>
#include <string.h>

// --- user includes --------------------------------------
#include "../includes/errorPS.h"
#include "../includes/pwDB.h"
#include "../includes/filehandler.h"

// --- defines --------------------------------------------
#define DATABASENAME     "locker"

// --- functios -------------------------------------------
/**
 * Server main function handles incoming strings, checks if they match to a
 * password and send an open instruction to a locker.
 * 
 * @param[in] unsigned char pointer to received string
 * @param[in] void function pointer to serial communication function 
 *       // TODO Alternative in der interface.h ein define setzten
 * 
 * @date 2017/11/18
 */
void server_main(char *string, void (*fp)(char *out))
{ 
  if ( NULL == string )
  {
    printERRmsg(EMPTY_STRING);
    return;
  }
  char buf[MAX_PASSWORD_LEN];
  errorPS_t ret;
  size_t stringLen = strlen(string);

  // 1. check string length
  if ( MAX_PASSWORD_LEN < stringLen + 1 || MIN_PASSWORD_LEN > stringLen )
  {
    printERRmsg(WRONG_PASWD_LEN);
    return;
  }

  // 2. check wether a database is available
  ret = checkForDatabase(DATABASENAME);
  if ( OK != ret )
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