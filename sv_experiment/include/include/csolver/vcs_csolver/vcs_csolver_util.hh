/******************************************************************
 *   Copyright (c) 2014 by Synopsys Inc. - All Rights Reserved    *
 *                                                                *
 *   CONFIDENTIAL AND PROPRIETARY INFORMATION OF SYNOPSYS INC.    *
 ******************************************************************/
#ifndef __SYNOPSYS_VCS_CSOLVER_UTIL_HH__
#define __SYNOPSYS_VCS_CSOLVER_UTIL_HH__
#include <limits>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <stdexcept>

#include "vcs_csolver_data_type.hh"
#include "vcs_csolver_var_handle.hh"

namespace vcs_csolver_api {

//////////////////////////////////////////////////////////////////////////////
//
// A simple singly-circular list item.
//
//////////////////////////////////////////////////////////////////////////////
template<class T> class CircularSList;
template<class T> class CircularSListIterator;

template<class T>
class CircularSListItem {
public:
    T*                          getNext() const;

    void                        setNext(T* n);

protected:
                                CircularSListItem();

private:
    friend class                CircularSList<T>;
    friend class                CircularSListIterator<T>;

    T*                          next_;
};

template<class T>
CircularSListItem<T>::CircularSListItem()
    : next_(static_cast<T*>(this)) {
}

template<class T>
T*
CircularSListItem<T>::getNext() const {
    return next_;
}

template<class T>
void
CircularSListItem<T>::setNext(T* n) {
    //
    // In circular list, next_ should never be NULL, else the circle will be
    // broken.
    //
    VCS_CSOLVER_NULLCHECK(n);
    next_ = n;
}

///////////////////////////////////////////////////////////////////////////////
//
// Implementation of CircularSList
//
///////////////////////////////////////////////////////////////////////////////
template<class T>
class CircularSList {
public:
                                CircularSList();

    explicit                    CircularSList(T* lastNode);

    void                        insert(T*);

    void                        append(T*);

    T*                          detachFirst();

    unsigned int                size() const;

    bool                        empty() const;

    CircularSListIterator<T>    getIterator();

private:
    friend class CircularSListIterator<T>;

    T*                          last_;    
    unsigned int                size_;
};

template<class T>
CircularSList<T>::CircularSList()
    : last_(0),
      size_(0) {
}

template<class T>
CircularSList<T>::CircularSList(T* lastNode)
    : last_(lastNode),
      size_(0) {
    VCS_CSOLVER_NULLCHECK(lastNode);

    CircularSListIterator<T> it(*this);
    while ((it++)) {
        ++size_;
    }
}

template<class T>
void
CircularSList<T>::insert(T* item) {
    VCS_CSOLVER_NULLCHECK(item);
    if (last_) {
        item->next_ = last_->next_;
        last_->next_ = item; 
    }
    else {
        last_ = item;
    }

    ++size_;
}

template<class T>
void
CircularSList<T>::append(T* item) {
    VCS_CSOLVER_NULLCHECK(item);
    if (last_) {
        item->next_ = last_->next_;
        last_->next_ = item;
        last_ = item; 
    }
    else {
        last_ = item;
    }

    ++size_;
}

template<class T>
T*
CircularSList<T>::detachFirst() {
    if (last_) {
        T* ret = last_->next_;
        VCS_CSOLVER_NULLCHECK(ret);
        if (ret == last_) {
            last_ = NULL;
        }
        else {
            last_->next_ = ret->next_;
            ret->next_ = ret;
        }

        --size_;
        return ret;
    }
    else {
        return NULL;
    }
}

template<class T>
bool
CircularSList<T>::empty() const {
    if (last_) {
        return false;
    }
    else {
        return true;
    }
}

template<class T>
unsigned int
CircularSList<T>::size() const {
    return size_;
}

template<class T>
CircularSListIterator<T>
CircularSList<T>::getIterator() {
    return CircularSListIterator<T>(*this);
}

///////////////////////////////////////////////////////////////////////////////
//
// Implementation of CircularSListIterator
//
///////////////////////////////////////////////////////////////////////////////
template<class T>
class CircularSListIterator {
public:
                                CircularSListIterator();

    explicit                    CircularSListIterator(const CircularSList<T>&);

    T*                          operator()() const;

    T*                          operator++(int);

    CircularSListIterator&      operator=(const CircularSListIterator&);

private:
    const CircularSList<T>*     list_;
    T*                          cur_it_node_;
};

template<class T>
CircularSListIterator<T>::CircularSListIterator()
    : list_(0),
      cur_it_node_(0) {
}

template<class T>
CircularSListIterator<T>::CircularSListIterator(
    const CircularSList<T>& list
)
    : list_(&list),
      cur_it_node_(list_->last_ ? list_->last_->next_ : 0) {
}

template<class T>
CircularSListIterator<T>&
CircularSListIterator<T>::operator=(const CircularSListIterator& o) {
    list_ = o.list_;
    if (o.list_) {
        cur_it_node_ = list_->last_ ? list_->last_->next_ : 0;
    }
    else {
        cur_it_node_ = 0;    
    }
    return *this;
}

template<class T>
T*
CircularSListIterator<T>::operator()() const {
    VCS_CSOLVER_ASSERT(list_, "List must have been initialized");
    return cur_it_node_;
}

template<class T>
T*
CircularSListIterator<T>::operator++(int) {
    VCS_CSOLVER_ASSERT(list_ && list_->last_, "List must have been initialized");

    T* ret = cur_it_node_;
    if (list_->last_ == cur_it_node_) {
        cur_it_node_ = NULL;
    }
    else if (cur_it_node_) {
        cur_it_node_ = cur_it_node_->next_; 
    }
    return ret;
}


///////////////////////////////////////////////////////////////////////////////
//
// std::stringstream doesn't convert signed/unsigned char to integral string, so
// re-factoring this routine for specially dealing with 'char' family.
//
///////////////////////////////////////////////////////////////////////////////
template<class T>
char*
integralToStr(T val) {
    std::stringstream ss;
    ss << val;
    return strdupWrapper(ss.str().c_str());
}

#define DECLARE_integralToStr_FOR(_TYPE_)                                       \
    template<>                                                                  \
    char*                                                                       \
    integralToStr<_TYPE_>(_TYPE_ val);

DECLARE_integralToStr_FOR(char);
DECLARE_integralToStr_FOR(signed char);
DECLARE_integralToStr_FOR(unsigned char);
#undef DECLARE_integralToStr_FOR


///////////////////////////////////////////////////////////////////////////////
//
// Implementation of endian friendly data readers/writers.
//
///////////////////////////////////////////////////////////////////////////////
template<class T>
void
copyLittleToBigEndian(const unsigned int*   src,
                      T&                    dst)
{
    VCS_CSOLVER_NULLCHECK(src);
    VCS_CSOLVER_ASSERT(src != (const unsigned int*) &dst, "");

    unsigned numWords = (((sizeof(T) - 1) / sizeof(int)) + 1);
    unsigned int* d = ((unsigned int*) &dst) + numWords - 1;

    for (unsigned i = 0; i < numWords; ++i) {
        *d-- = *src++;
    }
}

template<class T>
void
copyBigToLittleEndian(const T&              src,
                      unsigned int*         dst)
{
    VCS_CSOLVER_NULLCHECK(dst);
    VCS_CSOLVER_ASSERT((unsigned int*) &src != dst, "");

    unsigned numWords = (((sizeof(T) - 1) / sizeof(int)) + 1);
    unsigned int* s = ((unsigned int*) &src) + numWords - 1;

    for (unsigned i = 0; i < numWords; ++i) {
        *dst++ = *s--;
    }
}

template<class T>
CstrDataType*
getValueInCstrDataType(const T&             val,
                       const EnumTypeInfo*  enumTypInfo)
{
    const VarHandle<T> var_handle(const_cast<T*>(&val), enumTypInfo);
    return raceCreateAndSetDataTypeWrapper(var_handle.getPrecision(),
                                           var_handle.isSigned(),
                                           var_handle.getValueInUintArray());
}

template<class T>
T
getValueFromCstrDataType(const CstrDataType*  val,
                         const EnumTypeInfo*  enumTypInfo) {
    VCS_CSOLVER_NULLCHECK(val);

    const unsigned int* valInUIntArr = cstrDataTypeGetValueInUintArray(val);
    VCS_CSOLVER_NULLCHECK(valInUIntArr);

    T var;
    VarHandle<T> var_handle(&var, enumTypInfo);
    var_handle.setValueFromUintArray(valInUIntArr);
    return var;
}


//
// Creates/Allocates a CstrExprTree node for an integral constant.
//
template<class T>
CstrExprTree*
createCstrExprTreeConstantNode(const T& val) {
    EnumTypeInfoHelper<T> enumInfo;
    const VarHandle<T> var_handle(const_cast<T*>(&val),
                                  enumInfo.getEnumTypeInfo());
    if (!var_handle.isBuiltInIntegralOrEnumType() &&
        !var_handle.isSupportedSystemCType()) {
        vcsCsolverMsgReportNoSource("CPPSOLVER-UOUSCF");
        exitFromCSOLVER(1);
    }

    char* intStr = integralToStr<T>(val); 
    VCS_CSOLVER_NULLCHECK(intStr);
    CstrExprTree* constExpr = createCstrExprTreeConstantNode(
                                intStr,
                                var_handle.getPrecision(),
                                var_handle.isSigned(),
                                true
                              );
    VCS_CSOLVER_NULLCHECK(constExpr);
    freeWrapper(intStr);
    return constExpr;
}

} // End - namespace vcs_csolver_api

#endif
