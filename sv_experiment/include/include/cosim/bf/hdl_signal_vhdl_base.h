// This may look like C code, but it is really -*- C++ -*-
//
// hdl_signal_vhdl_base.h --
// Copyright Synopsys 2003
// Author          : Ric Hilderink
// Created On      : Tue Jul  1 16:24:55 2003
// Status          : none
//

#ifndef _hdl_signal_vhdl_base_h_
#define _hdl_signal_vhdl_base_h_

#if defined(SYSC_ACC_USER) && SYSC_ACC_USER == 0
#include "bf_user.h"
#else
#include "vhpi_user.h"
#endif

#include "hdl_signal_base.h"

extern "C" vhpiValueT *BF_vhpi_create_buffer(int, vhpiHandleT);
extern "C" vhpiValueT *BF_vhpi_create_buffer_str(vhpiHandleT);

extern vhpiHandleT BF_register_output_cb_vhpi(const char *, const char *,
        char *,
        void (*)(struct vhpiCbDataS *),
        int);
extern vhpiHandleT BF_register_input_cb_vhpi(const char *, const char *, int);

extern void        BF_transport_vhpi(vhpiHandleT, vhpiValueT *);
extern void        BF_obtain_value_vhpi(vhpiHandleT, vhpiValueT *);
extern void        BF_add_to_transport_queue_sc_to_hdl(hdl_signal_base *);

extern std::string BF_register_connection(const std::string &, const std::string &, sc_core::sc_object &);
//----------------------------------------------------------------------

typedef struct bf_vhdl_value
{
    vhpiValueT m_v;
    int m_size;
    int m_isNew;
    int m_mode;
    char *m_strval;
    vhpiHandleT m_handle;
} bf_vhdl_value_s;

struct hdl_cb_struct;
extern hdl_cb_struct *new_hdl_cb_struct();
extern void hdl_cb_struct_set(hdl_cb_struct *, hdl_signal_base *);

extern unsigned int BF_notify_vhpi(vhpiHandleT);
extern "C" bool isElabMode();

extern void MX_cb_vhpi(struct vhpiCbDataS *);

#endif
