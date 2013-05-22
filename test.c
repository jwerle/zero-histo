#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <term.h>
#include "test.h"
#include "src/zh.h"

int
main (void) {
	init_test();
	char str[256];
	char *host = "tcp://*:5555";
	zh_server_t *server = zh_server_new(host);

	sprintf(str, "server->host = %s", server->host);
	debug(str);

	assert(server->host == host);

	debug("binding server");
	zh_server_bind(server);

	debug("listening on connection");
	zh_server_listen(server);

	// pass test
	pass_test();
}

void
debug (char *message) {
	//printf("  debug: ");
	puts(message);
}

void 
init_test () {
	puts("\nzero-histo: starting test\n-------------------------\n");
}

void
fail_test () {
	term_reset();
	printf("\n  \e[31m\u2717 ");
	term_reset();
	term_color("red");
	puts("fail");
	term_reset();
}

void
pass_test () {
	term_reset();
	printf("\n  \e[32m\u2713 ");
	term_reset();
	term_color("cyan");
	puts("pass");
	term_reset();
	exit(0);
}