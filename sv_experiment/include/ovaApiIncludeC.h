#ifndef _OVA_API_INCLUDE_C_H
#define _OVA_API_INCLUDE_C_H
#include <stdio.h>
#include "vcsd.h"

#ifdef  __cplusplus
extern "C" {
#endif


/***************************************************************
 * OVA Client ID type
 ***************************************************************/
typedef unsigned int Ova_ClientID;

/***************************************************************
 * OVA Client ID Null value
 ***************************************************************/
#define OVA_CLIENTID_NULL 0

/***************************************************************
 * OVA Assertion ID type
 ***************************************************************/
typedef unsigned long Ova_AssertID;

/***************************************************************
 * OVA Assertion ID Null value
 ***************************************************************/
#define OVA_ASSERTID_NULL 0

/***************************************************************
 * OVA String Type
 ***************************************************************/
typedef char* Ova_String;


/***************************************************************
 * OVA Assertion Name type
 ***************************************************************/
typedef Ova_String Ova_AssertName;

/***************************************************************
 * OVA Source File Text Block type
 ***************************************************************/
typedef struct {
    Ova_String fileName;
    int startRow;
    int startColumn;
    int endRow;
    int endColumn;
} Ova_SrcFileBlock_s;
typedef Ova_SrcFileBlock_s* Ova_SrcFileBlock;


/***************************************************************
 * OVA Assertion Attempt ID type
 ***************************************************************/
typedef unsigned long Ova_AssertAttemptID;

/***************************************************************
 * OVA Assertion Attempt ID Null value
 ***************************************************************/
#define OVA_ASSERTATTEMPTID_NULL 5


/***************************************************************
 * OVA Assertion Clock ID type
 ***************************************************************/
typedef unsigned long Ova_AssertClockID;

/***************************************************************
 * OVA Assertion Clock ID Null value
 ***************************************************************/
#define OVA_ASSERTCLOCKID_NULL 0


/***************************************************************
 * Maximal number of events/actions in one event type
 ***************************************************************/
#define OVA_EVENTTYPE_WINDOW_SIZE 101


/***************************************************************
 * OVA Engine Event type
 ***************************************************************/
typedef enum {
    /* NOTE: This is NOT an event */
    OVA_ENGEVENT_FIRST = 100,

    OVA_ENGEVENT_ALL,
    OvaInitializeBeginEngE,       /* Initialization sequence began */
    OvaInitializeEndEngE,         /* Initialization sequence completed */
    OvaStartEngE,                 /* The engine started  */
    OvaResetBeginEngE,            /* Reset sequence began */
    OvaResetEndEngE,              /* Reset sequence completed*/
    OvaLoadBeginEngE,             /* Load sequence began */
    OvaLoadEndEngE,               /* Load sequence completed */
    OvaFinishEngE,                /* The engine finished (simend) */
    OvaTerminateBeginEngE,        /* Termination sequence began */
    OvaTerminateEndEngE,          /* Termination sequence completed */
    OvaErrorEngE,                 /* Unrecoverable error */

    /* NOTE: This is NOT an event */
    OVA_ENGEVENT_LAST
} Ova_EngEvent;


/***************************************************************
 * OVA Engine Action type
 ***************************************************************/
typedef enum {
    /* NOTE: This is NOT an event */
    OVA_ENGACTION_FIRST = OVA_ENGEVENT_FIRST + OVA_EVENTTYPE_WINDOW_SIZE,

    OvaResetEngA,                 /* Reset all engine states */
    OvaFinishEngA,                /* Finish execution (simend) */
    OvaTerminateEngA,             /* Terminate */

    /* NOTE: This is NOT an event */
    OVA_ENGACTION_LAST
} Ova_EngAction;


/***************************************************************
 * OVA Assertion Event type
 ***************************************************************/
typedef enum {
    /* NOTE: This is NOT an event */
    OVA_ASSERTEVENT_FIRST = OVA_ENGACTION_FIRST + OVA_EVENTTYPE_WINDOW_SIZE,

    OVA_ASSERTEVENT_ALL,
    OvaResetAssertE,              /* Terminate all evaluation attempts that are in progress */
    OvaNewAttemptStartAssertE,    /* New evaluation attempt started */
    OvaAttemptRemovedAssertE,     /* Evaluation attempt removed */
    OvaAttemptFailureAssertE,     /* Assertion match attempt failed */
    OvaAttemptSuccessAssertE,     /* Assertion match attempt succeded */
    OvaAttemptVacuousAssertE,     /* Assertion match attempt succeded vacuously */
    OvaAttemptMarkerE,            /* Assertion attempt crossed a marked transition */
    OvaDisableNewAttemptsAssertE, /* Generation of new evaluation attempts disabled */
    OvaEnableNewAttemptsAssertE,  /* Generation of new evaluation attempts enabled  */
    OvaAttemptKillAssertE,         /* Emitted when an attempt is killed by the userby calling OvaAttemptKillAssertA */
    OvaTransitionSuccessAssertE,         /*Transition to a state succeeded */
    OvaTransitionVacuousAssertE,         /*Transition to a vacuous succeeded state */
    OvaTransitionFailureAssertE,          /*Transition to a state failed*/
    OvaDisableNewAttemptsReportingAssertE, /* Generation of new attempt success/failure reporting disabled */
    OvaEnableNewAttemptsReportingAssertE, /* Generation of new attempt success/failure reporting enabled */
    OvaLocalVarCreatedAssertE,
    OvaLocalVarDuplicatedAssertE,
    OvaLocalVarUpdatedAssertE,
    OvaLocalVarDestroyedAssertE,
    OvaAttemptSeqFailE,

    /* NOTE: This is NOT an event */
    OVA_ASSERTEVENT_LAST
} Ova_AssertEvent;


/***************************************************************
 * OVA Assertion Action type
 ***************************************************************/
typedef enum {
    /* NOTE: This is NOT an event */
    OVA_ASSERTACTION_FIRST = OVA_ASSERTEVENT_FIRST + OVA_EVENTTYPE_WINDOW_SIZE,

    OvaResetAssertA,              /* Reset assertion */
    OvaDisableNewAttemptsAssertA, /* Do not make new attempts on the assertion */
    OvaEnableNewAttemptsAssertA,  /* Cancel the effect of OvaAssertDisableNewAttempts */
    OvaAttemptKillAssertA,        /* Kill an assertion attempt */
    OvaEnableTraceOnAssertA,            /* Enable tracing of an assertion attempt*/
    OvaDisableNewAttemptsReportingAssertA, /* disabling of new attempt success/failure reporting */
    OvaEnableNewAttemptsReportingAssertA, /* enabling of new attempt success/failure reporting */

    /* NOTE: This is NOT an event */
    OVA_ASSERTACTION_LAST
} Ova_AssertAction;


/***************************************************************
 * OVA User Data type
 ***************************************************************/
typedef const void *Ova_UserData;

/***************************************************************
 * OVA User Data Null value
 ***************************************************************/
static const Ova_UserData OVA_USERDATA_NULL = NULL;


/***************************************************************
 * OVA Time type
 ***************************************************************/
/*String representation of simulation time.*/
typedef char* Ova_Time;


/*Long representation of simulation time. */
#ifdef WIN32
typedef unsigned __int64  Ova_TimeL;
#else
typedef unsigned long long Ova_TimeL;
#endif



/***************************************************************
 * OVA Boolean type
 ***************************************************************/
typedef enum {
    OVA_FALSE,
    OVA_TRUE
} Ova_Bool;


/***************************************************************
 * OVA Expression type
 ***************************************************************/
typedef enum {
    OVA_OVA_EXPR_TYPE,
    OVA_CHECK_EXPR_TYPE,
    OVA_FORBID_EXPR_TYPE,
    OVA_COVER_EXPR_TYPE,
    OVA_COVER_NOT_EXPR_TYPE
} Ova_ExprType;

/***************************************************************
 * OVA Assertion Syntax Info type
 * NOTE: Exact composition TBD
 ***************************************************************/
typedef struct {
    Ova_AssertName name;
    Ova_ExprType exprType;
    Ova_SrcFileBlock srcBlock;
    unsigned int severity:8,    /* severity level assigned for assertion */
             category:24;   /* category assigned for assertion */
    Ova_String scopeName;
    Ova_String userMsg;         /* user defined message for assertion
                                 (second argument value for check/forbid */
} Ova_AssertSyntaxInfo_s;
typedef Ova_AssertSyntaxInfo_s* Ova_AssertSyntaxInfo;

#define OVA_ASSERTSYNTAXINFO_NULL 0

/***************************************************************
 * OVA Assertion Attempt Syntax Info type
 * NOTE: Exact composition TBD
 ***************************************************************/
typedef struct {
    Ova_Time timestamp;
} Ova_AssertAttemptSyntaxInfo_s;
typedef Ova_AssertAttemptSyntaxInfo_s* Ova_AssertAttemptSyntaxInfo;

typedef struct {
    Ova_TimeL timestamp;
} Ova_AssertAttemptSyntaxInfoL_s;
typedef Ova_AssertAttemptSyntaxInfoL_s* Ova_AssertAttemptSyntaxInfoL;

#define OVA_ASSERTATTEMPTSYNTAXINFO_NULL 0

/***************************************************************
 * OVA Assertion Clock Syntax Info type
 * NOTE: Exect composition TBD
 ***************************************************************/
typedef struct {
    Ova_String clockType;
} Ova_AssertClockSyntaxInfo_s;
typedef Ova_AssertClockSyntaxInfo_s* Ova_AssertClockSyntaxInfo;

#define OVA_ASSERTCLOCKSYNTAXINFO_NULL 0

/***************************************************************
 * OVA Engine Event User Callback Function type
 ***************************************************************/
typedef void (*Ova_EngCallback)(Ova_EngEvent,
                                Ova_Time,
                                Ova_UserData);


/***************************************************************
 * OVA Assertion Event User Callback Function type
 ***************************************************************/
typedef void (*Ova_AssertCallback)(Ova_AssertEvent,
                                   Ova_Time,
                                   Ova_AssertID,
                                   Ova_AssertAttemptID,
                                   Ova_UserData);


/***************************************************************
 * OVA Runtime Configuration Switches
 ***************************************************************/
typedef enum {
    /* NOTE: This is NOT a switch */
    OVA_CONFSWITCH_FIRST = 1000,

    Ova_ShowLineInfoConfSwitch,          /* Show line info in messages. Default: OVA_FALSE */
    Ova_Quiet0ConfSwitch,                /* Do not print any messages at runtime. Default: OVA_FALSE */
    Ova_PrintReportConfSwitch,           /* Print report at the end of simulation. Default: OVA_TRUE */
    Ova_ManageAttemptsSwitch, /* manage attempts */

    /* NOTE: This is NOT a switch */
    OVA_CONFSWITCH_LAST = OVA_CONFSWITCH_FIRST + 100
} Ova_ConfigSwitch;



/***************************************************************
 * The OVA engine constructs new unique ID for
 * client to identify itself on the following requests
 ***************************************************************/
Ova_ClientID ovaRegisterClient(void);



/***************************************************************
 * Notify clientID when state change eventID happens by
 * calling ref. If eventID equals to OVA_ENGEVENT_ALL,
 * the client will be notified of all events of Ova_EngEvent type.
 ***************************************************************/
Ova_Bool ovaAddEngListener(Ova_ClientID clientID,
                           Ova_EngEvent eventID,
                           Ova_EngCallback ref,
                           Ova_UserData udRef);


/***************************************************************
 * Notify clientID when assertion eventID happens bycalling ref.
 * If eventID equals to OVA_ENGEVENT_ALL, the client will be notified
 * of all events of Ova_AssertEvent type.
 ***************************************************************/
Ova_Bool ovaAddAssertListener(Ova_ClientID clientID,
                              Ova_AssertEvent eventID,
                              Ova_AssertID assertId,
                              Ova_AssertCallback ref,
                              Ova_UserData udRef);


/***************************************************************
 * Execute actioneventID command.
 ***************************************************************/
Ova_Bool ovaDoAction(Ova_ClientID clientID,
                     Ova_EngAction eventID,
                     Ova_UserData udRef);


/***************************************************************
 * Perform action eventID for assertion or assertion attempt
 * assertionID.
 ***************************************************************/
Ova_Bool ovaAssertDoAction(Ova_ClientID clientID,
                           Ova_AssertAction eventID,
                           Ova_AssertID assertionID,
                           Ova_AssertAttemptID attemptID,
                           Ova_UserData udRef);

/***************************************************************
 * If this is a SystemVerilog Assertion, return OVA_TRUE
 * Defined in txpApi.c -- Samik
 ***************************************************************/
Ova_Bool ovaIsSystemVerilogAssertion(Ova_AssertID assertionID);

/***************************************************************
 * Get ID of the assertion by its name.
 ***************************************************************/
Ova_AssertID ovaGetAssertByName(Ova_ClientID clientID,
                                Ova_AssertName name);


/***************************************************************
 * Get ID of first assertion. In other words, reset assertion
 * iterator of clientID.
 ***************************************************************/
Ova_AssertID ovaFirstAssert (Ova_ClientID clientID);


/***************************************************************
 * Get ID of next assertion. In other words, advance assertion
 * iterator of clientID.
 ***************************************************************/
Ova_AssertID ovaNextAssert (Ova_ClientID clientID);

/***************************************************************
 * Get ID of clock expression for assertion assertionID.
 ***************************************************************/
Ova_AssertClockID ovaGetAssertClock(Ova_ClientID clientID,
                                    Ova_AssertID assertionID);


/***************************************************************
 * Returns OVA_TRUE iff syntax information is available.
 * Should be called before ovaGetSyntaxInfo(id) is called.
 ***************************************************************/
Ova_Bool ovaHasSyntaxInfo(Ova_ClientID clientID);


/***************************************************************
 * Get Assertion Syntax Information
 ***************************************************************/
Ova_AssertSyntaxInfo ovaGetAssertSyntaxInfo(Ova_ClientID clientID,
                                            Ova_AssertID id);


/***************************************************************
 * Get Assertion Attempt Syntax Information
 ***************************************************************/
Ova_AssertAttemptSyntaxInfo ovaGetAssertAttemptSyntaxInfo(Ova_ClientID clientID,
                                                          Ova_AssertID assrtId,
                                                          Ova_AssertAttemptID attemptId);

Ova_AssertAttemptSyntaxInfoL ovaGetAssertAttemptSyntaxInfoL(Ova_ClientID clientID,
                                                            Ova_AssertID assrtId,
                                                            Ova_AssertAttemptID attemptId);

/***************************************************************
 * Get Assertion Clock Syntax Information
 ***************************************************************/
Ova_AssertClockSyntaxInfo ovaGetAssertClockSyntaxInfo(Ova_ClientID clientID,
                                                      Ova_AssertID assrtId,
                                                      Ova_AssertClockID id);


/***************************************************************
 * Set OVA Configuration Switch
 ***************************************************************/
Ova_Bool ovaSetConfigSwitch(Ova_ClientID clientID,
                            Ova_ConfigSwitch confSwitch,
                            Ova_Bool enable);


/***************************************************************
*Returns current simulation time as a character string
 ***************************************************************/

Ova_Time ovaGetCurrentTime(void);

/***************************************************************
*Returns current simulation time as an unsigned long long.
 ***************************************************************/
Ova_TimeL ovaGetCurrentTimeL(void);


/***************************************************************
 * Set category value for the specified assertion
 ***************************************************************/
Ova_Bool ovaSetAssertCategory(Ova_ClientID clientID,
                              Ova_AssertID id,
                              unsigned int category);


/***************************************************************
 * Returns the category value for the specified assertion as an unsigned int
 ***************************************************************/
unsigned int ovaGetAssertCategory(Ova_ClientID clientID,
                                  Ova_AssertID id);


/***************************************************************
 * Set severity level for the specified assertion
 ***************************************************************/
Ova_Bool ovaSetAssertSeverity(Ova_ClientID clientID,
                              Ova_AssertID id,
                              unsigned int severity);


/***************************************************************
 * Returns the severity level for the specified assertion as an unsigned int
 ***************************************************************/
unsigned int ovaGetAssertSeverity(Ova_ClientID clientID,
                                  Ova_AssertID id);


/***************************************************************
 * Set the custom user msg string for the specified assertion
 ***************************************************************/
Ova_Bool ovaSetAssertUserMessage(Ova_ClientID clientID,
                                 Ova_AssertID id,
                                 Ova_String msg);


/***************************************************************
 * Returns the custom user msg string for the specified assertion as a
   char* string
 ***************************************************************/
Ova_String ovaGetAssertUserMessage(Ova_ClientID clientID,
                                   Ova_AssertID id);


/*Get version of ova apis */
Ova_String ovaGetApiVersion(void);

/* max of 8 bits available for severity level
   max of 24 bits available for category value */
#define MAX_SEVERITY  ((1<<8) -1)
#define MAX_CATEGORY  (1 << 24) - 1

typedef  struct OvaAssertionSourceInfo_s {
    unsigned int lineNo;
    char* fileName;
} OvaAssertionSourceInfo;

typedef OvaAssertionSourceInfo* Ova_AssertionSourceInfo;
typedef struct OvaAssertionDataStruct_s {
    Ova_AssertName name;
    Ova_ExprType exprType;
    Ova_AssertionSourceInfo srcBlock;
    unsigned int severity:8,    /* severity level assigned for assertion */
             category:24;   /* category assigned for assertion */
    Ova_String userMessage;
    Ova_TimeL startTime;
    Ova_TimeL endTime;
} OvaAssertionDataStruct;

typedef OvaAssertionDataStruct* OvaAssertionData;
typedef void (*OvaAssertionFailCB)(OvaAssertionData asData);


/*Declaration of data types to allow read only access to ova vars. */

/*******************************************************************/
/*             Represents an ova variable handle                   */
/*******************************************************************/
typedef vcsd_handle Ova_VarHandle;


/*******************************************************************/
/*             Represents the type info for a variable, size etc.   */
/*******************************************************************/
typedef vcsd_var_info_t Ova_VarInfo_s;
typedef Ova_VarInfo_s*  Ova_VarInfo;

/*******************************************************************/
/*             Represents the dimension for a 2-D ova variable.    */
/*******************************************************************/
typedef vcsd_dim_info_t Ova_VarDimInfo_s;
typedef Ova_VarDimInfo_s* Ova_VarDimInfo;

/*******************************************************************/
/*             Represents the value of a word of a 2-D ova var.    */
/*******************************************************************/
typedef vcsd_word_val_info_t Ova_WordVal_s;
typedef Ova_WordVal_s* Ova_WordVal;

/*******************************************************************/
/*Returns a handle given the full hierarchical name of the variable. */
/*******************************************************************/
Ova_VarHandle ovaGetVarHandleByName( char* variableName );

/*******************************************************************/
/*Returns the type info given a var handle. */
/*******************************************************************/
Ova_VarInfo ovaGetVarInfo( Ova_VarHandle varHandle );
/*******************************************************************/
/*Returns the value of a variable. The value needs to be interpreted depending
  on the type returned in ovaGetVarInfo. For scalar vars, typecast to a
  unsigned char* , for a vector var typecast to vec32_t*, for a 2-D var,
  use ovaGetVarDimensions and ovaGetWordValue                      */
/*******************************************************************/
void* ovaGetValue( Ova_VarHandle varHandle );
/*******************************************************************/
/*Returns the dimensions of a 2-D var.*/
/*******************************************************************/
Ova_VarDimInfo ovaGetVarDimensions( Ova_VarHandle varHandle );
/*******************************************************************/
/*Returns the value of a word of 2-D var. */
/*******************************************************************/
Ova_WordVal ovaGetWordValue( Ova_VarHandle varHandle, int* dimsArray );
/*******************************************************************/
/*Ova_VarHandles in general cannot be cached. Call this function to get
  a handle that can be cached by the application. */
/*******************************************************************/
Ova_VarHandle ovaGetPersistentHandle( Ova_VarHandle varHandle );

/*******************************************************************/
/*Call to free a persistent handle */
/*******************************************************************/
void ovaFreeHandle( Ova_VarHandle varHandle );
/*******************************************************************/
/*Returns true if the variable is scalar or a vector variable. */
/*******************************************************************/
Ova_Bool ovaIs1dVar(Ova_VarInfo varInfo);

vcsd_handle ovasimd_scope_handle_by_name(char*);

typedef struct Ova_OffendingExpressions_s {
    int offendingExprCount;
    Ova_String* offendingExprs;
} Ova_OffendingExpressions_s;

typedef Ova_OffendingExpressions_s* Ova_OffendingExpressions;

Ova_OffendingExpressions ovaGetAllOffendingExpressions(Ova_ClientID clientID, Ova_AssertID id);

/***************************************************************
 * Get success covered of the assertion by its name.
 ***************************************************************/
int ovaGetAssertSuccessCoveredByName(Ova_ClientID clientID,
                                     Ova_AssertName name);

/***************************************************************
 * Get attempt covered of the assertion by its name.
 ***************************************************************/
int ovaGetAssertAttemptCoveredByName(Ova_ClientID clientID,
                                     Ova_AssertName name);

#ifdef  __cplusplus
}
#endif
#endif
