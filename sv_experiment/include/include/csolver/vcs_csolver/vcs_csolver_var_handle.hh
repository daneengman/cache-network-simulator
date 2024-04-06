/******************************************************************
 *   Copyright (c) 2014 by Synopsys Inc. - All Rights Reserved    *
 *                                                                *
 *   CONFIDENTIAL AND PROPRIETARY INFORMATION OF SYNOPSYS INC.    *
 ******************************************************************/
#ifndef __SYNOPSYS_VCS_CSOLVER_VAR_HANDLE_HH__
#define __SYNOPSYS_VCS_CSOLVER_VAR_HANDLE_HH__

#include <typeinfo>
#if __cplusplus >= 201103
#include <type_traits>
#endif
#include "vcs_csolver_decls.hh"

namespace vcs_csolver_api {


template<class T>
struct is_sizeof_T_LessThan_sizeof_int {
    static const bool result = (sizeof(T) < sizeof(int));
};

template<class T, bool isSizeOfTLessThanInt>
class VarHandleAssignHelper {
public:
    static void                     assignValToUintArr(
                                        unsigned int*       uintArr,
                                        const T*            src
                                    );

    static void                     assignValFrmUintArr(
                                        T*                  dst,
                                        const unsigned int* uintArr
                                    );
};

template<class T, bool isSizeOfTLessThanInt>
void
VarHandleAssignHelper<T,isSizeOfTLessThanInt>::assignValToUintArr(
        unsigned int*    uintArr,
        const T*         src
) {
    //
    // Adding static_cast due to clang build failure - ambigious call
    //
    VCS_CSOLVER_ASSERT(static_cast<bool>(false), "Should not be called");
}

template<class T, bool isSizeOfTLessThanInt>
void
VarHandleAssignHelper<T,isSizeOfTLessThanInt>::assignValFrmUintArr(
        T*                      dst,
        const unsigned int*     uintArr
) {
    //
    // Adding static_cast due to clang build failure - ambigious call
    //
    VCS_CSOLVER_ASSERT(static_cast<bool>(false), "Should not be called");
}


template<class T>
class VarHandleAssignHelper<T,true> {
public:
    static void                     assignValToUintArr(
                                        unsigned int*       uintArr,
                                        const T*            src
                                    );

    static void                     assignValFrmUintArr(
                                        T*                  dst,
                                        const unsigned int* uintArr
                                    );
};

template<class T>
void
VarHandleAssignHelper<T,true>::assignValToUintArr(
        unsigned int*           uintArr,
        const T*                src
) {
    *uintArr = *src;
}

template<class T>
void
VarHandleAssignHelper<T,true>::assignValFrmUintArr(
        T*                      dst,
        const unsigned int*     uintArr
) {
    *dst = (T) *uintArr;
}



template<class T>
class VarHandleAssignHelper<T,false> {
public:
    static void                     assignValToUintArr(
                                        unsigned int*       uintArr,
                                        const T*            src
                                    );

    static void                     assignValFrmUintArr(
                                        T*                  dst,
                                        const unsigned int* uintArr
                                    );
};

template<class T>
void
VarHandleAssignHelper<T,false>::assignValToUintArr(
        unsigned int*           uintArr,
        const T*                src
) {
    if (isBigEndianMachine()) {
        copyBigToLittleEndian(*src, uintArr);
    }
    else {
        *((T*) uintArr) = *src;
    }
}

template<class T>
void
VarHandleAssignHelper<T,false>::assignValFrmUintArr(
        T*                      dst,
        const unsigned int*     uintArr
) {
    if (isBigEndianMachine()) {
        copyLittleToBigEndian(uintArr, *dst);
    }
    else {
        *dst = *((T*) uintArr);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation of VarHandle
//
///////////////////////////////////////////////////////////////////////////////
class VarHandleBase {
public:
    virtual                         ~VarHandleBase();

    virtual VarHandleBase*          clone() const = 0;

    virtual bool                    isBool() const = 0;

    virtual const char*             getTypeIdName() const = 0;

    virtual const std::type_info&   getTypeId() const = 0;

    virtual unsigned int*           getValueInUintArray() const = 0;

    virtual void                    setValueFromUintArray(const unsigned int* val) = 0;

    const EnumTypeInfo*             getEnumTypeInfo() const;

    virtual bool                    isBuiltInIntegralOrEnumType() const; 

    virtual bool                    isUnionType() const;

    virtual bool                    isSigned() const;

    virtual size_t                  getSizeOf() const;

    virtual PrecisionType           getPrecision() const;

    virtual bool                    isBuiltInIntegralType() const; 

    virtual bool                    isSignedBuiltInIntegralType() const;

    virtual bool                    isSupportedSystemCType() const;

    virtual void                    dumpValueToUintArray(unsigned int**) const;

    virtual void                    readValueFromUintArray(const unsigned int*);

    void*                           operator new(size_t sz);

    void                            operator delete(void* ptr);

protected:
    explicit                        VarHandleBase(const EnumTypeInfo*);

private:
    typedef vcs_csolver_impl::VarHandleBaseImpl Impl_;

                                    VarHandleBase(const VarHandleBase&);

    VarHandleBase&                  operator=(const VarHandleBase&);

    Impl_* const                    impl_;
};

template<class T>
class VarHandle : public VarHandleBase {
public:
                            VarHandle(T*                    var,
                                      const EnumTypeInfo*   enumTypInfo);

    VarHandleBase*          clone() const;

    bool                    isBool() const;

    bool                    isUnionType() const;

    const char*             getTypeIdName() const;

    const std::type_info&   getTypeId() const;

    size_t                  getSizeOf() const;

    bool                    isBuiltInIntegralType() const; 

    bool                    isSignedBuiltInIntegralType() const; 

    unsigned int*           getValueInUintArray() const;

    void                    setValueFromUintArray(const unsigned int* val);

private:
    T*                      var_;
};

template<class T>
VarHandle<T>::VarHandle(T*                      var,
                        const EnumTypeInfo*     enumTypInfo)
        : VarHandleBase(enumTypInfo),
          var_(var) {
}

template<class T>
VarHandleBase*
VarHandle<T>::clone() const {
    return new VarHandle<T>(var_, this->getEnumTypeInfo());
}

template<class T>
bool
VarHandle<T>::isBool() const {
    return (typeid(T) == typeid(bool));
}

template<class T>
bool
VarHandle<T>::isUnionType() const {
#if __cplusplus >= 201103
    return std::is_union<T>::value;
#else
    //
    // NYI - for now.
    //
    return false;
#endif
}

template<class T>
const char*
VarHandle<T>::getTypeIdName() const {
    return typeid(T).name();
}

template<class T>
const std::type_info&
VarHandle<T>::getTypeId() const {
    return typeid(T);
}

template<class T>
size_t
VarHandle<T>::getSizeOf() const {
    return sizeof(T);
}

template<class T>
bool
VarHandle<T>::isBuiltInIntegralType() const {
    return std::numeric_limits<T>::is_integer;
}

template<class T>
bool
VarHandle<T>::isSignedBuiltInIntegralType() const {
    return std::numeric_limits<T>::is_signed;
}

//
// Endian friendly copy of data from unit array to var. In uint array, data
// is assumed to be in little endian format.
//
template<class T>
void
VarHandle<T>::setValueFromUintArray(const unsigned int* val) {
    VCS_CSOLVER_NULLCHECK(var_);
    VCS_CSOLVER_NULLCHECK(val);

    VCS_CSOLVER_ASSERT(this->isBuiltInIntegralOrEnumType(), "");

    VarHandleAssignHelper<
        T,
        is_sizeof_T_LessThan_sizeof_int<T>::result
    >::assignValFrmUintArr(var_, val);
}

//
// Endian friendly copy of data from var to unit array. In uint array, data
// is kept in little endian format.
//
// Allocates and returns storage for uint array using allocStorageFromRace
//
template<class T>
unsigned int*
VarHandle<T>::getValueInUintArray() const {
    VCS_CSOLVER_NULLCHECK(var_);
    unsigned int numWords = (this->getPrecision() + 31) >> 5;
    unsigned int size = numWords * sizeof(int);
    unsigned int* value = (unsigned int*) vcs_csolver_api::allocStorageFromRace(size);
    VCS_CSOLVER_NULLCHECK(value);
    std::memset(value, 0, size);

    VCS_CSOLVER_ASSERT(this->isBuiltInIntegralOrEnumType(), "");

    VarHandleAssignHelper<
        T,
        is_sizeof_T_LessThan_sizeof_int<T>::result
    >::assignValToUintArr(value, var_);
    return value;
}


} // end - namespace vcs_csolver_api

#endif

