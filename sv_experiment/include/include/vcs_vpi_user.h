/*
 *  FileName: vcs_vpi_user.h
 *
 *  Facility: Verilog Compiled Simulator (VCS)
 *
 *  Functional Description:
 *      Defines vpi types and  routines that are not part of the OVI standard.
 *
 *  Notes:
 *      "sv_vpi_user.h" is included here (to get type definitions.)
 *
 *  Copyright (c) 1997-98 by Synopsys, Inc. All rights reserved.
 */

#ifndef VCS_VPI_USER_H
#define VCS_VPI_USER_H

#include "sv_vpi_user.h"
#ifdef __cplusplus
extern "C" {
#endif

/************** Objects added for System Verilog **********/
#define vpiChar              140 /* char data type */
#define vpiEnumConstant      158 /* enum constant */
#define vpiPortRefObj        162
#define vpiTfDecl            165
#define vpiEnumType      167
#define vpiInterfaceConn     172
#define vpiRefObjType        174
#define vpiRealWire          130
#define vpiBase          179
#define vpiInstances         180
#define vpiDerived       181
#define vpiMailbox       182
#define vpiSemaphore         183
#define vpiTypeDef           vpiTypedef
#define vpiBreakStmt         189
#define vpiContinueStmt      190
#define vpiProceedStmt       195
#define vpiImplicitImport    196
#define vpiExplicitImport    197
#define vpiUnitPackage       198
#define vpiActiveTag         1101
#define vpiSvNettype         1102
#define vpiVoidVar           1103
#define vpiInterconnectVar   1104
#define vpiInterconnectEle   1105
#define vpiIdentifier         679 /* moved from sv_vpi_user.h for tb debug */

#define vpiModPortPort vpiModportPort
#define vpiModPort     vpiModport
#define vpiSequenceExpr vpiExpr

#define vpiCharVar  vpiChar
#define vpiInt      vpiIntVar
#define vpiLongInt  vpiLongIntVar
#define vpiByte     vpiByteVar
#define vpiShortInt     vpiShortIntVar
#define vpiClass    vpiClassVar
#define vpiEnum     vpiEnumVar
#define vpiStructure    vpiStructVar
#define vpiUnion    vpiUnionVar
#define vpiLogic    vpiLogicVar

/************** Objects added for NTB GUI **********/
#define vpiVeraProgram       200

/*********************** properties added with System Verilog**************/
#define vpiMultiPacArray       73   /* multiple packed dimensions */
#define vpiExport              75   /* export task or function */
#define vpiExtern              76   /* extern task or function */
#define vpiExternForkJoin      77   /* extern fork join task or function */
#define vpiPacArray            78   /* packed dimensions */
#define vpiLifeTime        80
#define vpiStatic          81
#define vpiId                  84   /* thread/mailbox/semaphore id */
#define vpiThreadState         85   /* thread state subtypes: */
#define vpiCurrent               1  /* currently executing */
#define vpiReady                 2  /* ready to execute at current time */
#define vpiBlocked               3  /* blocked due to mailbox/semaphore/event */
#define vpiWaiting               4  /* waiting for child(ren) to finish */
#define vpiWaitingProcess      vpiWaitingProcesses /* to be removed */
#define vpiMessage             87   /* messages in mailbox */
/*#define vpiCastOp              90 */ /* Typecasting operator ' */
#define vpiDPIExtern           98
#define vpiDPIImport           99
#define vpiAccess             100    /* we have vpiAccessType already defined */
#define vpiBuiltIn            102
#define vpiSmartQueue          4

#define vpiInterfaceTask      108
#define vpiInterfaceFunction  109
#define vpiQueue              110
#define vpiUnnamed            111
#define vpiZombie             112
#define vpiTwoState           113

#define vpiHasImport          114   /* Instance has a package import */
#define vpiIsForced           685
#define vpiFullFile           686  /* Full path of vpiFile */
#define vpiDefFullFile        687  /* Full path of vpiDefFile */
#define vpiThis               688  /* "this" of a method */

#define vpiHasStrength        689  /* net supports strength values */


/************** Testbench interface **************/
#define vpiCreatedObjects     900  /* Total number of created objects from the start of the simulation. */
#define vpiDeletedObjects     901  /* Total number of deleted objects. */
#define vpiObjectCount        902  /* Total number of the live object for the given class definition handle.
                                      Objects, which are not reachable, but not yet deleted by garbage collector,
                                      are still counted here. */
#define vpiMaxId              903  /* Maximum object id allocated for a class. */
#define vpiLiveObjects        904  /* Iterate over all live objects of some class.
                                      There are 'vpiObjectCount' such objects. */

/* Information where when the object was created.
 * It is available only for '-debug_all' and provided for
 * "class obj" handles. */
#define vpiCreateFile         905
#define vpiCreateLine         906
#define vpiCreateScope        907
#define vpiCreateThread       908
#define vpiCreateTimeLow      909  /* Low word of object create time. */
#define vpiCreateTimeHigh     910  /* High word of object create time. */

#define vpiTestbenchInstance  911  /* Global relation, which allows iterate over all instances in the design,
                                      which have SVTB constructs. */
#define vpiObjectSize         912  /* Int property for "class obj" handle - size in bytes, occupied by the object. */



/************** Always Objects added for System Verilog **********/
#define vpiAlwaysFf                73   /* always_Ff */

#define vpiSignalDriver       74      /*signal driver = local signal driver + XMR */
#define vpiSignalLoad         75      /*signal driver = local signal load + XMR */
#define vpiRealDirection      22 /* Should give the real port direction taking care of port coercion */
#define vpiReaderExpr         76
#define vpiWriterExpr         77
#define vpiLocalSignalDriver  221      /*for local signal driver*/
#define vpiLocalSignalLoad    222      /*for local signal load*/
#define vpiAccDriver          223      /* Similar to vpiDriver, introduced for internal purposes */
#define vpiActualDriver       224      /* returns actual verilog driver handles of driver handle (vpiDriver), introduced for internal purposes */

#define vpiPortBitIndex       225
/* the bit index (from LSB) of a vpiPortBit handle */

/********* Assertion callback *************/

/* the following are for sequence end markers */
#define cbAssertionAttemptEndMarker 714
#define cbAssertionSeqInstEndMatched 714
#define cbAssertionAttemptMarker cbAssertionAttemptEndMarker
#define cbAssertionSeqInstMatched cbAssertionSeqInstEndMatched

/* the following are for sequence begin markers */
#define cbAssertionAttemptBeginMarker 716
#define cbAssertionSeqInstBeginMatched 716

/* the following is for sequence fail */
#define cbAssertionSeqInstFailed 717

#define cbAssertionAttemptRemoved 715

/*********** random init callback *********************/
#define cbRandomInitReadyToWrite 718   /* Ready for vpi write */
#define cbRandomInitCombPropagateStart 719 /* Phase 1 started */
#define cbRandomInitCombPropagateDone 720 /* Phase 1 finished */
#define cbRandomInitDone 721 /* random init done */



/********* Function Types added for System Verilog ********************/
#define vpiRegFunc      6
#define vpiSysIntFunc       7
#define vpiByteFunc     8
#define vpiCharFunc     9
#define vpiShortIntFunc     10
#define vpiLongIntFunc      11
#define vpiBitFunc      12
#define vpiLogicFunc        13
#define vpiStringFunc       14
#define vpiTypeSpecFunc     15
#define vpiVoidFunc     16
#define vpiEventFunc        17

/********* Operation Subtypes added for System Verilog ***************/
#define vpiBitNandOp            49
#define vpiBitNorOp             50
#define vpiAndOp        77
#define vpiOrOp         78

/* LTL Operation subtypes added for p1800-2008 SVA implementation */

#define vpiStrongOp               1003
#define vpiWeakOp                 1004
#define vpiAnyedgeOp              97 /* edge or UnaryEdgeControlOpC */


/**********************************/

/******* Typespec object types added for System Verilog *************/
#define vpiMemberTypespec       216
#define vpiRegTypespec          220
#define vpiCharTypespec        1001
#define vpiIsRTConstraint      1002
#define vpiLPType              1003

/***** Constant type that also has a strength value *****/
/** Primarily used for constant to represent implicit  **/
/** driver on Tri0/Tri1 and Supply0/Supply1            **/
#define vpiStrengthConst    314

/*********Need to verify validity *********/
#define vpiArguments        303         /* Used by DVE SVA and walkers */
#define vpiAssertionType    304
#define vpiSequenceEvent            311
#define vpiIsValidForUniqFlow       313
/**********************************/

/****** added for Unique prior case *****/
#define vpiUniqPrior        1004
#define vpiUniqPriorDisable 1005
#define vpiUniqPriorEnable  1006

/******* added for ANALOG ************/
#define vpiModuleType           305
#define vpiDefaultModule        1
#define vpiAmsConnectModule     2
#define vpiSpiceModule          3
/**********************************/

/******* added for Magellan ************/
#define vpiBoundInst        311
/**********************************/

/******* added for DVE ************/
#define vpiDisplayName      609
/**********************************/

/******* cb extensions ************/
#define cbStmtAll               32
#define cbPreEndOfFrame     622 /* callback on pre frame exit */

#define vpiEndLineNo        800
#define vpiParameterTried   880
#define vpiParameterSuccess 881
#define vpiStringParameter  882

/******* added for constraints ************/
#define vpiConstrForeach        315

#define vpiEventClass                   52 /* related to vpiClassType */

#define vpiImplements                   1009
#define vpiImplementingClasses          1010
#define vpiInterfaceClass               6

/****** added for covergroups *************/
#define vpiCovergroup                   1011
#define vpiCoverpoint                   1012
#define vpiCovercross                   1013
#define vpiCoverbin                     1014
#define vpiCovergroupInst               1015
#define vpiIsClockedCovergroup          1016
#define vpiIsIllegalBin                 1017
#define vpiIsIgnoreBin                  1018
#define vpiGuardExpr                    1019
   
/*************** Properties added for Verilog-AMS Objects *************/
#define vpiDiscipline                   401
#define vpiNature                       402
#define vpiBranch                       403
#define vpiBranchBit                    404
#define vpiFlowQuantity                 405
#define vpiFlowQuantityBit              406
#define vpiPotentialQuantity            407
#define vpiPotentialQuantityBit         408
#define vpiAnalogNet                    409
#define vpiAnalogBitSelect              410
#define vpiAnalogFuncCall               411
#define vpiAnalogProcess                412
#define vpiAnalogPrimitive              413
#define vpiAnalogPrimitiveBit           414 /* may not be needed as spice doesn't support vectors */
#define vpiFlowNature                   415
#define vpiPotentialNature              416
#define vpiChild                        418
#define vpiPosNode                      419
#define vpiNegNode                      420
#define vpiPotential                    421 /* redundant w.r.t vpiPotentialQuantity */
#define vpiFlow                         422 /* redundant w.r.t vpiFlowQuantity */
#define vpiContrib                      423
#define vpiSource                       424
#define vpiEquationTarget               425
#define vpiDomain                       427
#define vpiContinuous                   428
#define vpiDiscrete                     429
#define vpiAnalogPartSelect             430
#define vpiAnalogNetBit                 431
#define vpiBranchPartSelect             432
#define vpiFlowQuantityPartSelect       433
#define vpiPotentialQuantityPartSelect  434

/***************************** Configure Types *****************************/
/* 0-6 was defined in lib/vpi_user.h */
#define vpiUseClassObject    7
#define vpiEnableSVCoverGroup 11

#define vpiRealCellInstance             18
#define vpiPassByRef                    6  /* return type for vpiDirection */
/* not defined in the LRM */
/* should alias to vpiRef as
   defined in the LRM */

#define vpiValueInfoVal                 25
#define vpiIPVal                        26 /* Synopsys Internal use
                                              for valueFormat*/

#define vpiAggregateVal                 14 /* ???? mdb/vlexprval stim */

/************************** vpi_register_systf **************************/
#define cbRegisterSysTf                300 /* Used internally, change to */
/* 300 to resolve conflict    */
/* with cbNBASynch            */

typedef struct t_vpi_analog_value {
    int format; /*vpiRealVal, vpiExpStrVal, vpiDecStrVal, vpiStringVal */
    union {
        char *str;
        double real;
        char *misc;
    } real;
    union {
        char *str;
        double real;
        char *misc;
    } imaginary;
} s_vpi_analog_value, *p_vpi_analog_value;

typedef struct t_vpi_stf_partials {
    int count;
    int *derivative_of; /* 0 = returned value, 1 = 1st arg, etc. */
    int *derivative_wrt; /* 1 = 1st arg, 2 = 2nd arg, etc. */
} s_vpi_stf_partials, *p_vpi_stf_partials;

typedef struct t_vpi_systf_analog_data {
    int type; /* vpiAnalogSysTask, vpiAnalogSysFunc */
    int sysfunctype; /* vpi[IntFunc, RealFunc] */
    char *tfname; /* first character shall be "$" */
    int (*calltf)();
    int (*compiletf)();
    int (*sizetf)(); /* for vpiSizedFunc system functions only */
    char *user_data;
} s_vpi_analog_systf_data, *p_vpi_analog_systf_data;

/**************** internal functions for Slave Master Implementation */
extern vpiHandle vpi_put_value_sm(vpiHandle object, p_vpi_value value_p,
                                  p_vpi_time time_p, PLI_INT32 flags);
/**************** internal functions for NTB, used by UCLI           */
extern vpiHandle vpi_handle_frame(vpiHandle tf, int fid, int tid);


/*********************************************************/
/*    Get the time elapsed since the previous solution   */
/*********************************************************/
extern double vpi_get_analog_delta(void);

/************************************************************/
/* Get the frequency for the current small signal analysis  */
/************************************************************/
extern double vpi_get_analog_freq(void);

/************************************************************/
/* Get the time of the current solution.                    */
/************************************************************/
extern double vpi_get_analog_time(void);

/**************************************************************/
/* Retrieve the simulation value of an analog quantity object */
/**************************************************************/
extern void vpi_get_analog_value(vpiHandle obj,
                                 p_vpi_analog_value  value_p);

/**************************************************************/
/* Set the simulation value of an analog quantity object      */
/**************************************************************/
extern vpiHandle vpi_put_analog_value(vpiHandle obj,
                                      p_vpi_analog_value  value_p,
                                      double time,
                                      int flags);

/**************************************************************/
/* Retrieve information about a user-defined analog system    */
/* task or function-related checback.                         */
/**************************************************************/
extern void vpi_get_analog_systf_info(vpiHandle obj,
                                      p_vpi_analog_systf_data systf_data_p);

/**************************************************************/
/* Register callbacks for user-defined analog system tasks or */
/* functions.                                                 */
/**************************************************************/
extern vpiHandle vpi_register_analog_systf(
    p_vpi_analog_systf_data systf_data_p);

typedef int (*cons_fptr)(p_cb_data);
/**************************************************************/
/* Check the existence of value change callback for VPI       */
/**************************************************************/
extern char* vpi_check_cb(vpiHandle h, cons_fptr consumer);

extern int vpi_can_expand_vector(vpiHandle h);

/**************************************************************/
/* help routine for fetch acc handle use vpi_* routine        */
/**************************************************************/
extern void push_third_party_acc(void);
extern void pop_third_party_acc(void);

/**************************************************************/
/* Get the replicated package context ID for MTS              */
/**************************************************************/
extern int vcsGetMtsContextId(void);

/**************************************************************/
/* Set vpi_iterator LP filter flag                            */
/**************************************************************/
extern void vpi_iterator_SetLPFilter(int i);

/**************************************************************/
/* Get LP design flag                                         */
/**************************************************************/
extern int vpi_GetLPDesignFlag(void);
extern int vpi_GetCpfDesignFlag(void);


/***************  SVA 3.1 definitions **************/
/********* Internally used by DVE routines *********/
/********* for registering callbacks on local vars */
/********* Values not conflicting ******************/
#define cbAssertionLocalVarCreated  720
#define cbAssertionLocalVarDuplicated   721
#define cbAssertionLocalVarUpdated  722
#define cbAssertionLocalVarDestroyed    723

/*********************** properties for MHDL **************/
#define vpiHasGenerate        1020

#define vpiDebugAccess        1021
#define vpiDebugAll           1023
#define vpiAccessUnnamedScopes 1024


/* Boolean property on vpiHandle:
 * If true, then the handle is a signal, which is directly connected to
 * some UPF driver (e.g. isolation strategy or SRSN).
 * It is returned together with other drivers during static driver tracing when 
 * vpi_configure(vpiFindLowPowerDrivers, "true") was called. */
#define vpiLowPowerDriver     1022


/* Property for VPI handle: basic block id for the corresponding statement. 
 * Available only by '-debug_access+reverse (used for reverse debug). */ 
#define vpiBasicBlock 1030


/* vpi_handle(vpiCopyIterator, iter) will make a copy of 'iter. 
 * This can be useful when we need to iterate over iterator, 
 * but leave the original iterator unchanged. */
#define vpiCopyIterator 1031


#ifdef VCS_ARGS_DEFINED_HERE
#undef VCS_ARGS_DEFINED_HERE
#undef VCS_ARGS
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VCS_VPI_USER_H */
