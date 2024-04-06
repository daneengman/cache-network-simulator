/*****************************************************************************
 
  rvm_sc_var.h : helper functions and classes
 
  Authors: Thorsten Groetker, Martin Janssen, Holger Keding, Synopsys Inc.

  Copyright 2003 Synopsys, Inc.
 
 *****************************************************************************/

#ifndef RVM_SC_VAR_H
#define RVM_SC_VAR_H

#include "systemc.h"


namespace sc_snps {


// ----------------------------------------------------------------------------
//  CLASS : rvm_sc_var<T>
//
//  Primitive channel, implementing the sc_signal_in_if<T> interface, that
//  uses the trace mechanism for observing value changes of an external
//  variable of type T.
// ----------------------------------------------------------------------------

template <class T>
class rvm_sc_var
    : public sc_signal_in_if<T>,
      public sc_prim_channel,
      public sc_trace_file
{
public:

    // c'tor 
    rvm_sc_var( const char* name, T* var_p = 0);
    
    // set the variable to observe - if not already set in the constructor
    virtual void set_var(T* var_p);

    // get the default event
    virtual const sc_event& default_event() const
	{ return m_value_changed_event; }

    // get the value changed event
    virtual const sc_event& value_changed_event() const
	{ return m_value_changed_event; }

    // read the current value
    virtual const T& read() const;


    // get a reference to the current value (for tracing)
    virtual const T& get_data_ref() const
    { sc_deprecated_get_data_ref(); return *m_var_p; }

    // was there an event?
    virtual bool event() const
        { return ( simcontext()->change_stamp() == m_change_stamp + 1 ); }

    // kind string
    virtual const char* kind() const
        { return "rvm_sc_var"; }

private:

    // helper methods
    void tni() const {
	SC_REPORT_ERROR(SC_ID_RVM_SC_VAR_NI_,
			"rvm_sc_var<T>::trace(.)");
    }
    void wni() const {
	SC_REPORT_ERROR(SC_ID_RVM_SC_VAR_NI_,
			"rvm_sc_var<T>::write_comment(.)");
    }
    void dni() const {
	SC_REPORT_ERROR(SC_ID_RVM_SC_VAR_NI_,
			"rvm_sc_var<T>::delta_cycles(.)");
    }

    // disabled trace functionality
    void trace(sc_trace_file*) const { tni(); }
    void trace(const bool&, const std::string&) { tni(); }
    void trace(const sc_bit&, const std::string&) { tni(); }
    void trace(const sc_logic&, const std::string&) { tni(); }
    void trace(const unsigned char&, const std::string&, int) { tni(); }
    void trace(const unsigned short&, const std::string&, int) { tni(); }
    void trace(const unsigned int&, const std::string&, int) { tni(); }
    void trace(const unsigned long&, const std::string&, int) { tni(); }
    void trace(const char&, const std::string&, int) { tni(); }
    void trace(const short&, const std::string&, int) { tni(); }
    void trace(const int&, const std::string&, int) { tni(); }
    void trace(const long&, const std::string&, int) { tni(); }
    void trace(const sc_dt::int64&, const std::string&, int) { tni(); }
    void trace(const sc_dt::uint64&, const std::string&, int) { tni(); }
    void trace(const float&, const std::string&) { tni(); }
    void trace(const double&, const std::string&) { tni(); }
    void trace(const sc_uint_base&, const std::string&) { tni(); }
    void trace(const sc_int_base&, const std::string&) { tni(); }
    void trace(const sc_unsigned&, const std::string&) { tni(); }
    void trace(const sc_signed&, const std::string&) { tni(); }
    void trace( const sc_dt::sc_fxval&, const std::string&) { tni(); }
    void trace( const sc_dt::sc_fxval_fast&, const std::string&) { tni(); }
    void trace( const sc_dt::sc_fxnum&, const std::string&) { tni(); }
    void trace( const sc_dt::sc_fxnum_fast&, const std::string&) { tni(); }
    void trace(const sc_bv_base&, const std::string&) { tni(); }
    void trace(const sc_lv_base&, const std::string&) { tni(); }
    void trace(const unsigned&, const std::string&, const char**) { tni(); }
    void write_comment(const std::string&) { wni(); }
    void delta_cycles(bool) { dni(); }

    virtual void set_time_unit( double v, sc_time_unit tu ) {/*no effect*/}

    // This is the one method we really need from the trace file.
    void cycle(bool delta_cycle);

    // data
    T*       m_var_p; // variable being observed
    T        m_old_val;
    sc_event m_value_changed_event;
    uint64   m_change_stamp; // delta of last event

private:

    // disabled
    rvm_sc_var();
    rvm_sc_var( const rvm_sc_var<T>& );
    rvm_sc_var<T>& operator = ( const rvm_sc_var<T>& );
};


// --------------------- inline methods ---------------------------

template<class T>
inline
rvm_sc_var<T>::rvm_sc_var( const char* name, T* var_p)
    : sc_prim_channel( name ), m_var_p( var_p ), m_change_stamp( ~sc_dt::UINT64_ONE )
{ 
    simcontext()->add_trace_file( this ); 
    
    if (m_var_p != 0) {
	m_old_val = *var_p;
    }
}


// set the variable to observe - if not already set in the constructor
template<class T>
inline
void rvm_sc_var<T>::set_var(T* var_p)
{
    m_var_p = var_p; 
    if (m_var_p != 0) {
	m_old_val = *var_p;
    } else {
	SC_REPORT_ERROR(SC_ID_RVM_SC_VAR_USAGE_, "set_var(T* var) used with NULL pointer");
    }
}  

template<class T>
inline
const T& rvm_sc_var<T>::read() const
{ 
    return *m_var_p; 
}

template<class T>
inline
void rvm_sc_var<T>::cycle(bool delta_cycle) 
{
    if (!delta_cycle) return;
    if (m_var_p && (*m_var_p != m_old_val)) {
	m_old_val = *m_var_p;
	m_change_stamp = simcontext()->change_stamp();
	m_value_changed_event.notify(SC_ZERO_TIME);
    }
}


// --------------------- Specialization for T=bool ---------------------------
// has additional events and methods (cf. sc_signal_in_if<bool>).

template <>
class rvm_sc_var<bool>
    : public sc_signal_in_if<bool>,
      public sc_prim_channel,
      public sc_trace_file
{
public:

    // c'tor 
    rvm_sc_var( const char* name, bool* var_p = 0 );

    // get the default event
    virtual void set_var(bool* var_p);

    // get the default event
    virtual const sc_event& default_event() const
	{ return m_value_changed_event; }

    // get the value changed event
    virtual const sc_event& value_changed_event() const
	{ return m_value_changed_event; }

    // get the positive edge event
    virtual const sc_event& posedge_event() const 
	{ return m_posedge_event; }

    // get the negative edge event
    virtual const sc_event& negedge_event() const 
	{ return m_negedge_event; }

    // read the current value
    virtual const bool& read() const;

    // get a reference to the current value (for tracing)
    virtual const bool& get_data_ref() const
    { sc_deprecated_get_data_ref(); return *m_var_p; }

    // was there an event?
    virtual bool event() const
        { return ( simcontext()->change_stamp() == m_change_stamp + 1 ); }

    // was there a positive or negative edge event?
    virtual bool posedge() const 
	{ return ( event() && m_old_val ); }
    virtual bool negedge() const 
	{ return ( event() && ! m_old_val ); }

    // delayed evaluation (not supported)
    virtual const sc_signal_bool_deval& delayed() const {
	SC_REPORT_ERROR(SC_ID_RVM_SC_VAR_NI_,
			"rvm_sc_var<bool>::delayed()");
	const sc_signal_in_if<bool>* iface = this;
	return RCAST<const sc_signal_bool_deval&>( *iface );
    }

    // kind string
    virtual const char* kind() const
        { return "rvm_sc_var"; }

private:

    // helper methods
    void tni() const {
	SC_REPORT_ERROR(SC_ID_RVM_SC_VAR_NI_,
			"rvm_sc_var<bool>::trace(.)");
    }
    void wni() const {
	SC_REPORT_ERROR(SC_ID_RVM_SC_VAR_NI_,
			"rvm_sc_var<bool>::write_comment(.)");
    }
    void dni() const {
	SC_REPORT_ERROR(SC_ID_RVM_SC_VAR_NI_,
			"rvm_sc_var<bool>::delta_cycles(.)");
    }

    // disabled trace functionality
    void trace(sc_trace_file*) const { tni(); }
    void trace(const bool&, const std::string&) { tni(); }
    void trace(const sc_bit&, const std::string&) { tni(); }
    void trace(const sc_logic&, const std::string&) { tni(); }
    void trace(const unsigned char&, const std::string&, int) { tni(); }
    void trace(const unsigned short&, const std::string&, int) { tni(); }
    void trace(const unsigned int&, const std::string&, int) { tni(); }
    void trace(const unsigned long&, const std::string&, int) { tni(); }
    void trace(const char&, const std::string&, int) { tni(); }
    void trace(const short&, const std::string&, int) { tni(); }
    void trace(const int&, const std::string&, int) { tni(); }
    void trace(const long&, const std::string&, int) { tni(); }
    void trace(const sc_dt::int64&, const std::string&, int) { tni(); }
    void trace(const sc_dt::uint64&, const std::string&, int) { tni(); }
    void trace(const float&, const std::string&) { tni(); }
    void trace(const double&, const std::string&) { tni(); }
    void trace(const sc_uint_base&, const std::string&) { tni(); }
    void trace(const sc_int_base&, const std::string&) { tni(); }
    void trace(const sc_unsigned&, const std::string&) { tni(); }
    void trace(const sc_signed&, const std::string&) { tni(); }
    void trace(const sc_dt::sc_fxval&, const std::string&) { tni(); }
    void trace(const sc_dt::sc_fxval_fast&, const std::string&) { tni(); }
    void trace(const sc_dt::sc_fxnum&, const std::string&) { tni(); }
    void trace(const sc_dt::sc_fxnum_fast&, const std::string&) { tni(); }
    void trace(const sc_bv_base&, const std::string&) { tni(); }
    void trace(const sc_lv_base&, const std::string&) { tni(); }
    void trace(const unsigned&, const std::string&, const char**) { tni(); }
    void write_comment(const std::string&) { wni(); }
    void delta_cycles(bool) { dni(); }

    virtual void set_time_unit( double v, sc_time_unit tu ) {/*no effect*/}

    // This is the one method we really need from the trace file.
    void cycle(bool delta_cycle);

    // data
    bool*    m_var_p; // pointer to variable being observed
    bool     m_old_val;
    sc_event m_value_changed_event;
    sc_event m_posedge_event;
    sc_event m_negedge_event;
    uint64   m_change_stamp; // delta of last event

private:

    // disabled
    rvm_sc_var();
    rvm_sc_var( const rvm_sc_var<bool>& );
    rvm_sc_var<bool>& operator = ( const rvm_sc_var<bool>& );
};


inline
rvm_sc_var<bool>::rvm_sc_var( const char* name, bool* var_p)
    : sc_prim_channel( name ), m_var_p( var_p ), m_change_stamp( ~sc_dt::UINT64_ONE )
{ 
    simcontext()->add_trace_file( this ); 
    
    if (m_var_p != 0) {
	m_old_val = *var_p;    
    }
}


inline
void rvm_sc_var<bool>::set_var(bool* var_p)
{ 
    m_var_p = var_p; 
    if (m_var_p != 0) {
	m_old_val = *var_p; 
    } else {
	SC_REPORT_ERROR(SC_ID_RVM_SC_VAR_USAGE_, "set_var(T* var) used with NULL pointer");
    }
}  

inline
const bool& rvm_sc_var<bool>::read() const
{ 
    return *m_var_p; 
}

inline
void rvm_sc_var<bool>::cycle(bool delta_cycle) 
{
    if (!delta_cycle) return;
    if (m_var_p && (*m_var_p != m_old_val)) {
	m_old_val = *m_var_p;
	m_change_stamp = simcontext()->change_stamp();
	m_value_changed_event.notify(SC_ZERO_TIME);
	if(*m_var_p)
	    m_posedge_event.notify(SC_ZERO_TIME);
	else
	    m_negedge_event.notify(SC_ZERO_TIME);
    }
}

} // namespace sc_snps

#ifdef TLI_TBLOG_H
// 
// rvm_sc_var
// NOTE:  This definition is used if tli_tblog.h was #included
//        before this file.
//
//        Any change here MUST be duplicated to tli_tblog.h !
//
template<class T>
inline
SC_SNPS TBlog::VarBase global_mkVar(const std::string& name, const SC_SNPS rvm_sc_var<T>& value)
{
    return global_mkVar(name, value.read());
}
#endif


#endif
