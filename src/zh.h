#ifndef _ZH_H
#define _ZH_H

#include <stdbool.h>
#include "server.h"
#include "client.h"

void
zh ();

void
zh_error (char *func);

void
zh_debug (char *message);

#endif