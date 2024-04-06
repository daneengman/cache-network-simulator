// This may look like C code, but it is really -*- C++ -*-
// 
// hdl_signal_base.h -- 
// Copyright Synopsys 2003
// Author          : Ric Hilderink
// Created On      : Tue Jul  1 16:24:55 2003
// Status          : none
// 

#ifndef _hdl_signal_base_h_
#define _hdl_signal_base_h_

#include "systemc_user.h"
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "vcs_cbug_object_info.h"

enum hdl_simulator { HDL_none = 0, HDL_vcs = 1, HDL_scirocco = 2 };

enum hdl_direction { HDL_NONE = 100, HDL_INPUT = 101, HDL_INOUT, HDL_OUTPUT };
enum scv_hdl_direction { SCV_INPUT, SCV_OUTPUT, SCV_INOUT };

extern hdl_direction HDL_DIRECTION(scv_hdl_direction);
extern "C" int bfvGetTime(unsigned int *);
extern bool G_is_stopped;

typedef struct bf_time
{
  struct {
    unsigned int lo;
    unsigned int hi;
  } vcs;
  uint64 time_sc;
} bf_time_s;

/************************************************************
 * Base class for hdl_signal_v and hdl_signal_vhdl
 ************************************************************/
class hdl_signal_base
{
public:
  virtual void transport_sc_to_hdl() = 0;
  virtual void get_data_from_hdl() = 0;
  virtual void transport_hdl_to_sc() = 0;
};

#if defined(SYSTEMC_2_3_0) || defined(SYSTEMC_2_3_1)
#define SNPS_VCS_POLICY , SC_UNCHECKED_WRITERS
#else
#define SNPS_VCS_POLICY
#endif

class sc_signal_kicker : public sc_signal<bool SNPS_VCS_POLICY> {
  public:
    sc_signal_kicker(const char *hdl_name) : sc_signal<bool SNPS_VCS_POLICY>(hdl_name)
    {
      sc_snps::vcs_cbug_attach_object_info_for_signal(this);
    }
    const char *kind() const { return "dki_module_inner"; }
};

#undef SNPS_VCS_POLICY


/************************************************************
 * Valid path dividers: [._/]
 * NOTE: the '_' is used for concatenating two objects
 ************************************************************/
inline
std::string bf_ConvertProblemCharacters(std::string &name)
{
  const char * str = name.c_str();
  int len = strlen(str);
  char*nstr = new char [ len + 1 ];
  int i=0;
  int j=0;
// strip leading delimiters
  while((str[i] == ':') || (str[i] == '/') || (str[i] == '.'))
      i++;
  while (str[i] != '\0') {
      if ((str[i] == ':') || (str[i] == '/') || (str[i] == '.'))
	  nstr[j] = '_';
      else if ((str[i] == '\\') || (str[i] == ' '))
          nstr[j] = '_';
      else
	  nstr[j] = str[i];
      i++; j++;
  }
  nstr[j] = '\0';
  return nstr;
}

inline
std::string bf_ConvertProblemCharactersVCSMX(std::string &name)
{
  const char * str = name.c_str();
  int len = strlen(str);
  char*nstr = new char [ len + 1 ];
  int i=0;
  int j=0;

  // Strip leading chars
  while(ispunct(str[i])) i++;
  while (str[i] != '\0') {
      if (str[i] != '\\') {
         if ((str[i] == ':') || (str[i] == '/')) {
            nstr[j] = '.'; j++;
         }else if (str[i] != ' ') {
            nstr[j] = str[i]; j++;
         }
      }
      i++;
   }
   nstr[j]='\0';

  return nstr;
}

inline void
bf_ConvertInstnameToUpper(std::string &a)
{
    int i=0;
    while( a[i] != '\0')
    {
	if ((a[i]>='a') && (a[i]<='z'))
	    a[i] = a[i]-'a'+'A';
	i++;
    }

}
#endif
