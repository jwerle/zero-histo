#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <term.h>
#include "test.h"
#include "src/helpers.h"
#include "src/zh.h"

/**
 * test name
 */

char suite[256]

/**
 * client messages
 */
   , *messages[] = {
      "hi",
      "hey",
      "hello",
      "yo",
      "aye",
      "suppp",
      "whatttuppp"
    };

/**
 * number of incoming server request
 */

int n_requests = 0

/**
 * number of message to send
 */
  , n_messages = sizeof(messages) / sizeof(char *);

int
main (int argc, char * argv[]) {
  char str[256]
     , *server_host = "tcp://*:5555"
     , *client_host = "tcp://localhost:5555";
  
  if (argc > 1 && strcmp(argv[1], "server") == 0) {
    init_test("server");
    zh_server_t *server = zh_server_new(server_host);
  
    sprintf(str, "server->host = %s", server->host);
    zh_debug(str);
    
    assert(server->host == server_host);

    zh_debug("binding server");
    zh_server_bind(server);

    zh_debug("listening on connection");
    zh_server_listen(server, &listen_callback);

  } else {
    init_test("client");
    zh_client_t *client = zh_client_new(client_host);
    
    sprintf(str, "client->host = %s", client->host);
    zh_debug(str);

    assert(client->host == client_host);

    zh_debug("client connecting to host server");
    zh_client_connect(client);
    
    sprintf(str, "message count '%d'", n_messages);
    zh_debug(str);

    for (int i = 0; i < n_messages; ++i) {
      sprintf(str, "messaging host server: (%d), '%s'", i, messages[i]);
      zh_debug(str);
      zh_client_message(client, messages[i]);
    }

    zh_client_disconnect(client);

  }

  // pass test
  pass_test();
}

/**
 * callback passed to `zh_server_listen`
 */

void
listen_callback (char buffer[]) {
  s_console(buffer);
  if (++n_requests == n_messages) pass_test();
}

/**
 * test initializer
 */

void 
init_test (char *name) {
  sprintf(suite, "%s_test", name);
  printf("\nzero-histo: starting '%s' test\n-------------------------\n", name);
}

/**
 * fails a test
 */

void
fail_test () {
  term_reset();
  printf("  %s: \e[31m\u2717 ", suite);
  term_reset();
  term_color("red");
  puts("fail");
  term_reset();
  exit(1);
}

/**
 * passes a test
 */
 
void
pass_test () {
  term_reset();
  printf("  %s: \e[32m\u2713 ", suite);
  term_reset();
  term_color("cyan");
  puts("pass");
  term_reset();
  exit(0);
}