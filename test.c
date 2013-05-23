#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <term.h>
#include "test.h"
#include "src/helpers.h"
#include "src/zh.h"

char *messages[] = {
	"hi",
	"hey",
	"hello",
	"yo",
	"aye",
	"suppp",
	"whatttuppp"
};

int requests = 0;
int n_messages = sizeof(messages) / sizeof(char *);

int
main (int argc, char * argv[]) {
	char str[256];
	char *server_host = "tcp://*:5555";
	char *client_host = "tcp://localhost:5555";
	
	if (argc > 1 && strcmp(argv[1], "server") == 0) {
		init_test("server");
		zh_server_t *server = zh_server_new(server_host);
	
		sprintf(str, "server->host = %s", server->host);
		zh_debug(str);
		
		assert(server->host == server_host);

		zh_debug("binding server");
		zh_server_bind(server);

		zh_debug("listening on connection");
		zh_server_listen(server, &listen_callback);

	} else {
		init_test("client");
		zh_client_t *client = zh_client_new(client_host);
		
		sprintf(str, "client->host = %s", client->host);
		zh_debug(str);

		assert(client->host == client_host);

		zh_debug("client connecting to host server");
		zh_client_connect(client);
		
		for (int i = 0; i < n_messages; ++i) {
			char msg[256];
			sprintf(msg, "messaging host server: '%s'", messages[i]);
			zh_debug(msg);
			zh_client_message(client, messages[i]);
		}

	}

	// pass test
	pass_test();
}

void
listen_callback (char buffer[]) {
	s_console(buffer);
	if (++requests == n_messages) pass_test();
}



void 
init_test (char *name) {
	printf("\nzero-histo: starting '%s' test\n-------------------------\n", name);
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