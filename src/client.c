#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <stdbool.h>
#include <zmq.h>
#include "helpers.h"
#include "zh.h"

/**
 * Creates a new zh_client_t struct
 *
 * @param {char} *host
 * @return zh_client_t *
 */
zh_client_t *
zh_client_new (char *host) {
	// initialize a new zh_client_t
	zh_client_t *client = malloc(sizeof(zh_client_t));
	// set the host
	client->host = host; 
	// create context
	client->context = zmq_ctx_new();
	assert(client->context);
	// create responder socket
	client->socket = zmq_socket(client->context, ZMQ_REQ);
	assert(client->socket);
	// set unique ID on socket
	//s_set_id(client->socket);
	// return to caller
	return client;
}

void
zh_client_connect (zh_client_t *client) {
	int rc = zmq_connect (client->socket, client->host);
	printf("%d\n", rc);
	if (rc != 0) zh_error("zh_client_connect");
}

void
zh_client_message (zh_client_t *client, char *message) {
	int size = s_send (client->socket, message);
	if (size != strlen(message)) zh_error("zh_client_message");
}