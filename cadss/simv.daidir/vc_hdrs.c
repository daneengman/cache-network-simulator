#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <dlfcn.h>
#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* VCS error reporting routine */
extern void vcsMsgReport1(const char *, const char *, int, void *, void*, const char *);

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

#ifndef __VCS_IMPORT_DPI_STUB_sv_socket_open
#define __VCS_IMPORT_DPI_STUB_sv_socket_open
__attribute__((weak)) int sv_socket_open(/* INPUT */int A_1)
{
    static int _vcs_dpi_stub_initialized_ = 0;
    static int (*_vcs_dpi_fp_)(/* INPUT */int A_1) = NULL;
    if (!_vcs_dpi_stub_initialized_) {
        _vcs_dpi_stub_initialized_ = 1;
        _vcs_dpi_fp_ = (int (*)(int A_1)) dlsym(RTLD_NEXT, "sv_socket_open");
    }
    if (_vcs_dpi_fp_) {
        return _vcs_dpi_fp_(A_1);
    } else {
        const char *fileName;
        int lineNumber;
        svGetCallerInfo(&fileName, &lineNumber);
        vcsMsgReport1("DPI-DIFNF", fileName, lineNumber, 0, 0, "sv_socket_open");
        return 0;
    }
}
#endif /* __VCS_IMPORT_DPI_STUB_sv_socket_open */

#ifndef __VCS_IMPORT_DPI_STUB_sv_socket_accept
#define __VCS_IMPORT_DPI_STUB_sv_socket_accept
__attribute__((weak)) int sv_socket_accept(/* INPUT */int A_1)
{
    static int _vcs_dpi_stub_initialized_ = 0;
    static int (*_vcs_dpi_fp_)(/* INPUT */int A_1) = NULL;
    if (!_vcs_dpi_stub_initialized_) {
        _vcs_dpi_stub_initialized_ = 1;
        _vcs_dpi_fp_ = (int (*)(int A_1)) dlsym(RTLD_NEXT, "sv_socket_accept");
    }
    if (_vcs_dpi_fp_) {
        return _vcs_dpi_fp_(A_1);
    } else {
        const char *fileName;
        int lineNumber;
        svGetCallerInfo(&fileName, &lineNumber);
        vcsMsgReport1("DPI-DIFNF", fileName, lineNumber, 0, 0, "sv_socket_accept");
        return 0;
    }
}
#endif /* __VCS_IMPORT_DPI_STUB_sv_socket_accept */

#ifndef __VCS_IMPORT_DPI_STUB_sv_socket_receive
#define __VCS_IMPORT_DPI_STUB_sv_socket_receive
__attribute__((weak)) int sv_socket_receive(/* INPUT */int A_1)
{
    static int _vcs_dpi_stub_initialized_ = 0;
    static int (*_vcs_dpi_fp_)(/* INPUT */int A_1) = NULL;
    if (!_vcs_dpi_stub_initialized_) {
        _vcs_dpi_stub_initialized_ = 1;
        _vcs_dpi_fp_ = (int (*)(int A_1)) dlsym(RTLD_NEXT, "sv_socket_receive");
    }
    if (_vcs_dpi_fp_) {
        return _vcs_dpi_fp_(A_1);
    } else {
        const char *fileName;
        int lineNumber;
        svGetCallerInfo(&fileName, &lineNumber);
        vcsMsgReport1("DPI-DIFNF", fileName, lineNumber, 0, 0, "sv_socket_receive");
        return 0;
    }
}
#endif /* __VCS_IMPORT_DPI_STUB_sv_socket_receive */

#ifndef __VCS_IMPORT_DPI_STUB_reply
#define __VCS_IMPORT_DPI_STUB_reply
__attribute__((weak)) int reply(/* INPUT */int A_1, /* INPUT */long long A_2)
{
    static int _vcs_dpi_stub_initialized_ = 0;
    static int (*_vcs_dpi_fp_)(/* INPUT */int A_1, /* INPUT */long long A_2) = NULL;
    if (!_vcs_dpi_stub_initialized_) {
        _vcs_dpi_stub_initialized_ = 1;
        _vcs_dpi_fp_ = (int (*)(int A_1, long long A_2)) dlsym(RTLD_NEXT, "reply");
    }
    if (_vcs_dpi_fp_) {
        return _vcs_dpi_fp_(A_1, A_2);
    } else {
        const char *fileName;
        int lineNumber;
        svGetCallerInfo(&fileName, &lineNumber);
        vcsMsgReport1("DPI-DIFNF", fileName, lineNumber, 0, 0, "reply");
        return 0;
    }
}
#endif /* __VCS_IMPORT_DPI_STUB_reply */

#ifndef __VCS_IMPORT_DPI_STUB_process_cache_transfer
#define __VCS_IMPORT_DPI_STUB_process_cache_transfer
__attribute__((weak)) int process_cache_transfer(/* OUTPUT */int *A_1, /* OUTPUT */long long *A_2, /* OUTPUT */int *A_3, /* OUTPUT */int *A_4)
{
    static int _vcs_dpi_stub_initialized_ = 0;
    static int (*_vcs_dpi_fp_)(/* OUTPUT */int *A_1, /* OUTPUT */long long *A_2, /* OUTPUT */int *A_3, /* OUTPUT */int *A_4) = NULL;
    if (!_vcs_dpi_stub_initialized_) {
        _vcs_dpi_stub_initialized_ = 1;
        _vcs_dpi_fp_ = (int (*)(int* A_1, long long* A_2, int* A_3, int* A_4)) dlsym(RTLD_NEXT, "process_cache_transfer");
    }
    if (_vcs_dpi_fp_) {
        return _vcs_dpi_fp_(A_1, A_2, A_3, A_4);
    } else {
        const char *fileName;
        int lineNumber;
        svGetCallerInfo(&fileName, &lineNumber);
        vcsMsgReport1("DPI-DIFNF", fileName, lineNumber, 0, 0, "process_cache_transfer");
        return 0;
    }
}
#endif /* __VCS_IMPORT_DPI_STUB_process_cache_transfer */


#ifdef __cplusplus
}
#endif

