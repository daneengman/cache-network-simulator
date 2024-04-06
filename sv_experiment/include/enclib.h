/*
 *
 *  FileName: enclib.h
 *
 *  Facility: VCS simulation
 *
 *  Functional Description:
 *      Prototypes for the public source protection algorithm routines.
 *
 *      Man pages are in <vcs_installation_dir/platform>/man.  Add this
 *      path to your MANPATH env var and do "man SrcProtection" for an
 *      overview and a list of the available routines.
 *
 *  Author:
 *      Matthew Chapman, Feb 1996
 *
 *  Modified by:
 *  Who         When            What
 *  M.Chapman   15-Feb-96       Original Coding.
 *  M.Chapman   05-Jan-98       Added VCS_ARGS to support non-ansi compilers
 *
 *  Copyright (c) 1996 by Viewlogic Systems, Inc.
 *
 */

#ifndef ENCLIB_H
#define ENCLIB_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef VCS_ARGS                /* support for non-ansi compilers */
# define VCS_ARGS_DEFINED_HERE
# if defined(__STDC__) || defined(__cplusplus) || defined(__osf__)
#  define VCS_ARGS(p) p
# else
#  define VCS_ARGS(p) ()
# endif
#endif /* VCS_ARGS */

typedef struct vcsSpState *vcsSpStateID;    /* struct defined in enclib.c */

extern vcsSpStateID vcsSpInitialize VCS_ARGS((void));
extern void vcsSpClose          VCS_ARGS((vcsSpStateID esp));
extern void vcsSpSetFilePtr     VCS_ARGS((vcsSpStateID esp, FILE *fp));
extern FILE *vcsSpGetFilePtr        VCS_ARGS((vcsSpStateID esp));
extern int vcsSpEncoding        VCS_ARGS((vcsSpStateID esp));
extern int vcsSpEncodeOn        VCS_ARGS((vcsSpStateID esp));
extern int vcsSpEncodeOff       VCS_ARGS((vcsSpStateID esp));
extern int vcsSpWriteChar       VCS_ARGS((vcsSpStateID esp, char c));
extern int vcsSpWriteString     VCS_ARGS((vcsSpStateID esp, char *s));
extern int vcsSpStarFixup       VCS_ARGS((vcsSpStateID esp));
extern int vcsSpError           VCS_ARGS((vcsSpStateID esp));
extern char *vcsSpGetErrorStr       VCS_ARGS((vcsSpStateID esp));
extern void vcsSpSetPliProtectionFlag   VCS_ARGS((vcsSpStateID esp, int enable));
extern void vcsSpSetDbgPartProtectFlag  VCS_ARGS((vcsSpStateID esp, int enable));
extern void vcsSpSetAutoBodyProtectFlag  VCS_ARGS((vcsSpStateID esp, int enable));
extern void vcsSpSetVipProtectFlag VCS_ARGS((vcsSpStateID exp, int enable));
extern void vcsSpSetLibLicenseCode  VCS_ARGS((vcsSpStateID esp, unsigned int code));
extern void vcsSpClearError     VCS_ARGS((vcsSpStateID esp));
extern vcsSpStateID vcsSpOvaDecodeLine  VCS_ARGS((vcsSpStateID esp, char *line));
extern void vcsSpSetDisplayMsgFlag      VCS_ARGS((vcsSpStateID esp, int enable));
extern int vcsSpGetDisplayMsgFlag       VCS_ARGS((vcsSpStateID esp));

#ifdef VCS_ARGS_DEFINED_HERE
#undef VCS_ARGS_DEFINED_HERE
#undef VCS_ARGS
#endif

#ifdef __cplusplus
} // extern "C"
#endif
#endif /* ENCLIB_H */
