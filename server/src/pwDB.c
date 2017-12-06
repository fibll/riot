/**
 * RIoT Project Seminar Add-On
 * pwDB – Password Database
 * 
 * @date 2017/11/18
 * 
 * ========= DELETE THIS BLOCK WHEN DONE ==================
 * echo -n "string" | openssl sha1
 * {5fc7e38bffe00ca46add89145464a2eaf759d5c2, "open", "May the Force be with you.", "Roger! Roger!"}
 * {ad782ecdac770fc6eb9a62e44f90873fb97fb26b, "two", "Cortana!", "Yes Master Chief?"}
 * ========================================================
 */
// --- sys includes ---------------------------------------
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/err.h>

// --- user includes --------------------------------------
#include "../includes/pwDB.h"
#include "../includes/filehandler.h"

// --- pasword struct --------------------------------------
typedef struct KEY
{
  // hash sum of pasphrase      // TODO Eventuell mit anderen Zahlen verknüpfen
  char hash[SHA_DIGEST_LENGTH];

  // original input passphrase  // TODO verschlüsselt ablegen
  char passphrase[MAX_PASSWORD_LEN];

  // lock/ unlock passphrase    // TODO verschlüsselt ablegen
  char lockerphrase[MAX_PASSWORD_LEN];

  // response to server/ keypad
  char *response;
}__attribute__((packed)) keyPS_t;

// --- variable -------------------------------------------
static keyPS_t password;

// --- prototypes -----------------------------------------
static errorPS_t calcHash(char *string, unsigned char *md);

// --- functions ------------------------------------------
errorPS_t check_pw(const char *string, const char *dbName)
{
  if ( NULL == string || NULL == dbName )
  {
    return GENERAL_FAILURE;
  }
  unsigned char md[SHA_DIGEST_LENGTH];
  errorPS_t ret = OK;

  // 1. calculate SHA1 hash sum of received password
  ret = calcHash((char*) string, md);

  // 2.
  for (int counter; OK != ret; counter++)
  {
    ret = readFromFile(dbName, &password, sizeof(password), counter);
    if ( 0 != strncmp((char*) md, password.hash, SHA_DIGEST_LENGTH) )
    {
      continue;
    }
  }
  return OK;
}

/**
 * calcHash calculates a SHA1 hash sum of received password phrase.
 * 
 * @param[in] char pointer to string
 * @param[out] unsigned char pinter to message digits buffer for hash sum
 * @return
 * 
 * @date 2017/11/18
 */
static errorPS_t calcHash(char *string, unsigned char *md)
{
  if ( NULL == string )
  {
    return 0;
  }

  EVP_MD_CTX c;
  ERR_load_crypto_strings();

  EVP_MD_CTX_init(&c); /* not necessary when not using _ex */

  //initialise hash operation
  if ( 0 == (EVP_DigestInit(&c, EVP_sha1())) )
  {
    ERR_free_strings();
    return FAIL;
  }

  // generate hash
  if ( 0 == (EVP_DigestUpdate(&c, string, strlen(string)+1)) )
  {
    ERR_free_strings();
    return FAIL;
  }

  // finalise hash operation
  if ( 0 == (EVP_DigestFinal(&c, md, NULL)) )
  {
    ERR_free_strings();
    return FAIL;
  }

  // clean up
  EVP_MD_CTX_cleanup(&c);
  free(string);
  ERR_free_strings();

  return OK;
}
/* EOF */