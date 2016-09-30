/* jollity irc client for plan 9 by sean caron (scaron@umich.edu) */

#include "main.h"

/* user input parser */

// return codes
// -1: input was null string
// -2: strtok error trying to parse command
// -3: strtok error parsing slash from command
// otherwise returns number of parameters parsed for command

int parse_user_input(char *string, struct command *cmd) {

	int i;
	char *temp;

	/* catch null string */

	if (strlen(string) == 1) {
		return -1;
	}

	/* first word will be the command */

	temp = strtok(string, " ");

	if ( temp == 0 ) {
		return -2;
	}

	else {

		cmd->command = realloc( cmd->command, sizeof(char)*(strlen(temp)+1) );

		if ( cmd->command == 0 ) {
			exits("REALLOC");
		}

		strcpy(cmd->command, temp);
	}

	/* subsequent words will be taken as parameters of the command */

	while (1) {

		if ( cmd->n_params > 0 ) {
			cmd->parameters = realloc(cmd->parameters, (sizeof(char *)*(cmd->n_params+1)));

			if ( cmd->parameters == 0 ) {
				threadexitsall("REALLOC");
			}
		}

		temp = strtok(0, " ");

		if ( temp == 0 ) {
			break;
		}

		else {

			*(cmd->parameters+cmd->n_params) = malloc(sizeof(char)*(strlen(temp)+1));

			if ( *(cmd->parameters+cmd->n_params) == 0 ) {
				threadexitsall("MALLOC");
			}

			strcpy( *(cmd->parameters+cmd->n_params), temp);
			cmd->n_params = cmd->n_params + 1;
		}
	}

	for ( i = 0; i < cmd->n_params; i++ ) {
		stripnl( *(cmd->parameters+i) );
	}

	temp = strtok(cmd->command, "/");

	if ( temp == 0 ) {
		return -3;
	}

	else {
		strcpy(cmd->command, strtok(cmd->command, "/"));
	}

	return cmd->n_params;
}
