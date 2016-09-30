/* jollity irc client for plan 9 by sean caron (scaron@umich.edu) */

#include <u.h>
#include <libc.h>
#include <stdio.h>
#include <ctype.h>
#include <thread.h>


/* these encode the program version as major.minor */

#define VMA			1
#define VMI			1


/* program state */

struct state {

	char *server;
	char *port;

	char *channel;

	char *nick;
};

/* a command entered by the user */

struct command {

	char *command;

	int n_params;
	char **parameters;
};

/* a message received from the network */

struct message {

	char *prefix;
	char *command;

	int n_params;
	char **parameters;

};


/* global variables */

struct state sta;


/* function prototypes */

/* top level routines of threads */

void network_input_thread(void *filep);
void user_input_thread(void *filep);

/* input and output parsers */

int parse_network_input(char *string, struct message *msg);
int parse_user_input(char *string, struct command *cmd);

void initialize_state_struct(struct state *sta);
void initialize_command_struct(struct command *cmd);
void initialize_message_struct(struct message *msg);

void free_state_vars(struct state *sta);
void free_command_vars(struct command *cmd);
void free_message_vars(struct message *msg);

/* string related utility routines */

void stripcr(char *string);
void stripnl(char *string);
void shiftl(char *string);
void stripctcp(char *string);

int read_line_user(char **ptr);
int read_line_net(int infd, char **ptr);

/* time related utility routines */

void timestamp(char *stamp);

/* network input handlers */

void c_ping(struct message msg, int fp);
void c_privmsg(struct message msg, int fp);
void c_srvmsg(struct message msg, int fp);
void c_join(struct message msg, int fp);
void c_part(struct message msg, int fp);
void c_topic(struct message msg, int fp, int isnew);
void c_srvmodes(struct message msg, int fp);
void c_numchans(struct message msg, int fp);
void c_mode(struct message msg, int fp);
void c_quit(struct message msg, int fp);
void c_invite(struct message msg, int fp);
void c_list(struct message msg, int fp);
void c_wreply(struct message msg, int fp);
void c_kick(struct message msg, int fp);
void c_whoisuser(struct message msg, int fp, int whowas);
void c_whoischannels(struct message msg, int fp);
void c_whoisserver(struct message msg, int fp);
void c_ctcp(struct message msg, int fp);
void c_notice(struct message msg, int fp);
void c_nick(struct message msg, int fp);
void c_awayresp(struct message msg, int fp);
void c_unique(struct message msg, int fp);
void c_supported(struct message msg, int fp);
