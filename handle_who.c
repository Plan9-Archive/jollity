/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"


/* handle who reply server message (353) */

void c_wreply(struct message msg, int fp) {

	int i;
	char *chan, *temp, *userlist;

	userlist = malloc( sizeof(char)*2 );

	if ( userlist == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(userlist, "");

	chan = malloc( sizeof(char)*(strlen(msg.parameters[2])+1) );

	if ( chan == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(chan, msg.parameters[2]);

	/* channel is populated, assemble the user list */

	if ( strlen(msg.parameters[3]) != 1 ) {

		temp = malloc ( sizeof(char) * (strlen(msg.parameters[3])+1) );

		if ( temp == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		strcpy(temp, strtok(msg.parameters[3], ":"));

		userlist = realloc(userlist, (sizeof(char)*(strlen(userlist)+strlen(temp)+2)) );

		if ( userlist == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		strcpy(userlist, temp);

		free(temp);

		for ( i = 4; i < msg.n_params; i++ ) {

			temp = malloc( sizeof(char) * (strlen(msg.parameters[i])+2) );

			if ( temp == 0 ) {
				print("*** Memory allocation error\n");
				threadexitsall("MALLOC");
			}

			sprint(temp, " %s", msg.parameters[i]);

			userlist = realloc(userlist, (sizeof(char)*(strlen(userlist)+strlen(temp)+2)) );

			if ( userlist == 0 ) {
				print("*** Memory allocation error\n");
				threadexitsall("MALLOC");
			}

			userlist = strcat(userlist, temp);

			free(temp);
		}
	}

	print("*** %s : %s\n", chan, userlist);

	free(chan);

	free(userlist);

	return;
}
