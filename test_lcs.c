#include "udf_lcs.h"
#include <stdio.h>
#include <string.h>

int main(char argc, char **argv) {

	if (argc != 4) {
		printf("3 parameters required\n");
		return(1);
	}

	char match[LCS_MAX];
	int m, i, n;

	n = atoi(argv[3]);
	if (n < 1) {
		printf("Invalid parameter: '%s'\n", argv[3]);
		return(2);
	}

	printf("Test %d time(s)\n\n", n);

	for (i=0; i<n; ++i) {
		m = __lcs(argv[1], argv[2], strlen(argv[1]), strlen(argv[2]), match);
	}

	match[m] = '\0';
	printf("Match count: %d\nMatch string: '%s'\n", m, match);
}
