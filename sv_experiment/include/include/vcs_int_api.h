/*
 *  Copyright (c) 1997-98 by Synopsys, Inc. All rights reserved.
 */

#ifndef VCS_INT_API_H
#define VCS_INT_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * For Model Save/Restore
 */
int ModelSave(char* fileName);
int ModelRestore(char* fileName, unsigned clockTicks);
void    vcsArmAlwaysBlocks();
void    vcsDisarmAlwaysBlocks();

/*
 * For RandomInit
 */
int VcsRandomInit(unsigned clockTicks);
int VcsDisableFlopLatchOnlyWrites();
int VcsEnableFlopLatchOnlyWrites();

/*
 * For I/O Control
 */

/* System Task Handler */
typedef enum {
    TF_DISPLAY=1,
    TF_DISPLAYB,
    TF_DISPLAYH,
    TF_DISPLAYO,
    TF_FDISPLAY,
    TF_FDISPLAYB,
    TF_FDISPLAYH,
    TF_FDISPLAYO,
    TF_WRITE,
    TF_WRITEB,
    TF_WRITEH,
    TF_WRITEO,
    TF_FWRITE,
    TF_FWRITEB,
    TF_FWRITEH,
    TF_FWRITEO,
    TF_SWRITE,
    TF_SWRITEB,
    TF_SWRITEH,
    TF_SWRITEO,
    TF_MONITOR,
    TF_MONITORB,
    TF_MONITORH,
    TF_MONITORO,
    TF_FMONITOR,
    TF_FMONITORB,
    TF_FMONITORH,
    TF_FMONITORO,
    TF_STROBE,
    TF_STROBEB,
    TF_STROBEH,
    TF_STROBEO,
    TF_FSTROBE,
    TF_FSTROBEB,
    TF_FSTROBEH,
    TF_FSTROBEO,
    TF_STACK,
    ALL_SYS_TASKS
} SysTaskTypes;

typedef void (*sysTaskHandler)(
    SysTaskTypes stfIndex,
    const char* formattedDisplayText,
    const char* fileName,
    int lineNumber,
    const char* simulationTime);

int  VcsRegisterSysTaskHandler(sysTaskHandler fn);
int  VcsUnregisterSysTaskHandler(void);
int  VcsSetSysTaskFlags(int sysTaskIndex, int trapEnabled, int skipOutput);

/* Generic Log Handler */
typedef void (*logHandler)(
    const char* formattedDisplayText,
    const char* simulationTime);

int  VcsRegisterLogHandler(logHandler fn);
int  VcsUnregisterLogHandler(void);
int  VcsSetLogHandlerFlags(int skipOutput);

/* Info, Warning and Error Handler */
typedef enum {
    VcsMsgFatal = 0,
    VcsMsgError,
    VcsMsgWarning,
    VcsMsgLint,
    VcsMsgNote,
    VcsMsgInfo,
    VcsMsgNumSeverities
} VcsMsgSeverity;

typedef void (*iweHandler)(
    const char* code,
    VcsMsgSeverity severity,
    const char* formattedMessage,
    const char* fileName,
    int lineNumber,
    const char* simulationTime);

int  VcsRegisterIWEHandler(iweHandler fn);
int  VcsUnregisterIWEHandler(void);
int  VcsSetIWEHandlerFlags(int skipOutput);

/* Status flags */
int VcsHasSystemC(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VCS_INT_API_H */
