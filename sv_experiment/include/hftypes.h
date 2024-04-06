/*
* vim: set expandtab:
********************************************************************************
*
* Copyright 1991-1995 Simulation Technologies Corporation. All rights reserved.
*
*   This Program is an unpublished work fully protected by the United States
*   copyright laws and is considered a trade secret belonging to Simulation
*   Technologies Corporation. It is not to be divulged or used by parties
*   who have not received written authorization from Simulation Technologies
*   Corporation.
*
*                              W A R N I N G
*
*   THIS SOFTWARE AND MANUAL ARE BOTH PROTECTED BY UNITED STATES COPYRIGHT
*   LAW (TITLE 17, UNITED STATES CODE). UNAUTHORIZED REPRODUCTION AND/OR
*   SALES MAY RESULT IN IMPRISONMENT OF UP TO ONE YEAR AND FINES OF UP TO
*   $10,000 (17 USC 506). COPYRIGHT INFRINGERS MAY ALSO BE SUBJECT TO CIVIL
*   LIABILITY.
*
*   Simulation Technologies Corporation
*   2299 Palmer Drive Suite 202
*   New Brighton, MN 55112
*   Phone 612 631-1858
*   Fax 612 631-1830
*
********************************************************************************
*/

#ifndef _hftypes_h
#define _hftypes_h

/** @file
 * This file has the basic types used in the HF interface.
 */
/*
*******************************************************************************************
*
* Verilog based types
*
*******************************************************************************************
*/
/** a nice type for counts, indices, etc. - guaranteed to be 32-bits */
typedef unsigned int tNatural;

/* Define for 64 bit signed and unsigned int */
#ifndef UINT64
#define UINT64  unsigned long long
#endif

#ifndef INT64
#define INT64   long long
#endif

/** \brief Enumerated type to indicate the type of object being referenced.
 *
 * The value is actually stored as a smaller unsigned type, for space
 * conservation. \sa eHfStructType.
 */
typedef enum
{
    eHfInvalidMin = 0,

    eHfAttributeList,
    eHfAttributeListFree,
    eHfAttributeListWalk,
    eHfBlock,
    eHfVcbHdrInfo,
    eHfEncodingWalk,
    eHfDesign,
    eHfRecord,
    eHfScope,
    eHfScopeAlias,
    eHfVariable,
    eHfVariableExpand,
    eHfPackedRecord,
    eHfMeta,
    eHfNotOutput,
    eHfBufOutput,
    eHfIterator,
    eHfIVcoIter,
    eHfRefScpIter,


    /* Value change entries.  Must have MS bit set. */
    eHfValueChangeRd    = 0x80,
    eHfValueChangeWr,
    eHfValueChangeWrPatRec,
    eHfValueChangeWrLazyVco,
    eHfValueChangeMeta,     // Read Only for now.
    eHfIVco,

    eHfInvalidMax   /* Must always be the last entry!! */
}
evHfStructType;


/** \brief Storage type for evHfStructType
 *
 * This typedef's name originally referred to the underlying enumeration.  It
 * has been taken over here to make sure that the representation is uniform
 * even in clients we are not aware of.  The downside is that casts may be
 * needed in existing code.
 *
 * \sa evHfStructType
 */
typedef unsigned char   eHfStructType;

/** pre-defined encoding types */
#define hfEncodingNull              0
#define hfEncodingLine              1
#define hfEncodingScalar            2
#define hfEncodingVector            3
#define hfEncodingInteger           4
#define hfEncodingReal              5
#define hfEncodingTime              6
#define hfEncodingRecord            7
#define hfEncodingExpanded          8
#define hfEncodingLineTraceOffset   9
#define hfEncodingArrayRecord       10   /* Unused */
#define hfEncodingString            11
#define hfEncodingSummary           12
#define hfEncodingPackedRecord      13
#define hfEncodingNotOutput         14
#define hfEncodingBufOutput         15
#define hfEncodingStrengthVector    16

/* Must always be one more than the last predefined encoding type. */
#define hfEncodingLastPreDefined    17

/* Names for the predefined encoding types. */
#define hfEncodingNullName              "Null"
#define hfEncodingLineName              "Line"
#define hfEncodingScalarName            "Scalar"
#define hfEncodingVectorName            "Vector"
#define hfEncodingIntegerName           "Integer"
#define hfEncodingRealName              "Real"
#define hfEncodingTimeName              "Time"
#define hfEncodingRecordName            "Record"
#define hfEncodingExpandedName          "Expanded Variable"
#define hfEncodingLineTraceOffsetName   "Line Trace Offset"
#define hfEncodingArrayRecordName       "Record Array"   /* Unused */
#define hfEncodingStringName            "String"
#define hfEncodingSummaryName           "Summary"
#define hfEncodingPackedRecordName      "PackedRecord"
#define hfEncodingNotOutputName         "NotOutput"
#define hfEncodingBufOutputName         "BufOutput"
#define hfEncodingStrengthVectorName    "Strength Vector"
#define hfEncodingHandleName            "Handle"

/* Bit sizes for the pre-defined encoding types. */
#define hfEncodingNullBitSize                 0
#define hfEncodingLineBitSize                32
#define hfEncodingScalarBitSize               8
#define hfEncodingVectorBitSize              -1
#define hfEncodingIntegerBitSize             32
#define hfEncodingRealBitSize                64
#define hfEncodingTimeBitSize                64
#define hfEncodingRecordBitSize               0
#define hfEncodingExpandedBitSize             0
#define hfEncodingLineTraceOffsetBitSize     -1
#define hfEncodingArrayRecordBitSize          0  /* Unused */
#define hfEncodingStringBitSize              32     /* The bit size of an unsigned integer which is also 4 bytes. */
#define hfEncodingSummaryBitSize             -1
#define hfEncodingPackedRecordBitSize        -1
#define hfEncodingNotOutputBitSize            8
#define hfEncodingBufOutputBitSize            8
#define hfEncodingHandleSize                 -1     /* Not sure what size this should be. */

/* User defined encoding types preloaded into the interface. */
/* Added from 22 for System Verilog, Terrence 2002/10/08. */
#define hfEncodingStdLogic  20
#define hfEncodingBit       21
#define hfEncodingLogic     22
#define hfEncodingSVBit     23

#define hfEncodingStdLogicName  "StdLogic"
#define hfEncodingBitName       "Bit"
#define hfEncodingLogicName     "Logic"
#define hfEncodingSVBitName     "SVBit"

#define hfEncodingStdLogicBitSize   4
#define hfEncodingBitBitSize        1
#define hfEncodingLogicBitSize      2
#define hfEncodingSVBitBitSize      1

/* Defines for the values and strings for the StdLogic encoding type. */
#define StdL_U 0
#define StdL_X 1
#define StdL_0 2
#define StdL_1 3
#define StdL_Z 4
#define StdL_W 5
#define StdL_L 6
#define StdL_H 7
#define StdL_N 8    /* NOTE: Couldn't use "-" since that is not a valid
character in a "C" identifier. */

#define StdL_U_Str "U"
#define StdL_X_Str "X"
#define StdL_0_Str "0"
#define StdL_1_Str "1"
#define StdL_Z_Str "Z"
#define StdL_W_Str "W"
#define StdL_L_Str "L"
#define StdL_H_Str "H"
#define StdL_N_Str "-"

/* Defines for the values and strings for the Bit encoding type. */
#define BitL_0 0
#define BitL_1 1

#define BitL_0_Str "0"
#define BitL_1_Str "1"

/* Defines for the values and strings for the Logic encoding type. Terrence. */
#define LogL_0 0
#define LogL_1 1
#define LogL_Z 2
#define LogL_X 3

#define LogL_0_Str "0"
#define LogL_1_Str "1"
#define LogL_Z_Str "z"
#define LogL_X_Str "x"

/* User defined encoding types that are NOT preloaded into the interface.  The
** writer is responsible for adding these encoding types if they are used. */

/* hfEncodingVpdlogAName is the encoding used for vpdlog objects.  While the intiial
** value change is an unsigned int HF stringId, this encoding is intended to encompass
** the formats of all the string information associated with that string id.
*/
#define hfEncodingVpdlogAName     "VpdlogA"
#define hfEncodingVpdlogABitSize  32
#define hfEncodingVpdlogAVCSize   4

/* hfEncodingMsglogAName is the encoding used for msglog objects.  While the intiial
** value change is an unsigned int HF stringId, this encoding is intended to encompass
** the formats of all the string information associated with that string id.
*/
#define hfEncodingMsglogAName     "MsglogA"
#define hfEncodingMsglogABitSize  32
#define hfEncodingMsglogAVCSize   4


/* hfEncodingInt32Name is a 32 bit signed integer. Can use INT32 to define the
** variable to hold the value change for this encoding.
*/
#define hfEncodingInt32Name     "Int32"
#define hfEncodingInt32BitSize  32
#define hfEncodingInt32VCSize   4

/* hfEncodingInt64Name is a 64 bit signed integer. Can use INT64 to define the
** variable to hold the value change for this encoding.
*/
#define hfEncodingInt64Name     "Int64"
#define hfEncodingInt64BitSize  64
#define hfEncodingInt64VCSize   8

/* hfEncodingClassObjName is the encoding used for Class definition objects.
** The first 4 bytes is an unsigned integer representing the Obj ID string. Use
** hfGetStringVal() to convert the ID to the actual string. The 5th byte is
** based on the class eClassObjEvent. The user is responsible for swapping bytes
** of the first 4 bytes if needed.
*/
enum eClassObjEvent {
    eClsObjStart = 0,
    eClsObjEnd
};

#define hfEncodingClassObjName     "ClassObj"
#define hfEncodingClassObjBitSize  40
#define hfEncodingClassObjVCSize   5

/* Only 1 VCO is created for hfEncodingNull and is shared by all variables that
** have this encoding. That allows the VCO ID to predefined.
*/
#define hfEncodingNullVcoID     INT_MAX

/* Event defined values predefined within the VCD+ file. */

/** hfEventNone is the value of the "Event" argument when there are no
 * events.  Implicitly indicates a "dumpon" condition for value change
 * signals
 */
#define hfEventNone     0

/* hfEventDumpOff is the event value when value changes are turned off. */
#define hfEventDumpOff          1
#define hfEventDumpOffName          "DumpOff"

/** hfEventNewScope is the event value when line trace info goes to a
 * new scope. */
#define hfEventNewScope         2
#define hfEventNewScopeName         "NewScope"

/** hfEventPatternLoopCount is the event value indicating the number
 * of times the previous two value changes are to be repeated. */
#define hfEventPatternLoopCount     3
#define hfEventPatternLoopCountName "PatternLoopCount"

/** hfZeroDelayGlitchEvent is the event value indicating a zero delay
 * value change occured. */
#define hfZeroDelayGlitchEvent  4
#define hfZeroDelayGlitchEventName  "\nWDmultiple value changes"

/** hfEventNameOverflow is the event value used when no more user
 * defined events are available. */
#define hfEventNameOverflow 5
#define hfEventNameOverflowName     "\nESEventNameOverflow"

/** Event value when recording is turned back on.  Initially only used
 * for line trace data encodings. */
#define hfEventDumpOn       6
#define hfEventDumpOnName           "DumpOn"

/**
** NOTE: All Events after this point do not have a predefined value.  Instead,
** on the write side when they are needed, use hfAddEventName() to add the event
** and obtain a value to be used for the event.  Similarily on the read side,
** use hfGetEventFromName() to determine if a particular event has been assigned
** an event value.
**/

/** The folowing force events are added to an object's value change stream to
** indicate the current value change is being forced.  In most cases there will
** be a value change immediately following the event for the same time
** indicating the new value change that is being forced.  It is possible to not
** include a following value change at the same time.  In this case it indicates
** the value of the object stays the same but is now being forced at the time of
** the event.  A value change is not being forced if there is no force event
** immediately preceding it at the same time.
**/

/** This event indidates the "force freeze" form.  That means a force has been
** applied to this signal and stays in affect until it is explicitly canceled.
** */
#define hfEventSignalValueForcedName   "SignalValueForced"

/* Event "hfEventForcedWithMaskName" indicates there will be 2 value changes
** folowing this event with the same time.  The first value change is a bitmask
** representing the bits of the value change that are being force deposited.
** The logical bits are used to indicate the bits that are forced.  The second
** value represents the actual value of the force.  This event requires a
** release event to allow subsequent value changes to be allowed.
**
** NOTE: the application can not assume the event, mask, and value will be
** returned in three consective calls unless only a single object is
** using the callback routine.  E.G. if callbacks are registered on more than
** one signal, say sig1 and sig2. And if both signals used the same callback
** routine, then you might get the following:
**    sig1 event, sig2 event, sig1 mask, sig2 mask, sig1 value, sig2 value
** and so on.
*/
#define hfEventForcedWithMaskName       "SignalValueForcedWithMask"

/*
** This event is identical to hfEventForcedWithMaskName, except that the
** application can assume the event, mask, and value will be returned in
** 3 consecutive callbacks.  E.G. if callbacks are registered on more than
** one signal, say sig1 and sig2. And if both signals used the same callback
** routine, then you can assume that ;
**    sig1 event, sig1 mask, sig1 value,
** will be returned in 3 cosecutive calls and
**    sig2 event, sig2 mask,sig2 value
** will also be returned in 3 consecutive calls.
*/
#define hfEventForcedMask2Name       "SignalValueForcedMask2"

/*
** This event is identical to hfEventForcedMask2Name, except that some of the
** zero bits in the mask were changed from a force -depoist or vpi_put_value()
** call.  The event, mask, and value are still returned in three consecutive
** calls.
*/
#define hfEventForcedDepositForcedMask2Name       "SignalValueForcedDepositForcedMask2"

/** This event indidates the "force deposit" form.  That means a force has been
** applied to this signal and only is in affect till the next value change.
** This form of force is not cancelled.
** */
#define hfEventSignalValueForcedDepositName   "SignalValueForcedDeposit"

/* Event "hfEventForcedDepositWithMaskName" indicates there will be 2 value
** changes folowing this event with the same time.  The first value change is a
** bitmask representing the bits of the value change that are being force
** deposited.  The bits set must match the encoding type used for the value
** change.
**
** This event indicates the "force deposit with mask" form.  That means a force
** has been applied to this signal and only is in affect till the next value
** change.  This form of force is not cancelled by a release event.
** */
#define hfEventForcedDepositWithMaskName   "SignalValueForcedDepositWithMask"

/* Event "hfEventValueReleaseName" indicates the "release or force -cancel"
** form.  That means a replease has been applied at this time and will allow
** other deposit events to take place
*/
#define hfEventValueReleaseName    "SignalValueRelease"

/* Event "hfEventValueReleaseWithMaskName" indicates the "release or force
** -cancel" form. That means a replease has been applied at this time and will
** allow other deposit events to take place
*/
#define hfEventValueReleaseWithMaskName     "SignalValueReleaseWithMask"

/* Event "hfEventSaveStateName" indicates there will be 1 value change folowing
** this event with the same time.  This event indicates the saved state of the
** object.  That means the state has been applied to this signal and is only in
** affect till the next value change.
*/
#define hfEventSaveStateName            "SaveState"

/* Event "hfEventSaveStateWithMaskName" indicates there will be 2 value changes
** folowing this event with the same time.  The first value change is a bitmask
** representing the bits of the value change that are part of the saved state.
** The logical bits are used to indicate the bits that are state.  The second
** value change is the actual state value for the object.  It is only in affect
** till the next value change.
*/
#define hfEventSaveStateWithMaskName    "SaveStateWithMask"

#define hfHsimForceEventName            "HsimForce"
#define hfHsimReleaseEventName          "HsimRelease"
/* Event value when signal is moved out of/into the VPD dumping scope
 * by vcdpluson/vcdplusoff command
 */
#define hfHsimVPDRecOnEventName            "HsimVPDRecOn"

#define hfHsimVPDRecOffEventName           "HsimVPDRecOff"

#define hfHsimWriteNetEventName            "HsimWriteNet"

#define hfHsimWriteNetOffEventName         "HsimWriteNetOff"

#define hfHsimVPDShowValueEventName        "HsimVPDShowValue"

#define hfHsimVPDHideValueEventName        "HsimVPDHideValue"

/** Event value when tblog recording is turned back on. */
#define hfTblogOnEventName   "TbLogOn"
/** Event value when tblog recording is turned off. */
#define hfTblogOffEventName  "TbLogOff"

/** Event value when tblog recording is turned back on. */
#define hfMsglogOnEventName   "MsgLogOn"
/** Event value when tblog recording is turned off. */
#define hfMsglogOffEventName  "MsgLogOff"

/* The following event names are only defined if they are used in the VPD file. */

/* The following are defined for ports of a scope instance. */

/* dHfEventPortUnconnectedName event indicates the port is not connected. */
#define dHfEventPortUnconnectedName         "PortUnconnected"

/* dHfEventPortNoDriverName event indicates the port is not driven by any
** driver. */
#define dHfEventPortNoDriverName           "NoPortDriver"

/* dHfEventPortNoDUTDriverName event indicates the port only has active drivers
** within the scope instance and is not driven. For example an unconnected port. */
#define dHfEventPortNoDUTDriverName         "NoDUTPortDriver"

/* dHfEventPortNoTBDriverName event indicates the port only has active drivers
** outside the scope instance and is not driven. For example an unused port. */
#define dHfEventPortNoTBDriverName          "NoTBPortDriver"

/* dHfEventPortDUTDriverName event indicates the port is driven by one driver
** within the scope instance (DUT). */
#define dHfEventPortDUTDriverName           "DutPortDriver"

/** dHfEventPortMultiDUTDriverName is similar to the above event, but
 * driven by multiple drivers within the scope instance. */
#define dHfEventPortMultiDUTDriverName      "DutMultiPortDrivers"

/** dHfEventPortTBDriverName event indicates the port is driven by one
 * driver outside the scope instance (TB). */
#define dHfEventPortTBDriverName            "TbPortDriver"

/** dHfEventPortMultiTBDriverName is similar to the above event, by
 * driver by multiple drivers outside the scope instance. */
#define dHfEventPortMultiTBDriverName       "TbMultiPortDrivers"

/** dHfEventPortTBandDUTDriverName indicates a port driven by both a
 * driver (or drivers) within and outside the scope instance. And the
 * resolved value of the drivers within has the same strength range as
 * the resolved value of the drivers outside.  There are two strength
 * ranges, weak and strong.  The weak range covers the strengths from
 * small to large. The strong range covers the strenghts from pull to
 * supply. */
#define dHfEventPortTBandDUTDriverName         "TbDutPortDrivers"

/** dHfEventPortStTBandWkDUTDriverName indicates a port driven by both
 * a driver (or drivers) within and outside the scope instance. And the
 * resolved value of the drivers within has a weak strength range and
 * the resolved value of the drivers outside has a strong strength
 * range with value 0.  There are two strength ranges, weak and strong.
 * The waak range covers the strengths from small to large. The strong range
 * covers the strenghts from pull to supply. (see Verilog LRM 1364-2005
 * section 18.4.3.2 for more information */
#define dHfEventPortStTB0andWkDUTDriverName     "StTb0WkDutPortDrivers"

/** dHfEventPortStTBandWkDUTDriverName indicates a port driven by both
 * a driver (or drivers) within and outside the scope instance. And the
 * resolved value of the drivers within has a weak strength range and
 * the resolved value of the drivers outside has a strong strength
 * range with value 1.  There are two strength ranges, weak and strong.
 * The waak range covers the strengths from small to large. The strong range
 * covers the strenghts from pull to supply. (see Verilog LRM 1364-2005
 * section 18.4.3.2 for more information */
#define dHfEventPortStTB1andWkDUTDriverName     "StTb1WkDutPortDrivers"

/** dHfEventPortStTBandWkDUTDriverName indicates a port driven by both
 * a driver (or drivers) within and outside the scope instance. And the
 * resolved value of the drivers within has a weak strength range and
 * the resolved value of the drivers outside has a strong strength
 * range with value X.  There are two strength ranges, weak and strong.
 * The waak range covers the strengths from small to large. The strong range
 * covers the strenghts from pull to supply. (see Verilog LRM 1364-2005
 * section 18.4.3.2 for more information */
#define dHfEventPortStTBXandWkDUTDriverName     "StTbXWkDutPortDrivers"

/** dHfEventPortWkTBandStDUTDriverName indicates a port driven by both
 * a driver (or drivers) within and outside the scope instance. And the
 * resolved value of the drivers within has a strong strength range with
 * a value of 0 and the resolved value of the drivers outside has a weak
 * strength range There are two strength ranges, weak and strong.  The weak
 * range covers the strengths from small to large. The strong range covers
 * the strenghts from pull to supply. (see Verilog LRM 1364-2005
 * section 18.4.3.2 for more information */
#define dHfEventPortWkTBandStDUT0DriverName     "WkTbStDut0PortDrivers"

/** dHfEventPortWkTBandStDUTDriverName indicates a port driven by both
 * a driver (or drivers) within and outside the scope instance. And the
 * resolved value of the drivers within has a strong strength range with
 * a value of 1 and the resolved value of the drivers outside has a weak
 * strength range There are two strength ranges, weak and strong.  The weak
 * range covers the strengths from small to large. The strong range covers
 * the strenghts from pull to supply. (see Verilog LRM 1364-2005
 * section 18.4.3.2 for more information */
#define dHfEventPortWkTBandStDUT1DriverName     "WkTbStDut1PortDrivers"

/** dHfEventPortWkTBandStDUTDriverName indicates a port driven by both
 * a driver (or drivers) within and outside the scope instance. And the
 * resolved value of the drivers within has a strong strength range with
 * a value of X and the resolved value of the drivers outside has a weak
 * strength range There are two strength ranges, weak and strong.  The weak
 * range covers the strengths from small to large. The strong range covers
 * the strenghts from pull to supply. (see Verilog LRM 1364-2005
 * section 18.4.3.2 for more information */
#define dHfEventPortWkTBandStDUTXDriverName     "WkTbStDutXPortDrivers"

/** dHfEventPortTB0andDUT1DriverName indicates a port driven by driver(s)
 * resulting in a 0 value in the Testbench (outside the scope instance)
 * and also driver(s) with a 1 value in the Design Under Test (inside the
 * scope instance). Also the resolved values of the drivers inside and
 * outside both have the same strength range. */
#define dHfEventPortTB0andDUT1DriverName       "Tb0Dut1PortDrivers"

/** dHfEventPortTB0andDUTXDriverName indicates a port driven by driver(s)
 * resulting in a 0 value in the Testbench (outside the scope instance)
 * and also driver(s) with an X value in the Design Under Test (inside the
 * scope instance). Also the resolved values of the drivers inside and
 * outside both have the same strength range. */
#define dHfEventPortTB0andDUTXDriverName       "Tb0DutXPortDrivers"

/** dHfEventPortTB1andDUT0DriverName indicates a port driven by driver(s)
 * resulting in a 1 value in the Testbench (outside the scope instance)
 * and also driver(s) with a 0 value in the Design Under Test (inside the
 * scope instance). Also the resolved values of the drivers inside and
 * outside both have the same strength range. */
#define dHfEventPortTB1andDUT0DriverName       "Tb1Dut0PortDrivers"

/** dHfEventPortTB1andDUTXDriverName indicates a port driven by driver(s)
 * resulting in a 1 value in the Testbench (outside the scope instance)
 * and also driver(s) with a X value in the Design Under Test (inside the
 * scope instance). Also the resolved values of the drivers inside and
 * outside both have the same strength range. */
#define dHfEventPortTB1andDUTXDriverName       "Tb1DutXPortDrivers"

/** dHfEventPortTBXandDUT0DriverName indicates a port driven by driver(s)
 * resulting in an X value in the Testbench (outside the scope instance)
 * and also driver(s) with a 0  value in the Design Under Test (inside the
 * scope instance). Also the resolved values of the drivers inside and
 * outside both have the same strength range. */
#define dHfEventPortTBXandDUT0DriverName       "TbXDut0PortDrivers"

/** dHfEventPortTBXandDUT1DriverName indicates a port driven by driver(s)
 * resulting in an X value in the Testbench (outside the scope instance)
 * and also driver(s) with a 1 value in the Design Under Test (inside the
 * scope instance). Also the resolved values of the drivers inside and
 * outside both have the same strength range. */
#define dHfEventPortTBXandDUT1DriverName       "TbXDut1PortDrivers"

/** dHfEventRealXValueName  This event is used to indicate when a Real value has
** gone to "X".  It assumed the value of the variable will stay at "X" until the
** next value change occurs or the simulation ends.  This event should only be
** used with variables of data type real.
**/
#define dHfEventRealXValueName  "RealXValue"

/** dHfEventRealXValueName  This event is used to indicate when a Real value has
** gone to "Z".  It assumed the value of the variable will stay at "Z" until the
** next value change occurs or the simulation ends. This event should only be
** used with variables of data type real.
**/
#define dHfEventRealZValueName  "RealZValue"

/** dHfEventVcoFreed: Event indicates value change data for VCO linked to an
** iVco has stopped and VCO is free to be used again at a later time. This
** event also implies a dump off event.
*/
#define dHfEventVcoFreedName  "VcoFreed"

/** Events greater than 246 are used to indicate other events the user
 * may want to know about.
*/
/** hfEventEndVCBlock is event value when the end of the Value Change Block
** (VCB) has been reached. This event will only occur if the option
** dHfReportEndOfVCBlock is passed to hfAddObjToValueChangeList(). */
#define hfEventEndVCBlock   247
#define hfEventEndVCBlockName       "EndVCBlock"


/** generic object pointer */
/*typedef UINT64 hfHandle; */
typedef void* hfHandle;

/** Enumerated type to indicate the status to be return by hfFileStatus() */
typedef enum
{
    eHfFileComplete,       /**< True if the VCD+ file is complete. This
                            * means that the application writing the file
                            * has called the hfFileClose function. */
    eHfFileUpdate,         /**< True if the VCD+ file was updated since
                            * the last read. */
    eHfFileNoLocking,      /**< True if the iFileLockFlag argument to
                            *  the nfFileOpen function was False. */
    eHfFileSwapBytes,      /**< True if the VCD+ file was created on a
                            * platform with a different endian than
                            * the current platform (host). */
    eHfFileNewHierarchy,   /**< True if the VCD+ file has had
                            * hierarchy data added incrementally since
                            * the last time this function was called
                            * for this status. The status will always
                            * return False if the VCD+ file is
                            * complete. */
    eHfFileDeltaCycleUsed, /**< True if the VCD+ file contains any
                            * delta cycle information. */
    eHfFileVersionNbr,
    eHfFileWrapOccurred,
    eHfFileRewindWithHierOccurred,
    eHfFileEOF,
    eHfFileNativeVPD,
    eHfFileNbaQueActive,
    eHfHitReadError,        /** True if a read error was encountered. */
    eHfFileTimeCreated      /* Value in VPD file header when opened for writing. */
    /* Value obtained from time(2) system function. */
}
eHfFileStatus;

/** simulation time 32-bits */
typedef unsigned int tHfTime32;

/** simulation time 64-bits */
typedef struct sHfTime64
{
    tHfTime32       Time32;
    tHfTime32       Time64;
}
tHfTime64;

/** structure passed to callback function when the object is an array. */
typedef struct sVCArray
{
    tNatural  Offset;
    tNatural  NumWords;
    void*     pValue;
}
tVCArray;

/** Structure to pass to callback function when the object is summary
 * variable. */
typedef struct
{
    hfHandle    hScopeInst;
    void*       pValue;
}
tHfSummaryValue;


/*******************************************************************************
* @brief Structures used to iterate over Value Change data.
*******************************************************************************/
typedef struct sHfIterData
{
    tHfTime64               tTime;
    const unsigned char*    pValue;
    unsigned int            uDeltaCycle;
    unsigned int            uEvent;
    /* User input flags */
    unsigned int            bValAtEndOfTimeFlag:1;  /* When true return last value of time unit. */
    unsigned int            bSkipValChgTimeFlag:1;  /* When true skip returning
                                                       time of last value change prior to time
                                                       specified. */
    /* Flags returned. */
    unsigned int            bSwapFlag:1;
    unsigned int            bGlitchFlag:1;
    unsigned int            ValueSize:28;
} tHfIterData;

typedef enum
{
    eVciMinInvalid            = 0,

    eVciGetCurrentValue,
    eVciGetNextValue,
    eVciGetPrevValue,
    eVciReleaseMemory,

    /* Must be last value. */
    eVciMaxInvalid
}
eHfIterCmd;

/*******************************************************************************
***@brief eRefScpIterCmds is used by the function hfRefScpGet() function below
*** to specify what action to perform. The variable be a report or a refport array.
***
***    Cmd
*** eGetRefScpCnt: Return the number of elements the refObject contains
***                 pVal passed to ftn:   N/A.
***                 pHdl passed to ftn:   N/A.
***                 pVal returned fm ftn: Number of elements.
***                 pHdl returned fm ftn: N/A
***
*** eGetNthRefScp: Return the interface/modport handle with the Nth offset. 
***                Returns false if the Nth offset is invalid or interface/modport
***                    handle is not available.
***                 pVal passed to ftn:   Offset to requested interface/modport.
***                 pHdl passed to ftn:   N/A.
***                 pVal returned fm ftn: Offset of requested interface/modport.
***                 pHdl returned fm ftn: hfHandle of interface/modport.
***
*** GetNextRefScp: Return the next interface/modport from the refport.
***                 Returns false if already at last element of refport.
***                 pVal passed to ftn:   N/A.
***                 pHdl passed to ftn:   N/A.
***                 pVal returned fm ftn: Offset within the interface array refport.
***                 pHdl returned fm ftn: hfHandle of interface/modport.
*** 
*** eGetPrevRefScp: Return the previous interface/modport from the interface array refport.
***                 Returns false if already at first element of interface array refport.
***                 pVal passed to ftn:   N/A.
***                 pHdl passed to ftn:   N/A.
***                 pVal returned fm ftn: Offset of requested interface/modport
***                 pHdl returned fm ftn: hfHandle of interface/modport.
*******************************************************************************/

typedef enum {
    eGetRefScpCnt,
    eGetNthRefScp,
    eGetNextRefScp,
    eGetPrevRefScp,
    eInvalidRefScpCmd 
} eRefScpIterCmds;

/* Some defines to make working with tHfTime64 structures easier. */
#define hfTime64EQ( X, Y ) (   (X).Time32 == (Y).Time32 && (X).Time64 == (Y).Time64 )
#define hfTime64NE( X, Y ) (   (X).Time32 != (Y).Time32 || (X).Time64 != (Y).Time64 )
#define hfTime64LT( X, Y ) ( ( (X).Time32 <  (Y).Time32 && (X).Time64 == (Y).Time64 ) || (X).Time64 < (Y).Time64 )
#define hfTime64LE( X, Y ) ( ( (X).Time32 <= (Y).Time32 && (X).Time64 == (Y).Time64 ) || (X).Time64 < (Y).Time64 )
#define hfTime64GT( X, Y ) ( ( (X).Time32 >  (Y).Time32 && (X).Time64 == (Y).Time64 ) || (X).Time64 > (Y).Time64 )
#define hfTime64GE( X, Y ) ( ( (X).Time32 >= (Y).Time32 && (X).Time64 == (Y).Time64 ) || (X).Time64 > (Y).Time64 )

#define hfTime64EQZERO( X ) ( 0 == (X).Time32 && 0 == (X).Time64 )
#define hfTime64NEZERO( X ) ( 0 != (X).Time32 || 0 != (X).Time64 )

/*
*******************************************************************************************
*
* VHDL based types
*
*******************************************************************************************
*/
#define vhdEncodingStdLogicName     "STD_LOGIC"
#define vhdEncodingBitName          "BIT"
#define vhdEncodingBooleanName      "BOOLEAN"
#define vhdEncodingCharacterName    "CHARACTER"
#define vhdEncodingStringName       "STRING"
#define vhdEncodingIntegerName      "INTEGER"
#define vhdEncodingRealName         "REAL"
#define vhdEncodingStandardTimeName "/STANDARD/TIME"

#define vhdEncodingStdLogicBitSize  4
#define vhdEncodingBitBitSize       1
#define vhdEncodingBooleanBitSize   1
#define vhdEncodingCharacterBitSize 8
#define vhdEncodingStringBitSize    8
#define vhdEncodingIntegerBitSize   32
#define vhdEncodingRealBitSize      32
#define vhdEncodingStandardTimeBitSize 64

/*
*******************************************************************************************
*
* OVA based types
*
*******************************************************************************************
*/

/*
** The "ovaResultEncoding" encoding type is added to designs that will store Ova/Sav result data.
*/
#define ovaResultEncoding         "OvaResult"
#define ovaResultEncodingSize     9

/**
 * The following structure can be used to define the memory layout of
 * the value change data returned for the "ovaResultEncoding" encoding
 * type.  The reader is responsible to handle any byte swapping if
 * needed for all the data fields.
 *
 * @note Only ucOvaResult[0] holds the enum value "eOvaResult" defined
 * below. "ucOvaResult" is defined as 4 bytes to properly align the
 * first byte and to fill out to a word (4 byte) boundary.
 */
typedef struct
{
    unsigned int    uTimeOffset64;
    unsigned int    uTimeOffset32;
    char        ucOvaResult[4];
}
tOvaResultValueChange;

/** Enumerated type used for the Ova/Sva Result value. */
typedef enum
{
    eOvaFailure      = 0,
    eOvaSuccess      = 1,
    eOvaBlank        = 2,
    eOvaVacuous      = 3,
    eOvaIncomplete   = 4,
    eOvaSwitchedOn   = 5,
    eOvaSwitchedOff  = 6,
    eOvaSwitchedKill
}
eOvaResult;

/**
 * Ova/Sva reason data is stored for an object using a common encoding
 * ("hfEncodingString") and the attribute "hfAttType" set to
 * "eHfOvaAssertReason". Also the size of the value change is 12
 * bytes. The following structure can be used to define the memory
 * layout of the value change data returned for Ova/Sva reason data.
 * The reader is responsible to handle any byte swapping if needed for
 * all the data fields.
 * @note To retrieve the string corresponding to the value in
 * "uOvaReason", use hfGetStringVal().
 */
typedef struct
{
    unsigned int    uTimeOffset64;
    unsigned int    uTimeOffset32;
    unsigned int    uOvaReason;
}
tOvaReasonValueChange;

/** @brief Designators for the discrete memory optimizations. */
typedef enum vpdMemOptKind
{
    VMOKNoneK               = 0,
    VMOKLazyVCOK,
    VMOKGatesOptimizationK,
    VMOKActiveScopesK,
    VMOQLTblK,
    VMOKVhdlAliasK,
    VMOKFoldedHierK,
    VMOKVlUnitK,
    VMOKVlMdaAliasK,
    VMOKRealXZK,
    VMOKGlitchFilterK,
    VMOKForce,
    VMOKDynAlias,
    VMOKNbaQue,
    VMOKSigRdOpt,
    VMOK64BitSigOpSz,
    VMOKCloseOnFinish,      /* Cause memory to be freed and CBs to be turned
                               off when simulation finishes. */
    VMOKLrgVCB,

    /* Next must be last */
    vpdMemOptKindCount
} vpdMemOptKind;

#endif
