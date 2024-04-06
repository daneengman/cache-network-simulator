#ifndef _HVPAPI_DEF_H
#define _HVPAPI_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#define HVP_STRBUF_LEN (1024*16)


typedef struct hvpHandle_s *hvpHandle;

typedef enum {
    hvpBadType,

    hvpPlan,
    hvpFeature,
    hvpAttribute,
    hvpMetric,
    hvpMeasure,
    hvpSource,
    hvpRegion,
    hvpIterator,
    hvpEnumDef,
    hvpEnumValue,
    hvpGoalAttribute,
    hvpAction,
    hvpFilter,
    hvpAssign,
    hvpOverride,
    hvpIncludeFile,
    hvpVE,
    hvpVEMetric,
    hvpVERegion,
    hvpVEValue,
    hvpCovdbHdl,
    hvpSpec,
    hvpSpecSect,
    hvpSpecSectObject,
    hvpBugServer,
    hvpProject,
    hvpNameList,

    /* value handle types */
    hvpInteger,  /* for attribute, metric */
    hvpReal,     /* for attribute, metric */
    hvpString,   /* for attribute only */
    hvpEnum,     /* for attribute, metric */
    hvpRatio,    /* for metric only */
    hvpPercent,  /* for metric only, treat as real */
    hvpNoData
} hvpTypeT;

typedef enum {
    hvpType,         /* hvp_get() returns hvpTypeT */
    hvpActive,       /* hvp_get() returns hdl->active */
    hvpIsFiltered,   /* hvp_get() returns plan/feature's hvpIsFiltered */
    hvpIntValue,
    hvpPlanId,       /* hvp_get() returns plan->id */
    hvpLineNo,
    hvpValueType,    /* hvp_get() returns attribute/metric value type*/
    hvpMetValType,   /* depricated. use hvpValueType */
    hvpMetAggType,   /* hvp_get() returns hvpAggRuleT */
    hvpGoalStatus,   /* return will be one of */
    /* hvpGoalMet, hvpGoalNotMet, */
    /* hvpGoalNone, hvpGoalError */
    hvpAttributeValueStatus,    /* hvp_get() return hvpAttributeValueStatusT of hvpValueHdlT */
    hvpNumerator,    /* valueH must be hvpRatio */
    hvpDenominator,   /* valueH must be hvpRatio */
    hvpIsAggregateMetric,  /* metric handle, returns TRUE/FALSE */
    hvpIsGlobalMetric,     /* metric handle, returns TRUE/FALSE */
    hvpCovered,       /* hvp_get() returns measure's status' bit0 */
    hvpOverrided,     /* hvp_get() returns measure's status' bit1 */
    hvpPropagate,     /* TRUE if attribute, FALSE if annotation */
    hvpIsOverdue,     /* hvp_get() returns plan file has been changed, only used in DVE */
    hvpSpcStatus,     /* plan->spcStatus, load .spc xml status hvpSpcStatusTypeE */
    hvpSpcLineTotal,  /* coverage info for spec pdf of total line number */
    hvpSpcLineLinked, /*                               linked line number */
    hvpSpcLineIgnored,/*                               ignored line number */
    hvpSpcLineTodo,   /*                               todo line number */
    hvpSpcLineUncovered, /*                            uncovered line number */
    hvpSecOffset,
    hvpSecLength,
    hvpSecLineTotal,  /* total line number of this section */
    hvpSecBoundStartPage,
    hvpSecBoundEndPage,
    hvpSecPageNum,
    hvpSecContentType,/* hvpSpecSectContentTypeE */
    hvpSecContentMode,/* hvpSpecSectModeTypeE */
    hvpUpdateStatus,  /* set/get the update status of hvp handle */
    hvpIsBuiltin,      /* TRUE for builtin metric/attribute definition */
    hvpCovStatus
} hvpIntPropertyT;

typedef enum {
    hvpName,
    hvpStringValue,
    hvpFileName,
    hvpAbsFileName,
    hvpGoal,
    hvpSubplanOverrides,
    hvpVersion,       /* for plan->.spc & spec->.pdf version */
    hvpSpcXML,
    hvpSpecComment,
    hvpSpecMD5,
    hvpSpecRelPath,
    hvpSpecMarginTop,
    hvpSpecMarginBottom,
    hvpSpecMarginLeft,
    hvpSpecMarginRight,
    hvpSpecHyperlink,
    hvpSpecPdfCovInfo,
    hvpSecNum,
    hvpSecTitle,
    hvpSecBoundStartX,
    hvpSecBoundStartY,
    hvpSecBoundEndX,
    hvpSecBoundEndY,
    hvpSecBoundMode,
    hvpSecBoundContent,
    hvpSecChecksum,
    hvpNumbering,
    hvpOrgStr,
    hvpUUID,          /* for verdi issue track system. add UUID on plan/feat node */
    hvpBugServURL,    /* bug server URL */
    hvpPrjID,         /* bug server project identify  */
    hvpStrPropNum
} hvpStrPropertyT;

typedef enum {
    hvpRealValue
} hvpRealPropertyT;

typedef enum {
    hvpChildren,
    hvpAttributes,
    hvpTests,
    hvpMetrics,
    hvpMeasures,
    hvpSources,
    hvpRegions,
    hvpScores,
    hvpEnumDefs,     /* for enum metric */
    hvpEnumVals,     /* for enum value */
    hvpMeasureTotalScores,
    hvpGoalAttributes,
    hvpIncludeFiles,
    hvpSpecs,
    hvpSpecSects,
    hvpSpecSectIgnores,
    hvpSpecSectTempIgnores,
    hvpSpecSectObjects,
    hvpVEMetrics,
    hvpVERegions,
    hvpVEValues,
    hvpAttributeValues,
    hvpExpectedMetrics,
    hvpFeatureIDs,  // find the feature handle by feature id
    hvpBugServers,
    hvpProjects,
    hvp1ToManyRelationNum
} hvp1ToManyRelationT;

typedef enum {
    hvpParent,
    hvpDefaultValue,
    hvpDefinition
} hvp1To1RelationT;

typedef enum {
    hvpDisplayErrors,   /* print out error message itself */
    hvpVerbose,         /* print out informative messages */
    hvpDebug,           /* print out debug infomation */
    hvpGroupRatio,
    hvpGroupMergeAcrossScopes,
    hvpGroupNoWildcard, /* not support wildcard in group source*/
    hvpHorizontalAggregation,
    hvpScoreMissing,    /* give 0 score for unmatched source */
    hvpLPPlan,          /* the plan is generated according to UPF */
    hvpNoNumbering,     /* do not save numbering assignments in hvp file */
    hvpLCAFlag,         /* suppress LCA license key */
    hvpDiffLevel,       /* "0": Feature/Sub-plan, "1": Measure, "2": Source*/
    hvpDiffOptions,
    hvpDiffIntoSubPlan, /* Whether diff into sub-plan: "false", "true"*/
    hvpDiffSubPlanDef,  /* Whether diff sub-plan def: "false", "true"*/
    hvpDiffAttribute,   /* Whether diff attribute def: "false", "true"*/
    hvpDiffMetric,      /* Whether diff metric def: "false", "true"*/
    hvpDiffSpec,        /* Whether diff spec: "false", "true"*/
    hvpIssueTracking,   /* enable/disable the issue tracking system */
    hvpConfigItemNum
} hvpConfigItemT;

typedef enum {
    hvpReportFormat,    /* report format value: hvpReportFormatT */
    hvpReportAnnotated, /* report the annotated report. true: annotated report, false: non-annotated_report */
    hvpReportColumnList,  /* string of metric and attribute names list which will be shown in report table. */
    hvpReportDir,       /* string of report file dir */
    hvpReportConfigNum
} hvpReportConfigT;

typedef enum {
    hvpReportFormatNo,         /* no report */
    hvpReportFormatSprsXML,    /* Spreadsheet XML */
    hvpReportFormatWordXML,    /* Word XML */
    hvpReportFormatNum
} hvpReportFormatT;

typedef enum {
    hvpRuleAverage,
    hvpRuleSum,
    hvpRuleUniqueSum,
    hvpRuleMin,
    hvpRuleMax
} hvpAggRuleT;

typedef enum {
    hvpNoError,
    hvpFileIOFailure,   /* user error */
    hvpLoadFailed,      /* user error */
    hvpNotImplemented,  /* user error */
    hvpNotSupported,    /* user error */
    hvpLicenseFailure,  /* user error */
    hvpCompileError,    /* user error */
    hvpCompileWarning,  /* user error */
    hvpEditingError,
    hvpOutOfMemory,
    hvpInternalError,
    hvpUnknownXml,
    hvpBadXml,
    hvpBadArguments,
    hvpStringOverflow,
    hvpBadHandle,
    hvpBadState,
    hvpDecompileError,
    hvpDecompileWarning
} hvpStatusT;


/* return code of hvp_get(score_hdl, hvpGoalStatus) */
typedef enum {
    hvpGoalMet,
    hvpGoalNotMet,
    hvpGoalError,
    hvpGoalNone
} hvpGoalStatusT;

enum {
    HVP_OPT_BASIC = 0x0000,
    HVP_OPT_KEEPXML = 0x0001,
    HVP_OPT_SKIP_SPC = 0x0002,
    HVP_OPT_SKIP_SPCCS = 0x0004,
    HVP_OPT_EDIT = 0x0010
};

typedef enum {
    hvpDefault,
    hvpDerived,
    hvpAssigned,
    hvpOvrd,
    hvpHidden,  // only for score of base metric
    hvpValueNone
} hvpAttributeValueStatusT;

// source status
enum {
    HVP_SOURCE_DEFAULT = 0x0000,
    HVP_SOURCE_IGNORED = 0x0001,
    HVP_SOURCE_NOMORE_WARNING = 0x0002,
    HVP_SOURCE_HIDDEN = 0x0004,
    HVP_SOURCE_OVERRIDE = 0x0008,
    HVP_SOURCE_ISPATTERN = 0x0010,
    HVP_SOURCE_COMPLEX_PATTERN = 0x0020,
    HVP_SOURCE_NOMATCH = 0x0040
};

// measure status
enum {
    HVP_MEASURE_DEFAULT = 0x0000,
    HVP_MEASURE_COVERED = 0x0001,
    HVP_MEASURE_SOURCE_OVERRIDE = 0x0002,
    HVP_MEASURE_NOMATCH = 0x0004
};

// plan/feature status
enum {
    HVP_NODE_DEFAULT = 0x0000,
    HVP_NODE_ISFILTERED = 0x0001,
    HVP_NODE_NOMATCH = 0x0002
};

typedef enum {
    // 0 for no spc info for this plan
    HVP_SPC_LOADED  = 0x0001, // .spc loaded with no problem
    HVP_SPC_MISSING = 0x0002, // .spc file is missing
    HVP_SPC_CS_MM   = 0x0004, // checksum mismatch
    HVP_SPC_XML_ERR = 0x0008  // .spc xml content corrupt
} hvpSpcStatusTypeE;

typedef enum {
    hvpSpecLink,
    hvpSpecIgnore,
    hvpSpecTempIgnore,
    hvpSpecNone
} hvpSpecSectTypeE;

typedef enum {
    hvpSpecSectContentText,
    hvpSpecSectContentImage,
    hvpSpecSectContentMixed,
    hvpSpecSectContentNone
} hvpSpecSectContentTypeE;

typedef enum {
    hvpSpecSectModeNormal,
    hvpSpecSectModeColumn,
    hvpSpecSectModeNone
} hvpSpecSectModeTypeE;

typedef enum {
    HVP_UPDATE_GOAL = 0x0001,         // mark_goal_status
    HVP_UPDATE_SCORE = 0x0002,        // propagate_scores
    HVP_UPDATE_EXPMET = 0x0004,       // propagate_scores
    HVP_UPDATE_EXCLUSION = 0x0008,    // exclude info changed
    HVP_UPDATE_SOURCE = 0x0010,       // part of source changed
    HVP_UPDATE_DATA = 0x0020,         // load_data/load_covdb_handle
    HVP_UPDATE_ATTR= 0x0040,          // propagate_atts
    HVP_UPDATE_ALL = 0x007f           // resolve_subplans/first run
} hvpUpdateStatusT;

typedef void (*hvpErrorCB)(hvpStatusT errcode, char *errmsg);

#ifdef __cplusplus
}
#endif

#endif /* _HVPAPI_H */

