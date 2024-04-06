#ifndef SCSD_H_H
#define SCSD_H_H

#ifdef __cplusplus
extern "C" {
#endif

/* header files */
#include "vhpi_user.h"


/* handles provided by vcs into its internal structure */
typedef unsigned long* scsdHandleT;
typedef unsigned long* scsdCbHandleT;

typedef double scsdRealT;

#ifdef Synopsys_Win32
typedef __int64 scsdPhysT, scsdTimeT;
#else
typedef long long scsdPhysT, scsdTimeT;
#endif

/**************************************************************************
 * SCSD handle get attributes APIs
***************************************************************************/

/************* Integer and boolean kind attributes **********/
typedef enum {
    /* boolean properties */
    scsdIsAccessTypeP,
    scsdIsArrayP,
    scsdIsByteValueP,
    scsdIsForeignP,
    scsdIsIndexedNameP,
    scsdIsPrecompiledPackP,
    scsdIsPrefixedNameP,
    scsdIsRecordP,
    scsdIsScalarP,
    scsdIsSelectedNameP,
    scsdIsSliceNameP,
    scsdIsVectorP,
    /* integer properties */
    scsdLineNoP,
    scsdObjectKindP,
    scsdSizeP,
    scsdTypeAccessValP,
    scsdTypeKindP,
    scsdValueFormatP,
    scsdValueSizeP,
    scsdInvalidIntPropertyP
} scsdIntPropertyT;

int scsd_get (scsdIntPropertyT scsdIntProperty, scsdHandleT scsdTypeHdl);

/* object kinds, if scsdObjectKindP property */
typedef enum {
    /* region object kinds */
    scsdBlockStmtK,
    scsdCompInstK,
    scsdGenerateStmtK,
    scsdForeignCompInstK,
    scsdForGenStmtK,
    scsdIfGenStmtK,
    scsdPackInstK,
    scsdProcessStmtK,
    scsdRootInstK,
    scsdVlogInstK,
    scsdVlogRegionK,
    /* declaration object kinds */
    scsdAliasDeclK,
    scsdAttributeK,
    scsdConstDeclK,
    scsdConstParamDeclK,
    scsdCompDeclK,
    scsdDerefObjK,
    scsdGenericDeclK,
    scsdFileDeclK,
    scsdFuncBodyK,
    scsdFuncCallK,
    scsdFuncDeclK,
    scsdParamK,
    scsdPortDeclK,
    scsdProcDeclK,
    scsdProcBodyK,
    scsdSigDeclK,
    scsdSigParamDeclK,
    scsdTypeDeclK,
    scsdVarDeclK,
    scsdVarParamDeclK,
    scsdUnitK,

    scsdInvalidObjK
} scsdObjectKindT;

/* object type kinds if scsdTypeKindP property */
typedef enum {
    /* scalar types */
    scsdTypeBitK,
    scsdTypeBooleanK,
    scsdTypeCharK,
    scsdTypeEnumK,
    scsdTypeFileK,
    scsdTypeIntK,
    scsdTypePhysK,
    scsdTypeRealK,
    scsdTypeStdLogicK,
    scsdTypeTimeK,
    /* vector types */
    scsdTypeBitVecK,
    scsdTypeBooleanVecK,
    scsdTypeEnumVecK,
    scsdTypeIntVecK,
    scsdTypePhysVecK,
    scsdTypeRealVecK,
    scsdTypeSignedK,
    scsdTypeStdLogicVecK,
    scsdTypeStringK,
    scsdTypeTimeVecK,
    scsdTypeUnsignedK,
    /* composite type kinds */
    scsdTypeArrayK,
    scsdTypeRecordK,
    scsdTypeAccessK,
    scsdInvalidTypeK
} scsdTypeKindT;

/************* String kind attributes **********/
typedef enum {
    scsdFileNameP,
    scsdFullNameP,
    scsdObjectKindStrP,
    scsdNameP,
    scsdValueFormatStrP,
    scsdTypeAccessValStrP,
    scsdTypeKindStrP,
    scsdInvalidStrPropertyP
} scsdStrPropertyT;

/* Return attribute in string formate *******/
char* scsd_get_str (scsdStrPropertyT scsdStrProperty,
                    scsdHandleT scsdTypeHdl);

/**************************************************************************
 * get SCSD handle APIs
***************************************************************************/

typedef enum {
    scsdAliased,
    scsdScope,
    scsdInvalidOneToOne
} scsdOneToOneT;

scsdHandleT scsd_handle (scsdOneToOneT relation, scsdHandleT scsdHdl);

/**************************************************************************
 * get value APIs
***************************************************************************/

/* Return pointer to raw format value of object specified by scsdHdl
 * parameter
 */
void* scsd_get_value (scsdHandleT scsdHdl);

typedef enum {
    scsdByteValK = 0,
    scsdIntValK,
    scsdRealValK,
    scsdTimeValK,
    scsdInvalidValK
} scsdValueFormatT;

/*** handle by name
 */
scsdHandleT scsd_handle_by_name (char* pathName, scsdHandleT regionHdl);
scsdHandleT scsd_handle_by_name_mx (char* pathName, char** pathNameRemainder,
                                    scsdHandleT regionHdl);

/*** scsd_get (scsdRawValueFormatP, scsdHdl) return scsdRawValueFormatT
 * raw value format
 */

/*** scsd_get_str (scsdRawValueFormatStrP, scsdHdl) return raw value format
 * string
 */

/**************************************************************************
 * Value change callback APIs
***************************************************************************/

typedef void  (*scsdValueChangeCbFnT) (void* user_data, void* pvalue);
typedef enum {
    scsdCbDeltaCycle = 0,
    scsdCbEndOfTime,
    scsdInvalidCbMode
} scsdValueChgCbModeT;

scsdCbHandleT scsd_register_value_chg_cb (scsdHandleT objHdl,
                                          scsdValueChangeCbFnT cbFn,
                                          void* user_data,
                                          scsdValueChgCbModeT cbMode,
                                          int alpBits);
scsdCbHandleT scsd_check_value_chg_cb (scsdHandleT objHdl,
                                       scsdValueChangeCbFnT cbFn,
                                       void* user_data);
int scsd_enable_value_chg_cb (scsdCbHandleT cbHdl);
int scsd_disable_value_chg_cb (scsdCbHandleT cbHdl);
int scsd_remove_value_chg_cb (scsdCbHandleT cbHdl);

/**************************************************************************/
/* function prototypes */
scsdHandleT vhpi_handle_to_scsd (vhpiHandleT vhpiHdl);
vhpiHandleT scsd_handle_to_vhpi (scsdHandleT scsdHdl);
int scsd_compare_handles (scsdHandleT scsdHdl1, scsdHandleT scsdHdl2);

/**** Traverse APIs *********************************************/
/******** Traverse hierarchy ************************************/
typedef int (*scsdObjCbFnT) (void* pUserData, scsdHandleT scsdObjHdl);

int scsd_traverse_hierarchy_down (void* pUserData, scsdHandleT scsdRegionHdl,
                                  int level, scsdObjCbFnT scsdDeclCbFn,
                                  scsdObjCbFnT scsdRegionCbFn);
int scsd_traverse_hierarchy_up (void* pUserData, scsdHandleT scsdRegionHdl,
                                int level, scsdObjCbFnT scsdRegionCbFn);

/******** Traverse prifexed names ********************************/
typedef int (*scsdPrefixedNameCbFnT) (scsdHandleT scsdPrefixedNameHdl);

int scsd_traverse_prefixed_names (scsdHandleT scsdObjHdl, int level,
                                  scsdPrefixedNameCbFnT scsdCbFn);


scsdHandleT scsd_handle_persistant (scsdHandleT scsdHdl);
int scsd_release_handle(scsdHandleT scsdHdl);
scsdHandleT scsd_handle_design_unit (scsdHandleT scsdCompInstHdl);
scsdHandleT scsd_handle_primary_unit (scsdHandleT scsdDesignUnitHdl);

// xprop related
extern int scsd_xprop_is_enabled(void);
extern int scsd_xprop_sig_is_promoted(scsdHandleT sig);
extern int scsd_xprop_int_xvalue(void);
extern int scsd_xprop_bool_xvalue(void);
extern int scsd_xprop_enum_xvalue(scsdHandleT sig);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* SCSD_H_H */
