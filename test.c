#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <term.h>
#include "test.h"
#include "src/helpers.h"
#include "src/zh.h"

int
main (int argc, char * argv[]) {
	init_test();

	char str[256];
	char *server_host = "tcp://*:5555";
	char *client_host = "tcp://localhost:5555";
	
	if (argc > 1 && strcmp(argv[1], "server") == 0) {
		zh_server_t *server = zh_server_new(server_host);
	
		sprintf(str, "server->host = %s", server->host);
		zh_debug(str);
		
		assert(server->host == server_host);

		zh_debug("binding server");
		zh_server_bind(server);

		zh_debug("listening on connection");
		zh_server_listen(server, &listen_callback);

	} else {
		zh_client_t *client = zh_client_new(client_host);
		
		sprintf(str, "client->host = %s", client->host);
		zh_debug(str);

		assert(client->host == client_host);

		zh_debug("client connecting to host server");
		zh_client_connect(client);

		int n = 10;
		
		for (int i = 0; i < n; ++i) {
			zh_debug("messaging host server");
			zh_client_message(client, "yooooo");
			s_sleep(100);
		}

	}

	// pass test
	pass_test();
}

int requests = 0;

void
listen_callback (char buffer[]) {
	s_console(buffer);
	char *str;
	//zh_debug(str);
	if (++requests == 10) pass_test();
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