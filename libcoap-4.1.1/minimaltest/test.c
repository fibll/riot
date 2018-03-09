#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *arguments[][5] = { 
	{"/home/tobi/RIOTPS/libcoap-4.1.1/minimaltest/test.sh", "Arg1", "Arg2", "Arg3", NULL},
	{NULL,NULL,NULL,NULL,NULL}
};

int main(int argc, char **argv) {
  fprintf(stderr, "EXEV Testlauf\n\n");
  fprintf(stderr, "C : %s %s %s %s\n\n",arguments[0][0], arguments[0][1], arguments[0][2], arguments[0][3]);
  
  execv(arguments[0][0], arguments[0]);
  
  fprintf(stderr, "\nC : Nach exec!\n");
  
  return 0;
}
