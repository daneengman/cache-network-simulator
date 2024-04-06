// ------------------------------------------------------------------
// SYNOPSYS CONFIDENTIAL                                             
//                                                                   
// This is an unpublished, proprietary work of Synopsys, Inc., and   
// is fully protected under copyright and trade secret laws. You may 
// not view, use, disclose, copy, or distribute this file or any     
// information contained herein except pursuant to a valid written   
// license from Synopsys.                                            
// ------------------------------------------------------------------

#ifndef _dpi_2v_sc_signal_h_
#define _dpi_2v_sc_signal_h_

#include "systemc.h"
#include "svdpi.h"
#include "vcs_cbug_object_info.h"

extern "C" bool BF_all_initial_events_are_done();

template < class U, typename T > 
void DPI_SC_to_HDL( U *t, int W, const T& value) 
{
  if (W < 32) {
    int mask = (1 << W) - 1;
    int val = value.to_int();
    (&t[0])->c = 0;
    (&t[0])->d = (val & mask);
  } else if (W == 32) {
    (&t[0])->c = 0;
    (&t[0])->d = value.to_int();
  } else if (W < 64) {
    int64 val = value.to_uint64();
    unsigned int mask = (1 << (W - 32)) - 1;
    (&t[1])->c = 0;
    (&t[1])->d = (unsigned int)((val >> 32) & mask);
    mask = 0xffffffff;
    (&t[0])->c = 0;
    (&t[0])->d = (unsigned int)(val & mask);
  } else if (W == 64) {
    uint64 val = value.to_int64();
    (&t[1])->c = 0;
    (&t[1])->d = (unsigned int)((val >> 32) & 0xffffffff);
    (&t[0])->c = 0;
    (&t[0])->d = (unsigned int)(val & 0xffffffff);
  } else {
    int size = W;
    int word = -1;
    int mask = 0;
    for (int i = 0; i < size; ++i) {
      if ((i % 32 ) == 0) {
	word++;
	mask = 1;
	(&t[word])->c = 0;
	(&t[word])->d = 0;
      }
      if (value[i] == 1) {
	(&t[word])->d |= mask;
      }
      mask <<= 1;
    }
  }
}

inline void DPI_type_convert_sc(unsigned char *t, int, const sc_int<1>& value)
{
    // t represents an unsigned 1 bit reg here.
    //  Assigning '-1' results in a SV value = 'C'
    int tmp_int = value.to_int();
    if (tmp_int != 0) {
        *t = 1;
    } else {
        *t = 0;
    }
}

inline void DPI_type_convert_sc(unsigned char *t, int W, const sc_int_base & value)
{
  *t = value.to_int();
}

inline void DPI_type_convert_sc(svLogicVec32 *t, int W, const sc_int_base & value)
{
  DPI_SC_to_HDL(t, W, value); 
}

inline void DPI_type_convert_sc(unsigned char *t, int W, const sc_uint_base & value)
{
  *t = value.to_int();
}

inline void DPI_type_convert_sc(svLogicVec32 *t, int W, const sc_uint_base & value)
{
  DPI_SC_to_HDL(t, W, value); 
}

template < class U > 
void DPI_type_convert_sc(U *t, int W, const sc_signed & value)
{
  DPI_SC_to_HDL(t, W, value); 
}

template < class U > 
void DPI_type_convert_sc(U *t, int W, const sc_unsigned & value)
{
  DPI_SC_to_HDL(t, W, value); 
}

template < class U > 
void DPI_type_convert_sc(U *t, int, const sc_biguint<1> & value)
{
    *t = value.to_uint();
}

template < class U > 
void DPI_type_convert_sc(U *t, int, const sc_bigint<1> & value)
{
    *t = value.to_uint();
}

template < class U >
inline void DPI_type_convert_sc(U *t, int, const sc_bv<1>& value) {
    switch(value.get_bit(0)) {
        case sc_dt::Log_0: *t = 0; break;
        case sc_dt::Log_1: *t = 1; break;
        default: break;
    }
}

template < class U >
void DPI_type_convert_sc(U *t, int, const sc_lv<1> &value) {
    switch(value.get_bit(0)) {
        case sc_dt::Log_0: *t = 0; break;
        case sc_dt::Log_1: *t = 1; break;
        case sc_dt::Log_Z: *t = 2; break;
        case sc_dt::Log_X: *t = 3; break;
        default: break;
    }
}

template < int W, class U >
void DPI_type_convert_sc(U *t, int, const sc_lv<W> &value) {
  const char *s_value;
  std::string str_value = value.to_string();
  s_value = str_value.c_str();

  int m = (W+31)>>5;

  for (int j = 0; j < m; ++j) {
    t[j].c = 0;
    t[j].d = 0;
  }

  for (int i = 0; i < W; ++i) {
    for (int j = m-1; j > 0; --j) {
      t[j].c <<= 1;
      t[j].d <<= 1;
      t[j].c += ((t[j-1].c & 0x80000000) ? 1 : 0);
      t[j].d += ((t[j-1].d & 0x80000000) ? 1 : 0);
    }

    t[0].c <<= 1;
    t[0].d <<= 1;
    switch(s_value[i]) {
    case '0': break;
    case '1': t->d += 1; break;
    case 'X': t->d += 1; t->c += 1; break;
    case 'Z': t->c += 1; break;
    default:
      std::cerr << "Oops, cannot handle '" << s_value[i] << "'\n";
      break;;
    }
  }
}

template < int W, class U >
void DPI_type_convert_sc(U *t, int, const sc_bv<W> &value) {
  const char *s_value;
  std::string str_value = value.to_string();
  s_value = str_value.c_str();

  int m = (W+31)>>5;

  for (int j = 0; j < m; ++j) {
    t[j].c = 0;
    t[j].d = 0;
  }

  for (int i = 0; i < W; ++i) {
    for (int j = m-1; j > 0; --j) {
      t[j].d <<= 1;
      t[j].d += ((t[j-1].d & 0x80000000) ? 1 : 0);
    }

    t[0].c <<= 1;
    t[0].d <<= 1;

    switch(s_value[i]) {
    case '1': t->d += 1; break;
    case '0': 
    case 'Z': 
    case 'X': break;
    default:
      std::cerr << "Oops, cannot handle '" << s_value[i] << "'\n";
      break;;
    }
  }
}

template < int W >
void DPI_type_convert_sc(svBitVec32 *t, int, const sc_bv<W> &value) {
  int m = (W+31)>>5;

  for (int j = 0; j < m; ++j) {
    t[j] = value.get_word(j);
  }
}

template < class U >
void DPI_type_convert_sc(U *t, int, const bool &value) {
  *t = value;
}
template < class U >
void DPI_type_convert_sc(U *t, int, const long &value) {
  t[0].c = 0;
  t[0].d = (int)value;
/*   t[1].c = 0; */
/*   t[1].d = 0; */
}
template < class U >
void DPI_type_convert_sc(U *t, int, const unsigned long &value) {
  t[0].c = 0;
  t[0].d = (int)value;
/*   t[1].c = 0; */
/*   t[1].d = 0; */
}

template < class U >
void DPI_type_convert_sc(U *t, int, const int &value) {
  t->c = 0;
  t->d = (int)value;
}
template < class U >
void DPI_type_convert_sc(U *t, int, const unsigned int &value) {
  t->c = 0;
  t->d = (int)value;
}

template < class U >
void DPI_type_convert_sc(U *t, int, const short &value) {
  t->c = 0;
  t->d = (int)value;
}
template < class U >
void DPI_type_convert_sc(U *t, int, const unsigned short &value) {
  t->c = 0;
  t->d = (int)value;
}

template < class U >
void DPI_type_convert_sc(U *t, int, const char &value) {
  t->c = 0;
  t->d = (int)value;
}
template < class U >
void DPI_type_convert_sc(U *t, int, const unsigned char &value) {
  t->c = 0;
  t->d = (int)value;
}
inline void DPI_type_convert_sc(double *t, int, const double &value) {
  *t = value;
}

template < class U >
inline void DPI_type_convert_sc(U *t, int, const sc_logic &value) {
  switch(value.value()) {
  case sc_dt::Log_0: *t = 0; break;
  case sc_dt::Log_1: *t = 1; break;
  case sc_dt::Log_Z: *t = 2; break;
  case sc_dt::Log_X: *t = 3; break;
  default:
    break;
  }
}

template < class U >
inline void DPI_type_convert_sc(U *t, int, const sc_bit &value) {
  if(value.to_bool()) 
    *t = 1;
  else
    *t = 0;
}


template < class T , class U , class V , class X >
class dpi_2v_sc_signal : public sc_signal<T>
{
  typedef void (*F)(const U);


 public:
  dpi_2v_sc_signal() : sc_signal<T>()
  {
    sc_snps::vcs_cbug_attach_object_info_for_signal(this);
  }
  virtual void write(const T &value) {
    svSetScope(m_s);
    DPI_type_convert_sc(m_t, m_w, value);
    if (BF_all_initial_events_are_done())
      m_F(m_t);
    else
      m_F1(m_t);
    sc_signal<T>::write(value);
  }
  void setName(const std::string &n) {
    m_myname = n;
  }
  void setF(F f, F f1) { m_F = f; m_F1 = f1; }
  void setW(int w, int words) { 
    m_w = w;
    if (words > 0) m_t = new X[words]; 
  }
  void setScope(svScope s) { m_s = s; }
 private:
  std::string m_myname;
  F m_F;
  F m_F1;
  V m_t;
  int m_w;
  svScope m_s;
};

template < class T >
class dpi_2v_sc_signal<T, const unsigned char, unsigned char, unsigned char> : public sc_signal<T>
{
  typedef void (*F)(const unsigned char);

 public:
  dpi_2v_sc_signal() : sc_signal<T>()
  {
    sc_snps::vcs_cbug_attach_object_info_for_signal(this);
  }
  virtual void write(const T &value) {
    svSetScope(m_s);
    DPI_type_convert_sc(&m_t, m_w, value);
    if (BF_all_initial_events_are_done())
      m_F(m_t);
    else
      m_F1(m_t);
     sc_signal<T>::write(value);
  }
  void setName(const std::string &n) {
    m_myname = n;
  }
  void setF(F f, F f1) { m_F = f; m_F1 = f1; }
  void setW(int w, int) { m_w = w; }  
  void setScope(svScope s) { m_s = s; }
 private:
  std::string m_myname;
  F m_F;
  F m_F1;
  unsigned char m_t;
  svScope m_s;
  int m_w;
};


template < class T >
class dpi_2v_sc_signal<T, const double, double, double> : public sc_signal<T>
{
  typedef void (*F)(const double);

 public:
  dpi_2v_sc_signal() : sc_signal<T>()
  {
    sc_snps::vcs_cbug_attach_object_info_for_signal(this);
  }
  virtual void write(const T &value) {
    svSetScope(m_s);
    DPI_type_convert_sc(&m_t, m_w, value);
    if (BF_all_initial_events_are_done())
      m_F(m_t);
    else
      m_F1(m_t);
     sc_signal<T>::write(value);
  }
  void setName(const std::string &n) {
    m_myname = n;
  }
  void setF(F f, F f1) { m_F = f; m_F1 = f1; }
  void setW(int w, int) { m_w = w; }  
  void setScope(svScope s) { m_s = s; }
 private:
  std::string m_myname;
  F m_F;
  F m_F1;
  double m_t;
  svScope m_s;
  int m_w;
};
#endif
