/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle messages from server (numeric commands) */

void c_srvmsg(struct message msg, int fp) {

	int i, mstart;
	char *temp, *message;

	mstart = 0;

	for ( i = 0; i < msg.n_params; i++) {
		if (msg.parameters[i][0] == ':') {
			mstart = i;
			break;
		}
	}

	message = malloc( sizeof(char)*(strlen(msg.parameters[mstart])+1) );

	if ( message == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	shiftl(msg.parameters[mstart]);

	strcpy(message, msg.parameters[mstart]);

	for (i = mstart+1; i < msg.n_params; i++) {

		temp = malloc( sizeof(char) * (strlen(msg.parameters[i])+2) );

		if ( temp == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		sprint(temp, " %s", msg.parameters[i]);

		message = realloc(message, (sizeof(char)*(strlen(message)+strlen(temp)+4)) );

		if ( message == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		message = strcat(message, temp);

		free(temp);
	}

	print("*** %s\n", message);

	free(message);

	return;
}
