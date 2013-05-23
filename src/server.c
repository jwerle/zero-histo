#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <stdbool.h>
#include <zmq.h>
#include "helpers.h"
#include "zh.h"

/**
 * Creates a new zh_server_t struct
 *
 * @param {char} *host
 * @return zh_server_t *
 */
zh_server_t *
zh_server_new (char *host) {
	// initialize a new zh_server_t
	zh_server_t *server = malloc(sizeof(zh_server_t));
	// set the host
	server->host = host; 
	// create context
	server->context = zmq_ctx_new();
	// create responder socket
	server->socket = zmq_socket(server->context, ZMQ_REP);
	// set unique ID on socket
	s_set_id(server->socket);
	// return to caller
	return server;
}

/**
 * Binds a new connection on a given zh_server_t struct
 *
 * @param {zh_server_t} *server
 */
void
zh_server_bind (zh_server_t *server) {
	// bind connection
	int rc = zmq_bind(server->socket, server->host);
	if (rc != 0) zh_error("zh_server_bind");
}

/**
 * Listens to a bound connection
 *
 * @param {zh_server_t} *server
 */
void
zh_server_listen (zh_server_t *server, void (*callback) (char[])) {
	//char *foo = "test";
	//callback(*foo);
	while (1) {
		zh_debug("waiting");
		char *buffer = s_recv(server->socket);
		if (buffer == NULL) zh_error("zh_server_listen");
		zh_debug("Got message");
		zh_server_reply_ok(server);
		callback(buffer);
		sleep(1);
	}
}

void
zh_server_reply_ok (zh_server_t *server) {
	zh_debug("reply: ok");
	int size = s_send(server->socket, "ok");
	if (size == -1) zh_error("zh_server_reply_ok");
}