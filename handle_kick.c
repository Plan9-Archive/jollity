/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle KICK */

void c_kick(struct message msg, int fp) {

	int i;
	char *temp, *reason, *user, *channel, *kicked, stamp[32];

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

	strcpy(temp, strtok(msg.prefix, ":"));
	strcpy(user, strtok(temp, "!"));

	channel = malloc( sizeof(char) * (strlen(msg.parameters[0])+1) );

	if ( channel == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(channel, msg.parameters[0]);

	kicked = malloc( sizeof(char) * (strlen(msg.parameters[1])+1) );

	if ( kicked == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(kicked, msg.parameters[1]);

	reason = malloc( sizeof(char) * (strlen(msg.parameters[2])+2) );

	if ( reason == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	shiftl(msg.parameters[2]);
	strcpy(reason, msg.parameters[2]);

	for (i = 3; i < msg.n_params; i++) {

		temp = malloc( sizeof(char)*(strlen(msg.parameters[i])+2) );

		if ( temp == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		sprint(temp, " %s", msg.parameters[i]);

		reason = realloc(reason, (sizeof(char)*(strlen(reason)+strlen(temp)+2)) );

		if ( reason == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("REALLOC");
		}

		reason = strcat(reason, temp);

		free(temp);
	}

	timestamp(stamp);

	print("*** (%s) %s has been kicked off channel %s by %s (%s)\n", stamp, kicked, channel, user, reason);

	free(user);
	free(kicked);
	free(channel);
	free(reason);

	return;
}
