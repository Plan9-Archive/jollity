/* jollity irc client for plan 9 by sean caron (scaron@umich.edu) */

#include "main.h"

int mainstacksize = 131072;

void threadmain(int argc, char **argv) {

	char dir[40], *addr;
	int i, fp, fd;

	if ( (argc < 3) || (argc > 4) ) {
		print("usage: %s server nick [port]\n", argv[0]);
		threadexitsall(0);
	}

	// set the terminal to scroll mode; this prevents a problem in which
	// the network input handler seems to crash or act funny when large
	// amounts of text build up in the scrollback buffer.

	fd = open("/dev/wctl", OWRITE);
	fprint(fd, "scroll");
	close(fd);



	/* initialize program state data structure */

	initialize_state_struct(&sta);



	// populate program state data structure

	sta.server = realloc(sta.server, sizeof(char)*(strlen(argv[1])+1) );

	if ( sta.server == 0 ) {
		exits("REALLOC");
	}

	strcpy(sta.server, argv[1]);

	sta.nick = realloc(sta.nick, sizeof(char)*(strlen(argv[2])+1) );

	if ( sta.nick == 0 ) {
		exits("REALLOC");
	}

	strcpy(sta.nick, argv[2]);


	/* if user supplied a port, use that, otherwise default to 6667 */

	if ( argc == 4 ) {

		for ( i = 0; i < strlen(argv[3]); i++ ) {

			if ( isdigit(argv[3][i]) == 0 ) {
				print("invalid port\n");

				free_state_vars(&sta);

				exits("INVALIDPORT");
			}
		}

		sta.port = realloc(sta.port, sizeof(char)*(strlen(argv[3])+1) );

		if ( sta.port == 0 ) {
			exits("REALLOC");
		}

		strcpy(sta.port, argv[3]);
	}

	else {

		sta.port = realloc(sta.port, 5*sizeof(char) );

		if ( sta.port == 0 ) {
			exits("REALLOC");
		}

		strcpy(sta.port, "6667");
	}


	/* try to connect to the server specified by the user */

	print("*** Connecting to port 6667 of server %s\n", argv[1]);

	addr = netmkaddr(argv[1], "tcp", sta.port);

	fp = dial(addr, 0, dir, 0);

	if (fp < 0) {
		print("error connecting to %s on port %s\n", sta.server, sta.port);

		free_state_vars(&sta);

		exits("DIAL");
	}


	fprint(fp, "USER %s %s %s %s\n", sta.nick, sysname(), sta.server, getuser());
	fprint(fp, "NICK %s\n", sta.nick);


	/* kick off the network input handler thread */

	proccreate(network_input_thread, &fp, 65536);

	/* user input loop */

	user_input_thread(&fp);

	/* should never reach this point */

	return;
}
