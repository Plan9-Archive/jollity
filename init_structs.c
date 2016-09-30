/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

void initialize_state_struct(struct state *sta) {

	sta->server = malloc(2*sizeof(char));

	if ( sta->server == 0 ) {
		threadexitsall("MALLOC");
	}

	strcpy(sta->server, "");

	sta->port = malloc(2*sizeof(char));

	if ( sta->port == 0 ) {
		threadexitsall("MALLOC");
	}

	strcpy(sta->port, "");

	sta->nick = malloc(2*sizeof(char));

	if ( sta->nick == 0 ) {
		threadexitsall("MALLOC");
	}

	strcpy(sta->nick, "");

	sta->channel = malloc(2*sizeof(char));

	if ( sta->channel == 0 ) {
		threadexitsall("MALLOC");
	}

	strcpy(sta->channel, "");

	return;
}

void initialize_message_struct(struct message *msg) {

	msg->prefix = malloc(2*sizeof(char));

	if ( msg->prefix == 0 ) {
		threadexitsall("MALLOC");
	}

	strcpy(msg->prefix, "");

	msg->command = malloc(2*sizeof(char));

	if ( msg->command == 0 ) {
		threadexitsall("MALLOC");
	}

	strcpy(msg->command, "");

	msg->n_params = 0;

	msg->parameters = malloc(sizeof(char *));

	if (msg->parameters == 0 ) {
		threadexitsall("MALLOC");
	}

	return;
}

void initialize_command_struct(struct command *cmd) {

	cmd->command = malloc(2*sizeof(char));

	if ( cmd->command == 0 ) {
		threadexitsall("MALLOC");
	}

	strcpy(cmd->command, "");

	cmd->n_params = 0;

	cmd->parameters = malloc(sizeof(char *));

	if (cmd->parameters == 0 ) {
		threadexitsall("MALLOC");
	}

	return;
}
