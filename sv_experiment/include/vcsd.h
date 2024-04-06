/***********STARTFILE*********************************************************
 * Copyright (C) 1997-1998 Synopsys Inc. All Rights Reserved.
 * File:   vcsd.h
 * Purpose: header file for vcs direct interface/API functions in vcsd.c
 *
 ************ENDFILE**********************************************************/

#ifndef VCS_DIRECT_H
#define VCS_DIRECT_H

#ifdef __cplusplus
extern "C" {
#endif
/* header files */
#include "acc_user.h"
#include "vcs_acc_user.h"

/* value representation:        */
/*      C       D       value   */
/*      0       0         0     */
/*      0       1         1     */
/*      1       0         z (2) */
/*      1       1         x (3) */
/* Please note that the above encoding is different from acc encoding for z
 * and x (as described in acc_user.h) */
/* Vectors greater than 32 bits will be stored in multiple words.
 * vec32[0].c, vec32[0].d --> first word control & data
 * vec32[1].c, vec32[1].d --> second word and so on.
 */
/* vector representation: */
typedef struct vec32_s
{
    unsigned int c;             /*      control bits (C)      */
    unsigned int d;             /*      value bits   (D)      */
} vec32_t;

#define VCSD_VAR_HANDLE   0
#define VCSD_SCOPE_HANDLE 1
#define VCSD_PARAM_HANDLE 2
#define VCSD_AGGREGATE_HANDLE 0x4
#define VCSD_CLASS_HANDLE 0x8

/* Force types for the vc_forced field in vcsd_vc_record_t */
#define VCSD_NO_FORCE       0
#define VCSD_FORCE_FREEZE   1
#define VCSD_FORCE_DEPOSIT  2
#define VCSD_INVALID_FORCE  3
/*Invalid force code can be reused for force -drive later, if needed */

/* handle provided by vcs into its internal structure */
typedef int *vcsd_handle;
typedef unsigned long vcsd_sva_handle; /* To correspond to Ova_AssertID */



typedef struct vcsd_index_data
{
    unsigned int nElem;
    unsigned int *elem;
} vcsd_index_data_s, *vcsd_index_data_t;


typedef union vcsd_value_u
{
    unsigned char logic_value;  /* store the value of logic, bit and scalar types. */
    double real_value;          /* store the value of real, perhaps shortreal. */
    vec32_t*  p_vector_value; /* store the value of bit vector, vector and logic vector type.
                                   * instead of handle as in
                                   * s_vc_record.out_value
                                   */
    /* for accEventVar p_vector_value
     * would be NULL
     */
    char*     p_strength_vector_value; /* store the value of strength vector
                                            * each bit of vector is represented
                                            * with 1 byte
                                            */
    s_strengths strengths_s;  /* defined in acc_user.h */
    char*       p_mem_val;    /* for memories and reg mdas */
    double*     p_real_mem_val;    /* for real memories and reg mdas */
    vcsd_handle dhandle;       /* for dynamic scopes/objects */

    unsigned int* p_2state_vector_value;    /*2state_vector_value_change */
    unsigned char* p_logic_mem_value;   /* logic_mem_value_change */
    double* p_real_mem_value;       /* real_mem_value_change */
    unsigned int *p_2state_vector_mem_value;/* 2state_vector_mem_value_change */
    vec32_t* p_vector_mem_value;        /* vector_mem_value_change */
    vec32_t* p_wire_mem_value;      /* wire_mem_value_change */
} vcsd_value_t;

/* definition of data structure which shall contain information about the
 * most recent change that occurred on the monitored object.
 * Similar to s_vc_record defined in acc_user.h, only difference is
 * its out_value structure, which no more has a handle for the vector
 * instead shall point the control/data directly.
 */
#define invalid_reason                  0
#define memory_value_change             6
#define wire_memory_value_change        7
#define real_memory_value_change        8
/* real_mmeory_value_change value changed to accomodate in VCO */

#define aggregate_value_change          14
#define vector_value_change_2state      15
#define logic_memory_value_change       16
#define vector_memory_value_change      18
#define vector_memory_value_change_2state   19
#define packed_struct_member_value_change   20
#define dyn_value_change                    21
#define hsopt_internal_cbk                  31

#define vcsd_vc_cb                               0
#define vcsd_force_cb                            1
#define vcsd_release_cb                          2

typedef struct vcsd_vc_record_s
{
    int vc_reason;
    int vc_hightime;
    int vc_lowtime;
    char *user_data;
    vcsd_value_t out_value;
    long mem_word_index; /* valid only for memory/reg MDAS */
    int thread_id;      /* valid only for dynamic scope callbacks */
    int frame_id;       /* valid only for dynamic scope callbacks */
#ifdef _AIX
    unsigned int vc_forced:2,
             vc_unused:6;
#else
    unsigned char vc_forced:2,
             vc_unused:6;
#endif
    unsigned char* mask_value;   /* valid only for memory words/vectors */
    unsigned int   frcb_reason:2,
             mask_reversed:1,
             forRent:5;
} vcsd_vc_record_t;

typedef struct vcsd_dim_info_s
{
    int  cDims; /* no. of dimensions, 1 for accMemory */
    int* lhsIndex; /*lhs indexes for each dimension*/
    int* rhsIndex; /*rhs indexes for each dimension*/
} vcsd_dim_info_t, vcsd_pac_dim_info_t;

/* structure for variable info */
typedef struct vcsd_var_info_s
{
    char*         p_name;      /* name of the variable */
    int           type;        /* the following types are supported
                                    * see acc_user.h
                                    * #define accNet 25
                                    * #define accReg 30
                                    * #define accRegister 30
                                    * #define accNamedEvent 280
                                    * #define accEventVar 280
                                    * #define accIntVar 281
                                    * #define accIntegerVar 281
                                    * #define accRealVar 282
                                    * #define accTimeVar 283
                    * #define accIntegerParam 200
                    * #define accIntParam 200
                    * #define accRealParam 202
                    * #define accStringParam 204
                                    * #define accMemory 700
                    * see vcs_acc_user.h
                    * #define accChar 650
                    * #define accInt 652
                    * #define accBitType 654
                    * #define accByte 656
                    * #define accShortInt 658
                    * #define accLongInt 660
                    * #define accLogic 662
                    * #define accMda 701
                    * #define accClass 744
                                    */
    int           vc_reason;   /* same as vc_reason in s_vc_record.
                                    * It determines what p_value will point to
                                    * #define logic_value_change 1
                                    * #define strength_value_change 2
                                    * #define real_value_change 3
                                    * #define vector_value_change 4
                                    * #define event_value_change 5
                    * #define memory_value_change 6
                    * #define wire_memory_value_change      7
                    * #define aggregate_value_change        14
                    * #define vector_value_change_2state    15
                    * #define logic_memory_value_change     16
                    * #define real_memory_value_change      17
                    * #define vector_memory_value_change    18
                    * #define vector_memory_value_change_2state 19
                                    */
    vcsd_value_t*  p_value;    /* point to the value */
    int           lsb;         /* least significant bit */
    int           msb;         /* most significant bit */
    /* lsb = msb = -1 for scalars */
    vcsd_pac_dim_info_t* p_dims; /* this structure stores the packed dimension.
                      * For normal vectors cDims will be 1.
                      */
    unsigned int        automatic:1,   /* whether var is automatic */
             full_type:9,   /* further classification on "type" */
             dlp_part_id:8, /* DLP partition ID */
             isWordLayout:1, /* memory layout information */
             isSparseMem:1, /* whether var is a sparse memory */
             unused:12;

} vcsd_var_info_t;

/* definitions of scope types */
typedef enum
{
    VCSD_UST_MODULE = 0,
    VCSD_UST_BLOCK,
    VCSD_UST_TASK,
    VCSD_UST_FUNC,
    VCSD_UST_FORK,
    VCSD_UST_AGGREGATE,
    VCSD_UST_UNPACKED_STRUCT,
    VCSD_UST_PACKED_STRUCT,
    VCSD_UST_UNPACKED_UNION,
    VCSD_UST_PACKED_UNION,
    VCSD_UST_INTERFACE,
    VCSD_UST_CLASS,
    VCSD_UST_MODPORT,
    VCSD_UST_INTERFACEPORT,
    VCSD_UST_PROGRAM,
    VCSD_UST_PACKAGE,
    VCSD_UST_CLOCKING_BLOCK,
    VCSD_UST_MODPORT_PORT
} VCSD_UST_e;

/* Source File Info Structure defined in vcs_acc_user.h */
/* typedef struct vcs_srcfile_info_t {
*      char *SourceFileName;
*      int SourceFileTag;
*      int StartLineNum;
*      int EndLineNum;
*  } vcs_srcfile_info_s, *vcs_srcfile_info_p;
*/
typedef vcs_srcfile_info_s vcsd_srcfile_info_t;

/* structure for scope info */
typedef struct vcsd_scope_info_s
{
    char*               p_def_scope_name; /* name of scope definition */
    char*               p_ins_scope_name; /* name of scope instance */
    VCSD_UST_e          type;             /* as defined above */
    /* for BLOCK, TASK, FUNC and FORK
     * p_def_scope_name and
     * p_ins_scope_name are identical
     */
    int                 ins_line_num;     /* scope instance declaration */
    vcsd_srcfile_info_t* p_srcfile_info;  /* defined above */
    /* there are at least two
     * vcs_srcfile_info_t structures
     * allocated consecutively in
     * memory. The last structure is
     * always empty to indicate the
     * end of the list. SourceFileName
     * of last structure is NULL. User
     * should free the memory of the
     * vcsd_srcfile_info_t structures
     */
    unsigned int        automatic:1,      /* whether scope is automatic */
             unused:31;
} vcsd_scope_info_t;

/* return values of vcsd_typep() */
#define vcsd_nullparam   0
#define VCSD_NULLPARAM   0
#define vcsd_stringparam 1
#define VCSD_STRINGPARAM 1
#define vcsd_scopeparam  2
#define VCSD_SCOPEPARAM  2
#define vcsd_varparam    3
#define VCSD_VARPARAM    3
#define vcsd_consparam   4
#define VCSD_CONSPARAM   4
#define VCSD_PARAM   5
#define vcsd_aggregateparam   6
#define VCSD_AGGREGATEPARAM   6

/**************************************************************************/

/* definitions for vcsdf_vcldata_t.type */
#define VCSDF_REAL              1
#define VCSDF_EVENT             2
#define VCSDF_TIME              3
#define VCSDF_INTEGER           4
#define VCSDF_LOGIC_SCALAR      5
#define VCSDF_LOGIC_VECTOR      6
#define VCSDF_STRENGTH_SCALAR   7
#define VCSDF_STRENGTH_VECTOR   8
#define VCSDF_RNET_SCALAR       9
#define VCSDF_RNET_VECTOR       10

#include "vcsdf.h"

typedef struct vcsd_handle_offset_info_s {
    vcsd_handle vcs_variable_handle;
    void* hMdaHandle;
    unsigned int bMdaVar:1, bMdaVarEl:1, bMem:1, bMask:1, uSize:28;
    unsigned int mdaElOffset;
    unsigned int left;
    unsigned int right;
} vcsd_handle_offset_info_t;

/* definitions of scope types */
/* Assertion related */
typedef enum 
{
    VCSD_SVA_ASSERT = 0,
    VCSD_SVA_ASSUME,
    VCSD_SVA_COVER,
    VCSD_SVA_IMMEDIATE_ASSERT,
    VCSD_SVA_IMMEDIATE_ASSUME,
    VCSD_SVA_IMMEDIATE_COVER,
    VCSD_SVA_DEFERRED_ASSERT,
    VCSD_SVA_DEFERRED_ASSUME,
    VCSD_SVA_DEFERRED_COVER,
    VCSD_SVA_SEQUENCE,
    VCSD_SVA_LAST
} VCSD_SVA_TYPE;

typedef enum
{
    VCSD_SVA_CB_SUCCESS = 0,
    VCSD_SVA_CB_VACUOUS_SUCCESS,
    VCSD_SVA_CB_FAIL,
    VCSD_SVA_CB_ATTEMPT_START,
    VCSD_SVA_CB_ATTEMPT_REMOVED,
    VCSD_SVA_CB_ATTEMPT_UNTERMINATED,
    VCSD_SVA_CB_LAST
} VCSD_SVA_CB_TYPE;

typedef enum
{
    VCSD_SVA_STATE_ASSERT_ON = 0,
    VCSD_SVA_STATE_ASSERT_OFF,
    VCSD_SVA_STATE_ASSERT_KILL,
    VCSD_SVA_STATE_ASSERT_RESET,
    VCSD_SVA_STATE_ASSERT_LOCK,
    VCSD_SVA_STATE_ASSERT_UNLOCK,
    VCSD_SVA_STATE_ASSERT_LAST
} VCSD_SVA_STATE_TYPE;

typedef enum
{
    VCSD_SVA_CTRLSRC_COMPILE=0,
    VCSD_SVA_CTRLSRC_RUNTIME,
    VCSD_SVA_CTRLSRC_LOWPOWER,
    VCSD_SVA_CTRLSRC_INTERACTIVE,
    VCSD_SVA_CTRLSRC_USERTASK,
    VCSD_SVA_CTRLSRC_CONFIG,   
    VCSD_SVA_CTRLSRC_LAST
} VCSD_SVA_CTRLSRC_TYPE;

/* structure for sva source info */
typedef struct vcsd_sva_src_info_s {
    char*          svaName;       /* assertion name */
    VCSD_SVA_TYPE  svaType;       /* assertion type */
    char*          svaFileName;   /* assertion source filename */
    unsigned int   svaLineNo;     /* assertion source line number */
} vcsd_sva_src_info_t;

/* structure for sva event info */
typedef struct vcsd_sva_event_info_s {
    VCSD_SVA_CB_TYPE eventType;   /* assertion cb event type */
    unsigned int     eventHiTime; /* assertion cb event hitime */
    unsigned int     eventLoTime; /* assertion cb event lotime */
    unsigned int     startHiTime; /* assertion attempt start hitime */
    unsigned int     startLoTime; /* assertion attempt start lotime */
    unsigned int     indexSigCount;   /* size of index sigs */
    char**           indexSigs;       /* names of index signals */
    int*             indexValues;     /* value of index signals */
} vcsd_sva_event_info_t;

/* structure for sva state info */
typedef struct vcsd_sva_state_info_s {
    VCSD_SVA_STATE_TYPE   stateType; /* assertion state type on/off/kill */
    VCSD_SVA_CTRLSRC_TYPE ctrlSrcType; /* assertion state change src type */
    char*                 fileName; /* assertion control task src file */
    unsigned int          lineNo;   /* assertion control task src lineno */
    unsigned int          ctrlHiTime; /* assertion state change hitime */
    unsigned int          ctrlLoTime; /* assertion state change lotime */
} vcsd_sva_state_info_t;

/**************************************************************************/

/* vcsd get current stack**************************************************/
typedef struct vcsd_callstack_node_s {
    char*        name;
    char*        filename;
    unsigned int line_number;
} vcsd_callstack_node_t;

typedef struct vcsd_callstack_s {
    int stack_size;       /* length of callstacks */
    vcsd_callstack_node_t* callstacks;
} vcsd_callstack_t;

/* return NULL if fail to get callstack */
vcsd_callstack_t* vcsd_get_vlog_callstack();


/* extern declarations */
/* Prototypes of callbacks */
typedef void  (*vcsd_scope_consumer) ( char *File, unsigned int Line,
                                       char *UserData, int iTag );
typedef void  (*vcsd_var_consumer) ( vcsd_vc_record_t* );
typedef void  (* vcsdf_var_consumer) ( vcsdf_vcldata_t *);
typedef void  (*vcsd_variable_ftn) ( void* user_parent_handle, vcsd_handle
                                     vcs_variable_handle, vcsd_var_info_t* p_variable_info );
typedef void* (*vcsd_scope_ftn) ( void* user_parent_handle, vcsd_handle
                                  vcs_scope_handle, vcsd_scope_info_t* p_scope_info );

/* Prototypes of System Verilog assertions */
typedef void  (*vcsd_sva_scope_fn) (vcsd_sva_handle assertionId, vcsd_sva_src_info_t* sva_src_info_p, void *user_data);
typedef void  (*vcsd_sva_event_fn) (vcsd_sva_handle assertionId, vcsd_sva_event_info_t* sva_event_info_p, void *user_data);
typedef void  (*vcsd_svactrl_state_fn) (vcsd_sva_handle assertionId, vcsd_sva_state_info_t* sva_state_info_p, void *user_data);


/* function prototypes */
extern vcsd_sva_state_info_t* vcsd_get_sva_state_info(vcsd_sva_handle assertionId);
extern vcsd_sva_src_info_t* vcsd_get_sva_src_info(vcsd_sva_handle assertionId);
extern char*  vcsd_get_sva_fullname(vcsd_sva_handle assertionId);
extern vcsd_sva_handle vcsd_get_sva_handle_by_vpi(vcsd_handle vcs_handle);
extern void vcsd_sva_enable_index_info( void );

extern char*  vcsd_get_version ( void );

extern int    vcsd_mod_add_lcb ( vcsd_handle vcs_handle, vcsd_scope_consumer
                                 p_function, void* p_user_data );
extern void*  vcsd_mod_check_lcb ( vcsd_handle vcs_handle, vcsd_scope_consumer
                                   p_function );
extern int    vcsd_mod_enable_lcb ( vcsd_handle vcs_handle, vcsd_scope_consumer
                                    p_function );
extern int    vcsd_mod_disable_lcb ( vcsd_handle vcs_handle, vcsd_scope_consumer
                                     p_function );
extern int    vcsd_mod_del_lcb ( vcsd_handle vcs_handle, vcsd_scope_consumer
                                 p_function );
extern int    vcsd_add_frcrel_callback( vcsd_handle vcs_handle, vcsd_var_consumer
                                        p_function, vcsd_var_consumer q_function, void* p_user_data );
extern int    vcsd_replace_callback_userdata ( vcsd_handle vcs_handle,
                                               void* p_user_data, vcsd_var_consumer p_new_function,
                                               unsigned alpBits);
extern int    vcsd_add_callback ( vcsd_handle vcs_handle, vcsd_var_consumer
                                  p_function, void* p_user_data );
extern int    vcsd_add_frc_callback ( vcsd_handle vcs_handle, vcsd_var_consumer
                                      p_function, void* p_user_data );
extern int    vcsd_add_rel_callback ( vcsd_handle vcs_handle, vcsd_var_consumer
                                      p_function, void* p_user_data );
extern int    vcsd_del_frc_callback ( vcsd_handle vcs_handle, vcsd_var_consumer
                                      p_function, void* p_user_data );
extern int    vcsd_del_rel_callback ( vcsd_handle vcs_handle, vcsd_var_consumer
                                      p_function, void* p_user_data );
extern int    vcsd_delete_callback_userdata ( vcsd_handle vcs_handle,
                                              vcsd_var_consumer p_function, void* p_user_data );
extern int    vcsdf_add_callback ( vcsd_handle vcs_handle, vcsdf_var_consumer
                                   p_function, void* p_user_data );
extern void*  vcsd_check_callback ( vcsd_handle vcs_handle, vcsd_var_consumer
                                    p_function );
extern int    vcsd_check_callback_status();
extern int    vcsd_enable_callback ( vcsd_handle vcs_handle, vcsd_var_consumer
                                     p_function );
extern int    vcsd_disable_callback ( vcsd_handle vcs_handle, vcsd_var_consumer
                                      p_function );
extern int    vcsd_delete_callback ( vcsd_handle vcs_handle, vcsd_var_consumer
                                     p_function );

extern int    vcsd_typep ( int nparam );
extern void   vcsd_propogate (vcsd_handle vcs_handle);
extern void   vcsSetCurrentTime(unsigned int low, unsigned int high);
extern void   ExecuteOneCycle(int clockTicks);
extern void   DisableEnableFlops(unsigned int fEnable);
extern void   SaveAllForcesInVPD(void);
extern bool   checkIfInputOrInoutPortHandle(void* vhan, bool dutNets);
extern void   RestoreForceReleaseFromVPD(void* han, void* pForceValue,
                                         unsigned int* pForceMask, unsigned int uBitSize,
                                         unsigned int fForce);
extern void   RestoreOneForceFromVPDI(unsigned int vpdId, void* pval,
                                      unsigned int* pMask, unsigned int width);
extern int    vcsd_traverse_hierarchy ( void* p_user_handle, vcsd_handle
                                        vcs_handle, int level, vcsd_variable_ftn
                                        p_variable_callback_function, vcsd_scope_ftn
                                        p_scope_callback_function );
extern int    vcsd_traverse_sva_hierarchy (void* p_user_data, vcsd_handle scope_handle,
                                        vcsd_sva_scope_fn p_sva_function);
extern void*  vcsd_check_sva_callback ( vcsd_sva_handle assertionId );
extern int    vcsd_remove_sva_callback ( vcsd_sva_handle assertionId );
extern int    vcsd_add_sva_callback ( vcsd_sva_handle assertionId, void* p_user_data);
extern int    vcsd_set_sva_callback (VCSD_SVA_CB_TYPE type, vcsd_sva_event_fn p_function);
extern int    vcsd_set_sva_control_callback (vcsd_svactrl_state_fn p_function);
extern void   vpd_dump_folded_hier(void *hfDesign);

extern vcsd_handle        vcsd_get_handle ( int nparam );
extern vcsd_handle        vcsd_get_parent_handle ( vcsd_handle vcs_handle );
extern vcsd_handle        vcsd_get_parent_module_handle(vcsd_handle vcs_handle);
extern vcsd_var_info_t*   vcsd_get_range ( vcsd_handle vcs_var_handle );
extern vcsd_var_info_t*   vcsd_get_var_info ( vcsd_handle vcs_var_handle );
extern char* vcsd_handle_get_name(vcsd_handle vcs_var_handle);
extern void getFlatDimsForTypedNode(vcsd_handle vcs_var_handle, int* msb, int* lsb);
extern vcsd_scope_info_t* vcsd_get_scope_info ( vcsd_handle vcs_scope_handle );
extern char *vcsd_get_full_scope(vcsd_handle vcs_handle);
extern vcsd_handle        vcsd_get_persistent_handle ( vcsd_handle vcs_handle );
extern int        vcsd_free_handle(vcsd_handle);
extern int        vcsd_handle_type ( vcsd_handle vcs_handle );
extern void*      vcsd_get_value ( vcsd_handle vcs_handle );
extern void*      vcsd_get_value_with_bounds(vcsd_handle vcs_handle, int* lsb, int* msb);
extern int        vcsd_get_module_type ( vcsd_handle vcs_handle );
extern int vcsd_has_celldefine(vcsd_handle h);
extern int vcsd_has_librarymodule(vcsd_handle h);
extern int fetch_type_vcsd (vcsd_handle vcs_handle);
extern int fetch_is_signed_vcsd (vcsd_handle vcs_handle);
extern vcsd_handle vcsd_handle_by_name (char *psName );
extern vcsd_handle vcsd_handle_from_scope(char *psName, vcsd_handle vcs_handle);
extern int vcsd_compare_handle(vcsd_handle obj1,vcsd_handle obj2);
extern vcsd_handle vcsd_simulated_net(vcsd_handle vcs_handle);
extern char vcsd_get_logical_value(int* vcsd_val);
extern int vcsd_is_logical(vcsd_handle vcs_handle);
extern void* vcsd_get_value_pointer(vcsd_handle vcs_handle);
extern void* vcsd_get_tran_connected_value(void* value_handle);
extern int   vcsd_is_tran_connected(vcsd_handle vcs_handle);
extern char* vcsd_srcfile_dir(void);
extern int vcsd_fetch_type(vcsd_handle vcs_handle);
extern int vcsd_fetch_ref_type(vcsd_handle vcs_handle);
int vcsd_fetch_size(vcsd_handle vcs_var_handle);
extern int vcsd_fetch_is_signed(vcsd_handle vcs_handle);
extern unsigned int vcsdIsRootStrengthVector(vcsd_handle vcs_handle);

extern void vcsd_set_need_vc_forced(int newVal);
extern int vcsd_get_need_vc_forced(void);

extern void vcsdCreateFnVpdIdMapping(vcsd_handle vcs_handle, void* pUserData,
                                     unsigned int* isPrimary);
extern void vcsdUpdateHsimfVCCallback(vcsd_handle vcs_handle, void* pUserData,
                                      unsigned int reason, int* iGateAlias, unsigned alpBits);
extern void vcsdResetAllHsimCallbacks(void);
extern void vcsdResetDesignNode(vcsd_handle vcs_handle);
extern void vcsdResetNDUserData(vcsd_handle vcs_handle);
extern void vcsdReplaceUserDataForHsimFn(
    vcsd_handle vcs_handle, void** vpdHandle, void* pUserData);
extern void* vcsdGetUserDataForHsimFn(vcsd_handle vcs_handle,
                                      unsigned int* fIsVpdHandleAsUserData, unsigned int* fIsNonDesignNode);
extern unsigned int vcsdIsHsimPrimaryFn(vcsd_handle vcs_handle);
extern void vcsdFlushFnVpdIdMap(void);
extern void vcsdPreHandleForHsimVPDOPT(void);
extern unsigned int vcsdIsAnyHsimVpdOpt(void);
extern void vcsdDisableVPDOPT(void);
extern void vcsdDisableVPDOPTGate(void);
extern void vcsdDisableVPDOPTVec(void);
extern unsigned int vcsdIsVPDOPTInited(void);

/* Added for MDA/Memory support in vcsd */
extern void setfHsimMemCbkSet(unsigned int val);
extern void setfHsimMemCbkWordIndex(unsigned int ind, unsigned int ws);
extern void setfHsimBitIndex(unsigned int ind, unsigned int ws);
extern void resetfHsimMdaCbkFlags(void);

extern vcsd_pac_dim_info_t*  vcsd_get_packed_dimensions(
    vcsd_handle vcs_handle );

typedef struct vcsd_frcrel_s {
    vcsd_handle obj;
    vcsd_var_consumer p_function;
} vcsd_frcrel_t;

typedef struct vec_val_s
{
    vec32_t* pvec32;
    int iBit;
    int nGroups;
} vec_val_t;

#define vcsdArrayMemVal   0
#define vcsdArrayVecVal   1
#define vcsdArrayRealVal  2
#define vcsdArrayLogicVal 3

typedef struct vcsd_word_val_info_s
{
    int format;
    union {
        unsigned char logic_value;
        double real_value;
        char* memval;
        vec_val_t vecval;
    } value;
} vcsd_word_val_info_t;

//To make coverage consumer function compatible with the expected consumer
//function of vcsd_traverse_word_members we need this structure.
typedef struct cov_traverse_word_members_s{
    void *user_data;
    void *h;
    void (*vcsd_tgl_ftn)(void *, int *, vcsd_var_info_t* );
} cov_traverse_word_members_t;

extern vcsd_dim_info_t*  vcsd_get_dimensions( vcsd_handle vcs_handle );
extern vcsd_word_val_info_t* vcsd_get_word_value( vcsd_handle vcs_handle, int* dimsArray );
extern vcsd_word_val_info_t* vcsd_get_word_value_with_dims( vcsd_handle vcs_handle, int* dimsArray,vcsd_dim_info_t* dimInfo );

/* Added for AMS, used by VirSim */
extern int vcsd_is_analog_obj(vcsd_handle vcs_var_handle);
extern char* vcsd_get_spice_hier_by_vpi(vcsd_handle vcs_var_handle);
/* Added for MixedHDL, currently used by CM */
extern void vcsd_set_vcsd_enabled(int flag);
extern void vcsd_set_parameter_dumping(int flag);
extern void vcsd_set_traverse_vhdl(int flag);
extern void vcsd_restore_traverse_vhdl(void);
extern int vcsd_is_vhdl_scope(vcsd_handle scope);
extern int vcsd_has_vhdl_parent(vcsd_handle scope);
extern void* vcsd_fetch_vhpi_handle(vcsd_handle scope);
extern int vcsd_is_2state(vcsd_handle vcs_var_handle);
/* Added for MixedHDL, currently used by VirSim PLI */
extern void *vcsdGetHandleFromAcc(void *accNode);
/* Added for getting bit values of scalarized vectors */
int vcsd_is_expanded(vcsd_handle var_handle);
extern int vcsd_is_scalarized(vcsd_handle vcs_var_handle);
extern int vcsd_is_memberhandle(vcsd_handle vcs_var_handle);
extern vcsd_var_info_t* vcsd_get_var_info_scalarized_bit(vcsd_handle vector_handle, int pos);
extern int vcsd_add_callback_scalarized_bit(vcsd_handle vector_handle, int pos,
                                            vcsd_var_consumer p_function, void* p_user_data);
extern vcsd_handle vcsd_get_cm_handle(vcsd_handle scope_handle, int rNum, int hNum);
extern int vcsd_is_cm_skippedModule(vcsd_handle vcs_handle);
extern int is_vcsd_cbk_disabled(void);

extern int   vcsd_handle_aggregate_type(vcsd_handle vcs_handle);
/*    This returns aggregate type handle is scope or variable         */
/*    which helps old user of vcsd be confortable with old vcsd types */
extern int   vcsd_aggregate_scope_type(vcsd_handle vcs_handle);
extern int   vcsd_is_packed(vcsd_handle aggregate_handle);
extern int   vcsd_is_wiremda(vcsd_handle aggregate_handle);
extern int   vcsd_is_old_mda_layout(void);
extern int   vcsd_is_old_mdanet_layout(void);
extern int   vcsd_is_tagged(vcsd_handle aggregate_handle);
extern int   vcsd_is_nettype(vcsd_handle variable_handle);
extern int   vcsd_is_enum(vcsd_handle variable_handle);
extern int   vcsd_is_generated(vcsd_handle variable_handle);
extern void* vcsd_enum_get_base(vcsd_handle variable_handle);
typedef void (*enum_consumer) (char* name, vcsd_value_t* value);
extern int   vcsd_enum_traverse(void* base, enum_consumer enumFn);
extern char* vcsd_get_defname(vcsd_handle vcs_handle);
extern int vcsd_fetch_enum_type(vcsd_handle vcs_handle);
extern int vcsd_traverse_word_members(vcsd_handle, vcsd_var_consumer, void*);
extern int vcsd_is_port(vcsd_handle vcs_handle);
/* If the variable is a port, it is one of accInput, accOutput or accInout.
   Else, it returns 0 */
extern int vcsd_fetch_port_direction(vcsd_handle var_handle);

/* Flag to indicate wreal multiple driver resolution is enabled.*/
extern int VCS_fWrealMdrEnabled;

/* delete, check, enable, disable don't support userData based comparison */
/* Following functions can be used to have additional comparison on that. */
typedef int (*vcsd_compare_ftn)(vcsd_handle ref, void* userData);
void vcsd_set_aux_cbk_compare_fn(vcsd_compare_ftn ftn);
void vcsd_reset_aux_cbk_compare_fn(void);

/* This is an auxilary function to vcsd_traverse_hierarchy() */
/* This is like the last argument of vcsd_traverse_hierarchy, but it will
   be called at the exit of every scope during DFS walk. */
/* It will be reset after every vcsd_traverse_hierarchy() */
void vcsd_set_scope_exit_callback(vcsd_scope_ftn ftn);
void vcsd_set_scope_reentry_callback(vcsd_scope_ftn vtn);

/* OVA related definitions */

typedef enum
{
    VCSD_OVA_VAR_TYPE_BOOL,
    VCSD_OVA_VAR_TYPE_BOOL_TEMPORAL,
    VCSD_OVA_VAR_TYPE_NONE
} VCSD_OVA_VAR_TYPE_e;

typedef struct vcsd_ova_var_info_s
{
    VCSD_OVA_VAR_TYPE_e               type; /* ova variable type */
} vcsd_ova_var_info_t;

typedef struct vcsd_ova_unit_info_s
{
    vcsd_srcfile_info_t* bind_srcfile_info; /* ova unit bind source information */
} vcsd_ova_unit_info_t;


/* this function tells if the module that you have got is actually an ova unit*/
extern int vcsd_is_PEsubstituted(vcsd_handle vcs_handle);
extern int vcsd_is_RtgDummy(vcsd_handle vcs_handle);
extern int vcsd_is_ova_unit(vcsd_handle vcs_handle);
extern int vcsd_is_unit_package(vcsd_handle vcs_handle);
extern char* vcsd_get_unit_package_name(vcsd_handle vcs_handle);
extern char* vcsd_get_unit_package_name_for_coverage(vcsd_handle vcs_handle);
extern char* vcsd_get_fullname_for_coverage(vcsd_handle vcsHandle);
extern char* vcsd_get_variant_name(vcsd_handle vcs_handle);
extern bool vcsd_is_skipped_node_for_cov(vcsd_handle vcsHandle);
extern void vcsd_refresh_dbs_flags(vcsd_handle vcsHandle);
/* this function returns OVA specific information for a net.
   Returns NULL if not OVA net */
extern vcsd_ova_var_info_t* vcsd_get_ova_var_info(vcsd_handle vcs_handle);
/* this function returns OVA specific information for a unit.
   Returns NULL if not OVA unit module */
extern vcsd_ova_unit_info_t* vcsd_get_ova_unit_info(vcsd_handle vcs_handle);

vcsd_handle vcsd_next_bit(vcsd_handle vec, vcsd_handle bit);
int vcsd_get_bitsel_index(vcsd_handle hbit);
int vcsd_get_select_type(vcsd_handle obj);

typedef enum {
    VCSD_LANG_VLOG,
    VCSD_LANG_SYSVLOG
} VCSD_LANG_e;

/* Return verilog flavor */
extern VCSD_LANG_e vcsd_get_lang(void);

typedef enum {
    VCSD_REAL_DEF_VAL = 0,
    VCSD_REAL_Z_VAL,
    VCSD_REAL_X_VAL
} VCSD_REAL_VAL_TYPE;

/* Return real value type */
extern VCSD_REAL_VAL_TYPE vcsd_get_real_val_type(double* data_ptr);

void* svaGetIpFromHandle(void* a);
unsigned int svaGetScopeFromHandle(void* a);
int vcsd_get_packed_index(vcsd_handle packedStru, vcsd_handle member,
                          unsigned int *msb, unsigned int *lsb);
vcsd_handle vcsd_get_TopPackedStructureHandle(vcsd_handle packedStru);

extern int vcsd_is_reference_object(vcsd_handle han);
extern vcsd_handle vcsd_get_actual_handle(vcsd_handle varHan);
extern void vcsd_set_vcsdtype(vcsd_handle han, int type);
extern int vcsd_get_vcsdtype(vcsd_handle han);
extern int vcsd_is_vcs_package(vcsd_handle vcs_handle);

/* vcsd_get_varinfo, vcsd_traverse_hierarchy have no value info */
int vcsd_begin_no_value_var_info();
int vcsd_end_no_value_var_info();

void* vcsd_get_value_ptr(vcsd_handle sig);

/*
 *   arguments :   NONE
 *   return value: non-zero if non-standard memory layout is used globally, otherwise zero.
 */
int vcsd_is_nonstd_mem(void);
int vcsd_is_wordlayout_mem(vcsd_handle vcs_handle);

extern int vcsd_get_incdirs(char **incdir);

/*--- PVCS API functions ----------------------------------------------------*/

/* Max number of consumers for most PVCS ALP technologies. */
enum { VCSD_MAX_ALP_CONSUMERS = 8 };

/* Alias for "unsigned int". Used to indicate function parameters that specify
 * "ALP bits". A DKI callback can be decorated with "ALP bits" that declare it
 * as thread-safe, or request special support from the simulation kernel.
 */
#ifndef vcsd_alp_bits_t__DEFINED
#    define vcsd_alp_bits_t__DEFINED
typedef unsigned vcsd_alp_bits_t;
#endif

/* Data on an ALP technology that requires support from the simulation kernel.
 *
 * Values overwritten by vcsd_alp_register_technology():
 * - req_consumers: number of consumers requested by command-line arguments to
 *   the simulation kernel. Can be 0 if the user did not enable the technology
 * - max_consumers: maximum allowed number of consumers. Will never exceed
 *   VCSD_MAX_ALP_CONSUMERS
 * - alp_bits_c0: value of "ALP bits" corresponding to the 0-th consumer. For
 *   i-th consumer (where i is between 0 and max_consumers-1, inclusively),
 *   alp_bits_c0+i can be used.
 *
 * Values that must be set in user's code before ALP consumers are created.
 * All of them are initialized in vcsd_alp_register_technology():
 * - n_consumers: number of consumers to be created. Can't exceed max_consumers.
 *   Initialized to req_consumers.
 * - is_disabled: if != 0, callbacks executed for the ALP technology will not
 *   spawn parallel consumers but rather be handled by the simulation kernel.
 * - on_init: pointer to a function to be called (in the consumer context)
 *   immediately after forking off a new consumer. consumerIdx is the index
 *   of the consumer (between 0 and n_consumers-1, inclusively). Initialized
 *   to NULL.
 * - on_message: pointer to a function to be called (in the consumer context)
 *   each time a message sent by vcsd_alp_send_message() is received. data_ptr
 *   and data_size define a chunk of data sent by the producer. data_ptr is
 *   NULL if data_size was 0; otherwise it's aligned on a pointer boundary.
 * - on_exit: pointer to a function to be called (in the consumer context)
 *   before shutting down a consumer. Initialized to NULL.
 * - on_spawn pointer to a function to be called (in the producer context)
 *   after forking off consumers and before sending any DKI callbacks.
 *   Initialized to NULL.
 */
typedef struct {
    unsigned    req_consumers;
    unsigned    max_consumers;
    vcsd_alp_bits_t alp_bits_c0;

    unsigned    n_consumers;
    int         is_disabled;
    void        (*on_init)(unsigned consumerIdx);
    void        (*on_message)(const void* data_ptr, unsigned data_size);
    void        (*on_exit)(void);
    void        (*on_spawn)(void);
} vcsd_alp_data_t;


/* Returns the number of DLP partitions the design is divided into:
 * - 1 for serial runs
 * - 1 + number of slave partitions in parallel runs.
 */
extern int vcsd_get_dlp_partition_count(void);


/* Returns a non-zero value of type vcsd_alp_bits_t that indicates an
 * unconditionally thread-safe DKI callback that does not require any
 * special support.
 */
extern vcsd_alp_bits_t vcsd_alp_bits_for_thread_safe(void);

/* Registers an ALP technology with the simulation kernel. Fills out the
 * contents of alp_data (see the comment on vcsd_alp_data_t). Returns 0 if
 * alp_name wasn't a known technology name, or 1 otherwise. In the latter
 * case, alp_data->alp_bits_c0 will be set to a non-zero value.
 */
extern int vcsd_alp_register_technology(const char* alp_name,
                                        vcsd_alp_data_t* alp_data);

/* Annotates the specified callback with information on thread-safety of the
 * callback. Returns 0 if successful or -1 otherwise. Note that alp_bits == 0
 * means that the callback is not thread-safe and should not be handled in any
 * special way; this is the default behaviour.
 */
extern int vcsd_alp_set_callback_bits(vcsd_handle vcs_handle,
                                      vcsd_var_consumer p_function, void* p_user_data, vcsd_alp_bits_t alp_bits);

/* Combination of vcsd_add_callback() and vcsd_alp_set_callback_bits(). May be
 * more efficient than if these two calls were executed separately.
 */
extern int vcsd_add_alp_callback(vcsd_handle vcs_handle,
                                 vcsd_var_consumer p_function, void* p_user_data, vcsd_alp_bits_t alp_bits);

/* Sends an arbitrary chunk of data to the specified ALP consumer. Returns 0 if
 * the data could not be sent (for example, the consumers have not yet been
 * created or the data chunk is too large); otherwise returns 1. Upon receiving
 * the message, the consumer ignores it if its on_message callback is NULL;
 * otherwise, it executes the callback function.
 *
 * data_ptr must be non-NULL if data_size is positive. data_size is the size
 * of the message to be sent. Note that data_size can't exceed the size of
 * the consumer's buffer; it's safe to assume that the limit is on the order
 * of 100 KB.
 */
extern int vcsd_alp_send_message(vcsd_alp_bits_t alp_consumer,
                                 const void* data_ptr, unsigned data_size);

/* Shuts down all active consumers created for the given ALP technology.
 * Sets alp_data->is_disabled to 1. Returns a binary OR of exit codes of
 * all consumer processes, or 0 if no consumers were active. Please note
 * that all consumers are automatically shut down at the end of simulation.
 */
extern int vcsd_alp_shutdown_consumers(vcsd_alp_data_t* alp_data);

/* Returns a non-NULL pointer to a working area created for the current
 * execution thread. If the working area didn't exist, it's allocated
 * with calloc(1, size) and initialized with init_fun(areaPtr) (if
 * init_fun==NULL, the second step is skipped). vc points to the data
 * passed to the callback function.
 *
 * Note: only one working area can be created per thread.
 */
extern void* vcsd_get_or_create_thsafe_area(vcsd_vc_record_t* vc,
                                            unsigned size, void (*init_fun)(void*));

/* Iterates over all working areas created for the design. Returns
 * a pointer to the next area or NULL if all areas have been visited.
 * *iter_aux must be set to 0 before the first call to this function.
 */
extern void* vcsd_iterate_over_thsafe_areas(int* iter_aux);

extern void vcsd_set_alpbits(unsigned alpbits);

extern int vcsd_compare_scope_handles(void *node1,void *node2);
extern bool vcsdIsSysvlogLang(void);
extern int vcsdIsV2KSVlogLang(void);
extern bool vcsd_is_low_power_assertion_checker(vcsd_handle vcs_scope_handle);
extern char* vcsd_get_power_scope_name(vcsd_handle vcs_scope_handle);
extern int vcsd_is_scope_protected(vcsd_handle vcs_scope_handle);
extern void* vcsd_check_aliased_var(vcsd_handle* p_vcs_handle,
                                    vcsd_var_consumer p_function,
                                    int* p_gate_opt);

extern void set_cm_userdata_for_lcovonly(vcsd_handle vcs_handle,void* user_data);
extern vcsd_handle vcsd_stim_handle(vcsd_handle vcs_handle);
extern int vcsd_get_bitselect_offset(vcsd_handle vcs_handle);

extern void  mt_fsdb_do_synch(void);
extern void  mt_pvpd_do_synch(void);
extern int   mt_fsdb_vcsd_is_paralleled(void);
extern void  mt_fsdb_check_thread_race(void);
extern int   mt_vcsd_add_callback ( vcsd_handle vcs_handle, vcsd_var_consumer
                                    p_function, void* p_user_data );
extern void* fh_get_dumpctrl(void);
extern int fh_process_dumpctrl(void);
extern void fh_flush_vpd(void* VpdHandle);
extern vcsd_ova_unit_info_t* vcsd_get_ova_unit_info_vir(void* vObj);
extern vcsd_handle getVcsdHandleFromMhpiHandle(void * mh);

extern int fThreadedPVPD;
extern void setMTPVPDStarted(int started);
extern unsigned int fNoCelldefinePli;
extern unsigned int fAllowCellPortPli;

#ifdef __cplusplus
}
#endif
#endif
