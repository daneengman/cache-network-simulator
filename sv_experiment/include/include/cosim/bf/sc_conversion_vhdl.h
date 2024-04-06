#ifndef __SC_CONVERSION_VHDL_H
#define __SC_CONVERSION_VHDL_H

namespace sc_conversion {
   namespace vhpi {
      void hdl_to_sc( const vhpiValueT& valuep, const int size, bool& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, sc_bit& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, char& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, unsigned char& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, short& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, unsigned short& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, int& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, unsigned int& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, long& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, unsigned long& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, double& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, sc_logic& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, sc_int_base& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, sc_uint_base& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, sc_signed& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, sc_unsigned& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, sc_bv_base& dest );
      void hdl_to_sc( const vhpiValueT& valuep, const int size, sc_lv_base& dest );

      void sc_to_hdl( const bool& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const sc_bit& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const char& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const unsigned char& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const sc_logic& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const short& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const unsigned short& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const int& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const unsigned int& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const long& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const unsigned long& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const double& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const sc_int_base& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const sc_uint_base& val, vhpiValueT* valuep , const std::string &);
      void sc_to_hdl( const sc_signed& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const sc_unsigned& val, vhpiValueT* valuep , const std::string & );
      void sc_to_hdl( const sc_bv_base& val, vhpiValueT* valuep, const std::string & );
      void sc_to_hdl( const sc_lv_base& val, vhpiValueT* valuep, const std::string & );
   
   } // end namespace vhpi

   namespace check_sc_vhdl {
     void check_sc_hdl(vhpiHandleT, bool, int, const char *);
     void check_sc_hdl(vhpiHandleT, sc_bit, int, const char *);
     void check_sc_hdl(vhpiHandleT, char, int, const char *);
     void check_sc_hdl(vhpiHandleT, unsigned char, int, const char *);
     void check_sc_hdl(vhpiHandleT, short, int, const char *);
     void check_sc_hdl(vhpiHandleT, unsigned short, int, const char *);
     void check_sc_hdl(vhpiHandleT, int, int, const char *);
     void check_sc_hdl(vhpiHandleT, unsigned int, int, const char *);
     void check_sc_hdl(vhpiHandleT, long, int, const char *);
     void check_sc_hdl(vhpiHandleT, unsigned long, int, const char *);
     void check_sc_hdl(vhpiHandleT, double, int, const char *);
     void check_sc_hdl(vhpiHandleT, sc_logic, int, const char *);
     void check_sc_hdl(vhpiHandleT, sc_int_base, int, const char *);
     void check_sc_hdl(vhpiHandleT, sc_uint_base, int, const char *);
     void check_sc_hdl(vhpiHandleT, sc_signed, int, const char *);
     void check_sc_hdl(vhpiHandleT, sc_unsigned, int, const char *);
     void check_sc_hdl(vhpiHandleT, sc_bv_base, int, const char *);
     void check_sc_hdl(vhpiHandleT, sc_lv_base, int, const char *);
   } // end check_sc_vhdl namespace
   
} // end sc_conversion namespace
#endif // __SC_CONVERSION_VHDL_H
