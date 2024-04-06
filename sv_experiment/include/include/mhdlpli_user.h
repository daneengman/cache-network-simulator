#ifndef MHDLPLI_USER_H
#define MHDLPLI_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __MHDL_HANDLE__
#define __MHDL_HANDLE__
typedef void * mhdlHandle;
#endif
typedef void * mhdlIterator;

typedef enum {
    UNKNOWN_OBJECT,
    VERILOG_OBJECT,
    VHDL_OBJECT
} mhdlObjectType;

typedef enum {
    mhdlShowAll,
    mhdlSuppressErr,
    mhdlSuppressWarn,
    mhdlSuppressAll
}configErr;


/* mhdlGetObjectByName
   This function gets a handle referenced by a pathname (absolute or
   relative) where:
         pathname   = absolute hierarchical path or relative to parent
                      scope handle,
         handle     = 0 for absolute paths or parent handle for
                      relative paths,
         delimiter  = path separator ('/' or '.'),
         *objType   = type of the object is filled in and returned.

   The API will fill *objType to VERILOG_OBJECT if it is a verilog
   object, VHDL_OBJECT if it's a VHDL object else UNKNOWN_OBJECT. */

mhdlHandle mhdlGetObjectByName(char *pathname, mhdlHandle parent,
                               char delimiter, mhdlObjectType *objType);

/* mhdlGetAccHandle
   This function returns the acc handle given mhdlHandle of a verilog
   object. A null value will be returned if the object is not a verilog
   object.  */

handle mhdlGetAccHandle(mhdlHandle objHandle);

/* mhdlGetVhpiHandle
   This function returns the corresponding vhpi handle given mhdlHandle
   of a VHDL object. A null value will be returned if the object is not
   a VHDL object.  */

vhpiHandleT mhdlGetVhpiHandle(mhdlHandle objHandle);

/* mhdlGetFullPathname
   This function returns a character string containing the full
   hierarchical name (encompassing VHDL and verilog design portions) of
   the mhdlHandle passed in. The delimiter is as specified. The
   character string is a static buffer and the contents should be
   copied.  */

char * mhdlGetFullPathname(mhdlHandle objHandle, char delimiter);

char getCurDelimiter();

/* This function returns a character string containing the name
   of the mhdlHandle passed in. The character string should be copied.
   For a boundary instance, this givens the correct instance name
   of the region.
*/

char * mhdlGetName(mhdlHandle objHandle);

/* mhdlGetChildIterator
   This function iterates over all children of a mhdlHandle - both VHDL
   and Verilog children. For example, if the mhdlHandle of a Verilog
   object is passed in, the iterator will iterate over all the verilog
   children (if any) and also all the vhdl children (if any). This
   should be used instead of vhpi or acc iterators to detect foreign
   children.  Use mhdlScan to go through the contents of the iterator.  */

mhdlIterator mhdlGetChildIterator(mhdlHandle objHandle);

/* mhdlScan
   This function scans through a iterator. The iterator has to be
   created by a call to the function mhdlGetChildIterator. Every call to
   mhdlScan returns a mhdlHandle and the relevant object type is filled in
   in *objType.  The termination is indicated by a null return value.  */

mhdlHandle mhdlScan(mhdlIterator iterator, mhdlObjectType *objType);

/* mhdlGetParent
   This function gets the parent of object regardless of whether the
   parent is a VHDL or Verilog object.  For example, if a verilog
   object is instantiated under a vhdl object and the verilog passed as
   a parameter to mhdlGetParent, then the vhdl object is returned. This
   should be used instead of acc_handle_parent or
   vhpi_get(vhpiParent,..).  If the parent of an object is in the same
   language, it will be returned. The type of the parent is filled in
   in *objType.  */

mhdlHandle mhdlGetParent(mhdlHandle objectHandle, mhdlObjectType *objType);


/* mhdlGetDesignTop
   This function returns the root of design hierarchy. For VHDL top
   designs, this is the top entity and for Verilog top designs, this is
   the first top module. Having known the top design language, regular
   acc_next_topmod or vhpi_iterator can be used. The paramter objType
   is filled in with the type of the object - VERILOG_OBJECT or
   VHDL_OBJECT.  If there is an error, *objType will be filled in with
   UNKNOWN_OBJECT.  */

mhdlHandle mhdlGetDesignTop(mhdlObjectType *objType);

/* mhdlGetHandleFromAccHandle
   This function returns the mhdl handle given a ACC handle */

mhdlHandle mhdlGetHandleFromAccHandle(handle accHandle);

/* mhdlGetHandleFromVhpiHandle
   This function returns the mhdl handle given a vhpi handle */

mhdlHandle mhdlGetHandleFromVhpiHandle(vhpiHandleT vhpiHandle);

/* mhdlConfigureError
   This function can be used to configure the error mechanism to
   suppress errors and/or warnings. The default value is mhdlShowAll.  */

void mhdlConfigureError(configErr errSetting);


/* Wrapper around mhdlConfigureError for hdl_xmr call.
 * This is defined to support hdl_xmr calls in pure
 * verilog flow.
 */
void mhdlConfigureErrorForHdlXmr();

/* mhdlGetVhpiTime
   This function returns the current simulation time in vhpi format. Note
   the time extracted by vhpi calls can sometimes be different from the
   actual simulation time in mixed designs.  */

vhpiTimeT mhdlGetVhpiTime();


/* mhdlGetAccTime
   This function returns the curent simulation time in acc format. Note the
   time extracted by acc calls can sometimes be differenct from the actual
   simulation time in mixed designs. */

p_setval_delay mhdlGetAccTime(void);

/* Given a vhpi handle to the Mx boundary, this will return the *
 * corresponding acc handle on the verilog side */

void * vhpi_fetch_acc_handle (vhpiHandleT scope_handle);

/* Given a vhpi handle to the Mx boundary, this will return the *
 * corresponding acc handle on the verilog side */

void * vhpi_fetch_vcsd_handle(vhpiHandleT scope_handle);

/* Given a vhpi handle to the Mx boundary, this will return the *
 * corresponding vpi handle on the verilog side */

void * vhpi_fetch_vpi_handle(vhpiHandleT scope_handle);

/* Given a vhpi handle to vhdl region instantiated under *
 * verilog, this function will return 1, else 0 */
int vhpi_has_verilog_parent(vhpiHandleT scope_handle);

/* Given a vhpi handle to Mx boundary, this will return*
 * 1 else 0 if the scope handle points to vhdl region */
int vhpi_is_verilog_scope(vhpiHandleT scope_handle);

/*
 * Given a vhpi handle to a procedure and a list parameters as strings
 * (VHDL formatted), following function calls it with given parameters
 * NOTE : The last parameter should be NULL.
 * For example:
 *
 * VOID mhdlSAPI_callVHDLProcedure(vhpi_handl_by_name(":package:proc"), \
 *              "1", "STRING'(\"string1\")",
 *              "STRING'(\"string2\")", NULL);
 */
typedef enum
{
    MXSAPI_UNKNOW_STATUS = 0,
    MXSAPI_NO_PROC_HANDLE,  /* No handle to VHDL procedure given */
    MXSAPI_NOT_PROC_TYPE,   /* Handle not a VHDL procedure type */
    MXSAPI_CALL_PASSED
} mhdlSAPIStatus_t;

mhdlSAPIStatus_t mhdlSAPI_callVHDLProcedure(vhpiHandleT vhpiHandle, ...);

/* Don't give error messages when coming through Specman ESI */
extern int inVCSMxESI;

#ifdef __cplusplus
}
#endif

#endif /* MHDLPLI_USER_H */

