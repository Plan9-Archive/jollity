/* jollity irc client for plan 9 by sean caron (scaron@umich.edu */

#include "main.h"

/* read in a line from the specified file descriptor to the specified buffer */

int read_line_user(char **ptr) {

	int len = 1;

	*ptr = malloc(sizeof(char));

	while (1) {

		*(*ptr+len-1) = getchar();

		*ptr = realloc(*ptr, (len+1)*sizeof(char));

		if ( *ptr == 0 ) {
			exits("REALLOC");
		}

		if ( *(*ptr+len-1) == 10 ) {
			*(*ptr+len) = '\0';
			break;
		}

		len = len + 1;

	}

	return len;
}
