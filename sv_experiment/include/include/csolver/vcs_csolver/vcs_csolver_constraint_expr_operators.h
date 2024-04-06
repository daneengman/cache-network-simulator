/******************************************************************
 *   Copyright (c) 2014 by Synopsys Inc. - All Rights Reserved    *
 *                                                                *
 *   CONFIDENTIAL AND PROPRIETARY INFORMATION OF SYNOPSYS INC.    *
 ******************************************************************/
#ifndef __VCS_CRAVE_CONSTRAINT_EXPR_OPERATORS_H__
#define __VCS_CRAVE_CONSTRAINT_EXPR_OPERATORS_H__

typedef enum {
    /**
    * If you make any change here, you might need to
    * change gp_rewrite_elem_t in gp_rewrite_int.h as
    * well. The order of these operators must be
    * exactly same in both places.
    */
    BIN_OP_NOT_BIN_OP = -1,

    /* Relational Operators */
    BIN_OP_REL_LT = 0,
    BIN_OP_REL_LEQ,
    BIN_OP_REL_GT,
    BIN_OP_REL_GEQ,

    /* IN Operators */
    BIN_OP_SET_IN,
    BIN_OP_SET_NOT_IN,

    /* Logical Operators */
    BIN_OP_LOG_AND,
    BIN_OP_LOG_OR,
    BIN_OP_LOG_EQEQ,
    BIN_OP_LOG_NEQ,

    /* Arithmetic Operators */
    BIN_OP_ARITH_PLUS,
    BIN_OP_ARITH_MINUS,
    BIN_OP_ARITH_MULT,
    BIN_OP_ARITH_DIV,
    BIN_OP_ARITH_MOD,

    /* Bitwise Operators */
    BIN_OP_BIT_AND,
    BIN_OP_BIT_NAND,
    BIN_OP_BIT_OR,
    BIN_OP_BIT_NOR,
    BIN_OP_BIT_EXOR,
    BIN_OP_BIT_EXNOR,
    BIN_OP_BIT_LSHIFT,
    BIN_OP_BIT_RSHIFT,

    /* Implies Operator */
    BIN_OP_GEN_IMPLIES
} CstrExprTreeBinaryOpType;

typedef enum {
    /**
    * If you make any change here, you might need to
    * change gp_rewrite_elem_t in gp_rewrite_int.h as
    * well. The order of these operators must be
    * exactly same in both places.
    */
    UN_OP_NOT_UN_OP = -1,

    /* Bitwise Operators */
    UN_OP_BIT_RED_AND =0,
    UN_OP_BIT_RED_NAND,
    UN_OP_BIT_RED_OR,
    UN_OP_BIT_RED_NOR,
    UN_OP_BIT_RED_EXOR,
    UN_OP_BIT_RED_EXNOR,
    UN_OP_BIT_NEG,

    /* Logical Operators */
    UN_OP_LOG_NEG,

    /* Arithmetic Operators */
    UN_OP_ARITH_MINUS,

    /* Sign Cast and Precision operators */
    UN_OP_CAST_TO_UNSIGNED,
    UN_OP_CAST_TO_SIGNED,
    UN_OP_CHANGE_PRECISION,

    /* Disable soft operator */
    UN_OP_DISABLE_SOFT
} CstrExprTreeUnaryOpType;

#endif
