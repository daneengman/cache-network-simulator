/*
* vim: set sw=4 expandtab:
*******************************************************************************
*
* Copyright 2000-2001 Synopsys Inc. All rights reserved.
*
*  This Program is an unpublished work fully protected by the United States
*  copyright laws and is considered a trade secret belonging to Synopsys
*  Inc. It is not to be divulged or used by parties who have not received
*  written authorization from Synopsys Inc.
*
*                              W A R N I N G
*
*  THIS SOFTWARE AND MANUAL ARE BOTH PROTECTED BY UNITED STATES COPYRIGHT
*  LAW (TITLE 17, UNITED STATES CODE). UNAUTHORIZED REPRODUCTION AND/OR
*  SALES MAY RESULT IN IMPRISONMENT OF UP TO ONE YEAR AND FINES OF UP TO
*  $10,000 (17 USC 506). COPYRIGHT INFRINGERS MAY ALSO BE SUBJECT TO CIVIL
*  LIABILITY.
*
*******************************************************************************
*/

/* $Id$ $Author$ $DateTime$ */

#ifndef _hfattributes_h
#define _hfattributes_h

#ifdef XVCS_PLI
#endif

/*
*******************************************************************************************
*
* Attributes used by both Verilog and other tools
*
*******************************************************************************************
*/
/* Type "dHfAttType" is added to all variable and scope objects to indicate
 * this object's type.  Use the "eHfAttType" enumerated type when adding
 * attributes of type dHfAttType. The enumerated type must be stored as 4
 * bytes.
 */

#define dHfAttType               "type"
#define dHfAttTypeSize           4

/*
 * NOTE! NOTE! NOTE!
 * All new entries MUST go at the end of this enum list!
 * Failure to do so will result in all VCD+ files becoming invalid.
 */

typedef enum
{
    eHfVlogEvent        =  0,
    eHfVlogFunction     =  1,
    eHfVlogInteger      =  2,
    eHfVlogModule       =  3,
    eHfVlogNamedBegin   =  4,
    eHfVlogNamedFork    =  5,
    eHfVlogParameter    =  6,
    eHfVlogReg          =  7,
    eHfVlogReal         =  8,
    eHfVlogSupply0      =  9,
    eHfVlogSupply1      = 10,
    eHfVlogTask         = 11,
    eHfVlogTime         = 12,
    eHfVlogTri          = 13,
    eHfVlogTri0         = 14,
    eHfVlogTri1         = 15,
    eHfVlogTriAnd       = 16,
    eHfVlogTriOr        = 17,
    eHfVlogTriReg       = 18,
    eHfVlogWand         = 19,
    eHfVlogWire         = 20,
    eHfVlogWor          = 21,
    eHfVlogInvalidType  = 22,
    eHfVlogPort         = 23,
    eHfVlogBit          = 24,
    eHfVlogByte         = 25,
    eHfVlogChar         = 26,
    eHfVlogShortInt     = 27,
    eHfVlogInt          = 28,
    eHfVlogLongInt      = 29,
    eHfVlogLogic        = 30,
    eHfVlogShortReal    = 31,
    eHfVlogEnum         = 32,
    eHfVlogStruct       = 33,
    eHfVlogPackedStruct = 34,
    eHfVlogUnion        = 35,
    eHfVlogPackedUnion  = 36,
    eHfVlogInterface    = 37,
    eHfVlogIntegerEnum  = 38,
    eHfVlogProgram      = 39,
    eHfVlogModPort      = 40,
    eHfVlogClockingBlock= 41,
    eHfVlogPackage      = 42,
    eHfVlogSVUnit       = 43,
    eHfVlogInterfacePort= 44,
    eHfVlogModPortPort  = 45,
    eHfVlogClass        = 46,  // Currently only used by for vpdlog dumping
    eHfVlogString       = 47,  // Used for SV string, in addition to vpdlog dumping.
    eHfVlogChandle      = 48,  // Currently only used by for vpdlog dumping
    eHfVlogClassDef     = 49,
    eHfVlogClassObj     = 50,
    eHfVlogVirtIntf     = 51,
    eHfVlogVoid         = 52,
    eHfVlogRealWire     = 53,
    eHfVlogUdp          = 54,

    /* Following used for VHDL based objects. */
    /* NOTE: VHDL still uses it's own attribute type to store this. */
    eHfVhdTypePackage   = 101,
    eHfVhdTypeEntity    = 102,
    eHfVhdTypeArchitecture  = 103,
    eHfVhdTypeBlock     = 104,
    eHfVhdTypeProcess   = 105,
    eHfVhdTypeProcedure = 106,
    eHfVhdTypeFunction  = 107,
    eHfVhdTypeSignal    = 108,
    eHfVhdTypeVariable  = 109,
    eHfVhdTypeConstant  = 110,
    eHfVhdTypeGeneric   = 111,
    eHfVhdTypePort      = 112,

    /* Following used for OVA based objects. */
    eHfOvaAssertRecord  = 200,
    eHfOvaAssertClock   = 201,
    eHfOvaAssertResult  = 202,
    eHfOvaAssertReason  = 203,
    eHfOvaUnit          = 204,

    /* Following used for Nanosim based objects. */
    eHfNanoSigned       = 250,
    eHfNanoLogic        = 251,
    /* Following used for Nanosim object subtype when type is "eHfNanoSigned". */
    eHfNano_v           = 260,
    eHfNano_i           = 261,
    eHfNano_I           = 262,
    eHfNano_I_rms       = 263,
    eHfNano_didt        = 264,
    eHfNano_m           = 265,
    eHfNano_M           = 266,
    eHfNano_M_rms       = 267,
    eHfNano_dmdt        = 268,
    eHfNano_Pc          = 269,
    ehfNanoModule       = 270,

    /* Following used for SystemC based objects. */
    eHfSyscType_enum_begin1 = 300,  // begin/end needed by DVE
    eHfSyscTypeModule       = 300,

    eHfSyscTypeMethod       = 301,
    eHfSyscTypeThread       = 302,
    eHfSyscTypeCThread      = 303,

    eHfSyscType_bool        = 304,
    eHfSyscType_char        = 305,
    eHfSyscType_uchar       = 306,
    eHfSyscType_short       = 307,
    eHfSyscType_ushort      = 308,
    eHfSyscType_int         = 309,
    eHfSyscType_uint        = 310,
    eHfSyscType_long        = 311,
    eHfSyscType_ulong       = 312,
    eHfSyscType_sc_logic    = 313,
    eHfSyscType_sc_int      = 314,
    eHfSyscType_sc_uint     = 315,
    eHfSyscType_sc_bigint   = 316,
    eHfSyscType_sc_biguint  = 317,
    eHfSyscType_sc_bv       = 318,
    eHfSyscType_sc_lv       = 319,
    eHfSyscType_sc_string   = 320,
    eHfSyscType_enum_end1   = 320,  // begin/end needed by DVE
    // gap left here for msglog/tblog 321-349 eHfSysc types start again at 350
    // below.

    // The following are tb/msg/vpd log related
    eHfVpdlogType_scope     = 321,
    eHfVpdlogType_master    = 322,
    eHfVpdlogType_stream    = 323,
    eHfVpdlogType_msgstream = 324,
    eHfVpdlogType_namedmsgstream = 325,
    // Do not exceed 349 for msglog/tbog numbers if more are needed start a new block
    // of messages numbers at the end.

    eHfSyscType_enum_begin2 = 350,  // begin/end needed by DVE
    eHfSyscType_int64       = 350,  // added later on
    eHfSyscType_uint64      = 351,  // added later on
    // room for 8 additional Sysc types
    eHfSyscType_struct      = 360,
    // room for additional Sysc entries
    eHfSyscType_enum_end2   = 399,  // begin/end needed by DVE

    eHfAttType_enum_end     = 399,  // used for array size in vpdxml__.cc

    /* High value for Unsupported type. */
    eHfUnsupported      = 65535
}
eHfAttType;

/* Type "dHfAttSubType" is added to variable and scope objects only when needed.
 * The enumerated type must be stored as 4 bytes.
 */

#define dHfAttSubType           "subtype"
#define dHfAttSubTypeSize       4

/*
 * NOTE! NOTE! NOTE!
 * All new entries MUST go at the end of this enum list!
 * Failure to do so will result in all VCD+ files becoming invalid.
 */

typedef enum
{
    eHfAttSubTypeInvalid   =  0,
    eHfAttEnumBit          =  1,
    eHfAttEnumLogic        =  2
}
eHfAttSubType;

/* Attribute "dHfAttVariableSizeArrayType" is added to and expanded variable to indicate an array of object
** whose size changes during the simulation. Use the "eHfAttVariableSizeArrayType" as the possible values for
** this attribute.
*/

#define dHfAttVariableSizeArrayType           "VariableArrayType"
#define dHfAttVariableSizeArrayTypeSize       4

/*
 * NOTE! NOTE! NOTE!
 * All new entries MUST go at the end of this enum list!
 * Failure to do so will result in all VCD+ files becoming invalid.
 */

typedef enum
{
    eHfAttInvalid       =  0,
    eHfAttDynamic       =  1,
    eHfAttAssociative   =  2,
    eHfAttQueue         =  3
}
eHfAttVariableSizeArrayType;

/* Type "dHfAttEncoding" is added to any variable that does not have value changes
** of it's own.  It indicates what it's encoding would have been. For example it
** is used for all SV variables within a packed structure or union.
** NOTE: The encoding may not match the packed parent's encoding.
*/
#define dHfAttEncoding          "encoding"
#define dHfAttEncodingSize      4

/* Type "dHfAttPort" is added to all variable objects to indicate
** this variable is also a port.  Use the "eHfAttPortType" enumerated type
** when adding attributes of type dHfAttPort. The enumerated type must be
** stored as 4 bytes.
*/
#define dHfAttPort               "Port"
#define dHfAttPortSize           4

/*
 * Port values start at one (1) to allow zero (0) to indicate an invalid entry.
 * NOTE! NOTE! NOTE!
 * All new entries MUST go at the end of this enum list!
 * Failure to do so will result in all VCD+ files becoming invalid.
 */

typedef enum
{
    eHfAttPortInvalid   = 0,
    eHfAttPortIn        = 1,
    eHfAttPortOut       = 2,
    eHfAttPortInOut     = 3,
    /* Following used by SystemC. */
    eHfAttPortMixed     =  4,
    eHfAttPortBuffer    =  5,
    eHfAttPortInternal      =  6,
    eHfAttPortInResolved    =  7,
    eHfAttPortOutResolved   =  8,
    eHfAttPortInOutResolved =  9
}
eHfAttPortType;

/* Type "dHfAttSize" is added to a variable object to specify the number of
** logical bits contained in the object.
*/
#define dHfAttSize               "size"
#define dHfAttSizeSize           4

/* Type "dHfAttDefName" is added to a scope object to specify the definition name
** of this instance.  The size argument is set the the string length of the
** definition name and value argument points to the first character of the character
** string.
*/
#define dHfAttDefName           "DefName"

/* Type "vhdAttDefinitionName" is added to a scope object to specify the definition
** name of this instance.  The size argument is set to the string length of the
** definition name and value argument points to the first character of the character
** string.
*/

/* Type "dHfAttMdaExpandedToBitLevel" is added to a variable object to specify that the
** packed ranges of the object are also fully expanded under this object.
*/
#define dHfAttMdaExpandedToBitLevel      "MdaExpandedToBitLevel"
#define dHfAttMdaExpandedToBitLevelSize  0

/* Type "dHfReferenceScopeID" is added to an object to indicate this object
** is referencing another scope ID.  The reader is responsible to handle any
** byte swapping of the value if needed. hfGetScopeHandle() can be used to
** convert the ID to a valid hfHandle.
** UPDATE: To support a reference arry object, please use the new APIs
** hfRefScpInit()/hfRefScpGet()/hfRefScpDestroy() to get the hfHandle
** for the referenced objects.
**/
#define dHfReferenceScopeID     "RefScopeID"
#define dHfReferenceScopeIDSize 4

/* Type "dHfFirstExpVarID" is added to an expanded variable object to indicate
** it is equivalent to another expanded variable already stored in the VPD file.
** The VPD reader is responsible to handle any byte swapping of the value if
** needed. hfGetScopeHandle() can be used to convert the ID to a valid hfHandle
**/
#define dHfFirstExpVarID        "FirstExpVarID"
#define dHfFirstExpVarIDSize    4


/* To help explain the following attributes to support packed and/or unpacked
** dimensions, here is a table that lists all the combinations for variables.
**
**                                                           d
**                                                           H
**                                                           f
**                                                           A
**                                                   d       t               d
**                                                   H       t       d       H
**                                                   f       T       H       f
**                                                   A       r       f       A
**                                                   t       u       A       t
**                                                   t       e       t       t
**                                                   D       D       t       R
**                                   h       h       i       i       L       i
**                                   f       f       m       m       e       g
**                                   V       V       e       e       f       h
**                                   l       l       n       n       t       t
**                                   o       o       s       s       B       B
**                                   g       g       i       i       o       o
**                                   M       L       o       o       u       u
**                                   s       s       n       n       n       n
**                                   b       b       s       s       d       d
*----------------------------------------+-------+-------+-------+-------+-------
*reg            p0u0;                x       x       x       x       x       x
*reg            p0u1 [5:4];          x       x       1       x      "5"     "4"
*reg            p0u2 [5:4][7:6];     x       x       2       x     "5 7"   "4 6"
*reg [1:0]      p1u0;                1       0       x       x       x       x
*reg [1:0]      p1u1 [5:4];          1       0       1       x      "5"     "4"
*reg [1:0]      p1u2 [5:4][7:6];     1       0       2       x     "5 7"   "4 6"
*reg [1:0][3:2] p2u0;                x       x       2       0     "1 3"   "0 2"
*reg [1:0][3:2] p2u1 [5:4];          x       x       3       1    "5 1 3" "4 0 2"
*reg [1:0][3:2] p2u2 [5:4][7:6];     x       x       4       2  "5 7 1 3" "4 6 0 2"
**
** System Verilog structs can only have any unpacked dimensions so only use the
** dHfAttDimensions attribute.
**
*----------------------------------------+-------+-------+-------+-------+-------
*UPS            p0u0;                x       x       x       x       x       x
*UPS            p0u1 [5:4];          x       x       1       x      "5"     "4"
*UPS            p0u2 [5:4][7:6];     x       x       2       x     "5 7"   "4 6"
**
** System Verilog packed struct can have both packed and unpacked dimensions.
** But these structures only use dHfAttDimensions and dHfAttTrueDimensions
** attribute to specify all combinations of packed and unpacked attributes.
*----------------------------------------+-------+-------+-------+-------+-------
*PS             p0u0;                x       x       x       x       x       x
*PS             p0u1 [5:4];          x       x       1       x      "5"     "4"
*PS             p0u2 [5:4][7:6];     x       x       2       x     "5 7"   "4 6"
*PS  [1:0]      p1u0;                x       x       1       0      "1"     "0"
*PS  [1:0]      p1u1 [5:4];          x       x       2       1     "5 1"   "4 0"
*PS  [1:0]      p1u2 [5:4][7:6];     x       x       3       2    "5 7 1" "4 6 0"
*PS  [1:0][3:2] p2u0;                x       x       2       0     "1 3"   "0 2"
*PS  [1:0][3:2] p2u1 [5:4];          x       x       3       1    "5 1 3" "4 0 2"
*PS  [1:0][3:2] p2u2 [5:4][7:6];     x       x       4       2  "5 7 1 3" "4 6 0 2"
**
** System Verilog enums need to use the Msb and Lsb attributes to give the left
** and right indicies of the enum that is stored as an encoding.  Encodings do
** not have attributes or any other way of keeping track of the indicies.  If a
** variable uses an enum's encoding AND it has any packed and/or unpacked
** dimensions, then dHfAttDimensions and dHfAttTrueDimensions must be used.
*/

/* Type "dHfAttDimensions" is added to arrays. This attribute specifies the
** number of dimensions of the multidimensional arrays.  For the following example, the
** dimesion value would be 3.
**   reg [7:0] mem1 [1:4][2:5][3:6];
*/
#define dHfAttDimensions        "Dimensions"
#define dHfAttDimensionsSize    4

/* Type "dHfAttTrueDimensions" is added to System Verilog MDAs that have at
** least 2 packed dimensions, or is either a packed aggregate or enum and has
** packed and/or unpacked dimensions.  This attribute specifies the number of unpacked
** dimensions while dHfAttDimensions indicates the total number of packed and
** unpacked dimensions.  If the MDA only has unpacked dimensions, this
** attributes value is 0.  A better word in the attribute name should have been
** "Unpacked" instead of "True".
** For example, bit [3:0][7:0] PackedBits [-2:-1];
**   dHfAttDimensions         => 3
**   dHfAttLeftBound          => "-2 3 7"
**   dHfAttRightBound         => "-1 0 0"
**   dHfAttTrueDimensions     => 1
 */
#define dHfAttTrueDimensions        "TrueDimensions"
#define dHfAttTrueDimensionsSize    4

/* Type "dHfAttDimensionsInParent" is added to expanded variables and records where the parent's
** attributes need to be accessed to get more dimension info.
*/
#define dHfAttDimensionsInParent        "DimensionsInParent"
#define dHfAttDimensionsInParentSize    0

/* Type "dHfAttLeftBound" is added to arrays. This attribute specifies the
** number of the left index for each of the dimensions as a character string
** with values separated by spaces.
** For example, an array with 3 dimensions of 0 to 4, 2 to 6, 0 to 31 would
** have a value of "0 2 0".
**
** NOTE. There is not an equivalent size define. The size given is the length
** of the string passed in.
*/
#define dHfAttLeftBound         "LeftBound"

/* Type "dHfAttRightBound" is added to arrays. This attribute specifies the
** number of the right index for each of the dimensions as a character string
** with values separated by spaces.
** For example, an array with 3 dimensions of 0 to 4, 2 to 6, 0 to 31 would
** have a value of "4 6 31".
**
** Note: There is not an equivalent size. The size given is the length
** of the string passed in.
*/
#define dHfAttRightBound        "RightBound"

/* Type "dHfAttMdaOffset" is added to a variable that represents an element of
 * an MDA.  This attribute specifies the offset of this element. A Size of
 * 4 bytes and an unsigned integer value pointer should be passed as arguments.
 */

#define dHfAttMdaOffset         "MdaOffset"
#define dHfAttMdaOffsetSize     4

/* Attribute "dHfAttDaiDir" is added to the design handle to indicate the full
** path to the DaiDir directory.  This can be an absolute path or relative to
** attribute SimulatorRunLocation.  The size argument is set to the string
** length of the path name plus one for the null character. The value
** argument points to the first character of the string.
*/
#define dHfAttDaiDir            "DaiDir"

/* Attribute "dHfAttSimulatorCompileVersion" stores the compiler version used to create the simulator
** used that writes the vpd file. It stores the string contained in VCS_VERSION define in version_defines.h
** the value of the arg points to the first character of the string.  NOTE: The length does not include the trailing null
** character.
*/
#define dHfAttSimulatorCompileVersion      "SimulatorCompileVersion"

/* Attribute "dHfAttSimulatorCompileLocation" is used to store the working directory where the simulator was
** compiled from.  The size argument is set to the string length of the path name.  The value argument
** points to the first character of the string.  NOTE: The length does not include the trailing null
** character.
*/
#define dHfAttSimulatorCompileLocation      "SimulatorCompileLocation"

/* Attribute "dHfAttSimulatorRunLocation" is used to store the working directory where the simulator is executed
** from.  The size argument is set to the string length of the path name.  The value argument points to the
** first character of the string.  NOTE: The length does not include the trailing null character.
*/
#define dHfAttSimulatorRunLocation          "SimulatorRunLocation"

/* Attribute "dHfAttSimulatorLocation" is used to store the directory where simulation executable is located.
** This can be an absolute path or relative to SimulatorRunLocation.
** The size argument is set to the string length of the path name.  The value argument points to the
** first character of the string.  NOTE: The length does not include the trailing null character.
*/
#define dHfAttSimulatorLocation             "SimulatorLocation"

/* Attribute "dHfAttVpdLocation" is used to store the path to VPD file. The path can be absolute or
** relative to SimulatorRunLocation. It can be usefull, when VPD is relocated together with simulation
** database file (see spec "Support for relocation of generated files"
** on http://wwwvcs.synopsys.com/twikiAll/cgi-bin/view.cgi/Visualization/DveMoveSimv).
** The size argument is set to the string length of the path name.  The value argument points to the
** first character of the string.  NOTE: The length does not include the trailing null character.
*/
#define dHfAttVpdLocation                   "VpdLocation"

/* Attribute "dHfAttSimulatorName" is used to store the simulator's name. It is only the base name, not the full
** path to the simulator.  The size argument is set to the string length of the path name.  The value argument
** points to the first character of the string.  NOTE: The length does not include the trailing null
** character.
*/
#define dHfAttSimulatorName                 "SimulatorName"

/// @brief Contiguous representation of the command line arguments.
///
/// NUL-separated and NUL-terminated (so the last two bytes are always \0\0).
#define dHfAttSimulatorRuntimeArgs          "SimulatorRuntimeArgs"

/// @brief Directories where included files may be found.
///
/// Initially supported for Verilog's `include.  It could be used for SystemC
/// as well.
///
/// The value is a pointer to an array of characters where the directory names
/// are laid end to end with \0 separators.  There is an additional \0 at the end
/// of the last directory. For instance, "a\0b\0\0" encodes the array of
/// directory names { "a", "b" }.
///
/// There is no need to memcpy this value, as it is always well-aligned.  The
/// size of the attribute is the number of characters, NULs included.
#define dHfAttCompilerIncludeDirs           "CompilerIncludeDirs"

/// @brief User supplied string associated with the VPD file.
///
/// The value is a pointer to an array of characters whose value can be used
/// to comunicate information between the writer and reader applications of
/// congruency files. It is recomended that the writer place some tag at the
/// begining of the string so reader applications can determine who wrote it
/// and what it is to be used for  E.G. "WriterApp:Version".
#define dHfAttCongUserData           "CongUserData"

/* dHfAttVarLocOffset will be added to all variables except those that are global
** when the env. variable VPDVARFILEINFOFLAG is set. `include and functions/tasks
** will be accounted while calculating offset. The size may be either 1, 2, or 4
** to indicate the value is a pointer to either an unsigned char, short, or int
** respectively.  The reader is responsible to handle any byte swapping if needed
** */
#define dHfAttVarLocOffset            "varLocOffset"

/* Type "dHfAttStateFlag" is added to a variable or element indicating this
** object has 1 or more state bits.  This object will have save state event data
** stored as its initial value.  This attribute itself has no attribute value.
*/
#define dHfAttStateFlag         "StateFlag"
#define dHfAttStateFlagSize     0

/* Type "dHfAttClockFlag" is added to a variable or element indicating this
** object is a clock.  This attribute itself has no attribute value.
*/
#define dHfAttClockFlag         "ClockFlag"
#define dHfAttClockFlagSize     0

/* Type "dHfAttElementCount" is added to a Record or Expanded variable to
** indicate the total number of elements contained within this object.
*/
#define dHfAttElementCount      "ElementCount"
#define dHfAttElementCountSize  4

/* dHfAttEncodingUnit will be added to all variables needing to specify the
** units of the Y-axis when displaying.  Possible values could be "V" for volts
** or "A" for amps.  The size argument is set to the string length of the name
** including the trailing null character.  The value argument points to the
** first character of the string.
*/
#define dHfAttObjValUnit             "ObjValUnit"

/* dHfAttEncodingResolution will be added to all variables needing to specify
** the resolution of the Y-axis when displaying.  It indicates the resolution of
** the object when changing the value by 1.  Use the "eHfAttResolution"
** enumerated type when adding attributes of type dHfAttEncodingResolution.  The
** enumerated type must be stored as 1 byte.
*/
#define dHfAttObjValResolution        "ObjValResolution"
#define dHfAttObjValResolutionSize    1

typedef enum
{
    eHfAttFemto     =  -15,
    eHfAtt10Femto   =  -14,
    eHfAtt100Femto  =  -13,
    eHfAttPico      =  -12,
    eHfAtt10Pico    =  -11,
    eHfAtt100Pico   =  -10,
    eHfAttNano      =  -9,
    eHfAtt10Nano    =  -8,
    eHfAtt100Nano   =  -7,
    eHfAttMicro     =  -6,
    eHfAtt10Micro   =  -5,
    eHfAtt100Micro  =  -4,
    eHfAttMilli     =  -3,
    eHfAttCenti     =  -2,
    eHfAttDeci      =  -1,
    eHfAttNone      =  0,
    eHfAttDeca      =  1,
    eHfAttHecto     =  2,
    eHfAttKilo      =  3,
    eHfAttMega      =  6,
    eHfAttGiga      =  9,
    eHfAttTera      =  12,
    eHfAttPeta      =  15
}
eHfAttResolution;

/* dHfAttInitMinMaxValues is added to all variable objects that need to indicate
** the initial minimum and maximum value range.  The attribute
** dHfAttObjValResolution must also be set to define the scale of these values.
** The value of the attribute is a string consisting of two signed double values
** with a minimum of 8 digits of precision.  On output, this can be done with
** "sprintf(buf, "r%.8g r%.8g", minVal, maxVal );"  This is required because
** previously these values were stored as 2 signed integers.  The 2 values
** consisting of the minimum and maximum value respectively with a space
** character in between.  For example "-5 10" would indicate the minimum value
** is -5 and the maximum value is 10. The size argument is set to the string
** length of the name including the trailing null character.  The value argument
** points to the first character of the string.
*/
#define dHfAttInitMinMaxValues           "InitMinMaxValues"

/* dHfAttDrawStyle is added to all variable objects to indicate the type of
** drawing style to be used.  Use the "eHfAttDrawStyle" enumerated type
** when adding attributes of type dHfAttDrawStyle. The enumerated type must be
** stored as 1 byte. The default drawing style is piecewise linear (PWC).
*/
#define dHfAttDrawStyle                 "DrawStyle"
#define dHfAttDrawStyleSize             1

/*
 * NOTE! NOTE! NOTE!
 * All new entries MUST go at the end of this enum list!
 * Failure to do so will result in all VCD+ files becoming invalid.
 */
typedef enum
{
    eHfAttPWC   =  0,       // Piecewise constant drawing style
    eHfAttPWL   =  1        // Piecewise linear drawing style
}
eHfAttDrawStyle;

#define dHfAttHsimDerivedNode      "HsimDerivedNode"
#define dHfAttHsimDerivedNodeSize  1

/*
* Used for gate level aliasing for inverters and buffers inputs/outputs.
*/
#define dHfAttGateAliasType     "GateAliasType"
#define dHfAttGateAliasTypeSize  1

#define dHfAttGateAliasId       "GateAliasId"
#define dHfAttGateAliasIdSize   4

/*
*******************************************************************************************
*
* Verilog based attributes
*
*******************************************************************************************
*/

/* Verilog Data Type Define.  Used with "hfFileSetDataTypeString()". */
#define dHfDataTypeString       "Verilog"

/* Some defines for scalar nets that includes default strengths. */
#define ST0 0xd8
#define ST1 0xd9
#define STX 0xdb
#define HIZ 0x02

/* Type "hfVlogSigned" is added to variables that are signed.  This was added in Verilog 2000
*/
#define hfVlogSigned            "signed"
#define hfVlogSignedSize        0

/* Type "hfVlogAutomatic" is added to variables and scope instances that are dynamic.  This was added for
** System Verilog
*/
#define hfVlogAutomatic            "automatic"
#define hfVlogAutomaticSize        0

/* Type "hfVlogBit" is added to a variable object when the net is a bit of an
 * expanded variable.  The value is the bit index of this element object. If the
 * vector "aWire[2:0]" or "aWire[0:2]" is expanded, then for either case the
 * object associated to "aWire[2]" would have the attributue value of "2".  A
 * Size of 4 bytes and the address of an integer should be passed as arguments.
 */

#define hfVlogBit               "bit"
#define hfVlogBitSize           4

/* Type "hfVlogTagWidth" is added to a variable object of packed tagged union
 * type, to indicate width of tag. Note, that dHfAttSize value for variable
 * is increased to include the tag width. So, user would get both tag and packed
 * union value, packed as a single integral value (tag is stored towards MSB).
 * So using TagWidth attribute, user may break that dumped value into tag and
 * actual union-value.
 */
#define hfVlogTagWidth           "TagWidth"
#define hfVlogTagWidthSize       4

/* Type "hfVlogSvNettype" is added to a variable object which is of SV nettype.
 * A Size of 0 bytes and a NULL value pointer should be passed as arguments.
 */
#define hfVlogSvNettype           "SvNettype"
#define hfVlogSvNettypeSize       0

/* Type "hfVlogExpanded" is added to a variable object when the net is
 * expanded.  A Size of 0 bytes and a NULL value pointer should be passed as
 * arguments.  Note, this is only used on the read side for compatibility.
 */

#define hfVlogExpanded          "expanded"
#define hfVlogExpandedSize      0

/* Type "hfVlogLsb" is added to a variable object when the net is a vector.
 * This attribute specifies the rightmost vector bit. A Size of 4 bytes and a
 * integer value pointer should be passed as arguments.
 */

#define hfVlogLsb               "lsb"
#define hfVlogLsbSize           4

/* Type "hfVlogMsb" is added to a variable object when the net is a vector.
 * This attribute specifies the leftmost vector bit. A Size of 4 bytes and a
 * integer value pointer should be passed as arguments.
 */

#define hfVlogMsb               "msb"
#define hfVlogMsbSize           4

/* Type "hfVlogMemory" is added to an expanded variable when it is
 * a memory.  A Size of 0 bytes and a NULL value pointer should be passed as
 * arguments.
 */

#define hfVlogMemory            "Memory"
#define hfVlogMemorySize            0

/* Type "hfVlogMemAdrs" is added to a variable that represents an element of
 * a memory.  This attribute specifies the address of this element. A Size of
 * 4 bytes and a integer value pointer should be passed as arguments.
 */

#define hfVlogMemAdrs           "MemAdrs"
#define hfVlogMemAdrsSize           4


/* Type "hfVlogFileInfo" is added to all scope objects to list the files
 * and line numbers that make up the source for this scope. Since a module
 * may have a `include statement, this attributes may have one or more entries
 * to specify each segment. The format for each segment is:
 *
 * <Start Line Nbr>\n<End Line Nbr>\n<File Name>[\n...]\0
 *
 * <Start Line Nbr>  First line of this segment.
 * <End Line Nbr>    Last line of this segment.
 *                   NOTE: <End Line Nbr> will be zero for named blocks, tasks, & functons.
 * <File Name>       The file name as given by the simulator.
 *
 * The last character must be the NULL character to indicate the end of the string.
 *
 * The size given for this attribute is the length of the string including the NULL character
 * at the end.
 *
 * NOTE: This attribute is also added to the design object to act as a flag indicating file
 * info is available for all scopes.  In this way, the reading software only needs to check once
 * to see if the file information is available. When added to the design object, the size and value
 * fields should be set to zero (0) and NULL respecively.
 */

#define hfVlogFileInfo          "FileInfo"

/* Type "hfVlogOptions" is added to the design handle to specify whether certain sets of data are
** available from this design.  See the following defines for the current list of options.
*/
#define hfVlogOptions           "Options"
#define hfVlogOptionsSize       4

/* A set of defines used to set bits within the "Options" attribute. */
#define hfVlogOptionsDrivers            0x1
#define hfVlogOptionsLines              0x2
#define hfVlogOptionsPorts              0x4
#define hfVlogOptionsAms                0x8
#define hfVlogOptionsSystemVerilog      0x10
#define hfVlogOptionsV2K                0x20
#define hfVlogOptionsCongruencySaveState    0x40
#define hfVlogOptionsCongruencyReplay   0x80

/* Following defines are used to inform Virsim of any generated files from VCS for Spice and
** Mixed design wrapper files
*/
#define hfVlogSpiceGlobalFileName   "GlobalFileName"
#define hfVlogSpiceShadowFileName   "ShadowFileName"
#define hfVlogMixWrapperFileName    "MixWrapperFileName"

/* Type "hfVlogHideObject" is added to a scope or variable that is not to be displayed in Virsim or
** translators.
*/
#define hfVlogHideObject            "HideObject"
#define hfVlogHideObjectSize        0

/* Type "hfVlogUnit" is added to a scope to indicate the $unit associated with
** this scope instance.  When writing this attribute, a Size of 4 bytes and a
** integer value pointer should be passed as arguments.  The reader is
** responsible to handle any byte swapping of the integer value if needed.
*/
#define hfVlogUnit                  "SVUnit"
#define hfVlogUnitSize              4

/* hfVlogClassDefName is string added to class objects to specify the object's
** class definition. The size of the attribute is the string length including
** the terminating NULL character.
*/
#define hfVlogClassDefName          "ClassDefName"

/* The dHfVlogClassMbrDepth attribute is added to the node of a class
** definition to indicate if it is defined in a base class.  A value of zero
** indicates the node is defined in the base class. A value of one indicates
** the node is defined in the class definition the current definition is
** derived from. etc.
** integer value pointer should be passed as arguments.  The reader is
** responsible to handle any byte swapping of the integer value if needed.
*/
#define dHVlogClassMbrDepth         "ClassMbrDepth"
#define dHVlogClassMbrDepthSize     4

/*
** The dhVlogModPortName attribute is added only for virtual modport nodes
** of a class.
 */
#define dHVlogModPortName           "VlogModPortName"


/*
*******************************************************************************************
*
* VHDL based attributes
*
*******************************************************************************************
*/
/* VHDL Data Type Define.  Used with "hfFileSetDataTypeString()". */
#define vhdDataTypeString       "VHDL"

/*
** Type "vhdAttType" is added to all objects to indicate the object's type.
** Use the "eVhdType" enumerated type (see hftypes.h) when adding
** attributes of type vhdAttType. The enumerated type must be stored as 4
** bytes.
*/
#define vhdAttType              "Type"
#define vhdAttTypeSize          4


/*
** Type "vhdAttPort" is added to only those variable objects that are ports
** of a scope.  Use the "eVhdPortSymbol" enumerated type (see hftypes.h)
** when adding attributes of this type. The enumerated type must be stored as 4 bytes.
*/
#define vhdAttPort              "Port"
#define vhdAttPortSize          4

/*
** NOTE! NOTE! NOTE!
** Failure to do so will result in all VCD+ files becoming invalid.
** When adding new types, add to end of list.
** (Existing VCD+ files may depend on these definitions.)
**
** Note: These defines are the same as eDsiPortVariableSymbol in
**       dsapi__.h but are defined here so that VCD+ writers
**       do not need to #include dsapi__.h. (The VCD+ reader
**       must map to eDsiPortVariableSymbol.)
*/
typedef enum eVhdPortSymbol
{
    eVhdPortInput       = 1,
    eVhdPortOutput      = 2,
    eVhdPortInout       = 3,
    eVhdPortBuffer      = 4,
    eVhdPortLinkage     = 5,
    eVhdPortNoSymbol    = 6
}
eVhdPortSymbol;

/* Type "vhdAttBit" is added to a variable object when the net is a bit of an
** expanded vector.  A Size of 4 bytes and the address of an integer should be
** passed as arguments.
**
** Note: For an array of arrays, each sub-array would be both an array and a
**       bit of an array. Therefore, these sub-arrays would have the bounds
**       attributes as well as this bit attribute.
*/
#define vhdAttBit               "Bit"
#define vhdAttBitSize           4

/* Type "vhdAttEnumIndexType" is added to an array object when the indexes of
** the array are an enumerated type. The value of this attribute specified
** the EncodingType of the indexes. A Size of 4 bytes and the address of an
** integer should be passed as arguments.
*/
#define vhdAttEnumIndexType     "EnumIndexType"
#define vhdAttEnumIndexTypeSize 4

/* "vhdAttFileInfo" is added to all entity/architecture instances. It specifies the
 * file name and line numbers of the source code for the instance. The format of
 * the data is "<filename> <starting line number> <ending line number>. Since
 * entity/architecture instances are made up of two elements, this attribute
 * must specify the location of the source code for both elements. For example:
 * "file1.vhd 50 59 file2.vhd 100 199". All other vhdl instances will only have 1
 * entry.
 */
#define vhdAttFileInfo          "FileInfo"

/* Type "vhdAttSimType" is added to objects to specify the type of simulator.
**
** Use the eVhdSimType enumerated values for this attribute.
*/
#define vhdAttSimType           "SimType"
#define vhdAttSimTypeSize       4

/*
** NOTE! NOTE! NOTE!
** When adding new types, add to end of list.
** Failure to do so will result in all VCD+ files becoming invalid.
** (Existing VCD+ files may depend on these definitions.)
*/
typedef enum eVhdSimType
{
    eVhdSimTypeEvent = 1,
    eVhdSimTypeCycle= 2
}
eVhdSimType;


/* This attribute is used to provide a name to be displayed for an enumeration names.
** The size argument is set the the string length of the name and the value argument points to
** the first character of the string.
*/
#define vhdAttEncodingTypeDisplayName   "EncodingTypeDisplayName"

/* Specify the type of iterator, when indexes are equal. For Example
*  (1 to 1) will be (1 to 1) or (1 downto 1). The attribute
*  is written only when both indexes are equal and downto.
*/
#define vhdAttIndexDownTo       "IndexDownTo"
#define vhdAttIndexDownToSize   4
#define vhdAttFirstDimension    0x1
#define vhdAttSecondDimension   0x2

/*
*******************************************************************************************
*
* Gate Optimization attributes and defines.
*
*******************************************************************************************
*/

/* Defines used as bit flags for attribute dHfAttGateOptFlags.
*/
#define dHfNewDaiDirPathFlag    0x000001
#define dHfHilRtlFlag           0x000002 // Indicate when HIL functions should be used
                                         // instead of Davinci in FHDB.
                                         // Equivalent FSDB flag: FSDB_HILRTL_FLAG
#define dHfUnused1Flag          0x000004
#define dHfUnused2Flag          0x000008
#define dHfNoDaiDirFlag         0x000010
#define dHfElabIncrMode2Flag    0x000020
#define dHfSigOpInVFSDBFlag     0x000040
#define dHfVpdVecOptFlag        0x000080  // Vector gates optimization are on.
#define dHfNoGTUInArchiveFlag   0x000100

/* Attribute to store the bit flags listed above plus the hsDirType value in the
** upper 8 bits of the 4 byte word. A Size of 4 bytes and the address of an
** integer should be passed as arguments.
*/
#define dHfAttGateOptFlags      "GateOptFlags"

/* Attribute stores the string value of simulator variable psSimBase0.  The size
** given for this attribute is the length of the string including the NULL
** character at the end.
*/
#define dHfAttSimBase0             "SimBase0"
#define dHfAttGateOptFlagsSize     4

/*
*******************************************************************************************
*
* OVA/SVA Assertion based attributes
*
*******************************************************************************************
*/

/* Type "hfAttAssertionVpiFlow" is added to the design handle when the VPI
 * assertion capabilities available.  No value is associated with this attribute.
 */
#define hfAttAssertionVpiFlow           "AssertionVpiFlow"
#define hfAttAssertionVpiFlowSize       0

/* Specify the path the the OVA XML file.  The path can either be absolute or relative to the
** location where the "simv" ran from. The size given for this attribute is the length of the
** string including the NULL character at the end.
*/
#define ovaAttXmlPath               "ovaXmlPath"

/* Specify the path the the OVA report file.  The path can either be absolute or relative to the
** location where the "simv" ran from.  The size given for this attribute is the length of the string
** including the NULL character at the end.
*/
#define ovaAttReportFilePath        "ovaReportPath"

/* The Source Info Attribute is used to store the source information of the assertion.
** It list the files and line numbers that make up the source for this assertion. Since a
** assertion may have an `include statement, this attributes may have one or more entries
** to specify each segment. The format for each segment is:
**
** <Start Line Nbr>\n<End Line Nbr>\n<File Name>[\n...]\0
**
** <Start Line Nbr>  First line of this segment.
** <End Line Nbr>    Last line of this segment.
** <File Name>       The file name as given by Ova.
**
** The last character must be the NULL character to indicate the end of the string.
**
** The size given for this attribute is the length of the string including the NULL character
** at the end.
**
*/
#define ovaAttSourceInfo            "ovaSourceInfo"

#define svaAttSeqInstInfo           "svaAutSeqInstInfo"
#define svaAttSeqOrigStr            "svaAutSeqOrigStr"

/* Assertions can be of many types. Following attribute is used to store the assertion type */
#define ovaAttAssertionType         "ovaAssertionType"

/* The various assertion types are as follows */
#define ovaNormalAssertion          "Normal Assertion"
#define ovaForbidAssertion          "Forbid Assertion"
#define ovaCoverageAssertion        "Coverage Assertion"
#define svaNormalAssertion          "SVA Normal Assertion"
#define svaCoverageAssertion        "SVA Coverage Assertion"
#define svaImmediateAssertion       "SVA Immediate Assertion"
#define svaSequence                 "SVA Sequence"
#define svaImmediateCover           "SVA Immediate Cover"

/* Low Power Specific attribute to check whether the signal has any isolation applied to it or not */
#define dHfAttIsolationSignal "dHfAttIsolationSignal"
#define dHfAttIsolationSignalSize 4
/* Low Power Specific attribute to check whether the signal is an always on signal or not */
#define dHfAttAlwaysOnSignal "dHfAttAlwaysOnSignal"
#define dHfAttAlwaysOnSignalSize 4
/* Low Power Specific attribute to check whether the signal is an SRSN port or not */
#define dHfAttIsSrsn "dHfAttIsSrsn"
#define dHfAttIsSrsnSize 4
/* Low Power Specific attribute to check whether the signal is a DB Logic PIN or not */
#define dHfAttIsDBLogicPin "dHfAttIsDBLogicPin"
#define dHfAttIsDBLogicPinSize 4

/* The ovaVarType attribute is used to provide the type of variable is part of the Ova Record. */
#define ovaVarType                  "ovaVarType"
#define ovaVarTypeSize              4

typedef enum
{
    eHfOvaVarTypeBool       =  0,
    eHfOvaVarTypeFree       =  1,
    eHfOvaVarTypeHDL        =  2
} eHfOvaType;

/* The ovaVarFullName attribute is used to provide the full pathname of a global variable that is part of an
** assertion.
*/
#define ovaVarFullName              "ovaVarFullName"

/* Define for the Ova Summary variable name. */
#define dHfOvaSummaryData           "OvaSummaryData"

/* Structure used to store Ova summary data to provide data of the first failure for each Ova Assertion. */
typedef struct
{
    unsigned int    uTime64;
    unsigned int    uTime32;
    unsigned int    uAssertionName;
    unsigned int    uOffendingString;
}  tOvaSumValChg;

/* Defines to store Ova unit binding information.  Two defines are used to allow better VPD space
** optimization. They MUST be used together.
*/

/* The dHfOvaUnitBindingSourceFile attribute is used to store the file name as a
** string. NOTE:  The byte size of the value stored does not include the
** terminating null character.
*/
#define dHfOvaUnitBindingSourceFile     "ovaUnitBindingSourceFile"

/* Attribute dHfOvaUnitBindingSourceStartLineNbr is used to store the start line
** number where the bind occurs.  NOTE:  The size may be either 1, 2, or 4 to
** indicate the value is a pointer to either an unsigned char, short, or int
** respectively.  The reader is responsible to handle any byte swapping if
** needed.
*/
#define dHfOvaUnitBindingSourceStartLineNbr "ovaUnitBindingSourceStartLineNbr"

/* Attribute dHfOvaUnitBindingSourceEndLineNbr is used to store the end line
** number where the bind occurs.  NOTE:  The size may be either 1, 2, or 4 to
** indicate the value is a pointer to either an unsigned char, short, or int
** respectively.  The reader is responsible to handle any byte swapping if
** needed.
*/
#define dHfOvaUnitBindingSourceEndLineNbr   "ovaUnitBindingSourceEndLineNbr"


/*
*******************************************************************************************
*
* System C based attributes
*
*******************************************************************************************
*/
/* System C Data Type Define.  Used with "hfFileSetDataTypeString()". */
#define hfSyscDataTypeString     "SystemC"

/* Type "hfAttChannel" is added to all variable objects to indicate this
** variable is also a SystemC channel.  Use the "eHfAttChannelType" enumerated
** type when adding attributes of type hfAttChannel. The enumerated type must
** be stored as 4 bytes.
*/
#define hfAttChannel            "Channel"
#define hfAttChannelSize        4

/* Attribute "hfAttrRealtypeString" is used to store the "real" typename of on
** variable/signal/etc as defined in the source code. This type string will be dispalyed
** to the user. The attribute is only needed when a different type is used to store
** the object within the database. Example: sc_fifo<myClass> is stored within VPD as
** a sc_fifo<string> but hfAttrRealtypeString="myClass"
*/
#define hfAttrRealtypeString       "realtype"

/* Attribute "hfAttrAltName" is used to store the alternative name of a SystemC
** object. When a signal/port is defined in SystemC, it -can- get a user defined name
** or a generated name. This name is displayed. However, this name does not reflect
** the C/C++ name of the signal itself. This alternative name is stored here:
**   sc_in<int> inport_a("foo")
** the user normally sees 'foo' as name, or when not given, 'port_0'
** the alternative name will be: 'inport_a'
*/
#define hfAttAltName              "AlternativeName"

/*
 * Channel values start at one (1) to allow zero (0) to indicate an invalid entry.
 * NOTE! NOTE! NOTE!
 * All new entries MUST go at the end of this enum list!
 * Failure to do so will result in all VCD+ files becoming invalid.
 */

typedef enum
{
    eHfAttChannel_invalid               = 0,
    eHfAttChannel_sc_signal             = 1,
    eHfAttChannel_sc_signal_resolved    = 2,
    eHfAttChannel_sc_buffer             = 3,
    eHfAttChannel_sc_clock              = 4,
    eHfAttChannel_rvm_sc_sig            = 5,
    eHfAttChannel_rvm_sc_var            = 6,
    eHfAttChannel_rvm_sc_event          = 7,
    eHfAttChannel_sc_fifo               = 8
}
eHfAttChannelType;

/*
*******************************************************************************************
*
* Vera based attributes
*
*******************************************************************************************
*/

#define hfVeraType                              "VeraType"
#define hfVeraTypeSize                          4

typedef enum
{
    eHfVeraScope            =  0,
    eHfVeraReg              =  1,
    eHfVeraEnum             =  2
}
eHfVeraType;

/*
*******************************************************************************************
*
* Older defines for attributes that have been renamed an a neutral attribute.  They will be
* maintained so older code does not have to be modified just for a name change.
* PLEASE NO LONGER USE IN NEW CODE.
*
*******************************************************************************************
*/
/* Older Verilog defines. */
#define hfVlogType                  dHfAttType
#define eHfVlogType                 eHfAttType
#define hfVlogTypeSize              dHfAttTypeSize
#define hfVlogSize                  dHfAttSize
#define hfVlogSizeSize              dHfAttSizeSize
#define hfVlogPort                  dHfAttPort
#define hfVlogPortSize              dHfAttPortSize
#define eHfVlogPortType             eHfAttPortType
#define hfVlogDefName               dHfAttDefName
#define hfSimulatorCompileLocation  dHfAttSimulatorCompileLocation
#define hfSimulatorCompileVersion   dHfAttSimulatorCompileVersion
#define hfSimulatorLocation         dHfAttSimulatorLocation
#define hfSimulatorName             dHfAttSimulatorName

/* Older Verilog port defines */
#define eHfVlogPortInvalid          eHfAttPortInvalid
#define eHfVlogPortIn               eHfAttPortIn
#define eHfVlogPortOut              eHfAttPortOut
#define eHfVlogPortInOut            eHfAttPortInOut
#define eHfVlogPortMixed            eHfAttPortMixed
#define eHfVlogPortBuffer           eHfAttPortBuffer
#define eHfVlogPortInternal         eHfAttPortInternal

/* Older VHDL defines. */
#define vhdAttDefName               dHfAttDefName
#define vhdAttLeftBound             dHfAttLeftBound
#define vhdAttRightBound            dHfAttRightBound

/* Below defines moves the VHDL "Type" attributes into the unified attribute */
#define eVhdType                    eHfAttType
#define eVhdTypePackage             eHfVhdTypePackage
#define eVhdTypeEntity              eHfVhdTypeEntity
#define eVhdTypeArchitecture        eHfVhdTypeArchitecture
#define eVhdTypeBlock               eHfVhdTypeBlock
#define eVhdTypeProcess             eHfVhdTypeProcess
#define eVhdTypeProcedure           eHfVhdTypeProcedure
#define eVhdTypeFunction            eHfVhdTypeFunction
#define eVhdTypeSignal              eHfVhdTypeSignal
#define eVhdTypeVariable            eHfVhdTypeVariable
#define eVhdTypeConstant            eHfVhdTypeConstant
#define eVhdTypeGeneric             eHfVhdTypeGeneric
#define eVhdTypePort                eHfVhdTypePort

/* I hate inconsistences!  Don't know how these got missed! */
#define hfAttType                   dHfAttType
#define hfAttTypeSize               dHfAttTypeSize
#define hfAttSize                   dHfAttSize
#define hfAttSizeSize               dHfAttSizeSize
#define hfAttPort                   dHfAttPort
#define hfAttPortSize               dHfAttPortSize
#endif
