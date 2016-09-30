/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle MODE */

void c_mode(struct message msg, int fp) {

	int i;
	char *temp, *setter, *recipient, *mode, stamp[32];

	temp = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( temp == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	setter = malloc( sizeof(char) * (strlen(msg.prefix)+1) );

	if ( setter == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	mode = malloc( sizeof(char) * 2 );

	if ( mode == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	strcpy(mode, "");

	strcpy(temp, strtok(msg.prefix, ":"));
	strcpy(setter, strtok(temp, "!"));

	recipient = malloc( sizeof(char) * (strlen(msg.parameters[0])+1) );

	if ( recipient == 0 ) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	free(temp);

	strcpy(recipient, msg.parameters[0]);

	timestamp(stamp);

	if ( msg.parameters[0][0] == '#' ) {

		/* stop one iteration before the last then sprint without a trailing space so it looks nice */

		for (i = 1; i < msg.n_params-1; i++) {

			temp = malloc( sizeof(char) * (strlen(msg.parameters[i])+2) );

			if ( temp == 0 ) {
				print("*** Memory allocation error\n");
				threadexitsall("MALLOC");
			}

			sprint(temp, "%s ",   msg.parameters[i]);

			mode = realloc(mode, (sizeof(char)*(strlen(mode)+strlen(temp)+2)) );

			if ( mode == 0 ) {
				print("*** Memory allocation error\n");
				threadexitsall("MALLOC");
			}

			strcat(mode, temp);

			free(temp);
		}

		temp = malloc( sizeof(char) * (strlen(msg.parameters[i])+2) );

		if ( temp == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		sprint(temp, "%s", msg.parameters[i]);

		mode = realloc(mode, (sizeof(char)*(strlen(mode)+strlen(temp)+2)) );

		if ( mode == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		strcat(mode, temp);

		free(temp);

		print("*** (%s) Mode change \"%s\" on channel %s by %s\n", stamp, mode, recipient, setter);
	}

	else {
	
		mode = realloc(mode, (sizeof(char)*(strlen(msg.parameters[1])+1)) );

		if ( mode == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		strcpy(mode, strtok(msg.parameters[1], ":"));

		print("*** (%s) Mode change \"%s\" for user %s by %s\n", stamp, mode, recipient, setter);
	}

	free(mode);
	free(recipient);
	free(setter);

	return;
}
