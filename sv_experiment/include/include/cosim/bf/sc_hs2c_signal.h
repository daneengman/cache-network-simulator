// ------------------------------------------------------------------
// SYNOPSYS CONFIDENTIAL                                             
//                                                                   
// This is an unpublished, proprietary work of Synopsys, Inc., and   
// is fully protected under copyright and trade secret laws. You may 
// not view, use, disclose, copy, or distribute this file or any     
// information contained herein except pursuant to a valid written   
// license from Synopsys.                                            
// ------------------------------------------------------------------

#ifndef _sc_hs2c_signal_h_
#define _sc_hs2c_signal_h_

#include "systemc.h"
#include "svdpi.h"
#include "vcs_cbug_object_info.h"

template < typename T > 
void typeconv_v_to_sc(T &value, int W, vec32 *a) {
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

inline void TypeConvert_v_to_sc(sc_int<1> &value, int, vec32 *a) {
  value = (a) ? 1 : 0;
}

inline void TypeConvert_v_to_sc(sc_int_base &value, int W, vec32 *a) {
  typeconv_v_to_sc(value, W, a);
}

inline void TypeConvert_v_to_sc(sc_bigint<1> &value, int, vec32 *a) {
  value = (a) ? 1 : 0;
}
inline void TypeConvert_v_to_sc(sc_signed &value, int W, vec32 *a) {
  typeconv_v_to_sc(value, W, a);
}

inline void TypeConvert_v_to_sc(sc_uint<1> &value, int, vec32 *a) {
  value = (a) ? 1 : 0;
}

inline void TypeConvert_v_to_sc(sc_uint_base &value, int W, vec32 *a) {
  typeconv_v_to_sc(value, W, a);
}

inline void TypeConvert_v_to_sc(sc_biguint<1> &value, int, vec32 *a) {
  value = (a) ? 1 : 0;
}

inline void TypeConvert_v_to_sc(sc_unsigned &value, int W, vec32 *a) {
  typeconv_v_to_sc(value, W, a);
}

inline void TypeConvert_v_to_sc(sc_bv<1> &value, int, vec32 *a) {
  int ai = (int)(((size_t)a & 0xffffffff));
  switch ((ai)) {
  case 1: value.set_bit(0, sc_dt::Log_1); break;
  case 0: 
  default:
    value.set_bit(0, sc_dt::Log_0); break;
    break;
  }
}

inline void TypeConvert_v_to_sc(sc_lv<1> &value, int, vec32 *a) {
  int ai = (int)(((size_t)a & 0xffffffff));
  switch ((ai)) {
  case 1: value.set_bit(0, sc_dt::Log_1); break;
  case 0: value.set_bit(0, sc_dt::Log_0); break;
  case 2: value.set_bit(0, sc_dt::Log_Z); break;
  case 3: 
  default:
    value.set_bit(0, sc_dt::Log_X); break;
    break;
  }
}

template < int W >
void TypeConvert_v_to_sc(sc_lv<W> &value, int w, vec32 *a) {
  int rc; 
  int rd;

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
      if (mrd == 0)  value.set_bit(i, sc_dt::Log_0);
      else value.set_bit(i, sc_dt::Log_1);
    else
      if (mrd == 0) value.set_bit(i, sc_dt::Log_Z);
      else value.set_bit(i, sc_dt::Log_X);
  }
}

template < int W >
void TypeConvert_v_to_sc(sc_bv<W> &value, int w, vec32 *a) {
  int rc; 
  int rd; 

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
void TypeConvert_v_to_sc(sc_bv<W> &value, int w, svBitVec32* a) {
  int m = (W+31)>>5;

  for (int j = 0; j < m; ++j) {
    value.set_word(j, a[j]); 
  }
}

inline void TypeConvert_v_to_sc(bool &value, int w, vec32 *a) {
  value = (a) ? true : false;
}

inline void TypeConvert_v_to_sc(sc_bit &value, int w, vec32 *a) {
  value = (a) ? true : false;
}

inline void TypeConvert_v_to_sc(sc_logic &value, int w, vec32 *a) {
  int ai = (int)(((size_t)a & 0x03));
  switch ((ai)) {
  case 1: value = SC_LOGIC_1; break;
  case 0: value = SC_LOGIC_0; break;
  case 2: value = SC_LOGIC_Z; break;
  case 3: 
  default:
    value = SC_LOGIC_X; 
    break;
  }
}

inline int TypeConvert_v_to_sc_R(sc_logic &value, int w, vec32 *a) {
  //  int ai = (int)(((size_t)a & 0xffffffff));
  int ai = (int)(((size_t)a & 0x03));
  //  if ((ai & 0xfc) != 0) { value = SC_LOGIC_Z; return 0; }
  switch ((ai)) {
  case 1: value = SC_LOGIC_1; break;
  case 0: value = SC_LOGIC_0; break;
  case 2: value = SC_LOGIC_Z; break;
  case 3: 
  default:
    value = SC_LOGIC_X; 
    break;
  }
  return 0;
}

inline void TypeConvert_v_to_sc(int &value, int w, vec32 *a) {
  value = (int)a->d;
}
inline void TypeConvert_v_to_sc(unsigned int &value, int w, vec32 *a) {
  value = (int)a->d;
}
inline void TypeConvert_v_to_sc(unsigned short &value, int w, vec32 *a) {
  value = (int)a->d;
}
inline void TypeConvert_v_to_sc(short &value, int w, vec32 *a) {
  value = (int)a->d;
}
inline void TypeConvert_v_to_sc(unsigned char &value, int w, vec32 *a) {
  value = (int)a->d;
}
inline void TypeConvert_v_to_sc(char &value, int w, vec32 *a) {
  value = (int)a->d;
}
inline void TypeConvert_v_to_sc(unsigned long &value, int w, vec32 *a) {
  value = (int)a->d;
}
inline void TypeConvert_v_to_sc(long &value, int w, vec32 *a) {
  value = (int)a[0].d;
}

template < int W >
inline void TypeConvert_v_to_sc_exp(sc_lv<W> &value, int w, unsigned int *u) {
  unsigned int val;
  int wcnt = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) val = u[wcnt++];
    unsigned int nibble = val & 0x03;
    val >>= 8;
    switch(nibble) {
    case 0: value.set_bit(i, sc_dt::Log_0); break;
    case 1: value.set_bit(i, sc_dt::Log_1); break;
    case 2: value.set_bit(i, sc_dt::Log_Z); break;
    case 3:
    default: value.set_bit(i, sc_dt::Log_X); break;
    }
  }
}

inline void TypeConvert_v_to_sc_exp(sc_logic &value, int, unsigned int *u) {
  unsigned int val = *u & 0x03;
  switch(val) {
  case 0: value = sc_dt::Log_0; break;
  case 1: value = sc_dt::Log_1; break;
  case 2: value = sc_dt::Log_Z; break;
  case 3:
  default:
    value = sc_dt::Log_X; break;
  }
}

inline void TypeConvert_v_to_sc_exp(sc_bit &value, int, unsigned int *u) {
  unsigned int val = *u & 0x03;
  switch(val) {
  case 1: value = sc_dt::Log_1; break;
  case 0: 
  default:
    value = sc_dt::Log_0; break;
  }
}

inline void TypeConvert_v_to_sc_scalar(sc_logic &value, int, unsigned int *u) {
  unsigned int val = (unsigned int)(((size_t)(u) & 0xffffffff)) & 0x03;
  switch(val) {
  case 0: value = sc_dt::Log_0; break;
  case 1: value = sc_dt::Log_1; break;
  case 2: value = sc_dt::Log_Z; break;
  case 3:
  default:
    value = sc_dt::Log_X; break;
  }
}

template < int W >
inline void TypeConvert_v_to_sc_exp(sc_bv<W> &value, int w, unsigned int *u) {
  unsigned int val;
  int wcnt = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) val = u[wcnt++];
    unsigned int nibble = val & 0x03;
    val >>= 8;
    switch(nibble) {
    case 1: value.set_bit(i, sc_dt::Log_1); break;
    case 0: 
    default: value.set_bit(i, sc_dt::Log_0); break;
    }
  }
}

template < int W >
inline void TypeConvert_v_to_sc_exp(sc_int<W> &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  sc_int<W> mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

template < int W >
inline void TypeConvert_v_to_sc_exp(sc_uint<W> &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  sc_uint<W> mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

template < int W >
inline void TypeConvert_v_to_sc_exp(sc_bigint<W> &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  sc_bigint<W> mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

template < int W >
inline void TypeConvert_v_to_sc_exp(sc_biguint<W> &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  sc_biguint<W> mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

inline void TypeConvert_v_to_sc_exp(char &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  int mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

inline void TypeConvert_v_to_sc_exp(unsigned char &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  int mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

inline void TypeConvert_v_to_sc_exp(int &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  int mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

inline void TypeConvert_v_to_sc_exp(long int &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  int mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

inline void TypeConvert_v_to_sc_exp(short int &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  int mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

inline void TypeConvert_v_to_sc_exp(unsigned int &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  unsigned int mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

inline void TypeConvert_v_to_sc_exp(unsigned short int &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  unsigned int mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

inline void TypeConvert_v_to_sc_exp(unsigned long int &value, int w, unsigned int *a) {
  int c = 0;
  unsigned int v = 0;
  unsigned int mask = 1;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
      v = a[c];
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) value += mask;
    mask <<= 1;
  }
}

inline void TypeConvert_v_to_sc_exp(bool &value, int w, unsigned int *a) {
  if (a[0] & 0x03) value = true; else value = false;
}

//-----------------------------------------------------------
//-- MHDL_INTEGER
//-----------------------------------------------------------

template < class T >
inline void TypeConvert_v_i_to_sc(T &value, int w, unsigned int *a) {
  value = (*a);
}

//-----------------------------------------------------------
//-- MHDL_REAL
//-----------------------------------------------------------

template < class T >
inline void TypeConvert_v_r_to_sc(T &value, int w, unsigned int *a) {
  BfAssert2(1, "Not Supported");
}

//-----------------------------------------------------------
//-- MHDL_REAL_VECTOR
//-----------------------------------------------------------

template < class T >
inline void TypeConvert_v_rv_to_sc(T &value, int w, unsigned int *a) {
  BfAssert2(23, "Not Supported");
}

//-----------------------------------------------------------
//-- MHDL_2STATE_SCALAR
//-----------------------------------------------------------

template < class T >
inline void TypeConvert_v_2ss_to_sc(T &value, int w, unsigned int *a) {
  BfAssert2(18, "Not Supported");
}

//-----------------------------------------------------------
//-- MHDL_2STATE_VECTOR
//-----------------------------------------------------------

template < class T >
inline void TypeConvert_v_2sv_to_sc(T &value, int w, unsigned int *a) {
  BfAssert2(19, "Not Supported");
}

//-----------------------------------------------------------
//-- MHDL_2STATE_WIDEVECTOR
//-----------------------------------------------------------

template < class T >
inline void TypeConvert_v_2swv_to_sc(T &value, int w, unsigned int *a) {
  BfAssert2(20, "Not Supported");
}

//-----------------------------------------------------------
//-- MHDL_LOGIC_SCALAR
//-----------------------------------------------------------

inline void TypeConvert_v_ls_to_sc(bool &value, int w, unsigned int *a) {
  value = ((size_t)a == 1) ? true : false;
  M_BfCollect(3, "bool", w, "->sc");
}

inline void TypeConvert_v_ls_to_sc(sc_logic &value, int w, unsigned int *a) {
  int ai = (int)(((size_t)a & 0xffffffff));
  switch ((ai)) {
  case 1: value = sc_dt::Log_1; break;
  case 0: value = sc_dt::Log_0; break;
  case 2: value = sc_dt::Log_Z; break;
  case 3: 
  default:
    value = sc_dt::Log_X;
    break;
  }
  M_BfCollect(3, "sc_logic", w, "->sc");
}

// only logic value '1' is converted to '1' for systemc, values 'x', 'z' are
// converted to '0'
// This conversion has only one logic scalar bit from verilog
inline void TypeConvert_v_ls_to_sc(sc_int<1> &value, int w, unsigned int *a) {
    value = ((unsigned int)(size_t)a == 0x01) ? 1 : 0;
  M_BfCollect(3, "sc_int", w, "->sc");
}

inline void TypeConvert_v_ls_to_sc(sc_uint<1> &value, int w, unsigned int *a) {
  value = ((unsigned int)(size_t)a == 0x01) ? 1 : 0;
  M_BfCollect(3, "sc_uint", w, "->sc");
}

inline void TypeConvert_v_ls_to_sc(sc_bigint<1> &value, int w, unsigned int *a) {
  value = ((unsigned int)(size_t)a == 0x01) ? 1 : 0;
  M_BfCollect(3, "sc_bigint", w, "->sc");
}

inline void TypeConvert_v_ls_to_sc(sc_biguint<1> &value, int w, unsigned int *a) {
    value = ((unsigned int)(size_t)a == 0x01) ? 1 : 0;
  M_BfCollect(3, "sc_biguint", w, "->sc");
}

inline void TypeConvert_v_ls_to_sc(sc_bv<1> &value, int w, unsigned int *a) {
  int ai = (int)(((size_t)a & 0xffffffff));
  switch ((ai)) {
  case 1: value.set_bit(0, sc_dt::Log_1); break;
  default:
    value.set_bit(0, sc_dt::Log_0); break;
    break;
  }
  M_BfCollect(3, "sc_bv", w, "->sc");
}

template < int W > 
inline void TypeConvert_v_ls_to_sc(sc_bv<W> &value, int w, unsigned int *a) {
  int ai = (int)(((size_t)a & 0xffffffff));
  switch ((ai)) {
  case 1: value.set_bit(0, sc_dt::Log_1); break;
  default:
    value.set_bit(0, sc_dt::Log_0); break;
    break;
  }
  M_BfCollect(3, "sc_bv", w, "->sc");
}

template < int W > 
inline void TypeConvert_v_ls_to_sc(sc_lv<W> &value, int w, unsigned int *a) {
  unsigned int ai = (int)(((size_t)a & 0xffffffff));
  switch ((ai)) {
  case 1: value.set_bit(0, sc_dt::Log_1); break;
  case 0: value.set_bit(0, sc_dt::Log_0); break;
  case 2: value.set_bit(0, sc_dt::Log_Z); break;
  case 3: 
  default:
    value.set_bit(0, sc_dt::Log_X); break;
    break;
  }
  M_BfCollect(3, "sc_lv", w, "->sc");
}

inline void TypeConvert_v_ls_to_sc(sc_lv<1> &value, int w, unsigned int *a) {
  unsigned int ai = (int)(((size_t)a & 0xffffffff));
  switch ((ai)) {
  case 1: value.set_bit(0, sc_dt::Log_1); break;
  case 0: value.set_bit(0, sc_dt::Log_0); break;
  case 2: value.set_bit(0, sc_dt::Log_Z); break;
  case 3: 
  default:
    value.set_bit(0, sc_dt::Log_X); break;
    break;
  }
  M_BfCollect(3, "sc_lv", w, "->sc");
}

inline void TypeConvert_v_ls_to_sc(sc_bit &value, int w, unsigned int *a) {
  unsigned int ai = (int)(((size_t)a & 0xffffffff));
  switch ((ai)) {
  case 1: value = sc_dt::Log_1; break;
  default:
    value = sc_dt::Log_0; break;
  }
  M_BfCollect(3, "sc_lv", w, "->sc");
}

inline void TypeConvert_v_ls_to_sc(signed char &value, int w, unsigned int *a) {
    value = (signed char)(((size_t)a & 0x01));
}

inline void TypeConvert_v_ls_to_sc(unsigned char &value, int w, unsigned int *a) {
    value = (unsigned char)(((size_t)a & 0x01));
}

inline void TypeConvert_v_ls_to_sc(char &value, int w, unsigned int *a) {
    value = (char)(((size_t)a & 0x01));
}

inline void TypeConvert_v_ls_to_sc(unsigned short &value, int w, unsigned int *a) {
    value = (unsigned short)(((size_t)a & 0x01));
}

inline void TypeConvert_v_ls_to_sc(short &value, int w, unsigned int *a) {
    value = (short)(((size_t)a & 0x01));
}

inline void TypeConvert_v_ls_to_sc(unsigned int &value, int w, unsigned int *a) {
    value = (unsigned int)(((size_t)a & 0x01));
}

inline void TypeConvert_v_ls_to_sc(int &value, int w, unsigned int *a) {
    value = (int)(((size_t)a & 0x01));
}

inline void TypeConvert_v_ls_to_sc(unsigned long &value, int w, unsigned int *a) {
    value = (unsigned long)(((size_t)a & 0x01));
}

inline void TypeConvert_v_ls_to_sc(long &value, int w, unsigned int *a) {
    value = (long)(((size_t)a & 0x01));
}

inline void TypeConvert_v_ls_to_sc(unsigned long long &value, int w, unsigned int *a) {
    value = (unsigned long long)(((size_t)a & 0x01));
}

inline void TypeConvert_v_ls_to_sc(long long &value, int w, unsigned int *a) {
    value = (long long)(((size_t)a & 0x01));
}

template < int W >
inline void TypeConvert_v_ls_to_sc(sc_dt::sc_int<W> &value, int w, unsigned int *a) {
    value = (sc_dt::sc_int<W>)(((size_t)a & 0x01));
}

template < int W >
inline void TypeConvert_v_ls_to_sc(sc_dt::sc_uint<W> &value, int w, unsigned int *a) {
    value = (sc_dt::sc_uint<W>)(((size_t)a & 0x01));
}

template < int W >
inline void TypeConvert_v_ls_to_sc(sc_dt::sc_bigint<W> &value, int w, unsigned int *a) {
    value = (sc_dt::sc_bigint<W>)(((size_t)a & 0x01));
}

template < int W >
inline void TypeConvert_v_ls_to_sc(sc_dt::sc_biguint<W> &value, int w, unsigned int *a) {
    value = (sc_dt::sc_biguint<W>)(((size_t)a & 0x01));
}

template < class T >
inline void TypeConvert_v_ls_to_sc(T &value, int w, unsigned int *a) {
  BfAssert2(3, "Not Supported");
}

//-----------------------------------------------------------
//-- MHDL_LOGIC_VECTOR
//-----------------------------------------------------------

inline void TypeConvert_v_lv_to_sc(bool &value, int w, unsigned int *a) {
  value = ((int)a[1]) ? true : false;
  M_BfCollect(4, "bool", w, "->sc");
}

inline void TypeConvert_v_lv_to_sc(sc_logic &value, int w, unsigned int *a) {
  vec32 *av = (vec32 *)a;
  unsigned int mc = av->c & 0x01;
  if (mc == 0)
    if (mc == 0)
      value = sc_dt::Log_0;
    else
      value = sc_dt::Log_Z;
  else
    if (mc == 0)
      value = sc_dt::Log_1;
    else
      value = sc_dt::Log_X;
  M_BfCollect(4, "sc_logic", w, "->sc");
}

inline void TypeConvert_v_lv_to_sc(char &value, int w, unsigned int *a) {
    value = (int)a[1] & ~(int)a[0];
  M_BfCollect(4, "char", w, "->sc");
}

inline void TypeConvert_v_lv_to_sc(unsigned char &value, int w, unsigned int *a) {
  value = (int)a[1] & ~(int)a[0];
  M_BfCollect(4, "unsigned char", w, "->sc");
}

inline void TypeConvert_v_lv_to_sc(short &value, int w, unsigned int *a) {
  value = (int)a[1] & ~(int)a[0];
  M_BfCollect(4, "short", w, "->sc");
}

inline void TypeConvert_v_lv_to_sc(unsigned short &value, int w, unsigned int *a) {
  value = (int)a[1] & ~(int)a[0];
  M_BfCollect(4, "unsigned short", w, "->sc");
}

inline void TypeConvert_v_lv_to_sc(int &value, int w, unsigned int *a) {
  value = (int)a[1] & ~(int)a[0];
  M_BfCollect(4, "int", w, "->sc");
}

inline void TypeConvert_v_lv_to_sc(unsigned int &value, int w, unsigned int *a) {
  value = (int)a[1] & ~(int)a[0];
  M_BfCollect(4, "unsigned int", w, "->sc");
}

inline void TypeConvert_v_lv_to_sc(long &value, int w, unsigned int *a) {
  value = (long)a[1] & ~(int)a[0];
  M_BfCollect(4, "long", w, "->sc");
}

inline void TypeConvert_v_lv_to_sc(unsigned long &value, int w, unsigned int *a) {
  value = (unsigned long)a[1] & ~(unsigned long)a[0];
  M_BfCollect(4, "unsigned long", w, "->sc");
}

inline void TypeConvert_v_lv_to_sc(long long &value, int w, unsigned int *a) {
/*   value = (int)a[1]; */
/*   M_BfCollect(4, "long long", w, "->sc"); */
  BfAssert2(4, "Not Supported for long long");
}

inline void TypeConvert_v_lv_to_sc(unsigned long long &value, int w, unsigned int *a) {
/*   value = (int)a[1]; */
/*   M_BfCollect(4, "unsigned long long", w, "->sc"); */
  BfAssert2(4, "Not Supported for unsigned long long");
}

template < int W >
inline void TypeConvert_v_lv_to_sc(sc_int<W> &value, int w, unsigned int *a) {
  vec32 *av = (vec32 *)a;
  int word = 0;
  int width = (w > 32) ? 32 : w;
  do {
    value.range(width-1, word * 32) = av[word].d & 0xffffffff & ~av[word].c;
    width += 32;
    if (width > w) width = w;
    ++word;
  } while ((word * 32) < w);

  M_BfCollect(4, "sc_int", w, "->sc");
}

template < int W >
inline void TypeConvert_v_lv_to_sc(sc_uint<W> &value, int w, unsigned int *a) {
  vec32 *av = (vec32 *)a;
  int word = 0;
  int width = (w > 32) ? 32 : w;
  do {
    value.range(width-1, word * 32) = av[word].d & 0xffffffff & ~av[word].c;
    width += 32;
    if (width > w) width = w;
    ++word;
  } while ((word * 32) < w);

  M_BfCollect(4, "sc_uint", w, "->sc");
}

template < int W >
inline void TypeConvert_v_lv_to_sc(sc_bigint<W> &value, int w, unsigned int *a) {
    vec32 *av = (vec32 *)a;
    int S = (w / 32) + 1;
    int mw = w % 32;
    unsigned int mask = (1 << mw) - 1;
    value = av[S-1].d & mask & ~av[S-1].c;
    for (int i = 1; i < S; ++i) {
        value <<= 32;
        value |= av[S - i - 1].d;
    }
    typeconv_v_to_sc(value, w, (vec32 *)a);
    M_BfCollect(4, "sc_bigint", w, "->sc");
}

template < int W >
inline void TypeConvert_v_lv_to_sc(sc_biguint<W> &value, int w, unsigned int *a) {
    vec32 *av = (vec32 *)a;
    int S = (w / 32) + 1;
    int mw = w % 32;
    unsigned int mask = (1 << mw) - 1;
    value = av[S-1].d & mask & ~av[S-1].c;
    for (int i = 1; i < S; ++i) {
        value <<= 32;
        value |= av[S - i - 1].d;
    }
    M_BfCollect(4, "sc_biguint", w, "->sc");
}

template < int W >
inline void TypeConvert_v_lv_to_sc(sc_bv<W> &value, int w, unsigned int *a) {
    vec32 *av = (vec32 *)a;
    int S = (w / 32) + 1;
    int mw = w % 32;
    unsigned int mask = (1 << mw) - 1;
    unsigned int cmask = ~(av[S-1].c);
    value = av[S-1].d & mask & cmask;
    for (int i = 1; i < S; ++i) {
        value <<= 32;
        cmask = ~(av[S - i - 1].c);
        value |= cmask & av[S - i - 1].d;
    }
    M_BfCollect(4, "sc_bv", w, "->sc");
}

template < int W >
inline void TypeConvert_v_lv_to_sc(sc_lv<W> &value, int w, unsigned int *a) {
  int rc; 
  int rd;
  vec32 *av = (vec32 *)a;

  int j = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 32) == 0) {
      rc = av[j].c;
      rd = av[j].d;
      ++j;
    }
    int mrc = rc & 0x01;
    int mrd = rd & 0x01;
    rc >>= 1;
    rd >>= 1;

    if (mrc == 0)
      if (mrd == 0)  value.set_bit(i, sc_dt::Log_0);
      else value.set_bit(i, sc_dt::Log_1);
    else
      if (mrd == 0) value.set_bit(i, sc_dt::Log_Z);
      else value.set_bit(i, sc_dt::Log_X);
  }
  M_BfCollect(4, "sc_lv", w, "->sc");
}

template < class T >
inline void TypeConvert_v_lv_to_sc(T &value, int w, unsigned int *a) {
  BfAssert2(4, "Not Supported");
}

//-----------------------------------------------------------
//-- MHDL_LOGIC_WIDEVECTOR
//-----------------------------------------------------------

template < class T >
inline void TypeConvert_v_lwv_to_sc(T &value, int w, unsigned int *a) {
  BfAssert2(5, "Not Supported");
}

//-----------------------------------------------------------
//-- MHDL_STRENGTH_SCALAR
//-----------------------------------------------------------

inline void TypeConvert_v_ss_to_sc(bool &value, int w, unsigned int *a) {
  unsigned int ai = (int)(((size_t)a & 0xffffffff));
  value = (ai) ? true : false;
  BfCollect(6, "bool", w, "->sc");
}

inline void TypeConvert_v_ss_to_sc(sc_logic &value, int w, unsigned int *a) {
  unsigned int ai = (int)(((size_t)a & 0xffffffff));
  switch (ai) {
  case 0: value = sc_dt::Log_0; break;
  case 1: value = sc_dt::Log_1; break;
  case 2: value = sc_dt::Log_Z; break;
  default:
    value = sc_dt::Log_X; break;
  }
  BfCollect(6, "sc_logic", w, "->sc");
}

inline void TypeConvert_v_ss_to_sc(sc_bit &value, int w, unsigned int *a) {
  unsigned int ai = (int)(((size_t)a & 0xffffffff));
  switch (ai) {
  case 1: value = sc_dt::Log_1; break;
  default:
    value = sc_dt::Log_0; break;
  }
  BfCollect(6, "sc_bit", w, "->sc");
}

template < int W >
inline void TypeConvert_v_ss_to_sc(sc_bv<W> &value, int w, unsigned int *a) { 
  unsigned int ai = (int)(((size_t)a & 0xffffffff));
  int mw = (w > 32) ? 32 : w;
  unsigned int mask = 1;
  for (int i = 0; i < mw; ++i) {
    if (ai & mask) value.set_bit(i, sc_dt::Log_1); else value.set_bit(i, sc_dt::Log_0);
    mask <<= 1;
  }
  BfCollect(6, "sc_bv", w, "->sc");
}

template < int W >
inline void TypeConvert_v_ss_to_sc(sc_lv<W> &value, int w, unsigned int *a) { 
  unsigned int ai = (int)(((size_t)a & 0xffffffff));
  int mw = (w > 32) ? 32 : w;
  unsigned int mask = 1;
  for (int i = 0; i < mw; ++i) {
    if (ai & mask) value.set_bit(i, sc_dt::Log_1); else value.set_bit(i, sc_dt::Log_0);
    mask <<= 1;
  }
  BfCollect(6, "sc_lv", w, "->sc");
}


template < class T >
inline void TypeConvert_v_ss_to_sc(T &value, int w, unsigned int *a) {
  BfAssert2(6, "Not Supported");
}

//-----------------------------------------------------------
//-- MHDL_STRENGTH_VECTOR
//-----------------------------------------------------------
#if defined(sparc)
#define M_TypeConvert_v_sv_to_sc \
  int c = 0;                     \
  unsigned int v = 0;            \
  value = 0;                     \
  for (int i = 0; i < w; ++i) {  \
    if ((i % 4) == 0) {          \
      v = a[c];                  \
      ++c;                       \
    }                            \
    unsigned int vm = v & 0x3000000;\
    v <<= 8;                     \
    if (vm == 0x1000000) value += mask;  \
    mask <<= 1;                  \
  }
#else
#define M_TypeConvert_v_sv_to_sc \
  int c = 0;                     \
  unsigned int v = 0;            \
  value = 0;                     \
  for (int i = 0; i < w; ++i) {  \
    if ((i % 4) == 0) {          \
      v = a[c];                  \
      ++c;                       \
    }                            \
    unsigned int vm = v & 0x03;  \
    v >>= 8;                     \
    if (vm == 1) value += mask;  \
    mask <<= 1;                  \
  }
#endif

inline void TypeConvert_v_sv_to_sc(bool &value, int w, unsigned int *a) {
  bool mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "bool", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(sc_logic &value, int w, unsigned int *a) {
  int ai = (int)(((size_t)a & 0xffffffff));
  switch(ai & 0x03) {
  case 0: value = sc_dt::Log_0; break;
  case 1: value = sc_dt::Log_1; break;
  case 2: value = sc_dt::Log_Z; break;
  default:
    value = sc_dt::Log_X; break;
  }
  M_BfCollect(7, "sc_logic", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(char &value, int w, unsigned int *a) {
  char mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "char", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(unsigned char &value, int w, unsigned int *a) {
  unsigned char mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "unsigned char", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(short &value, int w, unsigned int *a) {
  short mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "short", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(unsigned short &value, int w, unsigned int *a) {
  unsigned short mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "unsigned short", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(int &value, int w, unsigned int *a) {
  int mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "int", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(unsigned int &value, int w, unsigned int *a) {
  unsigned mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "unsigned int", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(long &value, int w, unsigned int *a) {
  int mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "long", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(unsigned long &value, int w, unsigned int *a) {
  unsigned mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "unsigned long", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(long long &value, int w, unsigned int *a) {
  long long mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "long long", w, "-sc");
}

inline void TypeConvert_v_sv_to_sc(unsigned long long &value, int w, unsigned int *a) {
  unsigned long long mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "unsigned long long", w, "-sc");
}

template < int W >
inline void TypeConvert_v_sv_to_sc(sc_int<W> &value, int w, unsigned int *a) {
  sc_int<W> mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "sc_int", w, "-sc");
}

template < int W >
inline void TypeConvert_v_sv_to_sc(sc_uint<W> &value, int w, unsigned int *a) {
  sc_uint<W> mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "sc_uint", w, "-sc");
}

template < int W >
inline void TypeConvert_v_sv_to_sc(sc_bigint<W> &value, int w, unsigned int *a) {
  sc_bigint<W> mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "sc_bigint", w, "-sc");
}

template < int W >
inline void TypeConvert_v_sv_to_sc(sc_biguint<W> &value, int w, unsigned int *a) {
  sc_biguint<W> mask = 1;
  M_TypeConvert_v_sv_to_sc;
  M_BfCollect(7, "sc_biguint", w, "-sc");
}

template < int W >
inline void TypeConvert_v_sv_to_sc(sc_bv<W> &value, int w, unsigned int *a) {
  int j = 0;
  int c = 0;
  unsigned int v = 0;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
#if defined(sparc)
      v = 
	((a[c] & 0xff000000) >> 24) + 
	((a[c] & 0xff0000) >> 8) + 
	((a[c] & 0xff00) << 8) + 
	((a[c] & 0xff) << 24);
#else
      v = a[c];
#endif
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    if (vm == 1) 
      value.set_bit(j, sc_dt::Log_1);
    else
      value.set_bit(j, sc_dt::Log_0);
    ++j;
  }
  M_BfCollect(7, "sc_bv", w, "-sc");
}

template < int W >
inline void TypeConvert_v_sv_to_sc(sc_lv<W> &value, int w, unsigned int *a) {
  int j = 0;
  int c = 0;
  unsigned int v = 0;
  value = 0;
  for (int i = 0; i < w; ++i) {
    if ((i % 4) == 0) {
#if defined(sparc)
      v = 
	((a[c] & 0xff000000) >> 24) + 
	((a[c] & 0xff0000) >> 8) + 
	((a[c] & 0xff00) << 8) + 
	((a[c] & 0xff) << 24);
#else
      v = a[c];
#endif
      ++c;
    }
    unsigned int vm = v & 0x03;
    v >>= 8;
    switch(vm) {
    case 1: value.set_bit(j, sc_dt::Log_1); break;
    case 0: value.set_bit(j, sc_dt::Log_0); break;
    case 2: value.set_bit(j, sc_dt::Log_Z); break;
    default:
      value.set_bit(j, sc_dt::Log_X); break;
    }
    ++j;
  }
  M_BfCollect(7, "sc_lv", w, "-sc");
}

template < class T >
inline void TypeConvert_v_sv_to_sc(T &value, int w, unsigned int *a) {
  BfAssert2(7, "Not Supported");
}



class sc_hs2c_signal_base
{
 public:
  virtual void writeHS(unsigned int *val) = 0;
  virtual void attachLoad(void *, int, int) = 0;
};

template < class T >
class sc_hs2c_signal : public sc_signal<T>, public sc_hs2c_signal_base
{ 
 public:
  sc_hs2c_signal() : sc_signal<T>(), sc_hs2c_signal_base()
  {
    sc_snps::vcs_cbug_attach_object_info_for_signal(this);
  }
  void setW(int w, std::string id) { m_w = w; m_id = id; m_nState = 0; }
  void writeHS(unsigned int *val) {

    switch(m_nState) {
    case MHDL_INTEGER:            TypeConvert_v_ls_to_sc(m_value, m_w, val);    break;
    case MHDL_REAL:               TypeConvert_v_r_to_sc(m_value, m_w, val);    break;
    case MHDL_2STATE_SCALAR:      TypeConvert_v_2ss_to_sc(m_value, m_w, val);  break;
    case MHDL_LOGIC_SCALAR:       TypeConvert_v_ls_to_sc(m_value, m_w, val);   break;
    case MHDL_STRENGTH_SCALAR:    TypeConvert_v_ss_to_sc(m_value, m_w, val);   break;
    case MHDL_REAL_VECTOR:        TypeConvert_v_rv_to_sc(m_value, m_w, val);   break;
    case MHDL_2STATE_VECTOR:      TypeConvert_v_2sv_to_sc(m_value, m_w, val);  break;
    case MHDL_2STATE_WIDEVECTOR:  TypeConvert_v_2swv_to_sc(m_value, m_w, val); break;
    case MHDL_LOGIC_VECTOR:       
    case MHDL_LOGIC_WIDEVECTOR:   TypeConvert_v_lv_to_sc(m_value, m_w, val);  break;
    case MHDL_STRENGTH_VECTOR:    TypeConvert_v_sv_to_sc(m_value, m_w, val);   break;
    default:
      BfAssert2((m_nState * (-1)), "Not supported"); break;
    }

    sc_signal<T>::write(m_value);
  }
  void attachLoad(void *writeNode, int nState, int width) {
    m_nState = nState;
    m_writeNode = writeNode;
#ifdef SYSC_DEBUG
    bf_debug_info_opt_if(m_id.c_str(), this->name(), m_nState, m_w);
#endif
  }
  void end_of_elaboration();
 private:
  void *m_writeNode;
  int m_w;
  std::string m_id;
  int m_nState;
  char *m_str;
  T m_value;
};

extern void check_type_2c(const char *, const char *, int);

template <>
inline void sc_hs2c_signal<bool>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "bool", m_w);
}

template <>
inline void sc_hs2c_signal<char>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "char", m_w);
}

template <>
inline void sc_hs2c_signal<unsigned char>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "unsigned char", m_w);
}

template <>
inline void sc_hs2c_signal<short>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "short", m_w);
}

template <>
inline void sc_hs2c_signal<unsigned short>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "unsigned short", m_w);
}

template <>
inline void sc_hs2c_signal<int>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "int", m_w);
}

template <>
inline void sc_hs2c_signal<unsigned int>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "unsigned int", m_w);
}

template <>
inline void sc_hs2c_signal<long>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "long", m_w);
}

template <>
inline void sc_hs2c_signal<unsigned long>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "unsigned long", m_w);
}

template <>
inline void sc_hs2c_signal<sc_bit>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "sc_bit", m_w);
}

template <>
inline void sc_hs2c_signal<double>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "double", m_w);
}

template <>
inline void sc_hs2c_signal<sc_logic>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "sc_logic", m_w);
}

template <>
inline void sc_hs2c_signal<sc_int_base>::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "sc_int", m_w);
}

template <>
inline void sc_hs2c_signal<sc_uint_base >::end_of_elaboration() {
  check_type_2c(m_id.c_str(), "sc_uint", m_w);
}

inline void check_type_2c_T(sc_int_base &tmp, std::string id, int w) {
  check_type_2c(id.c_str(), "sc_int", w);
}

inline void check_type_2c_T(sc_uint_base &tmp, std::string id, int w) {
  check_type_2c(id.c_str(), "sc_uint", w);
}

inline void check_type_2c_T(sc_signed &tmp, std::string id, int w) {
  check_type_2c(id.c_str(), "sc_signed", w);
}

inline void check_type_2c_T(sc_unsigned &tmp, std::string id, int w) {
  check_type_2c(id.c_str(), "sc_unsigned", w);
}

inline void check_type_2c_T(sc_lv_base &tmp, std::string id, int w) {
  check_type_2c(id.c_str(), "sc_lv", w);
}

inline void check_type_2c_T(sc_bv_base &tmp, std::string id, int w) {
  check_type_2c(id.c_str(), "sc_bv", w);
}


template < class T > 
inline void sc_hs2c_signal<T>::end_of_elaboration() {
  T tmp;
  check_type_2c_T(tmp, m_id, m_w);
}



#endif
