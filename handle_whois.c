/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* handle whois server message (312) */

void c_whoisserver(struct message msg, int fp) {

	int i;
	char *servorg, *temp;

	servorg = malloc( sizeof(char) * (strlen(msg.parameters[3])+1) );

	if ( servorg == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	shiftl(msg.parameters[3]);
	strcpy(servorg, msg.parameters[3]);

	for (i = 3; i < msg.n_params; i++) {

		temp = malloc( sizeof(char) * (strlen(msg.parameters[i])+2) );

		if ( temp == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		sprint(temp, " %s", msg.parameters[i]);

		servorg = realloc(servorg, (sizeof(char)*(strlen(servorg)+strlen(temp)+2)) );

		if ( servorg == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("REALLOC");
		}

		servorg = strcat(servorg, temp);

		free(temp);
	}

	print("*** on irc via server %s (%s)\n", msg.parameters[2], servorg);

	free(servorg);

	return;
}

/* handle whois, whowas user messages (311, 314) */

void c_whoisuser(struct message msg, int fp, int whowas) {

	int i;
	char *realname, *temp;

	realname = malloc( sizeof(char) * (strlen(msg.parameters[5])+1) );

	if ( realname == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	shiftl(msg.parameters[5]);
	strcpy(realname, msg.parameters[5]);

	for (i = 6; i < msg.n_params; i++) {

		temp = malloc( sizeof(char) * (strlen(msg.parameters[i])+2) );

		if ( temp == 0) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		sprint(temp, " %s", msg.parameters[i]);

		realname = realloc(realname, (sizeof(char)*(strlen(realname)+strlen(temp)+2)) );

		if ( realname == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		realname = strcat(realname, temp);

		free(temp);
	}

	if (whowas == 0) {
		print("*** %s is %s@%s (%s)\n", msg.parameters[1], msg.parameters[2], msg.parameters[3], realname);
	}

	else {
		print("*** %s was %s@%s (%s)\n", msg.parameters[1], msg.parameters[2], msg.parameters[3], realname);
	}

	free(realname);

	return;
}

/* handle whois channels message (319) */

void c_whoischannels(struct message msg, int fp) {

	int i;
	char *chanlist, *temp;


	chanlist = malloc( sizeof(char) * (strlen(msg.parameters[2])+1) );

	if ( chanlist == 0) {
		print("*** Memory allocation error\n");
		threadexitsall("MALLOC");
	}

	shiftl(msg.parameters[2]);
	strcpy(chanlist, msg.parameters[2]);

	for (i = 3; i < msg.n_params; i++) {

		temp = malloc( sizeof(char) * (strlen(msg.parameters[i])+1) );

		if ( temp == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		sprint(temp, " %s", msg.parameters[i]);

		chanlist = realloc(chanlist, (sizeof(char)*(strlen(chanlist)+strlen(temp)+2)) );

		if ( chanlist == 0 ) {
			print("*** Memory allocation error\n");
			threadexitsall("MALLOC");
		}

		chanlist = strcat(chanlist, temp);

		free(temp);
	}

	print("*** on channels: %s\n", chanlist);

	free(chanlist);

	return;
}
