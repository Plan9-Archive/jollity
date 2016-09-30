/* jollity irc client for plan 9 by sean caron (scaron@umich.edu) */

#include "main.h"

/* network input handler thread */

void network_input_thread(void *filep) {

	int cmdnum, *fp;
	char *line;
	struct message msg;

	fp = filep;

	/* loop forever getting input from the network */

	while (1) {

		initialize_message_struct(&msg);

		/* get a line of input from the network */

		read_line_net(*fp, &line);

		stripcr(line);

		//printf("rcvd <%s>\n", line );

		/* parse it out */

		parse_network_input(line, &msg);

/*
		printf("msg.prefix is <%s>\n", msg.prefix );

		printf("msg.command is <%s>\n", msg.command);

		printf("n_params = %d\n", msg.n_params );

		for ( i = 0; i < msg.n_params; i++ ) {

			printf("<%s> ", msg.parameters[i] );

		}

		printf("\n");
*/










		/* handle various commands */

		/* PING */

		if (strcmp(msg.command, "PING") == 0) {
			c_ping(msg, *fp);
		}

		/* PRIVMSG */

		else if (strcmp(msg.command, "PRIVMSG") == 0) {

			/* CTCP */

			if (msg.parameters[1][1] == 0x1) {
				c_ctcp(msg, *fp);
			}

			/* regular PRIVMSG */

			else {
				c_privmsg(msg, *fp);
			}
		}

		/* JOIN */

		else if (strcmp(msg.command, "JOIN") == 0) {
			c_join(msg, *fp);
		}

		/* PART */

		else if (strcmp(msg.command, "PART") == 0) {
			c_part(msg, *fp);
		}

		/* TOPIC */

		else if (strcmp(msg.command, "TOPIC") == 0) {
			c_topic(msg, *fp, 1);
		}

		/* MODE */

		else if ( strcmp(msg.command, "MODE") == 0) {
			c_mode(msg,*fp);
		}

		/* QUIT */

		else if ( strcmp(msg.command, "QUIT") == 0) {
			c_quit(msg, *fp);
		}

		/* INVITE */

		else if ( strcmp(msg.command, "INVITE") == 0) {
			c_invite(msg, *fp);
		}

		/* KICK */

		else if ( strcmp(msg.command, "KICK") == 0) {
			c_kick(msg, *fp);
		}

		/* NOTICE */

		else if ( strcmp(msg.command, "NOTICE") == 0) {
			c_notice(msg, *fp);
		}

		/* NICK */

		else if ( strcmp(msg.command, "NICK") == 0) {
			c_nick(msg, *fp);
		}

		/* numeric commands */

		else if ( atoi(msg.command) != 0) {

			cmdnum = atoi(msg.command);

			/* server messages */

			if ( (cmdnum == 001) || (cmdnum == 002) || (cmdnum == 003) || (cmdnum == 020) ||
				(cmdnum == 251) || (cmdnum == 255) || (cmdnum == 265) || (cmdnum == 266) ||
				(cmdnum == 422) || (cmdnum == 372) || (cmdnum == 375) || (cmdnum == 376) ||
				(cmdnum == 305) || (cmdnum == 306) || (cmdnum == 371) || (cmdnum == 391) ||
				(cmdnum == 374) ) {

				c_srvmsg(msg, *fp);
			}

			/* server modes */

			if ( cmdnum == 004 ) {
				c_srvmodes(msg, *fp);
			}

			/* supported by server */

			if ( cmdnum == 005 ) {
				c_supported(msg, *fp);
			}

			/* unique id */

			if ( cmdnum == 042 ) {
				c_unique(msg, *fp);
			}

			/* number of channels */

			if ( cmdnum == 254 ) {
				c_numchans(msg, *fp);
			}

			/* channel topic */

			if ( cmdnum == 332 ) {
				c_topic(msg, *fp, 0);
			}

			/* channel list */

			if ( cmdnum == 322) {
				c_list(msg, *fp);
			}

			/* user list */

			if ( cmdnum == 353) {
				c_wreply(msg, *fp);
			}

			/* invite only */

			if ( cmdnum == 473) {
				print("*** Cannot join channel %s (invite only channel)\n", msg.parameters[1]);
			}

			/* banned */

			if ( cmdnum == 474) {
				print("*** Cannot join channel %s (banned)\n", msg.parameters[1]);
			}

			/* nick already in use */

			if ( cmdnum == 433) {
				print("*** Nickname %s already in use\n", msg.parameters[1]);
			}

			/* channel is full */

			if ( cmdnum == 471) {
				print("*** Cannot join channel %s (channel is full)\n", msg.parameters[1]);
			}

			/* bad channel key */

			if ( cmdnum == 475) {
				print("*** Cannot join channel %s (bad channel key)\n", msg.parameters[1]);
			}

			/* key already set */

			if ( cmdnum == 467) {
				print("*** Cannot set key for channel %s (key already set)\n", msg.parameters[1]);
			}

			/* not channel operator */

			if ( cmdnum == 482 ) {
				print("*** Cannot perform action for channel %s (not channel operator)\n", msg.parameters[1]);
			}

			/* whois response */

			if ( cmdnum == 311) {
				c_whoisuser(msg, *fp, 0);
			}

			/* whois response */

			if ( cmdnum == 319) {
				c_whoischannels(msg, *fp);
			}

			/* whois and whowas response */

			if ( cmdnum == 312) {
				c_whoisserver(msg, *fp);
			}

			/* whowas response */

			if ( cmdnum == 314) {
				c_whoisuser(msg, *fp, 1);
			}

			/* no such nick or channel  */

			if ( cmdnum == 401) {
				print("*** %s: No such nick or channel\n", msg.parameters[1]);
			}

			/* was no such nickname */

			if ( cmdnum == 406) {
				print("*** %s: There was no such nickname\n", msg.parameters[1]);
			}

			/* no topic is set */

			if ( cmdnum == 331) {
				print("*** %s: No topic is set\n", msg.parameters[1]);
			}

			/* away response */

			if ( cmdnum == 301) {
				c_awayresp(msg, *fp);
			}

		}

		/* free up the buffer for the next line of input */

		free(line);

		/* free up the message struct for the next line of input */

		free_message_vars(&msg);
	}

}
