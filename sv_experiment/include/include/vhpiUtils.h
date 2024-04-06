/*******************************************************************************
* File      : vhpiUtils.h
* Author    : Vipul Gupta
* Date      : 08/26/99
* Desc.     : This file contains declarations for all the Utility Functions
*             required for VhPLI.
********************************************************************************/
#ifndef _vhpi_Utils_h_
#define _vhpi_Utils_h_

#include "vhpi_user.h"
#include "vhpi_snps.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "tcl.h"

#ifdef __cplusplus
} /* end extern "C" */
#endif

#define vhpiMaxVectorSize 512

typedef enum {
    vhpiUtilFalse,
    vhpiUtilTrue
} vhpiStatus;

typedef enum {
    vhpiUtilAccessType = 0x1,
    vhpiUtilAliasType = 0x2,
    vhpiUtilArrayType = 0x4,
    vhpiUtilAttributeType = 0x8,
    vhpiUtilAttrSpecType = 0x10,
    vhpiUtilComponentType = 0x20,
    vhpiUtilCompositeType = 0x40,
    vhpiUtilConfigType = 0x80,
    vhpiUtilConstantType = 0x100,
    vhpiUtilConstParamType = 0x200,
    vhpiUtilElemType = 0x400,
    vhpiUtilEnumType = 0x800,
    vhpiUtilFileType = 0x1000,
    vhpiUtilFileParamType = 0x2000,
    vhpiUtilPackageType = 0x4000,
    vhpiUtilProcedureType = 0x8000,
    vhpiUtilRecordType = 0x10000,
    vhpiUtilSignalType = 0x20000,
    vhpiUtilSignalParamType = 0x40000,
    vhpiUtilSubType = 0x80000,
    vhpiUtilType = 0x100000,
    vhpiUtilVariableType = 0x200000,
    vhpiUtilVariableParamType = 0x400000
}vhpiUtilItemType;

typedef char vhpiCharT;

typedef enum {
    vhpiUtilFS=0,
    vhpiUtilPS,
    vhpiUtilNS,
    vhpiUtilUS,
    vhpiUtilMS,
    vhpiUtilSEC
}vhpiUtilTimeUnitsT;

#ifdef __cplusplus
extern "C" {
#endif

/* Defines a new command in the scirocco TCl interpreter with name cmdName.
   When the command is invoked cmdProc will be called with clientData as
   argument; if the command is ever deleted, deleteProc will be called */

void Scirocco_CreateCommand(char *cmdName, Tcl_CmdProc *cmdProc, ClientData clientData,
                            Tcl_CmdDeleteProc *deleteProc);

/* If cmdName is a command or a procedure in interp, then deletes it and
   returns 0, else returns -1 */

int Scirocco_DeleteCommand(char *cmdName);

void Scirocco_RenameCommand(char* oldname, char* newname);

/* If cmdName is a valid Scirocco UI command or a procedure in TCL, Scirocco will
   execute that command */

int Scirocco_ExecUICommand(char *cmdName);


/* Following function makes a copy of the string passed, and sets the prompt to it. */

void Scirocco_SetPrompt(char* promptString);

/* Method to check if scirocco is running with virsim GUI in interactive mode.
 * Returns 1 if in GUI mode, else returns 0. */

int Scirocco_VirsimInteractiveMode(void);

/* Following function suspends the simulation in the immediate next phase, after
 * executing events in the currently running queue. */

void Scirocco_SuspendNextPhase(void);

/* Following function returns the value of a setup variable.
 * Caller needs to copy the returned string. */

char* Scirocco_GetSetupValue(char* varName);

/* 2d parameter specification deliberatly moved to next line make easer
 * automatic mhdl dummy function generator implementation
 */
vhpiStatus vhpiUtil_dump_hierarchy_by_name(char *pathName,
                                           void (*user_func)(vhpiHandleT));

char* vhpiUtil_print_object_value(char *pathName);

char* vhpiUtil_print_object_value_at_vhdlIndex(char *pathName, int index);

vhpiStatus vhpiUtil_assign_object_value(char *pathName, char* Value, vhpiPutValueFlagsT flag);

vhpiStatus vhpiUtil_dump_items_by_name(char *pathName,
                                       vhpiUtilItemType itemType,
                                       void (*user_func)(vhpiHandleT));
vhpiStatus vhpiUtil_func_iterator_by_name(char *pathName, vhpiOneToManyT relation,
                                          void ((*user_func)(vhpiHandleT)));

vhpiStatus vhpiUtil_dump_value_change(char *pathName,
                                      void (*dump_func)(char* , char*, char*));

double vhpiUtil_time_to_double(vhpiTimeT, vhpiUtilTimeUnitsT);

vhpiTimeT vhpiUtil_double_to_time(double, vhpiUtilTimeUnitsT);
void vhpiUtil_ReportError(const char *msgStr);

void vhpiUtil_IncrUseCount(vhpiHandleT);

#ifdef __cplusplus
}
#endif  /* For extern "C" */
#endif
