#ifndef _ZH_CLIENT_H
#define _ZH_CLIENT_H

/*
 * Default buffer size.
 */

#ifndef ZH_CLIENT_DEFAULT_RECV_TIMEOUT
#define ZH_CLIENT_DEFAULT_RECV_TIMEOUT 1000
#endif

/**
 * ZH Client struct
 */

typedef struct {
  
  char *host;
  void *context
     , *socket;

} zh_client_t;

/**
 * Client Prototypes
 */
zh_client_t *
zh_client_new (char *host);

void
zh_client_connect (zh_client_t *client);

void
zh_client_message (zh_client_t *client, char *message);

void
zh_client_disconnect (zh_client_t *client);

#endif