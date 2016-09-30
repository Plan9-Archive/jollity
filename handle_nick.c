/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle NICK */

void c_nick(struct message msg, int fp) {

	char *user, *newnick, *temp, stamp[32];

	temp = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( temp == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	user = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( user == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(temp, strtok(msg.prefix, "!"));
	strcpy(user, strtok(temp, ":"));

	free(temp);

	temp = malloc( sizeof(char) * (strlen(msg.parameters[0])+1) );

	if ( temp == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(temp, strtok(msg.parameters[0], ":"));

	newnick = malloc( sizeof(char)*(strlen(temp)+1) );

	if ( newnick == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(newnick, temp);

	timestamp(stamp);

	print("*** (%s) %s is now known as %s\n", stamp, user, newnick);

	free(temp);
	free(user);
	free(newnick);

	return;

}

