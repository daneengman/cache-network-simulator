// This may look like C code, but it is really -*- C++ -*-
//
// bf_struct.h --
// Copyright Synopsys 2002
// Author          : Ric Hilderink
// Created On      : Thu Sep 12 13:09:03 2002
// Status          : none
//


#ifndef _bf_struct_h_
#define _bf_struct_h_

class hdl_signal_base;


typedef struct hdl_cb_struct
{
    hdl_signal_base *m_sig;
} hdl_cb_struct_s;




#endif
