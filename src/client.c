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
  // assert context integrity
  assert(client->context);
  // create responder socket
  client->socket = zmq_socket(client->context, ZMQ_REQ);
  // assert socket integrity
  assert(client->socket);
  // set unique ID on socket
  s_set_id(client->socket);
  // return to caller
  return client;
}

void
zh_client_connect (zh_client_t *client) {
  int rc, timeout;

  rc = zmq_connect (client->socket, client->host);
  timeout = ZH_CLIENT_DEFAULT_RECV_TIMEOUT;

  if (rc != 0) zh_error("zh_client_connect");

  zmq_setsockopt(client->socket, ZMQ_RCVTIMEO, (const void *)timeout, 0);
}

void
zh_client_message (zh_client_t *client, char *message) {
  int size;
  char *buffer;

  size = s_send (client->socket, message);
  buffer = s_recv(client->socket);

  if (size != strlen(message)) zh_error("zh_client_message");
  else if (buffer == NULL) zh_error("zh_client_message");
}

void
zh_client_disconnect (zh_client_t *client) {
  zmq_close (client->socket);
  zmq_ctx_destroy (client->context);
}