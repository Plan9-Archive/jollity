/* jollity irc client by sean caron (scaron@umich.edu) */

#include "main.h"

/* strip carriage return from a string */

void stripcr(char *string) {

	int  i;

	for ( i = 0; i < strlen(string); i++) {
		if (string[i] == 13) {
			//string[i] = '\n';
			//string[i+1] = '\0';
			string[i] = '\0';
		}
	}

	return;
}

/* strip newline from a string */

void stripnl(char *string) {

	int i;

	for ( i = 0; i < strlen(string); i++) {
		if (string[i] == '\n') {
			string[i] = '\0';
		}
	}

	return;
}

/* shift a string one character to the left to remove leading colon */

void shiftl(char *string) {

	int i;

	for ( i = 1; i < strlen(string); i++) {
		string[i-1] = string[i];
	}

	string[i-1] = '\0';

	return;
}

/* strip leading and trailing 0x1 from a CTCP string */

void stripctcp(char *string) {

	int i;

	for ( i = 1; i < strlen(string); i++) {
		string[i-1] = string[i];
	}

	string[i-2] = '\0';

	return;
}

/* generate a timestamp for messages */

void timestamp(char *stamp) {

	Tm *ti;

	ti = localtime(time(0));

	sprint(stamp, "%02d:%02d", ti->hour, ti->min);

	return;
}
