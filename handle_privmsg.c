/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle PRIVMSG */

void c_privmsg(struct message msg, int fp) {

	int i, mstart;
	char *user, *temp, *message, stamp[32];

	mstart = 0;

	temp = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( temp == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	user = malloc ( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( temp == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(temp, strtok(msg.prefix, "!"));
	strcpy(user, strtok(temp, ":"));

	free(temp);

	for ( i = 0; i < msg.n_params; i++) {

		if (msg.parameters[i][0] == ':') {
			mstart = i;
			break;
		}

	}

	message = malloc( sizeof(char) * (strlen(msg.parameters[mstart])+1) );

	if ( message == 0) {
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

	timestamp(stamp);

	/* private message */

	if ( strcmp(msg.parameters[0], sta.nick) == 0) {
		print("(%s) *%s* %s\n", stamp, user, message);
	}

	/* channel message */

	else {
		print("(%s) <%s> %s\n", stamp, user, message);
	}

	free(user);
	free(message);

	return;
}
