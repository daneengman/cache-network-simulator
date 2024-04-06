/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2011 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  sc_writer_policy.h -- The sc_signal<T> writer policy definition

  Original Author: Philipp A: Hartmann, OFFIS

  CHANGE LOG IS AT THE END OF THE FILE
 *****************************************************************************/


#ifndef SC_WRITER_POLICY_H_INCLUDED_
#define SC_WRITER_POLICY_H_INCLUDED_



namespace sc_core {

class sc_object;
class sc_port_base;
class sc_process_handle;
extern
void
sc_signal_invalid_writer( sc_object* target, sc_object* first_writer,
                          sc_object* second_writer, bool check_delta );

// SIGNAL WRITING POLICIES
//
// Note: if you add a new policy to the enum below you will need to add
// an additional overload of sc_reset::reset_signal_is() for the sc_signal<bool>
// instance. That will require changes to sysc/kernel/sc_reset.cpp and 
// sysc/kernel/sc_reset.h

enum sc_writer_policy
{
  SC_ONE_WRITER        = 0, ///< unique writer (from a unique port)
  SC_MANY_WRITERS      = 1, ///< allow multiple writers (with different ports)
  SC_UNCHECKED_WRITERS = 3, ///< even allow delta cycle conflicts (non-standard)
  SNPS_SC_WRITER_POLICY = 4  /*snps-added*/
};

// signal forward declaration
template< typename T, sc_writer_policy POL = SNPS_SC_WRITER_POLICY >  /*snps-changed*/
class sc_signal;

template< sc_writer_policy >
struct sc_writer_policy_check;

struct sc_writer_policy_nocheck_write
{
  bool check_write( sc_object* /* target */, bool /* value_changed */ )
    { return true; }
  void update(){}
};

struct sc_writer_policy_check_write
{
  bool check_write( sc_object* target, bool value_changed );
  void update(){}
protected:
  sc_writer_policy_check_write( bool check_delta = false )
    : m_check_delta( check_delta ), m_writer_p(NULL) {}
  const bool         m_check_delta;
  sc_object*         m_writer_p;
};

struct sc_writer_policy_check_delta
    : sc_writer_policy_check_write
{

  sc_writer_policy_check_delta()
    : sc_writer_policy_check_write(true) {}

  bool check_write( sc_object* target, bool value_changed )
  {
      if( value_changed )
          return sc_writer_policy_check_write::check_write( target, true );
      return true;
  }

  void update(){ m_writer_p = NULL; }
};

struct sc_writer_policy_nocheck_port
{
  bool check_port( sc_object*, sc_port_base*, bool )
    { return true; }
};

struct sc_writer_policy_check_port
{
  bool check_port( sc_object* target, sc_port_base* port, bool is_output );

protected:
  sc_writer_policy_check_port() : m_output(0) {}
  sc_port_base* m_output;
};

template<>
struct sc_writer_policy_check<SC_ONE_WRITER>
  : sc_writer_policy_check_port
  , sc_writer_policy_check_write
{};

template<>
struct sc_writer_policy_check<SC_MANY_WRITERS>
  : sc_writer_policy_nocheck_port
  , sc_writer_policy_check_delta
{};

template<>
struct sc_writer_policy_check<SC_UNCHECKED_WRITERS>
  : sc_writer_policy_nocheck_port
  , sc_writer_policy_nocheck_write
{};

/*snps-added-begin*/
// ----------------------------------------------------------------------------
//  STRUCT : snps_sc_writer_policy_check
// ----------------------------------------------------------------------------

struct snps_sc_writer_policy_check
{
    bool check_port(sc_object* target_, sc_port_base* port_, bool is_output_)
    {
	init_on_the_fly();
        if (m_policy == SC_UNCHECKED_WRITERS) {
            return true;
        }
        return do_check_port(target_, port_, is_output_);
    }

    bool check_write(sc_object* target_, bool value_changed_)
    {
	init_on_the_fly();
        if (m_policy == SC_UNCHECKED_WRITERS) {
            return true;
        }
        return do_check_write(target_, value_changed_);
    }

    void update()
    {
	init_on_the_fly();
        if (m_policy == SC_MANY_WRITERS) {
            m_writer = 0;
        }
    }

    static sc_writer_policy get_writer_policy()
    { 
	init_on_the_fly();
	return m_policy; 
    }

protected:

snps_sc_writer_policy_check() : m_output(0), m_writer(0) {}
    /* snps-modified-begin */
    ~snps_sc_writer_policy_check();
    /* snps-modified-end */
    
private:

    bool do_check_port(
        sc_object* target_, sc_port_base* port_, bool is_output_);
    bool do_check_write(
        sc_object* target_, bool value_changed_);
    static sc_writer_policy initialize();
    static void init_on_the_fly() 
    {
	if (!m_valid) {
	    m_policy = initialize();
	    m_valid = true;
	}
    }
private:

    static sc_writer_policy m_policy;
    static bool   m_valid;

    sc_port_base* m_output;
    /* snps-modified-begin */
    sc_process_handle* m_writer;    // used to be sc_object*
    /* snps-modified-end */
};

// ----------------------------------------------------------------------------
//  STRUCT : sc_writer_policy_check<SNPS_SC_WRITER_POLICY>
// ----------------------------------------------------------------------------

template <>
struct sc_writer_policy_check<SNPS_SC_WRITER_POLICY>
    : snps_sc_writer_policy_check
{};
/*snps-added-end*/

} // namespace sc_core

#endif

// Taf!
