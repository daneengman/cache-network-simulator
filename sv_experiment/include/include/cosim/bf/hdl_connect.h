// This may look like C code, but it is really -*- C++ -*-
// 
// hdl_connect.h -- 
// Copyright Synopsys 2002
// Author          : Ric Hilderink
// Created On      : Fri Sep 13 12:08:01 2002
// Status          : none
// 


#ifndef _hdl_connect_h_
#define _hdl_connect_h_


#include "systemc.h"
#include "hdl_signal.h"

#include "hdl_connect_v.h"

/***************************************************************
 * Template definitions of hdl_connect according the specification
 * of the Verification Working Group of OSCI
 *
 * hdl_connect contains four parameters:
 * - sc_signal<T> &sig : a reference to the SystemC signal to 
 *                       which it is hooked
 * - const char *hdl_signal : a full pathname of the HDL object
 * - hdl_direction d : This can be HDL_INPUT: from HDL to SystemC
 *                                 HDL_OUTPUT: from SystemC to HDL
 *                     NOTE: HDL_INOUT is not supported yet
 * - int simid : identifier for the simulator to be used: 
 *               0: any HDL simulator
 *               1: first Verilog simulator
 *               2: first VHDL simulator
 *              >2: free
 * 
 * NOTE: hdl_connect(sc_clock &sig, ...) connects a sc_clock object
 *       to the HDL world. sc_clock is a sc_module object, so this
 *       is an extension of the specification.
 ******************************************************************/

template < class T >
void hdl_connect(sc_signal<T> &sig, const char *hdl_signal, hdl_direction d, int simid)
{
  switch(simid)
    {
    case HDL_vcs:
      hdl_connect_v(sig, hdl_signal, d, simid); break;
    default:
      // not supported
      break;
    }
}


inline void hdl_connect(sc_clock &sig, const char *hdl_signal, hdl_direction d, int simid)
{
  switch(simid)
    {
    case HDL_vcs:
      hdl_connect_v(sig, hdl_signal, d, simid); break;
    default:
      // not supported
      break;
    }
}

#endif
