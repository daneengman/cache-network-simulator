/*********************************************************************
*                                                                    *
*       C Y C L E C . H                                              *
*       CycleC (tm) methodology support header                       *
*                                                                    *
*       Copyright (c) 2001-2002  Synopsys Inc.                       *
*       Copyright (c) 1997-2001  C Level Design Inc.                 *
*                                                                    *
*       $RCSfile: cyclec.h,v $
*                                                                    *
*********************************************************************/

/* $Id$ $Author$ $DateTime$ */

#ifndef __CYCLEC_H_INCLUDED__
#define __CYCLEC_H_INCLUDED__

/*********************************************************************
*                                                                    *
*   Brief description of helper classes:                             *
*                                                                    *
*   Bit-level manipulations:                                         *
*                                                                    *
*       cc_getBit   (expression,  bit)                               *
*       cc_setBit   (expression,  bit, value)                        *
*       cc_getSlice (expression,  high, low)                         *
*       cc_setSlice (expression,  high, low, value)                  *
*       cc_concat   (expression1, expression2, size1, size2)         *
*                                                                    *
*   cc_sim - simulator abstraction; holder for two global indexes,   *
*   in and out, used for cc_wire functionality.                      *
*                                                                    *
*       cc_sim sim;                               Simulation only    *
*                                                                    *
*       cc_stepSim        ()                      Simulation only    *
*       cc_stepSim        (sim)                   Simulation only    *
*       cc_setCurrentSim  (sim)                   Simulation only    *
*                                                                    *
*   cc_wire - interconnect wire implementation. This class           *
*   holds two values - old and new value. Usually wire               *
*   comes from clocked output of some submodule and                  *
*   is an input of another submodule. Old and new values             *
*   are implemented as an array of two elements.                     *
*   cc_currentSim::sim.in and cc_currentSim::sim.out                 *
*   are used to access cc_wire old and new values                    *
*   correspondingly.                                                 *
*                                                                    *
*       cc_wire (type) wire;                                         *
*                                                                    *
*       cc_in  (wire)                                                *
*       cc_out (wire)                                                *
*                                                                    *
*       module1.run (..., wire ...    Wire is hooked to the input    *
*       module2.run (..., & wire ...  Wire is hooked to the output   *
*                                                                    *
*   cc_array - an array version of cc_wire.                          *
*                                                                    *
*       cc_array (type, n) array;                                    *
*                                                                    *
*       cc_in  (array)                                               *
*       cc_out (array)                                               *
*                                                                    *
*       module1.run (..., array ...   Array is hooked to the input   *
*       module2.run (..., & array ... Array is hooked to the output  *
*                                                                    *
*   cc_tri - tristate bus with high impedance.                       *
*   Used as a reference to represent an inout port.                  *
*                                                                    *
*       cc_tri (type) tri;                                           *
*                                                                    *
*       cc_readTri  (tri)                                            *
*       cc_writeTri (tri, enable, value)                             *
*                                                                    *
*       class UserModule {                                           *
*           void run (..., cc_tri (int) & bus, ...)   Tri port       *
*                                                                    *
*       cc_inIsZ   (tri)                          Simulation only    *
*       cc_outIsZ  (tri)                          Simulation only    *
*                                                                    *
*       cc_setInZ  (tri)                          Simulation only    *
*       cc_setOutZ (tri)                          Simulation only    *
*                                                                    *
*       cc_checkReadingFromHighImpedance      ()  Simulation only    *
*       cc_dontCheckReadingFromHighImpedance  ()  Simulation only    *
*       cc_checkMultipleDrivers               ()  Simulation only    *
*       cc_dontCheckMultipleDrivers           ()  Simulation only    *
*                                                                    *
*       cc_checkHighImpd                      ()  Simulation only    *
*       cc_dontCheckHighImpd                  ()  Simulation only    *
*       cc_checkMultiDrivers                  ()  Simulation only    *
*       cc_dontCheckMultiDrivers              ()  Simulation only    *
*                                                                    *
*   cc_timeType                                   Simulation only    *
*                                                                    *
*       __CC_TIMETYPE_IS_32_BIT_UNSIGNED__        Simulation only    *
*       __CC_TIMETYPE_IS_64_BIT_UNSIGNED__        Simulation only    *
*       __CC_TIMETYPE_IS_96_BIT_UNSIGNED__        Simulation only    *
*       __CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__  Simulation only    *
*                                                                    *
*       cc_timeBits95_32 ()                       Simulation only    *
*       cc_timeBits95_64 ()                       Simulation only    *
*       cc_timeBits63_0  ()                       Simulation only    *
*       cc_timeBits63_32 ()                       Simulation only    *
*       cc_timeBits31_0  ()                       Simulation only    *
*       cc_doubleTime    ()                       Simulation only    *
*       cc_timeString    ()                       Simulation only    *
*                                                                    *
*       cc_timeBits95_32 (time)                   Simulation only    *
*       cc_timeBits95_64 (time)                   Simulation only    *
*       cc_timeBits63_0  (time)                   Simulation only    *
*       cc_timeBits63_32 (time)                   Simulation only    *
*       cc_timeBits31_0  (time)                   Simulation only    *
*       cc_doubleTime    (time)                   Simulation only    *
*       cc_timeString    (time)                   Simulation only    *
*                                                                    *
*       cc_makeTime (bits31_0)                    Simulation only    *
*       cc_makeTime (bits63_32, bits31_0)         Simulation only    *
*                                                                    *
*       cc_makeTime                               Simulation only    *
*       (                                                            *
*           bits95_64,                                               *
*           bits63_32,                                               *
*           bits31_0                                                 *
*       )                                                            *
*                                                                    *
*   cc_clock - clock.                                                *
*                                                                    *
*       cc_clock clock;    Internally generated clock                *
*                                                                    *
*       cc_clock clock     Externally generated clock                *
*       (                  Simulation only                           *
*           period,                                                  *
*           posedgeTime,                                             *
*           negedgeTime,                                             *
*           activeEdges    POSEDGE, NEGEDGE, BOTHEDGES               *
*       )                                                            *
*                                                                    *
*       cc_clockValueName      (clock)            Simulation only    *
*       cc_clockValueShortName (clock)            Simulation only    *
*                                                                    *
*       clock = POSEDGE                                              *
*       clock = NEGEDGE                                              *
*       clock = HIGH                                                 *
*       clock = LOW                                                  *
*                                                                    *
*       if (clock == POSEDGE || ! reset)                             *
*       if (clock == NEGEDGE || reset)                               *
*                                                                    *
*       cc_posedge (clock)                                           *
*       cc_negedge (clock)                                           *
*       cc_level   (clock)                                           *
*                                                                    *
*       cc_advanceClocks ()                       Simulation only    *
*                                                                    *
*   VCD/VCD+/VPD dump                       All - Simulation only    *
*                                                                    *
*       cc_dumpFile            ("fileName")       Default is VCD     *
*       cc_dumpFile            ("fileName", VCD)                     *
*       cc_dumpFile            ("fileName", VPD)                     *
*                                                                    *
*       cc_dumpTimeScale       ("timeScale")                         *
*                                                                    *
*       cc_dumpScope           ("scope")                             *
*       cc_dumpUpScope         ("scope")                             *
*       cc_dumpUpScope         ()                                    *
*                                                                    *
*       cc_dumpClock           ("name", variable)                    *
*       cc_dumpReg             ("name", variable, bitWidth)          *
*       cc_dumpWire            ("name", variable, bitWidth)          *
*                                                                    *
*       cc_dumpLocalClockData  (variable)                            *
*       cc_dumpLocalClock      (variable)                            *
*       cc_dumpLocalData       (variable, bitWidth)                  *
*       cc_dumpLocal           (variable)                            *
*       cc_dumpLocalArrayData  (variable, bitWidth, nElements)       *
*       cc_dumpLocalArray      (variable, nElements)                 *
*                                                                    *
*       cc_dumpUpdate          ()                                    *
*       cc_dumpFlush           ()                                    *
*       cc_dumpFinish          ()                                    *
*                                                                    *
*   We are not using private, protected, virtual functions           *
*   and other "correct" C++ elements                                 *
*   in this ultra-lightweight minimalist helper classes.             *
*                                                                    *
*   We believe that our approach makes code easier to read           *
*   and easier to debug by the hardware RTL engineer.                *
*                                                                    *
*********************************************************************/

inline void cc_dummyFunctionToAvoidEDG_WarningAboutIncorrectPragma ()
{
}

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/********************************************************************/

#if defined (__SUNPRO_CC) && ! defined (_BOOL)
enum { false = 0, true = 1 };
typedef int bool;
#endif

/********************************************************************/

#if defined (__SUNPRO_CC) && __SUNPRO_CC < 0x500
#error cyclec.h is supported with version of CC starting 5.x. CC 4.x is not supported.
#endif

/********************************************************************/

#if defined (__CLEVEL__) && ! defined (__CYCLEC_TRANSLATION__)
#define __CYCLEC_TRANSLATION__
#endif

#if ! defined (__CLEVEL__) && ! defined (__CYCLEC_SIMULATION__)
#define __CYCLEC_SIMULATION__
#endif

#if ! defined (__CYCLEC_UINT_TEMPLATE_IMPLEMENTATION__) && defined (__CLEVEL_TEMPLATE__)
#define __CYCLEC_UINT_TEMPLATE_IMPLEMENTATION__
#endif

/********************************************************************/

#ifndef __CYCLEC_VERSION_STRING__
#define __CYCLEC_VERSION_STRING__   "1.0"
#endif

/********************************************************************/

#define cc_log stdout

/*********************************************************************
*                                                                    *
*   Integer arithmetics                                              *
*                                                                    *
*********************************************************************/

#ifdef __CYCLEC_SIMULATION__

#define _DEFINE_CYCLEC_TYPE_INT(size) \
    typedef int int##size;

#define _DEFINE_CYCLEC_TYPE_UINT(size) \
    typedef unsigned uint##size;

/********************************************************************/

#if defined (__unix) || defined (__GNUC__)

#define _DEFINE_CYCLEC_TYPE_LONG_INT(size) \
    typedef long long int##size;

#define _DEFINE_CYCLEC_TYPE_LONG_UINT(size) \
    typedef unsigned long long uint##size;

#else  /*  #if defined (__unix) || defined (__GNUC__)  */

#define _DEFINE_CYCLEC_TYPE_LONG_INT(size) \
    typedef _int64 int##size;

#define _DEFINE_CYCLEC_TYPE_LONG_UINT(size) \
    typedef unsigned _int64 uint##size;

#endif  /*  #if defined (__unix) || defined (__GNUC__)  */

/*********************************************************************
*                                                                    *
*   Microsoft cl uses _int64, Solaris Visual Workshop                *
*   and gcc use long long. long long can not be redefined            *
*   so define _int64 for unix and gcc                                *
*                                                                    *
*********************************************************************/

#if (defined (__unix) || defined (__GNUC__)) && ! defined (_int64)
#define _int64 long long
#endif

/********************************************************************/

#define CV_00000IOOO(bit)                                      \
    (1 << (bit-1))

#define CV_00000IOOO_64(bit)                                   \
    ( ((unsigned _int64)1) << (bit-1))

#define CV_IIIIIIOOOsizeOOO(bit_size)                          \
    (~ 0 << (bit_size) )

#define CV_IIIIIIOOOsizeOOO_64(bit_size)                       \
    (~ (unsigned _int64)0 << (bit_size))

#define CV_OOOOOOIIIsizeIII(bit_size)                          \
    (~ CV_IIIIIIOOOsizeOOO (bit_size))

#define CV_OOOOOOIIIsizeIII_64(bit_size)                       \
    (~ CV_IIIIIIOOOsizeOOO_64 (bit_size))

#define __CV_INTN(n) ( (((int##n) (x)) & CV_00000IOOO(n)) == 0 ? \
                       ((int##n) (x)) & CV_OOOOOOIIIsizeIII(n) : \
                       ((int##n) (x)) | CV_IIIIIIOOOsizeOOO(n) )

#define __CV_INTN_64(n) ( (((int##n) (x)) & CV_00000IOOO_64(n)) == 0 ? \
                          ((int##n) (x)) & CV_OOOOOOIIIsizeIII_64(n) : \
                          ((int##n) (x)) | CV_IIIIIIOOOsizeOOO_64(n) )

/********************************************************************/

_DEFINE_CYCLEC_TYPE_INT(1)
#define cv_int1(x)  (((int1)  (x)) & CV_OOOOOOIIIsizeIII(1))
_DEFINE_CYCLEC_TYPE_INT(2)
#define cv_int2(x)  __CV_INTN(2)
_DEFINE_CYCLEC_TYPE_INT(3)
#define cv_int3(x)  __CV_INTN(3)
_DEFINE_CYCLEC_TYPE_INT(4)
#define cv_int4(x)  __CV_INTN(4)
_DEFINE_CYCLEC_TYPE_INT(5)
#define cv_int5(x)  __CV_INTN(5)
_DEFINE_CYCLEC_TYPE_INT(6)
#define cv_int6(x)  __CV_INTN(6)
_DEFINE_CYCLEC_TYPE_INT(7)
#define cv_int7(x)  __CV_INTN(7)
_DEFINE_CYCLEC_TYPE_INT(8)
#define cv_int8(x)  __CV_INTN(8)
_DEFINE_CYCLEC_TYPE_INT(9)
#define cv_int9(x)  __CV_INTN(9)
_DEFINE_CYCLEC_TYPE_INT(10)
#define cv_int10(x) __CV_INTN(10)
_DEFINE_CYCLEC_TYPE_INT(11)
#define cv_int11(x) __CV_INTN(11)
_DEFINE_CYCLEC_TYPE_INT(12)
#define cv_int12(x) __CV_INTN(12)
_DEFINE_CYCLEC_TYPE_INT(13)
#define cv_int13(x) __CV_INTN(13)
_DEFINE_CYCLEC_TYPE_INT(14)
#define cv_int14(x) __CV_INTN(14)
_DEFINE_CYCLEC_TYPE_INT(15)
#define cv_int15(x) __CV_INTN(15)
_DEFINE_CYCLEC_TYPE_INT(16)
#define cv_int16(x) __CV_INTN(16)
_DEFINE_CYCLEC_TYPE_INT(17)
#define cv_int17(x) __CV_INTN(17)
_DEFINE_CYCLEC_TYPE_INT(18)
#define cv_int18(x) __CV_INTN(18)
_DEFINE_CYCLEC_TYPE_INT(19)
#define cv_int19(x) __CV_INTN(19)
_DEFINE_CYCLEC_TYPE_INT(20)
#define cv_int20(x) __CV_INTN(20)
_DEFINE_CYCLEC_TYPE_INT(21)
#define cv_int21(x) __CV_INTN(21)
_DEFINE_CYCLEC_TYPE_INT(22)
#define cv_int22(x) __CV_INTN(22)
_DEFINE_CYCLEC_TYPE_INT(23)
#define cv_int23(x) __CV_INTN(23)
_DEFINE_CYCLEC_TYPE_INT(24)
#define cv_int24(x) __CV_INTN(24)
_DEFINE_CYCLEC_TYPE_INT(25)
#define cv_int25(x) __CV_INTN(25)
_DEFINE_CYCLEC_TYPE_INT(26)
#define cv_int26(x) __CV_INTN(26)
_DEFINE_CYCLEC_TYPE_INT(27)
#define cv_int27(x) __CV_INTN(27)
_DEFINE_CYCLEC_TYPE_INT(28)
#define cv_int28(x) __CV_INTN(28)
_DEFINE_CYCLEC_TYPE_INT(29)
#define cv_int29(x) __CV_INTN(29)
_DEFINE_CYCLEC_TYPE_INT(30)
#define cv_int30(x) __CV_INTN(30)
_DEFINE_CYCLEC_TYPE_INT(31)
#define cv_int31(x) __CV_INTN(31)
_DEFINE_CYCLEC_TYPE_INT(32)
#define cv_int32(x) ((int32) (x))

/********************************************************************/

_DEFINE_CYCLEC_TYPE_LONG_INT(33)
#define cv_int33(x) __CV_INTN_64(33)
_DEFINE_CYCLEC_TYPE_LONG_INT(34)
#define cv_int34(x) __CV_INTN_64(34)
_DEFINE_CYCLEC_TYPE_LONG_INT(35)
#define cv_int35(x) __CV_INTN_64(35)
_DEFINE_CYCLEC_TYPE_LONG_INT(36)
#define cv_int36(x) __CV_INTN_64(36)
_DEFINE_CYCLEC_TYPE_LONG_INT(37)
#define cv_int37(x) __CV_INTN_64(37)
_DEFINE_CYCLEC_TYPE_LONG_INT(38)
#define cv_int38(x) __CV_INTN_64(38)
_DEFINE_CYCLEC_TYPE_LONG_INT(39)
#define cv_int39(x) __CV_INTN_64(39)
_DEFINE_CYCLEC_TYPE_LONG_INT(40)
#define cv_int40(x) __CV_INTN_64(40)
_DEFINE_CYCLEC_TYPE_LONG_INT(41)
#define cv_int41(x) __CV_INTN_64(41)
_DEFINE_CYCLEC_TYPE_LONG_INT(42)
#define cv_int42(x) __CV_INTN_64(42)
_DEFINE_CYCLEC_TYPE_LONG_INT(43)
#define cv_int43(x) __CV_INTN_64(43)
_DEFINE_CYCLEC_TYPE_LONG_INT(44)
#define cv_int44(x) __CV_INTN_64(44)
_DEFINE_CYCLEC_TYPE_LONG_INT(45)
#define cv_int45(x) __CV_INTN_64(45)
_DEFINE_CYCLEC_TYPE_LONG_INT(46)
#define cv_int46(x) __CV_INTN_64(46)
_DEFINE_CYCLEC_TYPE_LONG_INT(47)
#define cv_int47(x) __CV_INTN_64(47)
_DEFINE_CYCLEC_TYPE_LONG_INT(48)
#define cv_int48(x) __CV_INTN_64(48)
_DEFINE_CYCLEC_TYPE_LONG_INT(49)
#define cv_int49(x) __CV_INTN_64(49)
_DEFINE_CYCLEC_TYPE_LONG_INT(50)
#define cv_int50(x) __CV_INTN_64(50)
_DEFINE_CYCLEC_TYPE_LONG_INT(51)
#define cv_int51(x) __CV_INTN_64(51)
_DEFINE_CYCLEC_TYPE_LONG_INT(52)
#define cv_int52(x) __CV_INTN_64(52)
_DEFINE_CYCLEC_TYPE_LONG_INT(53)
#define cv_int53(x) __CV_INTN_64(53)
_DEFINE_CYCLEC_TYPE_LONG_INT(54)
#define cv_int54(x) __CV_INTN_64(54)
_DEFINE_CYCLEC_TYPE_LONG_INT(55)
#define cv_int55(x) __CV_INTN_64(55)
_DEFINE_CYCLEC_TYPE_LONG_INT(56)
#define cv_int56(x) __CV_INTN_64(56)
_DEFINE_CYCLEC_TYPE_LONG_INT(57)
#define cv_int57(x) __CV_INTN_64(57)
_DEFINE_CYCLEC_TYPE_LONG_INT(58)
#define cv_int58(x) __CV_INTN_64(58)
_DEFINE_CYCLEC_TYPE_LONG_INT(59)
#define cv_int59(x) __CV_INTN_64(59)
_DEFINE_CYCLEC_TYPE_LONG_INT(60)
#define cv_int60(x) __CV_INTN_64(60)
_DEFINE_CYCLEC_TYPE_LONG_INT(61)
#define cv_int61(x) __CV_INTN_64(61)
_DEFINE_CYCLEC_TYPE_LONG_INT(62)
#define cv_int62(x) __CV_INTN_64(62)
_DEFINE_CYCLEC_TYPE_LONG_INT(63)
#define cv_int63(x) __CV_INTN_64(63)
_DEFINE_CYCLEC_TYPE_LONG_INT(64)
#define cv_int64(x) ((int64) (x))

/********************************************************************/

_DEFINE_CYCLEC_TYPE_UINT(1)
#define cv_uint1(x)  (((uint1)  (x)) & CV_OOOOOOIIIsizeIII(1))
_DEFINE_CYCLEC_TYPE_UINT(2)
#define cv_uint2(x)  (((uint2)  (x)) & CV_OOOOOOIIIsizeIII(2))
_DEFINE_CYCLEC_TYPE_UINT(3)
#define cv_uint3(x)  (((uint3)  (x)) & CV_OOOOOOIIIsizeIII(3))
_DEFINE_CYCLEC_TYPE_UINT(4)
#define cv_uint4(x)  (((uint4)  (x)) & CV_OOOOOOIIIsizeIII(4))
_DEFINE_CYCLEC_TYPE_UINT(5)
#define cv_uint5(x)  (((uint5)  (x)) & CV_OOOOOOIIIsizeIII(5))
_DEFINE_CYCLEC_TYPE_UINT(6)
#define cv_uint6(x)  (((uint6)  (x)) & CV_OOOOOOIIIsizeIII(6))
_DEFINE_CYCLEC_TYPE_UINT(7)
#define cv_uint7(x)  (((uint7)  (x)) & CV_OOOOOOIIIsizeIII(7))
_DEFINE_CYCLEC_TYPE_UINT(8)
#define cv_uint8(x)  (((uint8)  (x)) & CV_OOOOOOIIIsizeIII(8))
_DEFINE_CYCLEC_TYPE_UINT(9)
#define cv_uint9(x)  (((uint9)  (x)) & CV_OOOOOOIIIsizeIII(9))
_DEFINE_CYCLEC_TYPE_UINT(10)
#define cv_uint10(x) (((uint10) (x)) & CV_OOOOOOIIIsizeIII(10))
_DEFINE_CYCLEC_TYPE_UINT(11)
#define cv_uint11(x) (((uint11) (x)) & CV_OOOOOOIIIsizeIII(11))
_DEFINE_CYCLEC_TYPE_UINT(12)
#define cv_uint12(x) (((uint12) (x)) & CV_OOOOOOIIIsizeIII(12))
_DEFINE_CYCLEC_TYPE_UINT(13)
#define cv_uint13(x) (((uint13) (x)) & CV_OOOOOOIIIsizeIII(13))
_DEFINE_CYCLEC_TYPE_UINT(14)
#define cv_uint14(x) (((uint14) (x)) & CV_OOOOOOIIIsizeIII(14))
_DEFINE_CYCLEC_TYPE_UINT(15)
#define cv_uint15(x) (((uint15) (x)) & CV_OOOOOOIIIsizeIII(15))
_DEFINE_CYCLEC_TYPE_UINT(16)
#define cv_uint16(x) (((uint16) (x)) & CV_OOOOOOIIIsizeIII(16))
_DEFINE_CYCLEC_TYPE_UINT(17)
#define cv_uint17(x) (((uint17) (x)) & CV_OOOOOOIIIsizeIII(17))
_DEFINE_CYCLEC_TYPE_UINT(18)
#define cv_uint18(x) (((uint18) (x)) & CV_OOOOOOIIIsizeIII(18))
_DEFINE_CYCLEC_TYPE_UINT(19)
#define cv_uint19(x) (((uint19) (x)) & CV_OOOOOOIIIsizeIII(19))
_DEFINE_CYCLEC_TYPE_UINT(20)
#define cv_uint20(x) (((uint20) (x)) & CV_OOOOOOIIIsizeIII(20))
_DEFINE_CYCLEC_TYPE_UINT(21)
#define cv_uint21(x) (((uint21) (x)) & CV_OOOOOOIIIsizeIII(21))
_DEFINE_CYCLEC_TYPE_UINT(22)
#define cv_uint22(x) (((uint22) (x)) & CV_OOOOOOIIIsizeIII(22))
_DEFINE_CYCLEC_TYPE_UINT(23)
#define cv_uint23(x) (((uint23) (x)) & CV_OOOOOOIIIsizeIII(23))
_DEFINE_CYCLEC_TYPE_UINT(24)
#define cv_uint24(x) (((uint24) (x)) & CV_OOOOOOIIIsizeIII(24))
_DEFINE_CYCLEC_TYPE_UINT(25)
#define cv_uint25(x) (((uint25) (x)) & CV_OOOOOOIIIsizeIII(25))
_DEFINE_CYCLEC_TYPE_UINT(26)
#define cv_uint26(x) (((uint26) (x)) & CV_OOOOOOIIIsizeIII(26))
_DEFINE_CYCLEC_TYPE_UINT(27)
#define cv_uint27(x) (((uint27) (x)) & CV_OOOOOOIIIsizeIII(27))
_DEFINE_CYCLEC_TYPE_UINT(28)
#define cv_uint28(x) (((uint28) (x)) & CV_OOOOOOIIIsizeIII(28))
_DEFINE_CYCLEC_TYPE_UINT(29)
#define cv_uint29(x) (((uint29) (x)) & CV_OOOOOOIIIsizeIII(29))
_DEFINE_CYCLEC_TYPE_UINT(30)
#define cv_uint30(x) (((uint30) (x)) & CV_OOOOOOIIIsizeIII(30))
_DEFINE_CYCLEC_TYPE_UINT(31)
#define cv_uint31(x) (((uint31) (x)) & CV_OOOOOOIIIsizeIII(31))
_DEFINE_CYCLEC_TYPE_UINT(32)
#define cv_uint32(x) ((uint32) (x))

/********************************************************************/

_DEFINE_CYCLEC_TYPE_LONG_UINT(33)
#define cv_uint33(x) (((uint33) (x)) & CV_OOOOOOIIIsizeIII_64(33))
_DEFINE_CYCLEC_TYPE_LONG_UINT(34)
#define cv_uint34(x) (((uint34) (x)) & CV_OOOOOOIIIsizeIII_64(34))
_DEFINE_CYCLEC_TYPE_LONG_UINT(35)
#define cv_uint35(x) (((uint35) (x)) & CV_OOOOOOIIIsizeIII_64(35))
_DEFINE_CYCLEC_TYPE_LONG_UINT(36)
#define cv_uint36(x) (((uint36) (x)) & CV_OOOOOOIIIsizeIII_64(36))
_DEFINE_CYCLEC_TYPE_LONG_UINT(37)
#define cv_uint37(x) (((uint37) (x)) & CV_OOOOOOIIIsizeIII_64(37))
_DEFINE_CYCLEC_TYPE_LONG_UINT(38)
#define cv_uint38(x) (((uint38) (x)) & CV_OOOOOOIIIsizeIII_64(38))
_DEFINE_CYCLEC_TYPE_LONG_UINT(39)
#define cv_uint39(x) (((uint39) (x)) & CV_OOOOOOIIIsizeIII_64(39))
_DEFINE_CYCLEC_TYPE_LONG_UINT(40)
#define cv_uint40(x) (((uint40) (x)) & CV_OOOOOOIIIsizeIII_64(40))
_DEFINE_CYCLEC_TYPE_LONG_UINT(41)
#define cv_uint41(x) (((uint41) (x)) & CV_OOOOOOIIIsizeIII_64(41))
_DEFINE_CYCLEC_TYPE_LONG_UINT(42)
#define cv_uint42(x) (((uint42) (x)) & CV_OOOOOOIIIsizeIII_64(42))
_DEFINE_CYCLEC_TYPE_LONG_UINT(43)
#define cv_uint43(x) (((uint43) (x)) & CV_OOOOOOIIIsizeIII_64(43))
_DEFINE_CYCLEC_TYPE_LONG_UINT(44)
#define cv_uint44(x) (((uint44) (x)) & CV_OOOOOOIIIsizeIII_64(44))
_DEFINE_CYCLEC_TYPE_LONG_UINT(45)
#define cv_uint45(x) (((uint45) (x)) & CV_OOOOOOIIIsizeIII_64(45))
_DEFINE_CYCLEC_TYPE_LONG_UINT(46)
#define cv_uint46(x) (((uint46) (x)) & CV_OOOOOOIIIsizeIII_64(46))
_DEFINE_CYCLEC_TYPE_LONG_UINT(47)
#define cv_uint47(x) (((uint47) (x)) & CV_OOOOOOIIIsizeIII_64(47))
_DEFINE_CYCLEC_TYPE_LONG_UINT(48)
#define cv_uint48(x) (((uint48) (x)) & CV_OOOOOOIIIsizeIII_64(48))
_DEFINE_CYCLEC_TYPE_LONG_UINT(49)
#define cv_uint49(x) (((uint49) (x)) & CV_OOOOOOIIIsizeIII_64(49))
_DEFINE_CYCLEC_TYPE_LONG_UINT(50)
#define cv_uint50(x) (((uint50) (x)) & CV_OOOOOOIIIsizeIII_64(50))
_DEFINE_CYCLEC_TYPE_LONG_UINT(51)
#define cv_uint51(x) (((uint51) (x)) & CV_OOOOOOIIIsizeIII_64(51))
_DEFINE_CYCLEC_TYPE_LONG_UINT(52)
#define cv_uint52(x) (((uint52) (x)) & CV_OOOOOOIIIsizeIII_64(52))
_DEFINE_CYCLEC_TYPE_LONG_UINT(53)
#define cv_uint53(x) (((uint53) (x)) & CV_OOOOOOIIIsizeIII_64(53))
_DEFINE_CYCLEC_TYPE_LONG_UINT(54)
#define cv_uint54(x) (((uint54) (x)) & CV_OOOOOOIIIsizeIII_64(54))
_DEFINE_CYCLEC_TYPE_LONG_UINT(55)
#define cv_uint55(x) (((uint55) (x)) & CV_OOOOOOIIIsizeIII_64(55))
_DEFINE_CYCLEC_TYPE_LONG_UINT(56)
#define cv_uint56(x) (((uint56) (x)) & CV_OOOOOOIIIsizeIII_64(56))
_DEFINE_CYCLEC_TYPE_LONG_UINT(57)
#define cv_uint57(x) (((uint57) (x)) & CV_OOOOOOIIIsizeIII_64(57))
_DEFINE_CYCLEC_TYPE_LONG_UINT(58)
#define cv_uint58(x) (((uint58) (x)) & CV_OOOOOOIIIsizeIII_64(58))
_DEFINE_CYCLEC_TYPE_LONG_UINT(59)
#define cv_uint59(x) (((uint59) (x)) & CV_OOOOOOIIIsizeIII_64(59))
_DEFINE_CYCLEC_TYPE_LONG_UINT(60)
#define cv_uint60(x) (((uint60) (x)) & CV_OOOOOOIIIsizeIII_64(60))
_DEFINE_CYCLEC_TYPE_LONG_UINT(61)
#define cv_uint61(x) (((uint61) (x)) & CV_OOOOOOIIIsizeIII_64(61))
_DEFINE_CYCLEC_TYPE_LONG_UINT(62)
#define cv_uint62(x) (((uint62) (x)) & CV_OOOOOOIIIsizeIII_64(62))
_DEFINE_CYCLEC_TYPE_LONG_UINT(63)
#define cv_uint63(x) (((uint63) (x)) & CV_OOOOOOIIIsizeIII_64(63))
_DEFINE_CYCLEC_TYPE_LONG_UINT(64)
#define cv_uint64(x) ((uint64) (x))

/********************************************************************/

#else  /*  #ifdef __CYCLEC_SIMULATION__  */

#ifdef __cplusplus
#ifdef __CYCLEC_UINT_TEMPLATE_IMPLEMENTATION__

class cc_base
{
};

/********************************************************************/

template <int size>
class ccT_int : public cc_base
{
public:

    ccT_int <size> ();
    ccT_int <size> (int);

    ccT_int <size> & operator =   (int);
    ccT_int <size> & operator +=  (int);
    ccT_int <size> & operator -=  (int);
    ccT_int <size> & operator *=  (int);
    ccT_int <size> & operator /=  (int);
    ccT_int <size> & operator &=  (int);
    ccT_int <size> & operator |=  (int);
    ccT_int <size> & operator ^=  (int);
    ccT_int <size> & operator %=  (int);
    ccT_int <size> & operator >>= (int);
    ccT_int <size> & operator <<= (int);
    ccT_int <size> & operator ++  ();
    ccT_int <size> & operator ++  (int);
    ccT_int <size> & operator --  ();
    ccT_int <size> & operator --  (int);

    operator int () const;

private:

    bool _value [size];
};

/********************************************************************/

template <int size>
class ccT_uint : public cc_base
{
public:

    ccT_uint <size> ();
    ccT_uint <size> (int);

    ccT_uint <size> & operator =   (unsigned);
    ccT_uint <size> & operator +=  (unsigned);
    ccT_uint <size> & operator -=  (unsigned);
    ccT_uint <size> & operator *=  (unsigned);
    ccT_uint <size> & operator /=  (unsigned);
    ccT_uint <size> & operator &=  (unsigned);
    ccT_uint <size> & operator |=  (unsigned);
    ccT_uint <size> & operator ^=  (unsigned);
    ccT_uint <size> & operator %=  (unsigned);
    ccT_uint <size> & operator >>= (unsigned);
    ccT_uint <size> & operator <<= (unsigned);
    ccT_uint <size> & operator ++  ();
    ccT_uint <size> & operator ++  (int);
    ccT_uint <size> & operator --  ();
    ccT_uint <size> & operator --  (int);

    operator int () const;

private:

    bool _value [size];
};

/********************************************************************/

#define int1    ccT_int  <1>
#define int2    ccT_int  <2>
#define int3    ccT_int  <3>
#define int4    ccT_int  <4>
#define int5    ccT_int  <5>
#define int6    ccT_int  <6>
#define int7    ccT_int  <7>
#define int8    ccT_int  <8>
#define int9    ccT_int  <9>
#define int10   ccT_int  <10>
#define int11   ccT_int  <11>
#define int12   ccT_int  <12>
#define int13   ccT_int  <13>
#define int14   ccT_int  <14>
#define int15   ccT_int  <15>
#define int16   ccT_int  <16>
#define int17   ccT_int  <17>
#define int18   ccT_int  <18>
#define int19   ccT_int  <19>
#define int20   ccT_int  <20>
#define int21   ccT_int  <21>
#define int22   ccT_int  <22>
#define int23   ccT_int  <23>
#define int24   ccT_int  <24>
#define int25   ccT_int  <25>
#define int26   ccT_int  <26>
#define int27   ccT_int  <27>
#define int28   ccT_int  <28>
#define int29   ccT_int  <29>
#define int30   ccT_int  <30>
#define int31   ccT_int  <31>
#define int32   ccT_int  <32>
#define int33   ccT_int  <33>
#define int34   ccT_int  <34>
#define int35   ccT_int  <35>
#define int36   ccT_int  <36>
#define int37   ccT_int  <37>
#define int38   ccT_int  <38>
#define int39   ccT_int  <39>
#define int40   ccT_int  <40>
#define int41   ccT_int  <41>
#define int42   ccT_int  <42>
#define int43   ccT_int  <43>
#define int44   ccT_int  <44>
#define int45   ccT_int  <45>
#define int46   ccT_int  <46>
#define int47   ccT_int  <47>
#define int48   ccT_int  <48>
#define int49   ccT_int  <49>
#define int50   ccT_int  <50>
#define int51   ccT_int  <51>
#define int52   ccT_int  <52>
#define int53   ccT_int  <53>
#define int54   ccT_int  <54>
#define int55   ccT_int  <55>
#define int56   ccT_int  <56>
#define int57   ccT_int  <57>
#define int58   ccT_int  <58>
#define int59   ccT_int  <59>
#define int60   ccT_int  <60>
#define int61   ccT_int  <61>
#define int62   ccT_int  <62>
#define int63   ccT_int  <63>
#define int64   ccT_int  <64>
#define int65   ccT_int  <65>
#define int66   ccT_int  <66>
#define int67   ccT_int  <67>
#define int68   ccT_int  <68>
#define int69   ccT_int  <69>
#define int70   ccT_int  <70>
#define int71   ccT_int  <71>
#define int72   ccT_int  <72>
#define int73   ccT_int  <73>
#define int74   ccT_int  <74>
#define int75   ccT_int  <75>
#define int76   ccT_int  <76>
#define int77   ccT_int  <77>
#define int78   ccT_int  <78>
#define int79   ccT_int  <79>
#define int80   ccT_int  <80>
#define int81   ccT_int  <81>
#define int82   ccT_int  <82>
#define int83   ccT_int  <83>
#define int84   ccT_int  <84>
#define int85   ccT_int  <85>
#define int86   ccT_int  <86>
#define int87   ccT_int  <87>
#define int88   ccT_int  <88>
#define int89   ccT_int  <89>
#define int90   ccT_int  <90>
#define int91   ccT_int  <91>
#define int92   ccT_int  <92>
#define int93   ccT_int  <93>
#define int94   ccT_int  <94>
#define int95   ccT_int  <95>
#define int96   ccT_int  <96>
#define int97   ccT_int  <97>
#define int98   ccT_int  <98>
#define int99   ccT_int  <99>
#define int100  ccT_int  <100>
#define int101  ccT_int  <101>
#define int102  ccT_int  <102>
#define int103  ccT_int  <103>
#define int104  ccT_int  <104>
#define int105  ccT_int  <105>
#define int106  ccT_int  <106>
#define int107  ccT_int  <107>
#define int108  ccT_int  <108>
#define int109  ccT_int  <109>
#define int110  ccT_int  <110>
#define int111  ccT_int  <111>
#define int112  ccT_int  <112>
#define int113  ccT_int  <113>
#define int114  ccT_int  <114>
#define int115  ccT_int  <115>
#define int116  ccT_int  <116>
#define int117  ccT_int  <117>
#define int118  ccT_int  <118>
#define int119  ccT_int  <119>
#define int120  ccT_int  <120>
#define int121  ccT_int  <121>
#define int122  ccT_int  <122>
#define int123  ccT_int  <123>
#define int124  ccT_int  <124>
#define int125  ccT_int  <125>
#define int126  ccT_int  <126>
#define int127  ccT_int  <127>
#define int128  ccT_int  <128>
#define int129  ccT_int  <129>
#define int130  ccT_int  <130>
#define int131  ccT_int  <131>
#define int132  ccT_int  <132>
#define int133  ccT_int  <133>
#define int134  ccT_int  <134>
#define int135  ccT_int  <135>
#define int136  ccT_int  <136>
#define int137  ccT_int  <137>
#define int138  ccT_int  <138>
#define int139  ccT_int  <139>
#define int140  ccT_int  <140>
#define int141  ccT_int  <141>
#define int142  ccT_int  <142>
#define int143  ccT_int  <143>
#define int144  ccT_int  <144>
#define int145  ccT_int  <145>
#define int146  ccT_int  <146>
#define int147  ccT_int  <147>
#define int148  ccT_int  <148>
#define int149  ccT_int  <149>
#define int150  ccT_int  <150>
#define int151  ccT_int  <151>
#define int152  ccT_int  <152>
#define int153  ccT_int  <153>
#define int154  ccT_int  <154>
#define int155  ccT_int  <155>
#define int156  ccT_int  <156>
#define int157  ccT_int  <157>
#define int158  ccT_int  <158>
#define int159  ccT_int  <159>
#define int160  ccT_int  <160>
#define int161  ccT_int  <161>
#define int162  ccT_int  <162>
#define int163  ccT_int  <163>
#define int164  ccT_int  <164>
#define int165  ccT_int  <165>
#define int166  ccT_int  <166>
#define int167  ccT_int  <167>
#define int168  ccT_int  <168>
#define int169  ccT_int  <169>
#define int170  ccT_int  <170>
#define int171  ccT_int  <171>
#define int172  ccT_int  <172>
#define int173  ccT_int  <173>
#define int174  ccT_int  <174>
#define int175  ccT_int  <175>
#define int176  ccT_int  <176>
#define int177  ccT_int  <177>
#define int178  ccT_int  <178>
#define int179  ccT_int  <179>
#define int180  ccT_int  <180>
#define int181  ccT_int  <181>
#define int182  ccT_int  <182>
#define int183  ccT_int  <183>
#define int184  ccT_int  <184>
#define int185  ccT_int  <185>
#define int186  ccT_int  <186>
#define int187  ccT_int  <187>
#define int188  ccT_int  <188>
#define int189  ccT_int  <189>
#define int190  ccT_int  <190>
#define int191  ccT_int  <191>
#define int192  ccT_int  <192>
#define int193  ccT_int  <193>
#define int194  ccT_int  <194>
#define int195  ccT_int  <195>
#define int196  ccT_int  <196>
#define int197  ccT_int  <197>
#define int198  ccT_int  <198>
#define int199  ccT_int  <199>
#define int200  ccT_int  <200>
#define int201  ccT_int  <201>
#define int202  ccT_int  <202>
#define int203  ccT_int  <203>
#define int204  ccT_int  <204>
#define int205  ccT_int  <205>
#define int206  ccT_int  <206>
#define int207  ccT_int  <207>
#define int208  ccT_int  <208>
#define int209  ccT_int  <209>
#define int210  ccT_int  <210>
#define int211  ccT_int  <211>
#define int212  ccT_int  <212>
#define int213  ccT_int  <213>
#define int214  ccT_int  <214>
#define int215  ccT_int  <215>
#define int216  ccT_int  <216>
#define int217  ccT_int  <217>
#define int218  ccT_int  <218>
#define int219  ccT_int  <219>
#define int220  ccT_int  <220>
#define int221  ccT_int  <221>
#define int222  ccT_int  <222>
#define int223  ccT_int  <223>
#define int224  ccT_int  <224>
#define int225  ccT_int  <225>
#define int226  ccT_int  <226>
#define int227  ccT_int  <227>
#define int228  ccT_int  <228>
#define int229  ccT_int  <229>
#define int230  ccT_int  <230>
#define int231  ccT_int  <231>
#define int232  ccT_int  <232>
#define int233  ccT_int  <233>
#define int234  ccT_int  <234>
#define int235  ccT_int  <235>
#define int236  ccT_int  <236>
#define int237  ccT_int  <237>
#define int238  ccT_int  <238>
#define int239  ccT_int  <239>
#define int240  ccT_int  <240>
#define int241  ccT_int  <241>
#define int242  ccT_int  <242>
#define int243  ccT_int  <243>
#define int244  ccT_int  <244>
#define int245  ccT_int  <245>
#define int246  ccT_int  <246>
#define int247  ccT_int  <247>
#define int248  ccT_int  <248>
#define int249  ccT_int  <249>
#define int250  ccT_int  <250>
#define int251  ccT_int  <251>
#define int252  ccT_int  <252>
#define int253  ccT_int  <253>
#define int254  ccT_int  <254>
#define int255  ccT_int  <255>
#define int256  ccT_int  <256>
#define int257  ccT_int  <257>
#define int258  ccT_int  <258>
#define int259  ccT_int  <259>
#define int260  ccT_int  <260>
#define int261  ccT_int  <261>
#define int262  ccT_int  <262>
#define int263  ccT_int  <263>
#define int264  ccT_int  <264>
#define int265  ccT_int  <265>
#define int266  ccT_int  <266>
#define int267  ccT_int  <267>
#define int268  ccT_int  <268>
#define int269  ccT_int  <269>
#define int270  ccT_int  <270>
#define int271  ccT_int  <271>
#define int272  ccT_int  <272>
#define int273  ccT_int  <273>
#define int274  ccT_int  <274>
#define int275  ccT_int  <275>
#define int276  ccT_int  <276>
#define int277  ccT_int  <277>
#define int278  ccT_int  <278>
#define int279  ccT_int  <279>
#define int280  ccT_int  <280>
#define int281  ccT_int  <281>
#define int282  ccT_int  <282>
#define int283  ccT_int  <283>
#define int284  ccT_int  <284>
#define int285  ccT_int  <285>
#define int286  ccT_int  <286>
#define int287  ccT_int  <287>
#define int288  ccT_int  <288>
#define int289  ccT_int  <289>
#define int290  ccT_int  <290>
#define int291  ccT_int  <291>
#define int292  ccT_int  <292>
#define int293  ccT_int  <293>
#define int294  ccT_int  <294>
#define int295  ccT_int  <295>
#define int296  ccT_int  <296>
#define int297  ccT_int  <297>
#define int298  ccT_int  <298>
#define int299  ccT_int  <299>
#define int300  ccT_int  <300>
#define int301  ccT_int  <301>
#define int302  ccT_int  <302>
#define int303  ccT_int  <303>
#define int304  ccT_int  <304>
#define int305  ccT_int  <305>
#define int306  ccT_int  <306>
#define int307  ccT_int  <307>
#define int308  ccT_int  <308>
#define int309  ccT_int  <309>
#define int310  ccT_int  <310>
#define int311  ccT_int  <311>
#define int312  ccT_int  <312>
#define int313  ccT_int  <313>
#define int314  ccT_int  <314>
#define int315  ccT_int  <315>
#define int316  ccT_int  <316>
#define int317  ccT_int  <317>
#define int318  ccT_int  <318>
#define int319  ccT_int  <319>
#define int320  ccT_int  <320>
#define int321  ccT_int  <321>
#define int322  ccT_int  <322>
#define int323  ccT_int  <323>
#define int324  ccT_int  <324>
#define int325  ccT_int  <325>
#define int326  ccT_int  <326>
#define int327  ccT_int  <327>
#define int328  ccT_int  <328>
#define int329  ccT_int  <329>
#define int330  ccT_int  <330>
#define int331  ccT_int  <331>
#define int332  ccT_int  <332>
#define int333  ccT_int  <333>
#define int334  ccT_int  <334>
#define int335  ccT_int  <335>
#define int336  ccT_int  <336>
#define int337  ccT_int  <337>
#define int338  ccT_int  <338>
#define int339  ccT_int  <339>
#define int340  ccT_int  <340>
#define int341  ccT_int  <341>
#define int342  ccT_int  <342>
#define int343  ccT_int  <343>
#define int344  ccT_int  <344>
#define int345  ccT_int  <345>
#define int346  ccT_int  <346>
#define int347  ccT_int  <347>
#define int348  ccT_int  <348>
#define int349  ccT_int  <349>
#define int350  ccT_int  <350>
#define int351  ccT_int  <351>
#define int352  ccT_int  <352>
#define int353  ccT_int  <353>
#define int354  ccT_int  <354>
#define int355  ccT_int  <355>
#define int356  ccT_int  <356>
#define int357  ccT_int  <357>
#define int358  ccT_int  <358>
#define int359  ccT_int  <359>
#define int360  ccT_int  <360>
#define int361  ccT_int  <361>
#define int362  ccT_int  <362>
#define int363  ccT_int  <363>
#define int364  ccT_int  <364>
#define int365  ccT_int  <365>
#define int366  ccT_int  <366>
#define int367  ccT_int  <367>
#define int368  ccT_int  <368>
#define int369  ccT_int  <369>
#define int370  ccT_int  <370>
#define int371  ccT_int  <371>
#define int372  ccT_int  <372>
#define int373  ccT_int  <373>
#define int374  ccT_int  <374>
#define int375  ccT_int  <375>
#define int376  ccT_int  <376>
#define int377  ccT_int  <377>
#define int378  ccT_int  <378>
#define int379  ccT_int  <379>
#define int380  ccT_int  <380>
#define int381  ccT_int  <381>
#define int382  ccT_int  <382>
#define int383  ccT_int  <383>
#define int384  ccT_int  <384>
#define int385  ccT_int  <385>
#define int386  ccT_int  <386>
#define int387  ccT_int  <387>
#define int388  ccT_int  <388>
#define int389  ccT_int  <389>
#define int390  ccT_int  <390>
#define int391  ccT_int  <391>
#define int392  ccT_int  <392>
#define int393  ccT_int  <393>
#define int394  ccT_int  <394>
#define int395  ccT_int  <395>
#define int396  ccT_int  <396>
#define int397  ccT_int  <397>
#define int398  ccT_int  <398>
#define int399  ccT_int  <399>
#define int400  ccT_int  <400>
#define int401  ccT_int  <401>
#define int402  ccT_int  <402>
#define int403  ccT_int  <403>
#define int404  ccT_int  <404>
#define int405  ccT_int  <405>
#define int406  ccT_int  <406>
#define int407  ccT_int  <407>
#define int408  ccT_int  <408>
#define int409  ccT_int  <409>
#define int410  ccT_int  <410>
#define int411  ccT_int  <411>
#define int412  ccT_int  <412>
#define int413  ccT_int  <413>
#define int414  ccT_int  <414>
#define int415  ccT_int  <415>
#define int416  ccT_int  <416>
#define int417  ccT_int  <417>
#define int418  ccT_int  <418>
#define int419  ccT_int  <419>
#define int420  ccT_int  <420>
#define int421  ccT_int  <421>
#define int422  ccT_int  <422>
#define int423  ccT_int  <423>
#define int424  ccT_int  <424>
#define int425  ccT_int  <425>
#define int426  ccT_int  <426>
#define int427  ccT_int  <427>
#define int428  ccT_int  <428>
#define int429  ccT_int  <429>
#define int430  ccT_int  <430>
#define int431  ccT_int  <431>
#define int432  ccT_int  <432>
#define int433  ccT_int  <433>
#define int434  ccT_int  <434>
#define int435  ccT_int  <435>
#define int436  ccT_int  <436>
#define int437  ccT_int  <437>
#define int438  ccT_int  <438>
#define int439  ccT_int  <439>
#define int440  ccT_int  <440>
#define int441  ccT_int  <441>
#define int442  ccT_int  <442>
#define int443  ccT_int  <443>
#define int444  ccT_int  <444>
#define int445  ccT_int  <445>
#define int446  ccT_int  <446>
#define int447  ccT_int  <447>
#define int448  ccT_int  <448>
#define int449  ccT_int  <449>
#define int450  ccT_int  <450>
#define int451  ccT_int  <451>
#define int452  ccT_int  <452>
#define int453  ccT_int  <453>
#define int454  ccT_int  <454>
#define int455  ccT_int  <455>
#define int456  ccT_int  <456>
#define int457  ccT_int  <457>
#define int458  ccT_int  <458>
#define int459  ccT_int  <459>
#define int460  ccT_int  <460>
#define int461  ccT_int  <461>
#define int462  ccT_int  <462>
#define int463  ccT_int  <463>
#define int464  ccT_int  <464>
#define int465  ccT_int  <465>
#define int466  ccT_int  <466>
#define int467  ccT_int  <467>
#define int468  ccT_int  <468>
#define int469  ccT_int  <469>
#define int470  ccT_int  <470>
#define int471  ccT_int  <471>
#define int472  ccT_int  <472>
#define int473  ccT_int  <473>
#define int474  ccT_int  <474>
#define int475  ccT_int  <475>
#define int476  ccT_int  <476>
#define int477  ccT_int  <477>
#define int478  ccT_int  <478>
#define int479  ccT_int  <479>
#define int480  ccT_int  <480>
#define int481  ccT_int  <481>
#define int482  ccT_int  <482>
#define int483  ccT_int  <483>
#define int484  ccT_int  <484>
#define int485  ccT_int  <485>
#define int486  ccT_int  <486>
#define int487  ccT_int  <487>
#define int488  ccT_int  <488>
#define int489  ccT_int  <489>
#define int490  ccT_int  <490>
#define int491  ccT_int  <491>
#define int492  ccT_int  <492>
#define int493  ccT_int  <493>
#define int494  ccT_int  <494>
#define int495  ccT_int  <495>
#define int496  ccT_int  <496>
#define int497  ccT_int  <497>
#define int498  ccT_int  <498>
#define int499  ccT_int  <499>
#define int500  ccT_int  <500>
#define int501  ccT_int  <501>
#define int502  ccT_int  <502>
#define int503  ccT_int  <503>
#define int504  ccT_int  <504>
#define int505  ccT_int  <505>
#define int506  ccT_int  <506>
#define int507  ccT_int  <507>
#define int508  ccT_int  <508>
#define int509  ccT_int  <509>
#define int510  ccT_int  <510>
#define int511  ccT_int  <511>
#define int512  ccT_int  <512>

/********************************************************************/

#define uint1   ccT_uint <1>
#define uint2   ccT_uint <2>
#define uint3   ccT_uint <3>
#define uint4   ccT_uint <4>
#define uint5   ccT_uint <5>
#define uint6   ccT_uint <6>
#define uint7   ccT_uint <7>
#define uint8   ccT_uint <8>
#define uint9   ccT_uint <9>
#define uint10  ccT_uint <10>
#define uint11  ccT_uint <11>
#define uint12  ccT_uint <12>
#define uint13  ccT_uint <13>
#define uint14  ccT_uint <14>
#define uint15  ccT_uint <15>
#define uint16  ccT_uint <16>
#define uint17  ccT_uint <17>
#define uint18  ccT_uint <18>
#define uint19  ccT_uint <19>
#define uint20  ccT_uint <20>
#define uint21  ccT_uint <21>
#define uint22  ccT_uint <22>
#define uint23  ccT_uint <23>
#define uint24  ccT_uint <24>
#define uint25  ccT_uint <25>
#define uint26  ccT_uint <26>
#define uint27  ccT_uint <27>
#define uint28  ccT_uint <28>
#define uint29  ccT_uint <29>
#define uint30  ccT_uint <30>
#define uint31  ccT_uint <31>
#define uint32  ccT_uint <32>
#define uint33  ccT_uint <33>
#define uint34  ccT_uint <34>
#define uint35  ccT_uint <35>
#define uint36  ccT_uint <36>
#define uint37  ccT_uint <37>
#define uint38  ccT_uint <38>
#define uint39  ccT_uint <39>
#define uint40  ccT_uint <40>
#define uint41  ccT_uint <41>
#define uint42  ccT_uint <42>
#define uint43  ccT_uint <43>
#define uint44  ccT_uint <44>
#define uint45  ccT_uint <45>
#define uint46  ccT_uint <46>
#define uint47  ccT_uint <47>
#define uint48  ccT_uint <48>
#define uint49  ccT_uint <49>
#define uint50  ccT_uint <50>
#define uint51  ccT_uint <51>
#define uint52  ccT_uint <52>
#define uint53  ccT_uint <53>
#define uint54  ccT_uint <54>
#define uint55  ccT_uint <55>
#define uint56  ccT_uint <56>
#define uint57  ccT_uint <57>
#define uint58  ccT_uint <58>
#define uint59  ccT_uint <59>
#define uint60  ccT_uint <60>
#define uint61  ccT_uint <61>
#define uint62  ccT_uint <62>
#define uint63  ccT_uint <63>
#define uint64  ccT_uint <64>
#define uint65  ccT_uint <65>
#define uint66  ccT_uint <66>
#define uint67  ccT_uint <67>
#define uint68  ccT_uint <68>
#define uint69  ccT_uint <69>
#define uint70  ccT_uint <70>
#define uint71  ccT_uint <71>
#define uint72  ccT_uint <72>
#define uint73  ccT_uint <73>
#define uint74  ccT_uint <74>
#define uint75  ccT_uint <75>
#define uint76  ccT_uint <76>
#define uint77  ccT_uint <77>
#define uint78  ccT_uint <78>
#define uint79  ccT_uint <79>
#define uint80  ccT_uint <80>
#define uint81  ccT_uint <81>
#define uint82  ccT_uint <82>
#define uint83  ccT_uint <83>
#define uint84  ccT_uint <84>
#define uint85  ccT_uint <85>
#define uint86  ccT_uint <86>
#define uint87  ccT_uint <87>
#define uint88  ccT_uint <88>
#define uint89  ccT_uint <89>
#define uint90  ccT_uint <90>
#define uint91  ccT_uint <91>
#define uint92  ccT_uint <92>
#define uint93  ccT_uint <93>
#define uint94  ccT_uint <94>
#define uint95  ccT_uint <95>
#define uint96  ccT_uint <96>
#define uint97  ccT_uint <97>
#define uint98  ccT_uint <98>
#define uint99  ccT_uint <99>
#define uint100 ccT_uint <100>
#define uint101 ccT_uint <101>
#define uint102 ccT_uint <102>
#define uint103 ccT_uint <103>
#define uint104 ccT_uint <104>
#define uint105 ccT_uint <105>
#define uint106 ccT_uint <106>
#define uint107 ccT_uint <107>
#define uint108 ccT_uint <108>
#define uint109 ccT_uint <109>
#define uint110 ccT_uint <110>
#define uint111 ccT_uint <111>
#define uint112 ccT_uint <112>
#define uint113 ccT_uint <113>
#define uint114 ccT_uint <114>
#define uint115 ccT_uint <115>
#define uint116 ccT_uint <116>
#define uint117 ccT_uint <117>
#define uint118 ccT_uint <118>
#define uint119 ccT_uint <119>
#define uint120 ccT_uint <120>
#define uint121 ccT_uint <121>
#define uint122 ccT_uint <122>
#define uint123 ccT_uint <123>
#define uint124 ccT_uint <124>
#define uint125 ccT_uint <125>
#define uint126 ccT_uint <126>
#define uint127 ccT_uint <127>
#define uint128 ccT_uint <128>
#define uint129 ccT_uint <129>
#define uint130 ccT_uint <130>
#define uint131 ccT_uint <131>
#define uint132 ccT_uint <132>
#define uint133 ccT_uint <133>
#define uint134 ccT_uint <134>
#define uint135 ccT_uint <135>
#define uint136 ccT_uint <136>
#define uint137 ccT_uint <137>
#define uint138 ccT_uint <138>
#define uint139 ccT_uint <139>
#define uint140 ccT_uint <140>
#define uint141 ccT_uint <141>
#define uint142 ccT_uint <142>
#define uint143 ccT_uint <143>
#define uint144 ccT_uint <144>
#define uint145 ccT_uint <145>
#define uint146 ccT_uint <146>
#define uint147 ccT_uint <147>
#define uint148 ccT_uint <148>
#define uint149 ccT_uint <149>
#define uint150 ccT_uint <150>
#define uint151 ccT_uint <151>
#define uint152 ccT_uint <152>
#define uint153 ccT_uint <153>
#define uint154 ccT_uint <154>
#define uint155 ccT_uint <155>
#define uint156 ccT_uint <156>
#define uint157 ccT_uint <157>
#define uint158 ccT_uint <158>
#define uint159 ccT_uint <159>
#define uint160 ccT_uint <160>
#define uint161 ccT_uint <161>
#define uint162 ccT_uint <162>
#define uint163 ccT_uint <163>
#define uint164 ccT_uint <164>
#define uint165 ccT_uint <165>
#define uint166 ccT_uint <166>
#define uint167 ccT_uint <167>
#define uint168 ccT_uint <168>
#define uint169 ccT_uint <169>
#define uint170 ccT_uint <170>
#define uint171 ccT_uint <171>
#define uint172 ccT_uint <172>
#define uint173 ccT_uint <173>
#define uint174 ccT_uint <174>
#define uint175 ccT_uint <175>
#define uint176 ccT_uint <176>
#define uint177 ccT_uint <177>
#define uint178 ccT_uint <178>
#define uint179 ccT_uint <179>
#define uint180 ccT_uint <180>
#define uint181 ccT_uint <181>
#define uint182 ccT_uint <182>
#define uint183 ccT_uint <183>
#define uint184 ccT_uint <184>
#define uint185 ccT_uint <185>
#define uint186 ccT_uint <186>
#define uint187 ccT_uint <187>
#define uint188 ccT_uint <188>
#define uint189 ccT_uint <189>
#define uint190 ccT_uint <190>
#define uint191 ccT_uint <191>
#define uint192 ccT_uint <192>
#define uint193 ccT_uint <193>
#define uint194 ccT_uint <194>
#define uint195 ccT_uint <195>
#define uint196 ccT_uint <196>
#define uint197 ccT_uint <197>
#define uint198 ccT_uint <198>
#define uint199 ccT_uint <199>
#define uint200 ccT_uint <200>
#define uint201 ccT_uint <201>
#define uint202 ccT_uint <202>
#define uint203 ccT_uint <203>
#define uint204 ccT_uint <204>
#define uint205 ccT_uint <205>
#define uint206 ccT_uint <206>
#define uint207 ccT_uint <207>
#define uint208 ccT_uint <208>
#define uint209 ccT_uint <209>
#define uint210 ccT_uint <210>
#define uint211 ccT_uint <211>
#define uint212 ccT_uint <212>
#define uint213 ccT_uint <213>
#define uint214 ccT_uint <214>
#define uint215 ccT_uint <215>
#define uint216 ccT_uint <216>
#define uint217 ccT_uint <217>
#define uint218 ccT_uint <218>
#define uint219 ccT_uint <219>
#define uint220 ccT_uint <220>
#define uint221 ccT_uint <221>
#define uint222 ccT_uint <222>
#define uint223 ccT_uint <223>
#define uint224 ccT_uint <224>
#define uint225 ccT_uint <225>
#define uint226 ccT_uint <226>
#define uint227 ccT_uint <227>
#define uint228 ccT_uint <228>
#define uint229 ccT_uint <229>
#define uint230 ccT_uint <230>
#define uint231 ccT_uint <231>
#define uint232 ccT_uint <232>
#define uint233 ccT_uint <233>
#define uint234 ccT_uint <234>
#define uint235 ccT_uint <235>
#define uint236 ccT_uint <236>
#define uint237 ccT_uint <237>
#define uint238 ccT_uint <238>
#define uint239 ccT_uint <239>
#define uint240 ccT_uint <240>
#define uint241 ccT_uint <241>
#define uint242 ccT_uint <242>
#define uint243 ccT_uint <243>
#define uint244 ccT_uint <244>
#define uint245 ccT_uint <245>
#define uint246 ccT_uint <246>
#define uint247 ccT_uint <247>
#define uint248 ccT_uint <248>
#define uint249 ccT_uint <249>
#define uint250 ccT_uint <250>
#define uint251 ccT_uint <251>
#define uint252 ccT_uint <252>
#define uint253 ccT_uint <253>
#define uint254 ccT_uint <254>
#define uint255 ccT_uint <255>
#define uint256 ccT_uint <256>
#define uint257 ccT_uint <257>
#define uint258 ccT_uint <258>
#define uint259 ccT_uint <259>
#define uint260 ccT_uint <260>
#define uint261 ccT_uint <261>
#define uint262 ccT_uint <262>
#define uint263 ccT_uint <263>
#define uint264 ccT_uint <264>
#define uint265 ccT_uint <265>
#define uint266 ccT_uint <266>
#define uint267 ccT_uint <267>
#define uint268 ccT_uint <268>
#define uint269 ccT_uint <269>
#define uint270 ccT_uint <270>
#define uint271 ccT_uint <271>
#define uint272 ccT_uint <272>
#define uint273 ccT_uint <273>
#define uint274 ccT_uint <274>
#define uint275 ccT_uint <275>
#define uint276 ccT_uint <276>
#define uint277 ccT_uint <277>
#define uint278 ccT_uint <278>
#define uint279 ccT_uint <279>
#define uint280 ccT_uint <280>
#define uint281 ccT_uint <281>
#define uint282 ccT_uint <282>
#define uint283 ccT_uint <283>
#define uint284 ccT_uint <284>
#define uint285 ccT_uint <285>
#define uint286 ccT_uint <286>
#define uint287 ccT_uint <287>
#define uint288 ccT_uint <288>
#define uint289 ccT_uint <289>
#define uint290 ccT_uint <290>
#define uint291 ccT_uint <291>
#define uint292 ccT_uint <292>
#define uint293 ccT_uint <293>
#define uint294 ccT_uint <294>
#define uint295 ccT_uint <295>
#define uint296 ccT_uint <296>
#define uint297 ccT_uint <297>
#define uint298 ccT_uint <298>
#define uint299 ccT_uint <299>
#define uint300 ccT_uint <300>
#define uint301 ccT_uint <301>
#define uint302 ccT_uint <302>
#define uint303 ccT_uint <303>
#define uint304 ccT_uint <304>
#define uint305 ccT_uint <305>
#define uint306 ccT_uint <306>
#define uint307 ccT_uint <307>
#define uint308 ccT_uint <308>
#define uint309 ccT_uint <309>
#define uint310 ccT_uint <310>
#define uint311 ccT_uint <311>
#define uint312 ccT_uint <312>
#define uint313 ccT_uint <313>
#define uint314 ccT_uint <314>
#define uint315 ccT_uint <315>
#define uint316 ccT_uint <316>
#define uint317 ccT_uint <317>
#define uint318 ccT_uint <318>
#define uint319 ccT_uint <319>
#define uint320 ccT_uint <320>
#define uint321 ccT_uint <321>
#define uint322 ccT_uint <322>
#define uint323 ccT_uint <323>
#define uint324 ccT_uint <324>
#define uint325 ccT_uint <325>
#define uint326 ccT_uint <326>
#define uint327 ccT_uint <327>
#define uint328 ccT_uint <328>
#define uint329 ccT_uint <329>
#define uint330 ccT_uint <330>
#define uint331 ccT_uint <331>
#define uint332 ccT_uint <332>
#define uint333 ccT_uint <333>
#define uint334 ccT_uint <334>
#define uint335 ccT_uint <335>
#define uint336 ccT_uint <336>
#define uint337 ccT_uint <337>
#define uint338 ccT_uint <338>
#define uint339 ccT_uint <339>
#define uint340 ccT_uint <340>
#define uint341 ccT_uint <341>
#define uint342 ccT_uint <342>
#define uint343 ccT_uint <343>
#define uint344 ccT_uint <344>
#define uint345 ccT_uint <345>
#define uint346 ccT_uint <346>
#define uint347 ccT_uint <347>
#define uint348 ccT_uint <348>
#define uint349 ccT_uint <349>
#define uint350 ccT_uint <350>
#define uint351 ccT_uint <351>
#define uint352 ccT_uint <352>
#define uint353 ccT_uint <353>
#define uint354 ccT_uint <354>
#define uint355 ccT_uint <355>
#define uint356 ccT_uint <356>
#define uint357 ccT_uint <357>
#define uint358 ccT_uint <358>
#define uint359 ccT_uint <359>
#define uint360 ccT_uint <360>
#define uint361 ccT_uint <361>
#define uint362 ccT_uint <362>
#define uint363 ccT_uint <363>
#define uint364 ccT_uint <364>
#define uint365 ccT_uint <365>
#define uint366 ccT_uint <366>
#define uint367 ccT_uint <367>
#define uint368 ccT_uint <368>
#define uint369 ccT_uint <369>
#define uint370 ccT_uint <370>
#define uint371 ccT_uint <371>
#define uint372 ccT_uint <372>
#define uint373 ccT_uint <373>
#define uint374 ccT_uint <374>
#define uint375 ccT_uint <375>
#define uint376 ccT_uint <376>
#define uint377 ccT_uint <377>
#define uint378 ccT_uint <378>
#define uint379 ccT_uint <379>
#define uint380 ccT_uint <380>
#define uint381 ccT_uint <381>
#define uint382 ccT_uint <382>
#define uint383 ccT_uint <383>
#define uint384 ccT_uint <384>
#define uint385 ccT_uint <385>
#define uint386 ccT_uint <386>
#define uint387 ccT_uint <387>
#define uint388 ccT_uint <388>
#define uint389 ccT_uint <389>
#define uint390 ccT_uint <390>
#define uint391 ccT_uint <391>
#define uint392 ccT_uint <392>
#define uint393 ccT_uint <393>
#define uint394 ccT_uint <394>
#define uint395 ccT_uint <395>
#define uint396 ccT_uint <396>
#define uint397 ccT_uint <397>
#define uint398 ccT_uint <398>
#define uint399 ccT_uint <399>
#define uint400 ccT_uint <400>
#define uint401 ccT_uint <401>
#define uint402 ccT_uint <402>
#define uint403 ccT_uint <403>
#define uint404 ccT_uint <404>
#define uint405 ccT_uint <405>
#define uint406 ccT_uint <406>
#define uint407 ccT_uint <407>
#define uint408 ccT_uint <408>
#define uint409 ccT_uint <409>
#define uint410 ccT_uint <410>
#define uint411 ccT_uint <411>
#define uint412 ccT_uint <412>
#define uint413 ccT_uint <413>
#define uint414 ccT_uint <414>
#define uint415 ccT_uint <415>
#define uint416 ccT_uint <416>
#define uint417 ccT_uint <417>
#define uint418 ccT_uint <418>
#define uint419 ccT_uint <419>
#define uint420 ccT_uint <420>
#define uint421 ccT_uint <421>
#define uint422 ccT_uint <422>
#define uint423 ccT_uint <423>
#define uint424 ccT_uint <424>
#define uint425 ccT_uint <425>
#define uint426 ccT_uint <426>
#define uint427 ccT_uint <427>
#define uint428 ccT_uint <428>
#define uint429 ccT_uint <429>
#define uint430 ccT_uint <430>
#define uint431 ccT_uint <431>
#define uint432 ccT_uint <432>
#define uint433 ccT_uint <433>
#define uint434 ccT_uint <434>
#define uint435 ccT_uint <435>
#define uint436 ccT_uint <436>
#define uint437 ccT_uint <437>
#define uint438 ccT_uint <438>
#define uint439 ccT_uint <439>
#define uint440 ccT_uint <440>
#define uint441 ccT_uint <441>
#define uint442 ccT_uint <442>
#define uint443 ccT_uint <443>
#define uint444 ccT_uint <444>
#define uint445 ccT_uint <445>
#define uint446 ccT_uint <446>
#define uint447 ccT_uint <447>
#define uint448 ccT_uint <448>
#define uint449 ccT_uint <449>
#define uint450 ccT_uint <450>
#define uint451 ccT_uint <451>
#define uint452 ccT_uint <452>
#define uint453 ccT_uint <453>
#define uint454 ccT_uint <454>
#define uint455 ccT_uint <455>
#define uint456 ccT_uint <456>
#define uint457 ccT_uint <457>
#define uint458 ccT_uint <458>
#define uint459 ccT_uint <459>
#define uint460 ccT_uint <460>
#define uint461 ccT_uint <461>
#define uint462 ccT_uint <462>
#define uint463 ccT_uint <463>
#define uint464 ccT_uint <464>
#define uint465 ccT_uint <465>
#define uint466 ccT_uint <466>
#define uint467 ccT_uint <467>
#define uint468 ccT_uint <468>
#define uint469 ccT_uint <469>
#define uint470 ccT_uint <470>
#define uint471 ccT_uint <471>
#define uint472 ccT_uint <472>
#define uint473 ccT_uint <473>
#define uint474 ccT_uint <474>
#define uint475 ccT_uint <475>
#define uint476 ccT_uint <476>
#define uint477 ccT_uint <477>
#define uint478 ccT_uint <478>
#define uint479 ccT_uint <479>
#define uint480 ccT_uint <480>
#define uint481 ccT_uint <481>
#define uint482 ccT_uint <482>
#define uint483 ccT_uint <483>
#define uint484 ccT_uint <484>
#define uint485 ccT_uint <485>
#define uint486 ccT_uint <486>
#define uint487 ccT_uint <487>
#define uint488 ccT_uint <488>
#define uint489 ccT_uint <489>
#define uint490 ccT_uint <490>
#define uint491 ccT_uint <491>
#define uint492 ccT_uint <492>
#define uint493 ccT_uint <493>
#define uint494 ccT_uint <494>
#define uint495 ccT_uint <495>
#define uint496 ccT_uint <496>
#define uint497 ccT_uint <497>
#define uint498 ccT_uint <498>
#define uint499 ccT_uint <499>
#define uint500 ccT_uint <500>
#define uint501 ccT_uint <501>
#define uint502 ccT_uint <502>
#define uint503 ccT_uint <503>
#define uint504 ccT_uint <504>
#define uint505 ccT_uint <505>
#define uint506 ccT_uint <506>
#define uint507 ccT_uint <507>
#define uint508 ccT_uint <508>
#define uint509 ccT_uint <509>
#define uint510 ccT_uint <510>
#define uint511 ccT_uint <511>
#define uint512 ccT_uint <512>

#endif  /*  #ifdef __CYCLEC_UINT_TEMPLATE_IMPLEMENTATION__  */

/********************************************************************/

#ifdef __CYCLEC_UINT_TEMPLATE_IMPLEMENTATION__

void _clevel_set_bit_slice (cc_base &, int, int, int);

#define _DEFINE_CYCLEC_CAST_INT(size)               \
    int##size _clevel_cv_int##size (unsigned i);    \
    int##size _clevel_cv_int##size (int i);

#define _DEFINE_CYCLEC_CAST_UINT(size)              \
    uint##size _clevel_cv_uint##size (unsigned i);  \
    uint##size _clevel_cv_uint##size (int i);

/********************************************************************/

#else  /*  #ifdef __CYCLEC_UINT_TEMPLATE_IMPLEMENTATION__  */

#define _DEFINE_CYCLEC_CAST_INT(size)               \
    typedef int int##size;                          \
    int##size _clevel_cv_int##size (unsigned i);    \
    int##size _clevel_cv_int##size (int i);

#define _DEFINE_CYCLEC_CAST_UINT(size)              \
    typedef unsigned uint##size;                    \
    typedef unsigned unsigned##size;                \
    uint##size _clevel_cv_uint##size (unsigned i);  \
    uint##size _clevel_cv_uint##size (int i);

#endif  /*  #ifdef __CYCLEC_UINT_TEMPLATE_IMPLEMENTATION__  */

/********************************************************************/

#else  /*  #ifdef __cplusplus  */

#define _DEFINE_CYCLEC_CAST_INT(size)       \
    int##size _clevel_cv_int##size (int);

#define _DEFINE_CYCLEC_CAST_UINT(size)      \
    uint##size _clevel_cv_uint##size (int);

#endif  /*  #ifdef __cplusplus  */

/********************************************************************/

_DEFINE_CYCLEC_CAST_INT(1)
#define cv_int1 _clevel_cv_int1
_DEFINE_CYCLEC_CAST_INT(2)
#define cv_int2 _clevel_cv_int2
_DEFINE_CYCLEC_CAST_INT(3)
#define cv_int3 _clevel_cv_int3
_DEFINE_CYCLEC_CAST_INT(4)
#define cv_int4 _clevel_cv_int4
_DEFINE_CYCLEC_CAST_INT(5)
#define cv_int5 _clevel_cv_int5
_DEFINE_CYCLEC_CAST_INT(6)
#define cv_int6 _clevel_cv_int6
_DEFINE_CYCLEC_CAST_INT(7)
#define cv_int7 _clevel_cv_int7
_DEFINE_CYCLEC_CAST_INT(8)
#define cv_int8 _clevel_cv_int8
_DEFINE_CYCLEC_CAST_INT(9)
#define cv_int9 _clevel_cv_int9
_DEFINE_CYCLEC_CAST_INT(10)
#define cv_int10 _clevel_cv_int10
_DEFINE_CYCLEC_CAST_INT(11)
#define cv_int11 _clevel_cv_int11
_DEFINE_CYCLEC_CAST_INT(12)
#define cv_int12 _clevel_cv_int12
_DEFINE_CYCLEC_CAST_INT(13)
#define cv_int13 _clevel_cv_int13
_DEFINE_CYCLEC_CAST_INT(14)
#define cv_int14 _clevel_cv_int14
_DEFINE_CYCLEC_CAST_INT(15)
#define cv_int15 _clevel_cv_int15
_DEFINE_CYCLEC_CAST_INT(16)
#define cv_int16 _clevel_cv_int16
_DEFINE_CYCLEC_CAST_INT(17)
#define cv_int17 _clevel_cv_int17
_DEFINE_CYCLEC_CAST_INT(18)
#define cv_int18 _clevel_cv_int18
_DEFINE_CYCLEC_CAST_INT(19)
#define cv_int19 _clevel_cv_int19
_DEFINE_CYCLEC_CAST_INT(20)
#define cv_int20 _clevel_cv_int20
_DEFINE_CYCLEC_CAST_INT(21)
#define cv_int21 _clevel_cv_int21
_DEFINE_CYCLEC_CAST_INT(22)
#define cv_int22 _clevel_cv_int22
_DEFINE_CYCLEC_CAST_INT(23)
#define cv_int23 _clevel_cv_int23
_DEFINE_CYCLEC_CAST_INT(24)
#define cv_int24 _clevel_cv_int24
_DEFINE_CYCLEC_CAST_INT(25)
#define cv_int25 _clevel_cv_int25
_DEFINE_CYCLEC_CAST_INT(26)
#define cv_int26 _clevel_cv_int26
_DEFINE_CYCLEC_CAST_INT(27)
#define cv_int27 _clevel_cv_int27
_DEFINE_CYCLEC_CAST_INT(28)
#define cv_int28 _clevel_cv_int28
_DEFINE_CYCLEC_CAST_INT(29)
#define cv_int29 _clevel_cv_int29
_DEFINE_CYCLEC_CAST_INT(30)
#define cv_int30 _clevel_cv_int30
_DEFINE_CYCLEC_CAST_INT(31)
#define cv_int31 _clevel_cv_int31
_DEFINE_CYCLEC_CAST_INT(32)
#define cv_int32 _clevel_cv_int32
_DEFINE_CYCLEC_CAST_INT(33)
#define cv_int33 _clevel_cv_int33
_DEFINE_CYCLEC_CAST_INT(34)
#define cv_int34 _clevel_cv_int34
_DEFINE_CYCLEC_CAST_INT(35)
#define cv_int35 _clevel_cv_int35
_DEFINE_CYCLEC_CAST_INT(36)
#define cv_int36 _clevel_cv_int36
_DEFINE_CYCLEC_CAST_INT(37)
#define cv_int37 _clevel_cv_int37
_DEFINE_CYCLEC_CAST_INT(38)
#define cv_int38 _clevel_cv_int38
_DEFINE_CYCLEC_CAST_INT(39)
#define cv_int39 _clevel_cv_int39
_DEFINE_CYCLEC_CAST_INT(40)
#define cv_int40 _clevel_cv_int40
_DEFINE_CYCLEC_CAST_INT(41)
#define cv_int41 _clevel_cv_int41
_DEFINE_CYCLEC_CAST_INT(42)
#define cv_int42 _clevel_cv_int42
_DEFINE_CYCLEC_CAST_INT(43)
#define cv_int43 _clevel_cv_int43
_DEFINE_CYCLEC_CAST_INT(44)
#define cv_int44 _clevel_cv_int44
_DEFINE_CYCLEC_CAST_INT(45)
#define cv_int45 _clevel_cv_int45
_DEFINE_CYCLEC_CAST_INT(46)
#define cv_int46 _clevel_cv_int46
_DEFINE_CYCLEC_CAST_INT(47)
#define cv_int47 _clevel_cv_int47
_DEFINE_CYCLEC_CAST_INT(48)
#define cv_int48 _clevel_cv_int48
_DEFINE_CYCLEC_CAST_INT(49)
#define cv_int49 _clevel_cv_int49
_DEFINE_CYCLEC_CAST_INT(50)
#define cv_int50 _clevel_cv_int50
_DEFINE_CYCLEC_CAST_INT(51)
#define cv_int51 _clevel_cv_int51
_DEFINE_CYCLEC_CAST_INT(52)
#define cv_int52 _clevel_cv_int52
_DEFINE_CYCLEC_CAST_INT(53)
#define cv_int53 _clevel_cv_int53
_DEFINE_CYCLEC_CAST_INT(54)
#define cv_int54 _clevel_cv_int54
_DEFINE_CYCLEC_CAST_INT(55)
#define cv_int55 _clevel_cv_int55
_DEFINE_CYCLEC_CAST_INT(56)
#define cv_int56 _clevel_cv_int56
_DEFINE_CYCLEC_CAST_INT(57)
#define cv_int57 _clevel_cv_int57
_DEFINE_CYCLEC_CAST_INT(58)
#define cv_int58 _clevel_cv_int58
_DEFINE_CYCLEC_CAST_INT(59)
#define cv_int59 _clevel_cv_int59
_DEFINE_CYCLEC_CAST_INT(60)
#define cv_int60 _clevel_cv_int60
_DEFINE_CYCLEC_CAST_INT(61)
#define cv_int61 _clevel_cv_int61
_DEFINE_CYCLEC_CAST_INT(62)
#define cv_int62 _clevel_cv_int62
_DEFINE_CYCLEC_CAST_INT(63)
#define cv_int63 _clevel_cv_int63
_DEFINE_CYCLEC_CAST_INT(64)
#define cv_int64 _clevel_cv_int64

/********************************************************************/

_DEFINE_CYCLEC_CAST_UINT(1)
#define cv_uint1 _clevel_cv_uint1
_DEFINE_CYCLEC_CAST_UINT(2)
#define cv_uint2 _clevel_cv_uint2
_DEFINE_CYCLEC_CAST_UINT(3)
#define cv_uint3 _clevel_cv_uint3
_DEFINE_CYCLEC_CAST_UINT(4)
#define cv_uint4 _clevel_cv_uint4
_DEFINE_CYCLEC_CAST_UINT(5)
#define cv_uint5 _clevel_cv_uint5
_DEFINE_CYCLEC_CAST_UINT(6)
#define cv_uint6 _clevel_cv_uint6
_DEFINE_CYCLEC_CAST_UINT(7)
#define cv_uint7 _clevel_cv_uint7
_DEFINE_CYCLEC_CAST_UINT(8)
#define cv_uint8 _clevel_cv_uint8
_DEFINE_CYCLEC_CAST_UINT(9)
#define cv_uint9 _clevel_cv_uint9
_DEFINE_CYCLEC_CAST_UINT(10)
#define cv_uint10 _clevel_cv_uint10
_DEFINE_CYCLEC_CAST_UINT(11)
#define cv_uint11 _clevel_cv_uint11
_DEFINE_CYCLEC_CAST_UINT(12)
#define cv_uint12 _clevel_cv_uint12
_DEFINE_CYCLEC_CAST_UINT(13)
#define cv_uint13 _clevel_cv_uint13
_DEFINE_CYCLEC_CAST_UINT(14)
#define cv_uint14 _clevel_cv_uint14
_DEFINE_CYCLEC_CAST_UINT(15)
#define cv_uint15 _clevel_cv_uint15
_DEFINE_CYCLEC_CAST_UINT(16)
#define cv_uint16 _clevel_cv_uint16
_DEFINE_CYCLEC_CAST_UINT(17)
#define cv_uint17 _clevel_cv_uint17
_DEFINE_CYCLEC_CAST_UINT(18)
#define cv_uint18 _clevel_cv_uint18
_DEFINE_CYCLEC_CAST_UINT(19)
#define cv_uint19 _clevel_cv_uint19
_DEFINE_CYCLEC_CAST_UINT(20)
#define cv_uint20 _clevel_cv_uint20
_DEFINE_CYCLEC_CAST_UINT(21)
#define cv_uint21 _clevel_cv_uint21
_DEFINE_CYCLEC_CAST_UINT(22)
#define cv_uint22 _clevel_cv_uint22
_DEFINE_CYCLEC_CAST_UINT(23)
#define cv_uint23 _clevel_cv_uint23
_DEFINE_CYCLEC_CAST_UINT(24)
#define cv_uint24 _clevel_cv_uint24
_DEFINE_CYCLEC_CAST_UINT(25)
#define cv_uint25 _clevel_cv_uint25
_DEFINE_CYCLEC_CAST_UINT(26)
#define cv_uint26 _clevel_cv_uint26
_DEFINE_CYCLEC_CAST_UINT(27)
#define cv_uint27 _clevel_cv_uint27
_DEFINE_CYCLEC_CAST_UINT(28)
#define cv_uint28 _clevel_cv_uint28
_DEFINE_CYCLEC_CAST_UINT(29)
#define cv_uint29 _clevel_cv_uint29
_DEFINE_CYCLEC_CAST_UINT(30)
#define cv_uint30 _clevel_cv_uint30
_DEFINE_CYCLEC_CAST_UINT(31)
#define cv_uint31 _clevel_cv_uint31
_DEFINE_CYCLEC_CAST_UINT(32)
#define cv_uint32 _clevel_cv_uint32
_DEFINE_CYCLEC_CAST_UINT(33)
#define cv_uint33 _clevel_cv_uint33
_DEFINE_CYCLEC_CAST_UINT(34)
#define cv_uint34 _clevel_cv_uint34
_DEFINE_CYCLEC_CAST_UINT(35)
#define cv_uint35 _clevel_cv_uint35
_DEFINE_CYCLEC_CAST_UINT(36)
#define cv_uint36 _clevel_cv_uint36
_DEFINE_CYCLEC_CAST_UINT(37)
#define cv_uint37 _clevel_cv_uint37
_DEFINE_CYCLEC_CAST_UINT(38)
#define cv_uint38 _clevel_cv_uint38
_DEFINE_CYCLEC_CAST_UINT(39)
#define cv_uint39 _clevel_cv_uint39
_DEFINE_CYCLEC_CAST_UINT(40)
#define cv_uint40 _clevel_cv_uint40
_DEFINE_CYCLEC_CAST_UINT(41)
#define cv_uint41 _clevel_cv_uint41
_DEFINE_CYCLEC_CAST_UINT(42)
#define cv_uint42 _clevel_cv_uint42
_DEFINE_CYCLEC_CAST_UINT(43)
#define cv_uint43 _clevel_cv_uint43
_DEFINE_CYCLEC_CAST_UINT(44)
#define cv_uint44 _clevel_cv_uint44
_DEFINE_CYCLEC_CAST_UINT(45)
#define cv_uint45 _clevel_cv_uint45
_DEFINE_CYCLEC_CAST_UINT(46)
#define cv_uint46 _clevel_cv_uint46
_DEFINE_CYCLEC_CAST_UINT(47)
#define cv_uint47 _clevel_cv_uint47
_DEFINE_CYCLEC_CAST_UINT(48)
#define cv_uint48 _clevel_cv_uint48
_DEFINE_CYCLEC_CAST_UINT(49)
#define cv_uint49 _clevel_cv_uint49
_DEFINE_CYCLEC_CAST_UINT(50)
#define cv_uint50 _clevel_cv_uint50
_DEFINE_CYCLEC_CAST_UINT(51)
#define cv_uint51 _clevel_cv_uint51
_DEFINE_CYCLEC_CAST_UINT(52)
#define cv_uint52 _clevel_cv_uint52
_DEFINE_CYCLEC_CAST_UINT(53)
#define cv_uint53 _clevel_cv_uint53
_DEFINE_CYCLEC_CAST_UINT(54)
#define cv_uint54 _clevel_cv_uint54
_DEFINE_CYCLEC_CAST_UINT(55)
#define cv_uint55 _clevel_cv_uint55
_DEFINE_CYCLEC_CAST_UINT(56)
#define cv_uint56 _clevel_cv_uint56
_DEFINE_CYCLEC_CAST_UINT(57)
#define cv_uint57 _clevel_cv_uint57
_DEFINE_CYCLEC_CAST_UINT(58)
#define cv_uint58 _clevel_cv_uint58
_DEFINE_CYCLEC_CAST_UINT(59)
#define cv_uint59 _clevel_cv_uint59
_DEFINE_CYCLEC_CAST_UINT(60)
#define cv_uint60 _clevel_cv_uint60
_DEFINE_CYCLEC_CAST_UINT(61)
#define cv_uint61 _clevel_cv_uint61
_DEFINE_CYCLEC_CAST_UINT(62)
#define cv_uint62 _clevel_cv_uint62
_DEFINE_CYCLEC_CAST_UINT(63)
#define cv_uint63 _clevel_cv_uint63
_DEFINE_CYCLEC_CAST_UINT(64)
#define cv_uint64 _clevel_cv_uint64

#endif  /*  #ifdef __CYCLEC_SIMULATION__  */

/********************************************************************/

#ifdef __SUPPORT_GREATER_THEN_64_BITS_INTEGER_TYPES__
#include "clevel64.h"
#endif

/********************************************************************/

#ifdef __CYCLEC_TRANSLATION__

#ifdef __cplusplus

int verilog (char * string);
int VERILOG (char * string);
int Verilog (char * string);

int vhdl (char * string);
int VHDL (char * string);
int Vhdl (char * string);

#endif  /*  #ifdef __cplusplus  */

#else  /*  #ifdef __CYCLEC_TRANSLATION__  */

#define verilog(string)
#define VERILOG(string)
#define Verilog(string)

#define vhdl(string)
#define VHDL(string)
#define Vhdl(string)

#endif  /*  #ifdef __CYCLEC_TRANSLATION__  */

/*********************************************************************
*                                                                    *
*           cc_clock                                                 *
*                                                                    *
*********************************************************************/

#define IIIIIIOOOsizeOOO(high_bit, low_bit)                          \
    (~ 0 << ((high_bit) - (low_bit) + 1))

#define IIIIIIOOOsizeOOO_64(high_bit, low_bit)                       \
    (~ (unsigned _int64)0 << ((high_bit) - (low_bit) + 1))

#define OOOOOOIIIsizeIII(high_bit, low_bit)                          \
    (~ IIIIIIOOOsizeOOO (high_bit, low_bit))

#define OOOOOOIIIsizeIII_64(high_bit, low_bit)                       \
    (~ IIIIIIOOOsizeOOO_64 (high_bit, low_bit))

#define SLICE_MASK(high_bit, low_bit)                                \
    (OOOOOOIIIsizeIII (high_bit, low_bit) << (low_bit))

#define SLICE_MASK_64(high_bit, low_bit)                             \
    (OOOOOOIIIsizeIII_64 (high_bit, low_bit) << (low_bit))

/********************************************************************/

#define GET_SLICE_USING_SHIFTS_AND_MASKS(expression, high_bit, low_bit)       \
    (  (expression) >> (low_bit)                                      \
       & OOOOOOIIIsizeIII (high_bit, low_bit) )

#define GET_SLICE_USING_SHIFTS_AND_MASKS_64(expression, high_bit, low_bit)    \
    (  (expression) >> (low_bit)                                      \
       & OOOOOOIIIsizeIII_64 (high_bit, low_bit) )

#define SET_SLICE_USING_SHIFTS_AND_MASKS(variable, high_bit, low_bit, value)  \
    ((variable) =     (variable)                                      \
                      & ~ SLICE_MASK (high_bit, low_bit)                  \
                      |                                            \
                      ((value) << (low_bit))                          \
                      &   SLICE_MASK (high_bit, low_bit) )

#define SET_SLICE_USING_SHIFTS_AND_MASKS_64(variable, high_bit, low_bit, value)  \
    ((variable) =     (variable)                                         \
                      & ~ SLICE_MASK_64 (high_bit, low_bit)                  \
                      |                                               \
                      (((uint64) value) << (low_bit))                    \
                      &   SLICE_MASK_64 (high_bit, low_bit) )

/********************************************************************/

#define GET_SLICE_FOR_SIMULATION GET_SLICE_USING_SHIFTS_AND_MASKS
#define SET_SLICE_FOR_SIMULATION SET_SLICE_USING_SHIFTS_AND_MASKS

#define GET_SLICE_FOR_SIMULATION_64 GET_SLICE_USING_SHIFTS_AND_MASKS_64
#define SET_SLICE_FOR_SIMULATION_64 SET_SLICE_USING_SHIFTS_AND_MASKS_64

#define GET_SLICE_FOR_SYNTHESIS _clevel_get_bit_slice
#define SET_SLICE_FOR_SYNTHESIS _clevel_set_bit_slice

#ifdef __cplusplus

int  GET_SLICE_FOR_SYNTHESIS ( unsigned, int, int );
void SET_SLICE_FOR_SYNTHESIS ( unsigned, int, int, unsigned );

#endif  /*  #ifdef __cplusplus  */

/********************************************************************/

#ifdef __CYCLEC_TRANSLATION__

#define get_slice   GET_SLICE_FOR_SYNTHESIS
#define set_slice   SET_SLICE_FOR_SYNTHESIS

#else  /*  #ifdef __CYCLEC_TRANSLATION__  */

#ifdef __cplusplus

inline unsigned int get_slice (unsigned int v, int h, int l)
{
    return GET_SLICE_FOR_SIMULATION (v, h, l);
}

inline int get_slice (int v, int h, int l)
{
    return GET_SLICE_FOR_SIMULATION (v, h, l);
}

inline unsigned _int64 get_slice (unsigned _int64 v, int h, int l)
{
    return GET_SLICE_FOR_SIMULATION_64 (v, h, l);
}

inline _int64 get_slice (_int64 v, int h, int l)
{
    return GET_SLICE_FOR_SIMULATION_64 (v, h, l);
}

inline void set_slice (int & e, int h, int l, int v)
{
    SET_SLICE_FOR_SIMULATION (e, h, l, v);
}

inline void set_slice (unsigned int & e, int h, int l, unsigned int v)
{
    SET_SLICE_FOR_SIMULATION (e, h, l, v);
}

inline void set_slice (unsigned int & e, int h, int l, int v)
{
    SET_SLICE_FOR_SIMULATION (e, h, l, v);
}

inline void set_slice (int & e, int h, int l, unsigned int v)
{
    SET_SLICE_FOR_SIMULATION (e, h, l, v);
}

inline void set_slice (unsigned int & e, int h, int l, unsigned _int64 v)
{
    SET_SLICE_FOR_SIMULATION (e, h, l, (unsigned int) v);
}

inline void set_slice (unsigned int & e, int h, int l, _int64 v)
{
    SET_SLICE_FOR_SIMULATION (e, h, l, (unsigned int) v);
}

inline void set_slice (int & e, int h, int l, unsigned _int64 v)
{
    SET_SLICE_FOR_SIMULATION (e, h, l, (unsigned int) v);
}

inline void set_slice (unsigned _int64 & e, int h, int l, unsigned int v)
{
    SET_SLICE_FOR_SIMULATION_64 (e, h, l, v);
}

inline void set_slice (unsigned _int64 & e, int h, int l, int v)
{
    SET_SLICE_FOR_SIMULATION_64 (e, h, l, v);
}

inline void set_slice (_int64 & e, int h, int l, unsigned int v)
{
    SET_SLICE_FOR_SIMULATION_64 (e, h, l, v);
}

inline void set_slice (unsigned _int64 & e, int h, int l, unsigned _int64 v)
{
    SET_SLICE_FOR_SIMULATION_64 (e, h, l, v);
}

inline void set_slice (unsigned _int64 & e, int h, int l, _int64 v)
{
    SET_SLICE_FOR_SIMULATION_64 (e, h, l, v);
}

inline void set_slice (_int64 & e, int h, int l, unsigned _int64 v)
{
    SET_SLICE_FOR_SIMULATION_64 (e, h, l, v);
}

#else  /*  #ifdef __cplusplus  */

#define get_slice   GET_SLICE_FOR_SIMULATION
#define set_slice   SET_SLICE_FOR_SIMULATION

#endif  /*  #ifdef __cplusplus  */
#endif  /*  #ifdef __CYCLEC_TRANSLATION__  */

/********************************************************************/

#define get_slice_with_variable_pos GET_SLICE_USING_SHIFTS_AND_MASKS
#define set_slice_with_variable_pos SET_SLICE_USING_SHIFTS_AND_MASKS

/********************************************************************/

#ifdef __CYCLEC_TRANSLATION__

#define get_bit(expression, bit)                                         \
    get_slice (expression, bit, bit)

#define set_bit(expression, bit, value)                                  \
    set_slice (expression, bit, bit, value)

#define get_bit_with_variable_pos(expression, bit)                       \
    get_slice_with_variable_pos (expression, bit, bit)

#define set_bit_with_variable_pos(expression, bit, value)                \
    set_slice_with_variable_pos (expression, bit, bit, value)

#else  /*  #ifdef __CYCLEC_TRANSLATION__  */

#ifdef __cplusplus

inline unsigned int get_bit (unsigned int e, int b)
{
    return GET_SLICE_FOR_SIMULATION (e, b, b);
}

inline unsigned int get_bit (unsigned _int64 e, int b)
{
    return (unsigned int) GET_SLICE_FOR_SIMULATION_64 (e, b, b);
}

#ifdef __SUPPORT_GREATER_THEN_64_BITS_INTEGER_TYPES__
inline unsigned int get_bit (cld_unsigned & e, int b)
{
    return to_uint (e.get_range (b, b));
}
#endif  /*  #ifdef __SUPPORT_GREATER_THEN_64_BITS_INTEGER_TYPES__  */

inline void set_bit (unsigned int & e, int b, unsigned int v)
{
    SET_SLICE_FOR_SIMULATION (e, b, b, v);
}

inline void set_bit (unsigned _int64 & e, int b, unsigned int v)
{
    SET_SLICE_FOR_SIMULATION_64 (e, b, b, v);
}

#ifdef __SUPPORT_GREATER_THEN_64_BITS_INTEGER_TYPES__
inline void set_bit (cld_unsigned & e, int b, unsigned int v)
{
    e.set_range (v, b, b);
}
#endif  /*  #ifdef __SUPPORT_GREATER_THEN_64_BITS_INTEGER_TYPES__  */

#define get_bit_with_variable_pos(expression, bit)                       \
    get_slice (expression, bit, bit)

#define set_bit_with_variable_pos(expression, bit, value)                \
    set_slice (expression, bit, bit, value)

#else  /*  #ifdef __cplusplus  */

#define get_bit(expression, bit)                                         \
    get_slice (expression, bit, bit)

#define set_bit(expression, bit, value)                                  \
    set_slice (expression, bit, bit, value)

#define get_bit_with_variable_pos(expression, bit)                       \
    get_slice_with_variable_pos (expression, bit, bit)

#define set_bit_with_variable_pos(expression, bit, value)                \
    set_slice_with_variable_pos (expression, bit, bit, value)

#endif  /*  #ifdef __cplusplus  */
#endif  /*  #ifdef __CYCLEC_TRANSLATION__  */

/*********************************************************************
*                                                                    *
*       Bit Concatenation macro                                      *
*                                                                    *
*********************************************************************/

#define bitvec_concat(var1, var2, size1, size2)                      \
    (((cv_uint##size1 (var1)) << size2) | var2)

/*********************************************************************
*                                                                    *
*       Delayed Assignment macro                                     *
*                                                                    *
*********************************************************************/

#ifdef __CYCLEC_TRANSLATION__

#ifdef __cplusplus

void  _clevel_delayAssign (int, int);
#define delayAssign(a,b) _clevel_delayAssign (a, b)

#else  /*  #ifdef __cplusplus  */

#define delayAssign(a,b) _clevel_delayAssign (a, b)

#endif  /*  #ifdef __cplusplus  */

#else  /*  #ifdef __CYCLEC_TRANSLATION__  */

#define delayAssign(a,b) a = b

#endif  /*  #ifdef __CYCLEC_TRANSLATION__  */

/*********************************************************************
*                                                                    *
*       New names                                                    *
*                                                                    *
*********************************************************************/

#define cc_getBit(expression, bit)                         get_bit(expression, bit)
#define cc_setBit(expression, bit, value)                  set_bit(expression, bit, value)
#define cc_getSlice(expression, high, low)                 get_slice(expression, high, low)
#define cc_setSlice(expression, high, low, value)          set_slice(expression, high, low, value)
#define cc_concat(expression1, expression2, size1, size2)  bitvec_concat(expression1, expression2, size1, size2)
#define cc_delayAssign(left, right)                        delayAssign(left, right)

/*********************************************************************
*                                                                    *
*    DO NOT USE THE MACROS BELOW IN NEW CODE.                        *
*                                                                    *
*    They are here for backwards compatiblity with old designs       *
*    only and may be removed in the future. The argument order       *
*    and meaning are different than the new get_slice macro, so      *
*    use of these macros can lead to considerable user confusion.    *
*                                                                    *
*********************************************************************/

#define GET_SLICE(var, size, low) \
    get_slice (var, (low) + (size) - 1, low)

#define SET_SLICE(var, size, low, val) \
    (set_slice (var, (low) + (size) - 1, low, val), var)

#define GET_BIT(var, bit)        get_slice (var, bit, bit)
#define SET_BIT(var, bit, val)  (set_slice (var, bit, bit, val), var)

/*********************************************************************
*                                                                    *
*   CycleC Translator uses "unknown" and "high_impedance"            *
*   as names of C pseudo-variables to assign                         *
*   "x" ("unknown") or "z" ("high_impedance") values.                *
*                                                                    *
*   In order to achieve compatibility with software C                *
*   compilers, this header defines "unknown"                         *
*   and "high_impedance" as zero.                                    *
*                                                                    *
*********************************************************************/

#ifdef __CYCLEC_TRANSLATION__

#ifdef __cplusplus
extern int high_impedance;
extern int unknown;
#endif

#define cc_setUnknown(reg)          ((reg) = unknown)
#define cc_setHighImpedance(reg)    ((reg) = high_impedance)

#else  /*  #ifdef __CYCLEC_TRANSLATION__  */

#define unknown         0
#define high_impedance  0

#define cc_setUnknown(reg)
#define cc_setHighImpedance(reg)

#endif  /*  #ifdef __CYCLEC_TRANSLATION__  */

/*********************************************************************
*                                                                    *
*           cc_sim                                                   *
*                                                                    *
*********************************************************************/

#ifdef __cplusplus

class cc_sim
{
public:

    int in, out;

    cc_sim () : in (0), out (1) {}
};

/*********************************************************************
*                                                                    *
*   cc_currentSim class (base class for cc_wire, cc_array            *
*   and cc_tri) is not necessary from the class library              *
*   design standpoint.                                               *
*                                                                    *
*   cc_currentSim::sim could be in principle implemented             *
*   as a global variable.                                            *
*                                                                    *
*   However static class member implementation is 10% faster         *
*   on some examples compiled with gnu g++ -O2.                      *
*                                                                    *
*********************************************************************/

class cc_currentSim
{
public:

    static cc_sim   sim;   // For fast access
    static cc_sim * pSim;  // For VCD dumping of cc_wire
};

#ifdef __CYCLEC_CPP__
cc_sim   cc_currentSim::sim;
cc_sim * cc_currentSim::pSim = & cc_currentSim::sim;
#endif

/* cc_stepSim () is defined after cc_setNoDriversForAllOutTris () */

inline void cc_setCurrentSim (cc_sim & sim)
{
    cc_currentSim::sim  = sim;
    cc_currentSim::pSim = & sim;
}

/*********************************************************************
*                                                                    *
*           cc_wire                                                  *
*                                                                    *
*********************************************************************/

template <class T>
class cc_wire : public cc_currentSim
{
public:

    T value [2];

    cc_wire ()
    {
    }

    operator T () const
    {
        return value [sim.in];
    }

    T * operator & ()
    {
        return & value [sim.out];
    }

#ifdef __CYCLEC_TRANSLATION__

    T & _wire_i ()
    {
        return value [sim.in];
    }

    T & _wire_o ()
    {
        return value [sim.out];
    }

#endif  /*  #ifdef __CYCLEC_TRANSLATION__  */

    cc_wire (cc_wire <T> const & anotherWire)
    {
        fprintf
        (
            cc_log,
            "CycleC: Initialization of cc_wire by another cc_wire"
            " is not consistent with CycleC design methodology\n"
        );
    }

    cc_wire <T> & operator = (cc_wire <T> const & anotherWire)
    {
        fprintf
        (
            cc_log,
            "CycleC: Assignment of cc_wire to another cc_wire"
            " is not consistent with CycleC design methodology\n"
        );
    }
};

#define cc_wire(T) cc_wire < T >

/********************************************************************/

#ifdef __CYCLEC_TRANSLATION__

#define cc_in(wire)   wire._wire_i ()
#define cc_out(wire)  wire._wire_o ()

#else  /*  #ifdef __CYCLEC_TRANSLATION__  */

#define cc_in(wire)   wire.value [wire.sim.in]
#define cc_out(wire)  wire.value [wire.sim.out]

#endif  /*  #ifdef __CYCLEC_TRANSLATION__  */

/*********************************************************************
*                                                                    *
*           cc_array                                                 *
*                                                                    *
*********************************************************************/

template <class T, int n>
class cc_array : public cc_currentSim
{
public:

    T value [2][n];

    cc_array ()
    {
    }

    operator T * ()
    {
        return value [sim.in];
    }

    T * operator & ()
    {
        return value [sim.out];
    }

#ifdef __CYCLEC_TRANSLATION__

    T * _wire_i ()
    {
        return value [sim.in];
    }

    T * _wire_o ()
    {
        return value [sim.out];
    }

#endif  /*  #ifdef __CYCLEC_TRANSLATION__  */

    cc_array (cc_array <T, n> const & anotherArray)
    {
        fprintf
        (
            cc_log,
            "CycleC: Initialization of cc_array"
            " by another cc_array"
            " is not consistent with CycleC design methodology\n"
        );
    }

    cc_array <T, n> & operator =
    (cc_array <T, n> const & anotherArray)
    {
        fprintf
        (
            cc_log,
            "CycleC: Assignment of cc_array"
            " to another cc_array"
            " is not consistent with CycleC design methodology\n"
        );
    }
};

#define cc_array(T, n) cc_array < T, n >

/*********************************************************************
*                                                                    *
*           cc_tri                                                   *
*                                                                    *
*********************************************************************/

#ifdef __CYCLEC_SIMULATION__

class cc_triHeader
{
public:

    cc_triHeader * nextOnListOfTris;
    bool bValueIsDriven [2];

    char const * lastDriver_triName;
    char const * lastDriver_sourceFileName;
    int          lastDriver_sourceLine;
};

#ifdef __CYCLEC_CPP__
cc_triHeader * cc_listOfTris = NULL;
#else
extern cc_triHeader * cc_listOfTris;
#endif

inline void cc_setNoDriversForAllOutTris ()
{
    cc_triHeader * p = cc_listOfTris;

    while (p != NULL)
    {
        p -> bValueIsDriven [cc_currentSim::sim.out] = false;
        p = p -> nextOnListOfTris;
    }
}

inline void cc_stepSim (cc_sim & sim = cc_currentSim::sim)
{
    sim.in  = ! sim.in;
    sim.out = ! sim.out;

    cc_setNoDriversForAllOutTris ();
}

/********************************************************************/

#ifdef __CYCLEC_CPP__

bool cc_flagCheckReadingFromHighImpedance  = true;
bool cc_flagCheckMultipleDrivers           = true;

#else  /*  #ifdef __CYCLEC_CPP__  */

extern bool cc_flagCheckReadingFromHighImpedance;
extern bool cc_flagCheckMultipleDrivers;

#endif  /*  #ifdef __CYCLEC_CPP__  */

const unsigned char cc_triValue_NoDrivers       = 0x55;
const unsigned char cc_triValue_MultipleDrivers = 0xAA;

template <class T>
class cc_tri : public cc_triHeader, public cc_currentSim
{
public:

    T value [2];

    cc_tri ()
    {
        nextOnListOfTris = cc_listOfTris;
        cc_listOfTris    = this;

        bValueIsDriven [0] = bValueIsDriven [1] = false;

        lastDriver_triName        = NULL;
        lastDriver_sourceFileName = NULL;
        lastDriver_sourceLine     = 0;

        memset (value, cc_triValue_NoDrivers, sizeof (value));
    }

    operator T () const
    {
        if (      cc_flagCheckReadingFromHighImpedance
                  && ! bValueIsDriven [sim.in] )
        {
            fprintf (cc_log, "CycleC: bus has no drivers\n");

            /*
                Yuri:

                Unfortunately, we have to use "operator T () const
                and then to discard const
                because of an issue with GCC and test_tri2.cpp.
                Non-const version of "operator T" will not work
                in that case
            */

            memset
            (
                (char *) & value [sim.in],
                cc_triValue_NoDrivers,
                sizeof (value [sim.in])
            );
        }

        return value [sim.in];
    }

    cc_tri (cc_tri <T> const & anotherTri)
    {
        fprintf
        (
            cc_log,
            "CycleC: Initialization of cc_tri"
            " by another cc_tri"
            " is not consistent with CycleC design methodology\n"
        );
    }

    cc_tri <T> & operator = (cc_tri <T> const & anotherTri)
    {
        fprintf
        (
            cc_log,
            "CycleC: Assignment of cc_tri"
            " to another cc_tri"
            " is not consistent with CycleC design methodology\n"
        );
    }

    T read
    (
        char const * triName,
        char const * sourceFileName,
        int          sourceLine
    )
    {
        if (      cc_flagCheckReadingFromHighImpedance
                  && ! bValueIsDriven [sim.in] )
        {
            fprintf
            (
                cc_log
                ,
                "CycleC: Attempt to read bus without drivers:"
                " \"%s\", file \"%s\", line %d\n"
                ,
                triName,
                sourceFileName,
                sourceLine
            );

            memset
            (
                & value [sim.in],
                cc_triValue_NoDrivers,
                sizeof (value [sim.in])
            );
        }

        return value [sim.in];
    }

    void write
    (
        bool         enable,
        T    const & outValue,
        char const * triName,
        char const * sourceFileName,
        int          sourceLine
    )
    {
        if (! enable)
            return;

        if (    cc_flagCheckMultipleDrivers
                && bValueIsDriven [sim.out] )
        {
            fprintf
            (
                cc_log
                ,
                "CycleC: Two drivers: \"%s\", file \"%s\", line %d\n"
                "and \"%s\", file \"%s\", line %d\n"
                ,
                lastDriver_triName,
                lastDriver_sourceFileName,
                lastDriver_sourceLine,

                triName,
                sourceFileName,
                sourceLine
            );

            memset
            (
                & value [sim.out],
                cc_triValue_MultipleDrivers,
                sizeof (value [sim.out])
            );
        }

        bValueIsDriven [sim.out] = true;

        lastDriver_triName        = triName;
        lastDriver_sourceFileName = sourceFileName;
        lastDriver_sourceLine     = sourceLine;

        value [sim.out] = outValue;
    }
};

#define cc_tri(T) cc_tri < T >

#define cc_readTri(tri)                                     \
    \
    (tri).read                                      \
    (                                               \
                                                    #tri,                                       \
                                                    __FILE__,                                   \
                                                    __LINE__                                    \
    )

#define cc_writeTri(tri, enable, value)                     \
    \
    (tri).write                                     \
    (                                               \
                                                    enable,                                     \
                                                    value,                                      \
                                                    #tri,                                       \
                                                    __FILE__,                                   \
                                                    __LINE__                                    \
    )

#define cc_inIsZ(tri)   (! (tri).bValueIsDriven [cc_currentSim::sim.in])
#define cc_outIsZ(tri)  (! (tri).bValueIsDriven [cc_currentSim::sim.out])

#define cc_setInZ(tri)  ((tri).bValueIsDriven [cc_currentSim::sim.in]  = false)
#define cc_setOutZ(tri) ((tri).bValueIsDriven [cc_currentSim::sim.out] = false)

#define cc_checkReadingFromHighImpedance()                  \
    (cc_flagCheckReadingFromHighImpedance = true)

#define cc_dontCheckReadingFromHighImpedance()              \
    (cc_flagCheckReadingFromHighImpedance = false)

#define cc_checkMultipleDrivers()                           \
    (cc_flagCheckMultipleDrivers = true)

#define cc_dontCheckMultipleDrivers()                       \
    (cc_flagCheckMultipleDrivers = false)

#else  /*  #ifdef __CYCLEC_SIMULATION__  */

template <class T>
class cc_bus
{
public:
    T value;

    void assign (bool enable, T value);
    operator T () const;
};

#define cc_tri(T) cc_bus < T >
#define cc_readTri(tri) tri
#define cc_writeTri(tri, enable, value) (tri).assign (enable, value)

#define cc_checkReadingFromHighImpedance()
#define cc_dontCheckReadingFromHighImpedance()
#define cc_checkMultipleDrivers()
#define cc_dontCheckMultipleDrivers()

#endif  /*  #ifdef __CYCLEC_SIMULATION__  */

#define cc_checkHighImpd()          cc_checkReadingFromHighImpedance      ()
#define cc_dontCheckHighImpd()      cc_dontCheckReadingFromHighImpedance  ()

#define cc_checkMultiDrivers()      cc_checkMultipleDrivers               ()
#define cc_dontCheckMultiDrivers()  cc_dontCheckMultipleDrivers           ()

#define cc_checkMultiDriver()       cc_checkMultipleDrivers               ()
#define cc_dontCheckMultiDriver()   cc_dontCheckMultipleDrivers           ()

/*********************************************************************
*                                                                    *
*           cc_timeType                                              *
*                                                                    *
*********************************************************************/

#ifdef __CYCLEC_SIMULATION__

#if    ! defined (__CC_TIMETYPE_IS_32_BIT_UNSIGNED__)       \
    && ! defined (__CC_TIMETYPE_IS_64_BIT_UNSIGNED__)       \
    && ! defined (__CC_TIMETYPE_IS_96_BIT_UNSIGNED__)       \
    && ! defined (__CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__)

#define __CC_TIMETYPE_IS_64_BIT_UNSIGNED__
#endif

#define CC_2_POW_32ULL  0x100000000ULL
#define CC_MASK_32U     0xFFFFFFFFU

/********************************************************************/

#ifdef __CC_TIMETYPE_IS_32_BIT_UNSIGNED__

typedef unsigned cc_timeType;
extern cc_timeType cc_time;

inline unsigned long long cc_timeBits95_32 (cc_timeType t = cc_time)
{
    return 0;
}

inline unsigned cc_timeBits95_64 (cc_timeType t = cc_time)
{
    return 0;
}

inline unsigned long long cc_timeBits63_0 (cc_timeType t = cc_time)
{
    return t;
}

inline unsigned cc_timeBits63_32 (cc_timeType t = cc_time)
{
    return 0;
}

inline unsigned cc_timeBits31_0 (cc_timeType t = cc_time)
{
    return t;
}

inline cc_timeType cc_makeTime
(
    unsigned bits31_0
)
{
    return bits31_0;
}

inline cc_timeType cc_makeTime
(
    unsigned bits63_32,
    unsigned bits31_0
)
{
    return bits31_0;
}

inline cc_timeType cc_makeTime
(
    unsigned bits95_64,
    unsigned bits63_32,
    unsigned bits31_0
)
{
    return bits31_0;
}

#endif  /*  #ifdef __CC_TIMETYPE_IS_32_BIT_UNSIGNED__  */

/********************************************************************/

#ifdef __CC_TIMETYPE_IS_64_BIT_UNSIGNED__

typedef unsigned long long cc_timeType;
extern cc_timeType cc_time;

inline unsigned long long cc_timeBits95_32 (cc_timeType t = cc_time)
{
    return t >> 32;
}

inline unsigned cc_timeBits95_64 (cc_timeType t = cc_time)
{
    return 0;
}

inline unsigned long long cc_timeBits63_0 (cc_timeType t = cc_time)
{
    return t;
}

inline unsigned cc_timeBits63_32 (cc_timeType t = cc_time)
{
    return t >> 32;
}

inline unsigned cc_timeBits31_0 (cc_timeType t = cc_time)
{
    return t & CC_MASK_32U;
}

inline cc_timeType cc_makeTime
(
    unsigned bits31_0
)
{
    return bits31_0;
}

inline cc_timeType cc_makeTime
(
    unsigned bits63_32,
    unsigned bits31_0
)
{
    return ((cc_timeType) bits63_32 << 32) | bits31_0;
}

inline cc_timeType cc_makeTime
(
    unsigned bits95_64,
    unsigned bits63_32,
    unsigned bits31_0
)
{
    return ((cc_timeType) bits63_32 << 32) | bits31_0;
}

#endif  /*  #ifdef __CC_TIMETYPE_IS_64_BIT_UNSIGNED__  */

/********************************************************************/

#if    defined (__CC_TIMETYPE_IS_96_BIT_UNSIGNED__)         \
    || defined (__CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__)

class cc_timeType
{
public:
    unsigned long long h;
    unsigned           l;

    cc_timeType (unsigned u = 0)
    {
        h = 0;
        l = u;
    }

    cc_timeType (double d, double factor)
    {
        d /= factor;

        h = (unsigned long long) d;
        l = (unsigned long) ((d - h) * CC_2_POW_32ULL);
    }

    friend bool operator == (cc_timeType const & a, cc_timeType const & b)
    {
        return a.h == b.h && a.l == b.l;
    }

    friend bool operator != (cc_timeType const & a, cc_timeType const & b)
    {
        return a.h != b.h || a.l != b.l;
    }

    friend bool operator < (cc_timeType const & a, cc_timeType const & b)
    {
        return a.h == b.h ? a.l < b.l : a.h < b.h;
    }

    friend bool operator <= (cc_timeType const & a, cc_timeType const & b)
    {
        return a.h == b.h ? a.l <= b.l : a.h <= b.h;
    }

    friend bool operator > (cc_timeType const & a, cc_timeType const & b)
    {
        return a.h == b.h ? a.l > b.l : a.h > b.h;
    }

    friend bool operator >= (cc_timeType const & a, cc_timeType const & b)
    {
        return a.h == b.h ? a.l >= b.l : a.h >= b.h;
    }

    friend void operator += (cc_timeType & a, cc_timeType const & b)
    {
        unsigned long long l_plus_l
            = (unsigned long long) a.l + (unsigned long long) b.l;

        a.l = l_plus_l & CC_MASK_32U;
        a.h = a.h + b.h + (l_plus_l >> 32);
    }
};

extern cc_timeType cc_time;

inline unsigned long long cc_timeBits95_32 (cc_timeType t = cc_time)
{
    return t.h;
}

inline unsigned cc_timeBits95_64 (cc_timeType t = cc_time)
{
    return t.h >> 32;
}

inline unsigned long long cc_timeBits63_0 (cc_timeType t = cc_time)
{
    return (unsigned long long)
           (((unsigned long long) t.h << 32) | t.l);
}

inline unsigned cc_timeBits63_32 (cc_timeType t = cc_time)
{
    return t.h & CC_MASK_32U;
}

inline unsigned cc_timeBits31_0 (cc_timeType t = cc_time)
{
    return t.l;
}

inline cc_timeType cc_makeTime
(
    unsigned bits31_0
)
{
    cc_timeType time;

    time.h = 0;
    time.l = bits31_0;

    return time;
}

inline cc_timeType cc_makeTime
(
    unsigned bits63_32,
    unsigned bits31_0
)
{
    cc_timeType time;

    time.h = bits63_32;
    time.l = bits31_0;

    return time;
}

inline cc_timeType cc_makeTime
(
    unsigned bits95_64,
    unsigned bits63_32,
    unsigned bits31_0
)
{
    cc_timeType time;

    time.h = ((unsigned long long) bits95_64 << 32) | bits63_32;
    time.l = bits31_0;

    return time;
}

#endif  /*  #if    defined (__CC_TIMETYPE_IS_96_BIT_UNSIGNED__)        */
/*      || defined (__CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__)  */

/********************************************************************/

#ifdef __CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__

inline double cc_doubleTime (cc_timeType t = cc_time)
{
    extern double cc_factorForClocksDefinedWithFloatingPoint;

    return (   (double) cc_timeBits95_32 (t) * CC_2_POW_32ULL
               + cc_timeBits31_0 (t) )

           * cc_factorForClocksDefinedWithFloatingPoint
           / CC_2_POW_32ULL
           ;
}

#else  /*  #ifdef __CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__  */

inline double cc_doubleTime (cc_timeType t = cc_time)
{
    return (double) cc_timeBits95_32 (t)
           * CC_2_POW_32ULL
           + cc_timeBits31_0 (t)
           ;
}

#endif  /*  #ifdef __CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__  */

#ifdef __CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__

inline char const * cc_timeString (cc_timeType t = cc_time)
{
    static char buffer [256];

    sprintf (buffer, "%g", cc_doubleTime (t));
    return buffer;
}

#else  /*  #ifdef __CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__  */

inline char const * cc_timeString (cc_timeType t = cc_time)
{
    static char buffer [256];

    if (cc_timeBits95_32 (t) == 0)
    {
        sprintf (buffer, "%u", cc_timeBits31_0 (t));
    }
    else if (cc_timeBits95_64 (t) == 0)
    {
        unsigned long long ull = cc_timeBits63_0 (t);

        static char reverseBuffer [256];
        char * r = reverseBuffer;

        while (ull != 0)
        {
            assert (r < reverseBuffer + sizeof (reverseBuffer));

            * r ++ = (char) ('0' + (int) (ull % 10));
            ull /= 10;
        }

        assert (r > reverseBuffer);
        assert (r < reverseBuffer + sizeof (reverseBuffer));

        char * p = buffer;

        while (r != reverseBuffer)
        {
            assert (p < buffer + sizeof (buffer));
            * p ++ = * -- r;
        }

        assert (p < buffer + sizeof (buffer));
        * p = '\0';
    }
    else
    {
        sprintf (buffer, "%g", cc_doubleTime (t));
    }

    return buffer;
}

#endif  /*  #ifdef __CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__  */

#endif  /*  #ifdef __CYCLEC_SIMULATION__  */

/*********************************************************************
*                                                                    *
*           cc_clock                                                 *
*                                                                    *
*********************************************************************/

#ifdef __CYCLEC_TRANSLATION__

int1 infer_clock (int1 clock);
int1 infer_reset (int1 reset);
int1 infer_clock (uint1 clock);
int1 infer_reset (uint1 reset);
bool infer_clock (bool clock);
bool infer_reset (bool reset);

#else  /*  #ifdef __CYCLEC_TRANSLATION__  */

#define infer_clock(clock) (clock)
#define infer_reset(reset) (reset)

#endif  /*  #ifdef __CYCLEC_TRANSLATION__  */

#define cc_inferReset(reset) infer_reset(reset)

/********************************************************************/

#ifdef __CYCLEC_SIMULATION__

enum cc_clockValue
{
    LOW         = 0,
    HIGH        = 1,
    NEGEDGE     = 2,
    POSEDGE     = 3,

    NEGEDGEONLY = 2,
    POSEDGEONLY = 3,
    BOTHEDGES   = 4
};

char const * cc_clockValueName      (enum cc_clockValue clockValue);
char const * cc_clockValueShortName (enum cc_clockValue clockValue);

/********************************************************************/

class cc_clockData
{
public:

    cc_clockData  * nextOnListOfClockData;
    cc_clockValue   value;

    bool            bIsInternallyGeneratedClock;
    bool            bIsClockDefinedWithFloatingPoint;

    bool            bPosedgeIsActive;
    bool            bNegedgeIsActive;

    cc_timeType     period;
    cc_timeType     posedgeTime;
    cc_timeType     negedgeTime;

    double          double_period;
    double          double_posedgeTime;
    double          double_negedgeTime;

    void checkDataConsistency ();
    void updateValue ();
    void convertClockDefinedWithFloatingPointIntoIntegerClock ();
};

/********************************************************************/

class cc_clock
{
public:

    cc_clockData * d;

    cc_clock ();

#ifdef __CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__

    cc_clock
    (
        double        _double_period,
        double        _double_posedgeTime,
        double        _double_negedgeTime,
        cc_clockValue activeEdges = BOTHEDGES
    );

#else  /*  #ifdef __CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__  */

    cc_clock
    (
        cc_timeType   _period,
        cc_timeType   _posedgeTime,
        cc_timeType   _negedgeTime,
        cc_clockValue activeEdges = BOTHEDGES
    );

#endif  /*  #ifdef __CC_TIMETYPE_IS_96_BIT_FIXED_POINT_32__  */

    void operator = (cc_clockValue newValue);
    void operator = (cc_clock const & clock);

    operator int () const;

    bool operator == (cc_clockValue _value) const
    {
        return d -> value == _value;
    }
};

char const * cc_clockValueName      (cc_clock clock);
char const * cc_clockValueShortName (cc_clock clock);

#define cc_posedge(clock)   (clock.d -> value == POSEDGE)
#define cc_negedge(clock)   (clock.d -> value == NEGEDGE)
#define cc_level(clock)     ((uint1) clock)

void cc_setupClocksDefinedWithFloatingPoint ();
void cc_advanceClocks ();

/********************************************************************/

#else  /*  #ifdef __CYCLEC_SIMULATION__  */

enum cc_clockValue
{
    LOW     = 0,
    HIGH    = 1,
    NEGEDGE = 0,
    POSEDGE = 1
};

typedef uint1 cc_clock;

#define cc_posedge(clock)   infer_clock (clock)
#define cc_negedge(clock)   infer_clock (! clock)
#define cc_level(clock)     clock

#endif  /*  #ifdef __CYCLEC_SIMULATION__  */

/*********************************************************************
*                                                                    *
*           VCD/VCD+/VPD dump                                        *
*                                                                    *
*********************************************************************/

enum
{
    VCD       = 1,
    VCD_PLUS  = 2,
    VPD       = 3
};

#ifdef __CYCLEC_SIMULATION__

void cc_dumpFile             (char const * fileName, int format = VCD);
void cc_dump_VPD_FileHandle  (void * new_VPD_FileHandle);

void cc_dumpTimeScale        (int iTimeScale);
void cc_dumpTimeScale        (char const * timeScale);

void cc_dumpScope            (char const * scope);
void cc_dumpUpScope          (char const * scope = NULL);

void cc_dumpClock
(
    char const * name,
    cc_clock   & variable
);

void cc_dumpRegEx
(
    char const * name,
    void       * pReg,
    int          valueByteSizeOnSimulationHost,
    int          bitWidthInRealHardware
);

#define cc_dumpReg(name, variable, bitWidth)  \
    cc_dumpRegEx (name, & variable, sizeof (variable), bitWidth)

void cc_dumpWireEx
(
    char const * name,
    void       * pWireArray,
    int          valueByteSizeOnSimulationHost,
    int          bitWidthInRealHardware
);

// Yuri: (char &) here is necessary to avoid overloaded "&"

#define cc_dumpWire(name, variable, bitWidth)  \
    \
    cc_dumpWireEx                          \
    (                                      \
                                           name,                              \
                                           variable.value,                    \
                                           sizeof (variable.value [0]),       \
                                           bitWidth                           \
    )

void cc_dumpUpdate ();
void cc_dumpFlush  ();
void cc_dumpFinish ();

/********************************************************************/

#else  /*  #ifdef __CYCLEC_SIMULATION__  */

#define cc_dumpFile             (void)
#define cc_dump_VPD_FileHandle  (void)
#define cc_dumpTimeScale        (void)
#define cc_dumpScope            (void)
#define cc_dumpUpScope          (void)
#define cc_dumpClock            (void)
#define cc_dumpReg              (void)
#define cc_dumpWire             (void)
#define cc_dumpVars             (void)
#define cc_dumpUpdate           (void)
#define cc_dumpFlush            (void)
#define cc_dumpFinish           (void)

#endif  /*  #ifdef __CYCLEC_SIMULATION__   */

/* Macros for dumping local variables */

#define cc_dumpLocalClockData(variable, bitWidth)                     \
    cc_clock variable##_cc_dump

#define cc_dumpLocalClock(variable)                                   \
    variable##_cc_dump = variable

#define cc_dumpLocalData(variable, bitWidth)                          \
    uint##bitWidth variable##_cc_dump

#define cc_dumpLocal(variable)                                        \
    variable##_cc_dump = variable

#define cc_dumpLocalArrayData(variable, bitWidth, nElements)          \
    uint##bitWidth variable##_cc_dump [nElements]

#define cc_dumpLocalArray(variable, nElements)                        \
    {                                                             \
        int cc_index;                                             \
        \
        for (cc_index = 0; cc_index < nElements; cc_index ++)     \
            variable##_cc_dump [cc_index] = variable [cc_index];  \
    }

/* Obsolete functions and function names */

#define cc_dumpEndDefinitions()
#define cc_freeDumpStructures()     cc_dumpFinish ()

#endif  /*  #ifdef __cplusplus             */

/********************************************************************/


#ifdef CC_HYBRID_SIMULATION
/* Include the cc_bits code only for hybrid simulation.
   Do not impact regular use of this file (cyclec.h). */

#ifndef __cplusplus
#error Hybrid simulation is supported in C++ (not C) mode only.
#endif

#include <assert.h>
#include <malloc.h>
#include <limits.h> /* For CHAR_BIT */
#include <map>
#include <string>
#include <alloca.h> // Shouldn't hurt Linux.

#ifdef __linux__
// Linux defines CHAR_BIT in limits.h, but not WORD_BIT.
#  define WORD_BIT 32
#endif

// log_2(WORD_BIT): Could be different on 64-bit architecture?
#define log_WORD_BIT 5

using namespace std;

#ifdef __ENABLE_PLI_WRAPPER__
#include <acc_user.h>

#ifdef MTI
#include <veriuser.h>
#else
#include <vcsuser.h>
#endif

#endif  //  #ifndef __ENABLE_PLI_WRAPPER__

#define bit_sizeof(x)   (sizeof (x) * CHAR_BIT)
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) < (b)) ? (b) : (a))

#ifdef __ENABLE_PLI_WRAPPER__

static bool
cc_isLittleEndian ()
{
    int     word = 0x10000000;
    char  * byte = (char *) & word;
    return  byte[0] == 0;
}

static void cc_unpackToBits  (int nbit, char bit [], unsigned word [])
{
    static map <int,    string, less<int   > > map_unpack;

    if (map_unpack.empty ())
    {
        for (int data = 0; data < 256; data++)
        {
            string vec (8, '\0');
            vec[0] = (data & 0x01) ? '1' : '0';
            vec[1] = (data & 0x02) ? '1' : '0';
            vec[2] = (data & 0x04) ? '1' : '0';
            vec[3] = (data & 0x08) ? '1' : '0';
            vec[4] = (data & 0x10) ? '1' : '0';
            vec[5] = (data & 0x20) ? '1' : '0';
            vec[6] = (data & 0x40) ? '1' : '0';
            vec[7] = (data & 0x80) ? '1' : '0';

            map_unpack [data] = vec;
        }
    }

    for (int pos = 0; pos < nbit; pos += bit_sizeof (char))
    {
        int wordN = pos / 32;
        int bitN  = pos % 32;

        int byteN = cc_isLittleEndian ()
                    ? bitN / 8
                    : 4 - (bitN / 8 + 1);

        unsigned char * byte = (unsigned char *) & word [wordN];

        assert (map_unpack.find (byte [byteN]) != map_unpack.end ());

        string & vec = map_unpack [byte [byteN]];
        int nchar = min (nbit - pos, (int) bit_sizeof (char));
        strncpy (bit + pos, vec.c_str (), nchar);
    }

    bit [nbit] = '\0'; /* NULL terminator */

}

static void cc_packToWords (int nbit, char bit [], unsigned word [])
{
    static map <string, int   , less<string> > map_pack;

    if (map_pack.empty ())
    {
        for (int data = 0; data < 256; data++)
        {
            string vec (8, '\0');
            vec[0] = (data & 0x01) ? '1' : '0';
            vec[1] = (data & 0x02) ? '1' : '0';
            vec[2] = (data & 0x04) ? '1' : '0';
            vec[3] = (data & 0x08) ? '1' : '0';
            vec[4] = (data & 0x10) ? '1' : '0';
            vec[5] = (data & 0x20) ? '1' : '0';
            vec[6] = (data & 0x40) ? '1' : '0';
            vec[7] = (data & 0x80) ? '1' : '0';

            map_pack [vec] = data;
        }
    }

    for (int pos = 0; pos < nbit; pos += bit_sizeof (char))
    {
        int wordN = pos / 32;
        int bitN  = pos % 32;
        int byteN = cc_isLittleEndian ()
                    ? bitN / 8
                    : 4 - (bitN / 8 + 1);

        string vec ("00000000");
        int nchar = min (nbit - pos, (int) bit_sizeof (char));
        vec.replace (0, nchar, & bit [pos], nchar );

        assert (map_pack.find (vec) != map_pack.end ());

        char * byte = (char *) & word [wordN];
        byte [byteN] = map_pack [vec];
    }
}


static int cc_getBitsInRange (struct t_vecval * p_vecval, int hi_bit, int lo_bit)
{
    assert (lo_bit >= 0);
    assert (hi_bit >= 0);
    assert (lo_bit <= hi_bit);

    int nbit  = 1 + hi_bit;
    int nword = 1 + hi_bit / bit_sizeof (unsigned);

    unsigned  * word = (unsigned *) alloca (nword * sizeof (unsigned));
    char      * bit  = (char *)     alloca (nbit  * sizeof (char));

    for (int i = 0; i < nword; i++)
    {
        int value01 = p_vecval[i].avalbits;
        int valueXZ = p_vecval[i].bvalbits;

        /* Convert bit positions with 'X' or 'Z' to '0'  */
        int value = value01 & ~valueXZ;
        word[i] = value;
    }

    cc_unpackToBits (nbit, bit, word);
    word[0] = 0;    /* cbs Initialize the output vector for PC Linux */
    cc_packToWords  (hi_bit - lo_bit + 1, &bit[lo_bit], word);

    int retVal = word[0];

    return retVal;
}



static void cc_setBitsInRange
(
    struct t_vecval * p_vecval,
    int hi_bit,
    int lo_bit,
    unsigned value
)
{
    assert (lo_bit >= 0);
    assert (hi_bit >= 0);
    assert (lo_bit <= hi_bit);

    int i;
    int nbit      = 1 + hi_bit;
    int nword     = 1 + hi_bit / bit_sizeof (unsigned);
    int nbitToSet = 1 + hi_bit - lo_bit;

    assert (nbitToSet <= bit_sizeof (unsigned));
    char bitToSet [1 + bit_sizeof (unsigned)];

    unsigned  * word = (unsigned *) alloca (    nword * sizeof (unsigned));
    char      * bit  = (char *)     alloca (1 + nword  * bit_sizeof (unsigned));

    for (i = 0; i < nword; i++)
    {
        int value01 = p_vecval[i].avalbits;
        int valueXZ = p_vecval[i].bvalbits;

        /* Convert bit positions with 'X' or 'Z' to '0'  */
        int value = value01 & ~valueXZ;
        word[i] = value;
    }

    /* Read from "word" array to "bit" array */
    cc_unpackToBits (nword * bit_sizeof (unsigned), bit, word);

    /* Modify "bit" array */
    cc_unpackToBits (nbitToSet, bitToSet, & value);
    strncpy (& bit[lo_bit], bitToSet, nbitToSet);

    /* Write from "bit" array to "word" array */
    cc_packToWords (nword * bit_sizeof (unsigned), bit, word);

    for (i = 0; i < nword; i++)
    {
        p_vecval[i].avalbits = word[i];
        p_vecval[i].bvalbits = 0;
    }
}

#endif  //  #ifndef __ENABLE_PLI_WRAPPER__

/* 2-state versions of cc_getBitsInRange() and cc_setBitsInRange()
  follow this comment.  They use "U*" instead of "struct t_vecval *".  */

typedef unsigned int U; /* Copied from $VCS_HOME/includeRT/typedefRT.h */

/* The slice does not straddle a word boundary. */
#define SLICE_FITS_IN_WORD(_hi_bit,_lo_bit) \
    (((_hi_bit) >> log_WORD_BIT) == ((_lo_bit) >> log_WORD_BIT))

/* The slice forms a word: i.e., _lo_bit is word-aligned, *and*
   the slice is precisely WORD_BIT bits long. */
#define SLICE_IS_A_WORD(_hi_bit,_lo_bit)          \
    (!((_lo_bit)&(WORD_BIT-1))                    \
     && (((_hi_bit) - (_lo_bit) + 1) == WORD_BIT))

/* _pointer points to contiguous memory.  Select the word in this memory
   where _lo_bit falls, and return it.  It can be used as an lvalue, too. */
#define SELECT_WORD(_pointer, _bit) ((_pointer)[(_bit) >> log_WORD_BIT])

#define GET_SLICE_INDIRECT(_pointer, _high_bit, _low_bit)  \
    (SLICE_IS_A_WORD(_high_bit, _low_bit)                  \
     ? SELECT_WORD(_pointer, _low_bit)                     \
     : GET_SLICE_USING_SHIFTS_AND_MASKS(                   \
                                                           SELECT_WORD(_pointer, _low_bit),                 \
                                                           (_high_bit) & (WORD_BIT-1),                      \
                                                           (_low_bit) & (WORD_BIT-1)))

/* The do{}while(0) below is a simple trick.  It allows this macro to be used
   in an if-else statement, without the need for braces.  Without it,
   "if (X) SET_SLICE_INDIRECT(...); else something()" would be a syntax
   error, because the ";" before the "else" would terminate the "if". */
#define SET_SLICE_INDIRECT(_pointer, _high_bit, _low_bit, _value)      \
    do {                                                               \
        if (SLICE_IS_A_WORD(_high_bit, _low_bit)) {                    \
            SELECT_WORD(_pointer, _low_bit) = (_value);                \
        } else {                                                       \
            SET_SLICE_USING_SHIFTS_AND_MASKS(                          \
                                                                       SELECT_WORD(_pointer, _low_bit),                       \
                                                                       (_high_bit) & (WORD_BIT-1), (_low_bit) & (WORD_BIT-1), \
                                                                       _value);                                               \
        }                                                              \
    } while (0)

static int cc_getBitsInRange (U *pvector, int hi_bit, int lo_bit)
{
    assert (lo_bit >= 0);
    assert (hi_bit >= lo_bit);
    assert (hi_bit - lo_bit < WORD_BIT);

    if (SLICE_FITS_IN_WORD(hi_bit, lo_bit)) {
        return GET_SLICE_INDIRECT(pvector, hi_bit, lo_bit);
    }

    /* The slice straddles one word boundary (but not two). */
    int mid_bit = hi_bit & ~(WORD_BIT-1); // LSB of second word.

    return ((GET_SLICE_INDIRECT(pvector, hi_bit, mid_bit)
             << (mid_bit-lo_bit))
            | GET_SLICE_INDIRECT(pvector, mid_bit-1, lo_bit));
} /* cc_getBitsInRange() */

static _int64 cc_getBitsInRange64 (U *pvector, int hi_bit, int lo_bit)
{
    assert (lo_bit >= 0);
    assert (hi_bit >= lo_bit);
    assert (hi_bit - lo_bit < 2*WORD_BIT);

    if (SLICE_FITS_IN_WORD(hi_bit, lo_bit)) {
        return GET_SLICE_INDIRECT(pvector, hi_bit, lo_bit);
    }

    int hi_mid_bit = hi_bit & ~(WORD_BIT-1); // LSB of Most Significant Word.

    unsigned _int64 p, q, r;

    p = GET_SLICE_INDIRECT(pvector, hi_bit, hi_mid_bit);

    if (((hi_bit) >> log_WORD_BIT) == (1 + ((lo_bit) >> log_WORD_BIT))) {
        /* The slice straddles one word boundary (but not two). */
        q = GET_SLICE_INDIRECT(pvector, hi_mid_bit-1, lo_bit);
        return ((p << (hi_mid_bit-lo_bit))
                | q);
    }

    /* The slice straddles exactly two word boundaries: not 0, 1, or 3. */
    int lo_mid_bit = hi_mid_bit-WORD_BIT; // LSB of second word.

    q = SELECT_WORD(pvector, lo_mid_bit);
    r = GET_SLICE_INDIRECT(pvector, lo_mid_bit-1, lo_bit);

    return ((p << (hi_mid_bit-lo_bit))
            | (q << (lo_mid_bit-lo_bit))
            | r);
} /* cc_getBitsInRange64() */


/* Get a slice, but the bit positions are specified with an offset.  Needed
   for cc_setBitsInRange() and cc_setBitsInRange64().  See example below.

   Example:
   - I need 3 bits to stuff into $pvector, from bit 31 down to bit 29.
       I call GET_SLICE_OFFSET(value, 31, 29, 29).  This invokes
       GET_SLICE_USING_SHIFTS_AND_MASKS(value, 31-29, 29-29) == (value, 2, 0), or
       the three LSB's.  I use that value.
   - Next, I need 7 more bits to stuff into $pvector, from bit 38 down to bit 32.
       So, I invoke GET_SLICE_OFFSET(value, 38, 32, 29), which calls
       GET_SLICE_USING_SHIFTS_AND_MASKS(value, 38-29, 32-29) == (value, 9, 3),
       which are the next 7 least significant bits.   I can then use that
       value.
   - And so on.
*/
#define GET_SLICE_OFFSET(_value, _high_bit, _low_bit, _offset) \
    GET_SLICE_USING_SHIFTS_AND_MASKS(                          \
                                                               _value, (_high_bit)-(_offset), (_low_bit)-(_offset))

#define GET_SLICE_OFFSET_64(_value, _high_bit, _low_bit, _offset) \
    GET_SLICE_USING_SHIFTS_AND_MASKS_64(                          \
            _value, (_high_bit)-(_offset), (_low_bit)-(_offset))

static void cc_setBitsInRange (U *pvector, int hi_bit, int lo_bit,
                               unsigned value)
{
    assert (lo_bit >= 0);
    assert (hi_bit >= lo_bit);
    assert (hi_bit - lo_bit < WORD_BIT);

    if (SLICE_FITS_IN_WORD(hi_bit, lo_bit)) {
        SET_SLICE_INDIRECT(pvector, hi_bit, lo_bit, value);
        return;
    }

    /* The slice straddles one word boundary (but not two). */
    int mid_bit = hi_bit & ~(WORD_BIT-1); // LSB of second word.

    SET_SLICE_INDIRECT(pvector, hi_bit, mid_bit,
                       GET_SLICE_OFFSET(value, hi_bit, mid_bit, lo_bit));
    SET_SLICE_INDIRECT(pvector, mid_bit-1, lo_bit,
                       GET_SLICE_OFFSET(value, mid_bit-1, lo_bit, lo_bit));
} /* cc_setBitsInRange() */

static void cc_setBitsInRange64 (U *pvector, int hi_bit, int lo_bit,
                                 unsigned _int64 value)
{
    assert (lo_bit >= 0);
    assert (hi_bit >= lo_bit);
    assert (hi_bit - lo_bit < 2*WORD_BIT);

    if (SLICE_FITS_IN_WORD(hi_bit, lo_bit)) {
        SET_SLICE_INDIRECT(pvector, hi_bit, lo_bit, value);
        return;
    }

    int hi_mid_bit = hi_bit & ~(WORD_BIT-1); // LSB of Most Significant Word.
    SET_SLICE_INDIRECT(
        pvector, hi_bit, hi_mid_bit,
        GET_SLICE_OFFSET_64(value, hi_bit, hi_mid_bit, lo_bit));

    if (((hi_bit) >> log_WORD_BIT) == (1 + ((lo_bit) >> log_WORD_BIT))) {
        /* The slice straddles one word boundary (but not two). */
        SET_SLICE_INDIRECT(
            pvector, hi_mid_bit-1, lo_bit,
            GET_SLICE_OFFSET_64(value, hi_mid_bit-1, lo_bit, lo_bit));
        return;
    }

    /* The slice straddles exactly two word boundaries: not 0, 1, or 3. */
    int lo_mid_bit = hi_mid_bit-WORD_BIT; // LSB of second word.

    SELECT_WORD(pvector, lo_mid_bit) =
        GET_SLICE_OFFSET_64(value, hi_mid_bit-1, lo_mid_bit, lo_bit);
    SET_SLICE_INDIRECT(
        pvector, lo_mid_bit-1, lo_bit,
        GET_SLICE_OFFSET_64(value, lo_mid_bit-1, lo_bit, lo_bit));
} /* cc_setBitsInRange64() */

#endif /* CC_HYBRID_SIMULATION */

#endif  /*  #ifndef __CYCLEC_H_INCLUDED__  */

/*********************************************************************
*                                                                    *
*           The end                                                  *
*                                                                    *
*********************************************************************/
