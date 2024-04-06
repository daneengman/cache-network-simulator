/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2011 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  sc_utils_ids.h -- Report ids for the utils code.

  Original Author: Martin Janssen, Synopsys, Inc., 2002-01-17

  CHANGE LOG AT END OF FILE
 *****************************************************************************/

#ifndef SC_UTILS_IDS_H
#define SC_UTILS_IDS_H

// ----------------------------------------------------------------------------
//  Report ids (utils)
//
//  Report ids in the range of 800-899.
// ----------------------------------------------------------------------------

#ifndef SC_DEFINE_MESSAGE
#define SC_DEFINE_MESSAGE(id,unused1,unused2) \
    namespace sc_core { extern const char id[]; }
namespace sc_core {
    extern const char SC_ID_REGISTER_ID_FAILED_[]; // in sc_report_handler.cpp
}
#endif

SC_DEFINE_MESSAGE(SC_ID_STRING_TOO_LONG_,
		  801, "string is too long")
SC_DEFINE_MESSAGE(SC_ID_FRONT_ON_EMPTY_LIST_,
		  802, "attempt to take front() on an empty list")
SC_DEFINE_MESSAGE(SC_ID_BACK_ON_EMPTY_LIST_,
		  803, "attempt to take back() on an empty list")
SC_DEFINE_MESSAGE(SC_ID_IEEE_1666_DEPRECATION_,
		  804, "/IEEE_Std_1666/deprecated" )
SC_DEFINE_MESSAGE(SC_ID_VECTOR_INIT_CALLED_TWICE_,
                  805, "sc_vector::init has already been called" )
SC_DEFINE_MESSAGE(SC_ID_VECTOR_INIT_INVALID_CONTEXT_,
                  806, "sc_vector::init called from invalid object context" )
SC_DEFINE_MESSAGE(SC_ID_VECTOR_BIND_EMPTY_,
                  807, "sc_vector::bind called with empty range" )
SC_DEFINE_MESSAGE(SC_ID_VECTOR_NONOBJECT_ELEMENTS_,
                  808, "sc_vector::get_elements called for element type "
                       "not derived from sc_object" )

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:
    
  Alex Riesen, Synopsys, Inc., 2003-02-02
  ported to SystemC 2.1 exception reporting.
    
 *****************************************************************************/

// $Log: sc_utils_ids.h,v $
// Revision 1.5  2011/08/26 20:46:20  acg
//  Andy Goodrich: moved the modification log to the end of the file to
//  eliminate source line number skew when check-ins are done.
//
//

#endif

// Taf!