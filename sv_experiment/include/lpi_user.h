/***************************************************************************
  SYNOPSYS CONFIDENTIAL -- This is an unpublished, proprietary work of
  Synopsys, Inc., and is fully protected under copyright and trade secret
  laws. You may not view, use, disclose, copy, or distribute this file or
  any information contained herein except pursuant to a valid written
  license from Synopsys.
 ***************************************************************************/
#ifndef _LPI_USER_H_
#define _LPI_USER_H_
#ifdef  __cplusplus
extern "C" {
#endif
/* Sized variables */
#ifndef LPI_TYPES
#define LPI_TYPES
typedef int             LPI_INT32;
typedef unsigned int    LPI_UINT32;
#endif

/******************************** LPI handle typedef **********************/
typedef LPI_UINT32 *lpiHandleT;
/*LPI 1-2-1 relationships*/
typedef enum {
    lpiHighConn,
    lpiScope,
    lpiParent,
    lpiFile,
    lpiDefFile, //normally return the UPF or LpaBind file

    //connection
    lpiFrom,
    lpiTo,
    lpiMergedCell
}lpiOneToOneT;

/*LPI 1-2-many relationships*/
typedef enum {
    lpiTopScopes,
    lpiPowerScopes,
    lpiScopes,
    lpiRanges,
    lpiPorts,
    lpiOriginalSignals,
    lpiDerivedSignals,
    lpiMemberSignals,
    lpiIsoCells, //return 4 kinds of IsoCells: uninstrument:{lpiIsoCellK, lpiAssociatedIsoCellK} 
                 //instrument:{lpiVirtIsoCellK, lpiMapVirtIsoCellK}
    lpiInternalSignals,
    lpiInstrumentSignalDecls,
    lpiInstrumentCells, //IsoCell, MapIsoCell, SRSN/SPA/DB, ExprCell
                        //ExprCell is used to transform expression for port
    lpiConnectionInfos,
    lpiPortInsts,
    lpiDriveCells,
    lpiBufferConnInfos,
    lpiLoadCells,
    lpiParameters
}lpiOneToManyT;

/*LPI integer or boolean properties*/
typedef enum {
    lpiLeftBoundP,
    lpiRightBoundP,
    lpiIsPackedRangeP,
    lpiLanguageP,
    lpiLineNoP,
    lpiDirectionP,
    lpiObjectKindP,
    lpiTypeKindP,
    lpiIsScopeP,
    lpiIsInstrumentP,
    lpiPurposeKindP,
    lpiPortKindP,
    lpiConnectKindP,
    lpiOperatorKindP,
    lpiIsDbAffectedP,
    lpiErrorKindP,
    lpiIsSimpleInstrumentedScopeP,
    lpiHasMapVirtIsoOrAssertionCellP,
    lpiHasIsoCellP
}lpiIntPropertyT;

typedef enum {
    lpiInputK,
    lpiOutputK,
    lpiInoutK,

    lpiNoDirectionK
}lpiDirectionKindT;

typedef enum {
    lpiInputDataPinK,
    lpiOutputDataPinK,
    lpiUnknownPinK
}lpiPortKindT;

typedef enum {
    lpiIsoShadowK,
    lpiIsoShadowPreK,
    lpiIsoEnableK,
    lpiIsoPowerK,
    lpiIsoGroundK,
    lpiRetShadowK,
    lpiRetStateK,
    lpiLsShadowK,
    lpiLsEnableK,
    lpiSpaShadowK,
    lpiSpaEnableK,
    lpiSrsnShadowK,
    lpiSrsnPowerK,
    lpiSrsnGroundK,
    lpiSupplyNetK,
    lpiSpaShadowPreK,
    lpiSrsnShadowPreK,
    lpiMvsimFlagK,
    lpiUpfSimstateK,
    lpiLogicNetK,
    lpiUnknownPurposeK
}lpiPurposeKindT;

typedef enum {
    lpiTopScopeK,
    lpiPowerScopeK,
    lpiScopeK,
    lpiGenerateBlockK,

    //UPF Object
    lpiPowerDomainK,
    lpiIsolationStrategyK,
    lpiRetentionStrategyK,
    lpiLevelShifterStrategyK,

    //instrumented cell
    lpiVirtIsoCellK,
    lpiMapVirtIsoCellK,
    lpiVirtPowerSwitchCellK,
    lpiVirtSrsnCellK,
    lpiVirtSpaCellK,
    lpiVirtDbCellK,
    lpiAssertionCellK,

    //Another 2 kinds of IsoCell
    lpiIsoCellK,
    lpiAssociatedIsoCellK,

    lpiPowerSwitchCellK,

    //hdl or instrument port or signal
    lpiPortK,
    lpiSignalK,
    lpiSignalDeclK,
    lpiPortExprRefK,
    lpiSignalExprK,
    lpiConnectionInfoK,

    lpiFileK,
    lpiRangeK,
    lpiMergedCellK,

    //UPF Object cont
    lpiSupplySetK,
    lpiPowerSwitchK,
    lpiPstK,

    lpiParameterK,
    lpiUnknownObjK
}lpiObjectKindT; 

typedef enum {
    lpiConnectK,
    lpiPortExprTransformK,
    lpiReplaceK,
    lpiBufConnectK, //connect from/to with transparent upf buffer cell

    lpiNoConnectK
}lpiConnectKindT;

typedef enum {
    lpiNoRewireK
}lpiRewireKindT;


typedef enum {
//    lpiWireK,
//    lpiRegK,
    lpiBitK,
    lpiLogicK,
    lpiBooleanK,
    lpiCharK,
    lpiIntK,
    lpiRealK,
    lpiEnumK,
    lpiStructK,
    lpiUserK,
    lpiArrayK,
/*
    lpiTypeBitK,
    lpiTypeLogicK,
    lpiTypeCharK,
    lpiTypeBooleanK,
    lpiTypeIntK,
    lpiTypeRealK,
    lpiTypeEnumK,
    lpiTypeRecordK,
    lpiTypeTimeK,
    lpiTypeArrayK,
    lpiTypeStringK,
    lpiTypeUserK,
    lpiTypeCharLiteralK,
    lpiTypeFileDeclK,
    lpiTypeAccessDeclK,
    lpiTypeStrLiteralK,
    lpiTypeIntLiteralK,
    lpiTypeClassK,
    lpiTypeVirtualSigK,
    lpiTypeMpPortK,
    lpiTypePhysK,
    lpiTypeWireRealK,
    lpiTypeInvalidK,
*/
    lpiUnknownTypeK = -1
}lpiTypeKindT;

/*
typedef enum {
    lpiIsoBufK,
    lpiSupplyNetK,
    lpiSimstateK,
    lpiMsimflagK
}lpiSigKindT;
*/

/*LPI string properties*/
typedef enum {
    lpiVcsVersion,
    lpiDataCreated,
    lpiLpaBindTclP,
    lpiLpaBindFileListP,
    lpiNameP,
    lpiFullNameP,
    lpiFileNameP,
    lpiObjectKindStrP,
    lpiTypeKindStrP,
    lpiSubTypeNameP,
    lpiModuleNameP,
    lpiSplitModuleNameP,  //analyze lpi database, deduce the split module name
    lpiIsolationStrategyNameP,
    lpiSrsnStrategyNameP,
    lpiSpaStrategyNameP,
    lpiSubVersion,  //File SubVersion
    lpiSoVcsVersion,  //So library Vcs Version
    lpiSoSubVersion, //So SubVersion
    lpiUpfHierarchicalNameP,
    lpiParameterValueP,
    lpiParameterTypeStrP
}lpiStrPropertyT;

/*
typedef enum {
    lpiAuto = 0, //will determine file format vir extension
    lpiXML,
    lpiVCSBin,
    lpiVCSText
}lpiFileFormatT;
*/

typedef enum {
    lpiVerilogK,
    lpiVhdlK,
    lpiUpfK,
    lpiCpfK,
    lpiUnknownLanK
}lpiLanguageT;

typedef enum {
    lpiConcatK,

    lpiUnknownOpK
}lpiOperatorKindT;

typedef enum {
    lpiNoErrorK,
    lpiSubVersionMismatchK,
    lpiNoWritingPermissionK,
    lpiNoReadingPermissionK,
    lpiInvalidFileK,

    //error
    lpiErrSubVersionMismatchK = 1,
    lpiErrNoWritingPermK,
    lpiErrNoReadingPermK,
    lpiErrInvalidFileK,

    //warning
    lpiWarnVcsVersionMismatchK = 20
}lpiErrorKindT;

/*lpi_open
 *This function will load the insturment.db if not loaded earlier. This is similer
 * to vpi_init one need to call before writing any power application
 */
LPI_INT32 lpi_open(const char* fileName);

/*lpi_close
 *This function is used to clean up allocated resource in LPI, especially
 *for shared library opened by LPI
 */
void lpi_close(void);

/* lpi_get
   This function can be used to get integer valued properties. This
   function returns 0 on failure, or the value of the property */

LPI_INT32 lpi_get(lpiIntPropertyT property, lpiHandleT handle);

/* lpi_get_str
   This function can be used to return string valued properties.
   The return value is 0 on failure. On success, the string value
   that is returned is expected to copied before a subsequent
   call to this function as the PLI does not guarantee persistence
   across calls */

const char* lpi_get_str(lpiStrPropertyT property, lpiHandleT handle);

/* lpi_handle
   This function can be used to traverse one-to-one relationships.
   The relation and the reference object are passed as parameters.
   If the requested relationship is not supported with respect to
   the class type of the reference handle, then an error will be
   generated */

lpiHandleT lpi_handle(lpiOneToOneT relation, lpiHandleT handle);

/* lpi_handle_by_name
   This function can be used to perform handle searches by name. The
   name passed here is expected to be in the format of name array,
   with the difference being that it could be absolute or relative to
   the reference object handle passed */
lpiHandleT lpi_handle_by_name(int argc, const char* argv[], lpiHandleT handle);

/* lpi_iterator
   This function can be used to traverse one-to-many relationships.
   The relation identifies the relationship and the handle should
   have a class type that supports that relationship */

lpiHandleT lpi_iterator(lpiOneToManyT relation, lpiHandleT handle);

/* lpi_scan
   This function can be used to scan through an iterator. The iterator
   creation and this function constitute the LPI mechanism to traverse
   one-to-many relationships */

lpiHandleT lpi_scan(lpiHandleT iterator);

/* lpi_release_handle
   This function should be used to release a LPI handle. All handles
   are created by the LPI and should be released by the users to
   prevent potential memory leaks */

void lpi_release_handle(lpiHandleT handle);

#ifdef  __cplusplus
}
#endif

#endif //_LPI_USER_H_
