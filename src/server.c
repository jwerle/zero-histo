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
  // assert context integrity
  assert(server->context);
  // create responder socket
  server->socket = zmq_socket(server->context, ZMQ_REP);
  // assert socket integrity
  assert(server->socket);
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
  int rc;
  // bind connection
  rc = zmq_bind(server->socket, server->host);
  if (rc != 0) zh_error("zh_server_bind");
}

/**
 * Listens to a bound connection
 *
 * @param {zh_server_t} *server
 */
void
zh_server_listen (zh_server_t *server, void (*callback) (char[])) {
  char *buffer;
  while (1) {
    zh_debug("waiting");
    buffer = s_recv(server->socket);
    if (buffer == NULL) zh_error("zh_server_listen");
    zh_debug("Got message");
    zh_server_reply_ok(server);
    callback(buffer);
    s_sleep(100);
  }
}

void
zh_server_reply_ok (zh_server_t *server) {
  int size;
  zh_debug("reply: ok");
  size = s_send(server->socket, "ok");
  if (size == -1) zh_error("zh_server_reply_ok");
}