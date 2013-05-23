#ifndef _ZH_CLIENT_H
#define _ZH_CLIENT_H

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