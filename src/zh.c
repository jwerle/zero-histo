#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <stdbool.h>
#include <zmq.h>
#include <logger.h>
#include "helpers.h"
#include "zh.h"

bool __zh_verbose_enabled = false;

void
zh (void) {

}

void
zh_error (char *func) {
  term_color("red");
  printf("error: ");
  if (errno != 0) printf("'%s': %s\n", func, zmq_strerror (errno));
  else puts(func);
  term_reset();
  abort();
}

void
zh_debug (char *message) {
  logger_debug(message);
}

void
zh_info (char *message) {
  logger_info(message);
}

void
zh_enable_verbose () {
  __zh_verbose_enabled = (bool) true;
}

void
zh_disabled_verbose () {
  __zh_verbose_enabled = (bool) false;
}

void
zh_verbose (char *message) {
  if (__zh_verbose_enabled == false) return;
  term_color("green");
  printf("  verbose: ");
  term_reset();
  puts(message);
}