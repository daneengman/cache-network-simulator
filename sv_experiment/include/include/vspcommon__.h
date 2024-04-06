/*
*******************************************************************************
*
* Copyright 2000 Synopsys, Inc. All rights reserved.
*
*  This Program is an unpublished work fully protected by the United States
*  copyright laws and is considered a trade secret belonging to Synopsys,
*  Inc. It is not to be divulged or used by parties who have not received
*  written authorization from Synopsys, Inc.
*
*                             W A R N I N G
*
*  THIS SOFTWARE AND MANUAL ARE BOTH PROTECTED BY UNITED STATES COPYRIGHT
*  LAW (TITLE 17, UNITED STATES CODE). UNAUTHORIZED REPRODUCTION AND/OR
*  SALES MAY RESULT IN IMPRISONMENT OF UP TO ONE YEAR AND FINES OF UP TO
*  $10,000 (17 USC 506). COPYRIGHT INFRINGERS MAY ALSO BE SUBJECT TO CIVIL
*  LIABILITY.
*
*  Synopsys, Inc.
*  8 Pine Tree Drive Suite 140
*  Arden Hills, MN 55112
*  651-482-1075
*  Fax 651-482-0394
*
*******************************************************************************
*/
#ifndef _vspcommon___h
#define _vspcommon___h

#include "hftypes.h"
#include "vcsd.h"

/*
****************************************************************************************************
*   Data structure definitions
****************************************************************************************************
*/

/*
****************************************************************************************************
*   Function Prototypes
****************************************************************************************************
*/
#if defined(__cplusplus)
extern "C" {
#endif

/* Prototypes for registering callbacks. */
typedef void (*tVspFileOpenCB) ( hfHandle hDesign );
typedef void (*tVspFileCloseCB) ( hfHandle hDesign );

/*  Defines used with the vspSetOption and vspClearOption functions below. */
#define dVspFileLock        0x1         /* Must be set prior to opening the VPD file. */
#define dVspExpandVectors   0x2         /* Causes all wire vectors to be expanded to scalar bits. */
#define dVspAllowIncrHierOpt 0x4
/* Allows Incremental hierarchy freeing
** to stay enabled when vspRegisterFileOpenCB() and
** vspRegisterFileCloseCB() are called */

/* Allow user to set a specific options.  The option will remain set for the rest
** of the program unless cleared with function vspClearOption().
*/
extern void             vspSetOption            ( unsigned int uOption );

/* mark hfOption to indicate finish of simulation, specially on MX design with VL top */
extern void             vspSetSimulationFinish (void);

/* Allow user to clear a specific options.  The option will remain set for the
** rest of the program unless set with function vspSetOption().
*/
extern void             vspClearOption          ( unsigned int uOption );

/* Allow user to fetch the state of all options.
*/
extern unsigned int     vspGetOption            ( unsigned int uOption );

/* Allow user to specify the VPD file size in megabytes, when to close the current
** VPD file and open a new VPD file with the same hierarchy included.  Please see
** documentation for runtime switch +vpdfileswitchsize+ for information.
** NOTE: This function must be called prior to calling vspFileOpen or allowing the
** VPD file to be opened by other means.
*/
extern void             vspSetFileSwitchSize    ( unsigned int uMegabyteSize );

/* Sets the VPD file name. It returns TRUE if successful else FALSE.
*/
extern int              vspSetVpdFileName       ( char* pName );

/* Return the VPD file name set by -vpd_file runtime argument or return an empty
** string.
*/
extern char*            vspGetRTVpdFileName       ( void );

/* Return the VPD file name used during save. */
extern char*            vspGetRestoreVpdFileName       ( void );

/* This function allows the application to include an attribute that is to be
** added to the VPD design handle.
*/
extern void             vspAddAttributeToVpd    (const char* sAttributeName,
                                                 const unsigned int iAttributeSize,
                                                 const void* pAttributeValue);
/* This function is called by the routine that first opens the VPD file and adds the attribute list to the
** design handle.  When VL is on top, this function is called by vcsdInitVcdPlus(), it should also be called
** by Scirocco when VHDL is on top.
*/
extern void             vspAddAttributes        ( hfHandle AttributeList );

/* This function creates a design handle if not already created
*/
extern hfHandle         vspFileOpen             ( void );

/* This function returns the current design handle. Could be NULL
*/
extern hfHandle         vspGetDesignHandle      ( void );

/* This function returns the scope hf handle corresponding to the given vcsd handle
*/
extern hfHandle         vspGetHfScopeHandle     ( vcsd_handle vScopeHandle );

/* This function registers a callback for closing a file.
*/
extern void             vspRegisterFileCloseCB  ( tVspFileCloseCB pFileOpenCB );

/* function to call to cause the VPD file to close.  Needed in the case when no $vcdplusXXX system tasks are
** in the source.
*/
extern void             vspFileClose            ( hfHandle hDesign );

/* This function redirects output to file named after its second argument (if
 * NULL, to a file named by HF), and returns a pointer to a static copy of the
 * file name actually used.  See hfFileSwitchNamed.
 */
extern char const* vspFileSwitch( hfHandle pDesign, char const* newName );

/* This function registers a callback for opening a file. The design handle is invalid after the pFileCloseCB
** function is called */
extern void             vspRegisterFileOpenCB   ( tVspFileOpenCB pFileOpenCB );

/* Update the VPD file to the current simulation time. */
extern void             vspUpdateSimulationTime ( void );
extern void             vspUpdateSimulationTimeWithTime(unsigned int uTime64, unsigned int uTime32);

/*  Update the VPF file to the simulation time based on provided value. */
extern void             vspUpdateSimulationTimeWithValue( hfHandle hDesign, tHfTime64* pNewTime );

/* Flushes any cached data to the VPD file. This function is equivalent to the system task $vcdplusflush
*/
extern void             vspValueBufferFlush     ( hfHandle hDesign );

/* The argument "portsflag" in the functions below is used to indicate internal
** signals and/or ports of the specified scope or variable are to be dumped.
*/
#define dAllPortsAndVars    0   /* Dump all ports and internal signals for specified scopes. */
#define dInPortsOnly        1   /* Dump only input ports. No internal signals. */
#define dOutPortsOnly       2   /* Dump only output ports. No Internal signals. */
#define dInoutPortsOnly     4   /* Dump only inout ports. No Internal signals. */
#define dAllPortsOnly       7   /* Dump only all ports. No Internal signals. */

/* NOTE: The defines dInPortsOnly, dOutPortsOnly, and dInoutPortsOnly can be
** OR'd together to dump any combination of these ports.  Currently there is no
** way to dump some ports and all internal signals.
*/

/* Allow the application to turn off value change recording for the specified
** scope or MDA variable. For MDA variables, iLevel is unused. For scopes, iLevel indicates
** the number of levels of hierarchy to descend. For example, a 1 would indicate
** turning off value change recording for all MDA variables contained in the
** specified scope instance. A 2 would indicate all MDA variables for the specified
** scope instance and all MDA variables for it's child scopes. A zero indicates turn
** value change recording off for all MDA variables below the specified scope
** instance to the leaf nodes.
*/
extern int              vspVcdPlusMemOff        ( int iLevel, vcsd_handle vScopeOrVariableHandle, int portsflag );

/* Allow the application to turn on value change recording for the specified
** scope or MDA variable. For MDA variables, iLevel is unused. For scopes, iLevel indicates
** the number of levels of hierarchy to descend. For example, a 1 would indicate
** turning on value change recording for all MDA variables contained in the
** specified scope instance. A 2 would indicate all MDA variables for the specified
** scope instance and all MDA variables for it's child scopes. A zero indicates turn
** value change recording on for all MDA variables below the specified scope
** instance to the leaf nodes.
*/
extern int              vspVcdPlusMemOn         ( int iLevel, vcsd_handle vScopeOrVariableHandle, int portsflag );

/* Allow the application to turn off value change recording for the specified
** scope or variable. For variables, iLevel is unused. For scopes, iLevel indicates
** the number of levels of hierarchy to descend. For example, a 1 would indicate
** turning off value change recording for all variables contained in the
** specified scope instance. A 2 would indicate all variables for the specified
** scope instance and all variables for it's child scopes. A zero indicates turn
** value change recording off for all variables below the specified scope
** instance to the leaf nodes.
*/
extern int              vspVcdPlusOff           ( int iLevel, vcsd_handle vScopeOrVariableHandle, int portsflag );

/* Allow the application to turn on value change recording for the specified
** scope or variable. For variables, iLevel is unused. For scopes, iLevel indicates
** the number of levels of hierarchy to descend. For example, a 1 would indicate
** turning on value change recording for all variables contained in the
** specified scope instance. A 2 would indicate all variables for the specified
** scope instance and all variables for it's child scopes. A zero indicates turn
** value change recording on for all variables below the specified scope
** instance to the leaf nodes.
*/
extern int              vspVcdPlusOn            ( int iLevel, vcsd_handle vScopeOrVariableHandle, int portsflag );

/* Allows an application to turn off value change recording for the ports of the
** specified scope instance similar in functionality to the system task
** $vcdplusdumportsoff.  iLevel indicates the number of levels of hierarchy to
** descend below the specified scope instance. For example, a 1 would indicate
** turning on value change recording for all ports contained in the specified
** scope instance. A 2 would indicate all ports for the specified scope instance
** and all ports for it's child scopes. A zero indicates turn value change
** recording on for all ports below the specified scope instance to the leaf
** nodes.
*/
extern int              vspVcdPlusDumpPortsOff  ( int iLevel, vcsd_handle vScope );

/* Allows an application to turn on value change recording for the ports of the
** specified scope instance similar in functionality to the system task
** $vcdplusdumportson.  iLevel indicates the number of levels of hierarchy to
** descend the specified scope instance. For example, a 1 would indicate turning
** on value change recording for all ports contained in the specified scope
** instance. A 2 would indicate all ports for the specified scope instance and
** all ports for it's child scopes. A zero indicates turn value change recording
** on for all ports below the specified scope instance to the leaf nodes.
*/
extern int              vspVcdPlusDumpPortsOn   ( int iLevel, vcsd_handle vScope );

/* Allow the application to add hierarchy to the VPD file without turning on any
** value recording.  iLevel indicates the number of levels of hierarchy to descend.
** For example, a 1 would indicate adding the hierarchy down to the specified scope
** instance and, if iIncludeVarsFlag is true, this scope instance's variables.
** An iLevel value of 2 would would include the specified scope instance's child
** scope instances and, if iIncludeVarsFlag is true, their variables also.  An iLevel
** value of 0 indicates to include all hierarchy below the specified scope instance.
** Variables would be included if iIncludeVarsFlag is true.
*/
extern int              vspVcdPlusAddHier       (int iLevel, int iIncludeVarsFlag, vcsd_handle vScopeHandle);

/* vspDisableAllCallbacks() traverses all current objects that are recording value change data and disables
** them.  It also writes the event hfEventDumpOff to indicate that value recording has been turned off.
*/
extern void             vspDisableAllCallbacks  ( hfHandle hDesign );

/* vspDeleteAllCallbacks() this is for abort condition to immediately delete all callbacks and free up memory*/
extern void             vspDeleteAllCallbacks   ( hfHandle hDesign );

/* vspEnableAllCallbacks() traverses all current objects that were recording value change data but were
** disabled by the function vspDisableAllCallbacks() and re-enables them.
*/
extern void             vspEnableAllCallbacks   ( hfHandle hDesign );

/* used by the -filter switch to elimate object types from the dump file
*/

#define AGGREGATES_FLAG       0x001
#define VARIABLE_DUMP_FLAG    0x002
#define GENERIC_DUMP_FLAG     0x004
#define CONSTANT_DUMP_FLAG    0x008
#define PACKAGE_DUMP_FLAG     0x010
#define PARAM_DUMP_FLAG       0x020
#define CELL_DEF_DUMP_FLAG    0x040
#define Y_CELL_DUMP_FLAG      0x080
#define SPECIFY_DUMP_FLAG     0x100
#define SUBCELL_DUMP_FLAG     0x200
#define REAL_DUMP_FLAG        0x400
#define PORTS_ONLY_FLAGS      (CELL_DEF_DUMP_FLAG | Y_CELL_DUMP_FLAG | SPECIFY_DUMP_FLAG)

/* flags for source of filter string for debugging & runtime/verilog task precidence */
#define ENV_VAR_FILTER        0x01000000
#define DUMP_FILTER_FILTER    0x02000000
#define DUMP_ADD_FILTER       0x04000000
#define RUNTIME_FILTER        0x08000000
#define VL_TASK_FILTER        0x10000000

extern int              vspGetDefaultDumpFilterFlags( void );
extern void             vspSetDefaultDumpFilterFlags( int flags );
extern int              vspGetCurrentDumpFilterFlags( void );
extern void             vspSetCurrentDumpFilterFlags( int flags );

#define IS_AGGREGATES_FLAG( x )  (AGGREGATES_FLAG &  x )
#define IS_VARIABLE_FLAG( x )    (VARIABLE_DUMP_FLAG &  x )
#define IS_GENERIC_FLAG( x )     (GENERIC_DUMP_FLAG &  x )
#define IS_CONSTANT_FLAG( x )    (CONSTANT_DUMP_FLAG &  x )
#define IS_PACKAGE_FLAG( x )     (PACKAGE_DUMP_FLAG &  x )
#define IS_PARAM_FLAG( x )       (PARAM_DUMP_FLAG &  x )
#define IS_CELL_DEF_FLAG( x )    (CELL_DEF_DUMP_FLAG &  x )
#define IS_Y_CELL_FLAG( x )      (Y_CELL_DUMP_FLAG &  x )
#define IS_SPECIFY_FLAG( x )     (SPECIFY_DUMP_FLAG &  x )
#define IS_SUBCELL_FLAG( x )     (SUBCELL_DUMP_FLAG &  x )
#define IS_REAL_FLAG( x )        (REAL_DUMP_FLAG & x )
#define IS_PORTS_ONLY_FLAGS( x ) (PORTS_ONLY_FLAGS &  x )

#define IS_ENV_VAR_FILTER( x )      (ENV_VAR_FILTER & x )
#define IS_DUMP_FILTER_FILTER( x )  (DUMP_FILTER_FILTER & x )
#define IS_DUMP_ADD_FILTER( x )     (DUMP_ADD_FILTER & x )
#define IS_RUNTIME_FILTER( x )      (RUNTIME_FILTER & x )
#define IS_VL_TASK_FILTER( x )      (VL_TASK_FILTER & x )

#ifdef XXDEBUG
extern int vspCall( int iTabDataValue );
extern int vspMisc( int Data, int iReason, int Param );
#endif

#if defined(__cplusplus)
}
#endif

#endif
