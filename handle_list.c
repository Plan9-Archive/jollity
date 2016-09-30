/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle list server message (322) */

void c_list(struct message msg, int fp) {

	int i;
	char *chan, *numusers, *temp, *topic;

	chan = malloc( sizeof(char) * (strlen(msg.parameters[1])+1) );

	if ( chan == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(chan, msg.parameters[1]);

	numusers = malloc( sizeof(char) * (strlen(msg.parameters[2])+1) );

	if ( numusers == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(numusers, msg.parameters[2]);

	/* no topic */

	topic = malloc( sizeof(char) * 2 );

	if ( topic == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	if ( strlen(msg.parameters[3]) == 1 ) {
		strcpy(topic, "");
	}

	/* topic set; parse it out */

	else {
		shiftl(msg.parameters[3]);

		topic = realloc(topic, (sizeof(char)*(strlen(topic)+strlen(msg.parameters[3])+2)) );

		if ( topic == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("REALLOC");
		}

		strcpy(topic, msg.parameters[3]);

		for ( i = 4; i < msg.n_params; i++ ) {

			temp = malloc( sizeof(char) * (strlen(msg.parameters[i])+2) );

			if ( temp == 0 ) {
				print("*** Memory allocation error\n");
				threadexitsall("MALLOC");
			}

			sprint(temp, " %s", msg.parameters[i]);

			topic = realloc(topic, (sizeof(char)*(strlen(topic)+strlen(temp)+2)) );

			if ( topic == 0 ) {
				print("*** Memory allocation error\n");
				threadexitsall("REALLOC");
			}

			topic = strcat(topic, temp);

			free(temp);
		}
	}

	print("*** %s\t%s\t%s\t\n", chan, numusers, topic);
	
	free(topic);
	free(chan);
	free(numusers);

	return;
}
