/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle JOIN */

void c_join(struct message msg, int fp) {

	char *user, *channel, *ident, *temp, stamp[32];

	temp = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( temp == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	ident = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( ident == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	user = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( user == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(temp, strtok(msg.prefix, "!"));

	strcpy(ident, strtok(0, "!"));

	strcpy(user, strtok(temp, ":"));

	free(temp);

	temp = malloc( sizeof(char) * (strlen(msg.parameters[0])+1) );

	if ( temp == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(temp, strtok(msg.parameters[0], ":"));

	channel = malloc( sizeof(char) * (strlen(temp)+1) );

	if ( channel == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(channel, temp);

	timestamp(stamp);

	print("*** (%s) %s (%s) has joined channel %s\n", stamp, user, ident, channel);

	free(user);
	free(channel);
	free(ident);
	free(temp);

	return;

}
