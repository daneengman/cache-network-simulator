// This may look like C code, but it is really -*- C++ -*-
// 
// hdl_signal_v.h -- 
// Copyright Synopsys 2002
// Author          : Ric Hilderink
// Created On      : Mon Aug 12 08:54:32 2002
// Status          : none
// 


#ifndef _HDL_SIGNAL_V_ENUM_XXX_
#define _HDL_SIGNAL_V_ENUM_XXX_

#include "systemc.h"
#include <string>
#include "bf_user.h"

namespace sc_conversion {
  namespace vcsacc {
    static void hdl_to_sc(t_acc_vecval *accvec, int size, ENUM_XXX &dest) {
        int tmp_dest = accvec[0].aval & (~accvec[0].bval);
        dest=(ENUM_XXX)tmp_dest;
    }
  }
};
#include "hdl_signal_v.h"
#include "hdl_signal_v_base.h"
#include "sc_conversion_v.h"
#include "VcsDesign.h"
#include "vcs_cbug_object_info.h"

template < >
__attribute__((weak))   hdl_signal_v<ENUM_XXX> :: hdl_signal_v() {
      m_io = 0;
      m_value_data.format = accVectorVal;

      m_port_name = 0;
      m_mode = 0;
      m_size = -1;
      m_s = 0;
      m_vecval = 0;

      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
   }

template < > 
__attribute__((weak)) hdl_signal_v<ENUM_XXX> :: hdl_signal_v(const char *hdl_name, hdl_direction direction, int simid) 
       {
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

template < > 
__attribute__((weak))    hdl_signal_v<ENUM_XXX> :: hdl_signal_v(const char *hdl_name, hdl_direction direction, int simid, const
                char *port_name, int mode){ 
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

template < > 
__attribute__((weak))    hdl_signal_v<ENUM_XXX> :: hdl_signal_v(const char *mod_name, const char *hdl_name, 
              hdl_direction direction) {

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

template < > 
__attribute__((weak))    hdl_signal_v<ENUM_XXX> :: hdl_signal_v(const char *fullname, const char *mod_name,
                const char *hdl_name, 
                hdl_direction direction) : sc_signal<ENUM_XXX>(fullname) {
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
template < > 
   void __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: write(const ENUM_XXX &value) {
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
     sc_signal<ENUM_XXX>::write(value);
   }
template < > 
  void __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: init_buffers() {
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

template < > 
  void __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: before_end_of_elaboration()
  {
  }

template < > 
  void __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: transport_hdl_to_sc() {
      sc_conversion::vcsacc::hdl_to_sc(m_vecval[m_read_idx], 
                                       m_size,
                                       m_state);

     m_read_idx++;
     m_read_idx &= m_value_buffer_wrap;
    
     sc_signal<ENUM_XXX>::write(m_state);
  }

  // Transport data from HDL to SC
template < > 
  void __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: get_data_from_hdl() {
    m_value_data.value.vector = m_vecval[m_write_idx];
    m_write_idx++;
    m_write_idx &= m_value_buffer_wrap;
    BF_obtain_value(m_io->m_hdl_signal, &m_value_data );

  };
template < > 
   void __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: end_of_elaboration() {
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

template < > 
  void __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: write_conn(const ENUM_XXX &value)
  {
    write(value);
  }

template < > 
  void __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: update() {
    if (!G_is_stopped)
      sc_signal<ENUM_XXX>::update();
   }

  // Transport data form SC to HDL
template < > 
   void __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: transport_sc_to_hdl() {
     m_value_data.value.vector = m_vecval[m_read_idx];
     m_read_idx++;
     m_read_idx &= m_value_buffer_wrap;
     BF_transport(m_io->m_hdl_signal, &m_value_data);
   };

template < > 
   s_hdl_v_io * __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: getIO() const { return m_io; }

template < > 
  void __attribute__((weak)) hdl_signal_v<ENUM_XXX> :: s(sc_signal<ENUM_XXX> &s) { m_s = &s; }

#endif
