/*
** vim: set sw=4 expandtab:
*******************************************************************************
* Copyright 2000 Synopsys, Inc. All rights reserved.
*
*   This Program is an unpublished work fully protected by the United States
*  copyright laws and is considered a trade secret belonging to Synopsys,
*  Inc. It is not to be divulged or used by parties who have not received
*  written authorization from Synopsys, Inc.
*
*                              W A R N I N G
*
*   THIS SOFTWARE AND MANUAL ARE BOTH PROTECTED BY UNITED STATES COPYRIGHT
*   LAW (TITLE 17, UNITED STATES CODE). UNAUTHORIZED REPRODUCTION AND/OR
*   SALES MAY RESULT IN IMPRISONMENT OF UP TO ONE YEAR AND FINES OF UP TO
*   $10,000 (17 USC 506). COPYRIGHT INFRINGERS MAY ALSO BE SUBJECT TO CIVIL
*   LIABILITY.
*
*  Synopsys, Inc.
*  8 Pine Tree Drive Suite 140
*  Arden Hills, MN 55112
*  651-766-2400
*  Fax 651-766-2494
*******************************************************************************
*/

/** @file
 * This contains the public interface to HF.
 */

#ifndef _hfapi_h
#define _hfapi_h

#include "hftypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* for exporting functions in a win32 dll */
#ifdef _WINDOWS
#define DLLEXP __declspec(dllexport)
#else
#define DLLEXP /*Nothing*/
#endif

/** This gets the HF version as a string. */
extern DLLEXP const char*   hfGetVersionStr         ( void );

/* error-handling prototypes */

/** This global variable holds the error code for the most recent API
 * function. */
extern int  hfErrorNumber;
/** This function is used to return a string containing the error message. */
extern DLLEXP char*  hfGetErrorMessage(int ErrorNumber);
extern DLLEXP void  hfGetLineTraceStats (int Flag);

/* file/design prototypes */

/** This function is provided to verify the given file name is a valid
 * VCD+ file. */
extern DLLEXP int       hfFileIsValid           (char* szName, int iFileLockFlag, char** ppDataTypeString);
/** This function is used to open a VCD+ file for reading or writing. */
extern DLLEXP hfHandle  hfFileOpen              (char* szName, const char* szMode, int fileLockFlag);
/** Prototype of callback function used in hfRegFileOpenFunc(). */
typedef void            (*hfFileOpenCBFunc)     (hfHandle hFile, void* pUserData );
extern DLLEXP void      hfRegFileOpenFunc       (hfFileOpenCBFunc pFunc, void* pUserData);
/** This function is used to close a VCD+ file. */
extern DLLEXP void      hfFileClose             (hfHandle hFile);
/** Prototype of callback function used in hfRegFileCloseFunc(). */
typedef void            (*hfFileCloseCBFunc)    (hfHandle hFile, void* pUserData );
extern DLLEXP void      hfRegFileCloseFunc      (hfHandle hFile, hfFileCloseCBFunc pFunc,
                                                 void* pUserData);

/* Two interfaces to file switching.
 *
 * The plain one does a lot for you implicitly; it is the recommended one when
 * you don't need to control the file name too closely.
 *
 * The *Named one lets you suggest a name (or, if NULL, leave it to HF to
 * decide), and in any case you get a static string back, with the chosen name.
 * The string is good until the next call to either routine.
 */
extern DLLEXP void      hfFileSwitch            (hfHandle hDesign);
extern DLLEXP const char* hfFileSwitchNamed     (hfHandle hDesign,
                                                 char const* szNewName);

/* @note the next 5 calls must be made just after hfFileOpen has been called. */
/** This function is used to specify the maximum size of the VCD+ file. */
extern DLLEXP void      hfFileSetLimit          (hfHandle hFile, UINT64 ulLimit);
extern DLLEXP void      hfFileSetSwitchLimit    (hfHandle hDesign, UINT64 ulLimit);
/** This function is used to specify the size of the value change
 * block (VCB). */
extern DLLEXP void      hfFileSetVCBLimit       (hfHandle hFile, unsigned int nLimit);
/** This function is used to set the simulation time-scale precision
 * used by the VCD+ file to store value change data. */
extern DLLEXP void      hfFileSetPrecision      (hfHandle hFile, int iPrecision);
/** Sets the time unit value to be stored in the VCD+ file. */
extern DLLEXP void      hfFileSetTimeUnit       (hfHandle hFile, int iTimeUnit);
/** This function is used to set the data type string within the VCD+
 * file. */
extern DLLEXP void      hfFileSetDataTypeString (hfHandle hFile, const char* pDataTypeString);

/** This function is used to lock a file prior to reading that file. */
extern DLLEXP void      hfFileSetReadLock       (hfHandle hFile);
/** This function is used to unlock a previously locked VCD+ file using
 * the hfFileSetReadLock function. */
extern DLLEXP void      hfFileClearReadLock     (hfHandle hFile);
/** This function is used to return current status information about the
 * VCD+ file. */
extern DLLEXP int       hfFileStatus            (hfHandle hFile, eHfFileStatus Status);
/** This function is used to access the simulation time-scale precision
 * specified in the VCD+ file. */
extern DLLEXP int       hfFileGetPrecision      (hfHandle hFile, int* pPrecision);
/** This function is used to access the simulation time-scale units
 * specified in the VCD+ file. */
extern DLLEXP int       hfFileGetTimeUnit       (hfHandle hFile, int* pTimeUnit);
/** Get the data type string from the Design structure. */
extern DLLEXP int       hfFileGetDataTypeString (hfHandle hFile, char** ppDataTypeString);

#define dHfLanguageVerilog      0x80000000
#define dHfLanguageVHDL         0x40000000
#define dHfLanguageSysemC       0x20000000
#define dHfLanguageNanosim      0x10000000

extern DLLEXP void          hfFileAddLanguageTypes  (hfHandle hFile, unsigned int uLanguageBits );
extern DLLEXP unsigned int  hfFileGetLanguageTypes  (hfHandle hFile );

extern DLLEXP void      hfFileSetUserData       (hfHandle hFile, void* pData);
extern DLLEXP void*     hfFileGetUserData       (hfHandle hFile);

/** The function hfGetDesignHandle is used to obtain the handle of the
 * design that the givenobject is part of. */
extern DLLEXP hfHandle  hfGetDesignHandle       (hfHandle hObject);

extern DLLEXP void      hfCopyBackPvpdData      ( hfHandle vpDesign);
extern DLLEXP void      hfCopyForthPvpdData     ( hfHandle vpDesign);

/** Option defines used by the set/retrieve options protypes. */
#define hfOptionAutomaticDeltaCycles    0x1
#define hfOptionDisplayMetrics          0x2
#define hfOptionRemoveCurValueInVCB     0x4
#define hfOptionRemoveVCBResizeMessages 0x8
#define hfOptionMemoryLimit             0x20
#define hfOptionDoNotFreeMemoryOnCloseFlag  0x40 /* Do not free memory when hfFileClose is called.
** Only use on write when ** program is about to exit
** anyway. */
#define hfOptionNoReadOptimizationFlag  0x80    /* No longer can be disabled. */
/* Will be removed in future versions. */
/* Option set/retrieve options protypes. */

/** This function sets the current option value for this design. */
extern DLLEXP void          hfSetOptions        (hfHandle hFile, unsigned int OptionFlags);
/** Get the options as previously set by hfSetOptions. */
extern DLLEXP unsigned int  hfGetOptions        (hfHandle hFile);
/** This function is used to control how compression is used within the
 * VCD+ file. */
extern DLLEXP void          hfSetCompressOptions    (hfHandle hFile, unsigned int uCompressSelect,
                                                     unsigned int uCompressEffort);
extern DLLEXP void          hfSetMaxScopesInMemory (hfHandle hFile, unsigned int uLimit, int iUseHandles);
extern DLLEXP unsigned int  hfGetMaxScopesInMemory (hfHandle hFile);

/* Event prototypes */

/** Add an Event name to the design. */
extern DLLEXP unsigned int  hfAddEventName      (hfHandle hFile, char* szName);
extern DLLEXP unsigned int  hfGetEventFromName  (hfHandle hFile, char* szName);
/** This function is used to retrieve the character string associated
 * with the specified value for this event. */
extern DLLEXP char*         hfGetEventName      (hfHandle hFile, unsigned int nEvent);
/** This function returns a handle to the next event value. */
extern DLLEXP hfHandle      hfNextEventName     (hfHandle hFile, hfHandle hItem, unsigned int* pEventValue,
                                                 char** ppEventName);
/** Encoding types prototypes */

/** This function is used to create a user-defined encoding type. */
extern DLLEXP unsigned int  hfAddEncodingType   (hfHandle hFile, const char* szName, unsigned int nSize);
/** This function allows the user to specify a set of units for an
 * encoding type. */
extern DLLEXP void          hfAddEncodingUnit   (hfHandle hFile, unsigned int nEncoding, void* pDivisor,
                                                 char* szName);
/** This function is used to define value/string pairs for an encoding type. */
extern DLLEXP void          hfAddEncodingValStr (hfHandle hFile, unsigned int nEncoding, void* pValue, char* szName);


/** String handling protyptypes. */
extern DLLEXP unsigned int  hfSaveStringVal     (hfHandle hFile, char* szString);
extern DLLEXP char*         hfGetStringVal      (hfHandle hFile, unsigned int uStringVal);

/* hierarchy building prototypes */

/** This function is used to add a record to a scope or record. */
extern DLLEXP hfHandle hfAddRecord              (hfHandle hParent, char* szName);
extern DLLEXP hfHandle hfAddPackedRecord        (hfHandle hParent, char* szName, unsigned int nEncoding,
                                                 unsigned int nByteSize);
extern DLLEXP hfHandle hfAddPackedRecordAlias   (hfHandle hParent, hfHandle hMaster, char *szName);
/** This function is used to add a scope to a design or a parent scope. */
extern DLLEXP hfHandle hfAddScope               (hfHandle hParent, char* szName, unsigned int nEncoding,
                                                 unsigned int nByteSize);
/** This function is used to create a scope that is aliased to an
 * existing scope. */
extern DLLEXP hfHandle  hfAddScopeAlias         (hfHandle hParent, hfHandle hAliasScope);
extern DLLEXP hfHandle  hfAddSummaryVariable    (hfHandle hDesign, char* szName, unsigned int uValueByteSize,
                                                 unsigned int uOptions );
/** This function is used to create a expanded variable record. */
extern DLLEXP hfHandle hfAddExpandedVariable    (hfHandle hParent, char* szName );
/** This function is used to add a variable to a scope. */
extern DLLEXP hfHandle hfAddVariable            (hfHandle hScope, char* szName, unsigned int iEncoding,
                                                 unsigned int nSize);
/** This function is used to create a new variable and equate value
 * changes to a previously defined variable. */
extern DLLEXP hfHandle hfAddVariableAlias       (hfHandle hVariable, hfHandle hScope, char* szAlias);
extern DLLEXP hfHandle hfAddVariableGateAlias   (hfHandle hVariable, hfHandle hScope, char* szAlias, int isNot);
extern DLLEXP hfHandle hfAddVariableElement             (hfHandle hParent, unsigned int  iEncoding, unsigned int nSize);
extern DLLEXP hfHandle hfAddVariableAliasElement        (hfHandle hVariable, hfHandle hParent);
extern DLLEXP hfHandle hfAddVariableElementWithName     (hfHandle hParent, char* szName, unsigned int nEncoding,
                                                         unsigned int nSize);
extern DLLEXP hfHandle hfAddVariableAliasElementWithName        (hfHandle hVariable, hfHandle hParent, char* szName );
extern hfHandle        hfAddVCO                 (hfHandle hDesign, unsigned int uValueSize,
                                                 unsigned int uEncoding );


extern DLLEXP void              hfSetTotalScopeCount    (hfHandle hObject, unsigned int iScopeCount);
extern DLLEXP void      hfSetTotalVariableCount (hfHandle hObject, unsigned int VariableCount);
extern DLLEXP void      hfSetScopeComplete (hfHandle hObject);
extern DLLEXP void      hfSetAggregateComplete  (hfHandle hObject);
extern DLLEXP int       hfIsScopeComplete       (hfHandle hObject);

/** Attribute building prototypes */

/** This function is used to obtain the handle to an empty
 * attribute-list structure. */
extern DLLEXP hfHandle hfNewAttributeList       (hfHandle hObject);
extern DLLEXP void      hfAddAttribute          (hfHandle hAttributeList, const char* szName, unsigned int nSize,
                                                 void* pValue);
extern DLLEXP void      hfAddAttributeList      (hfHandle hObject, hfHandle hAttributeList);
extern DLLEXP void      hfReleaseAttributeList  (hfHandle hAttributeList);

/* Delta Cycle support */

/** Prototype of callback function used in the functions below. */
typedef int             (*hfDeltaCycleChangeCBFunc) (hfHandle hFile, int iDeltaCycleOnFlag, void* pUserData );

extern DLLEXP void      hfRegDeltaCycleChangeCBFunc (hfHandle hFile, hfDeltaCycleChangeCBFunc pFunc,
                                                     void* pUserData);

/* In write mode we want to observe state changes.   This implementation of the
 * subscribe/publish pattern does not support multiple designs nor multiple
 * callbacks per design.
 */
typedef void (*hfDeltaCycleStateCB)( int capturing_deltas_0_or_1 );
extern DLLEXP void hfRegDeltaCycleStateCB( hfDeltaCycleStateCB );

/* Functions to enable/disable glitch filtering and glitch detection.
** NOTE: Glitch filtering is temporarily disabled when delta cycle is enabled.
**       Glitch detection is unaffected by delta cycle. */
extern DLLEXP void hfSetGlitchFiltering( hfHandle hDesign, int bOnOffFlag );
extern DLLEXP void hfSetGlitchDetection( hfHandle hDesign, int bOnOffFlag );

/** This function is used to turn on the storing of delta-cycle
 * time. */
extern DLLEXP void      hfDeltaCycleOn          (hfHandle hFile);
extern DLLEXP int      hfIsDeltaCycleOn          (hfHandle hFile);
/** This function is used to turn off the storing of delta-cycle
 * time. */
extern DLLEXP void      hfDeltaCycleOff         (hfHandle hFile);

extern DLLEXP unsigned int  hfGetDeltaCycleValue    (hfHandle hFile);

/** This function is used to set the current value of the delta
 * cycle. */
extern DLLEXP void          hfSetDeltaCycleValue    (hfHandle hFile, unsigned int DeltaCycleValue);

/* simulation data storage prototypes */

/** This function is used to return the recommended size needed for the
 * VCB. */
extern DLLEXP UINT64        hfGetMinValueBufferSize     (hfHandle hFile);
extern DLLEXP void          hfValueSetSimulationTime    (hfHandle hFile, tHfTime64* pTime);
extern DLLEXP void          hfValueStore                (hfHandle hObject, void* pValue);
extern DLLEXP void          hfValueEventMaskStore       (hfHandle hObject, unsigned int nEventValue,
                                                         void* pMaskValue, void* pValue,
                                                         int bDoAutoIncDc);
extern DLLEXP void          hfValueArrayEventMaskStore  (hfHandle hObject, unsigned int uEvent,
                                                         void* pMask, void *pValue, int bDoAutoIncDc,
                                                         unsigned int uOffset, unsigned int uRange );
extern DLLEXP void          hfValueStoreWDCAI           (hfHandle hObject, void* pValue);
extern DLLEXP void          hfValueTraceStore           (hfHandle hObject, unsigned int LineOffset);
extern DLLEXP void          hfValueEventStore           (hfHandle hObject, unsigned int nEventValue);
extern DLLEXP void          hfSummaryValueStore         (hfHandle hSummaryObject, hfHandle hScope,
                                                         void *pValue);
extern DLLEXP void          hfValueArrayStore           (hfHandle hObject, void* pValue,
                                                         unsigned int uOffset, unsigned int uRange);
extern DLLEXP void          hfValueArrayEventStore      (hfHandle hObject, unsigned int uOffset,
                                                         unsigned int uRange,
                                                         unsigned int uEventValue);

extern DLLEXP void          hfValueBufferFlush          (hfHandle hFile);


/* hierarchy retrieval prototypes */

/** Get the current number of scopes. */
extern DLLEXP unsigned int  hfGetCurrentScopeCount      (hfHandle hObject);
/** This function is used to determine the current number of variables
 * for a parent or for the whole design. */
extern DLLEXP unsigned int  hfGetCurrentVariableCount   (hfHandle hObject);
/** This function is used to determine the total number of child scopes
 * instantiated in the specified scope instance. */
extern DLLEXP unsigned int  hfGetTotalScopeCount        (hfHandle hObject, unsigned int* pScopeCount);
/** This function is used to determine the total number of variables
 * instantiated in the specified scope instance. */
extern DLLEXP unsigned int  hfGetTotalVariableCount     (hfHandle hObject, unsigned int* pVarCount);
/** This function is used to return the parent scope of a variable,
 * variable bit, record, or scope object. */
extern DLLEXP hfHandle      hfGetParent                 (hfHandle hObject);
/** This function is used to return the name of an object. */
extern DLLEXP char*         hfGetName                   (hfHandle hObject);
/** This function is used to return the refcount of an object. */
extern DLLEXP int           hfIsHandleValid             (hfHandle hObject);
extern DLLEXP hfHandle      hfGetHandle                 (hfHandle hScope, char* szName);
extern DLLEXP hfHandle      hfGetSummaryHandle          (hfHandle hFile, char* szName);
/** This function is used to determine the type of the given handle. */
extern DLLEXP eHfStructType hfGetHandleType             (hfHandle hScope);
/** This function returns a handle to the value change object associated
 * with the specified scope, variable, or variable element. */
extern DLLEXP hfHandle      hfGetReadObj                (hfHandle hObject);
extern DLLEXP hfHandle      hfGetVCO                    (hfHandle hObject);
extern DLLEXP unsigned int  hfGetEncodingBitSize        (hfHandle hFile, unsigned int nEncoding);
/** This function is used to return the encoding value given to the object. */
extern DLLEXP unsigned int  hfGetEncodingType           (hfHandle hObject);
/** This function is used to fetch the character string that contains
 * the name of this predefined or user-defined encoding type. */
extern DLLEXP char*         hfGetEncodingTypeName       (hfHandle hFile, unsigned int nEncoding);
/** This function is used to return the encoding value associated with
 * the given encoding name. */
extern DLLEXP unsigned int  hfGetEncodingTypeFromName   (hfHandle hFile, char* szName);
/** This function retrieves the character string associated with the
 * specified value for the given encoding type. */
extern DLLEXP char*         hfGetEncodingValStr         (hfHandle hFile, unsigned int nEncoding, void* pValue);
/** This function is used to return the number of bytes necessary to
 * encode or decode a single value change of the object. */
extern DLLEXP unsigned int  hfGetValueSize              (hfHandle hObject);
/** Fetch the hfHandle of an element in an array VCO. */
extern DLLEXP hfHandle      hfGetArrayElement           (hfHandle hVar, unsigned int Offset);

/** This function is used to return an attribute's size and value. */
extern DLLEXP unsigned int  hfGetAttribute              (hfHandle hObject, const char* szName, unsigned int* pnSize,
                                                         void** ppValue);

/* simulation data retrieval prototypes */

/** This function is used to retrieve the beginning simulation time
 * recorded in the VCD+ file. */
extern DLLEXP void          hfGetStartSimulationTime    (hfHandle hFile, tHfTime64* pTime);
/** This function is used to retrieve the last simulation time recorded
 * in the VCD+ file with the hfSetSimulationTime function. */
extern DLLEXP void          hfGetEndSimulationTime      (hfHandle hFile, tHfTime64* pTime);
extern DLLEXP void          hfGetCurrentSimulationTime  (hfHandle hFile, tHfTime64* pTime);

/** This function is used to fetch all of the variables and records
 * contained in a scope, expanded variable, or record. */
extern DLLEXP hfHandle      hfNextVariable          (hfHandle hParent, hfHandle hChild);

/** Prototype of callback function used in the functions below. */
typedef int             (*hfValueChangeCBFunc)          (void* pUserData1, void* pUserData2,
                                                         const tHfTime64* pTime, const unsigned char* pValue,
                                                         const unsigned int SwapFlag,
                                                         const unsigned int DeltaCycle,
                                                         const unsigned int Event);

/** Options defined to use with hfAddObjToValueChangeList()
 * OptionFlags argument. */
#define dHfReportLoopCountAsEvent           0x1
/* This option causes the registered callback routine to be called with a value
** change of the repeat count and EventValue == hfEventPatternLoopCount.  The
** Repeat count returned indicates the number of times to repeat the previous 2
** value changes.  Without this option set, the registered callback routine will
** just see the value change data unrolled.
*/
#define dHfReturnCurrentValueAtStartTime    0x2
/*  This option causes the registered callback routine to be called when the
**  start time specified has been reached, giving the current value for this
**  object. If this option is not set, the registered callback routine will be
**  first called with the first value change that occurs at or after the
**  specified start time.
*/
#define dHfReportEndOfVCBlock               0x4
/* When this option is set, the registered callback routine will be called with
** the event hfEventEndVCBlock at the end of each VCB.  Normally the registered
** callback routine is not notified when the end of the current VCB has been
** reached.
*/
#define dHfReportEndOfFileAsDumpOffEvent    0x8
/* When this option is set, the registered callback routine will be called with
** the event hfEventDumpOff when the end of the VPD file has been reached.
*/


/** Routine to be called for each object that value changes are needed for. */
extern DLLEXP void      hfAddObjToValueChangeList       (hfHandle hObject, hfValueChangeCBFunc pFunc,
                                                         tHfTime64 *pStartTime, unsigned int OptionFlags,
                                                         void *pUserData1, void *pUserData2);

extern DLLEXP void      hfAddObjToValueChangeList2      (hfHandle hObject, hfValueChangeCBFunc pFunc,
                                                         tHfTime64 *pEndTime, unsigned int uMinValChgs,
                                                         unsigned int OptionFlags, void *pUserData1,
                                                         void *pUserData2);

/** This function is used to register a callback routine to retrieve all
 * the scope trace information. */
extern DLLEXP int       hfAddTraceInfoToValueChangeList (hfHandle hFile, hfValueChangeCBFunc pFunc,
                                                         tHfTime64 *pStartTime, unsigned int OptionFlags,
                                                         void *pUserData1, void *pUserData2);

/** This function removes a callback that was previously registered by
 * the hfAddObjToValueChangeList() routine. */
extern DLLEXP void      hfRemoveObjFromValueChangeList  (hfHandle hObject, hfValueChangeCBFunc pFunc,
                                                         tHfTime64 *pStartTime, unsigned int OptionFlags,
                                                         void *pUserData1, void *pUserData2);

/** This function begins the process of fetching all of the value
 * changes for each object specified with the
 * hfAddObjToValueChangeList function. */
extern DLLEXP int   hfGetAllValueChanges            (hfHandle hFile);

/** Options defined to use with hfGetAllValueChangesInTimeOrder()
 * iFlags argument. */
#define dHfValueChangesWithDeltaCycle    0x1  /**< Currently unused. */

/** Allows hfGetAllValueChangesInTimeOrder() to be called multiple
 * times with the routine returning when the time is about to
 * advance. */
#define dHfValueChangesSuspendAtNewTime  0x2

/** This function begins the process of fetching in time order all of
 * the value changes for each object specified with the
 * hfAddObjToValueChangeList function. */
extern DLLEXP int   hfGetAllValueChangesInTimeOrder (hfHandle hFile, int iFlags);

extern DLLEXP void   hfReturnNowFmGetAllValueChangesInTimeOrder       (hfHandle hDesignL, unsigned int uFlags);

/** This function fetches the list of scope handles with trace
 * information for the given time. */
extern DLLEXP int   hfGetAllTraceInfo               (hfHandle hFile, hfValueChangeCBFunc pFunc,
                                                     tHfTime64* pStartTime,
                                                     void* pUserData1, void* pUserData2);

/* Next prototypes */

/** This function is used to fetch the scopes from a parent scope or the
 * top scopes of a design. */
extern DLLEXP hfHandle      hfNextScope             (hfHandle hParent, hfHandle hChild);
extern DLLEXP hfHandle      hfNextSummaryVariable   (hfHandle hParent, hfHandle hChild);
/** This function is used to fetch all of the attributes for a scope or
 * variable object. */
extern DLLEXP hfHandle      hfNextAttribute         (hfHandle hParent, hfHandle hChild, char** pszName,
                                                     unsigned int* pnSize, void** ppValue);
/** This function is used to fetch all the encoding types defined in
 * the VCD+ file, including the predefined encoding types. */
extern DLLEXP unsigned int  hfNextEncodingType      (hfHandle hFile, unsigned int nEncoding);
/** This function returns a handle to the next encoding unit. */
extern DLLEXP hfHandle      hfNextEncodingUnit      (hfHandle hFile, unsigned int nEncoding, hfHandle hItem,
                                                     void* pDivisor, char** pszName);
extern DLLEXP hfHandle      hfNextEncodingValStr    (hfHandle hFile, unsigned int nEncoding, hfHandle hItem,
                                                     void* pValue, char** pszName);

extern DLLEXP int           hfHasValueChangeData    (hfHandle hObject);

/** Functions used to iterate over the value change data of an object. */
/** NOTE: See hftypes.h file for structure and commands for hfGetIterValue
** function. */
extern hfHandle         hfGetReadIterator   ( hfHandle hObject );
extern int              hfGetIterValue      ( hfHandle hIter, tHfIterData* pIterData, eHfIterCmd eIterCmd );
extern hfHandle         hfFreeReadIterator  ( hfHandle hIter );

/*******************************************************************************
***@brief Returns a handle to be used by hfRefScpGet() to fetch the actual
*** handles of the interface or modport from the. This function return NULL if
*** the variable is not a refport.
*******************************************************************************/
extern hfHandle hfRefScpInit( hfHandle hRefVar );

/*******************************************************************************
***@brief Function performs the action specired by the "eCmd" argument.  See
*** table above for a description of each command.  Returns true if the action
*** was completed successfully.
*******************************************************************************/
extern int hfRefScpGet( hfHandle hRefIter, eRefScpIterCmds eCmd, unsigned int* pVal,
                        hfHandle* pHdl );

/*******************************************************************************
***@brief  Frees up the memory allocated for the iterator handle.
*******************************************************************************/
extern void hfRefScpDestroy( hfHandle hRefIter );


/** Misc. prototypes */
extern void                 hfSwapBytes             (unsigned int nBytes, void* pData);

/** @brief Utility to encode a command line (argc/argv) as a single buffer that
 *  can be passed as a value to hfAddAttribute.
 *
 *  If successful, the variables pointed to by the two last arguments can be
 *  used to define an attribute.  @sa hfArgsAttributeAsArray.
 *
 *  @return 0 if successful, <0 otherwise (in whose case neither *attValue nor
 *  *attSize are modified).
 *
 *  @param[in] argc Int, argument count.
 *
 *  @param[in] argv Pointer to array of NUL-terminated strings, where
 *  argv[0..argc-1] are the command line arguments to be encoded, and
 *  argv[argc] is 0.
 *
 *  @param[out] attValue Pointer to a pointer to void variable, through which a
 *  contiguous block allocated by mmMalloc will be returned.
 *
 *  @param[out] attSize Pointer to an unsigned int variable where the usable
 *  length of the array starting at attValue will be returned.
 */
#define dHfArgIsVHDLFlag    0x1
extern int hfArgsArrayAsAttribute( int           argc,
                                   char**        argv,
                                   void**        attValue,
                                   unsigned int* attSize,
                                   unsigned int  uOptions
                                 );

/** @brief Inverse of hfArgsArrayAsAttribute.  Allocates a char*[] array by
 *  mmMalloc; the array returned can be freed, but its contents should not!
 *
 *  If successful, the variables pointed to by the two last arguments can be
 *  used as if they came from main(int argc, char** argv).
 *
 *  @return 0 if successful, <0 otherwise (in whose case neither argc nor argv
 *  are modified).
 *
 *  @param[in] attValue Pointer returned by hfGetAttribute.
 *
 *  @param[in] attSize The value of the unsigned int returned by
 *  hfGetAttribute, cast to size_t to increase portability.
 *
 *  @param[out] argc Pointer to an int variable to contain the argument count.
 *
 *  @param[out] argv Pointer to a varible of type pointer to array of
 *  NUL-terminated strings, where argv[0..argc-1] are the command line
 *  arguments decoded from attValue, and argv[argc] is 0.
 */
extern int hfArgsAttributeAsArray( void const*  attValue,
                                   unsigned int attSize,
                                   int*         argc,
                                   char***      argv );

/** The following prototypes are just wrappers around renamed
** functions.  The names were changed to make the the names more
** meaningful.  Future versions of the code will eliminate these
** functions.
*/
/** Replaced by hfAddVariableElement() */
extern DLLEXP hfHandle hfAddVariableBit             (hfHandle hParent, unsigned int  iEncoding, unsigned int nSize);
/** Replaced by hfAddVariableAliasElement() */
extern DLLEXP hfHandle hfAddVariableAliasBit        (hfHandle hVariable, hfHandle hParent);
/** Replaced by hfAddVariableElementWithName() */
extern DLLEXP hfHandle hfAddVariableBitWithName     (hfHandle hParent, char* szName, unsigned int nEncoding,
                                                     unsigned int nSize);
/** Replaced by hfAddVariableAliasElementWithName() */
extern DLLEXP hfHandle hfAddVariableAliasBitWithName    (hfHandle hVariable, hfHandle hParent, char* szName );

/** Replaced by hfGetHandleType() */
#define hfGetType hfGetHandleType

/* NOTE: These functions are being removed from the source and no longer are supported. */

extern DLLEXP hfHandle  hfAddArrayRecord            (hfHandle hParent, char* szName, unsigned int NumElements);
extern DLLEXP unsigned int  hfGetArrayElementOffset (hfHandle hVar);
extern DLLEXP hfHandle  hfNextArrayElement          (hfHandle hParent, hfHandle hChild);

typedef void (*hfRecoverOnErr)(hfHandle);  /*user defined recovery function*/
void hfRegisterRecoverWrFunc(hfHandle hDesign, hfRecoverOnErr cb);
void hfRegisterRecoverRdFunc(hfHandle hDesign, hfRecoverOnErr cb);
extern DLLEXP void hfOnMemError(int size);  /* out of memory handler function*/

#ifdef __cplusplus
}
#endif

#endif
