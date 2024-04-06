// This may look like C code, but it is really -*- C++ -*-
// 
// hdl_signal_v.h -- 
// Copyright Synopsys 2002
// Author          : Ric Hilderink
// Created On      : Mon Aug 12 08:54:32 2002
// Status          : none
// 


#ifndef _hdl_signal_v_h_
#define _hdl_signal_v_h_

#include "systemc.h"
#include <string>

#include "hdl_signal_v_base.h"
#include "sc_conversion_v.h"
#include "VcsDesign.h"
#include "vcs_cbug_object_info.h"

typedef struct S_hdl_v_io
{
  handle m_hdl_signal;
  std::string m_fullname;
  std::string m_hdl_name;
  hdl_direction m_direction;
  int m_simid;
  struct S_hdl_v_io *m_next;
} s_hdl_v_io;

template < class T >
class hdl_signal_v : public sc_signal<T>, public hdl_signal_base
{
public:
   hdl_signal_v() : m_state(0) {
      m_io = 0;
      m_value_data.format = accVectorVal;

      m_port_name = 0;
      m_mode = 0;
      m_size = -1;
      m_s = 0;
      m_vecval = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }

   hdl_signal_v(const char *hdl_name, hdl_direction direction, int simid) : 
      m_state(0) {
      m_io = new s_hdl_v_io;
      m_io->m_next = 0;
      m_io->m_hdl_signal = 0;
      m_io->m_hdl_name = hdl_name;
      m_io->m_fullname = hdl_name;
      m_io->m_direction = direction;
      m_io->m_simid = simid;

      m_value_data.format = accVectorVal;

      m_port_name = 0;
      m_mode = 0;
      m_size = -1;
      m_value_buffer_size = 128;
      m_s = 0;
      m_vecval = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }

   hdl_signal_v(const char *hdl_name, hdl_direction direction, int simid, const char *port_name, int mode) : 
      m_state(0) {
      m_io = new s_hdl_v_io;
      m_io->m_next = 0;
      m_io->m_hdl_signal = 0;
      m_io->m_hdl_name = hdl_name;
      m_io->m_fullname = hdl_name;
      m_io->m_direction = direction;
      m_io->m_simid = simid;

      m_value_data.format = accVectorVal;
      
      if (port_name)
	{
	  m_port_name = new char[strlen(port_name)+1];
	  strcpy(m_port_name, port_name);
	}
      else
	m_port_name = 0;
      m_mode = 0;

      m_size = -1;
      m_value_buffer_size = 128;
      m_s = 0;
      m_vecval = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }

   hdl_signal_v(const char *mod_name, const char *hdl_name, 
              hdl_direction direction) :
      m_state(0) {

      m_io = new s_hdl_v_io;
      m_io->m_next = 0;
      m_io->m_hdl_signal = 0;
      m_io->m_hdl_name = hdl_name;
      m_io->m_simid = 0;

      if (direction == HDL_INPUT) {
         m_io->m_fullname = "top." + std::string(mod_name) + "_v_" + std::string(hdl_name);
      }
      else if (direction == HDL_OUTPUT) {
         m_io->m_fullname = "top." + std::string(mod_name) + "." + std::string(hdl_name);
      }
      m_io->m_direction = direction;

      m_value_data.format = accVectorVal;

      m_port_name = 0;
      m_mode = 0;
      m_size = -1;
      m_value_buffer_size = 128;
      m_s = 0;
      m_vecval = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }

   hdl_signal_v(const char *fullname, const char *mod_name,
                const char *hdl_name, 
                hdl_direction direction) : sc_signal<T>(fullname) {
      m_io = new s_hdl_v_io;
      m_io->m_next = 0;
      m_io->m_hdl_signal = 0;
      m_io->m_hdl_name = hdl_name;
      m_io->m_simid = 0;

      if (direction == HDL_INPUT) {
         m_io->m_fullname = "top." + std::string(mod_name) + "_v_" + std::string(hdl_name); 
      }
      else if (direction == HDL_OUTPUT) {
         m_io->m_fullname = "top." + std::string(mod_name) + "." + std::string(hdl_name);
      }
      m_io->m_direction = direction;

      m_value_data.format = accVectorVal;

      m_port_name = 0;
      m_mode = 0;
      m_size = -1;
      m_value_buffer_size = 128;
      m_s = 0;
      m_vecval = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }
  void init_buffers() {
    m_size = BF_notify(m_io->m_hdl_signal);
    if (m_size < 1) m_size = 1;
    if ((m_size%32) == 0)
      m_mask = -1;
    else
      m_mask = (1<<(m_size%32)) - 1;
    m_vecval = new t_acc_vecval*[m_value_buffer_size];
    for (int i=0; i<m_value_buffer_size; i++) {
      m_vecval[i] = new t_acc_vecval[m_size];
      m_vecval[i]->aval = m_vecval[i]->bval = 0;
    }
    m_read_idx = 0;
    m_write_idx = 0;
    m_value_buffer_wrap = m_value_buffer_size-1;
  }

  void before_end_of_elaboration()
  {
  }

   void end_of_elaboration() {
      VcsDesign::getDesignInstance()->SimvMain();

      s_hdl_v_io *nio = m_io;
      while (nio)
      {
	if (nio->m_simid == HDL_vcs)
	  {
	    if (nio->m_direction == HDL_OUTPUT)
	      {
		hdl_cb_struct *S = new_hdl_cb_struct();
		hdl_cb_struct_set(S, this);
		nio->m_hdl_signal = BF_register_output_cb(nio->m_fullname.c_str(),
							  nio->m_hdl_name.c_str(),
							  (char *)S, 
							  MX_cb, 
							  m_mode);

		if (!nio->m_hdl_signal)
		  {
		    // error is already printed by routine. Handle not valid, so:
		    return;
		  }

		sc_attribute<handle> *a = new sc_attribute<handle>("handle", nio->m_hdl_signal);
		this->add_attribute(*a);
		sc_attribute<hdl_direction> *d = 
		  new sc_attribute<hdl_direction>("hdl_direction", nio->m_direction);
		this->add_attribute(*d);
		
		sc_conversion::check_sc_hdl::check_sc_hdl(nio->m_hdl_signal, m_state, 1, this->basename());
		init_buffers();
		get_data_from_hdl();
		transport_hdl_to_sc();
	      }
	    else if (nio->m_direction == HDL_INPUT)
	      {
		nio->m_hdl_signal = BF_register_input_cb(nio->m_fullname.c_str(), m_mode);

		if (!nio->m_hdl_signal)
		  {
		    // error is already printed by routine. Handle not valid, so:
		    return;
		  }

		sc_attribute<handle> *a = new sc_attribute<handle>("handle", nio->m_hdl_signal);
		this->add_attribute(*a);
		sc_attribute<hdl_direction> *d = 
		  new sc_attribute<hdl_direction>("hdl_direction", nio->m_direction);
		this->add_attribute(*d);
		
		sc_conversion::check_sc_hdl::check_sc_hdl(nio->m_hdl_signal, m_state, 2, this->basename());
		init_buffers();
	      }
	    }
         nio = nio->m_next;
	 assert(!nio);
      }
   }


  virtual void write_conn(const T &value)
  {
    write(value);
  }

   virtual void write(const T &value) {
     if (m_io->m_direction == HDL_INPUT && m_vecval)
       {
         m_value_data.value.vector = m_vecval[m_write_idx];
         m_write_idx++;
         m_write_idx &= m_value_buffer_wrap;
         sc_conversion::vcsacc::sc_to_hdl( value,
                                           m_value_data.value.vector,
                                           m_mask, 
                                           m_size);
         BF_add_to_transport_queue_sc_to_hdl(this);
       }
     sc_signal<T>::write(value);
   }
  
  virtual void update() {
    if (!G_is_stopped)
      sc_signal<T>::update();
   }

  // Transport data form SC to HDL
   virtual void transport_sc_to_hdl() {
     m_value_data.value.vector = m_vecval[m_read_idx];
     m_read_idx++;
     m_read_idx &= m_value_buffer_wrap;
     BF_transport(m_io->m_hdl_signal, &m_value_data);
   };

  // Transport data from HDL to SC
  virtual void get_data_from_hdl() {
    m_value_data.value.vector = m_vecval[m_write_idx];
    m_write_idx++;
    m_write_idx &= m_value_buffer_wrap;
    BF_obtain_value(m_io->m_hdl_signal, &m_value_data );

  };
  virtual void transport_hdl_to_sc() {
    m_state = 0;
      sc_conversion::vcsacc::hdl_to_sc(m_vecval[m_read_idx], 
                                       m_size,
                                       m_state);

     m_read_idx++;
     m_read_idx &= m_value_buffer_wrap;
    
     sc_signal<T>::write(m_state);
  }

   s_hdl_v_io *getIO() const { return m_io; }

  void s(sc_signal<T> &s) { m_s = &s; }
private:
   s_hdl_v_io *m_io;
   sc_event m_event;
   T m_state;
   s_setval_value m_value_data;
   int m_size;
   int m_mask;

  p_acc_vecval *m_vecval;
  int m_read_idx;
  int m_write_idx;
  int m_value_buffer_size;
  int m_value_buffer_wrap;

  char *m_port_name;
  int m_mode;
  sc_signal<T> *m_s;
};

/****
// Does not work right now! In case of double type support
// we have to use at least the union member 'real', which is of type double.
// Furthermore the use of the member 'm_write_idx' has to be adapted.
template<>
virtual void hdl_signal_v::write(const double &value) {
     if (m_io->m_direction == HDL_INPUT && m_vecval)
       {
         // m_value_data.value.vector = m_vecval[m_write_idx];
         // m_write_idx++;
         // m_write_idx &= m_value_buffer_wrap;
            m_value_data.format = accRealVal;
           m_value_data.value.real = value;
         BF_add_to_transport_queue_sc_to_hdl(this);
       }
     sc_signal<T>::write(value);
   }
****/
#endif
