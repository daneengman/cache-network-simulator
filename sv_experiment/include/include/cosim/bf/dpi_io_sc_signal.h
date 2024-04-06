// ------------------------------------------------------------------
// SYNOPSYS CONFIDENTIAL                                             
//                                                                   
// This is an unpublished, proprietary work of Synopsys, Inc., and   
// is fully protected under copyright and trade secret laws. You may 
// not view, use, disclose, copy, or distribute this file or any     
// information contained herein except pursuant to a valid written   
// license from Synopsys.                                            
// ------------------------------------------------------------------

#ifndef _dpi_io_sc_signal_h_
#define _dpi_io_sc_signal_h_

#include "systemc_user.h"
#include <vector>
#include "vcs_cbug_object_info.h"

extern void BF_notify_vcs_event();
extern void BF_notify_sc_event();


template < int W , class U , class V , class X >
class dpi_io_sc_signal_rv : public sc_signal_rv<W>
{
  typedef void (*F)(const U);

 public:
  explicit dpi_io_sc_signal_rv( const char* name_ , const sc_lv<W> &zzz)
    : sc_signal_rv<W>( name_ ), m_B(0)
    , m_sv_value(zzz), m_sc_value(zzz), m_new_value(zzz), m_zzz(zzz), m_sv_set(0), m_sc_set(0), m_time(0)
    {
      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
    }
  
  void update() {

    sc_lv<W> tmp_sc;
    sc_lv<W> tmp_sv;

    int remember_sv = -1;
    int remember_sc = -1;

/*     std::cout << "Resolution for " << this->name() << " --------------------------------"  */
/* 	      << m_sv_set << " " << m_sc_set << " ----\n"; */
    std::cout << m_sv_set << ":" << m_sc_set << "  ";
    for (int i = 0; i < sc_signal_rv<W>::m_val_vec.size(); ++i) {
      std::cout << "@" << i << " = [" << sc_signal_rv<W>::m_val_vec[i]->to_string() << "]  ";
    }
    std::cout << "\n";
    
    if (sc_signal_rv<W>::m_val_vec.size() > 1) {
      for (int i = 0; i < sc_signal_rv<W>::m_val_vec.size(); ++i) {
	if (m_sv_set == 0) {
	  if (sc_signal_rv<W>::m_proc_vec[i] == 0) {
	    tmp_sc = *sc_signal_rv<W>::m_val_vec[i];
	    *sc_signal_rv<W>::m_val_vec[i] = m_zzz;
	    remember_sv = i;
	  }
	} 
	if (m_sc_set == 0) {
	  if (sc_signal_rv<W>::m_proc_vec[i] != 0) {
	    tmp_sc = *sc_signal_rv<W>::m_val_vec[i];
	    *sc_signal_rv<W>::m_val_vec[i] = m_zzz;
	    remember_sc = i;
	  }
	}
      }
    }

    if (sc_signal_rv<W>::m_val_vec.size() > 0)
      sc_signal_rv<W>::update();
    
    if (sc_signal_rv<W>::m_val_vec.size() > 1) {
      if (remember_sc != (-1)) {
	*sc_signal_rv<W>::m_val_vec[remember_sc] = tmp_sc;
      }
      if (remember_sv != (-1)) {
	*sc_signal_rv<W>::m_val_vec[remember_sv] = tmp_sv;
      }
    }



    if (m_s) 
      svSetScope(m_s);
    else
      svSetScope(svGetScopeFromName(m_myname.c_str()));

    m_old_value = m_new_value;
    m_new_value = this->read();
    DPI_type_convert_sc(m_t, W, m_new_value);

    if (m_new_value != m_old_value) {
      if (m_new_value == m_sv_value) {
	if (m_sv_set != 3) {
	  if (m_new_value != sc_lv<W>('X')) {
	    DPI_type_convert_sc(m_t, W, m_zzz);
	  }
	}
      }
      std::cout << "----> to Verilog " << m_new_value << " for " << this->name() << "\n";
      std::cout << "---->    m_sv_value: " << m_sv_value << "  m_sc_value: " << m_sc_value << "\n";
      //      if ((m_sv_set != 1) || (m_sc_set != 1))
      if ((m_sv_value != m_new_value) || (m_sv_set != 1) || (m_sc_set != 1))
	m_F(m_t);
    }
/*     m_sv_set = 0;  */
/*     m_sc_set = 0; */
  }

  void write_1(U a) {
    resetDelta();
    DPI_convert_sc(m_tmp_value, W, a);

    std::cout << "Write_1 : new = " << m_tmp_value << " prev = " << m_sv_value << "\n";
    if (m_tmp_value == m_sv_value) 
      m_tmp_value = m_zzz; // reverse resolution: FIXME

    m_sv_set = 1;
    m_sv_value = m_tmp_value;
    //    this->request_update();
    sc_signal_rv<W>::write(m_sv_value);
    this->update();
    if (m_B) {
      m_tmp_value = this->read();
      std::cout << "Write_1 : writing to SystemC: " << m_tmp_value << " m_sc_value: " << m_sc_value << "\n";
      if (m_tmp_value != m_sc_value)
	m_B->write(m_tmp_value);
    }

#if 0
    resetDelta();
    // new value from verilog
    DPI_convert_sc(m_tmp_value, W, a);

    std::cout << "ARRAY ";
    if (sc_signal_rv<W>::m_val_vec.size() > 1) {
      for (int i = 0; i < sc_signal_rv<W>::m_val_vec.size(); ++i) {
	//	      *sc_signal_rv<W>::m_val_vec[i] = m_zzz;
	std::cout << "[" << i << "] = " << *sc_signal_rv<W>::m_val_vec[i] << " ";
      }
    }
    std::cout << "\n";

    std::cout << "Write from Verilog " << m_tmp_value << " (new=" << m_new_value 
	      << ") for " << this->name() << "\n";
    std::cout << ".... m_sv_set = " << m_sv_set << " : m_sc_set = " << m_sc_set << "\n";
    std::cout << "     m_sv_value = " << m_sv_value << " : m_sc_value = " << m_sc_value << "\n";

    if (m_tmp_value == m_sv_value) m_tmp_value = m_zzz;



    //    if (m_B) // systemc-on-top
      if ((m_sv_set == 1) && (m_sc_set == 1)) {
	if (m_tmp_value == m_new_value) {
	  if (m_tmp_value != m_sv_value) {
	    if (m_sc_value != m_sv_value) {
	      m_sv_value = m_tmp_value;
	      this->request_update();
	      sc_signal_rv<W>::write(m_sv_value);
	      if (0)
	      if (m_B) {
		m_B->write(m_sv_value);
	      }
	    }
	  }
	}
      }
    

    //    if ((m_sv_set != 1) || (m_sc_set != 1))
      if ((m_tmp_value == m_new_value)) { // && (m_sv_set == 0) || (m_sc_set == 0)) {
	return;
      }


    m_sv_set = 1;

    m_sv_value = m_tmp_value;
    this->request_update();
    sc_signal_rv<W>::write(m_sv_value);

    //    if ((m_sv_set != 1) || (m_sc_set != 1))
      if (m_sv_value == m_new_value) return;

    if (m_B) {
      if (m_sv_value != m_sc_value) {
	m_B->write(m_sv_value);
      }
    }
#endif
  }
  
  virtual void write(const sc_lv<W> &value) {
    resetDelta();

    m_tmp_value = value;
    std::cout << "write   : new = " << m_tmp_value << " prev = " << m_sc_value << "\n";
    if (m_tmp_value == m_sc_value)
      m_tmp_value = m_zzz; // inverse resolution FIXME
    
    m_sc_set = 1;
    m_sc_value = m_tmp_value;
    sc_signal_rv<W>::write(m_sc_value);
    this->update();
    

#if 0
    resetDelta();

    if (m_sc_value == value) m_sc_value = m_zzz;
    else
      m_sc_value = value;

    std::cout << "Write from SystemC " << m_tmp_value << " (new=" << m_new_value 
	      << ") for " << this->name() << "\n";


    if (m_sc_value == m_new_value) {
      if (m_time != 0)
	return;
    }
    m_sc_set = 1;
    this->request_update();
    sc_signal_rv<W>::write(value);
#endif
  }    

  void setName(const std::string &n) {
    m_myname = n;
  }
  void setF(F f) { m_F = f; }
  void setW(int w) { 
    m_w = w; 
    if (w > 0) { 
      m_t = new X[w]; 
      m_z = new X[w]; 
      DPI_type_convert_sc(m_z, w, m_zzz);
    } 
  }
  void setScope(svScope s) { m_s = s; }
  void setB(sc_inout_rv<W> *b) { m_B = b; }

  void resetDelta() {
    uint64 t = sc_time_stamp().value();
    std::cout << "DELTA TIME " << m_time << " : " << t << "\n"; 
    if (t != m_time) {
      m_time = t;
      m_sc_set = 0;
      m_sv_set = 0;
    }
  }

 private:
  std::string m_myname; // it's my name
  F m_F;                // SystemVerilog DPI callback
  int m_w;              // width of vector
  V m_t;                // tmporary
  V m_z;                // a 'z' vector in SystemVerilog notation
  svScope m_s;          // SystemVerilog scope
  sc_inout_rv<W> *m_B;  // systemc-on-top: pointer to port of calling module

  sc_lv<W> m_sc_value;  // last verilog value
  sc_lv<W> m_sv_value;  // last systemc value
  sc_lv<W> m_old_value; // old resolution value
  sc_lv<W> m_new_value; // new resolution value
  sc_lv<W> m_zzz;       // a 'z' factor
  sc_lv<W> m_tmp_value; // temporary

  int m_sv_set;
  int m_sc_set;
  uint64 m_time;
};

template < class U , class V , class X >
class dpi_io_sc_signal_resolved : public sc_signal_resolved
{
  typedef void (*F)(const U);

 public:
  explicit dpi_io_sc_signal_resolved( const char *name_ , const char *)
    : sc_signal_resolved(name_), m_B(0)
    , m_sv_value(SC_LOGIC_Z), m_sc_value(SC_LOGIC_Z), m_new_value(SC_LOGIC_Z), m_zzz('z'), m_sv_set(0)
    {
      DPI_type_convert_sc(&m_z, 1, m_zzz);
      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
    }

  void update() {
    sc_logic tmp;

    int remember_i = -1;
    if (sc_signal_resolved::m_val_vec.size() > 1) {
      if (m_sv_set == 0) {
	for (int i = 0; i < sc_signal_resolved::m_val_vec.size(); ++i) {
	  if (sc_signal_resolved::m_proc_vec[i] == 0) {
#if SYSTEMC_VERSION >= 20110630
	    tmp = sc_signal_resolved::m_val_vec[i];
	    sc_signal_resolved::m_val_vec[i] = m_zzz;
#else
	    tmp = *sc_signal_resolved::m_val_vec[i];
	    *sc_signal_resolved::m_val_vec[i] = m_zzz;
#endif
	    remember_i = i;
	  }
	}
      }
    }

    if (sc_signal_resolved::m_val_vec.size() > 0) 
      sc_signal_resolved::update();

    if (sc_signal_resolved::m_val_vec.size() > 1) {
      if (m_sv_set == 0) {
#if SYSTEMC_VERSION >= 20110630
	sc_signal_resolved::m_val_vec[remember_i] = tmp;
#else
	*sc_signal_resolved::m_val_vec[remember_i] = tmp;
#endif
      }
    }

    if (m_s) 
      svSetScope(m_s);
    else
      svSetScope(svGetScopeFromName(m_myname.c_str()));

    m_old_value = m_new_value;
    m_new_value = this->read();
    DPI_type_convert_sc(&m_t, 1, m_new_value);

    if (m_new_value != m_old_value) {
      if (m_new_value == m_sv_value) {
	if (m_sv_set != 3) {
	  if (m_new_value != sc_dt::Log_X) {
	    DPI_type_convert_sc(&m_t, 1, m_zzz);
	  }
	}
      }
      m_F(m_t);
    }
    m_sv_set = 0;
  }

  void write_1(U a) {
    // new value from verilog
    DPI_convert_sc(m_tmp_value, 1, a);

    if (m_tmp_value == m_new_value) {
      return;
    }

    m_sv_set = 1;

    m_sv_value = m_tmp_value;
    this->request_update();
    sc_signal_resolved::write(m_sv_value);

    if (m_sv_value == m_new_value) return;

    if (m_B) {
      if (m_sv_value != m_sc_value) {
	m_B->write(m_sv_value);
      }
    }
  }

  virtual void write(const sc_logic &value) {
    m_sc_value = value;
    if (m_sc_value == m_new_value) {
      return;
    }
    
    this->request_update();
    sc_signal_resolved::write(value);
  }

  void setName(const std::string &n) {
    m_myname = n;
  }
  void setF(F f) { m_F = f; }
  void setW(int) { }
  void setScope(svScope s) { m_s = s; }
  void setB(sc_inout_resolved *b) { m_B = b; }

 private:
  std::string m_myname;   // it's my name
  F m_F;                  // SystemVerilog DPI callback
  V m_t;                  // temporary
  V m_z;                  // a 'z' value in SystemVerilog notation
  svScope m_s;            // SystemVerilog scope
  sc_inout_resolved *m_B; // systemc-on-top: Pointer to port of calling module

  sc_logic m_sc_value;    // last systemc value
  sc_logic m_sv_value;    // last verilog value
  sc_logic m_old_value;   // old resolution value
  sc_logic m_new_value;   // new resolution value
  sc_logic m_zzz;         // a 'z' factor
  sc_logic m_tmp_value;   // temporary

  int m_sv_set;
};

#endif
