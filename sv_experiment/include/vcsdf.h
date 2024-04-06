#ifndef VCSDF_H
#define VCSDF_H

/***********STARTFILE*********************************************************
 * Copyright 1993-1998 Chronologic Simulation
 * File:   lib/vcsdf.h
 * Last update: 09/22/98 [ahaldar]
 * $Id$ $Author$ $DateTime$
 * Author: Amalendu Haldar
 * Purpose: data structure definitions for vcsdirect interface used in
 * vcsd.c and vcd_new.c
 *
 ************ENDFILE**********************************************************/
typedef struct vcsdf_vcldata_s {
    unsigned char cb;
    unsigned char vc_reason;
    unsigned char size;
    unsigned char type;
    void (* vcsdf_var_consumer) (struct vcsdf_vcldata_s *);
    char *user_data;
    struct vcsdf_vcldata_s *pvdNext;
    void *p_value;
} vcsdf_vcldata_t;

void *vcsdGetIpNode(void *node);

/*  unsigned char cb;             system callback routine */
/*  unsigned char type;           vcs internal type, defined above */
/*  unsigned char size;           size of var as defined in verilog source */
/*  unsigned char vc_reason;      reason flag */
/*  char *user_data;              user data to be passed */
/*  void *p_value;                pointer to value of the signal */
/*  void (*vcsdf_var_consumer)(vcsdf_vcldata_t *);  user routine to call */

#endif
