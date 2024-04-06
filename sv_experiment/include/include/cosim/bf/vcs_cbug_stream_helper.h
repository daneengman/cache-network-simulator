/******************************************************************************
    Copyright (c) 2000-2009 Synopsys, Inc.    ALL RIGHTS RESERVED

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

    Original Author: Karsten Sievert. Synopsys, Inc. (sievert@synopsys.com)

******************************************************************************/


#ifndef vcs_cbug_stream_helper_h
#define vcs_cbug_stream_helper_h


// describe the types for correct template selection
//
template <class T, T v>
struct vcs_cbug_integral_constant
{
    enum value_type { value = v };
    typedef vcs_cbug_integral_constant<value_type, value> type;
};

typedef vcs_cbug_integral_constant<bool, true>  true_type;
typedef vcs_cbug_integral_constant<bool, false> false_type;

template <class T> struct vcs_cbug_remove_const { typedef T type; };
template <class T> struct vcs_cbug_remove_const<const T> { typedef T type; };
template <class T> struct vcs_cbug_remove_volatile { typedef T type; };
template <class T> struct vcs_cbug_remove_volatile<volatile T> { typedef T type; };
template <class T> struct vcs_cbug_remove_cv:
  vcs_cbug_remove_const<typename vcs_cbug_remove_volatile<T>::type> { };

template <class T> struct vcs_cbug_unsigned_type { typedef T type; };
template <> struct vcs_cbug_unsigned_type<char> { typedef unsigned char type; };
template <> struct vcs_cbug_unsigned_type<signed char> { typedef unsigned char type; };
template <> struct vcs_cbug_unsigned_type<int> { typedef unsigned int type; };
template <> struct vcs_cbug_unsigned_type<short> { typedef unsigned short type; };
template <> struct vcs_cbug_unsigned_type<long> { typedef unsigned long type; };
template <> struct vcs_cbug_unsigned_type<long long> { typedef unsigned long long type; };

template <class, class> struct vcs_cbug_is_same: false_type { };
template <class T> struct vcs_cbug_is_same<T, T>: true_type { };

// is T a standard signed/unsigned integer type?
template <class> struct vcs_cbug_is_signed: false_type { };
template <class> struct vcs_cbug_is_unsigned: false_type { };

// vcs_cbug_is_signed specializations for each standard signed
// integer type (T must not be cv-qualified)
template <> struct vcs_cbug_is_signed<signed char>: true_type { };
template <> struct vcs_cbug_is_signed<int>: true_type { };
template <> struct vcs_cbug_is_signed<short>: true_type { };
template <> struct vcs_cbug_is_signed<long>: true_type { };
template <> struct vcs_cbug_is_signed<long long>: true_type { };

// vcs_cbug_is_unsigned specializations for each standard unsigned
// integer type (T must not be cv-qualified)
template <> struct vcs_cbug_is_unsigned<unsigned char>: true_type { };
template <> struct vcs_cbug_is_unsigned<unsigned int>: true_type { };
template <> struct vcs_cbug_is_unsigned<unsigned short>: true_type { };
template <> struct vcs_cbug_is_unsigned<unsigned long>: true_type { };
template <> struct vcs_cbug_is_unsigned<unsigned long long>: true_type { };

//# template <class T>
//# struct vcs_cbug_is_integral:
//#   vcs_cbug_integral_constant<
//#     bool,
//#        vcs_cbug_is_signed<T>::value
//#     || vcs_cbug_is_unsigned<T>::value
//#     || vcs_cbug_is_same<typename vcs_cbug_remove_cv<T>::type, bool>::value
//#     || vcs_cbug_is_same<typename vcs_cbug_remove_cv<T>::type, char>::value>
//# { };

template <class T, bool s>
struct vcs_cbug_is_negative_impl {
    static bool result (T value) { return false; }
};

template <class T>
struct vcs_cbug_is_negative_impl<T, true> {
    static bool result (T value) { return value < 0; }
};

template <class T>
bool vcs_cbug_is_negative(T value)
{
    return vcs_cbug_is_negative_impl<T, vcs_cbug_is_signed<T>::value>::result(value);
}


#endif  //ifndef vcs_cbug_stream_helper_h

