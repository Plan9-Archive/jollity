/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle INVITE */

void c_invite(struct message msg, int fp) {

	char *user, *chan, *temp, stamp[32];

	temp = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( temp == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	/* if we were the user that got the invite */

	if ( strcmp(sta.nick, msg.parameters[0]) == 0) {
	
		/* inviting user */

		strcpy(temp, strtok(msg.prefix, ":"));

		user = malloc( sizeof(char) * (strlen(temp)+1) );

		if ( user == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		strcpy(user, strtok(temp, "!"));

		/* channel invited to */

		shiftl(msg.parameters[1]);

		chan = malloc( sizeof(char) * (strlen(msg.parameters[1])+1) );

		if ( chan == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		strcpy(chan, msg.parameters[1]);

		timestamp(stamp);

		print("*** (%s) %s invites you to channel %s\n", stamp, user, chan);

		free(user);

		free(chan);
	}

	free(temp);

	return;
}
