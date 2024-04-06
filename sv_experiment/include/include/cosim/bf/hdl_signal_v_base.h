// This may look like C code, but it is really -*- C++ -*-
//
// hdl_signal_v_base.h --
// Copyright Synopsys 2003
// Author          : Ric Hilderink
// Created On      : Tue Jul  1 16:24:55 2003
// Status          : none
//

#ifndef _hdl_signal_v_base_h_
#define _hdl_signal_v_base_h_

#include "vpi_user.h"
#include "bf_user.h"
#undef bool

#include "hdl_signal_base.h"

extern handle BF_register_output_cb(const char *, const char *,
                                    char *,
                                    int (*)(struct t_vc_record *),
                                    int);

extern handle BF_register_input_cb(const char *, int);
extern void   BF_obtain_value( handle ahandle, p_acc_value pValue );
extern void   BF_transport( handle ahandle, p_acc_value pValDataOut );
extern void   BF_add_to_transport_queue_sc_to_hdl(hdl_signal_base *);

extern std::string BF_register_connection(const std::string &, const std::string &, sc_core::sc_object &);

typedef struct bf_verilog_value
{
    t_setval_value m_v;
    int m_size;
    int m_isNew;
    int m_mode;
    char *m_strval;
    handle m_handle;
} bf_verilog_value_s;

struct hdl_cb_struct;
extern hdl_cb_struct *new_hdl_cb_struct();
extern void hdl_cb_struct_set(hdl_cb_struct *, hdl_signal_base *);

extern unsigned int BF_notify(handle);
extern "C" bool isElabMode();

extern int MX_cb(struct t_vc_record *rec);

#endif
