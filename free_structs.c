/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

void free_state_vars(struct state *sta) {

	free(sta->server);
	free(sta->port);
	free(sta->nick);
	free(sta->channel);

	return;
}

void free_message_vars(struct message *msg) {

	int i;

	free(msg->prefix);

	free(msg->command);

	for ( i = 0; i < msg->n_params; i++ ) {
		free( *(msg->parameters+i) );
	}

	free(msg->parameters);

	return;
}

void free_command_vars(struct command *cmd) {

	int i;

	free(cmd->command);

	for ( i = 0; i < cmd->n_params; i++ ) {

		free( *(cmd->parameters+i) );
	}

	free( cmd->parameters);

	return;
}
