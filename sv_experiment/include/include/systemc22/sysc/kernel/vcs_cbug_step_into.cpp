/******************************************************************************

    vcs_cbug_step_into.cpp -- function to handle stepping into a process.
                        when control is handed to the debugger, user
                        will need to do a 'next' followed by a step
                        to see his/her process code.

    Copyright (c) 2000-2000 Synopsys, Inc.
    ALL RIGHTS RESERVED

******************************************************************************/


#ifndef WIN32
#include <signal.h>
#else
#include <crtdbg.h>
#endif
#include "sysc/kernel/sc_module.h"
#include "sysc/kernel/sc_process.h"


namespace sc_snps {

void vcs_cbug_wait_stop_here()
{
  static int counter = 0;
  counter++;                                            /* CBUG_MARKER_5 */
}

} // namespace sc_snps


namespace sc_core {

//------------------------------------------------------------------------------
//"sc_process_b::semantics"
//
// This inline method invokes the semantics for this object instance. 
// We check to see if we are initially in reset and then invoke the
// process semantics.
//------------------------------------------------------------------------------
void sc_process_b::semantics()
{
/* FIXME: the assert statement may break CBug cross-stepping, so we disable them
   for now
    assert( m_process_kind != SC_NO_PROC_ );
*/
	m_throw_type = ( m_reset_p && m_reset_p->read() == m_reset_level ) ?
		THROW_RESET : THROW_NONE;
#   ifndef SC_USE_MEMBER_FUNC_PTR
        m_semantics_method_p->invoke( m_semantics_host_p );
#   else
        if (lineno>=0)
            (m_semantics_host_p->*m_semantics_method_p)();                    /* CBUG_MARKER_3 */ 
        else
            (m_semantics_host_p->*m_semantics_method_p)();                    /* CBUG_MARKER_4 */ 
#   endif
}


/*
  There is a cross-dependency between this source file and CBug stepping
  for SystemC processes. See also file hints for CBUG_MARKER_* in files
  vhdl-src/sim/mixedhdl/ucli/cbug/stepnext.C, state3()
  vhdl-src/sim/mixedhdl/ucli/cbug/init.C, sysc_macro_functions_22

  If you add/delete src lines above such that the CBUG_MARKER_* lines
  move, then look for these CBUG_MARKER_* strings in the CBug sources
  at vhdl-src/sim/mixed/ucli/cbug/... and adjust lines numbers as necessary.
*/


} // namespace sc_core
