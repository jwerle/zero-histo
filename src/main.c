#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <stdbool.h>
#include <zmq.h>
#include <commander.h>
#include <term.h>
#include "helpers.h"
#include "zh.h"

/**
 * `runtime options`
 */

static struct {
  const char *host;
} options = { 
  .host = "tcp://localhost:5555"
};



/**
 * `commands`
 */

static void
server (command_t *self) {
  char msg[256];
  sprintf(msg, "starting server listening on '%s'", options.host);
  zh_info(msg);
}



/**
 * `options`
 */

static void
verbose (command_t *self) {
  zh_enable_verbose();
  zh_verbose("enabled");
}

static void
host (command_t *self) {
  char msg[256];
  if (self->arg == 0) return;
  else options.host = self->arg;
  sprintf(msg, "");
}



/**
 * `main`
 */

int
main (int argc, char *argv[]) {
  command_t program;
  // initialize program with argument array and `ZH_VERSION`
  command_init(&program, "zero-histo (zh)", ZH_VERSION);
  /**
   * flags
   */
  command_option(&program, "-v", "--verbose", "enable verbose logging", verbose);
  command_option(&program, "-H", "--host [arg]", "specify connection host.", host);

  /**
   * commands
   */
  command_option(&program, "-s", "--server", "starts a server", server);


  // parse commands
  command_parse(&program, argc, argv);

  // free program
  command_free(&program);
  return 0;
}