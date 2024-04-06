/*****************************************************************************
 
  rvm_sc_event.h : helper function for RVM: sc_event observer
 
  Authors: Ulli Holtmann, Robert Graulich, Holger Keding, Synopsys Inc.

  Copyright 2004 Synopsys, Inc.

  
  The event observers makes it possible to query via the sc_signal_in_if<int> 
  interface when and how often an sc_event triggers. 

  An observer E has two arguments E(reset,event) which
  defines its behavior. The arguments can be given during the CTOR or
  later by method set_events(). 'reset' is an event and usually a clock edge. 
  It defines periods during which all triggers of 'event' are
  accumulated starting from 0. The period begins with the time step
  where 'reset' occurs and ends at the last time step before the next
  'reset' occurs. Please note that triggers of 'event' that fall into
  the same time step as an trigger of 'reset' are accumulated into the
  new period, regardless if they happen if a previous, same or later
  delta cycle. Only the time matters, not the delta cycle. Also note
  that multiple triggers of event within the SAME delta cycle increment
  the value of the event observer by exactly one only and not more; this
  is to ensure determinimsn.

  The observer itself has a value_changed_event (because it implements
  sc_signal_in_if) which will trigger one delta after 'event' or
  'reset' triggered.
  
  The observer is a sc_object and thus has a name and can be found
  within the object hierarchy.

 *****************************************************************************/

#ifndef RVM_SC_EVENT_H
#define RVM_SC_EVENT_H

#include "systemc.h"


namespace sc_snps {

class rvm_sc_event_helper;

class rvm_sc_event
    : public sc_module,
      public sc_signal_in_if<int>
{
    friend class rvm_sc_event_helper;

public:

    // c'tors
    rvm_sc_event( sc_module_name name, const sc_event* reset = 0, const sc_event* target = 0);
    
    // set member events
    void set_events(const sc_event* reset_event ,const sc_event* target_event);
	
    // inherited from sc_signal_in_if<>
    virtual const sc_event& default_event() const;
    virtual const sc_event& value_changed_event() const;
    virtual const int& read() const;
    virtual const int& get_data_ref() const;
    virtual bool event() const;

    virtual const char* kind() const
        { return "rvm_sc_event"; }

protected:

    virtual void end_of_elaboration();

private:
    // data
    rvm_sc_event_helper* S;
    const sc_event *m_reset_event;  // pointer to the reset (clk) event
    const sc_event *m_target_event; // pointer to the target (observed) event
    sc_event reset_required_event;  // event reducing the activations of the
                                    // reset process
	
    // methods
    void reset_event_process();
    void target_event_process();

private:
    // disabled
    rvm_sc_event();
    rvm_sc_event( const rvm_sc_event& );
    rvm_sc_event& operator = ( const rvm_sc_event& );
};

} // namespace sc_snps


#ifdef TLI_TBLOG_H
// 
// rvm_sc_event
// NOTE:  This definition is used if tli_tblog.h was #included
//        before this file.
//
//        Any change here MUST be duplicated to tli_tblog.h !
//
inline
SC_SNPS TBlog::VarBase global_mkVar(const std::string& name, const SC_SNPS rvm_sc_event& value)
{
    return global_mkVar(name, value.read());
}
#endif


#endif
