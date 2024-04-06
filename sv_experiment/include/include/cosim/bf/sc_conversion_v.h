#ifndef __SC_CONVERSION_V_H
#define __SC_CONVERSION_V_H

namespace sc_conversion {
#ifdef VCSDKI
   namespace vcsdki {
      void hdl_to_sc( const vcsd_var_info_t *varInfo, bool& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, sc_bit& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, char& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, unsigned char& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, short& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, unsigned short& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, int& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, unsigned int& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, long& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, unsigned long& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, double& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, sc_logic& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, sc_int_base& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, sc_uint_base& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, sc_signed& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, sc_unsigned& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, sc_bv_base& dest );
      void hdl_to_sc( const vcsd_var_info_t *varInfo, sc_lv_base& dest );

      void sc_to_hdl( bool& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( sc_bit& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( char& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( unsigned char& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( short& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( unsigned short& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( int& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( unsigned int& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( long& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( unsigned long& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( double& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( const sc_logic& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( const sc_int_base& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( const sc_uint_base& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( const sc_signed& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( const sc_unsigned& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( const sc_bv_base& src, vcsd_var_info_t *varInfo );
      void sc_to_hdl( const sc_lv_base& src, vcsd_var_info_t *varInfo );

   }  // end vcsdki namespace
#endif
   namespace vcsacc {
      void hdl_to_sc( t_acc_vecval *accvec, int size, bool& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, sc_bit& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, char& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, unsigned char& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, short& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, unsigned short& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, int& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, unsigned int& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, long& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, unsigned long& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, double& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, sc_logic& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, sc_int_base& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, sc_uint_base& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, sc_signed& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, sc_unsigned& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, sc_bv_base& dest );
      void hdl_to_sc( t_acc_vecval *accvec, int size, sc_lv_base& dest );

      void sc_to_hdl( const bool& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const sc_bit& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const char& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const unsigned char& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const short& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const unsigned short& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const int& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const unsigned int& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const long& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const unsigned long& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const double& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const sc_logic& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const sc_int_base& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const sc_uint_base& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const sc_signed& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const sc_unsigned& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const sc_bv_base& val, t_acc_vecval *accvec, const int mask, int size );
      void sc_to_hdl( const sc_lv_base& val, t_acc_vecval *accvec, const int mask, int size );
   
   } // end namespace vcsacc

   namespace check_sc_hdl {
     void check_sc_hdl(handle, bool, int, const char *);
     void check_sc_hdl(handle, sc_bit, int, const char *);
     void check_sc_hdl(handle, char, int, const char *);
     void check_sc_hdl(handle, unsigned char, int, const char *);
     void check_sc_hdl(handle, short, int, const char *);
     void check_sc_hdl(handle, unsigned short, int, const char *);
     void check_sc_hdl(handle, int, int, const char *);
     void check_sc_hdl(handle, unsigned int, int, const char *);
     void check_sc_hdl(handle, long, int, const char *);
     void check_sc_hdl(handle, unsigned long, int, const char *);
     void check_sc_hdl(handle, double, int, const char *);
     void check_sc_hdl(handle, sc_logic, int, const char *);
     void check_sc_hdl(handle, sc_int_base, int, const char *);
     void check_sc_hdl(handle, sc_uint_base, int, const char *);
     void check_sc_hdl(handle, sc_signed, int, const char *);
     void check_sc_hdl(handle, sc_unsigned, int, const char *);
     void check_sc_hdl(handle, sc_bv_base, int, const char *);
     void check_sc_hdl(handle, sc_lv_base, int, const char *);
   } // end check_sc_hdl namespace
   
} // end sc_conversion namespace
#endif // __SC_CONVERSION_V_H
