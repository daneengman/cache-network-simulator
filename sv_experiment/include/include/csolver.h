/******************************************************************
 *   Copyright (c) 2014 by Synopsys Inc. - All Rights Reserved    *
 *                                                                *
 *   CONFIDENTIAL AND PROPRIETARY INFORMATION OF SYNOPSYS INC.    *
 ******************************************************************/
#ifndef __SYNOPSYS_VCS_CSOLVER_H__
#define __SYNOPSYS_VCS_CSOLVER_H__

#include <sys/types.h>
#include <iostream>

#include "csolver/vcs_csolver/vcs_csolver.hh"

namespace csolver {

//
// Support for basic CSOLVER keywords.
//
using   vcs_csolver_api::i_;
using   vcs_csolver_api::j_;
using   vcs_csolver_api::k_;
using   vcs_csolver_api::ref;
using   vcs_csolver_api::soft;
using   vcs_csolver_api::dist;
using   vcs_csolver_api::inside;
using   vcs_csolver_api::unique;
using   vcs_csolver_api::foreach;
using   vcs_csolver_api::dist_set;
using   vcs_csolver_api::uniq_set;
using   vcs_csolver_api::rand_var;
using   vcs_csolver_api::rand_vec;
using   vcs_csolver_api::value_set;
using   vcs_csolver_api::EachItemWtC;
using   vcs_csolver_api::WholeRangeWtC;
using   vcs_csolver_api::rand_obj_base;
using   vcs_csolver_api::set_global_seed;

//
// Implementation of rand_cls
//
#if __cplusplus >= 201103
//
// C++11
//
template<typename T>
class rand_cls : public T {
public:
    template<typename... Args>
    rand_cls(rand_obj_base* parent, Args... args) : T(parent, args...) {
        this->enable_randomization();
    }
};

#else
//
// C++98
//
template<typename T>
class rand_cls : public T {
public:
    rand_cls(rand_obj_base*     parent,
             const char*        objName     = NULL,
             const char*        fileName    = NULL,
             size_t             lineNum     = 0)
        : T(parent)
    {
        this->enable_randomization();
        if (objName) {
            this->setName(objName);
        }
        if (fileName && lineNum) {
            this->setSourceInfo(fileName, lineNum);
        }
    }
};

#endif


typedef vcs_csolver_api::ForeachLoopVar             loop_var;
typedef vcs_csolver_api::ConstrainedRandomGenerator generator;

} // end - namespace csolver

#endif
