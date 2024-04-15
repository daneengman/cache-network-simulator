#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <dlfcn.h>
#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _VC_TYPES_
#define _VC_TYPES_
/* common definitions shared with DirectC.h */

typedef unsigned int U;
typedef unsigned char UB;
typedef unsigned char scalar;
typedef struct { U c; U d;} vec32;

#define scalar_0 0
#define scalar_1 1
#define scalar_z 2
#define scalar_x 3

extern long long int ConvUP2LLI(U* a);
extern void ConvLLI2UP(long long int a1, U* a2);
extern long long int GetLLIresult();
extern void StoreLLIresult(const unsigned int* data);
typedef struct VeriC_Descriptor *vc_handle;

#ifndef SV_3_COMPATIBILITY
#define SV_STRING const char*
#else
#define SV_STRING char*
#endif

#endif /* _VC_TYPES_ */


 extern int sv_socket_open(/* INPUT */int port);

 extern int sv_socket_accept(/* INPUT */int socket_fd);

 extern int sv_socket_receive(/* INPUT */int socket_fd, const /* INPUT */svOpenArrayHandle buffer, /* INPUT */int size);

 extern int sv_socket_send(/* INPUT */int socket_fd, const /* INPUT */svOpenArrayHandle buffer, /* INPUT */int size);

 extern int ack(/* INPUT */int countdown);

 extern int process_cache_transfer(/* OUTPUT */int *brt, /* OUTPUT */long long *addr, /* OUTPUT */int *procNumSource, /* OUTPUT */int *procNumDest);

#ifdef __cplusplus
}
#endif

