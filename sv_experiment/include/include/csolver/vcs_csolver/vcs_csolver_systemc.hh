/******************************************************************
 *   Copyright (c) 2014 by Synopsys Inc. - All Rights Reserved    *
 *                                                                *
 *   CONFIDENTIAL AND PROPRIETARY INFORMATION OF SYNOPSYS INC.    *
 ******************************************************************/
#ifndef __SYNOPSYS_VCS_CSOLVER_SYSTEMC_HH__
#define __SYNOPSYS_VCS_CSOLVER_SYSTEMC_HH__

#include "systemc.h"
#include "vcs_csolver_var_handle.hh"

namespace vcs_csolver_api {

//
// Common base class SystemC VarHandle(s)
//
template<class T>
class VarHandleSysCBase : public VarHandleBase {
public:
    bool                    isBool() const { return false; }

    const char*             getTypeIdName() const { return typeid(T).name(); }

    const std::type_info&   getTypeId() const { return typeid(T); }

    bool                    isSupportedSystemCType() const { return true; }

protected:
    explicit                VarHandleSysCBase(const EnumTypeInfo* enumTypInfo);
};

template<class T>
VarHandleSysCBase<T>::VarHandleSysCBase(const EnumTypeInfo* eti)
        : VarHandleBase(eti) {
}


//
// VarHandle specialization for sc_dt::sc_int
//
template<int W>
class VarHandle<sc_dt::sc_int<W> >
        : public VarHandleSysCBase<sc_dt::sc_int<W> > {
public:
                            VarHandle(sc_dt::sc_int<W>*     var,
                                      const EnumTypeInfo*   enumTypInfo);

    VarHandleBase*          clone() const;

    bool                    isSigned() const;

    PrecisionType           getPrecision() const;

    void                    dumpValueToUintArray(unsigned int**) const;

    void                    readValueFromUintArray(const unsigned int*);

    unsigned int*           getValueInUintArray() const;

    void                    setValueFromUintArray(const unsigned int* val);

private:
    sc_dt::sc_int<W>*       var_;
};

template<int W>
VarHandle<sc_dt::sc_int<W> >::VarHandle(sc_dt::sc_int<W>*   var,
                                        const EnumTypeInfo* eti)
        : VarHandleSysCBase<sc_dt::sc_int<W> >(eti),
          var_(var) {
    VCS_CSOLVER_NULLCHECK(var);
}

template<int W>
PrecisionType
VarHandle<sc_dt::sc_int<W> >::getPrecision() const {
    return W;
}

template<int W>
bool
VarHandle<sc_dt::sc_int<W> >::isSigned() const {
    return true;
}

template<int W>
void
VarHandle<sc_dt::sc_int<W> >::dumpValueToUintArray(unsigned int** mem) const {
    VCS_CSOLVER_NULLCHECK(mem);
    VCS_CSOLVER_NULLCHECK(var_);
    binaryNumStrToUnsignedIntArray(var_->to_string(SC_BIN).c_str(), mem);
}

template<int W>
void
VarHandle<sc_dt::sc_int<W> >::readValueFromUintArray(const unsigned int* mem) {
    VCS_CSOLVER_NULLCHECK(mem);
    VCS_CSOLVER_NULLCHECK(var_);
    std::stringstream val_ss;
    char* val_str = unsignedIntArrayToNumStr(mem, var_->length());
    VCS_CSOLVER_NULLCHECK(val_str);
    val_ss << val_str;
    var_->scan(val_ss);
    freeWrapper(val_str);
}

template<int W>
VarHandleBase*
VarHandle<sc_dt::sc_int<W> >::clone() const {
    return new VarHandle<sc_dt::sc_int<W> >(var_, NULL);
}

template<int W>
unsigned int*
VarHandle<sc_dt::sc_int<W> >::getValueInUintArray() const {
    unsigned int numWords = (this->getPrecision() + 31) >> 5;
    unsigned int size = numWords * sizeof(int);
    unsigned int* value = (unsigned int*) vcs_csolver_api::allocStorageFromRace(size);
    VCS_CSOLVER_NULLCHECK(value);
    std::memset(value, 0, size);
    this->dumpValueToUintArray(&value);
    return value;
}

template<int W>
void
VarHandle<sc_dt::sc_int<W> >::setValueFromUintArray(const unsigned int* val) {
    VCS_CSOLVER_NULLCHECK(val);
    this->readValueFromUintArray(val);
}


//
// VarHandle specialization for sc_dt::sc_uint
//
template<int W>
class VarHandle<sc_dt::sc_uint<W> >
        : public VarHandleSysCBase<sc_dt::sc_uint<W> > {
public:
                            VarHandle(sc_dt::sc_uint<W>*    var,
                                      const EnumTypeInfo*   enumTypInfo);

    VarHandleBase*          clone() const;

    bool                    isSigned() const;

    PrecisionType           getPrecision() const;

    void                    dumpValueToUintArray(unsigned int**) const;

    void                    readValueFromUintArray(const unsigned int*);

    unsigned int*           getValueInUintArray() const;

    void                    setValueFromUintArray(const unsigned int* val);

private:
    sc_dt::sc_uint<W>*      var_;
};

template<int W>
VarHandle<sc_dt::sc_uint<W> >::VarHandle(sc_dt::sc_uint<W>*     var,
                                         const EnumTypeInfo*    eti)
        : VarHandleSysCBase<sc_dt::sc_uint<W> >(eti),
          var_(var) {
    VCS_CSOLVER_NULLCHECK(var);
}

template<int W>
PrecisionType
VarHandle<sc_dt::sc_uint<W> >::getPrecision() const {
    return W;
}

template<int W>
bool
VarHandle<sc_dt::sc_uint<W> >::isSigned() const {
    return false;
}

template<int W>
void
VarHandle<sc_dt::sc_uint<W> >::dumpValueToUintArray(unsigned int** mem) const {
    VCS_CSOLVER_NULLCHECK(mem);
    VCS_CSOLVER_NULLCHECK(var_);
    binaryNumStrToUnsignedIntArray(var_->to_string(SC_BIN).c_str(), mem);
}

template<int W>
void
VarHandle<sc_dt::sc_uint<W> >::readValueFromUintArray(const unsigned int* mem) {
    VCS_CSOLVER_NULLCHECK(mem);
    VCS_CSOLVER_NULLCHECK(var_);
    std::stringstream val_ss;
    char* val_str = unsignedIntArrayToNumStr(mem, var_->length());
    VCS_CSOLVER_NULLCHECK(val_str);
    val_ss << val_str;
    var_->scan(val_ss);
    freeWrapper(val_str);
}

template<int W>
VarHandleBase*
VarHandle<sc_dt::sc_uint<W> >::clone() const {
    return new VarHandle<sc_dt::sc_uint<W> >(var_, 0);
}

template<int W>
unsigned int*
VarHandle<sc_dt::sc_uint<W> >::getValueInUintArray() const {
    unsigned int numWords = (this->getPrecision() + 31) >> 5;
    unsigned int size = numWords * sizeof(int);
    unsigned int* value = (unsigned int*) vcs_csolver_api::allocStorageFromRace(size);
    VCS_CSOLVER_NULLCHECK(value);
    std::memset(value, 0, size);
    this->dumpValueToUintArray(&value);
    return value;
}

template<int W>
void
VarHandle<sc_dt::sc_uint<W> >::setValueFromUintArray(const unsigned int* val) {
    VCS_CSOLVER_NULLCHECK(val);
    this->readValueFromUintArray(val);
}


//
// VarHandle specialization for sc_dt::sc_bv
//
template<int W>
class VarHandle<sc_dt::sc_bv<W> >
        : public VarHandleSysCBase<sc_dt::sc_bv<W> > {
public:
                            VarHandle(sc_dt::sc_bv<W>*      var,
                                      const EnumTypeInfo*   enumTypInfo);

    VarHandleBase*          clone() const;

    bool                    isSigned() const;

    PrecisionType           getPrecision() const;

    void                    dumpValueToUintArray(unsigned int**) const;

    void                    readValueFromUintArray(const unsigned int*);

    unsigned int*           getValueInUintArray() const;

    void                    setValueFromUintArray(const unsigned int* val);

private:
    sc_dt::sc_bv<W>*        var_;
};

template<int W>
VarHandle<sc_dt::sc_bv<W> >::VarHandle(sc_dt::sc_bv<W>*     var,
                                       const EnumTypeInfo*  eti)
        : VarHandleSysCBase<sc_dt::sc_bv<W> >(eti),
          var_(var) {
    VCS_CSOLVER_NULLCHECK(var);
}

template<int W>
PrecisionType
VarHandle<sc_dt::sc_bv<W> >::getPrecision() const {
    return W;
}

template<int W>
bool
VarHandle<sc_dt::sc_bv<W> >::isSigned() const {
    return false;
}

template<int W>
void
VarHandle<sc_dt::sc_bv<W> >::dumpValueToUintArray(unsigned int** mem) const {
    VCS_CSOLVER_NULLCHECK(mem);
    VCS_CSOLVER_NULLCHECK(var_);
    binaryNumStrToUnsignedIntArray(var_->to_string(SC_BIN).c_str(), mem);
}

template<int W>
void
VarHandle<sc_dt::sc_bv<W> >::readValueFromUintArray(const unsigned int* mem) {
    VCS_CSOLVER_NULLCHECK(mem);
    VCS_CSOLVER_NULLCHECK(var_);
    std::stringstream val_ss;
    char* val_str = unsignedIntArrayToNumStr(mem, var_->length());
    VCS_CSOLVER_NULLCHECK(val_str);
    val_ss << val_str;
    var_->scan(val_ss);
    freeWrapper(val_str);
}

template<int W>
VarHandleBase*
VarHandle<sc_dt::sc_bv<W> >::clone() const {
    return new VarHandle<sc_dt::sc_bv<W> >(var_, 0);
}

template<int W>
unsigned int*
VarHandle<sc_dt::sc_bv<W> >::getValueInUintArray() const {
    unsigned int numWords = (this->getPrecision() + 31) >> 5;
    unsigned int size = numWords * sizeof(int);
    unsigned int* value = (unsigned int*) vcs_csolver_api::allocStorageFromRace(size);
    VCS_CSOLVER_NULLCHECK(value);
    std::memset(value, 0, size);
    this->dumpValueToUintArray(&value);
    return value;
}

template<int W>
void
VarHandle<sc_dt::sc_bv<W> >::setValueFromUintArray(const unsigned int* val) {
    VCS_CSOLVER_NULLCHECK(val);
    this->readValueFromUintArray(val);
}

//
// VarHandle specialization for sc_dt::sc_bigint
//
template<int W>
class VarHandle<sc_dt::sc_bigint<W> >
        : public VarHandleSysCBase<sc_dt::sc_bigint<W> > {
public:
                            VarHandle(sc_dt::sc_bigint<W>*  var,
                                      const EnumTypeInfo*   enumTypInfo);

    VarHandleBase*          clone() const;

    bool                    isSigned() const;

    PrecisionType           getPrecision() const;

    void                    dumpValueToUintArray(unsigned int**) const;

    void                    readValueFromUintArray(const unsigned int*);

    unsigned int*           getValueInUintArray() const;

    void                    setValueFromUintArray(const unsigned int* val);

private:
    sc_dt::sc_bigint<W>*    var_;
};

template<int W>
VarHandle<sc_dt::sc_bigint<W> >::VarHandle(sc_dt::sc_bigint<W>*     var,
                                           const EnumTypeInfo*      eti)
        : VarHandleSysCBase<sc_dt::sc_bigint<W> >(eti),
          var_(var) {
    VCS_CSOLVER_NULLCHECK(var);
}

template<int W>
PrecisionType
VarHandle<sc_dt::sc_bigint<W> >::getPrecision() const {
    return W;
}

template<int W>
bool
VarHandle<sc_dt::sc_bigint<W> >::isSigned() const {
    return true;
}

template<int W>
void
VarHandle<sc_dt::sc_bigint<W> >::dumpValueToUintArray(unsigned int** mem) const {
    VCS_CSOLVER_NULLCHECK(mem);
    VCS_CSOLVER_NULLCHECK(var_);
    binaryNumStrToUnsignedIntArray(var_->to_string(SC_BIN).c_str(), mem);
}

template<int W>
void
VarHandle<sc_dt::sc_bigint<W> >::readValueFromUintArray(const unsigned int* mem) {
    VCS_CSOLVER_NULLCHECK(mem);
    VCS_CSOLVER_NULLCHECK(var_);
    std::stringstream val_ss;
    char* val_str = unsignedIntArrayToNumStr(mem, var_->length());
    VCS_CSOLVER_NULLCHECK(val_str);
    val_ss << val_str;
    var_->scan(val_ss);
    freeWrapper(val_str);
}

template<int W>
VarHandleBase*
VarHandle<sc_dt::sc_bigint<W> >::clone() const {
    return new VarHandle<sc_dt::sc_bigint<W> >(var_, NULL);
}

template<int W>
unsigned int*
VarHandle<sc_dt::sc_bigint<W> >::getValueInUintArray() const {
    unsigned int numWords = (this->getPrecision() + 31) >> 5;
    unsigned int size = numWords * sizeof(int);
    unsigned int* value = (unsigned int*) vcs_csolver_api::allocStorageFromRace(size);
    VCS_CSOLVER_NULLCHECK(value);
    std::memset(value, 0, size);
    this->dumpValueToUintArray(&value);
    return value;
}

template<int W>
void
VarHandle<sc_dt::sc_bigint<W> >::setValueFromUintArray(const unsigned int* val) {
    VCS_CSOLVER_NULLCHECK(val);
    this->readValueFromUintArray(val);
}


//
// VarHandle specialization for sc_dt::sc_biguint
//
template<int W>
class VarHandle<sc_dt::sc_biguint<W> >
        : public VarHandleSysCBase<sc_dt::sc_biguint<W> > {
public:
                            VarHandle(sc_dt::sc_biguint<W>*     var,
                                      const EnumTypeInfo*       enumTypInfo);

    VarHandleBase*          clone() const;

    bool                    isSigned() const;

    PrecisionType           getPrecision() const;

    void                    dumpValueToUintArray(unsigned int**) const;

    void                    readValueFromUintArray(const unsigned int*);

    unsigned int*           getValueInUintArray() const;

    void                    setValueFromUintArray(const unsigned int* val);

private:
    sc_dt::sc_biguint<W>*   var_;
};

template<int W>
VarHandle<sc_dt::sc_biguint<W> >::VarHandle(sc_dt::sc_biguint<W>*   var,
                                            const EnumTypeInfo*     eti)
        : VarHandleSysCBase<sc_dt::sc_biguint<W> >(eti),
          var_(var) {
    VCS_CSOLVER_NULLCHECK(var);
}

template<int W>
PrecisionType
VarHandle<sc_dt::sc_biguint<W> >::getPrecision() const {
    return W;
}

template<int W>
bool
VarHandle<sc_dt::sc_biguint<W> >::isSigned() const {
    return false;
}

template<int W>
void
VarHandle<sc_dt::sc_biguint<W> >::dumpValueToUintArray(unsigned int** mem) const {
    VCS_CSOLVER_NULLCHECK(mem);
    VCS_CSOLVER_NULLCHECK(var_);
    binaryNumStrToUnsignedIntArray(var_->to_string(SC_BIN).c_str(), mem);
}

template<int W>
void
VarHandle<sc_dt::sc_biguint<W> >::readValueFromUintArray(const unsigned int* mem) {
    VCS_CSOLVER_NULLCHECK(mem);
    VCS_CSOLVER_NULLCHECK(var_);
    std::stringstream val_ss;
    char* val_str = unsignedIntArrayToNumStr(mem, var_->length());
    VCS_CSOLVER_NULLCHECK(val_str);
    val_ss << val_str;
    var_->scan(val_ss);
    freeWrapper(val_str);
}

template<int W>
VarHandleBase*
VarHandle<sc_dt::sc_biguint<W> >::clone() const {
    return new VarHandle<sc_dt::sc_biguint<W> >(var_, 0);
}

template<int W>
unsigned int*
VarHandle<sc_dt::sc_biguint<W> >::getValueInUintArray() const {
    unsigned int numWords = (this->getPrecision() + 31) >> 5;
    unsigned int size = numWords * sizeof(int);
    unsigned int* value = (unsigned int*) vcs_csolver_api::allocStorageFromRace(size);
    VCS_CSOLVER_NULLCHECK(value);
    std::memset(value, 0, size);
    this->dumpValueToUintArray(&value);
    return value;
}

template<int W>
void
VarHandle<sc_dt::sc_biguint<W> >::setValueFromUintArray(const unsigned int* val) {
    VCS_CSOLVER_NULLCHECK(val);
    this->readValueFromUintArray(val);
}

} // end - namespace vcs_csolver_api

#endif
