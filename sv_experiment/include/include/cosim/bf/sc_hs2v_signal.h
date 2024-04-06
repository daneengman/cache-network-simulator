// ------------------------------------------------------------------
// SYNOPSYS CONFIDENTIAL                                             
//                                                                   
// This is an unpublished, proprietary work of Synopsys, Inc., and   
// is fully protected under copyright and trade secret laws. You may 
// not view, use, disclose, copy, or distribute this file or any     
// information contained herein except pursuant to a valid written   
// license from Synopsys.                                            
// ------------------------------------------------------------------

#ifndef _sc_hs2v_signal_h_
#define _sc_hs2v_signal_h_

#include "systemc.h"
#include "systemc_user.h"
#include "vcs_cbug_object_info.h"

template < int W >
inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const sc_lv<W> &val) {
  std::string std_value = val.to_string();
  int index = len +3;
  for (int i = 0; i < len; ++i) {
    u[i/4] <<= 8;
    if ((i % 4) == 0) index -= 8;
    if (index < 0) index = 0; else index++;
    switch(std_value[index]) {
    case '0': u[(i)/4] += 0; break; 
    case '1': u[(i)/4] += 1; break; 
    case 'Z': u[(i)/4] += 2; break; 
    case 'X': 
    default:  u[(i)/4] += 3; break; 
    }
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

template < int W >
inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const sc_bv<W> &val) {
  std::string std_value = val.to_string();
  int index = len +3;
  for (int i = 0; i < len; ++i) {
    u[i/4] <<= 8;
    if ((i % 4) == 0) index -= 8;
    if (index < 0) index = 0; else index++;
    switch(std_value[index]) {
    case '1': u[(i)/4] += 1; break; 
    case '0': 
    default:  u[(i)/4] += 0; break; 
    }
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

template < int W >
inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const sc_int<W> &val) {
  sc_int<W> mask = 1;
  sc_int<W> zero = 0;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { umask = 1; u[(i)/4] = 0; }
    if ((val & mask) != zero) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

template < int W >
inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const sc_uint<W> &val) {
  sc_uint<W> mask = 1;
  sc_uint<W> zero = 0;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { umask = 1; u[(i)/4] = 0; }
    if ((val & mask) != zero) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

template < int W >
inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const sc_bigint<W> &val) {
  sc_bigint<W> mask = 1;
  sc_bigint<W> zero = 0;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { umask = 1; u[(i)/4] = 0; }
    if ((val & mask) != zero) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

template < int W >
inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const sc_biguint<W> &val) {
  sc_biguint<W> mask = 1;
  sc_biguint<W> zero = 0;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { umask = 1; u[(i)/4] = 0; }
    if ((val & mask) != zero) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const bool &val) {
  if (val) u[0] = 1; else u[0] = 0;
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const sc_logic &val) {
  switch(val.value()) {
  case sc_dt::Log_0: u[0] = 0; break;
  case sc_dt::Log_1: u[0] = 1; break;
  case sc_dt::Log_Z: u[0] = 2; break;
  case sc_dt::Log_X:
  default: u[0] = 3; break;
  }
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const char &val) {
  int mask = 1;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { u[(i)/4] = 0; umask = 1; }
    if (val & mask) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const unsigned char &val) {
  int mask = 1;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { u[(i)/4] = 0; umask = 1; }
    if (val & mask) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const int &val) {
  int mask = 1;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { u[(i)/4] = 0; umask = 1; }
    if (val & mask) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const unsigned int &val) {
  unsigned int mask = 1;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { u[(i)/4] = 0; umask = 1; }
    if (val & mask) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const short int &val) {
  int mask = 1;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { u[(i)/4] = 0; umask = 1; }
    if (val & mask) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const unsigned short int &val) {
  unsigned int mask = 1;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0){ u[(i)/4] = 0; umask = 1; } 
    if (val & mask) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const long int &val) {
  int mask = 1;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { u[(i)/4] = 0; umask = 1; }
    if (val & mask) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const unsigned long int &val) {
  unsigned int mask = 1;
  int umask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 4)  == 0) { u[(i)/4] = 0; umask = 1; }
    if (val & mask) u[(i)/4] += umask;
    mask <<= 1;
    umask <<= 8;
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const double &val) {
    printf("FIXME:  TypeConvert_sc_to_v_exps(...., const double &val, file sc_hs2v_signal.h\n");
    *u = 0;
}
inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const sc_bit &val) {
  char std_value = val.to_char();
  if (std_value == '1') u[0] = 1; else u[0] = 0; 
}

template < typename T >
inline void TypeConvert_sc_to_v_exps(unsigned int *u, int len, const T &val) {
  std::string std_value = val.to_string(sc_dt::SC_BIN, false);
  int index = len +3;
  for (int i = 0; i < len; ++i) {
    u[i/4] <<= 8;
    if ((i % 4) == 0) index -= 8;
    if (index < 0) index = 0; else index++;
    switch(std_value[index]) {
    case '0': u[(i)/4] += 0; break; 
    case '1': u[(i)/4] += 1; break; 
    case 'Z': u[(i)/4] += 2; break; 
    case 'X': 
    default:  u[(i)/4] += 3; break; 
    }
  }
#if defined(sparc)
  for (int i = 0, j = 0; i <= len; i += 4, ++j) {
    unsigned int tmp;
    tmp = u[j];
    u[j] = 
      ((tmp & 0xff000000) >> 24) + 
      ((tmp & 0xff0000) >> 8) + 
      ((tmp & 0xff00) << 8) + 
      ((tmp & 0xff) << 24);
  }
#endif
}

template < int W >
inline void TypeConvert_sc_to_v_vec(unsigned int *u, int len, const sc_lv<W> &val) {
  int wcnt = -2;
  unsigned int bitmask = 1;
  for (int i = 0; i < len; ++i) {
    if ((i % 32)  == 0) { wcnt+= 2; bitmask = 1; u[wcnt] = 0; u[wcnt+1] = 0; }
    switch(val.get_bit(i)) {
    case sc_dt::Log_0: break;
    case sc_dt::Log_1: u[wcnt+1] |= bitmask; break;
    case sc_dt::Log_Z: u[wcnt] |= bitmask; break;
    case sc_dt::Log_X:
    default: u[wcnt] |= bitmask; u[wcnt+1] |= bitmask; break;
    }
    bitmask <<= 1;
  }
}

template < int W >
inline void TypeConvert_sc_to_v_vec(unsigned int *u, int len, const sc_bv<W> &val) {
    int wcnt = -2;
    unsigned int bitmask = 1;
    for (int i = 0; i < len; ++i) {
        if ((i % 32)  == 0) { wcnt+= 2; bitmask = 1; u[wcnt] = 0; u[wcnt+1] = 0; }
        if (val.get_bit(i) == sc_dt::Log_1) {
            u[wcnt+1] |= bitmask; 
        }
        bitmask <<= 1;
    }
}

template < int W >
inline void TypeConvert_sc_to_v_vec(unsigned int *u, int len, const sc_int<W> &val) {
    u[0] = 0;
    u[1] = val.to_uint();
    if (len>32) {
        u[2] = 0;
        u[3] = val.to_uint64() >>32;
    }
}

template < int W >
inline void TypeConvert_sc_to_v_vec(unsigned int *u, int len, const sc_uint<W> &val) {
  u[0] = 0;
  u[1] = val.to_uint();
  if (len>32) {
      u[2] = 0;
      u[3] = val.to_uint64() >>32;
  }
}

template < int W >
inline void TypeConvert_sc_to_v_vec(unsigned int *u, int len, const sc_bigint<W> &val) {
    if (len <= 32) {
        u[0] = 0;
        u[1] = val.to_uint();
    } else {
        int wcnt = -2;
        static sc_biguint<W> src;
        src = val;
        for (int i = 0; i < len; i+=32) {
            wcnt+= 2;
            u[wcnt] = 0;
            u[wcnt+1] = src.to_uint();
            src >>=32;
        }
    }
}

template < int W >
inline void TypeConvert_sc_to_v_vec(unsigned int *u, int len, const sc_biguint<W> &val) {
    if (len <= 32) {
        u[0] = 0;
        u[1] = val.to_uint();
    } else {
        int wcnt = -2;
        static sc_biguint<W> src;
        src = val;
        for (int i = 0; i < len; i+=32) {
            wcnt+= 2;
            u[wcnt] = 0;
            u[wcnt+1] = src.to_uint();
            src >>=32;
        }
    }
}

inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const sc_logic &val) {
  switch (val.value()) {
  case sc_dt::Log_0: u[0] = 0; u[1] = 0; break;
  case sc_dt::Log_1: u[0] = 0; u[1] = 1; break;
  case sc_dt::Log_Z: u[0] = 1; u[1] = 0; break;
  case sc_dt::Log_X:
  default: u[0] = 1; u[1] = 1; break;
  }
}

inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const bool &val) {
  if (val) u[1] = 1;
  else u[1] = 0;
  u[0] = 0;
}

inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const unsigned int &val) {
  u[1] = val;
  u[0] = 0;
}

inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const int &val) {
  u[1] = val;
  u[0] = 0;
}

inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const unsigned short &val) {
  u[1] = val;
  u[0] = 0;
}

inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const short &val) {
  u[1] = val;
  u[0] = 0;
}

inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const unsigned long &val) {
  u[1] = val;
  u[0] = 0;
}

inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const long &val) {
  u[1] = val;
  u[0] = 0;
}

inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const unsigned char &val) {
  u[1] = val;
  u[0] = 0;
}

inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const char &val) {
  u[1] = val;
  u[0] = 0;
}
inline void TypeConvert_sc_to_v_vec(unsigned int *u, int, const double &val) {
  printf("FIXME: TypeConvert_sc_to_v_vec(... const double &val in file sc_hs2v_signal.h\n");
}



template < typename T > 
void typeconv_sc_to_v( vec32 *t, int W, const T& value) 
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

inline void TypeConvert_sc_to_v(vec32 *&t, int, const sc_int<1> &value) {
  size_t ti = 0;
  if(value) {
    ti = 1;
  } else {
    ti = 0;
  }
  t = ( vec32 *)(ti);
}

inline void TypeConvert_sc_to_v(vec32 *&t, int, const sc_bigint<1> &value) {
  size_t ti = 0;
  if(value == (-1)) {
    ti = 1;
  } else {
    ti = 0;
  }
  t = ( vec32 *)(ti);
}

inline void TypeConvert_sc_to_v(vec32 *&t, int, const sc_uint<1> &value) {
  size_t ti = 0;
  if(value) {
    ti = 1;
  } else {
    ti = 0;
  }
  t = ( vec32 *)(ti);
}

inline void TypeConvert_sc_to_v(vec32 *&t, int, const sc_biguint<1> &value) {
  size_t ti = 0;
  if(value == 1) {
    ti = 1;
  } else {
    ti = 0;
  }
  t = ( vec32 *)(ti);
}

inline void TypeConvert_sc_to_v(vec32 *t, int W, const sc_int_base & value)
{
  int w = W;
  int i = 0;
  while (w > 32) {
    t[i].d = value(((i+1)*32)-1, i*32).to_int();
    t[i].c = 0;
    w -= 32;
    ++i;
  }
  t[i].d = value(W-1, i*32).to_int();
  t[i].c = 0;
}

inline void TypeConvert_sc_to_v(vec32 *t, int W, const sc_uint_base & value)
{
  int w = W;
  int i = 0;
  while (w > 32) {
    t[i].d = value(((i+1)*32)-1, i*32).to_uint();
    t[i].c = 0;
    w -= 32;
    ++i;
  }
  t[i].d = value(W-1, i*32).to_uint();
  t[i].c = 0;
}

inline void TypeConvert_sc_to_v(vec32 *t, int W, const sc_signed & value)
{
  unsigned int mw = 1;
  int i = 0;
  int wc = 0;
  t[wc].d = 0;
  t[wc].c = 0;
  while (i < W) {
    if (value[i] == 1)
      t[wc].d |= mw;
    mw <<= 1;
    ++i;
    if ((i % 32) == 0) {
      mw = 1;
      wc++;
      t[wc].d = 0;
      t[wc].c = 0;
    }
  }
}

inline void TypeConvert_sc_to_v(vec32 *t, int W, const sc_unsigned & value)
{
  unsigned int mw = 1;
  int i = 0;
  int wc = 0;
  t[wc].d = 0;
  t[wc].c = 0;
  while (i < W) {
    if (value[i] == 1)
      t[wc].d |= mw;
    mw <<= 1;
    ++i;
    if ((i % 32) == 0) {
      mw = 1;
      wc++;
      t[wc].d = 0;
      t[wc].c = 0;
    }
  }
}

inline void TypeConvert_sc_to_v(vec32 *&t, int, const sc_lv<1> &value) {
  size_t ti = 0;
  switch(value.get_bit(0)) {
  case sc_dt::Log_0: ti = 0; break;
  case sc_dt::Log_1: ti = 1; break;
  case sc_dt::Log_Z: ti = 2; break;
  case sc_dt::Log_X: 
  default: ti = 3; break;
  }
  t = (vec32 *)(ti);
}

inline void TypeConvert_sc_to_v(vec32 *&t, int, const sc_bv<1> &value) {
  size_t ti = 0;
  switch(value.get_bit(0)) {
  case sc_dt::Log_1: ti = 1; break;
  case sc_dt::Log_0: 
  default: ti = 0; break;
  }
  t = (vec32 *)(ti);
}

template < int W >
void TypeConvert_sc_to_v(vec32 *t, int, const sc_lv<W> &value) {
  const char *s_value;
  std::string str_value = value.to_string();
  s_value = str_value.c_str();
  //  int i = 0;
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
    case '1': t[0].d += 1; break;
    case 'X': t[0].d += 1; t[0].c += 1; break;
    case 'Z': t[0].c += 1; break;
    default:
      assert(0);
      break;;
    }
  }
}

template < int W >
void TypeConvert_sc_to_v(vec32 *t, int, const sc_bv<W> &value) {
  const char *s_value;
  std::string str_value = value.to_string();
  s_value = str_value.c_str();
  int i = 0;

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
    case '1': t[0].d += 1; break;
    case '0': 
    case 'Z': 
    case 'X': break;
    default:
      break;;
    }
  }
}

inline void TypeConvert_sc_to_v(vec32 *&t, int, const bool &value) {
  size_t ti = 0;
  if(value) {
    ti = 1;
  } else {
    ti = 0;
  }
  t = ( vec32 *)(ti);
}
inline void TypeConvert_sc_to_v(vec32 *t, int, const long &value) {
  t[0].c = 0;
  t[0].d = (int)value;
}
inline void TypeConvert_sc_to_v(vec32 *t, int, const unsigned long &value) {
  t[0].c = 0;
  t[0].d = (int)value;
}

inline void TypeConvert_sc_to_v(vec32 *t, int, const int &value) {
  t[0].c = 0;
  t[0].d = (int)value;
}
inline void TypeConvert_sc_to_v(vec32 *t, int, const unsigned int &value) {
  t[0].c = 0;
  t[0].d = (int)value;
}

inline void TypeConvert_sc_to_v(vec32 *t, int, const short &value) {
  t[0].c = 0;
  t[0].d = (int)value;
}
inline void TypeConvert_sc_to_v(vec32 *t, int, const unsigned short &value) {
  t[0].c = 0;
  t[0].d = (int)value;
}

inline void TypeConvert_sc_to_v(vec32 *t, int, const char &value) {
  t[0].c = 0;
  t[0].d = (int)value;
}
inline void TypeConvert_sc_to_v(vec32 *t, int, const unsigned char &value) {
  t[0].c = 0;
  t[0].d = (int)value;
}
inline void TypeConvert_sc_to_v(vec32 *t, int, const double &value) {
  printf("FIXME: TypeConvert_sc_to_v(.... const double &vale) in file sc_hs2v_signal.h\n");
}

inline void TypeConvert_sc_to_v(vec32 *&t, int, const sc_logic &value) {
  size_t ti = 0;
  switch(value.value()) {
  case sc_dt::Log_0: ti = 0; break;
  case sc_dt::Log_1: ti = 1; break;
  case sc_dt::Log_Z: ti = 2; break;
  case sc_dt::Log_X: ti = 3; break;
  default:
    break;
  }
  t = (vec32 *)(ti);
}

inline void TypeConvert_sc_to_v(vec32 *&t, int, const sc_bit &value) {
  size_t ti = 0;
  if(value.to_bool()) {
    ti = 1;
  } else {
    ti = 0;
  }
  t = ( vec32 *)(ti);
}

class sc_hs2v_signal_base
{
 public:
  virtual void attachDriver(void *, int (*)(void *, vec32 *, int), int, int, int) = 0;
  virtual void attachLoad(void *, int, int) = 0;
  int getCnt() { return m_cnt; }
 private:
  int m_cnt;
};

template < class T >
class sc_hs2v_signal : public sc_signal<T>, public sc_hs2v_signal_base
{
 public:
  sc_hs2v_signal() : m_rtn(0), m_nState(-1)
  {
    sc_snps::vcs_cbug_attach_object_info_for_signal(this);
  }
  void setW(int w, int words, std::string id) {   
    m_id = id;
    m_w = w;
    if (words > 0) m_t = new vec32[words]; 
    else m_t = &m_s;
    m_u = new unsigned int[w];
    for (int i = 0; i < w; ++i) m_u[i] = 0;
   
  }

  void attachDriver(void *writeNode, int (*fun)(void *, vec32 *, int), int nState, int w, int instNum) { 
    m_writeNode = writeNode;
    m_rtn = fun;
    m_nState = nState;
    m_instNum = instNum;
#ifdef SYSC_DEBUG
    bf_debug_info_opt_if(m_id.c_str(), this->name(), m_nState, m_w);
#endif
  }
  void attachLoad(void *writeNode, int nState, int width) {
    m_nState = nState;
    m_writeNode = writeNode;
#ifdef SYSC_DEBUG
    bf_debug_info_opt_if(m_id.c_str(), this->name(), m_nState, m_w);
#endif
  }
  void write(const T &val) {
      if (sc_snps::BfGuard(true, m_instNum) == 1) {
          // for DLP: not yet initialized
          return;
      }
    if (!m_rtn) { // connection is not established
      //      BfAssert("No Callback Function Registered");
      ;
    } else {
      switch(m_nState) {
      case MHDL_STRENGTH_VECTOR:
	TypeConvert_sc_to_v_exps(m_u, m_w, val);
	m_rtn(m_writeNode, (vec32 *)m_u, m_w);
	sc_signal<T>::write(val);
	break;
      case MHDL_LOGIC_VECTOR:
      case MHDL_LOGIC_WIDEVECTOR:
	TypeConvert_sc_to_v_vec(m_u, m_w, val);
	m_rtn(m_writeNode, (vec32 *)m_u, m_w);
	sc_signal<T>::write(val);
	break;
      default:
	TypeConvert_sc_to_v(m_t, m_w, val);
	if (m_rtn)
	  m_rtn(m_writeNode, m_t, m_w);
	sc_signal<T>::write(val);
	break;
      }
    }
    M_BfCollect(m_nState, "..", m_w, "->V");
    sc_snps::BfGuard(false, 0);
  }
  void end_of_elaboration();
 private:
  void *m_writeNode;
  int (*m_rtn)(void *, vec32 *, int);
  int m_w;
  int m_instNum;
  vec32 *m_t;
  unsigned int *m_u;
  vec32 m_s;
  int m_nState;
  std::string m_id;
};

extern void check_type_2v(const char *, const char *, int);

template <>
inline void sc_hs2v_signal<int>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "int", m_w);
}

template <>
inline void sc_hs2v_signal<unsigned int>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "unsigned int", m_w);
}

template <>
inline void sc_hs2v_signal<short>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "short", m_w);
}

template <>
inline void sc_hs2v_signal<unsigned short>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "unsigned short", m_w);
}

template <>
inline void sc_hs2v_signal<char>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "char", m_w);
}

template <>
inline void sc_hs2v_signal<unsigned char>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "unsigned char", m_w);
}

template <>
inline void sc_hs2v_signal<bool>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "bool", m_w);
}

template <>
inline void sc_hs2v_signal<long>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "long", m_w);
}

template <>
inline void sc_hs2v_signal<unsigned long>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "unsigned long", m_w);
}

template <>
inline void sc_hs2v_signal<double>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "double", m_w);
}

template <>
inline void sc_hs2v_signal<sc_bit>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "sc_bit", m_w);
}

template <>
inline void sc_hs2v_signal<sc_logic>::end_of_elaboration() {
  check_type_2v(m_id.c_str(), "sc_logic", m_w);
}

inline void check_type_2v_T(sc_int_base &tmp, std::string id, int w) {
  check_type_2v(id.c_str(), "sc_int", w);
}

inline void check_type_2v_T(sc_uint_base &tmp, std::string id, int w) {
  check_type_2v(id.c_str(), "sc_uint", w);
}

inline void check_type_2v_T(sc_signed &tmp, std::string id, int w) {
  check_type_2v(id.c_str(), "sc_signed", w);
}

inline void check_type_2v_T(sc_unsigned &tmp, std::string id, int w) {
  check_type_2v(id.c_str(), "sc_unsigned", w);
}

inline void check_type_2v_T(sc_lv_base &tmp, std::string id, int w) {
  check_type_2v(id.c_str(), "sc_lv", w);
}

inline void check_type_2v_T(sc_bv_base &tmp, std::string id, int w) {
  check_type_2v(id.c_str(), "sc_bv", w);
}

template <class T>
inline void sc_hs2v_signal<T>::end_of_elaboration() {
  T tmp;
  check_type_2v_T(tmp, m_id, m_w);
}



#endif
