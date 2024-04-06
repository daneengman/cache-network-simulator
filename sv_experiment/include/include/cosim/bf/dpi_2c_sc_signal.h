// ------------------------------------------------------------------
// SYNOPSYS CONFIDENTIAL                                             
//                                                                   
// This is an unpublished, proprietary work of Synopsys, Inc., and   
// is fully protected under copyright and trade secret laws. You may 
// not view, use, disclose, copy, or distribute this file or any     
// information contained herein except pursuant to a valid written   
// license from Synopsys.                                            
// ------------------------------------------------------------------

#ifndef _dpi_2c_sc_signal_h_
#define _dpi_2c_sc_signal_h_

#include "systemc.h"
#include "svdpi.h"
#include "vcs_cbug_object_info.h"

template < class U, typename T > 
void DPI_HDL_to_SC(T &value, int W, U *a) {
  if (W < 32) {
    int mask = (1 << W) - 1;
    value = (a[0].d & mask);
  } else if (W == 32) {
    value = a[0].d;
  } else if (W < 64) {
    unsigned int mask = (1 << (W - 32)) - 1;
    uint64 tmp = (unsigned int)(a[1].d & mask);
    tmp <<= 32;
    tmp |= (unsigned int)(a[0].d);
    value = tmp;
  } else if (W == 64) {
    uint64 tmp = (unsigned int)(a[1].d);
    tmp <<= 32;
    tmp |= (unsigned int)(a[0].d);
    value = tmp;
  } else {
    int S = (W / 32) + 1;
    int mw = W % 32;
    unsigned int mask = (1 << mw) - 1;
    value = a[S-1].d & mask;
    for (int i = 1; i < S; ++i) {
      value <<= 32;
      value += a[S - i - 1].d;
    }
  }
}

template < class U >
void DPI_convert_sc(sc_int_base &value, int W, U *a) {
  DPI_HDL_to_SC(value, W, a);
}

template < class U >
void DPI_convert_sc(sc_signed &value, int W, U *a) {
  DPI_HDL_to_SC(value, W, a);
}

template < class U >
void DPI_convert_sc(sc_uint_base &value, int W, U *a) {
  DPI_HDL_to_SC(value, W, a);
}

template < class U >
void DPI_convert_sc(sc_unsigned &value, int W, U *a) {
  DPI_HDL_to_SC(value, W, a);
}

template < class U >
void DPI_convert_sc(sc_lv<1> &value, int, U &a) {
}

template < int W, class U >
void DPI_convert_sc(sc_lv<W> &value, int w, U *a) {
  int rc; // = a[0].c;
  int rd; // = a[0].d;

/*   char *s = new char [w + 1]; */
/*   s[w] = 0; */

  int j = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 32) == 0) {
      rc = a[j].c;
      rd = a[j].d;
      ++j;
    }
    int mrc = rc & 0x01;
    int mrd = rd & 0x01;
    rc >>= 1;
    rd >>= 1;

    if (mrc == 0)
      if (mrd == 0) /*s[w - i - 1 ] = '0'; */ value.set_bit(i, sc_dt::Log_0);
      else /* s[w - i - 1 ] = '1';  */ value.set_bit(i, sc_dt::Log_1);
    else
      if (mrd == 0) /*s[w - i - 1 ] = 'Z'; */ value.set_bit(i, sc_dt::Log_Z);
      else /*s[w - i - 1 ] = 'X'; */ value.set_bit(i, sc_dt::Log_X);
  }
/*   std::cout << "DPI_convert: " << value.to_string() << "\n"; */
/*   static int cnt = 0; */
/*   cnt++; */
/*   if (cnt > 100) exit(1); */
}

template < int W, class U >
void DPI_convert_sc(sc_bv<W> &value, int w, U *a) {
  int rc; // = a[0].c;
  int rd; // = a[0].d;

  char *s = new char [w + 1];
  s[w] = 0;

  int j = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 32) == 0) {
      rc = a[j].c;
      rd = a[j].d;
      ++j;
    }
    int mrc = rc & 0x01;
    int mrd = rd & 0x01;
    rc >>= 1;
    rd >>= 1;

    if (mrc == 0)
      if (mrd == 0) s[w - i - 1] = '0'; 
      else s[w - i - 1] = '1'; 
    else
      s[w - i - 1] = '0';
  }
  value = s;
  delete [] s;
}

template < int W>
void DPI_convert_sc(sc_bv<W> &value, int w, svBitVec32* a) {
  int m = (W+31)>>5;

  for (int j = 0; j < m; ++j) {
    value.set_word(j, a[j]); 
  }
}
inline void DPI_convert_sc(bool &value, int w, const unsigned char a) {
  switch ((int)(a)) {
  case 1: value = 1; break;
  case 0: 
  case 2:
  case 3:
  default:
    value = 0; break;
    break;
  }
}

inline void DPI_convert_sc(sc_bit &value, int w, const unsigned char a) {
  switch ((int)(a)) {
  case 1: value = 1; break;
  case 0: 
  case 2:
  case 3:
  default:
    value = 0; break;
    break;
  }
}

inline void DPI_convert_sc(sc_logic &value, int w, const unsigned char a) {
  switch ((int)(a)) {
  case 1: value = SC_LOGIC_1; break;
  case 0: value = SC_LOGIC_0; break;
  case 2: value = SC_LOGIC_Z; break;
  case 3: 
  default:
    value = SC_LOGIC_X; 
    break;
  }
  //  std::cout << "DPI_convert: " << value << "\n";
}

inline void DPI_convert_sc(sc_int<1> &value, int, const unsigned char a) {
    value = (int)a;
}
inline void DPI_convert_sc(sc_uint<1> &value, int, const unsigned char a) {
    value = (int)a;
}
inline void DPI_convert_sc(sc_bigint<1> &value, int, const unsigned char a) {
    value = (int)a;
}
inline void DPI_convert_sc(sc_biguint<1> &value, int, const unsigned char a) {
    value = (int)a;
}
inline void DPI_convert_sc(sc_bv<1> &value, int, const unsigned char a) {
    switch ((int)(a)) {
        case 1: value.set_word(0,1);; break;
        case 0: 
        case 2:
        case 3:
        default: value.set_word(0,0); break;
    }
}
inline void DPI_convert_sc(sc_lv<1> &value, int, const unsigned char a) {
    switch ((int)(a)) {
        case 1: value.set_bit(0,sc_dt::Log_1); break;
        case 0: value.set_bit(0,sc_dt::Log_0); break;
        case 2: value.set_bit(0,sc_dt::Log_Z); break;
        case 3: 
        default: value.set_bit(0,sc_dt::Log_X); break;
    }
}

template < class U >
void DPI_convert_sc(int &value, int w, U *a) {
  value = (int)a->d;
}
template < class U >
void DPI_convert_sc(unsigned int &value, int w, U *a) {
  value = (int)a->d;
}
template < class U >
void DPI_convert_sc(unsigned short &value, int w, U *a) {
  value = (int)a->d;
}
template < class U >
void DPI_convert_sc(short &value, int w, U *a) {
  value = (int)a->d;
}
template < class U >
void DPI_convert_sc(unsigned char &value, int w, U *a) {
  value = (int)a->d;
}
template < class U >
void DPI_convert_sc(char &value, int w, U *a) {
  value = (int)a->d;
}
template < class U >
void DPI_convert_sc(unsigned long &value, int w, U *a) {
  value = (int)a->d;
}
template < class U >
void DPI_convert_sc(long &value, int w, U *a) {
/*   if (sizeof(long) > 32) { */
/*     value = (int)a[1].d; */
/*     value <<= 32; */
/*   } */
  value = (int)a[0].d;
  
}
inline void DPI_convert_sc(double &value, int w, const double a) {
  value = a;
}

template < class T , class U >
class dpi_2c_sc_signal : public sc_signal<T>
{
 public:
  dpi_2c_sc_signal() : sc_signal<T>(), m_w(0)
  {
    sc_snps::vcs_cbug_attach_object_info_for_signal(this);
  }
  void write(U a) {
    T value;
    DPI_convert_sc(value, m_w, a);
    sc_signal<T>::write(value);
  }
  void setW(int w) { m_w = w; }
 private:
  int m_w;
};

#endif
