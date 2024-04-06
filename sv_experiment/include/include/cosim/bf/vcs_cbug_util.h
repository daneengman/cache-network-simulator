/*****************************************************************************

  This code has been developed by Synopsys, Inc.
  COPYRIGHT (C) 2002, SYNOPSYS INC., ALL RIGHTS RESERVED.

 *****************************************************************************/

/*****************************************************************************

  vcs_cbug_util.h - Utilities

  Original Author: Ulli Holtmann, Synopsys, Inc.

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#ifndef VCS_CBUG_UTIL_H
#define VCS_CBUG_UTIL_H


namespace sc_snps {

//
// Class is used for printing diagnostic messages used in regressions
//

class vcs_cbug_diagnosis
{
public:
    // The prefix may contain an optional filename in the
    // format "[file=abc.log]rest of prefix".
    // Filenames "stdout" and "stderr" are recognized.
    // Default is stderr
    // 
    // Examples:                                           File         prefix
    // vcs_cbug_diagnosis a("-xyz- ");                    stderr       "-xyz- " 
    // vcs_cbug_diagnosis a("[file=/usr/a/b.log]-xyz- "); /usr/a/b.log "-xyz- "
    // vcs_cbug_diagnosis a("[file=/dev/stderr]-xyz- ");  stderr       "-xyz- " 
    // vcs_cbug_diagnosis a("[file=/dev/stdout]-xyz- ");  stdout       "-xyz- "  
    // vcs_cbug_diagnosis a("[file= abc ] -xyz- ");       stderr       "[file= abc ] -xyz- "
    vcs_cbug_diagnosis(const char * fname_and_prefix);

    // Explicit file pointer. Use prefix as it is
    vcs_cbug_diagnosis(const char * prefix, void* fp);
    ~vcs_cbug_diagnosis();
    void print(const char* s);
    void printf(const char* fmt, ...);
    void printf_noprefix(const char* fmt, ...);

    bool active() const { return m_fp != 0; }
    const char * prefix() const { return m_prefix; }

    void open(const char * prefix, void* fp);
    void close();

private:
    char * m_prefix;
    bool m_print_time;
    bool m_print_delta;
    void * m_fp;
    bool close_fp_on_destr;
};


// Register call-back from main function
// 
// The main function provided by Studio in kernel/sc_main.cpp will call
// a registered function during different phases. This allows to couple
// other simulators like Babelfish or other things to the SystemC
// simulation. See the enum below for a description of phases.
//
// The registered function will get called with the phase and several arguments
// which can not be obtained otherwise. These are currently the command
// line arguments.
// 
// Note: this solution requires you to register just a single function but
// be aware that your function is called multiple times (during each phase)
// and with arguments (argc,argv) which it may not need during a specific
// phase. A different solution might be define different function types
// and register them individually with the specific phases.
//
// How to register the function:
//    vcs_cbug_cb_fn( my_func );
// How to retrieve the currently registered function:
//    func = vcs_cbug_cb_fn( 0 );
// How to un-register the function:
//    currently not supported

// #ifndef BF_OSCI
enum vcs_cbug_cb_phase  { 
    vcs_cbug_cb_phase_earliest, // called immediately at the beginning of main
    vcs_cbug_cb_phase_after_initialize,       // called after Studio initilization has occured
    vcs_cbug_cb_phase_sim_done,               // called after Studio finishes running the simulation
    vcs_cbug_cb_phase_cleanup                 // called just before main() ends
};
// #endif

typedef void (*vcs_cbug_cb_fn_type)( vcs_cbug_cb_phase phase, int argc, char** argv );
extern "C"
vcs_cbug_cb_fn_type vcs_cbug_cb_fn( vcs_cbug_cb_fn_type fn );


// Execute simulate at the current point in time until no more runable
// processes and delta events are present Then check whether the
// simulation has to be aborted due to errors or calls to sc_stop()
// and return true if so. Do not consider timed events that fall into 
// future wall-clock time.
int vcs_cbug_simulate_crunch( sc_core::sc_simcontext* );

// Move time forward towards the next timed event and trigger all
// timed events at that time. Just trigger events which results in
// processes made runable but do not execute the processes. Do not
// advance time beyond until_t.
void vcs_cbug_simulate_next_until( sc_core::sc_simcontext*, const sc_core::sc_time & );

// Return the wall-clock time when the next timed event will occur.
const sc_core::sc_time &vcs_cbug_get_next_time( sc_core::sc_simcontext* );

// Update trace and streaming files
void vcs_cbug_update_traces( sc_core::sc_simcontext* );

// Check for user termination outside the usual crunch
bool vcs_cbug_simulation_stopped( sc_core::sc_simcontext* );

} // namespace sc_snps

#endif
