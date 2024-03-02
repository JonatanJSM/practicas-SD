#include "convertidor.h"

void
convertidor_prog_1(char *host)
{
	CLIENT *clnt; // This is the client handle
	float  *result_1; // This is the return value of the function conversion_1_svc
	inputs  conversion_1_arg; // This is the struct defined in convertidor.x

#ifndef	DEBUG
	clnt = clnt_create (host, CONVERTIDOR_PROG, CONVERTIDOR_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = conversion_1(&conversion_1_arg, clnt);
	if (result_1 == (float *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	convertidor_prog_1 (host);
exit (0);
}
