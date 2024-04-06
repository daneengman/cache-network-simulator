/******************************************************************
 *   Copyright (c) 2014 by Synopsys Inc. - All Rights Reserved    *
 *                                                                *
 *   CONFIDENTIAL AND PROPRIETARY INFORMATION OF SYNOPSYS INC.    *
 ******************************************************************/
#ifndef __SYNOPSYS_VCS_CSOLVER_CONSTRAINT_HH__
#define __SYNOPSYS_VCS_CSOLVER_CONSTRAINT_HH__

#include "vcs_csolver_constraint_expr_operators.h"
#include "vcs_csolver_util.hh"

namespace vcs_csolver_api {

class Constraint {
public:
    typedef enum {
        ExprConstraintC,
        SoftConstraintC,
        ForeachConstraintC,
        RangeConstraintC,
        UniqueConstraintC,
        BlockConstraintC,
        NamedBlockConstraintC
    } ConstraintType;

    virtual                         ~Constraint();

    ConstraintType                  getConstraintType() const;

    virtual bool                    isExprConstraint() const;

    virtual bool                    isRangeConstraint() const;

    virtual bool                    isUniqueConstraint() const;

    virtual bool                    isConstraintBlockItem() const;

    virtual bool                    isForeachConstraint() const;

    virtual VarIdType               getLHSExprVarId() const;

    virtual bool                    isSoftConstraint() const;

    virtual unsigned int            getSoftPriority() const;

    virtual void                    setSoftPriority(unsigned int);

    virtual bool                    isNamedBlockConstraint() const;

    virtual bool                    isBlockConstraint() const;

    virtual const CstrExprTree*     getConstraintExpr() const;

    virtual void                    setConstraintExpr(CstrExprTree*);

    virtual unsigned int            getNumRanges() const;

    virtual const char*             getName() const;

    virtual bool                    isEnabled() const;

    virtual void                    setEnabled();

    virtual void                    setDisabled();

    virtual CstrIdType              getId() const;

    virtual void                    setId(int id);

    const Constraint*               getParent() const;

    void                            setParent(const Constraint* p);

    virtual CstrIdType              getNextCstrBlkItemId();

    CstrIdType                      getTopLevelBlkCstrId() const;

    virtual void                    unregisterGenFromAllDistCstrs(
                                        vcs_csolver_impl::ConstrainedRandomGeneratorImpl* gen
                                    );

protected:
    explicit                        Constraint(ConstraintType t);

                                    Constraint(CstrIdType       id,
                                               ConstraintType   t);

private:
    typedef vcs_csolver_impl::ConstraintImpl Impl_;

                                    Constraint(const Constraint&);

    Constraint&                     operator=(const Constraint&);

    Impl_* const                    impl_;
};

class ConstraintBlockItem
    : public Constraint,
      public CircularSListItem<ConstraintBlockItem> {
public:
    //
    // Used for capturing/grouping comma separated list of independent
    // constraints, during parsing...
    //
    ConstraintBlockItem&    operator,(const ConstraintBlockItem&);

    bool                    isConstraintBlockItem() const;

protected:
    explicit                ConstraintBlockItem(ConstraintType t);
};

//
// Operator overloads for capturing syntactic usage errors.
//
bool                    operator,(const ConstraintBlockItem&, bool);
ConstraintBlockItem&    operator,(bool, const ConstraintBlockItem&);


//
// ExprConstraint
//
class ExprConstraint : public ConstraintBlockItem {
public:
    explicit            ExprConstraint(CstrExprTree* cstr_expr);

                        ~ExprConstraint();

    const CstrExprTree* getConstraintExpr() const;

    void                setConstraintExpr(CstrExprTree* e);

    bool                isExprConstraint() const;

protected:
                        ExprConstraint(CstrExprTree*    cstr_expr,
                                       ConstraintType   t);

private:
    typedef vcs_csolver_impl::ExprConstraintImpl Impl_;

    Impl_* const        impl_;
};


//
// Interface for constraint expression tree representation.
//
class CstrExprTree {
public:
    //
    // CAUTION: PLEASE DO NOT ADD ANY DATA MEMBER HERE (NOT EVEN ANY VIRTUAL
    //          MEMBER FUNCTION) AS THAT WOULD INCREASE THE SIZE OF
    //          its derived class gp_expr_tree. Currently, this class doesn't
    //          add a single byte to gp_expr_tree.
    //

    const CstrExprTree&             operator!() const;

    const CstrExprTree&             operator-() const;

    const CstrExprTree&             operator~() const;

    const CstrExprTree&             to_signed() const;

    const CstrExprTree&             to_unsigned() const;

    const CstrExprTree&             operator[](const CstrExprTree& idx) const;

    const CstrExprTree&             operator()(unsigned int left,
                                               unsigned int right) const;
    
    const CstrExprTree&             operator[](unsigned int index) const;

                                    operator ExprConstraint&() const;

    ConstraintBlockItem&            operator,(const ConstraintBlockItem&) const;

    const CstrExprTree&             size() const;

protected:
                                    CstrExprTree();

private:
                                    CstrExprTree(const CstrExprTree&);

    CstrExprTree&                   operator=(const CstrExprTree&);
};


//
// Operator overloads for parsing all kind of CSOLVER binary constraint
// expressions.
//
#define DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(_OPERATOR_,_BIN_OP_)     \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (const CstrExprTree&        lhs_tree,                  \
                         const CstrExprTree&        rhs_tree);                 \
                                                                               \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (const CstrExprTree&        lhs_tree,                  \
                         ForeachLoopVarForCrave&    rhs_tree);                 \
                                                                               \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (ForeachLoopVarForCrave&    lhs_tree,                  \
                         const CstrExprTree&        rhs_tree);                 \
                                                                               \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (ForeachLoopVarForCrave&    lhs_tree,                  \
                         ForeachLoopVarForCrave&    rhs_tree);                 \
                                                                               \
    template<class T>                                                          \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (const T&               lhs,                           \
                         const CstrExprTree&    rhs_tree) {                    \
        const CstrExprTree* lhs_tree = createCstrExprTreeConstantNode(lhs);    \
        VCS_CSOLVER_NULLCHECK(lhs_tree);                                       \
        return createCstrExprTreeBinOpNode(*lhs_tree, rhs_tree, _BIN_OP_);     \
    }                                                                          \
                                                                               \
    template<class T>                                                          \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (const CstrExprTree&    lhs_tree,                      \
                         const T&               rhs) {                         \
        const CstrExprTree* rhs_tree = createCstrExprTreeConstantNode(rhs);    \
        VCS_CSOLVER_NULLCHECK(rhs_tree);                                       \
        return createCstrExprTreeBinOpNode(lhs_tree, *rhs_tree, _BIN_OP_);     \
    }                                                                          \
                                                                               \
    template<class T>                                                          \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (T&                     lhs,                           \
                         const CstrExprTree&    rhs_tree) {                    \
        vcsCsolverMsgReportNoSource("CPPSOLVER-DUOLVIC");                      \
        const CstrExprTree* lhs_tree = createCstrExprTreeConstantNode(lhs);    \
        VCS_CSOLVER_NULLCHECK(lhs_tree);                                       \
        return createCstrExprTreeBinOpNode(*lhs_tree, rhs_tree, _BIN_OP_);     \
    }                                                                          \
                                                                               \
    template<class T>                                                          \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (const CstrExprTree&    lhs_tree,                      \
                         T&                     rhs) {                         \
        vcsCsolverMsgReportNoSource("CPPSOLVER-DUOLVIC");                      \
        const CstrExprTree* rhs_tree = createCstrExprTreeConstantNode(rhs);    \
        VCS_CSOLVER_NULLCHECK(rhs_tree);                                       \
        return createCstrExprTreeBinOpNode(lhs_tree, *rhs_tree, _BIN_OP_);     \
    }                                                                          \
                                                                               \
    template<class T>                                                          \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (const CstrExprTree&    lhs_tree,                      \
                         randv<T>&              rhs) {                         \
        const CstrExprTree* rhs_tree = createCstrExprTreeConstantNode(rhs.getValue());\
        VCS_CSOLVER_NULLCHECK(rhs_tree);                                       \
        return createCstrExprTreeBinOpNode(lhs_tree, *rhs_tree, _BIN_OP_);     \
    }                                                                          \
                                                                               \
    template<class T>                                                          \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (randv<T>&              lhs,                           \
                         const CstrExprTree&    rhs_tree) {                    \
        const CstrExprTree* lhs_tree = createCstrExprTreeConstantNode(lhs.getValue());\
        VCS_CSOLVER_NULLCHECK(lhs_tree);                                       \
        return createCstrExprTreeBinOpNode(*lhs_tree, rhs_tree, _BIN_OP_);     \
    }                                                                          \
                                                                               \
    template<class T>                                                          \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (const CstrExprTree&    lhs_tree,                      \
                         rand_var<T>&           rhs) {                         \
        const CstrExprTree* rhs_tree = createCstrExprTreeConstantNode(rhs.getValue());\
        VCS_CSOLVER_NULLCHECK(rhs_tree);                                       \
        return createCstrExprTreeBinOpNode(lhs_tree, *rhs_tree, _BIN_OP_);     \
    }                                                                          \
                                                                               \
    template<class T>                                                          \
    const CstrExprTree&                                                        \
    operator _OPERATOR_ (rand_var<T>&           lhs,                           \
                         const CstrExprTree&    rhs_tree) {                    \
        const CstrExprTree* lhs_tree = createCstrExprTreeConstantNode(lhs.getValue());\
        VCS_CSOLVER_NULLCHECK(lhs_tree);                                       \
        return createCstrExprTreeBinOpNode(*lhs_tree, rhs_tree, _BIN_OP_);     \
    }

DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(==, BIN_OP_LOG_EQEQ)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(!=, BIN_OP_LOG_NEQ)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(&&, BIN_OP_LOG_AND)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(||, BIN_OP_LOG_OR)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(<,  BIN_OP_REL_LT)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(>,  BIN_OP_REL_GT)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(<=, BIN_OP_REL_LEQ)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(>=, BIN_OP_REL_GEQ)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(+ , BIN_OP_ARITH_PLUS)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(- , BIN_OP_ARITH_MINUS)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(* , BIN_OP_ARITH_MULT)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(/ , BIN_OP_ARITH_DIV)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(% , BIN_OP_ARITH_MOD)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(& , BIN_OP_BIT_AND)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(| , BIN_OP_BIT_OR)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(^ , BIN_OP_BIT_EXOR)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(<<, BIN_OP_BIT_LSHIFT)
DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR(>>, BIN_OP_BIT_RSHIFT)
#undef DEFINE_OPERATOR_OVERLOADS_FOR_BINARY_OPERATOR

//
// Parser for Implication Constraints...
//
ConstraintBlockItem&
operator >>= (const CstrExprTree&           predicate_expr,
              const ConstraintBlockItem&    constraints);

const CstrExprTree&
operator >>= (const CstrExprTree&           predicate_expr,
              const CstrExprTree&           constraint);

} // end - namespace vcs_csolver_api

#endif
