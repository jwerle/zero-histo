#ifndef ZERO_HISTO_H
#define ZERO_HISTO_H

#include <stdbool.h>

void
zh ();

/**
 * ZH Server struct
 */
typedef struct {

	char *host;
	void *context;
	void *socket;
	bool bound;

} zh_server_t;

/**
 * ZH Client struct
 */

typedef struct {
	char *host;
	void *context;
	void *socket;
	bool bound;

} zh_client_t;


/**
 * Server Prototypes
 */

zh_server_t *
zh_server_new (char *host);

void
zh_server_bind (zh_server_t *server);

void
zh_server_listen (zh_server_t *server);

void
zh_server_destroy (zh_server_t *server);


/**
 * Client Prototypes
 */
zh_client_t *
zh_client_new (char *host);

void
zh_client_destroy (zh_client_t *client);
#endif