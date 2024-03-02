#include "convertidor.h"

float * conversion_1_svc(inputs *argp, struct svc_req *rqstp){
	static float  result;

	result = (argp->numero);

	return &result;
}
