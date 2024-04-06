/*****************************************************************************
 
  rvm_sc_sig.h : helper functions and classes
 
  Authors: Holger Keding, Synopsys Inc.

  Copyright 2004 Synopsys, Inc.
 
 *****************************************************************************/

#ifndef RVM_SC_SIG_H
#define RVM_SC_SIG_H

#include "systemc.h"


namespace sc_snps {


// ----------------------------------------------------------------------------
//  CLASS : rvm_sc_sig<T>
//
//  Primitive channel, implementing the sc_signal_in_if<T> interface, that
//  uses the trace mechanism for observing value changes of an external
//  variable of type T.
// ----------------------------------------------------------------------------

template <class T>
class rvm_sc_sig
    : public sc_signal_in_if<T>,
      public sc_prim_channel
{
public:

    // c'tor 
    rvm_sc_sig( const char* name, sc_signal<T>* ts = 0 );
    
	// set the pointer to the signal to be observed
	void set_sig(sc_signal<T>* sp);
	
	///////////////////////////////////////
	// derived from sc_interface:
	
    // get the default event
	virtual const sc_event& default_event() const  
	{ 
		sc_assert( referenced_signal );
		return referenced_signal->default_event(); 
	}

	////////////////////////////////////////
	// derived from sc_signal_in_if<T>

    // get the value changed event
    virtual const sc_event& value_changed_event() const
	{ return referenced_signal->value_changed_event(); }

    // read the current value
    virtual const T& read() const
	{ return referenced_signal->read(); }

    // get a reference to the current value (for tracing)
    virtual const T& get_data_ref() const
        { return referenced_signal->get_data_ref(); }

    // was there a value changed event?
    virtual bool event() const
    { return referenced_signal->event(); }

    // kind string
    virtual const char* kind() const
    { return "rvm_sc_sig"; }
	
protected:

	virtual void end_of_elaboration();

private:
    // members
    std::string     m_name;
    sc_signal<T>* referenced_signal;

    // disabled
    rvm_sc_sig();
    rvm_sc_sig( const rvm_sc_sig<T>& );
    rvm_sc_sig<T>& operator = ( const rvm_sc_sig<T>& );
};


// --------------------- inline methods ---------------------------

template<class T>
inline
rvm_sc_sig<T>::rvm_sc_sig( const char* name, sc_signal<T>* ts)
    : sc_prim_channel( name )
    , m_name( name )
    , referenced_signal( ts )
{
	if ( ts != 0 ) this->set_sig(ts);
}

template<class T> inline 
void rvm_sc_sig<T>::set_sig(sc_signal<T>* sp)
{ 
	referenced_signal = sp; 
}	

template<class T> inline 
void rvm_sc_sig<T>::end_of_elaboration()
{ 
	// sanity check: is the target signal set properly?
	if ( referenced_signal == 0 ) {
		SC_REPORT_ERROR(155 /*SC_ID_RVM_SC_SIG_NI_*/,"rvm_sc_sig: referenced_signal is not set.");
	}
}


//////////////////////////////////////////////////////////////////////////////
// --------------------- Specialization for T=bool ---------------------------
// has additional events and methods (cf. sc_signal_in_if<bool>).

template <>
class rvm_sc_sig<bool>
    : public sc_signal_in_if<bool>,
      public sc_prim_channel
{
public:

    // c'tor 
    rvm_sc_sig( const char* name, sc_signal<bool>* ts = 0 );
    
	// set the pointer to the signal to be observed
	void set_sig(sc_signal<bool>* sp);
		
	///////////////////////////////////////
	// derived from sc_interface:
	
	virtual const sc_event& default_event() const;	// get the default event
	
	////////////////////////////////////////
	// derived from sc_signal_in_if<bool>
    
    virtual const sc_event& value_changed_event() const; // get the value changed event
    virtual const sc_event& posedge_event() const;       // get the positive edge event
    virtual const sc_event& negedge_event() const;       // get the negative edge event
    virtual const bool& read() const;                       // read the current value
    virtual const bool& get_data_ref() const;               // get a reference to the current value (for tracing)
    virtual bool event() const;                          // was there an event?
    virtual bool posedge() const;                        // was there a positive edge event?
    virtual bool negedge() const;                        // was there a negative edge event?
    virtual const char* kind() const;                    // kind string
	
protected:

	virtual void end_of_elaboration();

private:

    // members
	sc_signal<bool>* referenced_signal;
	std::string     m_name;

    // disabled
    rvm_sc_sig();
    rvm_sc_sig( const rvm_sc_sig<bool>& );
    rvm_sc_sig<bool>& operator = ( const rvm_sc_sig<bool>& );
};

// --------------------- inline methods ---------------------------

// get the default event
inline 
const sc_event& rvm_sc_sig<bool>::default_event() const  
{ 
	sc_assert( referenced_signal );
	return referenced_signal->default_event(); 
}

// get the value changed event
inline 
const sc_event& rvm_sc_sig<bool>::value_changed_event() const
{ return referenced_signal->value_changed_event(); }

// get the positive edge event
inline 
const sc_event& rvm_sc_sig<bool>::posedge_event() const
{ return referenced_signal->posedge_event(); }

// get the negative edge event
inline 
const sc_event& rvm_sc_sig<bool>::negedge_event() const
{ return referenced_signal->negedge_event(); }

// read the current value
inline 
const bool& rvm_sc_sig<bool>::read() const
{ return referenced_signal->read(); }

// get a reference to the current value (for tracing)
inline 
const bool& rvm_sc_sig<bool>::get_data_ref() const
{ return referenced_signal->get_data_ref(); }

// was there an event?
inline 
bool rvm_sc_sig<bool>::event() const
{ return referenced_signal->event(); }

// was there a positive edge event?
inline 
bool rvm_sc_sig<bool>::posedge() const
{ return referenced_signal->posedge(); }

// was there a negative edge event?
inline 
bool rvm_sc_sig<bool>::negedge() const
{ return referenced_signal->negedge(); }

// kind string
inline 
const char* rvm_sc_sig<bool>::kind() const
{ return "rvm_sc_var"; }


inline
void rvm_sc_sig<bool>::end_of_elaboration()
{ 
	// sanity check: is the target signal set properly?
	if ( referenced_signal == 0 ) {
		SC_REPORT_ERROR(155 /*SC_ID_RVM_SC_SIG_NI_*/,"rvm_sc_sig: referenced_signal is not set.");
	}
}


//////////////////////////////////////////////////////////////////////////////
// --------------------- Specialization for T=sc_logic -----------------------
// has additional events and methods (cf. sc_signal_in_if<sc_logic>).

template <>
class rvm_sc_sig<sc_logic>
    : public sc_signal_in_if<sc_logic>,
      public sc_prim_channel
{
public:

    // c'tor 
    rvm_sc_sig( const char* name, sc_signal<sc_logic>* ts = 0 );
    
	// set the pointer to the signal to be observed
	void set_sig(sc_signal<sc_logic>* sp);
		
	///////////////////////////////////////
	// derived from sc_interface:
	
	virtual const sc_event& default_event() const;	// get the default event
	
	////////////////////////////////////////
	// derived from sc_signal_in_if<sc_logic>
    
    virtual const sc_event& value_changed_event() const; // get the value changed event
    virtual const sc_event& posedge_event() const;       // get the positive edge event
    virtual const sc_event& negedge_event() const;       // get the negative edge event
    virtual const sc_logic& read() const;                       // read the current value
    virtual const sc_logic& get_data_ref() const;               // get a reference to the current value (for tracing)
    virtual bool event() const;                          // was there an event?
    virtual bool posedge() const;                        // was there a positive edge event?
    virtual bool negedge() const;                        // was there a negative edge event?
    virtual const char* kind() const;                    // kind string
	
protected:

	virtual void end_of_elaboration();

private:

    // members
	sc_signal<sc_logic>* referenced_signal;
	std::string     m_name;

    // disabled
    rvm_sc_sig();
    rvm_sc_sig( const rvm_sc_sig<sc_logic>& );
    rvm_sc_sig<sc_logic>& operator = ( const rvm_sc_sig<sc_logic>& );
};

// --------------------- inline methods ---------------------------

// get the default event
inline 
const sc_event& rvm_sc_sig<sc_logic>::default_event() const  
{ 
	sc_assert( referenced_signal );
	return referenced_signal->default_event(); 
}

// get the value changed event
inline 
const sc_event& rvm_sc_sig<sc_logic>::value_changed_event() const
{ return referenced_signal->value_changed_event(); }

// get the positive edge event
inline 
const sc_event& rvm_sc_sig<sc_logic>::posedge_event() const
{ return referenced_signal->posedge_event(); }

// get the negative edge event
inline 
const sc_event& rvm_sc_sig<sc_logic>::negedge_event() const
{ return referenced_signal->negedge_event(); }

// read the current value
inline 
const sc_logic& rvm_sc_sig<sc_logic>::read() const
{ return referenced_signal->read(); }

// get a reference to the current value (for tracing)
inline 
const sc_logic& rvm_sc_sig<sc_logic>::get_data_ref() const
{ return referenced_signal->get_data_ref(); }

// was there an event?
inline 
bool rvm_sc_sig<sc_logic>::event() const
{ return referenced_signal->event(); }

// was there a positive edge event?
inline 
bool rvm_sc_sig<sc_logic>::posedge() const
{ return referenced_signal->posedge(); }

// was there a negative edge event?
inline 
bool rvm_sc_sig<sc_logic>::negedge() const
{ return referenced_signal->negedge(); }

// kind string
inline 
const char* rvm_sc_sig<sc_logic>::kind() const
{ return "rvm_sc_var"; }

inline
void rvm_sc_sig<sc_logic>::end_of_elaboration()
{ 
	// sanity check: is the target signal set properly?
	if ( referenced_signal == 0 ) {
		SC_REPORT_ERROR(155 /*SC_ID_RVM_SC_SIG_NI_*/,"rvm_sc_sig: referenced_signal is not set.");
	}
}


} // namespace sc_snps	


#ifdef TLI_TBLOG_H
// 
// rvm_sc_sig
// NOTE:  This definition is used if tli_tblog.h was #included
//        before this file.
//
//        Any change here MUST be duplicated to tli_tblog.h !
//
template<class T>
inline
SC_SNPS TBlog::VarBase global_mkVar(const std::string& name, const SC_SNPS rvm_sc_sig<T>& value)
{
    return global_mkVar(name, value.read());
}
#endif


#endif

