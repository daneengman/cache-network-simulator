/****************************************************************************
 *
 * Copyright (C) 2000 Synopsys, Inc. All Rights Reserved.
 *
 * DirectC.h: Release 10
 *
 * This file contains the constant definitions, structure definitions, and
 * routine declarations used by the VeriC/DirectC abstract interface.
 *
 * The file should be included with all C routines that use the DirectC
 * abstract interface routines.
 *
 ****************************************************************************/

/* $Revision$ */

#ifndef DIRECTC_H
#define DIRECTC_H

/*---------------------------------------------------------------------------*/
/*------------------------------- definitions -------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(__cplusplus)
extern "C" {
#else /* unwanted with C++ */

typedef int bool;

#endif

/* the following definitions should be eventually put into separate .h file */
#ifndef _VC_TYPES_
#define _VC_TYPES_
/* common definitions */

typedef unsigned int U;
typedef unsigned char UB;
typedef unsigned char scalar;
typedef struct { U c; U d;} vec32;

typedef struct VeriC_Descriptor *vc_handle;

#define scalar_0    0
#define scalar_1    1
#define scalar_z    2
#define scalar_x    3

/* end of common definitions */
#endif /* _VC_TYPES_ */

extern int flibNonStdMem;

extern bool vc_isScalar(vc_handle);
extern bool vc_isVector(vc_handle);
extern bool vc_isMemory(vc_handle);
extern bool vc_is4state(vc_handle);
extern bool vc_is2state(vc_handle);
extern bool vc_is4stVector(vc_handle);
extern bool vc_is2stVector(vc_handle);

extern int vc_width(vc_handle); /* 1 for scalars; width of a vector or an element of a memory */
extern int vc_arraySize(vc_handle); /* total number of elements; 0 for non-arrays */


/* for any scalar (2- or 4-state); no x/z checks for 2-state. */
extern scalar vc_getScalar(vc_handle);      /* for 2- and 4-state scalars */
extern void   vc_putScalar(vc_handle, scalar);  /* for 2- and 4-state scalars; */

extern void   vc_FillWithScalar(vc_handle, scalar); /* for any object: 2- or 4-state, scalar, vector, memory */

extern char vc_toChar(vc_handle);   /* Return a character: 0/1/x/z */

extern int vc_toInteger(vc_handle); /* for 2-state scalars and short vectors */
/* 0 (and warning) for 4-state or vector longer than 32 bits */
/* No unsigned-->signed conversion will be performed! */

/* Conversion to strings; any scalar or vector.              */
/* String will be placed in a temporary buffer and should be */
/* preserved if not used immediately.                        */

extern char *vc_argInfo(vc_handle); /* Return a string showing the definition of the actual parameter */

extern char *vc_toString(vc_handle);    /* return string of 0/1/x/z */
extern char *vc_toStringF(vc_handle, char); /* char format ('b', 'o', 'd', 'x') */

extern void   vc_putReal(vc_handle, double);    /* for real */
extern double vc_getReal(vc_handle);

/* conversion from strings, 2- and 4-state vectors */
extern void vc_putValue(vc_handle, char *); /* value represented as a string  of 0/1/x/z */
extern void vc_putValueF(vc_handle, char *, char);  /* char format: 'b', 'o', 'd', 'x' */

extern void  vc_putPointer(vc_handle, void*);   /* for 'pointer' or 'string' */
extern void *vc_getPointer(vc_handle);      /* generic pointer */

extern void vc_StringToVector(char *, vc_handle);   /* converts and assigns a C string to a vector */


/* Conversion from vectors interpreted as strings to C strings; */
/* resulting string is stored in user allocated memory */
extern void vc_VectorToString(vc_handle, char *);   /* converts a vector to a C string */

extern void vc_ConvertToString(vec32 *, int, char *);   /* converts a vector of a given width to a C string */
/* Similar to vc_VectorToString but takes explicit reference and size of vector */
/* May be called directly from Verilog code if declared as follows: */
/*   extern "C" void vc_ConvertToString(reg [], int, string);   */



/* Uninterpreted 32 bits with no implied semantics.   */
/* No signed-->unsigned conversion will be performed! */

extern int  vc_getInteger(vc_handle);       /* same as vc_toInteger(). */
extern void vc_putInteger(vc_handle, int);  /* for any scalars and short 2-state vectors */

/* return a pointer to a vector or NULL if not a vector of a desired kind */
extern vec32 *vc_4stVectorRef(vc_handle);   /* for 4 state vectors */
extern U     *vc_2stVectorRef(vc_handle);   /* for 2 state vectors; NULL for short input vectors */


/* Copy a Verilog vector to or from user's array (as in LRM, p.340).               */
/* The array of vec32 (for 4-state) or of U (for 2-state) shall contain an element */
/* for every 32 bits of the vector, plus an element for any remaining bits.        */
/* The second param. must be an array of the appropriate length.                   */
/* The number of elements to be copied depends on the size of parameter.           */

/* for 4-state vector */
extern void vc_get4stVector(vc_handle, vec32 *);    /* copy argument's value into the array */
extern void vc_put4stVector(vc_handle, vec32 *);    /* copy the array into the argument. */

/* for 2-state vector */
extern void vc_get2stVector(vc_handle, U *);    /* copy argument's value into the array */
extern void vc_put2stVector(vc_handle, U *);    /* copy the array into the argument. */



/* =========== for arrays (aka 'memories') =========== */
/* Arrays are assumed to be indexed from 0.            */

extern UB *vc_MemoryRef(vc_handle); /* a pointer to the memory; NULL if not a memory */
extern UB *vc_MemoryElemRef(vc_handle, U indx); /* a pointer to an element of memory; */
/* NULL if index outside the range or not a memory */

extern scalar vc_getMemoryScalar(vc_handle, U indx);        /* for 2- and 4-state scalars */
extern void   vc_putMemoryScalar(vc_handle, U indx, scalar);    /* for 2- and 4-state scalars */

extern int    vc_getMemoryInteger(vc_handle, U indx);   /* for short vectors only; ignoring control bits */
extern void   vc_putMemoryInteger(vc_handle, U indx, int);  /* for short vectors only */

/* copy a Verilog value between memory's element and user's array (as in LRM, p.340) */
extern void   vc_get4stMemoryVector(vc_handle, U indx, vec32 *);    /* copy one element into the array */
extern void   vc_put4stMemoryVector(vc_handle, U indx, vec32 *);    /* copy the array into an element. */

extern void   vc_put2stMemoryVector(vc_handle, U indx, U *);    /* for 2-state values */
extern void   vc_get2stMemoryVector(vc_handle, U indx, U *);    /* for 2-state */

/* conversion from strings */
extern void   vc_putMemoryValue(vc_handle, U indx, char *); /* value represented as a string  of 0/1/x/z */
extern void   vc_putMemoryValueF(vc_handle, U indx, char *, char);  /* format: 'b', 'o', 'd', 'x' */

/* conversion to strings; */
extern char  *vc_MemoryString(vc_handle, U indx);   /* return string of 0/1/x/z */
extern char  *vc_MemoryStringF(vc_handle, U indx, char);    /* format: 'b', 'o', 'd', 'x' */

/* For MDA (Multi Dimensional Arrrays) and abstract access mode: */

/* Return index in a linearized array or -1 if indices outside the range or not a memory */
extern int vc_Index(vc_handle h, U indx1, U indx2, ...);
/* specialized versions for 2- and 3-dimensional arrays: */
extern int vc_Index2(vc_handle h, U indx1, U indx2);
extern int vc_Index3(vc_handle h, U indx1, U indx2, U indx3);

extern U vc_mdaSize(vc_handle, U n); /* number of values of n-th index, n=1,2,..,  */
/* dimension (i.e. no. of indices) for n=0,  or 0 for non-arrays */

/* For arrays (including Multi Dimensional Arrrays) and abstract access mode: */

/* Return a pointer to an element of the array or NULL if index outside the range or null pointer */
extern UB *vc_arrayElemRef(UB *mem_ptr, U indx1, ...);
/* specialized versions for 1-, 2- and 3-dimensional arrays: */
extern UB *vc_arrayElemRef1(UB *mem_ptr, U indx1);
extern UB *vc_arrayElemRef2(UB *mem_ptr, U indx1, U indx2);
extern UB *vc_arrayElemRef3(UB *mem_ptr, U indx1, U indx2, U indx3);

extern U vc_getSize(UB *mem_ptr, U n); /* number of values of n-th index, n=1,2,..,  */
/* dimension (i.e. no. of indices) for n=0,  or 0 for null pointer */

extern void ConvLLI2UP(long long int lli, U *dest);
extern long long int ConvUP2LLI(U* src);
extern long long int GetLLIresult();
extern void StoreLLIresult(const unsigned int* data);

/* For passing shortreal (=float) as a 32-bit value */
typedef union { float f; U u; } FLOAT_U_UNION;

void vc_real_product(double *pres, double *arr1, double *arr2, int from, int to);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif /* DIRECTC_H */
