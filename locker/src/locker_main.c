/**
 * RIoT Project Seminar Add-On
 * locker_main – main interface function
 * 
 * @date 2017/11/18
 */
// --- sys includes ---------------------------------------
#include <stdio.h>

// --- user includes --------------------------------------
#include "shell.h"
#include "msg.h"
#include "../includes/error.h"
// #include "../includes/locker.h"

// --- defines --------------------------------------------
#define MAIN_QUEUE_SIZE (8)

// --- globals --------------------------------------------
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];
const shell_command_t shell_commands[] =
    { // cmd      description          function
        {"hello", "prints hello world", hello_world},
        {NULL, NULL, NULL}}; // Empty command to terminate the list

// --- functios -------------------------------------------
static int hello_world(int argc, char **argv)
{
  /* Suppress compiler errors */
  (void)argc;
  (void)argv;
  printf("hello world! %d\n", argc);
  return 0;
}

static int SetGPIO(int argc, char **argv)
{
  if (2 != argc)
  {
    fprintf(stderr, "usage: sgip <Port> <Pin>\n");
    fprintf(stderr, "Port eg PA or PB\n");
    fprintf(stderr, "Pin should be a integer\n");
  }
  // Todo: Abfragen
  gpio_t PApin = GPIO_PIN(PB, 2); // GPIO_PIN(Port Abkürzung, Pin)
  gpio_init(PApin, GPIO_OUT);
  gpio_set(PApin);   // high
  gpio_clear(PApin); // low
}

int main(void)
{
  /* we need a message queue for the thread running the shell in order to
     * receive potentially fast incoming networking packets */
  msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
  puts("RIOT border router example application with locker extention");

  /* start shell */
  puts("All up, running the shell now");
  char line_buf[SHELL_DEFAULT_BUFSIZE];
  shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

  /* should be never reached */
  return 0;
}