/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* network input parser */

int parse_network_input(char *string, struct message *msg) {

	int i;
	char *temp;

	/* prefix is attached; apparently this is optional per RFC 2812 */

	if (string[0] == ':') {
		temp = strtok(string, " ");

		if ( temp == 0 ) {
			return -1;
		}

		else {

			msg->prefix = realloc( msg->prefix, sizeof(char)*(strlen(temp)+1) );

			if ( msg->prefix == 0 ) {
				threadexitsall("REALLOC");
			}

			strcpy(msg->prefix, temp);
		}

		temp = strtok(0, " ");

		if ( temp == 0 ) {
			return -1;
		}

		else {

			msg->command = realloc( msg->command, sizeof(char)*(strlen(temp)+1) );

			if ( msg->command == 0 ) {
				threadexitsall("REALLOC");
			}

			strcpy(msg->command, temp );
		}

		stripnl(msg->prefix);
	}

	/* command, no prefix */

	else {

		temp = strtok(string, " ");

		if ( temp == 0 ) {
			return -1;
		}

		else {

			msg->command = realloc(msg->command, sizeof(char)*(strlen(temp)+1) );

			if ( msg->command == 0 ) {
				threadexitsall("REALLOC");
			}

			strcpy(msg->command, temp);
		}

	}

	/* strip the newline from the command */

	stripnl(msg->command);

	/* tokenize the parameters */

	while (1) {

		if ( msg->n_params > 0 ) {

			msg->parameters = realloc(msg->parameters, (sizeof(char *) * (msg->n_params+1)) );

			if ( msg->parameters == 0 ) {
				threadexitsall("REALLOC");
			}
		}

		temp = strtok(0, " ");

		if ( temp == 0 ) {
			break;
		}

		else {

			*(msg->parameters+msg->n_params) = malloc( sizeof(char)*(strlen(temp)+1) );

			if ( *(msg->parameters+msg->n_params) == 0 ) {
				threadexitsall("MALLOC");
			}

			strcpy( *(msg->parameters+msg->n_params), temp);
			msg->n_params = msg->n_params + 1;
		}

	}

	/* strip the newlines from the individual parameters */

	for ( i = 0; i < msg->n_params; i++ ) {
		stripnl( *(msg->parameters+i) );
	}

	/* return number of parameters to the caller */

	return msg->n_params;

}
