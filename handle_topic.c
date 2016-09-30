/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle TOPIC */

void c_topic(struct message msg, int fp, int isnew) {

	int i, mstart;
	char *user, *channel, *temp, *topic, stamp[32];

	mstart = 0;


	if (isnew == 1) {

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

		channel = malloc( sizeof(char) * (strlen(msg.parameters[0])+1) );

		if ( channel == 0) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		strcpy(channel, msg.parameters[0]);

		free(temp);
	}

	else if (isnew == 0) {

		channel = malloc( sizeof(char) * (strlen(msg.parameters[1])+1) );

		if ( channel == 0) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		strcpy(channel, msg.parameters[1]);
	}

	for ( i = 1; i < msg.n_params; i++) {
		if (msg.parameters[i][0] == ':') {
			mstart = i;
			break;
		}
	}

	topic = malloc( sizeof(char)*(strlen(msg.parameters[mstart])+1) );

	if ( topic == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	shiftl(msg.parameters[mstart]);
	strcpy(topic, msg.parameters[mstart]);

	for (i = mstart+1; i < msg.n_params; i++) {

		temp = malloc( sizeof(char) * (strlen(msg.parameters[i])+2) );

		if ( temp == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		sprint(temp, " %s", msg.parameters[i]);

		topic = realloc(topic, (sizeof(char)*(strlen(topic)+strlen(temp)+2)) );

		if ( topic == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		topic = strcat(topic, temp);

		free(temp);
	}

	if (isnew == 1) {

		timestamp(stamp);

		print("*** (%s) %s has changed the topic on channel %s to %s\n", stamp, user, channel, topic);

		free(user);
	}

	else if (isnew == 0) {
		print("*** Topic for %s: %s\n", channel, topic );
	}

	free(channel);
	free(topic);

	return;

}
