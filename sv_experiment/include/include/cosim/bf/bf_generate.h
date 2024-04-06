// This may look like C code, but it is really -*- C++ -*-
// 
// bf_generate.h -- 
// Copyright Synopsys 2002
// Author          : Ric Hilderink
// Created On      : Thu Sep 26 12:20:18 2002
// Status          : none
// 


#ifndef _bf_generate_h_
#define _bf_generate_h_

extern void BF_include(const char *);
extern void BF_reg(const char *, const char *, const char *);
extern void BF_instance(const char *, const char *);
extern void BF_instance_port(const char *, const char *, const char *);
extern void BF_instance_done();

#endif
