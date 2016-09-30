/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* CTCP handler; we just support VERSION for now */

void c_ctcp(struct message msg, int fp) {

	char *user, *temp, *message;
	char ctcpdelim[2];

	ctcpdelim[0] = 0x1;
	ctcpdelim[1] = '\0';


	user = malloc( sizeof(char)*(strlen(msg.prefix)+1) );

	if ( user == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	temp = malloc( sizeof(char)*(strlen(msg.prefix)+1) );

	if ( temp == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(temp, strtok(msg.prefix, "!"));
	shiftl(temp);
	strcpy(user, temp);

	free(temp);

	shiftl(msg.parameters[1]);
	stripctcp(msg.parameters[1]);

	/* CTCP VERSION */

	if ( strcmp(msg.parameters[1], "VERSION") == 0) {

		temp = malloc( sizeof(char) * 8 );

		if ( temp == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		sprint(temp, "%d.%d ", VMA, VMI);

		message = malloc( sizeof(char) * (81+strlen(temp)) );

		if ( message == 0) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		strcpy(message, ctcpdelim);

		message = strcat(message, "VERSION jollity irc " );
		message = strcat(message, temp);
		message = strcat(message, "| plan 9 | sean caron (scaron@umich.edu)");

		message = strcat(message, ctcpdelim);

		fprint(fp, "NOTICE %s :%s\n", user, message);

		free(temp);
		free(message);
	}

	free(user);

	return;
}
