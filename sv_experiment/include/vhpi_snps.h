/*
 * vhpi_snps.h
 *
 * The VHDL procedural interface nonstandard header file.
 *
 */

#ifndef VHPI_SNPS_H
#define VHPI_SNPS_H

#include "vhpi_user.h"

#ifdef __cplusplus
extern "C" {
#endif

/* vhpi_release_hold_keep_value
   This function can be used to release a signal or port that is on hold.
   A signal/port can be placed on hold by choosing vhpiForce or
   vhpiForce | vhpiForceEvent for the vhpi_put_value flags parameter */

vhpiIntT vhpi_release_hold_keep_value(vhpiHandleT objectHandle);
vhpiIntT vhpi_release_hold_keep_schedule_value(vhpiHandleT objectHandle);
/* vhpi_is_event_handle
 * Returns 1, if the handle belongs to the event-based part of the
 *            design being simulated on Scirocco
 *         0, otherwise
 */

vhpiIntT vhpi_is_event_handle(vhpiHandleT handle);


/* vhpi_is_cycle_handle
 * Returns 1, if the handle belongs to the cycle-based part of the
 *            design being simulated on Scirocco
 *         0, otherwise
 */

vhpiIntT vhpi_is_cycle_handle(vhpiHandleT handle);


/* vhpi_is_compact_handle
 * Returns 1, if the handle corresponds to the event-based compact
 *         formatted part of the design being simulated on Scirocco
 *         0, otherwise
 */

vhpiIntT vhpi_is_compact_handle(vhpiHandleT handle);

/* vhpi_is_spm_handle
 * Returns 1, if the handle corresponds to (event-based) object
 *          stored in format of sparse memory
 *         0, otherwise
 */
vhpiIntT vhpi_is_spm_handle(vhpiHandleT handle);


/* This function is a utility function that can be used to do delayed
   assignments. It is different from a VHDL assignment statement in that
   it does not access any drivers, but instead will change the effective
   value of signals, ports of mode in and the in-side of inout ports,
   and the driving value of ports of mode out and the out-side of inout
   ports */

int vhpi_put_value_delayed(vhpiHandleT objectHandle, vhpiValueT* pValue,
                           vhpiPutValueFlagsT flags, vhpiTimeT delay);

/* vhpi_get_transaction_time
   This function can be used to get the scheduled transaction time.
   handle is a transaction handle */

void vhpi_get_transaction_time(vhpiHandleT handle, vhpiTimeT* time);

/* to get the time resolution of Scirocco
 * FS -> -15, 10 FS-> -14, ..., SEC -> 0, 100 SEC ->2
 */
int vhpi_get_resolution(void);

/* This function is a utility function that can be used to clone (copy)
   a vhpi handle. Currently used in MVhpiDriver.C an MVhpiLoad.C */

void vhpi_handle_clone(vhpiHandleT objectHandle);
vhpiHandleT vhpiMxRootInstsIterator();


typedef void (*vhpiCbfnT)(vhpiCbDataT*);

/*
 * VHPI Fli (breakpoint at file:line) Callback Data Structure
 * IMPORTANT NOTE: assert (sizeof(vhpiFliCbDataT) == sizeof(vhpiCbDataT))
 *                 the time and value fields were replced by file and line.
 * To register an Fli callback, use vhpiCbStmt reason with obj = NULL.
 */
typedef struct vhpiFliCbDataS
{
    vhpiCbReasonT reason;             /* callback reason */
    vhpiCbfnT     cbf;                /* callback function */
    vhpiHandleT   obj;                /* trigger object */
    char*         file;               /* file name */
    int           line;               /* line number */
    void*         user_data;          /* to be passed to the callback function */
}
vhpiFliCbDataT;

typedef struct vhpiPartValueDataS {
    int offset;
    int size;
} vhpiPartValueDataT;

vhpiPartValueDataT* vhpi_get_part_value_data (vhpiHandleT vhpiHdl);

int vhpi_schedule_transaction_part(vhpiHandleT objectHandle,
                                   vhpiValueT** pValue,
                                   int numValues,
                                   vhpiTimeT* pDelay,
                                   int delayMode,
                                   vhpiTimeT* pPulseRej,
                                   vhpiPartValueDataT* valueData);

int vhpi_schedule_subelem_transaction(vhpiHandleT objectHandle,
                                      vhpiHandleT subelemHdl,
                                      vhpiValueT** pValue,
                                      int numValues,
                                      vhpiTimeT* pDelay,
                                      int delayMode,
                                      vhpiTimeT* pPulseRej);

/* Requied by FLI2VHPI converter create kind functions
 */

vhpiHandleT vhpi_create_region (vhpiHandleT parentRegionHdl,
                                char* regionName);
vhpiHandleT vhpi_create_process (vhpiHandleT parentRegionHdl,
                                 char* processName);
vhpiHandleT vhpi_create_signal (vhpiHandleT regionHdl,
                                vhpiHandleT signalTypeHdl,
                                char* signalName);
vhpiHandleT vhpi_create_array_type (vhpiHandleT regionHdl,
                                    vhpiHandleT elementTypeHdl,
                                    vhpiIntT leftBound,
                                    vhpiIntT rightBound,
                                    char* typeName);
vhpiHandleT vhpi_create_enum_type (vhpiHandleT regionHdl,
                                   vhpiIntT literalsNum,
                                   char** ppLiterals,
                                   char* typeName);
vhpiHandleT vhpi_create_real_type (vhpiHandleT regionHdl, char* typeName);
vhpiHandleT vhpi_create_scalar_type (vhpiHandleT regionHdl,
                                     vhpiIntT leftMost,
                                     vhpiIntT rightMost,
                                     char* typeName);
vhpiHandleT vhpi_create_time_type (vhpiHandleT regionHdl, char* typeName);
vhpiHandleT vhpi_move_driver (vhpiHandleT driverHdl,
                              vhpiHandleT newProcessHdl);
int         vhpi_remove_driver (vhpiHandleT driverHdl);

vhpiHandleT vhpi_handle_by_name_snps (char* name, vhpiHandleT regionHdl);

vhpiCbDataT* vhpi_get_simulated_net(vhpiCbDataT* cbData);
vhpiHandleT vhpi_file_line_instance_iterator(const char* file, vhpiIntT line, const char* objName);

int vhpi_get_value_snps(vhpiHandleT objectHandle, vhpiValueT* pValue,
                        vhpiPartValueDataT* vhpiPartValueData);
int vhpi_put_value_snps(vhpiHandleT objectHandle,
                        vhpiValueT* pValue, vhpiPutValueFlagsT flags,
                        vhpiPartValueDataT*vhpiPartValueData);
vhpiIntT vhpi_is_record_type(vhpiHandleT objHdl);
vhpiIntT vhpi_is_foreign_shell(vhpiHandleT objHdl);

vhpiHandleT vhpiHandleByName(char *name, void *handle);
vhpiHandleT vhpi_register_alp_cb(vhpiCbDataT* pCbData, unsigned);
vhpiHandleT mt_vhpi_register_alp_cb(vhpiCbDataT* pCbData);
void* vhpi_get_userdata_alp(vhpiCbDataT*);

/* vhpi_setEndOfProcessToBack controls if a EndOfProcess
 * event is put in the front or back of the list of events
 * The list is executed from front to back
 * The default is to place current input a the front
 * For "force -drive" events need to placed at the back so
 * the last event is executed last.
 */
void vhpi_setEndOfProcessToBack(int toBack);
/******************************************************
 objHdl - VHPI handle
 Returns base prefix handle if objHdl is
 indexed/selected/slice object. Otherwise returns NULL.
 Examples:
 objHdl is handle of "basePrefix(1)(2)" object
 returns handle of "basePrefix" object
 objHdl is handle of "basePrefix(1)(2)(0 to 2)" object
 returns handle of "basePrefix" object
 objHdl is handle of "basePrefix.rec1_elem.rec2_elem" object
 returns handle of "basePrefix" object
 *****************************************************/
vhpiHandleT vhpi_handle_base_prefix (vhpiHandleT objHdl);

/********************************************************
 * implemented to scan VHPI root instances instanced in Verilog MX
 * dummyPar parameter introduced to resolve mhpiVhpiDummy.c complain
 */
vhpiHandleT vhpi_iterator_vlog_instances (int dummyPar);

void vhpi_iterator_SetLPFilter(int i);
int vhpi_GetLPDesignFlag(void);

vhpiHandleT getVhpiHandleFromScalarOffset(vhpiHandleT obj, unsigned int offset, unsigned int length);

void vhpi_save_force_list(void);
void vhpi_restore_force_list(void);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif
