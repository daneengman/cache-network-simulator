//============================================================================
//  SYNOPSYS CONFIDENTIAL - This is an unpublished, proprietary work of
//  Synopsys, Inc., and is fully protected under copyright and trade secret
//  laws. You may not view, use, disclose, copy, or distribute this file or
//  any information contained herein except pursuant to a valid written
//  license from Synopsys.
//============================================================================

#ifndef _systemc_user_h_
#define _systemc_user_h_

#include "systemc.h"

#include <string>

#if SYSTEMC_VERSION >= 20050714
#define SC_CORE sc_core::
#define SC_SNPS sc_snps::
#define NS_SC_SNPS namespace sc_snps {
#define NS_SC_SNPS_END }
#else
#define SC_CORE
#define SC_SNPS
#define NS_SC_SNPS
#define NS_SC_SNPS_END
#endif

namespace sc_snps {

//
// sc_snps::GetName( sc_object* )
//
//  Returns the instance name (short name) of the given object
//  or "No Name" on error.
//
const char *GetName(sc_core::sc_object *obj);

//
// sc_snps:: GetFullName( sc_object* )
//
//  Returns the full logical name of the given object.
//  or "No Name" on error.
//  The full name can contain hierarchical sub-paths of other domains,
//  like Verilog/VHDL.
//
const char *GetFullName(sc_core::sc_object *obj);

// Variant of GetFullName() that also works for ports, signals
//
// Note that it returns a std::string, not char*, to avoid problems with
// lifetime of returned name.

std::string GetFullName2(const sc_core::sc_object* scobj);

//
// sc_snps::sc_object_handle_by_name( path )
//
//  Locate SystemC object by mixed HDL/SystemC path name.
//  Return 0 if not found or not an SystemC object.
//
//
// sc_snps_sc_object_handle_by_name( path )
//
//  Same as sc_object_handle_by_name() but with 'extern C' API
//
sc_core::sc_object* sc_object_handle_by_name(const char* path) ;


//
// sc_snps::request_to_use_pthreads( bool use_pthreads )
//
// Wish for either pthreads or quickthreads, return true if wish
// is granted, return false+produce warning if not possible. This
// function must be called before the first call to sc_start().
// Best place is to call it early on in sc_main() or from a static
// constructor.
// Available in SC 2.2. only
//
bool request_to_use_pthreads(bool use_pthreads);

//
// sc_snps::use_pthreads()
//
// Query which thread package is used. Return true if POSIX threads
// (pthreads) are used, returns false if quickthreads are used.
// Available in SC 2.2. only
//
bool use_pthreads();

// Available in SC 2.2. only
enum vmm_log_alignment { NoVMMLog, SingleVMMLog, MultipleVMMLogs };
enum uvm_log_alignment { NoUVMLog, SingleUVMLog, MultipleUVMLogs };
bool  align_sc_report_with_VMM(vmm_log_alignment);
bool  align_sc_report_with_UVM(uvm_log_alignment);

int sc_set_stack_size_sc_main(const char* size_str);

typedef enum {
    VCS_SYSC_LOGIC_NAME = 1,    // all sc_object::name() returns logical names when 2nd argument = 1
    VCS_SYSC_PHYS_NAME,         // all sc_object::name() returns physical names when 2nd argument = 1
    VCS_SYSC_LOGIC_NAME_TGL,    // sc_object::name() returns logical name only once
    VCS_SYSC_END_OF_LIST = 999
} SysCConfigure_e;

int sysc_configure(SysCConfigure_e, int);
int sysc_configure(SysCConfigure_e);

// enable/disable protected region for execution 
 int BfGuard(bool, int); 

}; // namespace sc_snps

extern "C" void* sc_snps_sc_object_handle_by_name(const char* path);

//
// bool hdl_elaboration_only()
//
// returns true when the simulator is still elaborated, and false
// when the simulator is fully build.
// The simulator is in elaboration phase when:
// - SystemC-on-top design: to determine the inner layer of HDL
// - -sysc=adjust_timeres : to determine whether the time resolution is OK
// - Verilog-SystemC-Verilog: to determine the inner layer of HDL
//
extern "C" bool hdl_elaboration_only();

//
// bf_delta_trace( bool flag )
//
//  Enables / Disables delta cycle tracing for SystemC objects
//  This function can be called anytime to turn tracing on and off
//  Return value is the previous setting.
//
extern "C" int bf_delta_trace(int flag);

//
// int disable_multiple_dki_driver_check(int flag)
//
// Disables (1) / Enables (0) a check for multiple writers
// on a sc_signal class object when at least one of the writers
// is driven by HDL. The old value is returned.
// The default value is 0
//
extern "C" int disable_multiple_dki_driver_check(int flag);
        
//
// Configure VPD dumping of sc_fifo
//
// sc_snps_cbug_fifo_set_limit_num_objects( int num, sc_object* ptr );
//
//  set max number of objects to be printed.
//  Negative value: dump nothing; value=0: dump all;
//  positive value <n>: print no more than <n> objects.
//  Applies to specific fifo (ptr!=0) or is default for all (ptr==0)
//
//
// sc_snps_cbug_fifo_set_show_proc (bool enable_showing_processes)
//
//  enable/disable printing information about processes
//

extern "C" int sc_snps_cbug_fifo_set_limit_num_objects (int num, sc_core::sc_object* fifo_ptr=0);
extern "C" int sc_snps_cbug_fifo_set_show_proc (int enable_showing_processes);

extern "C" bool vcdplussourcenames(bool flag);
extern "C" bool vcdplusplainmembers(bool flag);
extern "C" bool vcdplusstructtypes(bool flag);

/* APIs for TLI-4 Direct access to SV variables from SC */
extern "C" long long tli_get_int64(const char* path);
extern "C" void tli_set_int64(long long val, const char* path);
extern "C" unsigned long long tli_get_uint64(const char* path);
extern "C" void tli_set_uint64(unsigned long long val, const char* path);
extern "C" sc_logic tli_get_logic(const char* path);
extern "C" void tli_set_logic(sc_logic val, const char* path);
extern "C" sc_bv_base tli_get_bv(const char* path);
extern "C" void tli_set_bv(const sc_bv_base& val, const char* path);
extern "C" sc_lv_base tli_get_lv(const char* path);
extern "C" void tli_set_lv(const sc_lv_base& val, const char* path);
extern "C" std::string tli_get_string(const char* path);
extern "C" void tli_set_string(const char* val, const char* path);
extern "C" int sc_main_register(int (*)(int, char **));

#define SNPS_REGISTER_SC_MAIN(mymain) \
    static int _isRegistered = sc_main_register(mymain);

#define SNPS_REGISTER_SC_MODULE(mytopmodule) \
    extern "C" int sc_main(int,char**) { \
        mytopmodule top_inst(#mytopmodule); \
        sc_start(); \
        return 0; \
    }


#endif


#ifndef TLI_SPAWN_DECLARED
#define TLI_SPAWN_DECLARED

#include "sysc/kernel/sc_spawn.h"
#include "sysc/kernel/sc_join.h"
#include "sysc/kernel/sc_boost.h"

namespace sc_snps {

typedef void (*cb_fnt)(void*);

template<typename T>
class tli_spawn_object : public sc_core::sc_spawn_object<T> {
public:
    tli_spawn_object( T object,
                      cb_fnt cb_done_fn, void* cb_done_arg) :
        sc_core::sc_spawn_object<T>( object ),
        m_cb_done_arg(cb_done_arg)
    {
        m_cb_done_fn = cb_done_fn;
    }

    virtual void semantics()
    {
        sc_core::sc_spawn_object<T>::semantics();
        if (m_cb_done_fn)
            (*m_cb_done_fn)(m_cb_done_arg);
    }

protected:
    cb_fnt m_cb_done_fn;
    void*  m_cb_done_arg;
};

template <typename T>
inline sc_core::sc_process_handle tli_spawn
(T object,
 cb_fnt cb_done_fn,
 void* cb_done_arg,
 const char* name_p = 0,
 const sc_core::sc_spawn_options* opt_p = 0)
{
    sc_core::sc_simcontext* context_p;
    tli_spawn_object<T>*  spawn_p;

    context_p = sc_core::sc_get_curr_simcontext();

    spawn_p = new tli_spawn_object<T>(object, cb_done_fn, cb_done_arg);
    if ( !opt_p || !opt_p->is_method() )
    {
        sc_core::sc_process_handle thread_handle = context_p->create_thread_process
                ( name_p, true,
                  SC_MAKE_FUNC_PTR(sc_core::sc_spawn_object<T>,semantics),
                  spawn_p, opt_p
                );
        return thread_handle;
    }
    else
    {
        sc_core::sc_process_handle method_handle = context_p->create_method_process
                ( name_p, true,
                  SC_MAKE_FUNC_PTR(sc_core::sc_spawn_object<T>,semantics),
                  spawn_p, opt_p
                );
        return method_handle;
    }
}

template<typename T>
class tli_spawn_object_v : public sc_core::sc_spawn_object_v<T> {
public:
    tli_spawn_object_v( typename T::result_type* r_p, T object,
                        cb_fnt cb_done_fn, void* cb_done_arg) :
        sc_core::sc_spawn_object_v<T>( r_p,object ),
        m_cb_done_arg(cb_done_arg)
    {
        m_cb_done_fn = cb_done_fn;
    }

    virtual void semantics()
    {
        sc_core::sc_spawn_object_v<T>::semantics();
        if (m_cb_done_fn)
            (*m_cb_done_fn)(m_cb_done_arg);
    }

protected:
    cb_fnt m_cb_done_fn;
    void*  m_cb_done_arg;
};

template <typename T>
inline sc_core::sc_process_handle tli_spawn
(typename T::result_type* r_p,
 T object,
 cb_fnt cb_done_fn,
 void* cb_done_arg,
 const char* name_p = 0,
 const sc_core::sc_spawn_options* opt_p = 0)
{
    sc_core::sc_simcontext* context_p;
    tli_spawn_object_v<T>*  spawn_p;

    context_p = sc_core::sc_get_curr_simcontext();

    spawn_p = new tli_spawn_object_v<T>(r_p, object, cb_done_fn, cb_done_arg);
    if ( !opt_p || !opt_p->is_method() )
    {
        sc_core::sc_process_handle thread_handle = context_p->create_thread_process
                ( name_p, true,
                  SC_MAKE_FUNC_PTR(sc_core::sc_spawn_object_v<T>,semantics),
                  spawn_p, opt_p
                );
        return thread_handle;
    }
    else
    {
        sc_core::sc_process_handle method_handle = context_p->create_method_process
                ( name_p, true,
                  SC_MAKE_FUNC_PTR(sc_core::sc_spawn_object_v<T>,semantics),
                  spawn_p, opt_p
                );
        return method_handle;
    }
}
} // namespace sc_snps

#endif // !defined(TLI_SPAWN_DEFINED)
