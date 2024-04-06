/******************************************************************
 *   Copyright (c) 2014 by Synopsys Inc. - All Rights Reserved    *
 *                                                                *
 *   CONFIDENTIAL AND PROPRIETARY INFORMATION OF SYNOPSYS INC.    *
 ******************************************************************/
#ifndef __SYNOPSYS_VCS_CSOLVER_DECLS_HH__
#define __SYNOPSYS_VCS_CSOLVER_DECLS_HH__

#include <cstddef>

///////////////////////////////////////////////////////////////////////////////
//
// General/Utility macros ...
//
///////////////////////////////////////////////////////////////////////////////
#ifdef ENGINEER
#define VCS_CSOLVER_NULLCHECK(x) vcs_csolver_api::vcsAssertWrapper(             \
                                   x,                                       \
                                   "Error: Nullcheck failed!"               \
                               )
#else
#define VCS_CSOLVER_NULLCHECK(x)
#endif

#ifdef ENGINEER
#define VCS_CSOLVER_ASSERT(x,y) vcs_csolver_api::vcsAssertWrapper(x, y)
#else
#define VCS_CSOLVER_ASSERT(x,y)
#endif

#define VCS_CSOLVER_DISALLOW_COPY_AND_ASSIGN(_type_)                         \
    private:                                                               \
    _type_(const _type_& c) {                                              \
        VCS_CSOLVER_ASSERT(false, "Copy Constructor is NYI in this class."); \
    }                                                                      \
    _type_& operator=(const _type_& c) {                                   \
        VCS_CSOLVER_ASSERT(false, "Assignment op is NYI in this class.");    \
        return *this;                                                      \
    }

#define VCS_CSOLVER_DISALLOW_COPY_AND_ASSIGN_WITH_BASE(_type_,_base_)        \
    private:                                                               \
    _type_(const _type_& c) : _base_() {                                   \
        VCS_CSOLVER_ASSERT(false, "Copy Constructor is NYI in this class."); \
    }                                                                      \
    _type_& operator=(const _type_& c) {                                   \
        VCS_CSOLVER_ASSERT(false, "Assignment op is NYI in this class.");    \
        return *this;                                                      \
    }


//
// Only symbols/functions/classes/variables/decalrations that MUST be visible
// in the end-user/customer env during compilation/linking/loading (either
// directly or indirectly due to other exported API(s) being dependent on them)
// ARE ALLOWED to be kept in this namespace. Everything else, should be kept
// in vcs_csolver_impl namespace.
//
// Please note that we hide all global symbols with external linkage (that
// doesn't need to be exported outside libcsolver.so) using the linker
// version script, except for global symbols defined in the vcs_csolver_api
// namespace, which are part of the VCS CSOLVER API, so, must be visible and
// link-able from the customer environment.
//
namespace vcs_csolver_api {

///////////////////////////////////////////////////////////////////////////////
//
// Typedefs...
//
///////////////////////////////////////////////////////////////////////////////
typedef int                                     VarIdType;
typedef int                                     VecIdType;
typedef int                                     EnumIdType;
typedef int                                     CstrIdType;
typedef int                                     PathIdType;
typedef unsigned int                            PrecisionType;
typedef unsigned int                            VectorSizeType;
typedef unsigned long long                      WeightType;


///////////////////////////////////////////////////////////////////////////////
//
// Class forward declarations...
//
///////////////////////////////////////////////////////////////////////////////
class uniq_set;
class RangeData;
class RangeBase;
class OpenRangeList;
class RandVarBase;
class RandVecBase;
class EnumTypeInfo;
class CstrExprTree;
class rand_obj_base;
class ConstraintVar;
class ForeachLoopVar;
class RandObjForCrave;
class ConstraintBlockItem;
class ForeachLoopVarForCrave;
class ConstrainedRandomGenerator;
class ForeachConstraintPreParser;
class SoftConstrainedRandomGenerator;
template<class T> class randv;
template<class T> class RandVar;
template<class T> class rand_var;
template<class T> class RandVBase;
template<class T, class A> class rand_vec;
template<class T, class A> class RandVector;
template<class T> class EnumInfo;
template<class T> class EnumInfoBase; 


///////////////////////////////////////////////////////////////////////////////
//
// Function declarations...
//
///////////////////////////////////////////////////////////////////////////////
bool                            isBigEndianMachine();
void                            exitFromCSOLVER(int status);
void                            vcsAssertWrapper(bool, const char*);
void                            vcsAssertWrapper(const void*, const char*);
bool                            isSignedEnumTypInfo(const EnumTypeInfo*);
void*                           allocStorageFromRace(unsigned int size);
ConstraintBlockItem&            createDistConstraint(
                                    const CstrExprTree&     lhs,
                                    const OpenRangeList*    set
                                );
ConstraintBlockItem&            createInsideConstraint(
                                    const CstrExprTree&     lhs,
                                    const OpenRangeList*    set
                                );
ConstraintBlockItem&            createUniqueConstraint(
                                    const uniq_set*         set
                                );
CstrExprTree&                   createOrderedCstrExprVariable(
                                    ConstraintVar*          refVar,
                                    const char*             varName,
                                    const char*             fileName,
                                    size_t                  lineNum
                                );
const unsigned int*             cstrDataTypeGetValueInUintArray(
                                    const void*             data
                                );
void                            binaryNumStrToUnsignedIntArray(
                                    const char*             val,
                                    unsigned int**          mem
                                );
char*                           unsignedIntArrayToNumStr(
                                    const unsigned int*     mem,
                                    int                     len
                                );
CstrExprTree&                   createCstrExprVariable(
                                    ConstraintVar*          var,
                                    VarIdType               vid = -1
                                );
bool                            mustBeUnsignedEnum(
                                    int                     sizeofEnum,
                                    void*                   enumData
                                );
CstrDataType*                   raceCreateAndSetDataTypeWrapper(
                                    unsigned int            bits,
                                    bool                    isSigned,
                                    unsigned int*           value
                                );
CstrExprTree&                   createCstrExprTreeBinOpNode(
                                    const CstrExprTree&     lhs,
                                    const CstrExprTree&     rhs,
                                    CstrExprTreeBinaryOpType op_type
                                );
CstrExprTree*                   createCstrExprTreeConstantNode(
                                    const char*             const_val,
                                    unsigned                sizeof_const,
                                    bool                    is_signed,
                                    bool                    const_val_in_BASE_10_fmt
                                );
template<class T>
CstrExprTree*                   createCstrExprTreeConstantNode(
                                    const T&                val
                                );
template<class T>
void                            copyLittleToBigEndian(
                                    const unsigned int*     src,
                                    T&                      dst
                                );
template<class T>
void                            copyBigToLittleEndian(
                                    const T&                src,
                                    unsigned int*           dst
                                );

//
// 'disable_soft' constraint API
//
ConstraintBlockItem&            disable_soft(const CstrExprTree& var);



//
// Error reporting routines...
//
void                            vcsCsolverMsgReportNoSource(
                                    const char*             msg
                                );
void                            vcsCsolverMsgReportNoSource1(
                                    const char*             msg,
                                    const char*             arg1
                                );
void                            vcsCsolverMsgReportNoSource2(
                                    const char*             msg,
                                    const char*             arg1,
                                    const char*             arg2
                                );
void                            vcsCsolverMsgReportNoSource3(
                                    const char*             msg,
                                    const char*             arg1,
                                    const char*             arg2,
                                    const char*             arg3
                                );
void                            vcsCsolverMsgReportNoSource4(
                                    const char*             msg,
                                    const char*             arg1,
                                    const char*             arg2,
                                    const char*             arg3,
                                    const char*             arg4
                                );
void                            vcsCsolverMsgReportNoSource5(
                                    const char*             msg,
                                    const char*             arg1,
                                    const char*             arg2,
                                    const char*             arg3,
                                    const char*             arg4,
                                    const char*             arg5
                                );
void                            vcsCsolverMsgReport(
                                    const char*             msg,
                                    const char*             fName,
                                    const int               lnNum,
                                    const char*             region,
                                    const char*             object
                                );
void                            vcsCsolverMsgReport1(
                                    const char*             msg,
                                    const char*             fName,
                                    const int               lnNum,
                                    const char*             region,
                                    const char*             object,
                                    const char*             arg1
                                );
void                            vcsCsolverMsgReport2(
                                    const char*             msg,
                                    const char*             fName,
                                    const int               lnNum,
                                    const char*             region,
                                    const char*             object,
                                    const char*             arg1,
                                    const char*             arg2
                                );
void                            vcsCsolverMsgReport3(
                                    const char*             msg,
                                    const char*             fName,
                                    const int               lnNum,
                                    const char*             region,
                                    const char*             object,
                                    const char*             arg1,
                                    const char*             arg2,
                                    const char*             arg3
                                );
void                            vcsCsolverMsgReport4(
                                    const char*             msg,
                                    const char*             fName,
                                    const int               lnNum,
                                    const char*             region,
                                    const char*             object,
                                    const char*             arg1,
                                    const char*             arg2,
                                    const char*             arg3,
                                    const char*             arg4
                                );
void                            vcsCsolverMsgReport5(
                                    const char*             msg,
                                    const char*             fName,
                                    const int               lnNum,
                                    const char*             region,
                                    const char*             object,
                                    const char*             arg1,
                                    const char*             arg2,
                                    const char*             arg3,
                                    const char*             arg4,
                                    const char*             arg5
                                );


//
// Memory management wrapper routines.
//
// Memory allocated by regular memory allocation routines like 'malloc'/'new'
// may use Synopsys's memory manager if the 'malloc'/'new' call is located in
// the libcsolver.so library. In such cases, we will need to make sure that
// corresponding 'free'/'delete' is also called from the library (which may
// Synopsys memory mgr).
//
void*                           mallocWrapper(size_t size);
void                            freeWrapper(void* ptr);
char*                           strdupWrapper(const char* s1);
void*                           callocWrapper(size_t nelem, size_t elsize);
void*                           reallocWrapper(void* ptr, size_t size);


///////////////////////////////////////////////////////////////////////////////
//
// Class/Struct declarations...
//
///////////////////////////////////////////////////////////////////////////////
//
// Helper class for retreiving enum type info.
//
struct EnumTypeInfoHelperBase {
    const EnumTypeInfo*         getEnumTypeInfo();
};

template<class T>
struct EnumTypeInfoHelper : public EnumTypeInfoHelperBase {

};

} // end - namespace vcs_csolver_api



//
// All link time symbols that don't need to be visible from the customer
// environment, in other words, any symbol that doesn't need to be globally
// exported outside libcsolver.so MUST be kept here.
//
namespace vcs_csolver_impl {

///////////////////////////////////////////////////////////////////////////////
//
// Class forward declarations...
//
///////////////////////////////////////////////////////////////////////////////
class UniqSetImpl;
class RangeBaseImpl;
class RangeDataImpl;
class ConstraintImpl;
class SourceInfoImpl;
class RandObjBaseImpl;
class RandVarBaseImpl;
class OpenRangeListImpl;
class RandVecBaseImpl;
class EnumTypeInfoImpl;
class ConstraintVarImpl;
class VarHandleBaseImpl;
class VectorSizeVarImpl;
class ForeachLoopVarImpl;
class ExprConstraintImpl;
class VectorSelectBaseImpl;
class SoftConstraintParserImpl;
class UniqueConstraintParserImpl;
class ForeachConstraintParserImpl;
class RandVectorInterfaceBaseImpl;
class ForeachConstraintPreParserImpl;
class ConstrainedRandomGeneratorImpl;
class NamedBlockConstraintParserImpl;

class AggrVar;
class ForeachConstraint;
class VectorSelectIndexIterator;


///////////////////////////////////////////////////////////////////////////////
//
// Function declarations...
//
///////////////////////////////////////////////////////////////////////////////

} // end - namespace vcs_csolver_impl

#endif
