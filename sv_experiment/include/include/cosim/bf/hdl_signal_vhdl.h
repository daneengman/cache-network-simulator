// This may look like C code, but it is really -*- C++ -*-
// 
// hdl_signal.h -- 
// Copyright Synopsys 2002
// Author          : Ric Hilderink
// Created On      : Mon Aug 12 08:54:32 2002
// Status          : none
// 


#ifndef _hdl_vhdl_signal_h_
#define _hdl_vhdl_signal_h_

#include "systemc.h"
#include <string>

#include "hdl_signal_vhdl_base.h"
#include "sc_conversion_vhdl.h"
#include "VcsDesign.h"
#include "vcs_cbug_object_info.h"

typedef struct S_hdl_vhdl_io
{
  vhpiHandleT m_vhpi_signal;
  std::string m_fullname;
  std::string m_hdl_name;
  hdl_direction m_direction;
  int m_simid;
  struct S_hdl_vhdl_io *m_next;
} s_hdl_vhdl_io;


template < class T >
class hdl_signal_vhdl : public sc_signal<T>, public hdl_signal_base
{
public:
   hdl_signal_vhdl() : m_state(0) {
      m_io = 0;
      m_port_name = 0;
      m_mode = 0;
      m_size = -1;
      m_value_buffer_size = 1;
      m_s = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }

   hdl_signal_vhdl(const char *hdl_name, hdl_direction direction, int simid) : 
      m_state(0) {
      m_io = new s_hdl_vhdl_io;
      m_io->m_next = 0;
      m_io->m_vhpi_signal = 0;
      m_io->m_hdl_name = hdl_name;
      m_io->m_fullname = hdl_name;
      m_io->m_direction = direction;
      m_io->m_simid = simid;

      m_port_name = 0;
      m_mode = 0;
      m_size = -1;
      m_value_buffer_size = 1;
      m_s = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }

   hdl_signal_vhdl(const char *hdl_name, hdl_direction direction, int simid, const char *port_name, int mode) : 
      m_state(0) {
      m_io = new s_hdl_vhdl_io;
      m_io->m_next = 0;
      m_io->m_vhpi_signal = 0;
      m_io->m_hdl_name = hdl_name;
      m_io->m_fullname = hdl_name;
      m_io->m_direction = direction;
      m_io->m_simid = simid;
      
      if (port_name)
	{
	  m_port_name = new char[strlen(port_name) + 1];
	  strcpy(m_port_name, port_name);
	}
      else
	m_port_name = 0;
      m_mode = mode;
      m_size = -1;
      m_value_buffer_size = 1;
      m_s = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }

   hdl_signal_vhdl(const char *mod_name,
                   const char *hdl_name, 
                   hdl_direction direction) : m_state(0) {

      m_io = new s_hdl_vhdl_io;
      m_io->m_next = 0;
      m_io->m_vhpi_signal = 0;
      m_io->m_hdl_name = hdl_name;
      m_io->m_simid = 0;

      if (direction == HDL_INPUT) {
         m_io->m_fullname = "top." + std::string(mod_name) +
           "_v_" + std::string(hdl_name);
      }
      else if (direction == HDL_OUTPUT) {
         m_io->m_fullname = "top." + std::string(mod_name) + 
           "." + std::string(hdl_name);
      }
      m_io->m_direction = direction;

      m_port_name = 0;
      m_mode = 0;
      m_size = -1;
      m_value_buffer_size = 1;
      m_s = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }

   hdl_signal_vhdl(const char *fullname,
                   const char *mod_name,
                   const char *hdl_name, 
                   hdl_direction direction) : sc_signal<T>(fullname) {
      m_io = new s_hdl_vhdl_io;
      m_io->m_next = 0;
      m_io->m_vhpi_signal = 0;
      m_io->m_hdl_name = hdl_name;
      m_io->m_simid = 0;

      if (direction == HDL_INPUT) {
         m_io->m_fullname = "top." + std::string(mod_name) +
           "_v_" + std::string(hdl_name); 
      }
      else if (direction == HDL_OUTPUT) {
         m_io->m_fullname = "top." + std::string(mod_name) +
           "." + std::string(hdl_name);
      }
      m_io->m_direction = direction;

      m_port_name = 0;
      m_mode = 0;
      m_size = -1;
      m_value_buffer_size = 1;
      m_s = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }

  void init_buffers(hdl_direction direction) {
    mP_vhpi_value = new vhpiValueT*[m_value_buffer_size];
    m_read_idx = 0;
    m_write_idx = 0;
    m_value_buffer_wrap = m_value_buffer_size-1;
    if (direction == HDL_OUTPUT) {
      for (int i=0; i<m_value_buffer_size; i++) {
        mP_vhpi_value[i] =
          BF_vhpi_create_buffer(m_size, m_io->m_vhpi_signal);
      }
    } else {
      for (int i=0; i<m_value_buffer_size; i++) {
        mP_vhpi_value[i] = 
          BF_vhpi_create_buffer_str(m_io->m_vhpi_signal);
      }
    }
  }

  void before_end_of_elaboration()
  {
  }

   void end_of_elaboration() {
      VcsDesign::getDesignInstance()->SimvMain();

      s_hdl_vhdl_io *nio = m_io;
      while (nio)
      {
	if (nio->m_simid == HDL_scirocco)
	  {
	    if (nio->m_direction == HDL_OUTPUT)
	      {
		hdl_cb_struct *S = new_hdl_cb_struct();
		hdl_cb_struct_set(S, this);
                nio->m_vhpi_signal = BF_register_output_cb_vhpi(nio->m_fullname.c_str(),
								nio->m_hdl_name.c_str(),
								(char *)S,
								MX_cb_vhpi,
								m_mode);
		
		if (!nio->m_vhpi_signal)
		  {
		    // error is already printed by routine. Handle not valid, so:
		    return;
		  }

		m_size = BF_notify_vhpi(nio->m_vhpi_signal);
                if(m_size<1) m_size = 1;
		sc_attribute<vhpiHandleT> *a =
                  new sc_attribute<vhpiHandleT>("vhpihandle",
                                                nio->m_vhpi_signal);
		this->add_attribute(*a);
		sc_attribute<hdl_direction> *d = 
		  new sc_attribute<hdl_direction>("hdl_direction",
                                                  nio->m_direction);
		this->add_attribute(*d);

		sc_conversion::check_sc_vhdl::check_sc_hdl(nio->m_vhpi_signal, m_state, 1, nio->m_hdl_name.c_str());                init_buffers(HDL_OUTPUT);
		
		get_data_from_hdl();
		transport_hdl_to_sc();
	      }
	    else if (nio->m_direction == HDL_INPUT)
	      {
		nio->m_vhpi_signal = BF_register_input_cb_vhpi(nio->m_fullname.c_str(),
							       nio->m_hdl_name.c_str(),
							       m_mode);

		if (!nio->m_vhpi_signal)
		  {
		    // error is already printed by routine. Handle not valid, so:
		    return;
		  }

		m_size = BF_notify_vhpi(nio->m_vhpi_signal);
                if (m_size <1) m_size = 1;
		sc_attribute<vhpiHandleT> *a = new sc_attribute<vhpiHandleT>("vhpihandle", nio->m_vhpi_signal);
		this->add_attribute(*a);
		sc_attribute<hdl_direction> *d = 
		  new sc_attribute<hdl_direction>("hdl_direction", nio->m_direction);
		this->add_attribute(*d);
		
		sc_conversion::check_sc_vhdl::check_sc_hdl(nio->m_vhpi_signal, m_state, 2, nio->m_hdl_name.c_str());
                init_buffers(HDL_INPUT);
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
     if (m_io->m_direction == HDL_INPUT)
       {
         sc_conversion::vhpi::sc_to_hdl(value, mP_vhpi_value[m_write_idx], m_io->m_hdl_name);
         m_write_idx++;
         m_write_idx &= m_value_buffer_wrap;
         BF_add_to_transport_queue_sc_to_hdl(this);
       }
     sc_signal<T>::write(value);
   }
  
   virtual void update() {
     if (!G_is_stopped)
      sc_signal<T>::update();
   }

   virtual void transport_sc_to_hdl() {
     BF_transport_vhpi(m_io->m_vhpi_signal, mP_vhpi_value[m_read_idx]);
     m_read_idx++;
     m_read_idx &= m_value_buffer_wrap;
   };

  // transport data from HDL to SC
  virtual void get_data_from_hdl() {
    BF_obtain_value_vhpi(m_io->m_vhpi_signal, mP_vhpi_value[m_write_idx]);
    m_write_idx++;
    m_write_idx &= m_value_buffer_wrap;
  };

  virtual void transport_hdl_to_sc() {    
    sc_conversion::vhpi::hdl_to_sc(*mP_vhpi_value[m_read_idx],
                                   m_size,
                                   m_state);
    m_read_idx++;
    m_read_idx &= m_value_buffer_wrap;
    sc_signal<T>::write(m_state);
  }
   s_hdl_vhdl_io *getIO() const { return m_io; }

  void s(sc_signal<T> &s) { m_s = &s; }
  
private:
   s_hdl_vhdl_io *m_io;
   T m_state;
   vhpiValueT **mP_vhpi_value;
   int m_read_idx; 
   int m_write_idx;
   int m_value_buffer_size;
   int m_value_buffer_wrap;

   int m_size;

  char *m_port_name;
  int m_mode;
  sc_signal<T> *m_s;
};

#endif
