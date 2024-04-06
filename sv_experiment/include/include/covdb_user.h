/* SYNOPSYS CONFIDENTIAL -- This is an unpublished, proprietary work
 * of Synopsys, Inc., and is fully protected under copyright and trade
 * secret laws. You may not view, use, disclose, copy, or distribute
 * this file or any information contained herein except pursuant to a
 * valid written license from Synopsys.
 */

#ifndef _COVDB_USER_H
#define _COVDB_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL (0)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct covdbHandle_s *covdbHandle;

/* Object types */
typedef enum {
    covdbNullHandle = 1,
    covdbInternal,
    covdbDesign,
    covdbIterator,
    covdbContainer,
    covdbMetric,
    covdbSourceInstance,
    covdbSourceDefinition,
    covdbBlock,
    covdbIntegerValue,
    covdbScalarValue,
    covdbVectorValue,
    covdbIntervalValue,
    covdbBDDValue,
    covdbCross,
    covdbSequence,
    covdbAnnotation,
    covdbTest,
    covdbTestName,
    covdbInterval,
    covdbExcludeFile,
    covdbHierFile,
    covdbEditFile,
    covdbBDD,
    covdbError,
    covdbTable,
    covdbValueSet,
    covdbSBNRange,
    covdbTestInfo,
    covdbLastObjEntry
} covdbObjTypesT;

/* Properties that can be read from handles */
typedef enum {
    covdbName,
    covdbFullName,
    covdbFileName,
    covdbLineNo,
    covdbWeight,
    covdbSamplingEvent,
    covdbGuardCondition,
    covdbCoverable,
    covdbDeepCoverable,
    covdbValue,
    covdbValueName,
    covdbType,
    covdbTypeStr,
    covdbCovStatus,
    covdbCovCount,
    covdbCovCountGoal,
    covdbCovGoal,
    covdbCovered,
    covdbDeepCovered,
    covdbParameters,
    covdbTool,
    covdbIsTestFailed,
    covdbMessages,
    covdbWidth,
    covdbIsVerilog,
    covdbIsVhdl,
    covdbIsSigMda,
    covdbAutomatic,
    covdbTwoState,
    covdbSigned,
    covdbRepeatType,
    covdbArgFileName,
    covdbDavinciStr,
    covdbValueStr,
    covdbLastEntry
} covdbPropertiesT;

/* 1 to 1 relations */
typedef enum {
    covdbIdentity = 100,
    covdbParent,
    covdbDefinition,
    covdbBDDTrue,
    covdbRepeat,
    covdbFromValue,
    covdbToValue,
    covdbBDDFalse,
    covdbLast1RelationEntry
} covdb1To1RelationsT;

/* 1 to many relations */
typedef enum {
    covdbObjects = 200,
    covdbMetrics,
    covdbInstances,
    covdbDefinitions,
    covdbLoadedTests,
    covdbAvailableTests,
    covdbTests,
    covdbComponents,
    covdbExpanded,
    covdbTestNames,
    covdbAllExcludedRegions,
    covdbNewExcludedRegions,
    covdbLastRelationEntry
} covdb1ToManyRelationsT;

/* error codes */
typedef enum {
    covdbNoError = 0,
    covdbOutOfMemoryError = -1,
    covdbInitializeExtensionsError = -2,
    covdbInvalidHandleTypeError = -3,
    covdbInvalidHandleOwnerError = -4,
    covdbUnknownExtensionError = -5,
    covdbNotImplementedError = -6,
    covdbWrongHandleTypeError = -7,
    covdbInvalidPropertyError = -8,
    covdbInvalidRelationError = -9,
    covdbBadArgumentsError = -10,
    covdbLoadFailedError = -11,
    covdbInvalidQualifierError = -12,
    covdbInternalError = -13,
    covdbLicenseError = -14,
    covdbDesignNotLoadedYet = -15,
    covdbIncompatibleDatabases = -16,
    covdbIllegalExclude = -17,
    covdbExcludeNoFile = -18,
    covdbExcludeVersionMismatch = -19,
    covdbExcludeSyntaxError = -20,
    covdbIllegalExcludeFile = -21,
    covdbIllegalLoadExclude = -22,
    covdbLimitedDesignLoaded = -23,
    covdbInvalidExcludeItem = -24,
    covdbCoverPointResolveError = -25,
    covdbInconsistentExcludeMode = -26,
    covdbMappedModuleError = -27,
    covdbMapFileSyntaxError = -28,
    covdbWriteError = -29,
    covdbOperationNotAllowed = -30,
    covdbVersionMismatch = -31,
    covdbInvalidEntryInHierConfig = -32,
    covdbIllegalMapped = -33,
    covdbInvalidDavinciItem = -34,
    covdbInvalidTest = -35,
    covdbLastError = -36
} covdbStatusT;

/* Legal values for covdb_configure */
typedef enum {
    /* by default, covdbDisplayErrors is "false".  Set it to "true" and UCAPI
     * will print error messages to stderr when they occur
     */
    covdbDisplayErrors,

    /* the following config items control which metrics are loaded.  By
     * default, all are true and all types of coverage found will be loaded.
     * Set them to either "true" or "false"
     * Please keep the metric order the same as grLine ... and urgLine ...
     * NOTICE: covdbLoadPath is out of order!
     */
    covdbLoadLine,
    covdbLoadCond,
    covdbLoadTgl,
    covdbLoadFsm,
    covdbLoadBranch,
    /* used to be covdbLoadPath */
    covdbLoadAssert,
    covdbLoadGroup,

    covdbMergeRules,
    covdbKeepTestInfo,


    /* Mapping */
    covdbMappedModule,
    covdbMapFile,
    covdbMapMergeUnion,

    /* report only ports */
    covdbPortsOnly,

    /* if covdbLimitedDesign is set to "true", no design information will
     * be created and only testbench and assertions coverage can be loaded.
     * This must be set when loading coverage data from master/slave mode
     * simulations.
     */
    covdbLimitedDesign,
    covdbMergeAcrossScopes,
    covdbIgnoreAutoCrosses,
    covdbMergeSameCumulatives,
    covdbFlexMergeDrop,
    covdbMaxDefaultBins,
    covdbMaxTestsPerCoverable,
    covdbExcludeCondId,
    covdbNoCaseDef,
    covdbFsmDisableLoop,
    covdbPropExclInfoToCross,
    covdbScopeSemantics,
    covdbContainerSemantics,
    /* Strict exclude mark covered item excluded as attempted */
    covdbExcludeMode,

    /*
    To keep compatibility, new items are appended here.
    */
    covdbLoadPath,
    covdbExcludeFormat,

    /*
    By default, covdbVersionCheck is "true", and UCAPI will enforce
    compatibility check for any newDB database loaded by comparing the
    CovDB version.  To skip this check, please set covdbVersionCheck
    to "false".
    */
    covdbVersionCheck,
    covdbGroupSortByName,
    covdbExclBypassChecks,
    covdbGroupFilter,
    /* Covergroups will be reported under design hierarchy */
    covdbShowGroupsInDesign,
    covdbSetVcLicMode,
    /* Configure UCAPI to say whether to load metric specific test data.
     * Default is set to TRUE */
    covdbLoadMetricData,
    covdbMaxTestsPerCoverableToStore,
    covdbFlexMergeDropAll,
    covdbFlexMergeUnion,
    covdbSaveResetCoverage,
    covdbExclNoCgDefUpdate,
    covdbSqliteDB,
    covdbShowTestRecords,
    covdbVcFormalCoverageMode, //For VC-FCA
    covdbLastConfigEntry
} covdbConfigItemT;

/* Legal bit field values for covdbCovStatus.  Multiple bits may be set. */
typedef enum {
    covdbStatusUnreachable =        1,
    covdbStatusIllegal =        2,
    covdbStatusExcludedAtCompileTime =  4,
    covdbStatusCovered =        8,
    covdbStatusProven =         32,
    covdbStatusExcludedAtReportTime  =  64,
    covdbStatusAttempted =      128,
    covdbStatusExcluded =           covdbStatusExcludedAtCompileTime |
    covdbStatusExcludedAtReportTime,
    covdbStatusPartiallyExcluded = 256,
    covdbStatusPartiallyAttempted = 512
} covdbCovStatusE;

/* Scalar values for covdbScalarValue */
typedef enum {
    covdbValue0,
    covdbValue1,
    covdbValueX
} covdbScalarValueT;

typedef enum {
    covdbRepeatNone,
    covdbGoto, /* [->3],[->[3:4]] */
    covdbConsecutive, /* [*[3:4]], [*[3]]*/
    covdbNonConsecutive/* [=[3:4]], [=[3]]*/
}covdbRepeatTypes;


/* The struct returned by covdb_get_vec_4state_value */
typedef struct covdbVec32Value_s {
    unsigned int c;
    unsigned int d;
} covdbVec32ValueT;

/* Metric enumeration used for exclusion files */
typedef enum {
    METRIC_START = 0,
    METRIC_LINE = 1,
    METRIC_TGL = 2,
    METRIC_FSM = 3,
    METRIC_ASSERT = 4,
    METRIC_COND = 5,
    METRIC_ASSIGNTGL = 6,
    METRIC_TESTBENCH = 7,
    METRIC_PATH = 8,
    METRIC_BRANCH = 9,
    METRIC_END = 10,
    METRIC_ERROR = 11,
    NUM_METRIC_TYPES
} MetricType;

typedef covdbVec32ValueT covdb4stateValT;

covdb4stateValT* covdb_get_vec_4state_value(covdbHandle objHdl, covdbHandle regHdl);

unsigned int* covdb_get_vec_2state_value(covdbHandle objHdl, covdbHandle regHdl);


/****************************************************************************/
/* FUNCTIONS                                                                */
/****************************************************************************/

/************* functions for loading/unloading designs/tests ****************/

covdbHandle covdb_load(int what,
                       covdbHandle design,
                       const char* logical_fname);

covdbHandle covdb_loadmerge(int what,
                            covdbHandle dst_test,
                            const char* logical_fname);

covdbHandle covdb_merge(covdbHandle dst_test,
                        covdbHandle src_test);

int covdb_unload(covdbHandle design_or_test);

int covdb_create_dummy(covdbHandle design, covdbObjTypesT objType);

int covdb_save(covdbHandle design_or_test,
               const char* logical_fname);

int covdb_qualified_save(covdbHandle object, int what, covdbHandle qualifier,
                         const char* logical_fname);

covdbHandle covdb_qualified_loadmerge(int what,
                                      covdbHandle dst_test,
                                      covdbHandle qualifier,
                                      const char* logical_fname);
int covdb_dump_full_exclusions_file  (covdbHandle test, const char* instFileName, const char* modFileName, const char* mode, MetricType metType);
int covdb_save_exclude_file  (covdbHandle design_or_test, const char* logical_fname, const char* mode);
int covdb_save_attempted_file  (covdbHandle design_or_test, const char* logical_fname, const char* mode);

int covdb_load_mapfile  (covdbHandle design, const char* logical_fname);

int covdb_load_exclude_file  (covdbHandle design_or_test, const char* logical_fname);
int covdb_load_davinci_cp_file  (covdbHandle design_or_test, const char* logical_fname, const char* out_dir_name);
int covdb_get_davinci_cp_cov_status_from_id (covdbHandle design_or_test,covdbHandle metricH,unsigned int, unsigned int, unsigned int, unsigned int, unsigned int*);
int covdb_get_davinci_cp_cov_status_new (covdbHandle design_or_test,covdbHandle metricH,const char*, unsigned int, unsigned int, unsigned int, unsigned int*);
int covdb_get_davinci_cp_cov_status (covdbHandle design_or_test,covdbHandle metricH,const char*, const char*, const char*);
int covdb_populate_davinci_cp_cov_status (covdbHandle design_or_test,covdbHandle metricH,const char*, unsigned int**, unsigned int, unsigned int);
int covdb_get_davinci_cp_cov_status_from_id (covdbHandle design_or_test,covdbHandle metricH,unsigned int, unsigned int, unsigned int, unsigned int, unsigned int*);
int covdb_get_davinci_cp_cov_status_new (covdbHandle design_or_test,covdbHandle metricH,const char*, unsigned int, unsigned int, unsigned int, unsigned int*);
int covdb_get_davinci_cp_cov_status (covdbHandle design_or_test,covdbHandle metricH,const char*, const char*, const char*);
int covdb_populate_davinci_cp_cov_status (covdbHandle design_or_test,covdbHandle metricH,const char*, unsigned int**, unsigned int, unsigned int);
void covdb_dump_dvc_hint_mapping(covdbHandle testH, const char* common_file, int* lcIdxRanges, const char** fileSuffixes, int isFirst);

int covdb_unload_exclusion(covdbHandle design);
covdbHandle covdb_map (covdbHandle def_or_inst1, covdbHandle test1, covdbHandle def_or_inst2, covdbHandle test2);

/* Pass 0 for flags now. */
int covdb_synchronize_cov_status(covdbHandle design_or_test, unsigned int flags);

/********** functions available for all extensions ********************/


/* function to traverse 1-to-1 relations */
covdbHandle covdb_get_handle(covdbHandle obj,
                             covdb1To1RelationsT relation);

/* function to traverse qualified 1-to-1 relations */
covdbHandle covdb_get_qualified_handle(covdbHandle obj,
                                       covdbHandle prop,
                                       covdb1To1RelationsT relation);

/* function to traverse 1-to-many relations */
covdbHandle covdb_iterate(covdbHandle obj,
                          covdb1ToManyRelationsT relation);

/* function to traverse qualified 1-to-may relations */
covdbHandle covdb_iterate_table(covdbHandle obj,
                                covdbHandle region,
                                covdbHandle test);
covdbHandle covdb_qualified_iterate(covdbHandle obj,
                                    covdbHandle prop,
                                    covdb1ToManyRelationsT relation);

covdbHandle covdb_make_persistent_handle(covdbHandle obj);

/* declares that this handle is no longer being used by the caller. */
void covdb_release_handle(covdbHandle obj);

/* function to obtain the next handle from an iterator */
covdbHandle covdb_scan(covdbHandle iterator);

/*
 * function to obtain an integer valued property.  Non-regions
 * must specify their parent region handle.  Test-qualified properties
 * (such as covdbCovered) require a test handle.
 */
int covdb_get(covdbHandle obj, covdbHandle region,
              covdbHandle test, covdbPropertiesT property);

/* function to obtain an real valued property */
double covdb_get_real(covdbHandle obj, covdbPropertiesT property);

/* function to obtain an string valued property */
char* covdb_get_str(covdbHandle obj, covdbPropertiesT property);

char* covdb_get_annotation(covdbHandle obj, const char* key);

int covdb_set_annotation(covdbHandle obj, const char* key, const char* value);

const char *covdb_version(void);
const char *covdb_db_version(void);

char* covdb_get_qualified_annotation(covdbHandle obj,
                                     covdbHandle prop,
                                     const char* key);

int covdb_get_integer_annotation(covdbHandle obj, const char* key);

/* set integer valued property of an object */
int covdb_set(covdbHandle obj, covdbHandle region, covdbHandle test, covdbPropertiesT property, int value);

/* set string valued property of an object */
int covdb_set_str(covdbHandle obj, covdbPropertiesT property, const char* value);

/* check UCAPI error status.  *error_message is set to string */
covdbStatusT covdb_get_error(char **error_message);

/* set error callback function.
 * errHdl is created by UCAPI, and should be released by application
 */
typedef void (*covdbErrorCB)(covdbHandle errHdl, void *data);
int covdb_set_error_callback(covdbErrorCB fn, void *data);

void covdb_configure(covdbConfigItemT item, char *value);
void covdb_set_metric_for_show_tests(MetricType metType);

covdbHandle ucal_get_object_by_id(covdbHandle hi, int pos);

/*
 * Converts a handle represented by a tuple of ints. into a real handle.
 * containerHandle could be coverpoint handle or crosspoint handle etc.
 */
covdbHandle covdb_get_handle_from_ids(covdbHandle regionHandle,
                                      covdbHandle containerHandle,
                                      int* ids,
                                      int numIds);


covdbHandle covdb_qualified_object_iterate(covdbHandle objectHandle, covdbHandle regionHandle, covdbHandle testHandle, covdb1ToManyRelationsT relation);

/* Checks merge equivalence of two objects */
int covdb_compare(covdbHandle obj1, covdbHandle obj2);

/*#defines for annotations. */
#define COV_COMMENT "cov_comment"
#define IS_CROSS "isCross"
#define RANDOM_SEED "random seed"
#define RANDOM_SEED_48 "random seed 48"
#define SEMANTICS "semantics"
#define OLD_SEMANTICS "old_semantics"
#define NEW_SEMANTICS "new_semantics"
#define BIN_ID "id"
#define INDEX  "index"
#define BLOCK_TYPE "block_type"
#define STABLE_NAME "stable_name"
#define DEFAULT_BIN "default_bin"
#define WILDCARD_BIN "wildcard_bin"
#define CG_SIGNATURE "signature"
#define AUTO_BIN_MAX "auto_bin_max"
#define CROSS_AUTO_BIN_MAX "cross_auto_bin_max"
#define CROSS_BIN_MAX "cross_bin_max"
#define LOW_ID "low_id"
#define HIGH_ID "high_id"
#define NUM_SCOPE_DEFINITIONS "num_scope_definitions"
#define SIMULATION_TIME "simulation time"
#define MERGE_ACROSS_SCOPES "merge_across_scopes"
#define IGNORE_AUTO_CROSSES "ignore_auto_crosses"
#define NESTED_SCOPE_NAME "nested_scope_name"
#define COVERPOINT_BIN "cp_bin" /*Whether a bin is a coverpoint bin. */
#define MERGE_SAME_SHAPES "merge_same_shapes" /*For a covergroup, merge all covergroup shapes that are same.*/
#define ENCLOSING_SCOPE_DEF "enclosing_scope_def"
#define ENCLOSING_SCOPE_INST "enclosing_scope_inst"
#define MAX_DEFAULT_BINS "max_default_bins"
#define FLEX_MERGE_UNION "flex_merge_union"
#define FLEX_MERGE_DROP "flex_merge_drop"
#define RESET_HIT_COUNT_AMD_SWITHCG "RESET_HIT_COUNT_AMD_SWITHCG"
#define RESET_COUNT "reset_count"
#define KEEP_TEST_INFO "keep_test_info"
#define MAX_TESTS_PER_COVERABLE "max_tests_per_coverable"
#define IS_LP_GROUP "is_lp_group"
#define IS_DEFAULT_CASE_STMT "is_default_case_stmt"
#define STROBE "strobe"
#define DETECT_OVERLAP "detect_overlap"
#define CROSS_NUM_PRINT_MISSING "cross_num_print_missing"
#define AT_LEAST "at_least"
#define GOAL "goal"
#define WEIGHT "weight"
#define PER_INSTANCE "per_instance"


extern int isLineMetric(covdbHandle metric);
extern int isFsmMetric(covdbHandle metric);
extern int isCondMetric(covdbHandle metric);
extern int isTglMetric(covdbHandle metric);
extern int isAssertMetric(covdbHandle metric);
extern int isTestbenchMetric(covdbHandle metric);
extern int isBranchMetric(covdbHandle metric);
extern int isPathMetric(covdbHandle metric);

/* For code coverage, return true if counting coverage of the metric is done.
For example, with -cm_count at compiletime, counting coverage database for
line/cond/fsm/tgl will be generated. With -cm_tgl tglcount, toggle coverage
will be counting.    */
extern int isCovCountMetric(covdbHandle metric, covdbHandle test);


/*******************************************************************************
 * These definitions and functions are used to support for search with SQLite  *
 ******************************************************************************/
/* defines for SQLite table and view name */
#define SQLITE_T_MODULE "module_t"
#define SQLITE_T_INSTANCE "instance_t"
#define SQLITE_T_GROUP_DEFINITION "group_def_t"
#define SQLITE_T_GROUP_SHAPE "group_shape_t"
#define SQLITE_T_GROUP_INSTANCE "group_inst_t"
#define SQLITE_T_GROUP_COVERPOINT "group_cp_t"
#define SQLITE_T_GROUP_INSTANCE_COVERPOINT "group_inst_cp_t"
#define SQLITE_T_ASSERT "assert_t"
#define SQLITE_V_GROUP "group_v"
#define SQLITE_V_GROUP_COVERPOINT "group_cp_v"
#define SQLITE_V_GROUP_INSTANCE "group_inst_v"
#define SQLITE_V_GROUP_INSTANCE_COVERPOINT "group_inst_cp_v"

typedef enum{
    SQLITE_BACKUP_MEMORY_TO_FILE,
    SQLITE_BACKUP_FILE_TO_MEMORY
}sqliteBackupType;

typedef struct sqlite3 sqlite3;
typedef struct sqlite3_stmt sqlite3_stmt;
int         ucal_backup_sqlite(sqlite3 * pInMemeory, const char *zFilename, sqliteBackupType type);
sqlite3 *   ucal_gen_sqlite(covdbHandle designH, covdbHandle testH);
int         ucal_delete_sqlite(covdbHandle designH, covdbHandle testH);
const char *ucal_gen_dbname(covdbHandle designH, covdbHandle testH, int isMemoryDB);
sqlite3 *   ucal_get_sqlite_handle(covdbHandle designH, covdbHandle testH);
int         ucal_use_sqlite();
int         ucal_sqlite_max_row();
int         ucal_sqlite_prepare(sqlite3 * db, const char *zSql, int igCase, sqlite3_stmt **ppStmt);
int         ucal_sqlite_step(sqlite3_stmt *stmt);
int         ucal_sqlite_finalize(sqlite3_stmt *stmt);
int         ucal_sqlite_column_int(sqlite3_stmt *stmt, int iCol);
const void *ucal_sqlite_column_blob(sqlite3_stmt *stmt, int iCol);
const unsigned char *ucal_sqlite_column_text(sqlite3_stmt *stmt, int iCol);

/*****************************************************************
 * These functions are deprecated and will be deleted in the near
 * future.  They should not be used in new applications
 *****************************************************************/

extern covdbHandle covdb_getHandleByName(const char *name,covdbObjTypesT type);
int covdb_qualified_configure(covdbHandle designH, covdbConfigItemT item, const char* value);

#ifdef __cplusplus
}
#endif


#endif
