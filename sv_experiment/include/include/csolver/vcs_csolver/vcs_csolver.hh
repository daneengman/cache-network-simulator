/******************************************************************
 *   Copyright (c) 2014 by Synopsys Inc. - All Rights Reserved    *
 *                                                                *
 *   CONFIDENTIAL AND PROPRIETARY INFORMATION OF SYNOPSYS INC.    *
 ******************************************************************/
#ifndef __SYNOPSYS_VCS_CSOLVER_HH__
#define __SYNOPSYS_VCS_CSOLVER_HH__

#include <map>
#include <vector>
#include <utility>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "vcs_csolver_constraint.hh"

namespace vcs_csolver_api {

//
// Basic Source Info interface
//
class SourceInfo {
public:
                                SourceInfo(const char*      fileName,
                                           size_t           lineNum);

    virtual                     ~SourceInfo();

    const char*                 getFileName() const;

    size_t                      getLineNumber() const;

    void                        setFileName(const char*);

    void                        setLineNumber(size_t);

private:
    typedef vcs_csolver_impl::SourceInfoImpl Impl_;

    Impl_*                      impl_;
};

//
// Top-most base class for all kind of variables
//
class Variable {
public:
    virtual                     ~Variable();

    //
    // Gets variable name, if available.
    //
    virtual const char*         getName() const = 0;

    //
    // Gets source info, if available.
    //
    virtual const SourceInfo*   getSourceInfo() const = 0;

    //
    // Checks if the Variable CAN participate in any constraint expr.
    //
    virtual bool                isConstraintVar() const;

    //
    // Checks if the Variable is an instance of RandObj.
    //
    virtual bool                isRandObj() const;

    //
    // Checks if the Variable is a Constrained random var.
    //
    virtual bool                isRandVar() const;

    //
    // Checks if the Variable is a 'rand_var' instance.
    //
    virtual bool                isRandV() const;

    //
    // Checks if the Variable is a RandVector instance.
    //
    virtual bool                isRandVector() const;

    //
    // Checks if the Variable is an Enum var.
    //
    virtual bool                isEnumVar() const;

    //
    // Checks if the Variable is a PathSpecVar var.
    //
    virtual bool                isPathSpecVar() const;

    //
    // Checks if the Variable is a Constrained non-random var.
    //
    virtual bool                isStateVar() const;

    //
    // Checks if the Variable is void function var.
    //
    virtual bool                isFunctionVar() const;

    //
    // Checks if the Variable is part/bit-select var.
    //
    virtual bool                isSelect() const;

    virtual void                clearupGenerator(
                                    const vcs_csolver_impl::ConstrainedRandomGeneratorImpl*
                                );

    virtual unsigned int        getNumRanges() const;

    virtual rand_obj_base*      getParent() const;

    virtual bool                isRandModeON(void) const;
 
    virtual const EnumTypeInfo* getEnumTypeInfo() const;

protected:
                                Variable();
};

//
// Every construct that participates in a CSOLVER constraint expr will have a
// path spec id associated with it.
//
class PathSpecVar : public Variable {
public:
    bool                        isPathSpecVar() const;

    PathIdType                  getPathId(
                                    vcs_csolver_impl::ConstrainedRandomGeneratorImpl*
                                ) const;

    virtual RandVecBase&        getVector();

    virtual bool                isStateVar() const;

    virtual bool                isVectorSizeVar() const;

    virtual bool                isVectorSelect() const;

    virtual bool                isForeachLoopVar() const;

protected:
                                PathSpecVar();
};

//
// A Variable that can take part in a CSOLVER constraint expr/compuation.
//
class ConstraintVar : public PathSpecVar {
public:
                                ~ConstraintVar();

    const char*                 getName() const;

    const SourceInfo*           getSourceInfo() const;

    VarIdType                   getId(vcs_csolver_impl::ConstrainedRandomGeneratorImpl*) const;

    virtual bool                isSigned() const;

    virtual bool                isAggrVar() const;

    virtual bool                hasSameType(const ConstraintVar*) const;

    virtual const void*         getValuePtr() const;

    virtual PrecisionType       getPrecision() const;

    bool                        isConstraintVar() const;

    virtual void                setValue(const unsigned int*);

    virtual CstrDataType*       getValueInCstrDataType() const;
 
    virtual void                setValueFromCstrDataType(const CstrDataType*);
   
    virtual bool                addRangeConstraintToGenerator(
                                    vcs_csolver_impl::ConstrainedRandomGeneratorImpl*
                                );

    void                        unconstrainedRandValue(vcs_csolver_impl::RandObjBaseImpl*);  

    virtual const char*         getEnumName() const;

    virtual EnumIdType          getEnumId(
                                    vcs_csolver_impl::ConstrainedRandomGeneratorImpl*
                                ) const;

    virtual unsigned int        getNumEnumElements() const;

    virtual CstrExprTree*       getSelectExpr() const;

    virtual ConstraintVar*      getBase() const;

    virtual void                appendVectorSelectIndex(const CstrExprTree* idx);

    virtual VarHandleBase*      getVarHandle();

    virtual const VarHandleBase* getVarHandle() const;

    virtual bool                isDistCstrExprDirty() const;

    virtual void                setDistCstrExprDirty(bool);

    virtual bool                isResolutionHelperGlobalLoopVar() const;

    const EnumTypeInfo*         getEnumTypeInfo() const;

    bool                        isEnumVar() const;

    virtual void                deleteRangeConstraintFromGen(
                                    vcs_csolver_impl::ConstrainedRandomGeneratorImpl*
                                ); 

protected:
                                ConstraintVar(VarHandleBase*    varHandle,
                                              const char*       varName,
                                              const char*       fileName,
                                              size_t            lineNum);
                                 

                                ConstraintVar(const ConstraintVar& c);

    ConstraintVar&              operator=(const ConstraintVar& c);

    typedef vcs_csolver_impl::ConstraintVarImpl Impl_;

    Impl_*                      impl_;
};

//
// Represents all non-random state variables created using reference()/ref()
// function.
//
class StateVarBase : public ConstraintVar {
public:
    void*                   operator new(size_t sz);

    void                    operator delete(void* ptr);

    bool                    isStateVar() const;

    virtual StateVarBase*   clone() const = 0;

protected:
                            StateVarBase(VarHandleBase*     vh,
                                         const char*        varName,
                                         const char*        fileName,
                                         size_t             lineNum);

                            StateVarBase(const StateVarBase&);
};

template<class T>
class StateVar : public StateVarBase {
public:
                    StateVar(const T&               value,
                             const EnumTypeInfo*    enumTypInfo,
                             const char*            varName,
                             const char*            fileName,
                             size_t                 lineNum);

                    StateVar(const StateVar& cpy);

    const T&        getValue() const { return var_; }

    bool            hasSameType(const ConstraintVar*) const;

    const void*     getValuePtr() const { return &var_; }

    StateVarBase*   clone() const { return new StateVar<T>(*this); }

    //
    // This function would allocate storage for raceDataType, so users would
    // need to deep delete the returned raceDataType (after use) using
    // raceFreeDataType.
    //
    CstrDataType*   getValueInCstrDataType() const;

private:
    const T&        var_;
};

template<class T>
StateVar<T>::StateVar(const T&              value,
                      const EnumTypeInfo*   enumTypInfo,
                      const char*           varName,
                      const char*           fileName,
                      size_t                lineNum)
        : StateVarBase(new VarHandle<T>(const_cast<T*>(&value),
                                        enumTypInfo),
                       varName,
                       fileName,
                       lineNum),
          var_(value) {
}

template<class T>
StateVar<T>::StateVar(const StateVar& cpy)
        : StateVarBase(cpy),
          var_(cpy.var_) {
}

template<class T>
CstrDataType*
StateVar<T>::getValueInCstrDataType() const {
    return vcs_csolver_api::getValueInCstrDataType(var_, getEnumTypeInfo());
}

template<class T>
bool
StateVar<T>::hasSameType(const ConstraintVar* var) const {
    return this->getVarHandle()->getTypeId() == var->getVarHandle()->getTypeId();
}

//
// Non-templatized base class of random constraint vars
//
class RandVarBase : public ConstraintVar {
public:
                                ~RandVarBase();

    bool                        isRandVar() const;

    unsigned int                getNumEnumElements() const;

    void                        clearupGenerator(const vcs_csolver_impl::ConstrainedRandomGeneratorImpl*);

    const char*                 getEnumName() const;

    void                        addRange(RangeBase* range);

    bool                        addRangeConstraintToGenerator(
                                    vcs_csolver_impl::ConstrainedRandomGeneratorImpl*
                                );

    virtual bool                next();

    virtual bool                randomize();

    void                        resetDistribution();

    virtual const CstrExprTree& operator()();

    const CstrExprTree&         operator()(unsigned int left,
                                           unsigned int right);

    const CstrExprTree&         operator[](unsigned int i);

    const CstrExprTree&         operator[](const CstrExprTree& index);

    const CstrExprTree&         operator[](const ConstraintVar&);

    void                        deleteRangeConstraintFromGen(
                                    vcs_csolver_impl::ConstrainedRandomGeneratorImpl*
                                );

    virtual bool                isDistCstrExprDirty() const;

    virtual void                setDistCstrExprDirty(bool);

    rand_obj_base*              getParent() const;

    unsigned int                getNumRanges() const;

    void                        disable_randomization();

    void                        enable_randomization();

    void                        setRandMode(bool isON);

    bool                        isRandModeON(void) const;

    void                        set_parent(rand_obj_base* parent);

protected:
                                RandVarBase(VarHandleBase*      vh,
                                            rand_obj_base*      parent,
                                            const char*         varName = NULL,
                                            const char*         fileName = NULL,
                                            size_t              lineNum = 0);

                                RandVarBase(const RandVarBase&);

    RandVarBase&                operator=(const RandVarBase&);

private:
    typedef vcs_csolver_impl::RandVarBaseImpl Impl_;

    Impl_*                      impl_;

public:
    Impl_&                      getImpl();
};

//
// The key API(s) that the RandVec needs to support.
//
class RandVectorInterfaceBase {
public:
    explicit                        RandVectorInterfaceBase(RandVecBase& vec);

    virtual                         ~RandVectorInterfaceBase();

    virtual const CstrExprTree&     size() const;

    virtual const CstrExprTree&     SUM() const;

    virtual const CstrExprTree&     PRODUCT() const;

    virtual const CstrExprTree&     AND() const;

    virtual const CstrExprTree&     OR() const;

    virtual const CstrExprTree&     XOR() const;

    virtual const CstrExprTree&     operator[](const CstrExprTree& idx) = 0;

    virtual const CstrExprTree&     operator[](VectorSizeType idx) = 0;

    virtual const CstrExprTree&     operator()(VectorSizeType sliceMinIdx,
                                               VectorSizeType sliceMaxIdx) = 0;

    void                            setVector(RandVecBase& vec);

    RandVecBase*                    getVector();

    void                            deleteSizeVar();

private:
    typedef vcs_csolver_impl::RandVectorInterfaceBaseImpl Impl_;

    Impl_*                          impl_;

public:
    Impl_&                          getImpl();
};

//
// Non-template base class of random vector implementation (RandVector)
//
class RandVecBase : public PathSpecVar {
public:
                                ~RandVecBase();

    bool                        isRandVector() const;

    const char*                 getName() const;

    const SourceInfo*           getSourceInfo() const;

    virtual VecIdType           getId(vcs_csolver_impl::ConstrainedRandomGeneratorImpl*) const;

    const EnumTypeInfo*         getEnumTypeInfo() const;

    virtual unsigned int        getNDimension() const = 0;

    virtual const char*         getEnumName() const;

    virtual void                reSize(VectorSizeType sz) = 0;

    virtual EnumIdType          getEnumId(
                                    vcs_csolver_impl::ConstrainedRandomGeneratorImpl*
                                ) const;

    virtual VectorSizeType      getSize() const = 0;

    virtual bool                isEnumVector() const;

    virtual PrecisionType       getPrecision() const = 0;

    virtual bool                isSigned() const = 0;

    virtual RandVectorInterfaceBase& operator()() = 0;

    virtual void                resizeWrapper(VectorSizeType sz);

    virtual void                resizeWrapper(const CstrDataType* sz);

    virtual bool                next();

    virtual bool                randomize();

    void                        setRandMode(bool on);

    bool                        isRandModeON() const;

    virtual rand_obj_base*      getParent() const;

    virtual void                setParent(rand_obj_base*);

    virtual void                setValueFromCstrDataType(VectorSizeType      idx,
                                                         const CstrDataType* val) = 0;

    virtual void                setValue(VectorSizeType index,
                                         unsigned int*  value,
                                         const EnumTypeInfo* enumTypeInfo) = 0;

    virtual CstrDataType*       getValueInCstrDataType(VectorSizeType idx) = 0;

    bool                        solveUnconstrainedVector(int*   rngState,
                                                         bool   craveNextFlow);

    void                        enable_randomization();

    void                        disable_randomization();

    void                        set_parent(rand_obj_base* parent);

protected:
                                RandVecBase(rand_obj_base*  parent,
                                            const char*     vecName,
                                            const char*     fileName,
                                            size_t          lineNum);

                                RandVecBase(const RandVecBase& c);

    RandVecBase&                operator=(const RandVecBase& c);

private:
    typedef vcs_csolver_impl::RandVecBaseImpl Impl_;

    Impl_*                      impl_;
};


//
// Represents the size() variable of a random vector.
//
class VectorSizeVar : public RandVarBase {
public:
    explicit                    VectorSizeVar(RandVecBase& vec);

                                ~VectorSizeVar();

    bool                        isVectorSizeVar() const;

    RandVecBase&                getVector();

    void                        setValueFromCstrDataType(const CstrDataType* size);

    bool                        isRandModeON() const;

private:
    typedef vcs_csolver_impl::VectorSizeVarImpl Impl_;

                                VectorSizeVar(const VectorSizeVar&);

    VectorSizeVar&              operator=(const VectorSizeVar&);

    Impl_*                      impl_;
};


//
// Helper templates/functions for VectorSelect implementation.
//
template<class T,class A>
struct VectorTypInfo {
    typedef T PrimaryValueTyp;
};

template<class T,class A>
struct VectorTypInfo<rand_vec<T,A>, A> {
    typedef typename VectorTypInfo<T,A>::PrimaryValueTyp  PrimaryValueTyp;
};

//
// Vector dimension computation
//
template<class T, class A>
struct GetVectorDimension {
    static unsigned const value = 1;
};

template<class T, class A>
struct GetVectorDimension<rand_vec<T,A>, A> {
    static unsigned const value = GetVectorDimension<T,A>::value + 1;
};


//
// Represents the select operation of a random vector element.
//
class VectorSelectBase : public RandVarBase {
public:
                                ~VectorSelectBase();

    bool                        isVectorSelect() const;

    RandVecBase&                getVector();

    const CstrExprTree*         getIndexExpr(unsigned int nth_dim) const;

    VectorSizeType              getIndexValue(unsigned int nth_dim) const;

    void                        setIndexValue(unsigned int      nth_dim,
                                              VectorSizeType    val);

    unsigned int                getNumIndexes() const;

    void                        appendVectorSelectIndex(const CstrExprTree* idx);

    bool                        isRandModeON() const;

    bool                        isEnumVar() const;

    bool                        isVectorSlice() const;

    VectorSizeType              getSliceSize() const;

    const EnumTypeInfo*         getEnumTypeInfo() const;

    void*                       operator new(size_t sz);

    void                        operator delete(void* ptr);

    vcs_csolver_impl::VectorSelectBaseImpl& getImpl();

protected:
                                VectorSelectBase(RandVecBase&           vec,
                                                 const CstrExprTree*    idx,
                                                 VarHandleBase*         varHandle);

                                VectorSelectBase(RandVecBase&           vec,
                                                 VectorSizeType         idx,
                                                 VarHandleBase*         varHandle,
                                                 VectorSizeType         sliceSize);

private:
    typedef vcs_csolver_impl::VectorSelectBaseImpl Impl_;

    Impl_*                      impl_;
};

template<class T,class A>
class VectorSelect : public VectorSelectBase {
public:
                                VectorSelect(RandVecBase&        vec,
                                             const CstrExprTree* idx,
                                             const EnumTypeInfo* enumTypInfo);

                                VectorSelect(RandVecBase&        vec,
                                             VectorSizeType      idx,
                                             const EnumTypeInfo* enumTypInfo,
                                             VectorSizeType      sliceSize = 0);

    VCS_CSOLVER_DISALLOW_COPY_AND_ASSIGN(VectorSelect);
};

template<class T, class A>
VectorSelect<T,A>::VectorSelect(RandVecBase&         vec,
                                const CstrExprTree*  idx,
                                const EnumTypeInfo*  enumTypInfo)
    : VectorSelectBase(vec,
                       idx,
                       new VarHandle<T>(0, enumTypInfo)) {

}

template<class T, class A>
VectorSelect<T,A>::VectorSelect(RandVecBase&          vec,
                                VectorSizeType        idx,
                                const EnumTypeInfo*   enumTypInfo,
                                VectorSizeType        sliceSize)
    : VectorSelectBase(vec,
                       idx,
                       new VarHandle<T>(
                           &((*(static_cast<RandVector<T,A>* >(&vec)))[idx]),
                           enumTypInfo
                       ),
                       sliceSize) {

}


//
// Specializing for bool, since taking address of bool will not be possible.
//
template<class A>
class VectorSelect<bool,A> : public VectorSelectBase {
public:
                                VectorSelect(RandVecBase&        vec,
                                             const CstrExprTree* idx,
                                             const EnumTypeInfo* enumTypInfo);

                                VectorSelect(RandVecBase&        vec,
                                             VectorSizeType      idx,
                                             const EnumTypeInfo* enumTypInfo,
                                             VectorSizeType      sliceSize = 0);

    VCS_CSOLVER_DISALLOW_COPY_AND_ASSIGN(VectorSelect);
};

template<class A>
VectorSelect<bool,A>::VectorSelect(RandVecBase&         vec,
                                   const CstrExprTree*  idx,
                                   const EnumTypeInfo*  enumTypInfo)
    : VectorSelectBase(vec,
                       idx,
                       new VarHandle<bool>(0, enumTypInfo)) {

}

template<class A>
VectorSelect<bool,A>::VectorSelect(RandVecBase&          vec,
                                   VectorSizeType        idx,
                                   const EnumTypeInfo*   enumTypInfo,
                                   VectorSizeType        sliceSize)
    : VectorSelectBase(vec,
                       idx,
                       new VarHandle<bool>(
                           NULL,
                           enumTypInfo
                       ),
                       sliceSize) {

}

//
// Represents loop vars used in foreach constraints.
//
class ForeachLoopVar : public ConstraintVar {
public:
                                    ForeachLoopVar(const char*  varName  = NULL,
                                                   const char*  fileName = NULL,
                                                   size_t       lineNum  = 0);

                                    ForeachLoopVar(const ForeachLoopVar&);

                                    ~ForeachLoopVar();

    ForeachLoopVar&                 operator=(const ForeachLoopVar&);

    bool                            isForeachLoopVar() const;

    const CstrExprTree&             operator()() const;

    vcs_csolver_impl::ForeachLoopVarImpl& getImpl();

private:
    friend class                    vcs_csolver_impl::ForeachConstraint;

    typedef vcs_csolver_impl::ForeachLoopVarImpl Impl_;

                                    ForeachLoopVar(bool         resolutionHelper,
                                                   const char*  varName = NULL,
                                                   const char*  fileName = NULL,
                                                   size_t       lineNum = 0);

    Impl_*                          impl_;
};

//
// Represents loop vars used in foreach constraints in VCS CRAVE.
//
class ForeachLoopVarForCrave : public ForeachLoopVar {
public:
                                    ForeachLoopVarForCrave(const char*  varName  = NULL,
                                                           const char*  fileName = NULL,
                                                           size_t       lineNum  = 0);

                                    ForeachLoopVarForCrave(const ForeachLoopVarForCrave&);

                                    //
                                    // This is CRAVE specific, we do required foreach loop
                                    // variables to use () suffix while used in expr context.
                                    //
                                    operator CstrExprTree&();
};

//
// Pre-defined CRAVE style loop vars...
//
extern ForeachLoopVarForCrave _i;
extern ForeachLoopVarForCrave _j;
extern ForeachLoopVarForCrave _k;

//
// Pre-defined CSOLVER style loop vars...
//
extern ForeachLoopVar i_;
extern ForeachLoopVar j_;
extern ForeachLoopVar k_;

//
// 'foreach' constraint parser...
//
class ForeachConstraintParser {
public:
                                        ~ForeachConstraintParser();

    ConstraintBlockItem&                operator()(ConstraintBlockItem& cstr);

    ConstraintBlockItem&                operator()(bool);

    ConstraintBlockItem&                operator()(ConstraintBlockItem&,
                                                   ConstraintBlockItem&,
                                                   ...);

    RandVecBase&                        getVector();

private:
    friend class                        ForeachConstraintPreParser;

    typedef vcs_csolver_impl::ForeachConstraintParserImpl Impl_;

                                        ForeachConstraintParser(RandVecBase&            vec,
                                                                const ForeachLoopVar&   loopVar1);

    Impl_*                              impl_;
};

class ForeachConstraintPreParser {
public:
                                        ForeachConstraintPreParser();

    ForeachConstraintParser             operator()(const RandVecBase&     vec,
                                                   const ForeachLoopVar&  loopVar);
};

extern ForeachConstraintPreParser& foreach;


//
// 'soft' constraint parser
//
class SoftConstraintParser {
public:
                                    SoftConstraintParser();

    ExprConstraint&                 operator()(const CstrExprTree& cstr);

    ExprConstraint&                 operator()(bool);

    SoftConstrainedRandomGenerator  operator() (ConstrainedRandomGenerator& gen) const;
};

extern SoftConstraintParser& soft;

//
// Parse helper for named block constraints.
//
class NamedBlockConstraintParser {
public:
                                ~NamedBlockConstraintParser();

    void                        operator()(ConstraintBlockItem&);

    void                        operator()(bool);

private:
    friend class                ConstrainedRandomGenerator;

                                NamedBlockConstraintParser(ConstrainedRandomGenerator&  gen,
                                                           const char*                  cb_name);

    typedef vcs_csolver_impl::NamedBlockConstraintParserImpl Impl_;

    Impl_*                      impl_;
};


//
// VCS CSOLVER Constrained Random Generator...
//
class ConstrainedRandomGenerator {
public:
                                    ConstrainedRandomGenerator();

    explicit                        ConstrainedRandomGenerator(ConstraintBlockItem& cstr);

                                    ConstrainedRandomGenerator(const char*           name,
                                                               ConstraintBlockItem&  cstr);

    explicit                        ConstrainedRandomGenerator(bool);

                                    ConstrainedRandomGenerator(const char*           name,
                                                               bool);

                                    ~ConstrainedRandomGenerator();

    ConstrainedRandomGenerator&     constraint(ConstraintBlockItem& cstr);

    ConstrainedRandomGenerator&     constraint(ConstraintBlockItem&,
                                               ConstraintBlockItem&,
                                               ...);

    ConstrainedRandomGenerator&     operator()();

    ConstrainedRandomGenerator&     operator()(ConstraintBlockItem& cstr);

    ConstrainedRandomGenerator&     operator()(ConstraintBlockItem&,
                                               ConstraintBlockItem&,
                                               ...);

    ConstrainedRandomGenerator&     operator()(const char*          name,
                                               ConstraintBlockItem& cstr);

    NamedBlockConstraintParser      operator()(const char*          name);

    ConstrainedRandomGenerator&     soft(const CstrExprTree&        expr_cstr);

    ConstrainedRandomGenerator&     soft(const char*                cstr_name,
                                         const CstrExprTree&        expr_cstr);

    ConstrainedRandomGenerator&     foreach(const RandVecBase&     vec,
                                            const ForeachLoopVar&  i,
                                            const CstrExprTree&    cstr);

    ConstrainedRandomGenerator&     foreach(const char*            name,
                                            const RandVecBase&     vec,
                                            const ForeachLoopVar&  i,
                                            const CstrExprTree&    cstr);

    ConstrainedRandomGenerator&     soft_foreach(const RandVecBase&    vec,
                                                 const ForeachLoopVar& i,
                                                 const CstrExprTree&   cstr);

    ConstrainedRandomGenerator&     soft_foreach(const char*           name,
                                                 const RandVecBase&    vec,
                                                 const ForeachLoopVar& i,
                                                 const CstrExprTree&   cstr);

    ConstrainedRandomGenerator&     operator()(bool);

    ConstrainedRandomGenerator&     operator()(const char*         name,
                                               bool);

    ConstrainedRandomGenerator&     soft(bool);

    ConstrainedRandomGenerator&     soft(const char*               cstr_name,
                                         bool);

    ConstrainedRandomGenerator&     foreach(const RandVecBase&     vec,
                                            const ForeachLoopVar&  i,
                                            bool);

    ConstrainedRandomGenerator&     foreach(const char*            name,
                                            const RandVecBase&     vec,
                                            const ForeachLoopVar&  i,
                                            bool);

    ConstrainedRandomGenerator&     soft_foreach(const RandVecBase&    vec,
                                                 const ForeachLoopVar& i,
                                                 bool);

    ConstrainedRandomGenerator&     soft_foreach(const char*           name,
                                                 const RandVecBase&    vec,
                                                 const ForeachLoopVar& i,
                                                 bool);

    ConstrainedRandomGenerator&     unique(RandVecBase& vec);

    ConstrainedRandomGenerator&     non_unique(RandVecBase& vec);

    bool                            next();

    bool                            randomize();

    bool                            enable_constraint(const char* constraint_name);

    bool                            disable_constraint(const char* constraint_name);

    SoftConstrainedRandomGenerator  operator()(SoftConstraintParser const &);


    // Implementation Detail: STRICTLY FOR INTERNAL USE ONLY
    // 
    // Users of this library should never use/call this function.
    vcs_csolver_impl::ConstrainedRandomGeneratorImpl& getImpl();

private:
    friend class                    rand_obj_base;

    typedef vcs_csolver_impl::ConstrainedRandomGeneratorImpl  Impl_; 

    explicit                        ConstrainedRandomGenerator(rand_obj_base* parent);

                                    ConstrainedRandomGenerator(
                                        const ConstrainedRandomGenerator&
                                    );

    ConstrainedRandomGenerator&     operator=(const ConstrainedRandomGenerator&);

    Impl_*                          impl_;
};

struct SoftConstrainedRandomGenerator {
    explicit                            SoftConstrainedRandomGenerator(
                                            ConstrainedRandomGenerator&
                                        );

    SoftConstrainedRandomGenerator&     operator()(const CstrExprTree& e);

    //
    // Keeping it public for BC reasons.
    //
    ConstrainedRandomGenerator&         gen;
};


//
// Keeps track of the enum type info
//
class EnumValueIterator {
public:
                                    EnumValueIterator();

    virtual                         ~EnumValueIterator();

    virtual const char*             getCurrentEnumValueName() const = 0;

    void*                           operator new(size_t sz);

    void                            operator delete(void* ptr);

    //
    // Note: In the following 2 routines, newly allocated memory is returned.
    //       Users of these routines would be responsible for release these
    //       allocated memories. Please check implementation of the allocation
    //       routines below and choose the right free routines when
    //       de-allocating them.
    //
    virtual CstrExprTree*           getCurrentEnumValInCstrExprTree() const = 0;
    virtual CstrDataType*           getCurrentEnumValInCstrDataType() const = 0;
    virtual CstrExprTree*           getCurrentEnumValInCstrExprTreeUsingPostfixIncr() = 0;
    virtual CstrDataType*           getCurrentEnumValInCstrDataTypeUsingPostfixIncr() = 0;

private:
    VCS_CSOLVER_DISALLOW_COPY_AND_ASSIGN(EnumValueIterator);
};

template<class T>
class EnumValueIteratorImpl : public EnumValueIterator {
public:
    explicit                            EnumValueIteratorImpl(const EnumInfoBase<T>&);

    const char*                         getCurrentEnumValueName() const;

    const T*                            operator()() const;

    const T*                            operator++(int);

    CstrDataType*                       getCurrentEnumValInCstrDataType() const;

    CstrExprTree*                       getCurrentEnumValInCstrExprTree() const;

    CstrExprTree*                       getCurrentEnumValInCstrExprTreeUsingPostfixIncr();

    CstrDataType*                       getCurrentEnumValInCstrDataTypeUsingPostfixIncr();
private:
    const EnumInfoBase<T>&                            enum_info_;
    typename std::map<T,std::string>::const_iterator  it_;
};

template<class T>
EnumValueIteratorImpl<T>::EnumValueIteratorImpl(const EnumInfoBase<T>& ei)
    : EnumValueIterator(),
      enum_info_(ei),
      it_(ei.enumerators_.begin()) {
}

template<class T>
const char*
EnumValueIteratorImpl<T>::getCurrentEnumValueName() const {
    VCS_CSOLVER_ASSERT(this->operator()(), "");
    return it_->second.c_str();
}

template<class T>
const T*
EnumValueIteratorImpl<T>::operator()() const {
    if (it_ == enum_info_.enumerators_.end()) {
        return NULL;
    }
    return &it_->first;
}

template<class T>
const T*
EnumValueIteratorImpl<T>::operator++(int) {
    if (it_ == enum_info_.enumerators_.end()) {
        return NULL;
    }

    const T* tmp = &it_->first;
    ++it_;
    return tmp;
}

template<class T>
CstrDataType*
EnumValueIteratorImpl<T>::getCurrentEnumValInCstrDataType() const {
    const T* curEnumVal = operator()();
    if (curEnumVal) {
        return vcs_csolver_api::getValueInCstrDataType(*curEnumVal, &enum_info_);
    }
    return NULL;
}

template<class T>
CstrExprTree*
EnumValueIteratorImpl<T>::getCurrentEnumValInCstrExprTree() const {
    const T* curEnumVal = operator()();
    if (curEnumVal) {
        return createCstrExprTreeConstantNode(*curEnumVal);
    }
    return NULL;
}

template<class T>
CstrExprTree*
EnumValueIteratorImpl<T>::getCurrentEnumValInCstrExprTreeUsingPostfixIncr() {
    const T* curEnumVal = (*this)++;
    if (curEnumVal) {
        return createCstrExprTreeConstantNode(*curEnumVal);
    }
    return NULL;
}

template<class T>
CstrDataType*
EnumValueIteratorImpl<T>::getCurrentEnumValInCstrDataTypeUsingPostfixIncr() {
    const T* curEnumVal = (*this)++;
    if (curEnumVal) {
        return vcs_csolver_api::getValueInCstrDataType(*curEnumVal, &enum_info_);
    }
    return NULL;
}

class EnumTypeInfo {
public:
    virtual                     ~EnumTypeInfo();

    virtual unsigned int        getNumEnumElements() const = 0;

    virtual bool                hasContagiousEnumValues(CstrExprTree** minValue,
                                                        CstrExprTree** maxValue) const = 0;

    virtual EnumValueIterator*  createEnumValueIterator() const = 0;

    virtual void                deleteEnumValueIterator(EnumValueIterator*) const = 0;

    const char*                 getEnumName() const;

    EnumIdType                  getEnumId(const vcs_csolver_impl::ConstrainedRandomGeneratorImpl*) const;

    bool                        isSigned() const;

    void                        setUnsigned();

protected:
    explicit                    EnumTypeInfo(const char* enum_name);

private:
    typedef vcs_csolver_impl::EnumTypeInfoImpl Impl_;

    Impl_*                      impl_;
};

template<class T>
class EnumInfoBase : public EnumTypeInfo {
public:
    const char*                 getEnumeratorNameByValue(T val) const;

    T                           getEnumValue(unsigned int index) const;

    unsigned int                getNumEnumElements() const;

    EnumValueIterator*          createEnumValueIterator() const;

    void                        deleteEnumValueIterator(EnumValueIterator*) const;

    bool                        hasContagiousEnumValues(CstrExprTree** minValue,
                                                        CstrExprTree** maxValue) const;

protected:
    explicit                    EnumInfoBase(const char* enum_name);

    void                        addEnumMember(T             member_value,
                                              const char*   member_name);

    void                        initialize(unsigned int     num_enumerators,
                                           const char*      enumerators_str,
                                           const T*         enumerators_arr);
private:
    friend class                EnumValueIteratorImpl<T>;

    //
    // We need to ensure that this map is an ordered map, since for implementation
    // reasons, we need to retain the order of enumerator declarations.
    //
    std::map<T,std::string>     enumerators_;
};

template<class T>
EnumInfoBase<T>::EnumInfoBase(const char* enum_name) 
    : EnumTypeInfo(enum_name)
{
    VCS_CSOLVER_NULLCHECK(enum_name);
}

template<class T>
const char*
EnumInfoBase<T>::getEnumeratorNameByValue(T val) const {
    VCS_CSOLVER_ASSERT(enumerators_.find(val) != enumerators_.end(), "");
    return enumerators_[val].c_str();
}

template<class T>
T
EnumInfoBase<T>::getEnumValue(unsigned int index) const {
    typename std::map<T,std::string>::const_iterator it =
    enumerators_.begin();
    std::advance(it, index);
    return it->first;
}

template<class T>
unsigned int
EnumInfoBase<T>::getNumEnumElements() const
{
    return enumerators_.size();
}

template<class T>
EnumValueIterator*
EnumInfoBase<T>::createEnumValueIterator() const {
    return new EnumValueIteratorImpl<T>(*this);
}

template<class T>
void
EnumInfoBase<T>::deleteEnumValueIterator(EnumValueIterator* ptr) const {
    VCS_CSOLVER_NULLCHECK(ptr);
    delete ptr;
}

template<class T>
bool
EnumInfoBase<T>::hasContagiousEnumValues(CstrExprTree** minValue,
                                         CstrExprTree** maxValue) const {
    VCS_CSOLVER_NULLCHECK(minValue);
    VCS_CSOLVER_NULLCHECK(maxValue);

    T maxVal;
    T minVal;
    int enumeratorsCount = 0;
    typename std::map<T,std::string>::const_iterator it;

    *minValue = NULL;
    *maxValue = NULL;
    for (it = enumerators_.begin(); it != enumerators_.end(); ++it) {
        const VarHandle<T> var_handle(const_cast<T*>(&it->first), this);
        VCS_CSOLVER_ASSERT(var_handle.isBuiltInIntegralOrEnumType(), 
                         "Should be built-in integral type");
        if (enumeratorsCount == 0) {
            maxVal = it->first;
            minVal = maxVal;
        }
        else if (it->first > maxVal) {
            maxVal = it->first;
        }
        else if (minVal > it->first) {
            minVal = it->first;
        }
        enumeratorsCount++;
    }

    if (maxVal - minVal + 1 == enumeratorsCount) {
        *minValue = createCstrExprTreeConstantNode(minVal);
        *maxValue = createCstrExprTreeConstantNode(maxVal);
        return true;
    }
    return false;
}

template<class T>
void
EnumInfoBase<T>::addEnumMember(T                member_value,
                               const char*      member_name)
{
    VCS_CSOLVER_NULLCHECK(member_name);

    if (enumerators_.find(member_value) != enumerators_.end()) {
        vcsCsolverMsgReportNoSource1("CPPSOLVER-UEIC", member_name);
        return;
    }
    enumerators_[member_value] = std::string(member_name);

    if (member_value >= 0 && mustBeUnsignedEnum(sizeof(member_value),
                                                &member_value)) {
        this->setUnsigned();
    }
}

template<class T>
void
EnumInfoBase<T>::initialize(unsigned int   num_enumerators,
                            const char*    enumerators_str,
                            const T*       enumerators_arr)
{
    VCS_CSOLVER_NULLCHECK(enumerators_str);
    VCS_CSOLVER_NULLCHECK(enumerators_arr);
    if (num_enumerators == 0) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-ICS");
        return;
    }

    char* enum_str = strdupWrapper(enumerators_str);
    char* org_enum_str = enum_str;
    for (unsigned int i = 0; i < num_enumerators; ++i) {
        T val = enumerators_arr[i]; 
        const char* delimiters = " \t,";
        if (i == 0) {
            enum_str = std::strtok(enum_str, delimiters);
        }
        else {
            enum_str = std::strtok(NULL, delimiters);;
        }
        VCS_CSOLVER_NULLCHECK(enum_str);

        if (enumerators_.find(val) != enumerators_.end()) {
            vcsCsolverMsgReportNoSource1("CPPSOLVER-UEIC", enum_str);
            return;
        }
        enumerators_[val] = std::string(enum_str);

        if (val >= 0 && mustBeUnsignedEnum(sizeof(val), &val)) {
            this->setUnsigned();
        }
    }
    freeWrapper(org_enum_str);
}

template<class T>
class EnumInfo : public EnumInfoBase<T> {
public:
    EnumInfo();
};

template<class T>
EnumInfo<T>::EnumInfo() : EnumInfoBase<T>(0) {
    vcsCsolverMsgReportNoSource("CPPSOLVER-EINS");
}

// Mandatory base class of a class object that needs to be randomized.
class rand_obj_base : public Variable {
public:
                                    rand_obj_base(
                                        rand_obj_base*  parent,
                                        const char*     objName     = NULL,
                                        const char*     fileName    = NULL,
                                        size_t          lineNum     = 0
                                    );

                                    ~rand_obj_base();

    virtual const char*             getName() const;

    void                            setName(const char*);

    virtual const SourceInfo*       getSourceInfo() const;

    void                            setSourceInfo(const char* fName,
                                                  size_t      lnNum);

    virtual bool                    randomize();

    virtual void                    pre_randomize();

    virtual void                    post_randomize();

    void                            set_random_seed(unsigned int s);

    bool                            enable_constraint(const char* name);

    bool                            disable_constraint(const char* name);

    bool                            isRandObj() const;

    void                            disable_randomization();
  
    void                            enable_randomization();

    void                            setRandMode(bool isOn);

    bool                            isRandModeON(void) const;

    // Implementation Detail: STRICTLY FOR INTERNAL USE ONLY
    // 
    // Users of this library should never use/call this function directly.
    vcs_csolver_impl::RandObjBaseImpl& getImpl();

    virtual const char*             getRandObjBaseClassName() const;

    ConstrainedRandomGenerator      constraint;

protected:
                                    rand_obj_base(
                                        bool            randModeON,
                                        rand_obj_base*  parent,
                                        const char*     objName     = NULL,
                                        const char*     fileName    = NULL,
                                        size_t          lineNum     = 0
                                    );
private:
    //
    // Copy operations are not yet supported, will be supported soon.
    //
                                    rand_obj_base(const rand_obj_base& o);

    rand_obj_base&                  operator=(const rand_obj_base& o);


    typedef vcs_csolver_impl::RandObjBaseImpl Impl_;

    Impl_*                          impl_;
};

//
// CRAVE version of rand_obj_base
//
class RandObjForCrave : public rand_obj_base {
public:
                                    RandObjForCrave(RandObjForCrave* parent = NULL,
                                                    const char* objName = NULL,
                                                    const char* fileName= NULL,
                                                    size_t      lineNum = 0);

                                    RandObjForCrave(const RandObjForCrave& o);

    virtual bool                    next();

    const char*                     getRandObjBaseClassName() const;
};

//
// Weight distribution type/constants for Ranges.
//
typedef enum {
    RangeWtDistNotApplicableC,
    WholeRangeWtC,
    EachItemWtC
} RangeWeightDistType;

class RangeBase {
public:
    virtual                     ~RangeBase();

    virtual CstrExprTree*       getLeftInCstrExprTree() const;

    virtual CstrExprTree*       getRightInCstrExprTree() const;

    virtual CstrExprTree*       getWeightInCstrExprTree() const;

    virtual bool                isNonRangeItem() const;

    virtual bool                isWeightedRange() const;

    virtual RangeWeightDistType getRangeDistTyp() const;

    virtual RangeBase*          clone() const = 0;

    void*                       operator new(size_t sz);

    void                        operator delete(void* ptr);

protected:
                                RangeBase(
                                    const CstrExprTree*     rangeMin,
                                    const CstrExprTree*     rangeMax,
                                    const CstrExprTree*     wt, 
                                    RangeWeightDistType     dt
                                );

                                RangeBase(const RangeBase&);

    RangeBase&                  operator=(const RangeBase&);

private:
    typedef vcs_csolver_impl::RangeBaseImpl Impl_;

    Impl_*                      impl_;

public:
    Impl_*                      getImpl();

    const Impl_*                getImpl() const;
};

template<class T>
class Range : public RangeBase {
public:
                                Range(
                                    const T&                        l,
                                    const T&                        r,
                                    const WeightType&               w = 0,
                                    const RangeWeightDistType       dt
                                            = RangeWtDistNotApplicableC
                                );
                            
                                Range(
                                    const CstrExprTree&             l,
                                    const T&                        r,
                                    const WeightType&               w = 0,
                                    const RangeWeightDistType       dt
                                            = RangeWtDistNotApplicableC
                                );

                                Range(
                                    const T&                        l,
                                    const CstrExprTree&             r,
                                    const WeightType&               w = 0,
                                    const RangeWeightDistType       dt
                                            = RangeWtDistNotApplicableC
                                );

                                Range(
                                    const CstrExprTree&             l,
                                    const CstrExprTree&             r,
                                    const WeightType&               w = 0,
                                    const RangeWeightDistType       dt
                                            = RangeWtDistNotApplicableC
                                );

                                Range(
                                    const T&                        l,
                                    const T&                        r,
                                    const CstrExprTree&             w,
                                    const RangeWeightDistType       dt
                                            = RangeWtDistNotApplicableC
                                );
                            
                                Range(
                                    const CstrExprTree&             l,
                                    const T&                        r,
                                    const CstrExprTree&             w,
                                    const RangeWeightDistType       dt
                                            = RangeWtDistNotApplicableC
                                );

                                Range(
                                    const T&                        l,
                                    const CstrExprTree&             r,
                                    const CstrExprTree&             w,
                                    const RangeWeightDistType       dt
                                            = RangeWtDistNotApplicableC
                                );

                                Range(
                                    const CstrExprTree&             l,
                                    const CstrExprTree&             r,
                                    const CstrExprTree&             w,
                                    const RangeWeightDistType       dt
                                            = RangeWtDistNotApplicableC
                                );

    Range<T>*                   clone() const { return new Range<T>(*this); }
};

template<class T>
Range<T>::Range(const T&                    min,
                const T&                    max,
                const WeightType&           w,
                const RangeWeightDistType   dt)
        : RangeBase(createCstrExprTreeConstantNode(min),
                    min != max ? createCstrExprTreeConstantNode(max) : NULL,
                    w ? createCstrExprTreeConstantNode(w) : NULL,
                    dt)
{
    if (min > max) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-IRS");
    }
}

template<class T>
Range<T>::Range(const CstrExprTree&         min,
                const T&                    max,
                const WeightType&           w,
                const RangeWeightDistType   dt)
        : RangeBase(&min,
                    createCstrExprTreeConstantNode(max),
                    w ? createCstrExprTreeConstantNode(w) : NULL,
                    dt)
{
}

template<class T>
Range<T>::Range(const T&                    min,
                const CstrExprTree&         max,
                const WeightType&           w,
                const RangeWeightDistType   dt)
        : RangeBase(createCstrExprTreeConstantNode(min),
                    &max,
                    w ? createCstrExprTreeConstantNode(w) : NULL,
                    dt)
{
}

template<class T>
Range<T>::Range(const CstrExprTree&         min,
                const CstrExprTree&         max,
                const WeightType&           w,
                const RangeWeightDistType   dt)
        : RangeBase(&min,
                    &min == &max ? NULL : &max,
                    w ? createCstrExprTreeConstantNode(w) : NULL,
                    dt)
{
}

template<class T>
Range<T>::Range(const T&                    min,
                const T&                    max,
                const CstrExprTree&         w,
                const RangeWeightDistType   dt)
        : RangeBase(createCstrExprTreeConstantNode(min),
                    min != max ? createCstrExprTreeConstantNode(max) : NULL,
                    &w,
                    dt)
{
    if (min > max) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-IRS");
    }
}

template<class T>
Range<T>::Range(const CstrExprTree&         min,
                const T&                    max,
                const CstrExprTree&         w,
                const RangeWeightDistType   dt)
        : RangeBase(&min,
                    createCstrExprTreeConstantNode(max),
                    &w,
                    dt)
{
}

template<class T>
Range<T>::Range(const T&                    min,
                const CstrExprTree&         max,
                const CstrExprTree&         w,
                const RangeWeightDistType   dt)
        : RangeBase(createCstrExprTreeConstantNode(min),
                    &max,
                    &w,
                    dt)
{
}

template<class T>
Range<T>::Range(const CstrExprTree&         min,
                const CstrExprTree&         max,
                const CstrExprTree&         w,
                const RangeWeightDistType   dt)
        : RangeBase(&min,
                    &min == &max ? NULL : &max,
                    &w,
                    dt)
{
}

//
// List of ranges (allows non-range singular item as well as weighted range)
//
class OpenRangeList {
    typedef vcs_csolver_impl::OpenRangeListImpl Impl_;

public:
                        OpenRangeList(const OpenRangeList&);

    OpenRangeList&      operator=(const OpenRangeList&);

    virtual             ~OpenRangeList();

    virtual bool        isDistSet() const;

    virtual bool        isValueSet() const;

    virtual bool        isEmpty() const;

    virtual RangeBase*  operator[](size_t);

    size_t              getNumRanges() const;

    void                addRangeBase(RangeBase*);

    Impl_&              getImpl();

protected:
                        OpenRangeList();

private:
    Impl_*              impl_;
};


//
// Used for capturing the list of items/ranges to be passed to 'inside'
// constraints
//
template<class T>
class value_set : public OpenRangeList {
public:
    void                addItem(T val);

    void                addItem(const CstrExprTree& val);

    void                addRange(T min, T max);

    void                addRange(T                      min,
                                 const CstrExprTree&    max);

    void                addRange(const CstrExprTree&    min,
                                 T                      max);

    void                addRange(const CstrExprTree&    min,
                                 const CstrExprTree&    max);

    bool                isValueSet() const;
};

template<class T>
void
value_set<T>::addItem(T val) {
    this->addRangeBase(new Range<T>(val, val));
}

template<class T>
void
value_set<T>::addItem(const CstrExprTree& val) {
    this->addRangeBase(new Range<T>(val, val));
}

template<class T>
void
value_set<T>::addRange(T min, T max) {
    this->addRangeBase(new Range<T>(min, max));
}

template<class T>
void
value_set<T>::addRange(T                    min,
                       const CstrExprTree&  max) {
    this->addRangeBase(new Range<T>(min, max));
}

template<class T>
void
value_set<T>::addRange(const CstrExprTree&  min,
                       T                    max) {
    this->addRangeBase(new Range<T>(min, max));
}

template<class T>
void
value_set<T>::addRange(const CstrExprTree&  min,
                       const CstrExprTree&  max) {
    this->addRangeBase(new Range<T>(min, max));
}

template<class T>
bool
value_set<T>::isValueSet() const {
    return true;
}

//
// Used for capturing the list of weighted items/ranges to be passed to 'dist'
// constraints
//
template<class T>
class dist_set : public OpenRangeList {
public:
    void                addWeightedItem(T           val,
                                        WeightType  wt = 1);

    void                addWeightedItem(const CstrExprTree& val,
                                        WeightType  wt = 1);

    void                addWeightedRange(
                            T                       min,
                            T                       max,
                            WeightType              wt = 1,
                            RangeWeightDistType     dt
                                    = WholeRangeWtC
                        );

    void                addWeightedRange(
                            const CstrExprTree&     min,
                            T                       max,
                            WeightType              wt = 1,
                            RangeWeightDistType     dt
                                    = WholeRangeWtC
                        );

    void                addWeightedRange(
                            T                       min,
                            const CstrExprTree&     max,
                            WeightType              wt = 1,
                            RangeWeightDistType     dt
                                    = WholeRangeWtC
                        );

    void                addWeightedRange(
                            const CstrExprTree&     min,
                            const CstrExprTree&     max,
                            WeightType              wt = 1,
                            RangeWeightDistType     dt
                                    = WholeRangeWtC
                        );

    void                addWeightedItem(
                            T                       val,
                            const CstrExprTree&     wt
                        );

    void                addWeightedItem(
                            const CstrExprTree&     val,
                            const CstrExprTree&     wt
                        );

    void                addWeightedRange(
                            T                       min,
                            T                       max,
                            const CstrExprTree&     wt,
                            RangeWeightDistType     dt
                                    = WholeRangeWtC
                        );

    void                addWeightedRange(
                            const CstrExprTree&     min,
                            T                       max,
                            const CstrExprTree&     wt,
                            RangeWeightDistType     dt
                                    = WholeRangeWtC
                        );

    void                addWeightedRange(
                            T                       min,
                            const CstrExprTree&     max,
                            const CstrExprTree&     wt,
                            RangeWeightDistType     dt
                                    = WholeRangeWtC
                        );

    void                addWeightedRange(
                            const CstrExprTree&     min,
                            const CstrExprTree&     max,
                            const CstrExprTree&     wt,
                            RangeWeightDistType     dt
                                    = WholeRangeWtC
                        );

    bool                isDistSet() const;
};

template<class T>
void
dist_set<T>::addWeightedItem(T                      val,
                             WeightType             wt) {
    this->addRangeBase(new Range<T>(val, val, wt, RangeWtDistNotApplicableC));
}

template<class T>
void
dist_set<T>::addWeightedItem(const CstrExprTree&    val,
                             WeightType             wt) {
    this->addRangeBase(new Range<T>(val, val, wt, RangeWtDistNotApplicableC));
}

template<class T>
void
dist_set<T>::addWeightedRange(T                     min,
                              T                     max,
                              WeightType            wt,
                              RangeWeightDistType   dt) {
    this->addRangeBase(new Range<T>(min, max, wt, dt));
}

template<class T>
void
dist_set<T>::addWeightedRange(const CstrExprTree&   min,
                              T                     max,
                              WeightType            wt,
                              RangeWeightDistType   dt) {
    this->addRangeBase(new Range<T>(min, max, wt, dt));
}

template<class T>
void
dist_set<T>::addWeightedRange(T                     min,
                              const CstrExprTree&   max,
                              WeightType            wt,
                              RangeWeightDistType   dt) {
    this->addRangeBase(new Range<T>(min, max, wt, dt));
}

template<class T>
void
dist_set<T>::addWeightedRange(const CstrExprTree&   min,
                              const CstrExprTree&   max,
                              WeightType            wt,
                              RangeWeightDistType   dt) {
    this->addRangeBase(new Range<T>(min, max, wt, dt));
}

template<class T>
void
dist_set<T>::addWeightedItem(T                      val,
                             const CstrExprTree&    wt) {
    this->addRangeBase(new Range<T>(val, val, wt,
                                            RangeWtDistNotApplicableC));
}

template<class T>
void
dist_set<T>::addWeightedItem(const CstrExprTree&    val,
                             const CstrExprTree&    wt) {
    this->addRangeBase(new Range<T>(val, val, wt,
                                            RangeWtDistNotApplicableC));
}

template<class T>
void
dist_set<T>::addWeightedRange(T                     min,
                              T                     max,
                              const CstrExprTree&   wt,
                              RangeWeightDistType   dt) {
    this->addRangeBase(new Range<T>(min, max, wt, dt));
}

template<class T>
void
dist_set<T>::addWeightedRange(const CstrExprTree&   min,
                              T                     max,
                              const CstrExprTree&   wt,
                              RangeWeightDistType   dt) {
    this->addRangeBase(new Range<T>(min, max, wt, dt));
}

template<class T>
void
dist_set<T>::addWeightedRange(T                     min,
                              const CstrExprTree&   max,
                              const CstrExprTree&   wt,
                              RangeWeightDistType   dt) {
    this->addRangeBase(new Range<T>(min, max, wt, dt));
}

template<class T>
void
dist_set<T>::addWeightedRange(const CstrExprTree&   min,
                              const CstrExprTree&   max,
                              const CstrExprTree&   wt,
                              RangeWeightDistType   dt) {
    this->addRangeBase(new Range<T>(min, max, wt, dt));
}

template<class T>
bool
dist_set<T>::isDistSet() const {
    return true;
}


class RangeData {
public:
                                    RangeData();

                                    RangeData(const RangeData&);

                                    ~RangeData(); 

    RangeData&                      operator=(const RangeData&);

    void                            setInternalGen(
                                        vcs_csolver_impl::ConstrainedRandomGeneratorImpl*
                                    );

    void                            clearRangeConstraint(RandVarBase *rv);  

    vcs_csolver_impl::ConstrainedRandomGeneratorImpl* getInternalGen();

    vcs_csolver_impl::RangeDataImpl&  getImpl();

private:
    typedef vcs_csolver_impl::RangeDataImpl Impl_;

    Impl_*                          impl_;
};


// Implementation of random constraint var
template<class T>
class RandVar : public RandVarBase {
public:
    operator                    T() const { return var_; }

    void                        addWeightedRange(const T&           left,
                                                 const T&           right,
                                                 const WeightType   weight);

    void                        addRange(const T& left,
                                         const T& right);

    void                        range(const T& left,
                                      const T& right);

    T                           nextValue();

    const T&                    getValue() const { return var_; }

    void                        setValue(T val) { var_ = val; }

    void                        setValue(const unsigned int* val);

    // This function will allocate storage for raceDataType, so users would
    // need to deep delete the returned raceDataType (after use) using
    // raceFreeDataType.
    CstrDataType*               getValueInCstrDataType() const;

    void                        setValueFromCstrDataType(const CstrDataType* data);

protected:
                                RandVar(rand_obj_base*      parent,
                                        T&                  val,
                                        const EnumTypeInfo* enumTypInfo,
                                        const char*         varName,
                                        const char*         fileName,
                                        size_t              lineNum);

                                RandVar(const RandVar<T>& cpy);

    RandVar&                    operator=(const RandVar<T>& cpy);

    T&                          var_;
};

template<class T>
RandVar<T>::RandVar(rand_obj_base*      parent,
                    T&                  val,
                    const EnumTypeInfo* enumTypInfo,
                    const char*         varName,
                    const char*         fileName,
                    size_t              lineNum)
        : RandVarBase(new VarHandle<T>(&val, enumTypInfo),
                      parent,
                      varName,
                      fileName,
                      lineNum),
          var_(val) {
}

template<class T>
RandVar<T>::RandVar(const RandVar<T>& c)
    : RandVarBase(c),
      var_(c.var_) {
}

template<class T>
RandVar<T>&
RandVar<T>::operator=(const RandVar<T>& c)  {
    if (&c == this) {
        return *this;
    }

    RandVarBase::operator=(c);
    var_ = c.var_;
    return *this;
}

// Allocates raceDataType and fills it with the value of the random constraint
// var and returns the allocated raceDataType.
template<class T>
CstrDataType*
RandVar<T>::getValueInCstrDataType() const {
    return vcs_csolver_api::getValueInCstrDataType(var_, this->getEnumTypeInfo());
}

template<class T>
void
RandVar<T>::setValueFromCstrDataType(const CstrDataType* val) {
    VCS_CSOLVER_NULLCHECK(val);
    var_ = vcs_csolver_api::getValueFromCstrDataType<T>(val, this->getEnumTypeInfo());
}

template<class T>
void 
RandVar<T>::setValue(const unsigned int *val)
{
    this->getVarHandle()->setValueFromUintArray(val);
}

template<class T>
void
RandVar<T>::addWeightedRange(const T&            l,
                             const T&            r,
                             const WeightType    w) {
    RandVarBase::addRange(new Range<T>(l, r, w, WholeRangeWtC));
}

template<class T>
void
RandVar<T>::addRange(const T& l,
                     const T& r) {
    RandVarBase::addRange(new Range<T>(l, r));
}

template<class T>
void
RandVar<T>::range(const T& l,
                  const T& r) {
    this->resetDistribution();
    RandVarBase::addRange(new Range<T>(l, r));
}

template<class T>
T
RandVar<T>::nextValue() {
    if (!this->next()) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-RF");
    }
    return var_;
}

template<class T>
class RandVBase : public RandVar<T> {
public:
    virtual             ~RandVBase() {}

    bool                isRandV() const { return true; }

protected:
                        RandVBase(rand_obj_base*        parent,
                                  const EnumTypeInfo*   enumTypInfo,
                                  const char*           objName,
                                  const char*           fileName,
                                  size_t                lineNum);

                        RandVBase(const RandVBase<T>& cpy);

    RandVBase&          operator=(const RandVBase<T>& cpy);

    T                   value_;
};

template<class T>
RandVBase<T>::RandVBase(rand_obj_base*          parent,
                        const EnumTypeInfo*     enumTypInfo,
                        const char*             varName,
                        const char*             fileName,
                        size_t                  lineNum)
    : RandVar<T>(parent,
                 value_,
                 enumTypInfo,
                 varName,
                 fileName,
                 lineNum),
      value_() {
}

template<class T>
RandVBase<T>::RandVBase(const RandVBase<T>& c)
    : RandVar<T>(c),
      value_(c.value_) {
}

template<class T>
RandVBase<T>&
RandVBase<T>::operator=(const RandVBase<T>& c)  {
    if (&c == this) {
        return *this;
    }

    RandVar<T>::operator=(c); 
    value_ = c.value_;
    return *this;
}


//
// Implementation of randv
//
template<class T>
class randv : public RandVBase<T> {
public:
    randv() : RandVBase<T>(NULL, NULL, NULL, NULL, 0) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-VCERV");
    }

    randv(rand_obj_base*    parent,
          const char*       varName = NULL,
          const char*       fileName = NULL,
          size_t            lineNum = 0) : RandVBase<T>(parent,
                                                        NULL,
                                                        varName,
                                                        fileName,
                                                        lineNum) {
    }

    randv(const randv& other) : RandVBase<T>(other) { }

    randv<T>& operator=(const randv<T>& c) {
        RandVBase<T>::operator=(c);
        return *this;
    }

    randv<T>& operator=(T i) {
        this->value_ = i;
        return *this;
    }

    randv<T>& operator++() {
        ++this->value_;
        return *this;
    }

    T operator++(int) {
        T t = this->value_;
        ++this->value_;
        return t;
    }

    randv<T>& operator--() {
        --this->value_;
        return *this;
    }

    T operator--(int) {
        T t = this->value_;
        --this->value_;
        return t;
    }

    randv<T>& operator+=(T i) {
        this->value_ += i;
        return *this;
    }

    randv<T>& operator-=(T i) {
        this->value_ -= i;
        return *this;
    }

    randv<T>& operator*=(T i) {
        this->value_ *= i;
        return *this;
    }

    randv<T>& operator/=(T i) {
        this->value_ /= i;
        return *this;
    }

    randv<T>& operator%=(T i) {
        this->value_ %= i;
        return *this;
    }

    randv<T>& operator&=(T i) {
        this->value_ &= i;
        return *this;
    }

    randv<T>& operator|=(T i) {
        this->value_ |= i;
        return *this;
    }

    randv<T>& operator^=(T i) {
        this->value_ ^= i;
        return *this;
    }

    randv<T>& operator<<=(T i) {
        this->value_ <<= i;
        return *this;
    }

    randv<T>& operator>>=(T i) {
        this->value_ >>= i;
        return *this;
    }
};

template<class T>
std::ostream&
operator<<(std::ostream& os, const randv<T>& e) {
    os << e.getValue();
    return os;
}

template<>
class randv<bool> : public RandVBase<bool> {
public:
    randv() : RandVBase<bool>(NULL, NULL, NULL, NULL, 0) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-VCERV");
    }

    randv(rand_obj_base*    parent,
          const char*       varName  = NULL,
          const char*       fileName = NULL,
          size_t            lineNum  = 0) : RandVBase<bool>(parent,
                                                            NULL,
                                                            varName,
                                                            fileName,
                                                            lineNum) {
    }

    randv(const randv& other) : RandVBase<bool>(other) {
    }

    randv<bool>& operator=(const randv<bool>& c) {
        RandVBase<bool>::operator=(c);
        return *this;
    }

    randv<bool>& operator=(bool i) {
        this->value_ = i;
        return *this;
    }
};


//
// Implementation of rand_var
//
template<class T>
class rand_var : public RandVBase<T> {
public:
    rand_var() : RandVBase<T>(NULL, NULL, NULL, NULL, 0) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-VCERV");
    }

    rand_var(rand_obj_base* parent,
          const char*       varName = NULL,
          const char*       fileName = NULL,
          size_t            lineNum = 0) : RandVBase<T>(parent,
                                                        NULL,
                                                        varName,
                                                        fileName,
                                                        lineNum) {
    }

    rand_var(const rand_var& other) : RandVBase<T>(other) { }

    rand_var<T>& operator=(const rand_var<T>& c) {
        RandVBase<T>::operator=(c);
        return *this;
    }

    rand_var<T>& operator=(T i) {
        this->value_ = i;
        return *this;
    }

    rand_var<T>& operator++() {
        ++this->value_;
        return *this;
    }

    T operator++(int) {
        T t = this->value_;
        ++this->value_;
        return t;
    }

    rand_var<T>& operator--() {
        --this->value_;
        return *this;
    }

    T operator--(int) {
        T t = this->value_;
        --this->value_;
        return t;
    }

    rand_var<T>& operator+=(T i) {
        this->value_ += i;
        return *this;
    }

    rand_var<T>& operator-=(T i) {
        this->value_ -= i;
        return *this;
    }

    rand_var<T>& operator*=(T i) {
        this->value_ *= i;
        return *this;
    }

    rand_var<T>& operator/=(T i) {
        this->value_ /= i;
        return *this;
    }

    rand_var<T>& operator%=(T i) {
        this->value_ %= i;
        return *this;
    }

    rand_var<T>& operator&=(T i) {
        this->value_ &= i;
        return *this;
    }

    rand_var<T>& operator|=(T i) {
        this->value_ |= i;
        return *this;
    }

    rand_var<T>& operator^=(T i) {
        this->value_ ^= i;
        return *this;
    }

    rand_var<T>& operator<<=(T i) {
        this->value_ <<= i;
        return *this;
    }

    rand_var<T>& operator>>=(T i) {
        this->value_ >>= i;
        return *this;
    }
};

template<class T>
std::ostream&
operator<<(std::ostream& os, const rand_var<T>& e) {
    os << e.getValue();
    return os;
}

template<>
class rand_var<bool> : public RandVBase<bool> {
public:
    rand_var() : RandVBase<bool>(NULL, NULL, NULL, NULL, 0) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-VCERV");
    }

    rand_var(rand_obj_base*    parent,
             const char*       varName  = NULL,
             const char*       fileName = NULL,
             size_t            lineNum  = 0) : RandVBase<bool>(parent,
                                                            NULL,
                                                            varName,
                                                            fileName,
                                                            lineNum) {
    }

    rand_var(const rand_var& other) : RandVBase<bool>(other) {
    }

    rand_var<bool>& operator=(const rand_var<bool>& c) {
        RandVBase<bool>::operator=(c);
        return *this;
    }

    rand_var<bool>& operator=(bool i) {
        this->value_ = i;
        return *this;
    }
};

template<class T, class A>
class RandVectorInterface : public RandVectorInterfaceBase {
public:
    explicit                    RandVectorInterface(RandVector<T,A>& vec);

    const CstrExprTree&         operator[](const CstrExprTree& idx);

    const CstrExprTree&         operator[](VectorSizeType idx);

    const CstrExprTree&         operator()(VectorSizeType arrSliceMinIdx,
                                           VectorSizeType arrSliceMaxIdx);
};

template<class T, class A>
RandVectorInterface<T,A>::RandVectorInterface(RandVector<T,A>& vec)
    : RandVectorInterfaceBase(vec) {
}

template<class T, class A>
const CstrExprTree&
RandVectorInterface<T,A>::operator[](const CstrExprTree& idx) {
    RandVecBase* vec = this->getVector();
    VCS_CSOLVER_NULLCHECK(vec);
    return createCstrExprVariable(new VectorSelect<T,A>(*vec,
                                                        &idx,
                                                        vec->getEnumTypeInfo()));
}

template<class T, class A>
const CstrExprTree&
RandVectorInterface<T,A>::operator[](VectorSizeType idx) {
    RandVecBase* vec = this->getVector();
    VCS_CSOLVER_NULLCHECK(vec);
    return createCstrExprVariable(new VectorSelect<T,A>(*vec,
                                                        idx,
                                                        vec->getEnumTypeInfo()));
}

template<class T, class A>
const CstrExprTree&
RandVectorInterface<T,A>::operator()(VectorSizeType     idxMin,
                                     VectorSizeType     idxMax) {
    RandVecBase* vec = this->getVector();
    VCS_CSOLVER_NULLCHECK(vec);
    if (idxMax < idxMin) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-IVSS");
    }
    return createCstrExprVariable(new VectorSelect<T,A>(*vec,
                                                        idxMin,
                                                        vec->getEnumTypeInfo(),
                                                        idxMax - idxMin + 1));
}


//
// A representation of RandVector that actually extends from std::vector, so
// will support full capabilities of std::vector. In other words, RandVector<T>
// "is a" std::vector<T>.
//
template<class T, class A>
class RandVector : public RandVecBase, public std::vector<T,A> {
public:
                                        RandVector(rand_obj_base*   parent,
                                                   const char*      vecName,
                                                   const char*      fileName,
                                                   size_t           lineNum);

                                        RandVector(const RandVector& c);

                                        RandVector(rand_obj_base*   parent,
                                                   const char*      vecName,
                                                   const char*      fileName,
                                                   size_t           lineNum,
                                                   const A&         a);

                                        RandVector(rand_obj_base*   parent,
                                                   typename std::vector<T,A>::size_type sz,
                                                   const char*      vecName,
                                                   const char*      fileName,
                                                   size_t           lineNum,
                                                   const T&         val,
                                                   const A&         a);

                                        template<typename InputIterator_>
                                        RandVector(rand_obj_base*   parent,
                                                   InputIterator_   first,
                                                   InputIterator_   last,
                                                   const char*      vecName,
                                                   const char*      fileName,
                                                   size_t           lineNum,
                                                   const A&         a)
                                            : RandVecBase(parent,
                                                          vecName,
                                                          fileName,
                                                          lineNum),
                                              std::vector<T,A>(
                                                  first,
                                                  last,
                                                  a
                                              ),
                                              ifc_(*this) {}

                                        ~RandVector();

    RandVector&                         operator=(const RandVector& c); 

    RandVectorInterfaceBase&            operator()() { return ifc_; }

    VectorSizeType                      getSize() const;

    void                                reSize(VectorSizeType sz) { this->resize(sz); }

    typename std::vector<T,A>::reference operator[](typename std::vector<T,A>::size_type);

    typename std::vector<T,A>::const_reference operator[](typename std::vector<T,A>::size_type) const;

    const CstrExprTree&                 operator[](const CstrExprTree&) const;

    virtual unsigned int                getNDimension() const;

    virtual PrecisionType               getPrecision() const;

    virtual bool                        isSigned() const;

    void                                setValueFromCstrDataType(VectorSizeType      idx,
                                                                 const CstrDataType* val);

    CstrDataType*                       getValueInCstrDataType(VectorSizeType      idx);

    void                                setValue(VectorSizeType     index,
                                                 unsigned int*      value,
                                                 const EnumTypeInfo* enumTypeInfo);

private:
    RandVectorInterface<T,A>            ifc_;
};

template<class T, class A>
RandVector<T,A>::RandVector(rand_obj_base*  parent,
                            const char*     vecName,
                            const char*     fileName,
                            size_t          lineNum)
    : RandVecBase(parent, vecName, fileName, lineNum),
      std::vector<T,A>(),
      ifc_(*this) {
}

template<class T, class A>
RandVector<T,A>::RandVector(const RandVector<T,A>& c)
    : RandVecBase(c),
      std::vector<T,A>(c),
      ifc_(*this) {
}

template<class T, class A>
RandVector<T,A>::RandVector(rand_obj_base*  parent,
                            const char*     vecName,
                            const char*     fileName,
                            size_t          lineNum,
                            const A&        a)
    : RandVecBase(parent, vecName, fileName, lineNum),
      std::vector<T,A>(a),
      ifc_(*this) {
}

template<class T, class A>
RandVector<T,A>::RandVector(rand_obj_base*                          parent,
                            typename std::vector<T,A>::size_type    sz,
                            const char*                             vecName,
                            const char*                             fileName,
                            size_t                                  lineNum,
                            const T&                                val,
                            const A&                                a)
    : RandVecBase(parent, vecName, fileName, lineNum),
      std::vector<T,A>(sz, val, a),
      ifc_(*this) {
}

template<class T, class A>
RandVector<T,A>::~RandVector() {
    ifc_.deleteSizeVar();
}

template<class T, class A>
RandVector<T,A>&
RandVector<T,A>::operator=(const RandVector<T,A>& c) {
    if (this == &c) return *this;

    std::vector<T,A>::operator=(c);
    ifc_.setVector(*this);
}

template<class T, class A>
typename std::vector<T,A>::reference
RandVector<T,A>::operator[](typename std::vector<T,A>::size_type idx) {
    return std::vector<T,A>::operator[](idx);
}

template<class T, class A>
typename std::vector<T,A>::const_reference
RandVector<T,A>::operator[](typename std::vector<T,A>::size_type idx) const {
    return std::vector<T,A>::operator[](idx);
}

template<class T, class A>
const CstrExprTree&
RandVector<T,A>::operator[](const CstrExprTree& idx) const {
    vcsCsolverMsgReportNoSource("CPPSOLVER-IVSIF");
    return idx;
}

template<class T, class A>
VectorSizeType
RandVector<T,A>::getSize() const {
    return static_cast<VectorSizeType>(std::vector<T,A>::size());
}

template<class T, class A>
unsigned int
RandVector<T,A>::getNDimension() const {
    return GetVectorDimension<T,A>::value;
}

template<class T,class A>
PrecisionType
RandVector<T,A>::getPrecision() const {
    T tmp;
    const VarHandle<T> var_handle(const_cast<T*>(&tmp),
                                  this->getEnumTypeInfo());
    return var_handle.getPrecision();
}

template<class T, class A>
bool
RandVector<T,A>::isSigned() const {
    T tmp;
    const VarHandle<T> var_handle(const_cast<T*>(&tmp),
                                  this->getEnumTypeInfo());
    return var_handle.isSigned();
}

template<class T, class A>
CstrDataType*
RandVector<T,A>::getValueInCstrDataType(VectorSizeType idx) {
    return vcs_csolver_api::getValueInCstrDataType<T>(this->operator[](idx),
                                                      this->getEnumTypeInfo());
}

template<class T, class A>
void
RandVector<T,A>::setValueFromCstrDataType(VectorSizeType        idx,
                                          const CstrDataType*   val) {
    VCS_CSOLVER_NULLCHECK(val);
    typedef typename VectorTypInfo<T,A>::PrimaryValueTyp ValueTyp;
    T value = getValueFromCstrDataType<T>(val, this->getEnumTypeInfo());
    this->operator[](idx) = value;
}

template<class T, class A>
void
RandVector<T,A>::setValue(VectorSizeType        idx,
                          unsigned int*         val,
                          const EnumTypeInfo*   enumTypInfo) {
    VCS_CSOLVER_NULLCHECK(val);

    T tmp;
    VarHandle<T> var_handle(&tmp, enumTypInfo);
    var_handle.setValueFromUintArray(val);
    this->at(idx) = tmp;
}


//
// Implementation of rand_vec
//
template<class T, class A = std::allocator<T> >
class rand_vec : public RandVector<T,A> {
public:
    rand_vec() : RandVector<T,A>(NULL, NULL, NULL, 0) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-VCERVEC");
    }

    rand_vec(rand_obj_base*         parent,
             const char*            varName     = NULL,
             const char*            fileName    = NULL,
             size_t                 lineNum     = 0)
        : RandVector<T,A>(parent, varName, fileName, lineNum) {
    }

    rand_vec(rand_obj_base*         parent,
             const A&               a,
             const char*            varName     = NULL,
             const char*            fileName    = NULL,
             size_t                 lineNum     = 0)
        : RandVector<T,A>(parent, varName, fileName, lineNum, a) {
    }

    rand_vec(rand_obj_base*                         parent,
             typename std::vector<T,A>::size_type   sz,
             const T&                               val         = T(),
             const A&                               a           = A(),
             const char*                            varName     = NULL,
             const char*                            fileName    = NULL,
             size_t                                 lineNum     = 0)
        : RandVector<T,A>(parent, sz, varName, fileName, lineNum, val, a) {
    }

    template<typename InputIterator_>
    rand_vec(rand_obj_base*         parent,
             InputIterator_         first,
             InputIterator_         last,
             const A&               a           = A(),
             const char*            varName     = NULL,
             const char*            fileName    = NULL,
             size_t                 lineNum     = 0)
        : RandVector<T,A>(parent, first, last, varName, fileName, lineNum, a) {
    }
};


//
// This function can be used for overriding the implementation
// defined value of the global RNG (Random Number Generator)
// seed.
//
void set_global_seed(unsigned int s);


//
// Implementation of ref (Essentially, it returns a reference to its argument).
//
template<class T>
const CstrExprTree&
ref(T&                  r,
    const char*         varName     = NULL,
    const char*         fileName    = NULL,
    size_t              lineNum     = 0) {
    EnumTypeInfoHelper<T> enumInfo;
    return createCstrExprVariable(new StateVar<T>(r,
                                                  enumInfo.getEnumTypeInfo(),
                                                  varName,
                                                  fileName,
                                                  lineNum));
}

template<class T>
const CstrExprTree&
ref(randv<T>&           r,
    const char*         varName     = NULL,
    const char*         fileName    = NULL,
    size_t              lineNum     = 0) {
    return createOrderedCstrExprVariable(&r,
                                         varName,
                                         fileName,
                                         lineNum);
}

template<class T>
const CstrExprTree&
ref(rand_var<T>&        r,
    const char*         varName     = NULL,
    const char*         fileName    = NULL,
    size_t              lineNum     = 0) {
    return createOrderedCstrExprVariable(&r,
                                         varName,
                                         fileName,
                                         lineNum);
}

template<class T>
const CstrExprTree&
ref(const T&            value,
    const char*         varName     = NULL,
    const char*         fileName    = NULL,
    size_t              lineNum     = 0) {
    //
    // Reference to constant could as well be a constant.
    //
    CstrExprTree* ret = createCstrExprTreeConstantNode(value);
    VCS_CSOLVER_NULLCHECK(ret);
    return *ret;
}


//
// 'inside' constraint API
//
template<class T>
ConstraintBlockItem&
inside(const CstrExprTree&      lhs,
       const value_set<T>&      set) {
    return vcs_csolver_api::createInsideConstraint(lhs, &set);
}

//
// 'dist' constraint API
//
template<class T>
ConstraintBlockItem&
dist(const CstrExprTree&        lhs,
     const dist_set<T>&         set) {
    return vcs_csolver_api::createDistConstraint(lhs, &set);
}

//
// 'unique' constraint API support
//
class uniq_set {
public:
                        uniq_set();

                        ~uniq_set();

                        uniq_set(const uniq_set&);

    uniq_set&           operator=(const uniq_set&);

    void                add(const CstrExprTree&);

    void                add(const RandVectorInterfaceBase&);

    void                add(const ConstraintVar&);

    void                add(const RandVecBase&);

private:
    typedef vcs_csolver_impl::UniqSetImpl Impl_;

    Impl_*              impl_;

public:
    Impl_*              getImpl() const;
};

ConstraintBlockItem&    unique(const uniq_set&);

} // end - namespace vcs_csolver_api


/**
* Constraint specification API
*/
#define CSOLVER_CONSTRAINT(_cstr_expr_) constraint((_cstr_expr_))

/**
* Used for specifying source info during construction.
*/
#define CSOLVER_SRCINFO(__var__) #__var__, __FILE__, __LINE__

/**
* CSolver enum support
*/
#define CSOLVER_ENUM(enum_type)                                             \
    namespace vcs_csolver_api {                                             \
    template<>                                                              \
    class EnumInfo<enum_type> : public EnumInfoBase<enum_type> {            \
    public:                                                                 \
        EnumInfo();                                                         \
    };                                                                      \
                                                                            \
    template<>                                                              \
    struct  EnumTypeInfoHelper<enum_type> {                                 \
        const EnumTypeInfo* getEnumTypeInfo() {                             \
            static EnumInfo<enum_type> enum_typ_info;                       \
            return &enum_typ_info;                                          \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<>                                                              \
    class rand_var<enum_type> : public RandVBase<enum_type> {               \
    public:                                                                 \
        rand_var() : RandVBase<enum_type>(NULL,                             \
                                       this->getEnumTypeInfo(),             \
                                       NULL,                                \
                                       NULL,                                \
                                       0) {                                 \
            vcsCsolverMsgReportNoSource("CPPSOLVER-VCERV");                 \
        }                                                                   \
                                                                            \
        rand_var(rand_obj_base* parent,                                     \
                 const char*    varName  = NULL,                            \
                 const char*    fileName = NULL,                            \
                 size_t         lineNum  = 0) : RandVBase<enum_type>(       \
                                                    parent,                 \
                                                    this->getEnumTypeInfo(),\
                                                    varName,                \
                                                    fileName,               \
                                                    lineNum                 \
                                                ) {                         \
        }                                                                   \
                                                                            \
        rand_var(const rand_var& other) : RandVBase<enum_type>(other) { }   \
                                                                            \
        rand_var<enum_type>& operator=(const rand_var<enum_type>& c) {      \
            RandVBase<enum_type>::operator=(c);                             \
            return *this;                                                   \
        }                                                                   \
                                                                            \
        rand_var<enum_type>& operator=(enum_type i) {                       \
            this->value_ = i;                                               \
            return *this;                                                   \
        }                                                                   \
                                                                            \
        bool isSigned() const { return getEnumTypeInfo()->isSigned(); }     \
                                                                            \
        const EnumTypeInfo* getEnumTypeInfo() const {                       \
            static EnumInfo<enum_type> enum_typ_info;                       \
            return &enum_typ_info;                                          \
        }                                                                   \
                                                                            \
        const char* getEnumName() const {                                   \
            return getEnumTypeInfo()->getEnumName();                        \
        }                                                                   \
                                                                            \
        EnumIdType getEnumId(vcs_csolver_impl::ConstrainedRandomGeneratorImpl* genImpl) const {\
            return getEnumTypeInfo()->getEnumId(genImpl);                   \
        }                                                                   \
                                                                            \
        bool isEnumVar() const {                                            \
            return true;                                                    \
        }                                                                   \
                                                                            \
        void setValue(const unsigned int* v) {                              \
            var_ = static_cast<                                             \
                       const EnumInfo<enum_type>*                           \
                   >(this->getEnumTypeInfo())->getEnumValue(v[0]);          \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<>                                                              \
    class rand_vec<enum_type, std::allocator<enum_type> >                   \
            : public RandVector<enum_type, std::allocator<enum_type> > {    \
    public:                                                                 \
        rand_vec() : RandVector<enum_type,std::allocator<enum_type> >(      \
                        NULL,                                               \
                        NULL,                                               \
                        NULL,                                               \
                        0                                                   \
                     ) {                                                    \
            vcsCsolverMsgReportNoSource("CPPSOLVER-VCERVEC");               \
        }                                                                   \
                                                                            \
        rand_vec(rand_obj_base*     parent,                                 \
                 const char*        varName  = NULL,                        \
                 const char*        fileName = NULL,                        \
                 size_t             lineNum  = 0)                           \
            : RandVector<enum_type, std::allocator<enum_type> >(parent,     \
                                                                varName,    \
                                                                fileName,   \
                                                                lineNum) {  \
                                                                            \
        }                                                                   \
                                                                            \
        const char* getEnumName() const {                                   \
            return getEnumTypeInfo()->getEnumName();                        \
        }                                                                   \
                                                                            \
        EnumIdType getEnumId(vcs_csolver_impl::ConstrainedRandomGeneratorImpl* genImpl) const {\
            return getEnumTypeInfo()->getEnumId(genImpl);                   \
        }                                                                   \
                                                                            \
        bool isEnumVector() const {                                         \
            return true;                                                    \
        }                                                                   \
                                                                            \
        const EnumTypeInfo* getEnumTypeInfo() const {                       \
            static EnumInfo<enum_type> enum_typ_info;                       \
            return &enum_typ_info;                                          \
        }                                                                   \
    };                                                                      \
                                                                            \
    }                                                                       \
                                                                            \
    vcs_csolver_api::EnumInfo<enum_type>::EnumInfo()                        \
            : EnumInfoBase<enum_type>(#enum_type)

#define CSOLVER_ENUM_MEMBER(_x_) addEnumMember(_x_, #_x_)


/**
* Enum support in CRAVE style/API
*/
#define CRAVE_ENUM(enum_type, num_enumerators, ...)                         \
    namespace vcs_csolver_api {                                             \
    template<>                                                              \
    class EnumInfo<enum_type> : public EnumInfoBase<enum_type> {            \
    public:                                                                 \
        EnumInfo() : EnumInfoBase<enum_type>(#enum_type) {                  \
            const enum_type enumerators[] = { __VA_ARGS__ };                \
            initialize(num_enumerators, #__VA_ARGS__, enumerators);         \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<>                                                              \
    struct  EnumTypeInfoHelper<enum_type> {                                 \
        const EnumTypeInfo* getEnumTypeInfo() {                             \
            static EnumInfo<enum_type> enum_typ_info;                       \
            return &enum_typ_info;                                          \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<>                                                              \
    class randv<enum_type> : public RandVBase<enum_type> {                  \
    public:                                                                 \
        randv() : RandVBase<enum_type>(NULL,                                \
                                       this->getEnumTypeInfo(),             \
                                       NULL,                                \
                                       NULL,                                \
                                       0) {                                 \
            vcsCsolverMsgReportNoSource("CPPSOLVER-VCERV");                 \
        }                                                                   \
                                                                            \
        randv(RandObjForCrave* parent,                                      \
              const char*      varName  = NULL,                             \
              const char*      fileName = NULL,                             \
              size_t           lnNum  = 0) : RandVBase<enum_type>(          \
                                                parent,                     \
                                                this->getEnumTypeInfo(),    \
                                                varName,                    \
                                                fileName,                   \
                                                lnNum                       \
                                             ) {                            \
        }                                                                   \
                                                                            \
        randv(const randv& other) : RandVBase<enum_type>(other) { }         \
                                                                            \
        randv<enum_type>& operator=(const randv<enum_type>& c) {            \
            RandVBase<enum_type>::operator=(c);                             \
            return *this;                                                   \
        }                                                                   \
                                                                            \
        randv<enum_type>& operator=(enum_type i) {                          \
            this->value_ = i;                                               \
            return *this;                                                   \
        }                                                                   \
                                                                            \
        bool isSigned() const { return getEnumTypeInfo()->isSigned(); }     \
                                                                            \
        const EnumTypeInfo* getEnumTypeInfo() const {                       \
            static EnumInfo<enum_type> enum_typ_info;                       \
            return &enum_typ_info;                                          \
        }                                                                   \
                                                                            \
        const char* getEnumName() const {                                   \
            return getEnumTypeInfo()->getEnumName();                        \
        }                                                                   \
                                                                            \
        EnumIdType getEnumId(vcs_csolver_impl::ConstrainedRandomGeneratorImpl* genImpl) const {\
            return getEnumTypeInfo()->getEnumId(genImpl);                   \
        }                                                                   \
                                                                            \
        bool isEnumVar() const {                                            \
            return true;                                                    \
        }                                                                   \
                                                                            \
        void setValue(const unsigned int* v) {                              \
            var_ = static_cast<                                             \
                       const EnumInfo<enum_type>*                           \
                   >(this->getEnumTypeInfo())->getEnumValue(v[0]);          \
        }                                                                   \
    };                                                                      \
                                                                            \
    template<>                                                              \
    class rand_vec<enum_type, std::allocator<enum_type> >                   \
            : public RandVector<enum_type, std::allocator<enum_type> > {    \
    public:                                                                 \
        rand_vec() : RandVector<enum_type,std::allocator<enum_type> >(      \
                        NULL,                                               \
                        NULL,                                               \
                        NULL,                                               \
                        0                                                   \
                     ) {                                                    \
            vcsCsolverMsgReportNoSource("CPPSOLVER-VCERVEC");               \
        }                                                                   \
                                                                            \
        rand_vec(RandObjForCrave*   parent,                                 \
                 const char*        varName  = NULL,                        \
                 const char*        fileName = NULL,                        \
                 size_t             lineNum  = 0)                           \
            : RandVector<enum_type, std::allocator<enum_type> >(parent,     \
                                                                varName,    \
                                                                fileName,   \
                                                                lineNum) {  \
                                                                            \
        }                                                                   \
                                                                            \
        const char* getEnumName() const {                                   \
            return getEnumTypeInfo()->getEnumName();                        \
        }                                                                   \
                                                                            \
        EnumIdType getEnumId(vcs_csolver_impl::ConstrainedRandomGeneratorImpl* genImpl) const {\
            return getEnumTypeInfo()->getEnumId(genImpl);                   \
        }                                                                   \
                                                                            \
        bool isEnumVector() const {                                         \
            return true;                                                    \
        }                                                                   \
                                                                            \
        const EnumTypeInfo* getEnumTypeInfo() const {                       \
            static EnumInfo<enum_type> enum_typ_info;                       \
            return &enum_typ_info;                                          \
        }                                                                   \
    };                                                                      \
                                                                            \
    } // end - namespace vcs_csolver_api

#endif
