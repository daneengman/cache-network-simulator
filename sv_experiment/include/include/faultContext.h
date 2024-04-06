/***************************************************************************
   SYNOPSYS CONFIDENTIAL -- This is an unpublished, proprietary work of
   Synopsys, Inc., and is fully protected under copyright and trade secret
   laws. You may not view, use, disclose, copy, or distribute this file or
   any information contained herein except pursuant to a valid written
   license from Synopsys.
 ***************************************************************************/

#ifndef FAULTCONTEXT_H
#define FAULTCONTEXT_H

/* CAF: contains the struct _faultContext_s.  This struct was defined both here
        and in verr.h. Putting this struct in scMsg leads to dup def errors
        in those places that didn't use verr for error messages but used the
        other definition of _faultContext_s
*/
struct _faultContext_s {
    char    *du;
    int     lineNo;
    char const *phase;
    int     unused_int[4];
    char    *unused_string[4];
};

#endif
