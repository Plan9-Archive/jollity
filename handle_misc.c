/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle PING */

void c_ping(struct message msg, int fp) {

	char *server;

	server = malloc( sizeof(char) * (strlen(msg.parameters[0])+1) );

	if ( server == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(server, strtok( msg.parameters[0], ":"));

	fprint(fp, "PONG %s\n", server);

	free(server);

	return;
}

/* handle channel modes server message */

void c_srvmodes(struct message msg, int fp) {

	print("*** umodes available %s, channel modes available %s\n", msg.parameters[3], msg.parameters[4]);

	return;
}

/* handle number of channels server message */

void c_numchans(struct message msg, int fp) {

	print("*** %s channels have been formed\n", msg.parameters[1]);

	return;
}

/* handle unique ID server message */

void c_unique(struct message msg, int fp) {

	print("*** %s your unique id\n", msg.parameters[1]);

	return;
}

/* handle 005 supported messages */

void c_supported(struct message msg, int fp) {

	int i, mstart;

	mstart = 0;

	for ( i = 1; i < msg.n_params; i++) {
		if (msg.parameters[i][0] == ':') {
			mstart = i;
			break;
		}
	}

	print("*** ");

	for ( i = 1; i < mstart; i++ ) {
		print("%s ", msg.parameters[i]);
	}

	printf("are supported by this server\n");

	return;
}
