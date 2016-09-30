/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle QUIT */

void c_quit(struct message msg, int fp) {

	int i;
	char *temp, *reason, *user, stamp[32];

	temp = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( temp == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	user = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( user == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(temp, strtok(msg.prefix, ":"));
	strcpy(user, strtok(temp, "!"));

	free(temp);

	reason = malloc ( sizeof(char) * (strlen(msg.parameters[0])+1) );

	if ( reason == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	shiftl(msg.parameters[0]);
	strcpy(reason, msg.parameters[0]);

	for (i = 1; i < msg.n_params; i++) {

		temp = malloc ( sizeof(char) * (strlen(msg.parameters[i])+2) );

		if ( temp == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		sprint(temp, " %s", msg.parameters[i]);

		reason = realloc(reason, (sizeof(char)*(strlen(reason)+strlen(temp)+2)) );

		if ( reason == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		strcpy(reason, strcat(reason, temp));

		free(temp);

	}

	timestamp(stamp);

	print("*** (%s) Signoff: %s (%s)\n", stamp, user, reason);

	free(user);
	free(reason);

	return;
}
