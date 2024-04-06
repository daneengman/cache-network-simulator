/*
*******************************************************************************
* Copyright 2009 Synopsys, Inc. All rights reserved.
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
*  700 E. Middlefield Road
*  Mountain View, CA
*******************************************************************************
*/

#ifndef __hfc_h
#define __hfc_h

/* Include files required by this header. */
#include "hfapi.h"
#include "hfattributes.h"
#include "vpi_user.h"

/* Insure these abbreviations are defined. UINT64 and INT64 are already defined
** in hftypes.h
*/
#ifndef UINT32
#define UINT32 unsigned int
#endif
#ifndef INT32
#define INT32 int
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
** Defines used by uFlags arguments below:
*/
#define dFlagClear  0x0000
#define dPortIn     0x0001
#define dPortOut    0x0002
#define dPortInOut  0x0003
#define dStateFlag  0x0004
#define dClockFlag  0x0008

typedef struct tHfcFileData
{
    hfHandle                hDesignH;
    UINT32                  uEventSaveState;
    UINT32                  uEventSaveStateWithMask;
    UINT32                  uEventForced;
    UINT32                  uEventForcedWithMask;
    UINT32                  uEventForcedDeposit;
    UINT32                  uEventForcedDepositWithMask;
    UINT32                  uEventValueRelease;
    UINT32                  uEventValueReleaseWithMask;
} sHfcFileData, *pHfcFileData;

typedef struct tHfcValue {
    UINT32*         pMask;
    p_vpi_vecval    pValue;
} sHfcValue, *pHfcValue;

typedef struct tHfcStateForceData
{
    tHfTime64       sValTime;
    UINT32          uValueWords;
    sHfcValue       sStateVal;
    bool            bForceDeposit;
    sHfcValue       sForceVal;
} sHfcStateForceData, *pHfcStateForceData;

//
// The type of value returned
//
typedef enum
{
    eHfcValue,
    eHfcStateValue,
    eHfcStateValueAndMask,
    eHfcForcedValue,
    eHfcForcedValueAndMask,
    eHfcRelease,
    eHfcReleaseMask,
    eHfcDumpOff
} eHfcValueType;

typedef int (*pHfcValueCB) (void* pUserData1, const tHfTime64* pTime,
                            eHfcValueType eValType, bool bForceDeposit,
                            UINT32 uValWordSize, pHfcValue pValue);


extern tHfcFileData sHfcEmptyFileDataG;

hfHandle hfcNextLeaf(hfHandle hObj, hfHandle hPrevLeaf, const char** pLeafName);
hfHandle hfcGetVarData( hfHandle hVar, UINT32* uFlags, UINT32* uBitSize );
void hfcAddObjToValueChangeList(hfHandle hLeafH, pHfcValueCB pValueCB,
                                tHfTime64* pValTime, void* pUserData, pHfcFileData pFileData);
void hfcGetAllValueChangesInTimeOrder( hfHandle hDesignH, int iFlags );

/*
********************************************************************************
** General information about the API.
** All string (char*) input parameters are copied to lcoal storage and are not
** freed by the API.
**
** At file close time all storage allocated by the API for the closed file is
** freed.
********************************************************************************
*/

/*
********************************************************************************
** hfcFileOpen: Opens a VPD file for either Save-State or Replay usage.  The
** return value is the handle of the opened VPD design and file.
**
** Params:
**   szFileName:    String giving the path and/or name of the VPD files to be
**                  written or read. The path may be relative or absolute.
**   pSzUserData    On open for write this string, if specified, is written to
**                  the dHfAttCongUserData attribue of the design handle. No
**                  interpretaion is done on the contents of the string. The
**                  writer application should put a tag at the start of the
**                  string to identify the writer and purpose of the rest of
**                  the information in the string. E.G. "Cong:Version xxxx".
**
**                  On open for read if the value is not NULL, then it will
**                  point to the first dHfCongAttUserData string contained
**                  in the opened file. If the attribute does not exist the
**                  return pointer will be NULL.
**   szMode:        String indicating how the VPD file should be opened.
**                  Possible values are:
**                  "sw" Save-State Write. Opened for writing Save-State VPD
**                       file. Previous file with the same name will be
**                       overwritten.
**                  "pw" Port Replay Write. Opened for writing Replay VPD file.
**                       Previous file with the same name will be overwritten.
**                  "sr" Save-State Read. File must exist and have been created
**                       with "Save-State Write".
**                  "pr" Port Replay Read. File must exist and have been created
**                       with "Replay Write".
********************************************************************************
*/
hfHandle hfcFileOpen( const char* szFileName, const char** pSzUserData, const char* szMode );

/*
********************************************************************************
** hfcFileTimeFormat: Specifies the how time is represented in the VPD file.
**
** Params:
**   hDesign:       Handle to VPD design returned by hfcFileOpen().
**   iUnit:         Specifies the time units when displaying time.
**   iPrecision:    Specifies the time precision when displaying time. This
**                  value is also used to indicate the unit value when calling
**                  hfcSetSimulationTime().
**  NOTE: Both iUnit an iPrecision accept the same values as specified for the
**  Verilog system task $timeformat().  Examples are:
**       0 == seconds
**      -9 == nanoseconds
**     -12 == picoseconds
**  The full table is given in the "IEEE std. spec 1364-2005", Table 17-10.
********************************************************************************
*/
void hfcFileTimeFormat( hfHandle hDesign, INT32 iUnit, INT32 iPrecision );

/*
********************************************************************************
** hfcAddScopeInst: Adds a scope instance to a parent scope instance.  If this
** scope instance is a top level scope, then hParent will be the handle of the
** VPD design.
**
** The return value is handle of this scope instance.  This handle is used for
** subsequent calls to other functions where this scope instance is the parent
** in the hierarchy.
**
** Params:
**   hParent:       Handle of the parent scope, or the handle of the VPD design
**                  if this scope instance is a top level scope.
**   szName:        String specifying the instance name of the scope.
**   uFlags:        Used to specify certain options about this object. Currently
**                  unused for this function call and should be set to zero.
********************************************************************************
*/
hfHandle hfcAddScopeInst( hfHandle hParent, char* szName, UINT32 uFlags );

/*
********************************************************************************
** hfcAddVariable: Adds a variable to a parent scope, struct, or Mda struct.  If
** this variable is global then the parent will be the handle of the VPD design.
**
** The return value is the handle of this variable and is used to record its
** saved-state, force, or replay value.
**
** Params:
**   hParent:       Handle of the parent scope, struct, or Mdastruct, or the
**                  handle of the VPD design if this variable is a global
**                  variable.
**   szName:        String specifying the name of the variable.
**   uFlags:        Used to specify certain options about this object. Valid
**                  options are:
**                  dPortIn     Specify variable is an input port.
**                  dPortOut    Specify variable is an output port.
**                  dPortInOut  Specify variable is an inout port.
**                  dStateFlag  Specify variable contains 1 or more bits of
**                              saved-state.
**                  dClockFlag  Specify variabel is a clock.
**  uBitSize:       Specifies the number of logical bits contained within
**                  this variable. The value must include all packed dimensions.
**                  For example:
**                  "logic [7:0] a;"        has a logical bit size of 8.
**                  "logic [7:0][1:3] b;"   has a logical bit size of 24.
********************************************************************************
*/
hfHandle hfcAddVariable( hfHandle hParent, char* szName, UINT32 uFlags,
                         UINT32 uBitSize );

/*
********************************************************************************
** hfcAddMdaVariable: Adds an Mda variable to a parent scope instance.  An Mda
** variable does not store value changes itself. But it does define the
** unpacked dimensions and the name of the Mda variable.
**
** The return value is the handle of this Mda variable.  This handle is used as
** the parent handle when calling hfcAddMdaElement().
**
** Params:
**   hParent:       Handle of the parent scope, struct,  Mda struct, or the
**                  handle of the VPD design if this variable is a global
**                  variable.
**   szName:        String specifying the name of the Mda variable.
**   uFlags:        Used to specify certain options about this object. Valid
**                  options are:
**                  dPortIn     Specify variable is an input port.
**                  dPortOut    Specify variable is an output port.
**                  dPortInOut  Specify variable is an inout port.
**   uElements:     Specifies the number of elements contained within this
**                  unpacked Mda. If one or more parents up the hierarchy path
**                  were created with hfcAddMdaStructInst(), this count must
**                  include elements created for those elements as well.
**   uBitSize:      Specifies the number of logical bits contained within each
**                  element of this MDA.  This argument is used the same as in
**                  hfcAddVariable().
**   uDimensions:   Specifies the number of unpacked dimensions for this
**                  variable.  This value may be 0 if all the unpacked
**                  dimenesions for this variable are defined in the parent(s)
**                  up the hierarchy path.
**   pLeftBounds:   Specifies a string containing all left bound indicies using
**                  a space character as a delimiter.  The indicies are recorded
**                  from left to right.  If uDimensions is 0, this argument is
**                  unused and can be set to NULL.
**   pRightBounds:  Specifies a string containing all right bound indicies using
**                  a space character as a delimiter.  The indicies are recorded
**                  from left to right.  If uDimensions is 0, this argument is
**                  unused and can be set to NULL.
**
**   Examples for uElements, uDimensions, pLeftBounds, and pRightBounds
**   logic [7:0] a [1:3][8:4];
**                  uElements == 15.
**                  uDimensions = 2.
**                  pLeftBounds = "1 8".
**                  pRightBounds = "3 4".
********************************************************************************
*/
hfHandle hfcAddMdaVariable( hfHandle hParent, char* szName, UINT32 uFlags,
                            UINT32 uElements, UINT32 uBitSize,
                            UINT32 uDimensions, char* pLeftBounds,
                            char* pRightBounds );

/*
********************************************************************************
** hfcAddMdaElement: Adds an element to an Mda variable created with
** hfcAddMdaVariable().  In the VPD file all unpacked dimensions are flattened
** into 1 dimension and the offset to the element is recorded instead of its
** name.
**
** The return value is the handle of this variable instance and is used to
** record the saved-state, force, or replay value of this element.
**
** Params:
**   hParent:       hfHandle of an Mda variable. Only Mda Variables can be the
**                  parent of elements.
**   uFlags:        Used to specify certain options about this object. Valid
**                  options are:
**                  dStateFlag  Specify variable contains 1 or more bits of
**                              saved-state.
**                  dClockFlag  Specify variabel is a clock.
**   uOffset:       Specifies the flattened offset value of this element within
**                  the unpacked MDA.
**  Example of converting from multiple dimensions to a flattened offest:
**      "logic aAry [1:4][8:5];" flattens to:
**              aAry[1][8] == Offset 0
**              aAry[1][7] == Offset 1
**              aAry[2][8] == Offset 4
**              aAry[4][6] == Offset 14
**              aAry[4][5] == Offset 15
********************************************************************************
*/
hfHandle hfcAddMdaElement( hfHandle hParent, UINT32 uFlags, UINT32 uOffset );

/*
********************************************************************************
** hfcAddStructInst: Adds a System Verilog struct to a parent scope, struct, or
** Mda struct.  If this struct is a top level struct, then the parent will be
** the hfHandle of the VPD design.
**
** The return value is hHandle of this struct.  This handle is used for
** subsequent calls to other functions where this struct instance is the parent
** in the hierarchy.
**
** Params:
**   hParent:       hfHandle of the parent scope, struct, Mda struct, or the
**                  hfHandle of the VPD design if this struct is a top level
**                  struct.
**   szName:        String specifying the struct instance name.
**   uFlags:        Used to specify certain options about this object. Valid
**                  options are:
**                  dPortIn     Specify variable is an input port.
**                  dPortOut    Specify variable is an output port.
**                  dPortInOut  Specify variable is an inout port.
********************************************************************************
*/
hfHandle hfcAddStructInst( hfHandle hParent, char* szName, UINT32 uFlags );

/*
********************************************************************************
** hfcAddMdaStructInst: Adds a struct with unpacked Mda dimensions.
**
** The return value is handle of this Mda struct.  This handle is used for
** subsequent calls to other functions where this Mda struct instance is the
** parent in the hierarchy.
**
** Params:
**   hParent:       hfHandle of the parent scope, struct, Mda struct, or the
**                  handle of the VPD design if this variable is a global
**                  Mda struct.
**   szName:        String specifying the instance name of the Mda struct.
**   uFlags:        Used to specify certain options about this object. Valid
**                  options are:
**                  dPortIn     Specify variable is an input port.
**                  dPortOut    Specify variable is an output port.
**                  dPortInOut  Specify variable is an inout port.
**   uElements:     Specifies the number of elements contained within this
**                  unpacked Mda. If one or more parents up the hierarchy path
**                  were created with hfcAddMdaStructInst(), this count must
**                  include elements created for those elements as well.
**   uDimensions:   Specifies the number of unpacked dimensions for this
**                  Mda struct.  This value may must be > 0.
**   pLeftBounds:   Specifies a string containing all left bound indicies using
**                  a space character as a delimiter.  The indicies are recorded
**                  from left to right.
**   pRightBounds:  Specifies a string containing all right bound indicies using
**                  a space character as a delimiter.  The indicies are recorded
**                  from left to right.
********************************************************************************
*/
hfHandle hfcAddMdaStructInst( hfHandle hParent, char* szName, UINT32 uFlags,
                              UINT32 uElements, UINT32 uDimensions,
                              char* pLeftBounds, char* pRightBounds );

/*
********************************************************************************
** hfcSaveStateValueStore: This function is used to store the saved state of a
** variable or Mda element created with hfcAddVariable() or hfcAddMdaElement()
** respectively.  This function can only be used for creating the saved-state
** VPD file.
**
** Params:
**   hObj:          hfHandle of object created with hfcAddVariable() or
**                  hfcAddMdaElement(). For both functions the argument
**                  iStateFlag must have been set.
**   pMaskArray:    A pointer to an array of UINT32 variables used as a mask to
**                  identify the bits that have saved-state.  The layout is the
**                  same as the "aval" portion of s_vpi_vecval where the first
**                  word of UINT32 is the least significant 32 bits of the
**                  vector.  The next word of UINT32 is the next least
**                  significant 32 bits.  The size of the array must large
**                  enough to cover all logical bits specified with "uBitSize"
**                  when creating hObj.
**                  NOTE: If all bits of the object have a saved-state, then
**                  the pMaskArray does not need to be included and the pointer
**                  can be set to NULL.
**   pStateValue:   A pointer to an array of s_vpi_vecval structures used to
**                  define the the saved-state of the object.  s_vpi_vecval is
**                  defined in the specification "IEEE std. spec 1364-2005",
**                  Figure 27-8 and specifies a aval/bval pair the defines the
**                  values for "0", "1", "X", and "Z".
********************************************************************************
*/
void hfcSaveStateValueStore( hfHandle hObject, UINT32* pMaskArray,
                             p_vpi_vecval pStateValue );

/*
********************************************************************************
** hfcForceValueStore: Used to record a force value on the variable or Mda
** element created with hfcAddVariable() or hfcAddMdaElement() respectively.
** The pMaskArray is used to indicate what bits of the variable or element are
** to be forced.  This function can be used for both creating the saved-state
** VPD file or the replay VPD file.
**
** Params:
**   hObj:          hfHandle of object created with hfcAddVariable() or
**                  hfcAddMdaElement().
**   uForceDepositFlag: Boolean flag set to true if this is a force deposit
**                      indicating it is a forced value change but will be
**                      released on the next value change. If this flag is
**                      false, the there must be call to hfcReleaseValueStore()
**                      to indicate when the variable is released.
**   pMaskArray:    A pointer to an array of UINT32 variables used as a mask to
**                  identify the bits that are forced.  The layout is the
**                  same as the "aval" portion of s_vpi_vecval where the first
**                  word of UINT32 is the least significant 32 bits of the
**                  vector.  The next word of UINT32 is the next least
**                  significant 32 bits.  The size of the array must large
**                  enough to cover all bits specified with "uBitSize" when
**                  creating hObj.
**                  NOTE: If all bits of the object are forced then the
**                  pMaskArray does not need to be included and the pointer
**                  set to NULL.
**   pForceValue:   A pointer to an array of s_vpi_vecval structures used to
**                  define the the forced value of the object.  s_vpi_vecval is
**                  defined in the specification "IEEE std. spec 1364-2005",
**                  Figure 27-8 and specifies a aval/bval pair the defines the
**                  values for "0", "1", "X", and "Z".
********************************************************************************
*/
void hfcForceValueStore( hfHandle hObj, UINT32 uForceDepositFlag,
                         UINT32* pMaskArray, p_vpi_vecval pForceValue );

/*
********************************************************************************
** hfcReleaseValueStore: Used to record a release has occured on a previously
** forced value on the variable or Mda element created with hfcAddVariable() or
** hfcAddMdaElement() respectively.  The pMaskArray is used to indicate what
** bits of the variable or element are to be released.  This function is only
** used for creating the replay VPD file.
**
** Params:
**   hObj:          hfHandle of object created with hfcAddVariable() or
**                  hfcAddMdaElement().
**   pMaskArray:    A pointer to an array of UINT32 variables used as a mask to
**                  identify the bits that are released.  The layout is the
**                  same as the "aval" portion of s_vpi_vecval where the first
**                  word of UINT32 is the least significant 32 bits of the
**                  vector.  The next word of UINT32 is the next least
**                  significant 32 bits.  The size of the array must large
**                  enough to cover all bits specified with "uBitSize" when
**                  creating hObj.
**                  NOTE: If all bits of the object are released then the
**                  pMaskArray does not need to be included and the pointer
**                  set to NULL.
********************************************************************************
*/
void hfcReleaseValueStore( hfHandle hObj, UINT32* pMaskArray );

/*
********************************************************************************
** hfcValueStore: Used to record a value change for a variable or Mda element
** created with hfcAddVariable() or hfcAddMdaElement() respectively.  This
** function is only used for creating the replay VPD file.
**
** Params:
**   hObj:          hfHandle of object created with hfcAddVariable() or
**                  hfcAddMdaElement().
**   pValue:        A pointer to an array of s_vpi_vecval structures used to
**                  define the the value change of the object.  s_vpi_vecval is
**                  defined in the specification "IEEE std. spec 1364-2005",
**                  Figure 27-8 and specifies a aval/bval pair the defines the
**                  values for "0", "1", "X", and "Z".
********************************************************************************
*/
void hfcValueStore( hfHandle hObj, p_vpi_vecval pValue );

/*
********************************************************************************
** hfcSetSimulationTime: Used to record the current simulation.  All subsequent
** calls to hfcSaveStateValueStore(), hfcForceValueStore(),
** hfcReleaseValueStore(), and hfcValueStore() use the specified time as the
** current simulation time.  This function can be used for both creating the
** saved-state VPD file or the replay VPD file.  Each call to the routine must
** specify a time greater than or equal to the previous call.
**
** Params:
**   hDesign:       Handled to VPD design returned by hfcFileOpen().
**   uTime:         Specifies the current simulation time in the units specified
**                  for the precision with hfcFileTimeFormat()
********************************************************************************
*/
void hfcSetSimulationTime( hfHandle hDesign, UINT64 uTime );

/*
********************************************************************************
** hfcGetFileData: Fills in the fields of the theFileData arguemnt.  This
** structure contains file/design level information needed to get the
** state information for signals within this design.
**
** Params:
**   hDesign:       Handled to VPD design returned by hfcFileOpen().
**   theFileData:   Return argument filled in by this call.  The memory for
**                  structure must be allocated be the user.  The fields of
**                  the structure are filled in by the call.
********************************************************************************
*/
void hfcGetFileData(hfHandle hDesign, tHfcFileData* theFileData);

/*
********************************************************************************
** hfcGetStateForceData: Used to get the state information for the given leaf
** signal handle.  The information it returned in the structure
** pStateForceData.  The pointers in the structure will point to temporary
** storage that may be overwritten by other hfc calls.  So this data should be
** copied to user storage if not used immediately.  A NULL value for a pointer
** fields indicates that data did not exist for the given signal.
**
** Params:
**   pStartTime:        Currently this should just be a pointer to an allocated
**                      hfTime64 structure with both fields set to 0.  This
**                      field is intended for future if we support having state
**                      information for multiple times stored in the
**                      save-state.vpd file.
**   pCurFileData       pointer to the structure filled in by calling
**                      hfcGetFileData.
**   hLeafH:            Handle to the leaf signal to get the state information
**                      for.
**   pStateForceData:   Return structure for the state information. The
**                      following fields are updated:
**                      sValTime        The actual simulation time the
**                                      information was written to the VPD file.
**                      uValueByteSize  The size of the value change in bytes.
**                      pStateMask      A pointer to the state mask if one
**                                      existed.
**                      pStateValue     A pointer to the state value if one
**                                      existed.
**                      pForceMask      A pointer to the force mask if one
**                                      existed.
**                      bForceDeposit   A flag that is true if this was a force
**                                      deposit value.
**                      pStateValue     A pointer to the force value if one
**                                      existed.
********************************************************************************
*/
const sHfcStateForceData* hfcGetStateForceData(tHfTime64* pValTime,
                                               pHfcFileData pFileData, hfHandle hLeafH);

/*
********************************************************************************
** hfcNextScope: Same as hfNextScope. returns the handle to the next child scope
** for the given parent handle.
**
** Params:
**   hParent:       Handled to parent to get child scopes from.
**   hPrevScope:    Handled to the last child scope returned from this function,
**                  or NULL if this is the first call for this parent.
********************************************************************************
*/
hfHandle hfcNextScope(hfHandle hParent, hfHandle hPrevScope);

/*
********************************************************************************
** hfcNextVariable: Same as hfNextVariable. returns the handle to the next child
** variable for the given parent handle.
**
** Params:
**   hParent:       Handled to parent to get child variables from.
**   hPrevVariable: Handled to the last child variable returned from this
**                  function, or NULL if this is the first call for this parent.
********************************************************************************
*/
hfHandle hfcNextVariable(hfHandle hParent, hfHandle hPrevVariable);

/*
********************************************************************************
** hfcFileClose: Closes the give file and frees up memory associated with that
** handle.
**
** Params:
**   hDesign:       Handled to VPD design returned by hfcFileOpen().
********************************************************************************
*/
void hfcFileClose(hfHandle hDesign);

/*
********************************************************************************
** Returns uElements for the handle.
********************************************************************************
*/
UINT32 hfcGetNumElements(hfHandle hObj);

#ifdef __cplusplus
}
#endif
#endif
