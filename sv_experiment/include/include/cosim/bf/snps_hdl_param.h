#ifndef _snps_hdl_param_h_
#define _snps_hdl_param_h_

#include "systemc_user.h"
#include "systemc.h"
#include "bf_user.h"

#define HDL_INST(p) p(#p)
#define HDL_PARAM(p, v) p(#p, v)

void BF_overrule_parameter(const std::string &);
void BF_set_parameter(const std::string &);
void BF_set_parameter(const std::string &, int&);
void BF_set_parameter(const std::string &, double&);
void BF_set_parameter(const std::string &, std::string&);
void BF_set_parameter(const std::string &, int &, const int);
void BF_set_parameter(const std::string &, double &, const double);
void BF_set_parameter(const std::string &, std::string &, const std::string &);
void BF_set_parameter(const std::string &, int &, const int, const int);
void BF_set_parameter(const std::string &, double &, const double, const double);
void BF_set_parameter(const std::string &, std::string &, const std::string &,
                      const std::string &);
bool BF_in_patchmode();
void BF_check_get_parameter_status(const std::string &);

extern "C" bool isElabMode();

namespace sc_snps {

template < class T >
class hdl_param : public sc_core::sc_object
{
public:
    enum hdl_param_mode { hdl_param_init,
                          hdl_param_default,
                          hdl_param_set };

    hdl_param(const char *name_, const T &init_val);

    const T &get()
    {
        BF_check_get_parameter_status(name());
        m_mode = hdl_param_set;
        return _get();
    }

    void operator()(const T &val)
    {
#if 0
        // value is set explicitly in constructor, cannot be overruled by
        // instantiation.
        if (m_mode == hdl_param_init && !BF_in_patchmode())  {
            m_value = val;
            m_init_value = val;
        }
#endif
        if (m_mode == hdl_param_set)
            BF_overrule_parameter(name());
        else
            BF_set_parameter(name(), *&m_value, val, m_init_value);
    }
    const char *kind() const;
private:
    const T &_get() const { return m_value; }

private:
    T m_value;
    T m_init_value;
    hdl_param_mode m_mode;
};


template <>
inline const char *hdl_param<int>::kind() const { return "hdl_param_int"; }
template <>
inline const char *hdl_param<double>::kind() const { return "hdl_param_real"; }
template <>
inline const char *hdl_param<std::string>::kind() const { return "hdl_param_string"; }
template < class T >
inline const char *hdl_param<T>::kind() const { return "hdl_param_unsupported"; }

template <>
inline hdl_param<int>::hdl_param(const char *name_, const int &init_val)
    : sc_core::sc_object(name_), m_value(init_val), m_init_value(init_val), m_mode(hdl_param_init)
{
    BF_set_parameter(name_, *&m_value);
}

template <>
inline hdl_param<double>::hdl_param(const char *name_, const double &init_val)
    : sc_core::sc_object(name_), m_value(init_val), m_init_value(init_val), m_mode(hdl_param_init)
{
    BF_set_parameter(name_, *&m_value);
}

template <>
inline hdl_param<std::string>::hdl_param(const char *name_, const std::string &init_val)
    : sc_core::sc_object(name_), m_value(init_val), m_init_value(init_val), m_mode(hdl_param_init)
{
    BF_set_parameter(name_, *&m_value);
}

template < class T >
inline hdl_param<T>::hdl_param(const char *name_, const T &init_val)
    : sc_core::sc_object(name_), m_value(init_val), m_init_value(init_val), m_mode(hdl_param_init)
{
    BF_set_parameter(name_);
}


}; // namespace sc_snps

#endif
