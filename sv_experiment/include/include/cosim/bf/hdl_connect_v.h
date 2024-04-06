// This may look like C code, but it is really -*- C++ -*-
// 
// hdl_connect_v.h -- 
// Copyright Synopsys 2002
// Author          : Ric Hilderink
// Created On      : Fri Sep 13 12:08:01 2002
// Status          : none
// 


#ifndef _hdl_connect_v_h_
#define _hdl_connect_v_h_


#include "systemc.h"
#include "hdl_signal_v.h"


#define sc_stop bf_sc_stop
extern void bf_sc_stop();
extern void alterString(std::string &, const char *);

/****************************************************************
 * hdl_connect(... HDL_OUTPUT)   // from SystemC to HDL
 *
 * --------+-------->sc_signal
 *         |
 *         |         +------------+
 *         +-------->| sc_outConn 
 *                   |          -------> hdl_signal
 *                   +------------+
 *
 * sc_outConn is a module, sensitive on value changes of the
 * signal it is attached to. Inside this module the input port is
 * connected to a hdl_signal. This signal doesn't have a drain. 
 *
 * A special sc_outConnClk module attaches to a sc_clock object. 
 *
 * hdl_connect(... HDL_INPUT)   // from HDL to SystemC
 *
 *               +-----------+
 *                 sc_inConn |----->sc_signal
 * hdl_signal --------->     |
 *               +-----------+
 *
 * sc_inConn is a module which doesn't have an input port, but only one
 * output port. The output port is driven by a hdl_signal. The module
 * contains a method that is sensitive to changes of this hdl_signal, and
 * will pass the values through. 
 ***********************************************************************/

template < class T >
SC_MODULE(bf_inConn_v)
{
 public:
  sc_out<T> outx;
  hdl_signal_v<T> sig;

  SC_HAS_PROCESS(bf_inConn_v);

  bf_inConn_v(sc_module_name name_, const char *hdl_signal, int simid, const char *port_name, int mode) 
    : sc_module(name_), sig(hdl_signal, HDL_OUTPUT, simid, port_name, mode)
    {
      SC_METHOD(bf_inConn_action);
      sensitive << sig;
    }
  void bf_inConn_action()
    {
      outx = sig.read();
    }
  const char *kind() const { return "dki_signal_verilog"; }
  void hdl(sc_signal<T> &s) { sig.s(s); }
};

template < class T >
SC_MODULE(bf_outConn_v)
{
 public:
  sc_in<T> ina;
  hdl_signal_v<T> sig;

  SC_HAS_PROCESS(bf_outConn_v);

  bf_outConn_v(sc_module_name name_, const char *hdl_signal, int simid, const char *port_name, int mode) 
    : sc_module(name_), sig(hdl_signal, HDL_INPUT, simid, port_name, mode)
    {
      SC_METHOD(bf_outConn_action);
      sensitive << ina;
    }
  void bf_outConn_action()
    {
      sig.write_conn(ina.read());
    }
  const char *kind() const { return "dki_signal_verilog"; }
  void hdl(sc_signal<T> &s) { sig.s(s); }
};

SC_MODULE(bf_outConnClk_v)
{
 public:
  sc_in_clk ina;
  hdl_signal_v<bool> sig;

  SC_HAS_PROCESS(bf_outConnClk_v);

  bf_outConnClk_v(sc_module_name name_, const char *hdl_signal, int simid) 
    : sc_module(name_), sig(hdl_signal, HDL_INPUT, simid)
    {
      SC_METHOD(bf_outConnClk_action);
      sensitive << ina;
    }
  void bf_outConnClk_action()
    {
      sig.write(ina.read());
    }
  const char *kind() const { return "dki_signal_verilog"; }
};

/***************************************************************
 * Template definitions of hdl_connect according the specification
 * of the Verification Working Group of OSCI
 *
 * hdl_connect_v contains four parameters:
 * - sc_signal<T> &sig : a reference to the SystemC signal to 
 *                       which it is hooked
 * - const char *hdl_signal : a full pathname of the HDL object
 * - hdl_direction d : This can be HDL_INPUT: from HDL to SystemC
 *                                 HDL_OUTPUT: from SystemC to HDL
 *                     NOTE: HDL_INOUT is not supported yet
 * - int simid : identifier for the simulator to be used:
 *               ignored. Must be an integer value, but value
 *               is not used.
 * 
 * NOTE: hdl_connect(sc_clock &sig, ...) connects a sc_clock object
 *       to the HDL world. sc_clock is a sc_module object, so this
 *       is an extension of the specification.
 ******************************************************************/

template < class T >
void hdl_connect_v(sc_signal<T> &sig, const char *hdl_signal, hdl_direction d, int simid,
		   const char *port_name = 0, int mode = 0)
{
  std::string hdl_conn_name = sig.name();
  hdl_conn_name += "_hdl";
  while (hdl_conn_name.find(".") != std::string::npos)
    hdl_conn_name.replace(hdl_conn_name.find("."), 1, "_");
  hdl_conn_name = BF_register_connection(sig.name(), hdl_conn_name, sig);

  switch(d)
    {
    case HDL_INPUT:
      {
	bf_inConn_v<T> *bfin = new bf_inConn_v<T>(hdl_conn_name.c_str(), hdl_signal, HDL_vcs, port_name, mode);
	bfin->outx(sig);
	bfin->hdl(sig);
      }
      break;
    case HDL_OUTPUT:
      {
	bf_outConn_v<T> *bfout = new bf_outConn_v<T>(hdl_conn_name.c_str(), hdl_signal, HDL_vcs, port_name, mode);
	bfout->ina(sig);
	bfout->hdl(sig);
      }
      break;
    case HDL_INOUT:
	// probably unreachable for VcsSystemC, relict from Studio
      cerr << "INOUT ports are not supported by this release of DKI.\n"
	   << "Please use the pipes or socket connection interface.\n";
      exit(2);
    default:
      exit(2);
    }
}

#if SYSTEMC_VERSION >= 20110630

template < class T >
void hdl_connect_v(sc_signal<T,SC_ONE_WRITER> &sig, const char *hdl_signal, hdl_direction d, int simid,
		   const char *port_name = 0, int mode = 0)
{
    return hdl_connect_v( reinterpret_cast<sc_signal<T>&>(sig),hdl_signal,d,simid,port_name,mode );
}

template < class T >
void hdl_connect_v(sc_signal<T,SC_MANY_WRITERS> &sig, const char *hdl_signal, hdl_direction d, int simid,
		   const char *port_name = 0, int mode = 0)
{
    return hdl_connect_v( reinterpret_cast<sc_signal<T>&>(sig),hdl_signal,d,simid,port_name,mode );
}

template < class T >
void hdl_connect_v(sc_signal<T,SC_UNCHECKED_WRITERS> &sig, const char *hdl_signal, hdl_direction d, int simid,
		   const char *port_name = 0, int mode = 0)
{
    return hdl_connect_v( reinterpret_cast<sc_signal<T>&>(sig),hdl_signal,d,simid,port_name,mode );
}

#endif

inline void hdl_connect_v(sc_clock &sig, const char *hdl_signal, hdl_direction d, int simid)
{
  std::string hdl_conn_name = sig.name();
  hdl_conn_name += "_hdl";
  while (hdl_conn_name.find(".") != std::string::npos)
    hdl_conn_name.replace(hdl_conn_name.find("."), 1, "_");
  hdl_conn_name = BF_register_connection(sig.name(), hdl_conn_name, sig);

  switch(d)
    {
    case HDL_INPUT:
      // sc_clock is driven by SystemC, so there is no HDL_INPUT possible
      break;
    case HDL_OUTPUT:
      {
	bf_outConnClk_v *bfout = new bf_outConnClk_v(hdl_conn_name.c_str(), hdl_signal, HDL_vcs);
	bfout->ina(sig);
      }
      break;
    case HDL_INOUT:
      break;
    default:
      exit(2);
    }
}

#endif
