/******************************************************************************
    Copyright (c) 2000-2012 Synopsys, Inc.    ALL RIGHTS RESERVED

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC(TM) Open Community License Software Download and
  Use License Version 1.1 (the "License"); you may not use this file except
  in compliance with such restrictions and limitations. You may obtain
  instructions on how to receive a copy of the License at
  http://www.systemc.org/. Software distributed by Original Contributor
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

******************************************************************************/

/******************************************************************************

    vcs_cbug_streaming.h -- Streaming functions for SystemC data types

    Original Author: Kola Djigande. Synopsys, Inc. (djigande@synopsys.com)

******************************************************************************/

/******************************************************************************

    MODIFICATION LOG - modifiers, enter your name, affliation and
    changes you are making here:

    Modifier Name & Affiliation:
    Description of Modification:


******************************************************************************/

#ifndef VCS_CBUG_STREAMING_H
#define VCS_CBUG_STREAMING_H


#ifndef __SUNPRO_CC
#define SNPS_USE_MEMBER_TEMPLATE 1
#else
#if ( __SUNPRO_CC >= 0x520 )
#define SNPS_USE_MEMBER_TEMPLATE 1
#endif
#endif

#define private public
#include "sysc/utils/sc_string.h"
#undef private
#include "sysc/utils/sc_iostream.h"
#include <string>
#include <assert.h>



namespace sc_dt
{
class sc_bit;
class sc_logic;
class sc_uint_base;
class sc_int_base;
class sc_int_subref;
class sc_uint_subref;
class sc_unsigned;
class sc_signed;
class sc_fxval;
class sc_fxval_fast;
class sc_fxnum;
class sc_fxnum_fast;
class scfx_rep;
}

#ifdef SC_INCLUDE_FX
#include "sysc/datatypes/fx/sc_fxdefs.h"
#include "sysc/datatypes/fx/sc_fxtype_params.h"

namespace sc_dt
{
class sc_fix;
class sc_fix_fast;
class sc_ufix;
class sc_ufix_fast;
template <int W, int I, sc_q_mode Q, sc_o_mode O, int N> class sc_fixed;
template <int W, int I, sc_q_mode Q, sc_o_mode O, int N> class sc_ufixed;
template <int W, int I, sc_q_mode Q, sc_o_mode O, int N> class sc_fixed_fast;
template <int W, int I, sc_q_mode Q, sc_o_mode O, int N> class sc_ufixed_fast;
}

#endif   // #ifdef SC_INCLUDE_FX


namespace sc_dt
{
template<int W> class sc_int;
template<int W> class sc_uint;
template<int W> class sc_bigint;
template<int W> class sc_biguint;

  class sc_bv_base;
  class sc_lv_base;
  template<int w> class sc_bv;
  template<int w> class sc_lv;
}

namespace sc_core {
template<class T> class sc_in;
template<class T> class sc_inout;
template<class T> class sc_out;
} // namespace sc_core


namespace sc_snps {

#define VCS_CBUG_UNSUPPORTED "unsupported"

class vcs_cbug_object_info;

// parameter handling

class vcs_cbug_param_setting_base
{
  public:
    vcs_cbug_param_setting_base() {}
    virtual ~vcs_cbug_param_setting_base() {}

    std::string name_;
};

template<class T> class vcs_cbug_param_setting : public vcs_cbug_param_setting_base
{
  public:
    vcs_cbug_param_setting(const char *param_name, const T& param_value);
    ~vcs_cbug_param_setting();

    T value_;
};

template<class T>
inline
vcs_cbug_param_setting<T>::vcs_cbug_param_setting(const char *param_name, const T& param_value)
    : vcs_cbug_param_setting_base()
{
    name_ = param_name;
    value_ = param_value;
}

template<class T>
inline
vcs_cbug_param_setting<T>::~vcs_cbug_param_setting()
{
}


//////////////////////////////////////////////////////////////////////////


class vcs_cbug_stream_helper
{
public:

#define VCS_CBUG_SHOW(type,name) \
  static bool vcs_cbug_set_value_##name(type& value, const char *string_value); \
  static const char *vcs_cbug_show_value_##name(const type& value); \
  static const char *show_value_slice_##name(const type& value, char radix, int highRange, int lowRange, int maxRange); \
  static const char *gdb_show_value_##name(const type&, char radix, int highRange, int lowRange); \
  static const char *gdb_show_inp_##name(const sc_core::sc_in<type>&, char radix, int highRange, int lowRange); \
  static const char *gdb_show_iop_##name(const sc_core::sc_inout<type>&, char radix, int highRange, int lowRange); \
  static const char *gdb_show_outp_##name(const sc_core::sc_out<type>&, char radix, int highRange, int lowRange)

  VCS_CBUG_SHOW(sc_dt::sc_string_old, sc_string);
  VCS_CBUG_SHOW(std::string, string);
  VCS_CBUG_SHOW(sc_dt::sc_bit, sc_bit);
  VCS_CBUG_SHOW(sc_dt::sc_logic, sc_logic);
  VCS_CBUG_SHOW(sc_dt::sc_uint_base, sc_uint_base);
  VCS_CBUG_SHOW(sc_dt::sc_int_base, sc_int_base);
  VCS_CBUG_SHOW(sc_dt::sc_unsigned, sc_unsigned);
  VCS_CBUG_SHOW(sc_dt::sc_signed, sc_signed);
  VCS_CBUG_SHOW(sc_dt::sc_unsigned, sc_biguint);
  VCS_CBUG_SHOW(sc_dt::sc_signed, sc_bigint);
  VCS_CBUG_SHOW(sc_dt::sc_bv_base, sc_bv_base);
  VCS_CBUG_SHOW(sc_dt::sc_lv_base, sc_lv_base);
#ifdef SC_INCLUDE_FX
  VCS_CBUG_SHOW(sc_dt::sc_fix, sc_fixed);
  VCS_CBUG_SHOW(sc_dt::sc_fix_fast, sc_fixed_fast);
  VCS_CBUG_SHOW(sc_dt::sc_ufix, sc_ufixed);
  VCS_CBUG_SHOW(sc_dt::sc_ufix_fast, sc_ufixed_fast);
  VCS_CBUG_SHOW(sc_dt::sc_fix, sc_fix);
  VCS_CBUG_SHOW(sc_dt::sc_fix_fast, sc_fix_fast);
  VCS_CBUG_SHOW(sc_dt::sc_ufix, sc_ufix);
  VCS_CBUG_SHOW(sc_dt::sc_ufix_fast, sc_ufix_fast);
  VCS_CBUG_SHOW(sc_dt::sc_fxval, sc_fxval);
  VCS_CBUG_SHOW(sc_dt::sc_fxval_fast, sc_fxval_fast);
  VCS_CBUG_SHOW(sc_dt::sc_fxnum, sc_fxnum);
  VCS_CBUG_SHOW(sc_dt::sc_fxnum_fast, sc_fxnum_fast);
#endif // SC_INCLUDE_FX
  VCS_CBUG_SHOW(bool, bool);
  VCS_CBUG_SHOW(char, char);
  VCS_CBUG_SHOW(signed char, s_char);
  VCS_CBUG_SHOW(unsigned char, u_char);
  VCS_CBUG_SHOW(short int, short);
  VCS_CBUG_SHOW(short unsigned int, ushort);
  VCS_CBUG_SHOW(int, int);
  VCS_CBUG_SHOW(unsigned int, uint);
  VCS_CBUG_SHOW(long int, long);
  VCS_CBUG_SHOW(long unsigned int, ulong);
  VCS_CBUG_SHOW(long long, longlong);
  VCS_CBUG_SHOW(unsigned long long, ulonglong);
  VCS_CBUG_SHOW(sc_dt::int64, int64);
  VCS_CBUG_SHOW(sc_dt::uint64, uint64);
  VCS_CBUG_SHOW(float, float);
  VCS_CBUG_SHOW(double, double);
  VCS_CBUG_SHOW(long double, long_double);
  VCS_CBUG_SHOW(void*, pointer);
#undef VCS_CBUG_SHOW

    template <class T>
    inline static bool validate_value(const T&) { return true; }
    template <int W>
    inline static bool validate_value(const sc_dt::sc_lv<W>& value) { return validate_sc_vector_base((const sc_dt::sc_lv_base&)value); }
    template <int W>
    inline static bool validate_value(const sc_dt::sc_bv<W>& value) { return validate_sc_vector_base((const sc_dt::sc_bv_base&)value); }
    template <int W>
    inline static bool validate_value(const sc_dt::sc_int<W>& value) { return validate_sc_Xint_base((const sc_dt::sc_int_base&)value); }
    template <int W>
    inline static bool validate_value(const sc_dt::sc_uint<W>& value) { return validate_sc_Xint_base((const sc_dt::sc_uint_base&)value); }
    template <int W>
    inline static bool validate_value(const sc_dt::sc_bigint<W>& value) { return validate_sc_Xsigned((const sc_dt::sc_signed&)value); }
    template <int W>
    inline static bool validate_value(const sc_dt::sc_biguint<W>& value) { return validate_sc_Xsigned((const sc_dt::sc_unsigned&)value); }

    inline static bool validate_value(const sc_dt::sc_string_old& value) { return validate_sc_old_string(value); }
    inline static bool validate_value(const std::string& value) { return value.data() && validate_string(value); }
    inline static bool validate_value(const sc_dt::sc_fxnum_fast& value) { return validate_sc_fxnum_fast(value); }
    inline static bool validate_value(const sc_dt::sc_fxnum& value) { return validate_sc_fxnum(value); }
    inline static bool validate_value(const sc_dt::sc_lv_base& value) { return validate_sc_vector_base(value); }
    inline static bool validate_value(const sc_dt::sc_bv_base& value) { return validate_sc_vector_base(value); }
    inline static bool validate_value(const sc_dt::sc_int_base& value) { return validate_sc_Xint_base(value); }
    inline static bool validate_value(const sc_dt::sc_uint_base& value) { return validate_sc_Xint_base(value); }
    inline static bool validate_value(const sc_dt::sc_signed& value) { return validate_sc_Xsigned(value); }
    inline static bool validate_value(const sc_dt::sc_unsigned& value) { return validate_sc_Xsigned(value); }

protected:
    static bool validate_pointer(const void *p, size_t range = 0);
    template <class T> // sc_lv, sc_bv
    static bool validate_sc_vector_base(const T& value);
    static bool validate_sc_old_string(const sc_dt::sc_string_old& value);
    static bool validate_sc_string(const sc_dt::sc_string_old& value);
    static bool validate_string(const std::string& value);
    static bool validate_scfx_rep(const sc_dt::scfx_rep* pRep);
    static bool validate_sc_fxnum_fast(const sc_dt::sc_fxnum_fast& value);
    static bool validate_sc_fxnum(const sc_dt::sc_fxnum& value);
    template <class T> // sc_int_base, sc_uint_base
    static bool validate_sc_Xint_base(const T& value);
    template <class T> // sc_unsigned, sc_signed
    static bool validate_sc_Xsigned(const T& value);

// public:
    static void adjust_boundaries(int nBits, int* pHighRange, int* pLowRange, int maxRange, bool* pIsTooLong, bool* pHasRange, bool* pIsReversedRange);
    static void print_radix(std::string& s, char radix, int nBits, bool isTooLong);
    static sc_dt::sc_numrep radix_to_sc_numrep(char radix);
    static bool set_no_pointer_validation(bool f);

    template <class T>
    static const char *show_value_slice_int_template(T value, char radix, int highRange, int lowRange, int maxRange);
    template <class T>
    static const char *show_value_slice_template(T value, char radix, int length, int highRange, int lowRange, int maxRange);

protected:
    static size_t  page_size;
    static void *lower_heap_limit;
// public:
    static bool no_pointer_validation;
};

// moved to end of file: gcc4
// backward compatibility function:
template <class T> inline
bool vcs_cbug_get_stream_value(const T& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype) 
{
    if (errmsg)
        *errmsg = VCS_CBUG_UNSUPPORTED;
    return false;
}

template <class T> inline
bool vcs_cbug_set_value(T& value, const char *string_value)
{
    return false;
}

template <class T> inline
const char *vcs_cbug_show_value(const T& value)
{
    return VCS_CBUG_UNSUPPORTED;
}
template <class T> inline
const char *vcs_cbug_show_value_slice(const T& value, char radix, int highRange, int lowRange, int maxRange)
{
    return VCS_CBUG_UNSUPPORTED;
}

bool vcs_cbug_get_stream_value_pointer(const void* value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <class T> inline
bool vcs_cbug_set_value(T*& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_pointer((void*&)value, string_value);
}

template <class T> inline
bool vcs_cbug_get_stream_value(T* value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_pointer((const void*)value, ppVpd_data, errmsg, datatype);
}

template <class T> inline
const char *vcs_cbug_show_value(T* value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_pointer((const void*&)value);
}
template <class T> inline
const char *vcs_cbug_show_value_slice(T* value, char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_pointer((const void*&)value, radix, highRange, lowRange, maxRange);
}

#define VCS_CBUG_SHOW_IMPL(type,name) \
  template <> inline const char *vcs_cbug_show_value(const type& value) \
  { return vcs_cbug_stream_helper::vcs_cbug_show_value_##name(value); } \
  template <> inline const char *vcs_cbug_show_value_slice(const type& value, char radix, int highRange, int lowRange, int maxRange) \
  { return vcs_cbug_stream_helper::show_value_slice_##name(value, radix, highRange, lowRange, maxRange); } \


  VCS_CBUG_SHOW_IMPL(sc_dt::sc_string_old, sc_string)
  VCS_CBUG_SHOW_IMPL(std::string, string)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_bit, sc_bit)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_logic, sc_logic)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_uint_base, sc_uint_base)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_int_base, sc_int_base)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_unsigned, sc_unsigned)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_signed, sc_signed)
  // VCS_CBUG_SHOW_IMPL(sc_unsigned, sc_biguint)
  // VCS_CBUG_SHOW_IMPL(sc_signed, sc_bigint)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_bv_base, sc_bv_base)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_lv_base, sc_lv_base)
#ifdef SC_INCLUDE_FX
  // VCS_CBUG_SHOW_IMPL(sc_fix, sc_fixed)
  // VCS_CBUG_SHOW_IMPL(sc_fix_fast, sc_fixed_fast)
  // VCS_CBUG_SHOW_IMPL(sc_ufix, sc_ufixed)
  // VCS_CBUG_SHOW_IMPL(sc_ufix_fast, sc_ufixed_fast)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_fix, sc_fix)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_fix_fast, sc_fix_fast)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_ufix, sc_ufix)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_ufix_fast, sc_ufix_fast)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_fxval, sc_fxval)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_fxval_fast, sc_fxval_fast)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_fxnum, sc_fxnum)
  VCS_CBUG_SHOW_IMPL(sc_dt::sc_fxnum_fast, sc_fxnum_fast)
#endif // SC_INCLUDE_FX
  VCS_CBUG_SHOW_IMPL(bool, bool)
  VCS_CBUG_SHOW_IMPL(char, char)
  VCS_CBUG_SHOW_IMPL(signed char, s_char)
  VCS_CBUG_SHOW_IMPL(unsigned char, u_char)
  VCS_CBUG_SHOW_IMPL(short int, short)
  VCS_CBUG_SHOW_IMPL(short unsigned int, ushort)
  VCS_CBUG_SHOW_IMPL(int, int)
  VCS_CBUG_SHOW_IMPL(unsigned int, uint)
  VCS_CBUG_SHOW_IMPL(long int, long)
  VCS_CBUG_SHOW_IMPL(long unsigned int, ulong)
  //  VCS_CBUG_SHOW_IMPL(long long, longlong)            same as (sc_dt::int64, int64)
  //  VCS_CBUG_SHOW_IMPL(unsigned long long, ulonglong)  same as (sc_dt::uint64, uint64)
  VCS_CBUG_SHOW_IMPL(sc_dt::int64, int64)
  VCS_CBUG_SHOW_IMPL(sc_dt::uint64, uint64)
  VCS_CBUG_SHOW_IMPL(float, float)
  VCS_CBUG_SHOW_IMPL(double, double)
  VCS_CBUG_SHOW_IMPL(long double, long_double)
#undef VCS_CBUG_SHOW_IMPL

// std::string
bool vcs_cbug_get_stream_value_string(const std::string& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_get_stream_value(const std::string& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_string(value, ppVpd_data, errmsg, datatype);
}
template <> inline
bool vcs_cbug_set_value(std::string& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_string(value, string_value);
}

// sc_string
bool vcs_cbug_get_stream_value_sc_string(const sc_dt::sc_string_old& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_string_old& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_string(value, string_value);
}


template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_string_old& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_string(value, ppVpd_data, errmsg, datatype);
}

// sc_bit
bool vcs_cbug_get_stream_value_sc_bit(const sc_dt::sc_bit& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_bit& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_bit(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_bit& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_bit(value, ppVpd_data, errmsg, datatype);
}
bool vcs_cbug_get_stream_value_sc_logic(const sc_dt::sc_logic& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_logic& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_logic(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_logic& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_logic(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_sc_uint_base(const sc_dt::sc_uint_base& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_uint_base& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_uint_base(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_uint_base& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_uint_base(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_sc_int_base(const sc_dt::sc_int_base& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_int_base& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_int_base(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_int_base& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_int_base(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_sc_unsigned(const sc_dt::sc_unsigned& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_unsigned& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_unsigned(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_unsigned& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_unsigned(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_sc_signed(const sc_dt::sc_signed& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_signed& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_signed(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_signed& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_signed(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_sc_bv_base(const sc_dt::sc_bv_base& value, 
        void **ppVpd_data, std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_bv_base& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_bv_base(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_bv_base& value,
        void **ppVpd_data, std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_bv_base(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_sc_lv_base(const sc_dt::sc_lv_base& value, 
        void **ppVpd_data, std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_lv_base& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_lv_base(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_lv_base& value, 
        void **ppVpd_data, std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_lv_base(value, ppVpd_data, errmsg, datatype);
}

#if !defined(SC_STREAMOP_EXTENSIONS) && !defined(CCSS_PARAM_DEFS_H)
#define SC_STREAMOP_EXTENSIONS 1
std::ostream& operator<< (std::ostream&, const sc_dt::sc_bv_base&);
std::istream& operator>> (std::istream&, sc_dt::sc_bv_base&);
std::ostream& operator<<(std::ostream&, const sc_dt::sc_lv_base&);
std::istream& operator>>(std::istream&, sc_dt::sc_lv_base&);
#endif



#ifdef SC_INCLUDE_FX

bool vcs_cbug_get_stream_value_sc_fxval(const sc_dt::sc_fxval& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_fxval& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_fxval(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_fxval& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_fxval(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_sc_fxval_fast(const sc_dt::sc_fxval_fast& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_fxval_fast& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_fxval_fast(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_fxval_fast& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_fxval_fast(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_sc_fxnum(const sc_dt::sc_fxnum & value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_fxnum& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_fxnum(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_fxnum & value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_fxnum(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_sc_fxnum_fast(const sc_dt::sc_fxnum_fast& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_fxnum_fast& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_fxnum_fast(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_fxnum_fast& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_fxnum_fast(value, ppVpd_data, errmsg, datatype);
}

// sc_fix
bool vcs_cbug_get_stream_value_sc_fix(const sc_dt::sc_fix& value,  void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_fix& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_fix(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_fix& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_fix(value, ppVpd_data, errmsg, datatype);
}

// sc_fix_fast
bool vcs_cbug_get_stream_value_sc_fix_fast(const sc_dt::sc_fix_fast& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_fix_fast& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_fix_fast(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_fix_fast& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_fix_fast(value, ppVpd_data, errmsg, datatype);
}

// sc_ufix
bool vcs_cbug_get_stream_value_sc_ufix(const sc_dt::sc_ufix& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_ufix& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_ufix(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_ufix& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_ufix(value, ppVpd_data, errmsg, datatype);
}

// sc_ufix_fast
bool vcs_cbug_get_stream_value_sc_ufix_fast(const sc_dt::sc_ufix_fast& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(sc_dt::sc_ufix_fast& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_ufix_fast(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_ufix_fast& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_ufix_fast(value, ppVpd_data, errmsg, datatype);
}

#ifdef SNPS_USE_MEMBER_TEMPLATE
// sc_fixed
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
bool vcs_cbug_set_value(sc_dt::sc_fixed<W, I, Q, O, N>& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_fix(value, string_value);
}
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
const char *vcs_cbug_show_value(const sc_dt::sc_fixed<W, I, Q, O, N>& value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_sc_fix(value);
}
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
const char *vcs_cbug_show_value_slice(const sc_dt::sc_fixed<W, I, Q, O, N>& value,
        char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_sc_fix(value, radix, highRange, lowRange, maxRange);
}

template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_fixed<W, I, Q, O, N>& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_fix(value, ppVpd_data, errmsg, datatype);
}


// sc_fixed_fast
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
bool vcs_cbug_set_value(sc_dt::sc_fixed_fast<W, I, Q, O, N>& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_fix_fast(value, string_value);
}
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
const char *vcs_cbug_show_value(const sc_dt::sc_fixed_fast<W, I, Q, O, N>& value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_sc_fix_fast(value);
}
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
const char *vcs_cbug_show_value_slice(const sc_dt::sc_fixed_fast<W, I, Q, O, N>& value,
        char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_sc_fix_fast(value, radix, highRange, lowRange, maxRange);
}

template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_fixed_fast<W, I, Q, O, N>& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_fix_fast(value, ppVpd_data, errmsg, datatype);
}


// sc_ufixed
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
bool vcs_cbug_set_value(sc_dt::sc_ufixed<W, I, Q, O, N>& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_ufix(value, string_value);
}
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
const char *vcs_cbug_show_value(const sc_dt::sc_ufixed<W, I, Q, O, N>& value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_sc_ufix(value);
}
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
const char *vcs_cbug_show_value_slice(const sc_dt::sc_ufixed<W, I, Q, O, N>& value,
        char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_sc_ufix(value, radix, highRange, lowRange, maxRange);
}

template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_ufixed<W, I, Q, O, N>& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_ufix(value, ppVpd_data, errmsg, datatype);
}


// sc_ufixed_fast
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
bool vcs_cbug_set_value(sc_dt::sc_ufixed_fast<W, I, Q, O, N>& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_ufix_fast(value, string_value);
}
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
const char *vcs_cbug_show_value(const sc_dt::sc_ufixed_fast<W, I, Q, O, N>& value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_sc_ufix_fast(value);
}
template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
const char *vcs_cbug_show_value_slice(const sc_dt::sc_ufixed_fast<W, I, Q, O, N>& value,
        char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_sc_ufix_fast(value, radix, highRange, lowRange, maxRange);
}

template <int W, int I, sc_dt::sc_q_mode Q, sc_dt::sc_o_mode O, int N> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_ufixed_fast<W, I, Q, O, N>& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_ufix_fast(value, ppVpd_data, errmsg, datatype);
}

#endif

#endif

bool vcs_cbug_get_stream_value_bool(const bool& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(bool& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_bool(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const bool& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_bool(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_ushort(const unsigned short& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(unsigned short& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_ushort(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const unsigned short& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_ushort(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_uint(const unsigned int& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(unsigned int& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_uint(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const unsigned int& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_uint(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_ulong(const unsigned long& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(unsigned long& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_ulong(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const unsigned long& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_ulong(value, ppVpd_data, errmsg, datatype);
}


bool vcs_cbug_get_stream_value_ulonglong(const unsigned long long& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);

template <> inline
bool vcs_cbug_set_value(sc_dt::uint64& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_uint64(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::uint64& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_ulonglong((unsigned long long)value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_short(const short& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(short& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_short(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const short& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_short(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_int(const int& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(int& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_int(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const int& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_int(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_long(const long& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(long& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_long(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const long& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_long(value, ppVpd_data, errmsg, datatype);
}


bool vcs_cbug_get_stream_value_longlong(const long long& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);

template <> inline
bool vcs_cbug_set_value(sc_dt::int64& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_int64(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const sc_dt::int64& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    // FIXME rename either longlong to int64 or vice versa
    return vcs_cbug_get_stream_value_longlong((long long)value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_float(const float& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(float& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_float(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const float& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_float(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_double(const double& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(double& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_double(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const double& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_double(value, ppVpd_data, errmsg, datatype);
}


bool vcs_cbug_get_stream_value_long_double(const long double& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(long double& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_long_double(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const long double& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_long_double(value, ppVpd_data, errmsg, datatype);
}


bool vcs_cbug_get_stream_value_u_char(const unsigned char& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(unsigned char& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_u_char(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const unsigned char& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_u_char(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_s_char(const signed char& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(signed char& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_s_char(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const signed char& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_s_char(value, ppVpd_data, errmsg, datatype);
}

bool vcs_cbug_get_stream_value_char(const char& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype);
template <> inline
bool vcs_cbug_set_value(char& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_char(value, string_value);
}

template <> inline
bool vcs_cbug_get_stream_value(const char& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_char(value, ppVpd_data, errmsg, datatype);
}


#ifdef SNPS_USE_MEMBER_TEMPLATE
template <int W> inline
bool vcs_cbug_set_value(sc_dt::sc_uint<W>& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_uint_base(value, string_value);
}
template <int W> inline
const char *vcs_cbug_show_value(const sc_dt::sc_uint<W>& value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_sc_uint_base(value);
}
template <int W> inline
const char *vcs_cbug_show_value_slice(const sc_dt::sc_uint<W>& value,
        char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_sc_uint_base(value, radix, highRange, lowRange, maxRange);
}

template <int W> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_uint<W>& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_uint_base(value, ppVpd_data, errmsg, datatype);
}

template <int W> inline
bool vcs_cbug_set_value(sc_dt::sc_int<W>& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_int_base(value, string_value);
}
template <int W> inline
const char *vcs_cbug_show_value(const sc_dt::sc_int<W>& value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_sc_int_base(value);
}
template <int W> inline
const char *vcs_cbug_show_value_slice(const sc_dt::sc_int<W>& value,
        char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_sc_int_base(value, radix, highRange, lowRange, maxRange);
}

template <int W> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_int<W>& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_int_base(value, ppVpd_data, errmsg, datatype);
}

template <int W> inline
bool vcs_cbug_set_value(sc_dt::sc_biguint<W>& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_unsigned(value, string_value);
}
template <int W> inline
const char *vcs_cbug_show_value(const sc_dt::sc_biguint<W>& value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_sc_unsigned(value);
}
template <int W> inline
const char *vcs_cbug_show_value_slice(const sc_dt::sc_biguint<W>& value,
        char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_sc_unsigned(value, radix, highRange, lowRange, maxRange);
}

template <int W> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_biguint<W>& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_unsigned(value, ppVpd_data, errmsg, datatype);
}


template <int W> inline
bool vcs_cbug_set_value(sc_dt::sc_bigint<W>& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_signed(value, string_value);
}
template <int W> inline
const char *vcs_cbug_show_value(const sc_dt::sc_bigint<W>& value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_sc_signed(value);
}
template <int W> inline
const char *vcs_cbug_show_value_slice(const sc_dt::sc_bigint<W>& value,
        char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_sc_signed(value, radix, highRange, lowRange, maxRange);
}

template <int W> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_bigint<W>& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_signed(value, ppVpd_data, errmsg, datatype);
}

template <int w> inline
bool vcs_cbug_set_value(sc_dt::sc_bv<w>& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_bv_base(value, string_value);
}
template <int w> inline
const char *vcs_cbug_show_value(const sc_dt::sc_bv<w>& value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_sc_bv_base(value);
}
template <int w> inline
const char *vcs_cbug_show_value_slice(const sc_dt::sc_bv<w>& value,
        char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_sc_bv_base(value, radix, highRange, lowRange, maxRange);
}

template <int w> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_bv<w>& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_bv_base(value, ppVpd_data, errmsg, datatype);
}


template <int w> inline
bool vcs_cbug_set_value(sc_dt::sc_lv<w>& value, const char *string_value)
{
    return vcs_cbug_stream_helper::vcs_cbug_set_value_sc_lv_base(value, string_value);
}
template <int w> inline
const char *vcs_cbug_show_value(const sc_dt::sc_lv<w>& value)
{
    return vcs_cbug_stream_helper::vcs_cbug_show_value_sc_lv_base(value);
}
template <int w> inline
const char *vcs_cbug_show_value_slice(const sc_dt::sc_lv<w>& value,
        char radix, int highRange, int lowRange, int maxRange)
{
    return vcs_cbug_stream_helper::show_value_slice_sc_lv_base(value, radix, highRange, lowRange, maxRange);
}

template <int w> inline
bool vcs_cbug_get_stream_value(const sc_dt::sc_lv<w>& value, void **ppVpd_data,
                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value_sc_lv_base(value, ppVpd_data, errmsg, datatype);
}


#endif

template <class T> inline
bool vcs_cbug_get_stream_datatype(const T& value, 
                                        std::string *errmsg, std::string *datatype)
{
    return vcs_cbug_get_stream_value(value, (void**)0, errmsg, datatype);
}


// base class for all kinds of objects to stream
class vcs_cbug_stream_object_base {
  public:
     enum { STREAM_BUF_SIZE = 8192 };
     vcs_cbug_stream_object_base(const char *objectname,
             void *hObject,
             const char *datatype);
     virtual ~vcs_cbug_stream_object_base();

     virtual void cycle(bool /*force_streaming*/) {;}

     virtual bool is_equiv(vcs_cbug_stream_object_base* obj);

     virtual void close();

     void set_streaming_mode(bool flag);
     bool isOn();
  private:
     std::string object_name;
  protected:
     void *hVPD_Object;
     std::string data_type;
};

void stream_data(void *hVPD_Object, const char *type_info, void *vpd_data);
// 
// backward compatibility function to keep regressions alive
//
inline void stream_data(const char *type_info, void *vpd_data)
{
    stream_data(0, type_info, vpd_data);
}


template< class T >
class vcs_cbug_stream_object : public vcs_cbug_stream_object_base {
  public:
       // create a stream object
     static vcs_cbug_stream_object_base *create(const char *objectname,
             void *hObject,
             T *object_to_stream, const char *datatype);

       // stream a cycle
     virtual void cycle(bool force_streaming);

  protected:
       // c'tor
     vcs_cbug_stream_object(const char *objectname,
                      void *hObject,
                      T *object_to_stream, const char *datatype);

       // d'tor
     ~vcs_cbug_stream_object();

  private:
     T* value;
     bool first_time;  // are we streaming the first value
     T old_value;
};


template< class T >
inline
vcs_cbug_stream_object<T>::vcs_cbug_stream_object(const char *objectname,
                 void *hObject,
               T *object_to_stream, const char *datatype)
    : vcs_cbug_stream_object_base(objectname, hObject, datatype)
    , value(object_to_stream), first_time(true), old_value(*value)
{
    assert(object_to_stream);  // should never be null since it is from &curr_value.
}

template< class T >
inline
vcs_cbug_stream_object<T>::~vcs_cbug_stream_object()
{
}

template< class T >
inline
void
vcs_cbug_stream_object<T>::cycle(bool force_streaming)
{
    if (!isOn())
        return;
    if (!vcs_cbug_stream_helper::validate_value(*value))
        return;
    assert(sizeof(old_value) == sizeof(*value));
    if (first_time || force_streaming || !(old_value == *value) ) {
        void *vpd_data = 0;
        // third parameter was set to &, reverted to 0
        vcs_cbug_get_stream_value(*value, &vpd_data,
                (std::string *)0, (std::string *)0);
        stream_data(hVPD_Object, data_type.c_str(), vpd_data);
        old_value = *value;
        first_time = false;
    }
}

template< class T >
inline
vcs_cbug_stream_object_base *
vcs_cbug_stream_object<T>::create(const char *objectname,
                void *hObject,
                T *object_to_stream, const char *datatype)
{
    return new vcs_cbug_stream_object<T>(objectname,
            hObject,
            object_to_stream, datatype);
}


// base objects need the copy constructor of the old_value called to
// configure the object.
template< class T >
class vcs_cbug_stream_configured_object : public vcs_cbug_stream_object_base {
  public:
       // create a stream object
     static vcs_cbug_stream_object_base* create(const char *objectname,
             void *hObject,
             T *object_to_stream, const char *datatype);

       // stream a cycle
     virtual void cycle(bool force_streaming);

  protected:
       // c'tor
     vcs_cbug_stream_configured_object(const char *objectname,
                      void *hObject,
                      T *object_to_stream, const char *datatype);

       // d'tor
     ~vcs_cbug_stream_configured_object();

  private:
     T* value;
     bool first_time;  // are we streaming the first value
     T old_value;
};


template< class T >
inline
vcs_cbug_stream_configured_object<T>::vcs_cbug_stream_configured_object(const char *objectname,
                 void *hObject,
               T *object_to_stream, const char *datatype)
    : vcs_cbug_stream_object_base(objectname, hObject, datatype)
    , value(object_to_stream), first_time(true)
    , old_value(*object_to_stream)
{
    assert(object_to_stream);  // should never be null since it is from &curr_value.
}

template< class T >
inline
vcs_cbug_stream_configured_object<T>::~vcs_cbug_stream_configured_object()
{
}

template< class T >
inline
void
vcs_cbug_stream_configured_object<T>::cycle(bool force_streaming)
{
    if (!isOn())
        return;
    if (!vcs_cbug_stream_helper::validate_value(*value))
        return;
    assert(sizeof(old_value) == sizeof(*value));
    if (first_time || force_streaming || !(old_value == *value) ) {
        void *vpd_data = 0;
        // third parameter was set to &, reverted to 0
        vcs_cbug_get_stream_value(*value, &vpd_data,
                (std::string *)0, (std::string *)0);
        stream_data(hVPD_Object, data_type.c_str(), vpd_data);
        old_value = *value;
        first_time = false;
    }
}

template< class T >
inline
vcs_cbug_stream_object_base *
vcs_cbug_stream_configured_object<T>::create(const char *objectname,
                void *hObject,
                T *object_to_stream, const char *datatype)
{
    return new vcs_cbug_stream_configured_object<T>(objectname,
            hObject,
            object_to_stream, datatype);
}



// specialization for fifo objects
template< class T >
class vcs_cbug_stream_object_guarded : public vcs_cbug_stream_object<T> {
  public:

     static vcs_cbug_stream_object_base *create
                (const char *objectname,
		 void *hObject,
		 T *object_to_stream, 
		 vcs_cbug_object_info* obj_info,
		 int *counter_indicating_object_has_changed,
		 bool dump_all_updates,
		 const char *datatype);

       // stream a cycle
     virtual void cycle(bool force_streaming);

  protected:
       // c'tor
     vcs_cbug_stream_object_guarded
	 (const char *objectname,
	  void *hObject,
	  T *object_to_stream,
	  vcs_cbug_object_info* obj_info,
          int *counter_indicating_object_has_changed,
	  bool dump_all_updates,
	  const char *datatype);

       // d'tor
     ~vcs_cbug_stream_object_guarded();

  private:
     vcs_cbug_object_info* m_obj_info; // corresponding info object
     int*                  m_change_ptr;  // guard indicating if value [may] have changed
     int                   m_change_ref;  // reference for previous guard
     bool                  m_dump_all_updates;
                                       // true: also dump when *m_change_ptr==m_change_ref
                                       //   and value itself has not changed
                                       // false: dump only when *m_change_ptr==m_change_ref
                                       //   and value has changed
};

template< class T >
inline
vcs_cbug_stream_object_guarded<T>::vcs_cbug_stream_object_guarded
  (const char *objectname,
   void *hObject,
   T *object_to_stream,
   vcs_cbug_object_info* obj_info,
   int *counter_indicating_object_has_changed,
   bool dump_all_updates,
   const char *datatype
  )
      :  vcs_cbug_stream_object<T>( objectname, 
				    hObject, object_to_stream, datatype)
      , m_obj_info(obj_info)
      , m_change_ptr(counter_indicating_object_has_changed)
      , m_change_ref(0)
      , m_dump_all_updates(dump_all_updates)
{
}

template< class T >
inline
vcs_cbug_stream_object_guarded<T>::~vcs_cbug_stream_object_guarded()
{
}

// The member belongs logically to vcs_cbug_streaming.h and not the current 
// header file but this would create a cyclic dependency between both headers
//
// template< class T >
// inline
// void 
// vcs_cbug_stream_object_guarded<T>::cycle(bool force_streaming)
// {
//   ... see vcs_cbug_object_info.h ...
// }

template< class T >
inline
vcs_cbug_stream_object_base *
vcs_cbug_stream_object_guarded<T>::create
    (const char *objectname,
     void *hObject,
     T *object_to_stream, 
     vcs_cbug_object_info* obj_info,
     int *counter_indicating_object_has_changed,
     bool dump_all_updates,
     const char *datatype)
{
    return new vcs_cbug_stream_object_guarded<T>
        ( objectname, hObject,
	  object_to_stream, obj_info, counter_indicating_object_has_changed,
	  dump_all_updates, datatype);
}






template< class T >
class vcs_cbug_stream_object_fifo_size : public vcs_cbug_stream_object_base {
  public:
       // create a stream object
     static vcs_cbug_stream_object_base *create(const char *objectname,
             void *hObject,
             int elmt_index, const char *datatype,
             int *size, int *ri, int *wi, T **buf, int *free);

       // stream a cycle
     virtual void cycle(bool force_streaming);

 protected:
       // c'tor
     vcs_cbug_stream_object_fifo_size(const char *objectname,
                      void *hObject,
                      int elmt_index, const char *datatype,
                      int *size, int *ri, int *wi, T **buf, int *free);

       // d'tor
     ~vcs_cbug_stream_object_fifo_size();

     int *m_size;                 // size of the buffer
     int *m_ri;                   // index of next read
     int *m_wi;                   // index of next write
     T   **m_buf;                 // the buffer
     int *m_free;
     bool first_time;  // are we streaming the first value
     int old_value;
     int old_value_size;
     int element_index;  // index of the lement in fifo, -1 is for the size
};

template< class T >
inline
vcs_cbug_stream_object_fifo_size<T>::vcs_cbug_stream_object_fifo_size(const char *objectname,
                      void *hObject,
                      int elmt_index, const char *datatype,
                      int *size, int *ri, int *wi, T **buf, int *free)
    :  vcs_cbug_stream_object_base(objectname, hObject, datatype),
       m_size(size), m_ri(ri), m_wi(wi), m_buf(buf), m_free(free), 
       first_time(true), old_value(), old_value_size(0), element_index(elmt_index)
{
}

template< class T >
inline
vcs_cbug_stream_object_fifo_size<T>::~vcs_cbug_stream_object_fifo_size()
{
}

template< class T >
inline
void
vcs_cbug_stream_object_fifo_size<T>::cycle(bool force_streaming)
{
    if (!isOn())
        return;
    int val = 0; // number of elements
    if( *m_free != *m_size ) {
        int i = *m_ri;
        do {
            val++;
            i = ( i + 1 ) % *m_size;
        } while (i != *m_wi);
    }
    if (first_time || force_streaming || !(old_value_size == val) ) {
        void *vpd_data = 0;
        vcs_cbug_get_stream_value(val, &vpd_data,
                (std::string *)0, (std::string *)0);
        if (first_time) { // this is the first time I have been called
            stream_data(hVPD_Object, data_type.c_str(), vpd_data);
            first_time = false;
        }
        else {
            stream_data(hVPD_Object, "", vpd_data);
        }
    }
    old_value_size = val;
}

template< class T >
inline
vcs_cbug_stream_object_base *
vcs_cbug_stream_object_fifo_size<T>::create(const char *objectname,
             void *hObject,
             int elmt_index, const char *datatype,
             int *size, int *ri, int *wi, T **buf, int *free)
{
    return new vcs_cbug_stream_object_fifo_size<T>(objectname, hObject,
                       elmt_index, datatype, size, ri, wi, buf, free);
}


template< class T >
class vcs_cbug_stream_object_fifo_elmt : public vcs_cbug_stream_object_base {
  public:
       // create a stream object
     static vcs_cbug_stream_object_base *create(const char *objectname,
             void *hObject,
             int elmt_index, const char *datatype,
             int *size, int *ri, int *wi, T **buf, int *free);


       // stream a cycle
     virtual void cycle(bool force_streaming);

 protected:
       // c'tor
     vcs_cbug_stream_object_fifo_elmt(const char *objectname,
                      void *hObject,
                      int elmt_index, const char *datatype,
                      int *size, int *ri, int *wi, T **buf, int *free);

       // d'tor
     ~vcs_cbug_stream_object_fifo_elmt();

     int *m_size;                 // size of the buffer
     int *m_ri;                   // index of next read
     int *m_wi;                   // index of next write
     T   **m_buf;                 // the buffer
     int *m_free;
     bool first_time;  // are we streaming the first value
     T old_value;
     int old_value_size;
     int element_index;  // index of the lement in fifo, -1 is for the size
};

template< class T >
inline
vcs_cbug_stream_object_fifo_elmt<T>::vcs_cbug_stream_object_fifo_elmt(const char *objectname,
                      void *hObject,
                      int elmt_index, const char *datatype,
                      int *size, int *ri, int *wi, T **buf, int *free)
    :  vcs_cbug_stream_object_base(objectname, hObject, datatype),
       m_size(size), m_ri(ri), m_wi(wi), m_buf(buf), m_free(free), 
       first_time(true), old_value(T()), old_value_size(0), element_index(elmt_index)
{
}

template< class T >
inline
vcs_cbug_stream_object_fifo_elmt<T>::~vcs_cbug_stream_object_fifo_elmt()
{
}

template< class T >
inline
void
vcs_cbug_stream_object_fifo_elmt<T>::cycle(bool force_streaming)
{
    if (!isOn())
        return;
    int index_in_buf = -1;
    if( *m_free != *m_size ) {
        int elmt_pos = 0;
        int i = *m_ri;
        do {
            if (element_index == elmt_pos)
                index_in_buf = i;
            i = ( i + 1 ) % *m_size;
            elmt_pos++;
        } while (i != *m_wi);
    }
    T val;
    if (index_in_buf >= 0) 
        val = (*m_buf)[index_in_buf];
    else
        val = T();

    if (first_time || force_streaming || !(old_value == val) ) {
        void *vpd_data = 0;
        vcs_cbug_get_stream_value(val, &vpd_data,
                (std::string *)0, (std::string *)0);
        if (first_time) { // this is the first time I have been called
            stream_data(hVPD_Object, data_type.c_str(), vpd_data);
            first_time = false;
        }
        else {
            stream_data(hVPD_Object, "", vpd_data);
        }
    }
    old_value = val;
}

template< class T >
inline
vcs_cbug_stream_object_base *
vcs_cbug_stream_object_fifo_elmt<T>::create(const char *objectname,
             void *hObject,
             int elmt_index, const char *datatype,
             int *size, int *ri, int *wi, T **buf, int *free)
{
    return new vcs_cbug_stream_object_fifo_elmt<T>(objectname, hObject,
                       elmt_index, datatype, size, ri, wi, buf, free);
}


template< class T >
class vcs_cbug_stream_object_fifo : public vcs_cbug_stream_object_base {
  public:
       // create a stream object
     static vcs_cbug_stream_object_base *create(const char *objectname,
             void *hObject, const char *datatype,
             int *size, int *ri, int *wi, T **buf, int *free,
             int *num_readable, int *num_read, int *num_written, int *nbwrt);


       // stream a cycle
     virtual void cycle(bool force_streaming);

 protected:
       // c'tor
     vcs_cbug_stream_object_fifo(const char *objectname,
                      void *hObject, const char *datatype,
                      int *size, int *ri, int *wi, T **buf, int *free,
                      int *num_readable, int *num_read, int *num_written, int *nbwrt);

       // d'tor
     ~vcs_cbug_stream_object_fifo();

     int *m_size;                 // size of the buffer
     int *m_ri;                   // index of next read
     int *m_wi;                   // index of next write
     T   **m_buf;                 // the buffer
     int *m_free; 
     int *m_num_readable; 
     int *m_num_read; 
     int *m_num_written; 
     int *m_nbwrt; 
     bool first_time;  // are we saving the first value

};

template< class T >
inline
vcs_cbug_stream_object_fifo<T>::vcs_cbug_stream_object_fifo(const char *objectname,
                      void *hObject, const char *datatype,
                      int *size, int *ri, int *wi, T **buf, int *free, int *num_readable,
                      int *num_read, int *num_written, int *nbwrt)
    :  vcs_cbug_stream_object_base(objectname, hObject, datatype),
       m_size(size), m_ri(ri), m_wi(wi), m_buf(buf), m_free(free), m_num_readable(num_readable),
       m_num_read(num_read), m_num_written(num_written), m_nbwrt(nbwrt), first_time(true)
{
}

template< class T >
inline
vcs_cbug_stream_object_fifo<T>::~vcs_cbug_stream_object_fifo()
{
}

template< class T >
inline
void
vcs_cbug_stream_object_fifo<T>::cycle(bool force_streaming)
{
    /* nothing to be done for now */
    return;
}

template< class T >
inline
vcs_cbug_stream_object_base *
vcs_cbug_stream_object_fifo<T>::create(const char *objectname,
             void *hObject, const char *datatype,
             int *size, int *ri, int *wi, T **buf, int *free, int *num_readable,
             int *num_read, int *num_written, int *nbwrt)
{
    return new vcs_cbug_stream_object_fifo<T>(objectname, hObject,
                       datatype, size, ri, wi, buf, free, num_readable, 
                       num_read, num_written, nbwrt);
}


} // namespace sc_snps


#endif
