/**
 * Project Locker coap-client Add-On
 * 
 * TOTO : add config function to add parameters and devices during live time
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEBUG 1

// -> { full sh script path, USB addr., tunnel ID, IPV6 addr., NULL }
char *arguments[][5] = { 
	{"/home/{user}/RIOT/examples/server/start_network.sh", "/dev/ttyACM0", "tap0", "fd17:cafe:cafe:3::3/64", NULL},
	{NULL,NULL,NULL,NULL,NULL}
};

int check_for_password(char payload) {
  if( '9' != payload) {
	  printf("\nReceived a message for project Locker with a wrong password! ");
	  printf("-> Return to stand by mode.\n");
      return 0;
  }
  
  printf("\nReceived a message for project Locker. -> Access granted!\n");
  
  // create shell command
  // static char shellBuf[128];
  // sprintf(shellBuf,"%s %s %s %s\n",arguments[0][0], arguments[0][1], arguments[0][2], arguments[0][3]);
  
  // run script
  // system(ahellBuf);
#if (DEBUG)
  printf("%s %s %s %s\n",arguments[0][0], arguments[0][1], arguments[0][2], arguments[0][3]);
#endif
  
  execv(arguments[0][0], arguments[0]);
  
  return 0;
}
