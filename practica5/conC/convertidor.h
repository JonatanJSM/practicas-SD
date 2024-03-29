/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CONVERTIDOR_H_RPCGEN
#define _CONVERTIDOR_H_RPCGEN

#include <tirpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct inputs {
	float numero;
	char unidadMedida;
};
typedef struct inputs inputs;

#define CONVERTIDOR_PROG 0x2fffffff
#define CONVERTIDOR_VER 1

#if defined(__STDC__) || defined(__cplusplus)
#define conversion 1
extern  float * conversion_1(inputs *, CLIENT *);
extern  float * conversion_1_svc(inputs *, struct svc_req *);
extern int convertidor_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define conversion 1
extern  float * conversion_1();
extern  float * conversion_1_svc();
extern int convertidor_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_inputs (XDR *, inputs*);

#else /* K&R C */
extern bool_t xdr_inputs ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CONVERTIDOR_H_RPCGEN */
