// Copyright (c) 2011 The CRAVE developers <crave@informatik.uni-bremen.de>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __SYNOPSYS_VCS_CRAVE_H__
#define __SYNOPSYS_VCS_CRAVE_H__ 

#include <sys/types.h>
#include <iostream>

#include "csolver/vcs_csolver/vcs_csolver.hh"

namespace crave {

#ifdef CRAVE_COMPATIBLE
using std::ostream;
#endif

//
// The API keywords...
//
using   vcs_csolver_api::_i;
using   vcs_csolver_api::_j;
using   vcs_csolver_api::_k;
using   vcs_csolver_api::ref;
using   vcs_csolver_api::soft;
using   vcs_csolver_api::dist;
using   vcs_csolver_api::randv;
using   vcs_csolver_api::rand_vec;
using   vcs_csolver_api::inside;
using   vcs_csolver_api::unique;
using   vcs_csolver_api::foreach;
using   vcs_csolver_api::dist_set;
using   vcs_csolver_api::uniq_set;
using   vcs_csolver_api::value_set;
using   vcs_csolver_api::EachItemWtC;
using   vcs_csolver_api::WholeRangeWtC;
using   vcs_csolver_api::set_global_seed;
using   vcs_csolver_api::SoftConstrainedRandomGenerator;

typedef vcs_csolver_api::RandObjForCrave            rand_obj;
typedef vcs_csolver_api::ForeachLoopVarForCrave     ForeachLoopVar;
typedef vcs_csolver_api::ConstrainedRandomGenerator DefaultGenerator;

//
// In CRAVE, Generator is a parameterized class, which takes an implementation
// specific type (Context) as its parameter.
//
// We don't need our implementation of Generator to be parameterized. However,
// for retaining backward compatibility with CRAVE, we will retain Generator as
// parameterized, which would take in a dummy param (DefaultContext) as arg.
//
struct DefaultContext {};
typedef DefaultContext Context;


//
// Support for CRAVE Generator for backward compatibility.
//
template<class T = DefaultContext>
class Generator : public vcs_csolver_api::ConstrainedRandomGenerator {
public:
                Generator();

    explicit    Generator(vcs_csolver_api::ConstraintBlockItem& constraint);
};

template<class T>
Generator<T>::Generator()
    : vcs_csolver_api::ConstrainedRandomGenerator()
{

}

template<class T>
Generator<T>::Generator(vcs_csolver_api::ConstraintBlockItem& constraint)
    : vcs_csolver_api::ConstrainedRandomGenerator(constraint)
{

}


//
// Support for CRAVE Soft_Generator for backward compatibility.
//
template<class T = DefaultContext>
struct Soft_Generator : public SoftConstrainedRandomGenerator {
    explicit        Soft_Generator(Generator<T>& gen);
};

template<class T>
Soft_Generator<T>::Soft_Generator(Generator<T>& gen)
        : SoftConstrainedRandomGenerator(gen) {
}

//
// Support for CRAVE reference(...)
//
template<class T>
inline const vcs_csolver_api::CstrExprTree&
reference(T& r)
{
    return ref(r);
}

template<class T>
inline const vcs_csolver_api::CstrExprTree&
reference(randv<T>& r)
{
    return ref(r);
}

template<class T>
inline const vcs_csolver_api::CstrExprTree&
reference(const T& val)
{
    return ref(val);
}

} // end - namespace crave


/**
* Used for specifying source info during construction.
*/
#define CRAVE_SRCINFO(__var__) #__var__, __FILE__, __LINE__

#endif
