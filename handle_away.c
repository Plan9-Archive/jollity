/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle away message (301) */

void c_awayresp(struct message msg, int fp) {

	char *temp, *message, stamp[32];
	int i;
	int mstart = 0;

	for ( i = 0; i < msg.n_params; i++) {

		if (msg.parameters[i][0] == ':') {
			mstart = i;
			break;
		}

	}

	message = malloc( sizeof(char)*(strlen(msg.parameters[mstart])+1) );

	if ( message == 0) {
		print("*** Memory allocation error\n");
		threadexitsall(0);
	}

	shiftl(msg.parameters[mstart]);
	strcpy(message, msg.parameters[mstart]);

	for (i = mstart+1; i < msg.n_params; i++) {

		temp = malloc(sizeof(char)*(strlen(msg.parameters[i])+2) );

		if ( temp == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		sprint(temp, " %s", msg.parameters[i]);

		message = realloc(message, (sizeof(char)*(strlen(message)+strlen(temp)+2)) );

		if ( message == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("REALLOC");
		}

		message = strcat(message, temp);

		free(temp);
	}

	timestamp(stamp);

	print("*** (%s) %s is away: %s\n", stamp, msg.parameters[1], message);

	free(message);

	return;
}
