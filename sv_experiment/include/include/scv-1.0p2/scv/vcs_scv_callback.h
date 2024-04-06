// ------------------------------------------------------------------
// SYNOPSYS CONFIDENTIAL                                             
//                                                                  
// This is an unpublished, proprietary work of Synopsys, Inc., and   
// is fully protected under copyright and trade secret laws. You may 
// not view, use, disclose, copy, or distribute this file or any     
// information contained herein except pursuant to a valid written   
// license from Synopsys.                                            
// ------------------------------------------------------------------

#ifndef _vcs_scv_callback_h_
#define _vcs_scv_callback_h_

#include "systemc.h"
#include "scv.h"
#include "tli_msglog.h"

#ifdef SNPS_MSGLOG_OVERLAP
#define MSGLOG_OVERLAP 1
#else
#define MSGLOG_OVERLAP 0
#endif

namespace sc_snps {
  namespace sc_scv {

    void my_callback_msglog(const scv_tr_handle& t, 
			    scv_tr_handle::callback_reason reason, 
			    void * user_data,
			    int msglog_overlap);
    
    void my_callback_record_attribute_msglog(const scv_tr_handle& obj,
					     const char* attribute_name,
					     const scv_extensions_if* exts_p,
					     void* user_data_p,
					     int msglog_overlap);
  }; // namespace sc_scv
}; // namespace sc_snps
					 
inline void vcs_scv_callback(const scv_tr_handle& t, 
			scv_tr_handle::callback_reason reason, 
			void * user_data) {
  sc_snps::sc_scv::my_callback_msglog(t, reason, user_data, MSGLOG_OVERLAP);
}

inline void vcs_scv_callback_record_attribute(const scv_tr_handle& obj,
					 const char* attribute_name,
					 const scv_extensions_if* exts_p,
					 void* user_data_p)
{
  sc_snps::sc_scv::my_callback_record_attribute_msglog(obj, attribute_name, exts_p, user_data_p, MSGLOG_OVERLAP);
}

#undef MSGLOG_OVERLAP


#endif

