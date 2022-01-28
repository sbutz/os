#include <stdio.h>

#include <rpc/rpc.h>
#include "date.h"

int main(int argc, char *argv[])
{
	long *lresult; /* return from bin_date */
	char **sresult; /* return from str_date */
	CLIENT *cl;
	char *server = "localhost";

	if (argc != 1) {
		fprintf(stderr, "usage: %s\n", argv[0]);
		return 1;
	}

	cl = clnt_create(server, DATE_PROG, DATE_VERS, "tcp");

	/* call the procedure bin_date */
	if ((lresult = bin_date_1(NULL, cl)) == NULL)
	{
		clnt_perror(cl, server);
		return 1;
	}
	printf("time on %s is %ld\n", server, *lresult);

	/* convert the result to a date string */
	if ((sresult = str_date_1(lresult, cl)) == NULL)
	{
		clnt_perror(cl, server);
		return 1;
	}
	printf("date on is %s", *sresult);

	return 0;
}
