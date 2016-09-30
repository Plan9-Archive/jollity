/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* user input handler thread */

void user_input_thread(void *filep) {

	/* old vars*/

	int *fp, i, nparams;
	fp = filep;

	/* rewrite vars*/

	struct command cmd;
	char *line, *temp, *message;


	/* loop forever getting lines of input from the user */

	while (1) {
	
		initialize_command_struct(&cmd);

		read_line_user(&line);

		stripnl(line);

		/* if not prefixed by a slash then the user is typing into the channel */

		if ( line[0] != '/' ) {

			/* only process lines that arent the null string */

			if ( strlen(line) > 0 ) {

				/* send it to the server */

				fprint(*fp, "PRIVMSG %s :%s\n", sta.channel, line);

				/* and echo a copy locally to make the user feel better */

				print("> %s\n", line);
			}
		}

		/* otherwise if input prefixed by a slash we must interpret it as a command */

		else {
			nparams = parse_user_input(line, &cmd);

			/* convert the command to all lower case before processing */

			for ( i = 0; i < strlen(cmd.command); i++ ) {

				if ( isalpha(cmd.command[i]) ) {
					cmd.command[i] = tolower(cmd.command[i]);
				}
			}

			/* quit */

			if ( strcmp(cmd.command, "quit") == 0) {
				fprint(*fp, "QUIT\n");
				threadexitsall(0);
			}

			/* join | channel */

			if ( (strcmp(cmd.command, "join") == 0) || (strcmp(cmd.command, "channel") == 0) ) {

				/* no channel key specified */

				if ( cmd.n_params == 1) {

					if ( strcmp(sta.channel, "") != 0 ) {
						fprint(*fp, "PART %s\n", sta.channel);
					}

					sta.channel = realloc(sta.channel, sizeof(char)*(strlen(*(cmd.parameters))+1) );

					if ( sta.channel == 0 ) {
						threadexitsall("REALLOC");
					}

					strcpy(sta.channel, *(cmd.parameters) );

					fprint(*fp, "JOIN %s\n", sta.channel);
				}

				/* channel key specified */

				else if ( cmd.n_params == 2) {
					fprint(*fp, "PART %s\n", sta.channel);

					sta.channel = realloc(sta.channel, sizeof(char)*(strlen(*(cmd.parameters))+1) );

					if ( sta.channel == 0 ) {
						threadexitsall("REALLOC");
					}

					strcpy(sta.channel, *(cmd.parameters) );

					fprint(*fp, "JOIN %s %s\n", sta.channel, *(cmd.parameters+1) );
				}

				/* nothing specified; just print current channel */

				else {
					print("*** Current channel %s\n", sta.channel );
				}
			}

			/* part */

			if ( strcmp(cmd.command, "part") == 0) {

				fprint(*fp, "PART %s\n", sta.channel);

				sta.channel = realloc(sta.channel, 2*sizeof(char));

				if ( sta.channel == 0 ) {
					threadexitsall("REALLOC");
				}

				strcpy(sta.channel, "");
			}

			/* nick */

			if ( strcmp(cmd.command, "nick") == 0) {

				if ( nparams == 1 ) {

					sta.nick = realloc(sta.nick, sizeof(char)*(strlen(*(cmd.parameters))+1) );

					if ( sta.nick == 0 ) {
						threadexitsall("REALLOC");
					}

					strcpy(sta.nick, *(cmd.parameters) );

					fprint(*fp, "NICK %s\n", sta.nick);
				}
			}

			/* list */

			if ( strcmp(cmd.command, "list") == 0) {
				fprint(*fp, "LIST\n");
			}

			/* names */

			if ( strcmp(cmd.command, "names") == 0) {
				fprint(*fp, "NAMES\n");
			}

			/* time */

			if ( strcmp(cmd.command, "time") == 0) {
				fprint(*fp, "TIME\n");
			}

			/* info */

			if ( strcmp(cmd.command, "info") == 0) {
				fprint(*fp, "INFO\n");
			}

			/* away */

			if ( strcmp(cmd.command, "away") == 0) {

				message = malloc( sizeof(char) * 2 );

				if ( message == 0 ) {
					print("*** Memory allocation error\n");
					threadexitsall("MALLOC");
				}

				strcpy(message, "");

				/* user coming out of away state*/

				if ( nparams == 0 ) {
					fprint(*fp, "AWAY\n");
				}

				/* enter away state with away message */

				else {
						for (i = 0; i < cmd.n_params; i++) {

							temp = malloc( sizeof(char) * (strlen(*(cmd.parameters+i))+2) );

							if ( temp == 0 ) {
								print("*** Memory allocation error\n");
								threadexitsall("MALLOC");
							}

							sprint(temp, "%s ", *(cmd.parameters+i) );

							message = realloc(message, (sizeof(char)*(strlen(message)+strlen(temp)+2)) );

							if ( message == 0 ) {
								print("*** Memory allocation error\n");
								threadexitsall("REALLOC");
							}

							strcat(message, temp);

							free(temp);
						}

						fprint(*fp, "AWAY :%s\n", message);
				}

				free(message);
			}

			/* topic */

			if ( strcmp(cmd.command, "topic") == 0) {

				message = malloc( sizeof(char) * 2 );

				if ( message == 0 ) {
					print("*** Memory allocation error\n");
					threadexitsall("MALLOC");
				}

				strcpy(message, "");

				/* user just typed topic; print current topic */

				if ( cmd.n_params <= 0) {
					fprint(*fp, "TOPIC %s\n", sta.channel);
				}

				/* user actually wants to set a topic */

				else {

					/* user specified channel */

					if ( cmd.parameters[0][0] == '#') {
						for (i = 1; i < cmd.n_params; i++) {

							temp = malloc( sizeof(char)*(strlen(*(cmd.parameters+i))+2) );

							if ( temp == 0 ) {
								print("*** Memory allocation error\n");
								threadexitsall("MALLOC");
							}

							sprint(temp, "%s ", *(cmd.parameters+i) );

							message = realloc(message, (sizeof(char)*(strlen(message)+strlen(temp)+2)) );

							if ( message == 0 ) {
								print("*** Memory allocation error\n");
								threadexitsall("REALLOC");
							}
			
							strcat(message, temp);

							free(temp);
						}

					fprint(*fp, "TOPIC %s :%s\n", *(cmd.parameters), message);


					}

					/* user did not specify channel, use value of ourchan */

					else {
						for (i = 0; i < cmd.n_params; i++) {

							temp = malloc( sizeof(char)*(strlen(*(cmd.parameters+i))+2) );

							if ( temp == 0 ) {
								print("*** Memory allocation error\n");
								threadexitsall("MALLOC");
							}

							sprint(temp, "%s ", *(cmd.parameters+i) );

							message = realloc(message, (sizeof(char)*(strlen(message)+strlen(temp)+2)) );

							if ( message == 0 ) {
								print("*** Memory allocation error\n");
								threadexitsall("REALLOC");
							}

							strcat(message, temp);

							free(temp);
						}

						fprint(*fp, "TOPIC %s :%s\n", sta.channel, message);
					}
				}

				free(message);
			}

			/* mode */

			if ( strcmp(cmd.command, "mode") == 0) {

				/* two parameters (most user modes)*/

				if ( nparams == 2 ) {
					fprint(*fp, "MODE %s %s\n", *(cmd.parameters), *(cmd.parameters+1));
				}

				/* three parameters (some channel modes)*/

				else if ( nparams == 3 ) {
					fprint(*fp, "MODE %s %s %s\n", *(cmd.parameters), *(cmd.parameters+1), *(cmd.parameters+2) );
				}

			}

			/* invite */

			if ( strcmp(cmd.command, "invite") == 0) {
				if ( nparams == 1) {
					print("*** Inviting %s to channel %s\n", *(cmd.parameters), sta.channel);
					fprint(*fp, "INVITE %s %s\n", *(cmd.parameters), sta.channel);
				}
			}

			/* msg */

			if ( strcmp(cmd.command, "msg") == 0) {

				message = malloc( sizeof(char) * 2 );

				if ( message == 0 ) {
					print("*** Memory allocation error\n");
					threadexitsall("MALLOC");
				}

				strcpy(message, "");

				/* make sure the user actually entered a message otherwise do nothing */

				if ( cmd.n_params > 1) {
					for (i = 1; i < cmd.n_params; i++) {
					
						temp = malloc( sizeof(char)*(strlen(*(cmd.parameters+i))+2) );

						if ( temp == 0 ) {
							print("*** Memory allocation error\n");
							threadexitsall("MALLOC");
						}

						sprint(temp, "%s ", *(cmd.parameters+i));

						message = realloc(message, (sizeof(char)*(strlen(message)+strlen(temp)+2)) );

						if ( message == 0 ) {
							print("*** Memory allocation error\n");
							threadexitsall("REALLOC");
						}

						strcat(message, temp);

						free(temp);
					}

					print("-> *%s* %s\n", *(cmd.parameters), message);
					fprint(*fp, "PRIVMSG %s :%s\n", *(cmd.parameters), message);
				}

				free(message);
			}

			/* notice */

			if ( strcmp(cmd.command, "notice") == 0) {

				message = malloc( sizeof(char) * 2 );

				if ( message == 0 ) {
					print("*** Memory allocation error\n");
					threadexitsall("MALLOC");
				}

				strcpy(message, "");
				
				/* make sure the user actually entered a message otherwise do nothing */

				if ( cmd.n_params > 1) {
					for (i = 1; i < cmd.n_params; i++) {

						temp = malloc( sizeof(char)*(strlen(*(cmd.parameters+i))+2) );

						if ( temp == 0 ) {
							print("*** Memory allocation error\n");
							threadexitsall("MALLOC");
						}

						sprint(temp, "%s ", *(cmd.parameters+i) );

						message = realloc(message, (sizeof(char)*(strlen(message)+strlen(temp)+2)) );

						if ( message == 0 ) {
							print("*** Memory allocation error\n");
							threadexitsall("REALLOC");
						}

						strcat(message, temp);

						free(temp);
					}

					print("-> -%s- %s\n", *(cmd.parameters), message);
					fprint(*fp, "NOTICE %s :%s\n", *(cmd.parameters), message);
				}

				free(message);
			}


			/* kick */

			if ( strcmp(cmd.command, "kick") == 0) {
				if ( nparams == 1 ) {
					fprint(*fp, "KICK %s %s\n", sta.channel, *(cmd.parameters));
				}

				else if ( nparams == 2 ) {
					fprint(*fp, "KICK %s %s\n", *(cmd.parameters), *(cmd.parameters+1));
				}

				else {
					print("*** KICK not enough parameters\n");
				}
			}

			/* whois */

			if ( strcmp(cmd.command, "whois") == 0) {
				if ( nparams == 1) {
					fprint(*fp, "WHOIS %s\n", *(cmd.parameters));
				}

				else {
					print("*** WHOIS not enough parameters\n");
				}
			}

			/* whowas */

			if ( strcmp(cmd.command, "whowas") == 0) {
				if ( nparams == 1) {
					fprint(*fp, "WHOWAS %s\n", *(cmd.parameters));
				}

				else {
					print("*** WHOWAS not enough parameters\n");
				}
			}
		}

		/* free the buffer for the next input line */

		free(line);

		/* free the command struct for the next line of input */

		free_command_vars(&cmd);
	}

}
