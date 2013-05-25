#ifndef _ZH_H
#define _ZH_H

/*
 * version
 */

#ifndef ZH_VERSION
#define ZH_VERSION "0.0.1"
#endif

#include <stdbool.h>
#include "server.h"
#include "client.h"

void
zh ();

void
zh_error (char *func);

void
zh_debug (char *message);

void
zh_info (char *message);

void
zh_enable_verbose ();

void
zh_disabled_verbose ();

void
zh_verbose (char *message);

#endif