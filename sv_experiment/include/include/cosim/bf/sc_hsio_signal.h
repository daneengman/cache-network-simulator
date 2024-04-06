// ------------------------------------------------------------------
// SYNOPSYS CONFIDENTIAL
//
// This is an unpublished, proprietary work of Synopsys, Inc., and
// is fully protected under copyright and trade secret laws. You may
// not view, use, disclose, copy, or distribute this file or any
// information contained herein except pursuant to a valid written
// license from Synopsys.
// ------------------------------------------------------------------

#ifndef _sc_hsio_signal_h_
#define _sc_hsio_signal_h_

#if !defined _VC_TYPES_ && !defined TYPEDEFRT_H && !defined vec32
typedef struct { unsigned int c; unsigned int d;} vec32;
#endif

#define MHDL_INTEGER           0
#define MHDL_REAL              1
#define MHDL_TIME              2
#define MHDL_LOGIC_SCALAR      3
#define MHDL_LOGIC_VECTOR      4
#define MHDL_LOGIC_WIDEVECTOR  5
#define MHDL_STRENGTH_SCALAR   6
#define MHDL_STRENGTH_VECTOR   7
#define MHDL_STRING            8         /* needed for parameter */

#define MHDL_2STATE_SCALAR     18
#define MHDL_2STATE_VECTOR     19
#define MHDL_2STATE_WIDEVECTOR 20
#define MHDL_RECORD_SCALAR      21
#define MHDL_RECORD_VECTOR      22
#define MHDL_REAL_VECTOR        23
#define MHDL_PHYSICAL           24

#ifdef SYSC_DEBUG
extern "C" void bf_debug_info_opt_if(const char *, const char *, int, int);
#endif

void BfAssert(const char *);
void BfAssert2(int, const char *);
void BfCollect(int, const char *, int, const char *);

#ifdef SYSC_DEBUG
#define M_BfCollect(a, b, c, d) BfCollect(a, b, c, d)
#else
#define M_BfCollect(a, b, c, d)
#endif

#include "sc_hs2v_signal.h"
#include "sc_hs2c_signal.h"
#include "vcs_cbug_object_info.h"


/*********************************************************
 *  Four V bits are packed into an int.
 *  Ordering is reversed.
 *  u[0] holds the uppermost four bits; u[(len-1)/4] holds the lowest bits(s)
 *  and may not be completely filled. Examples for len=17
 *
 * i=0 index=13 u[0] bits 24..31 within int
 * i=1 index=14 u[0]
 * i=2 index=15 u[0]
 * i=3 index=16 u[0] bits 0..7 within int
 * i=4 index=9 u[1] bits 24..31 within int
 * i=5 index=10 u[1]
 * i=6 index=11 u[1]
 * i=7 index=12 u[1]
 * i=8 index=5 u[2]
 * i=9 index=6 u[2]
 * i=10 index=7 u[2]
 * i=11 index=8 u[2]
 * i=12 index=1 u[3]
 * i=13 index=2 u[3]
 * i=14 index=3 u[3]
 * i=15 index=4 u[3]
 * i=16 index=0 u[4]
 ************************************************************/
template < int W >
inline void TypeConvert_sc_to_v_exp(unsigned int *u, int len, const sc_lv<W> &val) {
    std::string std_value = val.to_string();
    int index = len +3;
    for (int i = 0; i < len; ++i) {
        u[i/4] <<= 8;
        if ((i % 4) == 0) { index -= 8; u[(i)/4] = 0; }
        if (index < 0) index = 0; else index++;
        switch(std_value[index]) {
        case '0': u[(i)/4] += 0; break;
        case '1': u[(i)/4] += 1; break;
        case 'Z': u[(i)/4] += 2; break;
        case 'X':
        default:  u[(i)/4] += 3; break;
        }
    }
#if defined(sparc)
    for (int i = 0, j = 0; i <= len; i += 4, ++j) {
        unsigned int tmp;
        tmp = u[j];
        u[j] =
            ((tmp & 0xff000000) >> 24) +
            ((tmp & 0xff0000) >> 8) +
            ((tmp & 0xff00) << 8) +
            ((tmp & 0xff) << 24);
    }
#endif
}

inline void TypeConvert_sc_to_v_strexp(unsigned int *u, int len, const char *val) {
    std::string std_value = val;
    int index = len +3;
    for (int i = 0; i < len; ++i) {
        u[i/4] <<= 8;
        if ((i % 4) == 0) { index -= 8; u[(i)/4] = 0; }
        if (index < 0) index = 0; else index++;
        switch(std_value[index]) {
        case '0': u[(i)/4] += 0; break;
        case '1': u[(i)/4] += 1; break;
        case 'Z': u[(i)/4] += 2; break;
        case 'X':
        default:  u[(i)/4] += 3; break;
        }
    }
#if defined(sparc)
    for (int i = 0, j = 0; i <= len; i += 4, ++j) {
        unsigned int tmp;
        tmp = u[j];
        u[j] =
            ((tmp & 0xff000000) >> 24) +
            ((tmp & 0xff0000) >> 8) +
            ((tmp & 0xff00) << 8) +
            ((tmp & 0xff) << 24);
    }
#endif
}

template <int W >
inline void TypeConvert_v_exp_to_sc(sc_lv<W> &value, int w, unsigned int *u) {
    unsigned int val;
    int wcnt = 0;
    for (int i = 0; i < w; ++i) {
        if ((i % 4) == 0) {
#if defined(sparc)
            val =
                ((u[wcnt] & 0xff000000) >> 24) +
                ((u[wcnt] & 0xff0000) >> 8) +
                ((u[wcnt] & 0xff00) << 8) +
                ((u[wcnt] & 0xff) << 24);
            ++wcnt;
#else
            val = u[wcnt++];
#endif
        }
        unsigned int nibble = val & 0x03;

        val >>= 8;
        switch(nibble) {
        case 0: value.set_bit(i, sc_dt::Log_0); break;
        case 1: value.set_bit(i, sc_dt::Log_1); break;
        case 2: value.set_bit(i, sc_dt::Log_Z); break;
        case 3:
        default: value.set_bit(i, sc_dt::Log_X); break;
        }
    }
}

template <int W >
inline void TypeConvert_v_vec_to_sc(sc_lv<W> &value, int w, unsigned int *u) {
    unsigned int dval;
    unsigned int cval;
    int wcnt = 0;
    for (int i = 0; i < w; ++i) {
        if ((i % 32) == 0) { dval = u[wcnt++]; cval = u[wcnt++]; }
        if ((cval & 0x01) == 0) {
            if ((dval & 0x01) == 0) {
                value.set_bit(i, sc_dt::Log_0);
            } else {
                value.set_bit(i, sc_dt::Log_Z);
            }
        } else {
            if ((dval & 0x01) == 0) {
                value.set_bit(i, sc_dt::Log_1);
            } else {
                value.set_bit(i, sc_dt::Log_X);
            }
        }
        cval >>= 1;
        dval >>= 1;
    }
}

template < int W >
inline void TypeConvert_sc_to_v_int(unsigned int *u, int len, const sc_lv<W> &val) {
    assert(0);
}

template < int W >
inline void TypeConvert_sc_to_v_ls(unsigned int *u, int len, const sc_lv<W> &val) {
    assert(0);
}

inline void TypeConvert_sc_to_v_str_c(vec32 *&t, int, const char v) {
    size_t ti = 0;
    switch(v) {
    case '0': ti = 0; break;
    case '1': ti = 1; break;
    case 'Z': ti = 2; break;
    case 'X':
    default:
        ti = 3; break;
    }
    t = (vec32 *)(ti);
}

inline void TypeConvert_sc_to_v_scalar(vec32 *&t, int, const char v) {
    size_t ti = 0;
    switch (toupper(v)) {
    case '0': ti = 0; break;
    case '1': ti = 1; break;
    case 'Z': ti = 2; break;
    case 'X':
    default:
        ti = 3; break;
    }
    t = (vec32 *)(ti);
}

inline void TypeConvert_sc_to_v_str(vec32 *&t, int w, const char *vec) {
    unsigned int mask = 1;
    int word = -1;
    for (int i = 0; i < w; ++i) {
        if ((i % 32) == 0) {
            word++;
            mask = 1;
            t[word].c = 0;
            t[word].d = 0;
        }
        switch (vec[w - i - 1]) {
        case '0': break;
        case '1': t[word].d |= mask; break;
        case 'Z': t[word].c |= mask; break;
        case 'X':
        default:  t[word].c |= mask; t[word].d |= mask; break;
        }
        mask <<= 1;
    }
}

class sc_hsio_signal_base
{
public:
    virtual ~sc_hsio_signal_base() {}
    virtual void attachDriver(void *, int (*)(void *, vec32 *, int), int, int, int) = 0;
    virtual void attachLoad(void *, int, int) = 0;
    virtual void writeHS(unsigned int *val, void *) = 0;
    virtual void write2V(const char) = 0;
    virtual void write2V(const char *) = 0;
    virtual void write2V_Z() = 0;
    virtual bool dir2SC(void) = 0;
    virtual int getType() const = 0;
    virtual void setName(const char *n) { m_name = n; }
    virtual const char *getName() { return m_name.c_str(); }
    virtual void request_update() {}
    void setCrd(int c) { m_crd = c; }
    virtual void virtualFunc() = 0;
private:
    std::string m_name;
protected:
    int m_crd;
};

namespace sc_snps {
extern void HSIO_resolve(sc_hsio_signal_base *, const char *);
}

class sc_hsio_signal_resolved : public sc_signal_resolved, public sc_hsio_signal_base
{
public:
    sc_hsio_signal_resolved() : m_rtn(0), m_nState(-1), m_done(false) {
        this->m_crd = 0;
        sc_snps::vcs_cbug_attach_object_info_for_signal(this);
    }
    ~sc_hsio_signal_resolved() { delete m_t; }

    void end_of_elaboration() {
#ifdef SYSC_INIT_INOUT_WITH_Z
        virtualFunc();
#endif
    }
    
    int getType() const { return 1; }
    void virtualFunc() {
        if (this->m_new_val == sc_dt::Log_X) {
            sc_signal_resolved::write(sc_dt::Log_Z);
        }
    }

    void setW(int w, int words, std::string id) {
        m_id = id;
        m_t = new vec32;
        m_dir2V = false;
        m_out = 0;
        m_resolve = true;
        m_w = w;
        m_u = new unsigned int;
    }

    void attachDriver(void *writeNode, int (*fun)(void *, vec32 *, int), int nState, int w, int instNum) {
        m_writeNode = writeNode;
        m_rtn = fun;
        m_nState = nState;
        m_done = true;
        m_vcs_rtn.push_back(fun);
        m_vcs_writeNode.push_back(writeNode);
        m_instNum = instNum;

#ifdef SYSC_DEBUG
        bf_debug_info_opt_if(m_id.c_str(), this->name(), m_nState, m_w);
#endif
    }

    void attachLoad(void *writeNode, int nState, int w) {
        m_nState = nState;
#ifdef SYSC_DEBUG
        bf_debug_info_opt_if(m_id.c_str(), this->name(), m_nState, w);
#endif
    }

    void setOut(sc_inout_resolved *out) {
        m_out = out;
    }

    bool dir2SC(void) {
        return m_dir2V;
    }

    // SystemC-on-top, updating the verilog side
    void write2V(const char v) {

        if (m_crd > 1) return;
        m_hdl_val = v;
        if (m_hdl_val == m_sysc_val) return;

        switch(m_nState) {
        case MHDL_STRENGTH_VECTOR: assert(0); break;
        case MHDL_STRENGTH_SCALAR:
            TypeConvert_sc_to_v_scalar(m_t, m_w, v);
            for (unsigned int i = 0; i < m_vcs_rtn.size(); ++i)
                m_vcs_rtn[i](m_vcs_writeNode[i], m_t, m_w);
            break;
        case MHDL_LOGIC_SCALAR:
        case MHDL_LOGIC_WIDEVECTOR:
        case MHDL_LOGIC_VECTOR:
        case MHDL_INTEGER:
        default:
            TypeConvert_sc_to_v_str_c(m_t, m_w, v);
            for (unsigned int i = 0; i < m_vcs_rtn.size(); ++i)
                m_vcs_rtn[i](m_vcs_writeNode[i], m_t, m_w);
            break;
        }
    }

    void write2V(const char *val) {
        assert(0);
    }

    void write2V_Z() {
        write2V('Z');
    }

    // SystemC-down, propagating new SystemC value to Verilog side
    // no propagation on SystemC side
    void write(const sc_logic &val) {
        if (m_resolve) {
            sc_process_b* cur_proc = sc_get_current_process_b();

            bool found = false;

            for( int i = this->m_proc_vec.size() - 1; i >= 0; -- i ) {
                if( cur_proc == this->m_proc_vec[i] ) {
#if SYSTEMC_VERSION >= 20110630
                    if( val !=  this->m_val_vec[i] ) {
                        this->m_val_vec[i] = val;
#else
                    if( val != *this->m_val_vec[i] ) {
                        *this->m_val_vec[i] = val;
#endif
                    }
                    found = true;
                    break;
                }
            }

            if( ! found ) {
                this->m_proc_vec.push_back( cur_proc );
#if SYSTEMC_VERSION >= 20110630
                this->m_val_vec.push_back( sc_dt::sc_logic( val ) );
#else
                this->m_val_vec.push_back( new sc_dt::sc_logic( val ) );
#endif
            }
#if SYSTEMC_VERSION >= 20110630
            sc_core::sc_logic_resolve( this->m_new_val, this->m_val_vec );
#else
            sc_core::sc_logic_resolve::resolve( this->m_new_val, this->m_val_vec );
#endif
        } else {
            this->m_new_val = val;
        }
        if (m_rtn) {
            switch (m_nState) {
            case MHDL_STRENGTH_VECTOR:
                TypeConvert_sc_to_v_exps(m_u, m_w, this->m_new_val);
                m_rtn(m_writeNode, (vec32 *)m_u, m_w);
                break;
            default:
                TypeConvert_sc_to_v(m_t, m_w, this->m_new_val);
                m_rtn(m_writeNode, m_t, m_w);
                break;
            }
        }
    }

    // all topologies: Verilog propagates to SystemC
    void writeHS(unsigned int *val, void *obj) {
        sc_logic value;
        switch (m_nState) {
        case MHDL_STRENGTH_VECTOR:
            TypeConvert_v_to_sc_exp(value, m_w, val);
            break;
        case MHDL_STRENGTH_SCALAR:
            TypeConvert_v_to_sc_scalar(value, m_w, val);
            break;
        case MHDL_LOGIC_VECTOR:
        case MHDL_LOGIC_WIDEVECTOR:
        default:
            TypeConvert_v_to_sc_R(value, m_w, (vec32 *)val);
            break;
        }
        if (m_crd > 1) return;

        m_dir2V = true;
        if (m_out) {
            (*m_out).write(value);
            m_sysc_val = value;
        } else {
            this->m_new_val = value;
        }
        m_dir2V = false;

        this->request_update();
    }

    void request_update() {
        sc_core::sc_prim_channel::request_update();
    }


protected:
    virtual void update()
    {
        //   resolve_table_and_propagate();
#if SYSTEMC_VERSION >= 20110630
        this->sc_signal<sc_dt::sc_logic,SC_MANY_WRITERS>::update();
#else
        this->sc_signal<sc_dt::sc_logic>::update();
#endif
    }
private:
    void *m_writeNode;
    int (*m_rtn)(void *, vec32 *, int);
    int m_w;
    int m_instNum;
    vec32 *m_t;
    unsigned int *m_u;
    int m_nState;
    bool m_done;
    std::string m_id;
    bool m_dir2V;
    sc_inout_resolved *m_out;
    sc_logic m_new_value;
    std::vector<void *> m_vcs_proc;
    std::vector<int (*)(void *, vec32 *, int)> m_vcs_rtn;
    std::vector<void *> m_vcs_writeNode;
    int m_cnt;
    bool m_resolve;
    sc_logic m_sysc_val;
    sc_logic m_hdl_val;
};


template < int W >
class sc_hsio_signal : public sc_signal_rv<W>, public sc_hsio_signal_base
{
public:
    sc_hsio_signal() : m_rtn(0), m_nState(-1), m_done(false) {
        this->m_crd = 0;
        sc_snps::vcs_cbug_attach_object_info_for_signal(this);
    }

    void end_of_elaboration() {
#ifdef SYSC_INIT_INOUT_WITH_Z
        virtualFunc();
#endif
    }
            
    int getType() const { return 2; }
    void virtualFunc() {
        char Z[W+1];
        char X[W+1];
        Z[W] = 0;
        X[W] = 0;
        for (int i = 0; i < W; ++i) { Z[i] = 'Z'; X[i] = 'X'; }
        sc_lv<W> sc_X(X);
        if (this->m_new_val == sc_X) {
            write(Z);
        }
    }

    void setW(int w, int words, std::string id) {
        m_id = id;
        m_w = w;
        if (words > 0) {
            m_t = new vec32[words];
            for (int i = 0; i < (words); ++i) { m_t[i].c = 0; m_t[i].d = 0; }
        }
        m_u = new unsigned int[w];
        for (int i = 0; i < w; ++i) m_u[i] = 0;
        m_dir2V = false;
        m_out = 0;
        m_resolve = true;
    }

    void attachDriver(void *writeNode, int (*fun)(void *, vec32 *, int), int nState, int w, int instNum) {
        m_writeNode = writeNode;
        m_rtn = fun;
        m_nState = nState;
        m_done = true;
        m_vcs_rtn.push_back(fun);
        m_vcs_writeNode.push_back(writeNode);
        m_instNum = instNum;

#ifdef SYSC_DEBUG
        bf_debug_info_opt_if(m_id.c_str(), this->name(), m_nState, m_w);
#endif
    }
    void attachLoad(void *writeNode, int nState, int w) {
        m_nState = nState;
    }

    void setOut(sc_inout_rv<W> *out) {
        m_out = out;
    }

    bool dir2SC(void) {
        return m_dir2V;
    }

    // SystemC-on-top, updating the verilog side
    void write2V(const char v) {
        assert(0);
    }

    void write2V(const char *val) {
        if (m_crd > 1) return;
        m_hdl_val = val;
        if (m_hdl_val == m_sysc_val) return;

        switch(m_nState) {
        case MHDL_STRENGTH_VECTOR:
            TypeConvert_sc_to_v_strexp(m_u, m_w, val);
            for (unsigned int i = 0; i < m_vcs_rtn.size(); ++i)
                m_vcs_rtn[i](m_vcs_writeNode[i], (vec32 *)m_u, m_w);
            break;
        case MHDL_LOGIC_SCALAR:
        case MHDL_LOGIC_WIDEVECTOR:
        case MHDL_LOGIC_VECTOR:
        case MHDL_INTEGER:
        default:
            TypeConvert_sc_to_v_str(m_t, m_w, val);
            for (unsigned int i = 0; i < m_vcs_rtn.size(); ++i)
                m_vcs_rtn[i](m_vcs_writeNode[i], m_t, m_w);
            break;
        }
    }

    void write2V_Z() {
        static char *Z = new char [ W + 1 ];
        bool first = true;
        if (first) {
            for (int i = 0; i < W; ++i) Z[i] = 'Z';
            Z[W] = 0;
        }
        first = false;
        write2V(Z);
    }

    // SystemC-down, propagating new SystemC value to Verilog side
    // no propagation on SystemC side
    void write(const sc_lv<W> &val) {
        if (m_resolve) {
            sc_process_b* cur_proc = sc_get_current_process_b();

            bool found = false;

            for( int i = this->m_proc_vec.size() - 1; i >= 0; -- i ) {
                if( cur_proc == this->m_proc_vec[i] ) {
                    if( val != *this->m_val_vec[i] ) {
                        *this->m_val_vec[i] = val;
                    }
                    found = true;
                    break;
                }
            }

            if( ! found ) {
                this->m_proc_vec.push_back( cur_proc );
                this->m_val_vec.push_back( new sc_dt::sc_lv<W>( val ) );
            }

            sc_lv_resolve<W>::resolve( this->m_new_val, this->m_val_vec );

        } else {
            this->m_new_val = val;
        }

        if (m_rtn) {
            switch(m_nState) {
            case MHDL_STRENGTH_VECTOR:
                TypeConvert_sc_to_v_exp(m_u, m_w, this->m_new_val);
                m_rtn(m_writeNode, (vec32 *)m_u, m_w);
                break;
            case MHDL_LOGIC_SCALAR:
                TypeConvert_sc_to_v(m_t, m_w, val);
                m_rtn(m_writeNode, m_t, m_w);
                break;
            case MHDL_LOGIC_WIDEVECTOR:
            case MHDL_LOGIC_VECTOR:
                TypeConvert_sc_to_v_vec(m_u, m_w, this->m_new_val);
                m_rtn(m_writeNode, (vec32 *)m_u, m_w);
                break;
            case MHDL_INTEGER:
                TypeConvert_sc_to_v_int(m_u, m_w, this->m_new_val);
                m_rtn(m_writeNode, (vec32 *)m_u, m_w);
                break;
            default:
                TypeConvert_sc_to_v(m_t, m_w, this->m_new_val);
                m_rtn(m_writeNode, m_t, m_w);
                break;
            }
        }
    }

    // all topologies: Verilog propagates to SystemC
    void writeHS(unsigned int *val, void *obj) {
        sc_lv<W> value;
        switch(m_nState) {
        case MHDL_STRENGTH_VECTOR:
            TypeConvert_v_exp_to_sc(value, m_w, val);
            break;
        case MHDL_LOGIC_SCALAR:
            TypeConvert_v_ls_to_sc(value, m_w, val);
            break;
        case MHDL_LOGIC_WIDEVECTOR:
        case MHDL_LOGIC_VECTOR:
            TypeConvert_v_vec_to_sc(value, m_w, val);
            break;
        default:
            TypeConvert_v_to_sc(value, m_w, (vec32 *)val);
            break;
        }
        if (m_crd > 1) return;

        m_dir2V = true;
        if (m_out) {
            (*m_out).write(value);
            m_sysc_val = value;
        } else {
            this->m_new_val = value;
        }
        m_dir2V = false;

        this->request_update();
    }

    void request_update() {
        sc_core::sc_prim_channel::request_update();
    }
protected:
    virtual void update()
    {
        //      resolve_table_and_propagate();
#if defined(SYSTEMC_VERSION) && (SYSTEMC_VERSION >= 20110630)
        sc_signal<sc_dt::sc_lv<W>, SC_MANY_WRITERS>::update();
#else
        sc_signal<sc_dt::sc_lv<W>                 >::update();
#endif
    }

private:
    void *m_writeNode;
    int (*m_rtn)(void *, vec32 *, int);
    int m_w;
    int m_instNum;
    vec32 *m_t;
    unsigned int *m_u;
    int m_nState;
    bool m_done;
    std::string m_id;
    bool m_dir2V;
    sc_inout_rv<W> *m_out;
    sc_lv<W> m_new_value;
    std::vector<void *> m_vcs_proc;
    std::vector<int (*)(void *, vec32 *, int)> m_vcs_rtn;
    std::vector<void *> m_vcs_writeNode;
    int m_cnt;
    bool m_resolve;
    sc_lv<W> m_sysc_val;
    sc_lv<W> m_new_val2;
    sc_lv<W> m_hdl_val;
};


#endif
