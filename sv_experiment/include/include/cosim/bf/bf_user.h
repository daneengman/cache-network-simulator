// This may look like C code, but it is really -*- C++ -*-
// 
// bf_user.h -- 
// Copyright Synopsys 2002-2009
// Author          : Ric Hilderink
// Created On      : Tue Aug 20 16:17:49 2002
// Last update     : Mon Apr 20 2009


#ifndef _bf_user_h_
#define _bf_user_h_


//----------------------------------------------------------------------------
// Should acc_user.h be used or not?
//
// Header file acc_user.h contains many #defines and typedefs that 
// may conflict with C++ classes. There are different options
// how to deal with these conflicts:
//
// (0) Use a minimal subset of definitions from acc_user.h:
// Usage: syscan myfile.cpp:myfile -cflags -DSYSC_ACC_USER=0
//
// Very few #defines + typedefs from acc_user.h are used, therefore
// the potential for clashes with C++ classes is very low. Note 
// that statement "#include <acc_user.h>" in your source code is 
// not possible, it would create a compile error.
//
// (1: use entire acc_user.h except the most risky #defines
// Usage: syscan myfile.cpp:myfile -cflags -DSYSC_ACC_USER=1
// 
// If the user code does not include <acc_user.h>, then it is
// guarantied that the following macros are NOT defined:
//   bool, true, TRUE, false, FALSE, global, exfunc, local, null
// If the user code includes <acc_user.h>, then the macros may or
// may not be defined depending on the order of include statements.
//
// (2, Default)) Use acc_user.h exactly as is:`
// Usage: syscan myfile.cpp:myfile
//  or    syscan myfile.cpp:myfile -cflags -DSYSC_ACC_USER=2
//
// You can use "#include <acc_user.h>" at any place in your source
// code. All definitions inside acc_user.h are visible including
// macros true, TRUE, ...
//----------------------------------------------------------------------------

#if !defined(SYSC_ACC_USER) || SYSC_ACC_USER == 1 || SYSC_ACC_USER == 2

#include <acc_user.h>

#if SYSC_ACC_USER == 1
// use model 1: use acc_user.h  but undef the most risky #defines
#undef bool 
#undef true 
#undef TRUE 
#undef false
#undef FALSE
#undef global
#undef exfunc
#undef local
#undef null 
#else
// use model 2 (default): use acc_user.h as is
#endif

 
#else 
// use model 0: Use only a minimal subset of definitions from acc_user.h

typedef int *handle; // handle defined in acc_user.h

#ifndef VPI_USER_H
// vhdl-only: define the vpi-types used here
#endif

#ifndef VHPI_H
// verilog-only: define the vhpi-types used here
typedef unsigned long *vhpiHandleT;
typedef enum {
  vhpiEnumVal,
  vhpiEnumVecVal,
  vhpiIntVal,
  vhpiIntVecVal,
  vhpiRealVal,
  vhpiRealVecVal,
  vhpiPhysVal,
  vhpiPhysVecVal,
  vhpiCharVal,
  vhpiStrVal,
  vhpiObjTypeVal,
  vhpiPtrVal,                /* for access type variables */
  vhpiPtrVecVal,             /* the ptr formats will have different */
                             /* positional values after ballot */
  vhpiRawData,

  /* The following format value is for internal use by the VHPI
     implementation of Synopsys */

  vhpiInvalidFormat

} vhpiValueFormatT;
typedef unsigned vhpiEnumT;
typedef int vhpiIntT;
typedef double vhpiRealT;
#ifdef _MSC_VER
typedef __int64 vhpiPhysT, vhpiTimeT;
#else
typedef long long vhpiPhysT, vhpiTimeT;
#endif

typedef struct {
  vhpiValueFormatT format;   /* value format */
  vhpiIntT bufSize;          /* size of the vector */
  vhpiIntT numscalars;       /* the number of scalar represented by the value */
  vhpiIntT unit;             /* physical unit. 0 for base unit */
  union {
    vhpiEnumT enumval, *enums; /* enumeration value(s) */
    vhpiIntT  intg, *intgs;    /* integer value(s) */
    vhpiRealT real, *reals;    /* real value(s) */
    vhpiPhysT phys, *physs;    /* physical value(s) */
    char      ch, *str;        /* character or string formatting */
    void      *ptr, **ptrs;         /* values of access types and raw data */
  } value;
} vhpiValueT;
#endif


/*--------------------- data structure of vector values ---------------------*/
typedef struct t_acc_vecval
{
    int aval;
    int bval;
} s_acc_vecval, *p_acc_vecval;

#define accBinStrVal                1
#define accVectorVal               10

/*------ data structure used with acc_set_value() and acc_fetch_value() -----*/
typedef struct t_setval_value
{
    int format;
    union {
        char *str;
        int scalar;
        int integer;
        double real;
        p_acc_vecval vector;
    } value;
} s_setval_value, *p_setval_value, s_acc_value, *p_acc_value;


extern "C" char *acc_fetch_fullname(handle);
extern "C" int  acc_fetch_size(handle);
extern "C" char *acc_fetch_value(handle, char *, t_setval_value *);
extern "C" char *acc_fetch_type_str(int);
extern "C" int acc_fetch_type(handle);


#endif   // #if !defined(SYSC_ACC_USER) || SYSC_ACC_USER == 1 || SYSC_ACC_USER == 2


extern "C" int bfvGetTime(unsigned int *);

extern "C" int scEvent;
extern "C" int vcsEvent;



#endif
