#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <stdbool.h>
#include <zmq.h>
#include "helpers.h"
#include "zh.h"

void
zh (void) {

}

void
zh_error (char *func) {
  printf("error: '%s': %s\n", func, zmq_strerror (errno));
  abort();
}

void
zh_debug (char *message) {
  printf("  debug: ");
  puts(message);
}