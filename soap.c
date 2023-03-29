/* See LICENSE file for copyright and license details. */
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
	const char *regex;
	const char *action;
} Pair;

#include "config.h"

#define FILE_URI "file://"
#define LEN(x)   (sizeof(x) / sizeof(*x))


int
main(int argc, char *argv[])
{
	struct stat s;
	regex_t regex;
	const char *act = NULL;
	const char *arg;
	size_t i, len = LEN(FILE_URI) - 1;
	char cmd[BUFSIZ];

	/* require at least one argument */
	if (argc < 2) {
		fprintf(stderr, "usage: %s <data>\n", argv[0]);
		return EXIT_FAILURE;
	}
	arg = argv[1];

	if (strstr(arg, FILE_URI) != NULL)
		arg += len;

	/* check if it is a directory */
	if ((!lstat(((char *)arg) + len, &s)
		|| !lstat(arg, &s)) && S_ISDIR(s.st_mode))
		act = dircmd;

	if (setenv("SOAP", arg, 1) < 0) {
		fprintf(stderr, "setenv error\n");
		return EXIT_FAILURE;
	}

	if (act) /* if opening a directory */
		goto run;

	/* check regex and launch action if it matches the argument */
	for (i = 0; i < LEN(pairs); i++) {
		if (regcomp(&regex, pairs[i].regex, REG_EXTENDED|REG_NOSUB)) {
			fprintf(stderr, "invalid regex: %s\n", pairs[i].regex);
			break;
		}
		if (!regexec(&regex, arg, 0, NULL, 0)) {
			act = pairs[i].action;
			regfree(&regex);
			goto run;
		}
		regfree(&regex);
	}
	/* fallback to xdg-open if no pair matches */
	act = FALLBACK;

run:
	snprintf(cmd, sizeof(cmd), act, getenv("SOAP"));
	system(cmd);
	return EXIT_SUCCESS;
}
