/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle PART */

void c_part(struct message msg, int fp) {

	char *user, *channel, *temp, stamp[32];

	temp = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( temp == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	user = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( user == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(temp, strtok(msg.prefix, "!"));

	strcpy(user, strtok(temp, ":"));

	free(temp);

	temp = malloc( sizeof(char) * (strlen(msg.parameters[0])+1) );

	if ( temp == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	channel = malloc( sizeof(char) * (strlen(msg.parameters[0])+1) );

	if ( channel == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(temp, strtok(msg.parameters[0], ":"));
	strcpy(channel, temp);

	free(temp);

	timestamp(stamp);

	print("*** (%s) %s has left channel %s\n", stamp, user, channel);

	free(user);
	free(channel);

	return;

}
