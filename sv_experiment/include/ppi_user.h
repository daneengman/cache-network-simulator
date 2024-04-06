/*******************************************************************************
 * ppi_user.h
 * Power Programming Interface(PPI) will be used to access any power(upf/cpf)
 * related static/dynamic information.
 ********************************************************************************/
#ifndef PPI_USER_H
#define PPI_USER_H
#include <stdarg.h>
#ifdef  __cplusplus
extern "C" {
#endif
/* Sized variables */
#ifndef PPI_TYPES
#define PPI_TYPES
typedef int             PPI_INT32;
typedef unsigned int    PPI_UINT32;
typedef short           PPI_INT16;
typedef unsigned short  PPI_UINT16;
typedef char            PPI_BYTE8;
typedef unsigned char   PPI_UBYTE8;
typedef double          PPI_REAL;
#endif

/******************************** PPI handle typedef **********************/
typedef PPI_UINT32 *ppiHandleT;
/*PPI class/object kinds*/
typedef enum {
    ppiUpfNamedObjK = 3000,
    ppiPowerNetworkK,
    ppiPowerDomainK,
    ppiPowerStateTableK,
    ppiPstStateK,
    ppiPstEntryK,
    ppiHdl2UpfVctK,
    ppiUpf2HdlVctK,
    ppiBindCheckerK,
    ppiNameFormatK,
    ppiSaveUpfK,
    ppiLoadUpfK,
    ppiSupplyNetK,
    ppiSupplyNetPairK,
    ppiSupplyNetHandleK,
    ppiSupplySetK,
    ppiSupplySetHandleK,
    ppiSupplySetStateK,
    ppiSupplySetPowerFunctionK,
    ppiSupplySetGroundFunctionK,
    ppiSupplySetNWellFunctionK,
    ppiSupplySetPWellFunctionK,
    ppiSupplySetDeepNWellFunctionK,
    ppiSupplySetDeepPWellFunctionK,
    ppiSupplyPortK,
    ppiLogicNetK,
    ppiLogicPortK,
    ppiDesignPortK,
    ppiPowerSwitchK,
    ppiBoolConstK,
    ppiBoolExprIdK,
    ppiBoolExprUnaryK,
    ppiBoolExprBinaryK,
    ppiBoolExprConcatK,
    ppiOnPortStateK,
    ppiControlPortK,
    ppiAckPortK,
    ppiStateK,
    ppiLevelShifterStrategyK,
    ppiIsolationStrategyK,
    ppiRetentionStrategyK,
    ppiRetentionSignalK,
    ppiUpfElementK,
    ppiDesignScopeK,
    ppiUpfModelK,
    ppiUpfRetentionElementK,
    ppiRtnPortMapK,
    ppiMapRtnElementK,
    ppiScopeTableK,
    ppiAssertionControlK,
    ppiPowerStateSimstateK,
    ppiCurrentPowerStateK,
    ppiRootSupplyDriverK,
    ppiPowerSwitchSignatureK,
    ppiSupplyNetAnalysisK,
    ppiPowerScopeK,
    ppiIsolationCellFuncK,
    ppiAttributeValueK,
    ppiPortAttributeK, /*Until this point types arein the order of upf class type*/
    ppiIsolationCellK,
    ppiIsolationEnableK,
    ppiPowerNetK,
    ppiGroundNetK,
    ppiSaveSignalK,
    ppiRestoreSignalK,
    ppiSaveRestoreSignalK,
    ppiSaveAssertK,
    ppiRestoreAssertK,
    ppiSaveRestoreAssertK,
    ppiPowerSwitchStateK,
    ppiUnknownK
}ppiClassKindT;
/*PPI 1-2-1 relationships*/
typedef enum {
    ppiPowerNetwork = 3100,
    ppiPowerDomain,
    ppiPowerSwitch,
    ppiIsolationStrategy,
    ppiRetentionStrategy,
    ppiLevelShifterStrategy,
    ppiPrimaryPowerNet,
    ppiPrimaryGroundNet,
    ppiIsolationPowerNet,
    ppiIsolationGroundNet,
    ppiRetentionPowerNet,
    ppiRetentionGroundNet,
    ppiSRSNPowerNet,
    ppiSRSNGroundNet,
    ppiOutputSupplyPort,
    ppiScope,
    ppiIsolationEnable,
    ppiSaveSignal,
    ppiRestoreSignal,
    ppiSaveCondition,
    ppiRestoreCondition,
    ppiRetentionCondition,
    ppiLogicNet,
    ppiPowerStateSimstate,
    ppiCurrentPowerState,
    ppiPowerScope,
    ppiDesignScope,
    ppiPowerControlSupply,
    ppiConnectedSupplyNet,
    ppiPowerSwitchState,
    ppiPowerModesState,
    ppiRootSupplySet,
    ppiRelatedPowerNet,
    ppiRelatedGroundNet,
    ppiMappedIsoStrategy,
    ppiDriverObj,
    ppiBindCheckerStrategy
}ppiOneToOneT;
/*PPI 1-2-many relationships*/
typedef enum {
    ppiPowerDomains = 3200,
    ppiPowerSwitches,
    ppiIsolationStrategies,
    ppiRetentionStrategies,
    ppiLevelShifterStrategies,
    ppiElements,
    ppiSupplyNets,
    ppiAllSupplySets,
    ppiSupplySets,
    ppiSupplySetStates,
    ppiSupplySetFunctions,
    ppiSupplyPorts,
    ppiFlipFlops,
    ppiShadowFlops,
    ppiInputSupplyPorts,
    ppiControlPorts,
    ppiAckPorts,
    ppiSMutexes,
    ppiRMutexes,
    ppiRSMutexes,
    ppiVariables, /*It's for all kind of variable object in a PD,
                    iso,pst,ret etc. Varibale can be supplyPorts,
                    nets,simstate*/
    ppiPowerStateTables,
    ppiPstStates,
    ppiPstEntries,
    ppiPstLocalSupplies,
    ppiIsolationCells,
    ppiIsolatedNets,
    ppiPowerScopes,
    ppiPowerSwitchStates,
    ppiSupplyStates,
    ppiLowPowerLoads,
    ppiLowPowerDrivers,
    ppiConnectExprPorts,
    ppiSupplyTaskScopes,
    ppiSRSNCells,
    ppiSPACells,
    ppiIsolationEnables,
    ppiIsolationPowerNets,
    ppiIsolationGroundNets,
    ppiSRSNPowerNets,
    ppiSRSNGroundNets,
    ppiSPAControls,
    ppiSRSNStrategies,
    ppiSPAStrategies,
    ppiUpfBufferCells,
    ppiLogicNets
}ppiOneToManyT;
/*PPI integer or boolean properties*/
typedef enum {
    ppiLineNoP,
    ppiDirectionP,
    ppiIsSwitchPortP,
    ppiResolveNetP,
    ppiAckDelayP,
    ppiIsNoIsolationP,
    ppiClampValueP,
    ppiLocationP,
    ppiSenseP,
    ppiSignalLevelP,
    ppiUseRetentionAsPrimaryP,
    ppiClassKindP,
    ppiSignalPurposeP,
    ppiIsOffState,
    ppiIsDontCare,
    ppiIsIsolationCell,
    ppiIsIsolationEnable,
    ppiIsCellInputDataPin,
    ppiIsCellOutputDataPin,
    ppiIsBindCheckerCell,
    ppiIsDbAffected,
    ppiIsSupplyPortP,
    ppiIsExplicitSupplySetP,
    ppiIsPowerAware,
    ppiPowerFormatP,
    ppiIsSRSNCell,
    ppiIsSPACell,
    ppiSRSNStrategyIndexP,
    ppiSPAStrategyIndexP,
    ppiIsNonDisplayNode
}ppiIntPropertyT;

#ifndef PPI_PURPOSE_TYPES
#define PPI_PURPOSE_TYPES
typedef enum {
    ppiIsoShadowK,
    ppiIsoShadowPreK,
    ppiIsoEnableK,
    ppiIsoPowerK,
    ppiIsoGroundK,
    ppiRetShadowK,
    ppiRetStateK,
    ppiLsShadowK,
    ppiLsEnableK,
    ppiSpaShadowK,
    ppiSpaShadowPreK,
    ppiSpaEnableK,
    ppiSrsnShadowK,
    ppiSrsnShadowPreK,
    ppiSrsnPowerK,
    ppiSrsnGroundK,
    ppiMvsimFlagK,
    ppiUpfSimstateK,
    ppiSupplyNetPurposeK, //add postfix Purpose just to avoid confliction with ppiSupplyNetK 
    ppiLogicNetPurposeK, //add postfix Purpose just to avoid confliction with ppiSupplyNetK 
    ppiUnknownPurposeK
}ppiSignalPurposeT;
#endif

typedef enum {
    ppiMinVoltageP,
    ppiNomVoltageP,
    ppiMaxVoltageP
}ppiRealPropertyT;

/*PPI string properties*/
typedef enum {
    ppiNameP,
    ppiFullNameP,
    ppiRelativeNameP, //return name relative to its Power Scope.
    //e.g: tb/TOP/Switch/vout, return "Switch/vout"
    ppiKindStrP,
    ppiFileNameP,
    ppiFullFileNameP,
    ppiLpaBindTclP,
    ppiLpaBindFileListP,
    ppiDbInfoP,
    ppiPowerTopP,
    ppiSupplyExprP,
    ppiSimstateStrP,
    ppiCurrentWorkDirP,
    ppiConnectedLogicNetNameP,
    ppiPSTSupplyNames,
    ppiCurrentScopeP,
    ppiCellPositionLowConnNameP,
    ppiCellPositionHighConnNameP,
    ppiPortConnectExprStringP,
    ppiMhpiDataTypeStrP,
    ppiMhpiKindStrP,
    ppiPackedRangeStrP,
    ppiUnpackedRangeStrP,
    ppiBindCheckerResolvedParametersP
}ppiStrPropertyT;

typedef enum {
    ppi0 = 1,
    ppi1,
    ppiAny,
    ppiZ,
    ppiLatch,
    ppiValue
}ppiClampValueT;


typedef enum {
    ppiAutomatic = 1,
    ppiSelf,
    ppiOther,
    ppiFanout,
    ppiFanin,
    ppiFaninout,
    ppiParent,
    ppiSibling
}ppiLocationT;

typedef enum {
    ppiHigh = 1,
    ppiLow,
    ppiPosedge,
    ppiNegedge
}ppiSenseT;

typedef enum {
    ppiUnresolved = 1,
    ppiOneHot,
    ppiParallel,
    ppiParallelOneHot,
    ppiEither,
    ppiStrong,
    ppiWeak,
    ppiIsPowerNet,
    ppiIsGroundNet


}ppiResolveNetT;
typedef enum {
    ppiIn = 1,
    ppiOut,
    ppiInout
}ppiDirectionT;

typedef enum {
    ppiUpf = 1,
    ppiCpf
}ppiPowerFormatT;

typedef enum {
    ppiInPowerManagedHierFlag
}ppiGlobalFlagT;

/*ppi_init
 *This function will load the upfir/diir if not loaded earlier. This is similer
 * to vpi_init one need to call before writing any power application
 */
void ppi_init(void);

/*ppi_cleanup
 *This function is used to clean up allocated resource in PPI, especially
 *for shared library opened by PPI
 */
void ppi_cleanup(void);

/* ppi_get
   This function can be used to get integer valued properties. This
   function returns 0 on failure, or the value of the property */

PPI_INT32 ppi_get(ppiIntPropertyT property, ppiHandleT handle);

/* ppi_get_str
   This function can be used to return string valued properties.
   The return value is 0 on failure. On success, the string value
   that is returned is expected to copied before a subsequent
   call to this function as the PLI does not guarantee persistence
   across calls */

char* ppi_get_str(ppiStrPropertyT property, ppiHandleT handle);

/* ppi_handle
   This function can be used to traverse one-to-one relationships.
   The relation and the reference object are passed as parameters.
   If the requested relationship is not supported with respect to
   the class type of the reference handle, then an error will be
   generated */

ppiHandleT ppi_handle(ppiOneToOneT relation, ppiHandleT handle);

PPI_REAL ppi_get_real(ppiRealPropertyT property, ppiHandleT handle);

/*ppi_mhpi_handle
 *This will be used to get design to power information like power domain of an
 *instance
 */

ppiHandleT ppi_mhpi_handle(ppiOneToOneT relation, mhpiHandleT mhpiHandle);

/* ppi_handle_by_name
   This function can be used to perform handle searches by name. The
   name passed here is expected to be in the same format as the UPF
   path_name, with the difference being that it could be absolute or
   relative to the reference object handle passed */

ppiHandleT ppi_handle_by_name(ppiClassKindT type, char* name);

/* ppi_iterator
   This function can be used to traverse one-to-many relationships.
   The relation identifies the relationship and the handle should
   have a class type that supports that relationship */

ppiHandleT ppi_iterator(ppiOneToManyT relation, ppiHandleT handle);

/* ppi_scan
   This function can be used to scan through an iterator. The iterator
   creation and this function constitute the PPI mechanism to traverse
   one-to-many relationships */

ppiHandleT ppi_scan(ppiHandleT iterator);

/* ppi_mhpi_scan
   this function should be used when ppi_mhpi_iterator has been
   called to get an iterator.
   */
mhpiHandleT ppi_mhpi_scan (mhpiHandleT iter);

/* ppi_release_handle
   This function should be used to release a PPI handle. All handles
   are created by the PPI and should be released by the users to
   prevent potential memory leaks */

int ppi_release_handle(ppiHandleT handle);

ppiHandleT ppi_get_from_mhpi (mhpiHandleT inst);
/*
 *ppi_get_mhpi_handle
 * Return MHPI handle to the ppi handle to design instance/signal references
 */
mhpiHandleT ppi_get_mhpi_handle(ppiHandleT handle);
ppiHandleT ppi_mhpi_ppi_iterator(ppiOneToManyT relation,mhpiHandleT handle);
mhpiHandleT ppi_mhpi_iterator(ppiOneToManyT relation,mhpiHandleT handle);

#ifdef  __cplusplus
}
#endif

#endif /* PPI_USER_H */
