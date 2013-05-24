#ifndef _ZH_SERVER_H
#define _ZH_SERVER_H

/**
 * ZH Server struct
 */
typedef struct {

  char *host;
  void *context
     , *socket;

} zh_server_t;




/**
 * Server Prototypes
 */

zh_server_t *
zh_server_new (char *host);

void
zh_server_bind (zh_server_t *server);

void
zh_server_listen (zh_server_t *server, void (*callback) (char[]));

void
zh_server_reply_ok (zh_server_t *server);

void
zh_server_destroy (zh_server_t *server);

#endif