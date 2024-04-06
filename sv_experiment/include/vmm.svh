

/******************************************************************
 *   Copyright (c) 2006 by Synopsys Inc. - All Rights Reserved    *
 *                                                                *
 *    CONFIDENTIAL AND PROPRIETARY INFORMATION OF SYNOPSYS INC.   *
 ******************************************************************/

`ifndef INC_VMM_LIB_SVH
`define INC_VMM_LIB_SVH

/*

	This file is not intended to be included in user code, it simply
	this contains all the function prototypes for the VMM classes.   

 	Please contact vcs-support@synopsys.com, pioneer-support@synopsys.com
	if you have any questions!

	4/6/06
*/

/*    
	
class vmm_env;
   vmm_log log;
   vmm_notify notify;
   typedef enum int unsigned {GEN_CFG = 1,
                              BUILD,
                              RESET_DUT,
                              CFG_DUT,
                              START,
                              RESTART,
                              WAIT_FOR_END,
                              STOP,
                              CLEANUP,
                              REPORT} notifications_e;
   event end_test;

   extern function new(string name = "Verif Env");
   extern task run();
   extern virtual function void gen_cfg();
   extern virtual function void build();
   extern virtual task reset_dut();
   extern virtual task cfg_dut();
   extern virtual task start();
   extern virtual task wait_for_end();
   extern virtual task stop();
   extern virtual task cleanup();
   extern virtual task restart(bit reconfig = 0);
   extern virtual task report();
endclass: vmm_env

class vmm_log_msg;
   vmm_log    log;
   
   time       timestamp;
   int        original_typ;
   int        original_severity;
   int        effective_typ;
   int        effective_severity;
   string     text[$];
   logic      issued;
   int        handling;
endclass: vmm_log_msg

class vmm_log_format;
   extern virtual function string format_msg(string name,
                                             string instance,
                                             string msg_typ,
                                             string severity,
                                             ref string lines[$]);

   extern virtual function string continue_msg(string name,
                                               string instance,
                                               string msg_typ,
                                               string severity,
                                               ref string lines[$]);

   extern virtual function string abort_on_error(int count,
                                                 int limit);

   extern virtual function string pass_or_fail(bit    pass,
                                               string name,
                                               string instance,
                                               int    fatals,
                                               int    errors,
                                               int    warnings,
                                               int    dem_errs,
                                               int    dem_warns);
endclass: vmm_log_format

class vmm_log_callbacks;
   extern virtual task pre_abort(vmm_log log);
   extern virtual task pre_stop(vmm_log log);
   extern virtual task pre_debug(vmm_log log);
endclass: vmm_log_callbacks

class vmm_log;

   //
   // Symbolic constants for message types
   //
   typedef enum int {FAILURE_TYP     = 'h0001,
                     NOTE_TYP        = 'h0002,
                     DEBUG_TYP       = 'h0004,
                     REPORT_TYP      = 'h0008,
                     NOTIFY_TYP      = 'h0010,
                     TIMING_TYP      = 'h0020,
                     XHANDLING_TYP   = 'h0040,
                     PROTOCOL_TYP    = 'h0080,
                     TRANSACTION_TYP = 'h0100,
                     COMMAND_TYP     = 'h0200,
                     CYCLE_TYP       = 'h0400,
                     USER_TYP_0      = 'h0800,
                     USER_TYP_1      = 'h1000,
                     USER_TYP_2      = 'h2000,
                     INTERNAL_TYP    = 'h4000,
                     DEFAULT_TYP     = -1,
                     ALL_TYPS        = 'hFFFF} types_e;

   //
   // Symbolic values for message severity
   //
   typedef enum int {FATAL_SEV   = 'h0001,
                     ERROR_SEV   = 'h0002,
                     WARNING_SEV = 'h0004,
                     NORMAL_SEV  = 'h0010,
                     TRACE_SEV   = 'h0020,
                     DEBUG_SEV   = 'h0040,
                     VERBOSE_SEV = 'h0080,
                     HIDDEN_SEV  = 'h0100,
                     IGNORE_SEV  = 'h0200,
                     DEFAULT_SEV = -1,
                     ALL_SEVS    = 'hFFFF} severities_e;

   //
   // Symbolic values for simulation handling
   //
   typedef enum int {ABORT_SIM        = 'h0001,
                     COUNT_ERROR      = 'h0002,
                     STOP_PROMPT      = 'h0004,
                     DEBUGGER         = 'h0008,
                     DUMP_STACK       = 'h0010,
                     CONTINUE         = 'h0020,
                     IGNORE           = 'h0040,
                     DEFAULT_HANDLING = -1} handling_e;
   
   extern function new(string name,
                string instance,
                vmm_log under = null);
      
   extern virtual function void is_above(vmm_log log);
   extern virtual function vmm_log copy(vmm_log to = null);

   extern virtual function string get_name();
   extern virtual function string get_instance();

   extern virtual function void list(string name     = "/./",
                                     string instance = "/./",
                                     bit    recurse  = 0);
   extern virtual function void display(string prefix = "");
   extern virtual function string psdisplay(string prefix = "");

   //
   // Formatting
   //
   extern virtual function vmm_log_format set_format(vmm_log_format fmt);
   extern virtual function string set_typ_image(int typ, string  image);
   extern virtual function string set_sev_image(int severity, string  image);
      
   extern virtual function void report(string name     = "/./",
                                       string instance = "/./",
                                       bit    recurse  = 0);
      
   //
   // Issue messages
   //
   extern virtual function bit start_msg(int typ,
                                         int severity = DEFAULT_SEV);
   extern virtual function bit text(string msg = "");
   extern virtual function void end_msg();

   //
   // Message management
   //
   extern virtual function void enable_typs(int     typs,
                                            string  name      = "",
                                            string  instance  = "",
                                            bit     recursive = 0);
   extern virtual function void disable_typs(int     typs,
                                             string  name     = "",
                                             string  instance = "",
                                             bit     recursive = 0);
   extern virtual function int modify(string name         = "",
                                      string instance     = "",
                                      bit    recursive    = 0,
                                      int    typ          = ALL_TYPS,
                                      int    severity     = ALL_SEVS,
                                      string text         = "",
                                      int    new_typ      = UNCHANGED,
                                      int    new_severity = UNCHANGED,
                                      int    handling     = UNCHANGED);
   extern virtual function void unmodify(int    modification_id = -1,
                                      string name            = "",
                                      string instance        = "",
                                      bit    recurse         = 0);

   extern virtual function void set_verbosity(int    severity,
                                              string name      = "",
                                              string instance  = "",
                                              bit    recurse   = 0);
   extern function int get_verbosity();

   //
   // File logging
   //
   extern virtual function void log_start(int    file,
                                          string name     = "",
                                          string instance = "",
                                          bit    recurse  = 0);
   extern virtual function void log_stop(int    file,
                                         string name     = "",
                                         string instance = "",
                                         bit    recurse  = 0);

   //
   // Manage error counts
   //
   extern virtual function void stop_after_n_errors(int n);
   extern virtual function int get_message_count(int    severity = ALL_SEVS,
                                                 string name     = "",
                                                 string instance = "",
                                                 bit    recurse  = 0);

   //
   // Synchronize with messages
   //
   extern virtual task wait_for_msg(string name     = "",
                                    string instance = "",
                                    bit    recurse  = 0,
                                    int    typs     = ALL_TYPS,
                                    int    severity = ALL_SEVS,
                                    string text     = "",
                                    logic  issued   = 1'bx,
                                    ref vmm_log_msg msg);
   extern virtual function int create_watchpoint(int    typs     = ALL_TYPS,
                                                 int    severity = ALL_SEVS,
                                                 string text     = "",
                                                 logic  issued   = 1'bx);
   extern virtual function void add_watchpoint(int    watchpoint_id,
                                               string name            = "",
                                               string instance        = "",
                                               bit    recurse         = 0);
   extern virtual function void remove_watchpoint(int    watchpoint_id = -1,
                                                  string name          = "",
                                                  string instance      = "",
                                                  bit    recurse       = 0);
   extern virtual task wait_for_watchpoint(int watchpoint_id,
                                           ref vmm_log_msg msg);

   //
   // Callback Management
   //
   extern virtual function void prepend_callback(vmm_log_callbacks cb);
   extern virtual function void append_callback(vmm_log_callbacks cb);
   extern virtual function void unregister_callback(vmm_log_callbacks cb);
endclass: vmm_log

class vmm_data;
   int stream_id;
   int scenario_id;
   int data_id;
   vmm_notify notify;
   typedef enum int {EXECUTE,
                     STARTED,
                     ENDED} notifications_e;

   extern function new(vmm_log log);
   extern function vmm_log set_log(vmm_log log);
   extern function void display(string prefix = "");
   extern virtual function string psdisplay(string prefix = "");
   extern virtual function bit is_valid(bit silent = 1,
                                 int kind   = -1);
   extern virtual function vmm_data allocate();
   extern virtual function vmm_data copy(vmm_data to = null);
   extern virtual protected function void copy_data(vmm_data to);
   extern virtual function bit compare(       vmm_data to,
                                output string   diff,
                                input  int      kind = -1);
   extern virtual function int unsigned byte_size(int kind = -1);
   extern virtual function int unsigned max_byte_size(int kind = -1);
   extern virtual function int unsigned byte_pack(ref logic [7:0]    bytes[],
                                           input int unsigned offset = 0,
                                           input int          kind   = -1);
   extern virtual function int unsigned byte_unpack(const ref logic [7:0] bytes[],
                                             input int unsigned    offset = 0,
                                             input int             len    = -1,
                                             input int             kind   = -1);
   extern virtual function bit load(int file);
   extern virtual function void save(int file);

endclass: vmm_data

class vmm_channel;
   vmm_log log;
   vmm_notify notify;
   // Predefined notifications
   typedef enum int unsigned {FULL,
                              EMPTY,
                              PUT,
                              GOT,
                              PEEKED,
                              ACTIVATED,
                              ACT_STARTED,
                              ACT_COMPLETED,
                              ACT_REMOVED,
                              LOCKED,
                              UNLOCKED} notifications_e;

   // Arguments for lock methods
   typedef enum bit [1:0] {SOURCE = 2'b01,
                           SINK   = 2'b10} endpoints_e;

   typedef enum int unsigned {INACTIVE,
                              PENDING,
                              STARTED,
                              COMPLETED} active_status_e;

   extern function new(string       name,
                string       instance,
                int unsigned full           = 1,
                int unsigned empty          = 0,
                bit          fill_as_bytes  = 1'b0);

   extern virtual void reconfigure(int   full          = -1,
                             int   empty         = -1,
                             logic fill_as_bytes = 1'bx);

   extern virtual int unsigned full_level();
   extern virtual int unsigned empty_level();
   extern virtual int unsigned level();
   extern virtual int unsigned size();
   extern virtual bit is_full();

   extern function void flush();
   extern function void sink();
   extern function void flow();
   extern function void lock(bit [1:0] who);
   extern function void unlock(bit [1:0] who);
   extern function bit  is_locked(bit [1:0] who);
   extern function void display(string prefix = "");
   extern function string psdisplay(string prefix = "");
   extern task put(vmm_data obj, int offset = -1);
   extern function void sneak(vmm_data obj, int offset = -1);
   extern function vmm_data unput(int offset = -1);
   extern task get(output vmm_data obj,
            input  int      offset = 0);
   extern task peek(output vmm_data obj,
             input  int      offset = 0);
   extern task activate(output vmm_data obj,
                 input  int      offset = 0);
   extern function vmm_data active_slot();
   extern function vmm_data start();
   extern function vmm_data complete(vmm_data status = null);
   extern function vmm_data remove();
   extern function active_status_e status();
   extern function bit tee_mode(bit is_on);
   extern task tee(output vmm_data obj);
   extern function void connect(vmm_channel downstream);
   extern function vmm_data for_each(bit reset = 0);
   extern function int unsigned for_each_offset();
   extern function bit record(string filename);
   extern task playback(output bit      success,
                 input  string   filename,
                 input  vmm_data loader,
                 input  bit      metered = 0);
   
endclass: vmm_channel

`define vmm_channel_(T) T``_channel
`define vmm_channel(T) \
class `vmm_channel_(T) extends vmm_channel; \
   extern function new(string name, \
                string instance, \
                int    full = 1, \
                int    empty = 0, \
                bit    fill_as_bytes = 0); \
   extern function T unput(int offset = -1); \
   extern task get(output T obj, input int offset = 0); \
   extern task peek(output T obj, input int offset = 0); \
   extern task activate(output T obj, input int offset = 0); \
   extern function T active_slot(); \
   extern function T start(); \
   extern function T complete(vmm_data status = null); \
   extern function T remove(); \
   extern task tee(output T obj); \
endclass

class vmm_broadcast extends vmm_xactor;

   typedef enum {AFAP,
                 ALAP} bcast_mode_e;
   
   extern function new(string            name,
                string            instance,
                vmm_channel source,
                bit               use_references = 1,
                int               mode           = AFAP);
   extern virtual task broadcast_mode(bcast_mode_e mode);
   extern virtual function int     new_output(vmm_channel channel,
                                       logic use_references = 1'bx);
   extern virtual task bcast_to_output(int     channel_id,
                                int     on_off);
   extern virtual protected function bit add_to_output(int unsigned decision_id,
                                             int unsigned output_id,
                                             vmm_channel       channel,
                                             vmm_data          obj);
   extern virtual function void start_xactor();
   extern virtual function void stop_xactor();
   extern virtual function void reset_xactor(reset_e rst_type = SOFT_RST);
endclass : vmm_broadcast 

class vmm_scheduler_election;
   int     instance_id;
   int unsigned election_id;

   int unsigned      n_sources;   
   vmm_channel       sources[$];
   int unsigned      ids[$];
   int unsigned      id_history[$];
   vmm_data          obj_history[$];

   rand int unsigned source_idx;
   rand int unsigned obj_offset;

   constraint default_round_robin;
endclass: vmm_scheduler_election

class vmm_scheduler extends vmm_xactor;

   vmm_scheduler_election randomized_sched;
   
   protected vmm_channel out_chan;

   extern function new(string       name,
            string            instance,
            vmm_channel       destination,
            int               instance_id = -1);
   extern virtual function int     new_source(vmm_channel channel);
   extern virtual task sched_from_input(int     channel_id,
                                 int     on_off);
   extern virtual protected task schedule(output vmm_data obj,
                                                input  vmm_channel sources[$],
                                                input  int unsigned input_ids[$]);
   extern virtual protected task get_object( output vmm_data obj,
                                               input vmm_channel source,
                                               input int unsigned    input_id,
                                               input int     offset);
   extern virtual function void start_xactor();
   extern virtual function void stop_xactor();
   extern virtual function void reset_xactor(reset_e rst_typ = SOFT_RST);
endclass: vmm_scheduler
  
virtual class vmm_notification;
   extern virtual task indicate(ref vmm_data status);
   extern virtual task reset();
endclass: vmm_notification

class vmm_notify;
   vmm_log log;

   typedef enum int {ONE_SHOT = 1,
                     BLAST,
                     ON_OFF} sync_e;

   typedef enum bit {SOFT,
                     HARD} reset_e;
 
   extern function new(vmm_log log);
   extern virtual function void display(string prefix = "");
   extern virtual function string psdisplay(string prefix = "");
   extern virtual function vmm_notify copy(vmm_notify to = null);
   extern virtual function int configure(int notification_id = -1,
        			  sync_e sync = ONE_SHOT);
   extern virtual function int is_configured(int notification_id);
   extern virtual function bit is_on(int notification_id);
   extern virtual task wait_for(int notification_id);
   extern virtual task wait_for_off(int notification_id);
   extern virtual function bit is_waited_for(int notification_id);
   extern virtual function void terminated(int notification_id);
   extern virtual function vmm_data status(int notification_id);
   extern virtual function time timestamp(int notification_id);
   extern virtual function void indicate(int notification_id,
	            		  vmm_data status = null);
   extern virtual function void set_notification(int          notification_id,
    				          vmm_notification ntfy = null);
   extern virtual function vmm_notification get_notification(int notification_id);
   extern virtual function void reset(int     notification_id = -1,
                               reset_e rst_typ         = SOFT);

endclass: vmm_notify

virtual class vmm_xactor_callbacks;
endclass: vmm_xactor_callbacks

class vmm_xactor;
   vmm_log  log;

   int stream_id;

   vmm_notify notify;
   typedef enum int {XACTOR_IDLE = 999990,
                     XACTOR_BUSY,
                     XACTOR_STARTED,
                     XACTOR_STOPPED,
                     XACTOR_RESET} notifications_e;

   typedef enum int {SOFT_RST,
                     PROTOCOL_RST,
                     FIRM_RST,
                     HARD_RST} reset_e;

   extern function new(string name,
	    	string instance,
		int    stream_id = -1);
   extern virtual function string get_name();
   extern virtual function string get_instance();
   extern virtual function void start_xactor();
   extern virtual function void stop_xactor();
   extern virtual function void reset_xactor(reset_e rst_typ = SOFT_RST);
   extern virtual function void save_rng_state();
   extern virtual function void restore_rng_state();
   extern virtual function void xactor_status(string prefix = "");
   extern virtual protected task main();
   extern protected task wait_if_stopped();
   extern protected task wait_if_stopped_or_empty(vmm_channel chan);
   extern virtual function void prepend_callback(vmm_xactor_callbacks cb);
   extern virtual function void append_callback(vmm_xactor_callbacks cb);
   extern virtual function void unregister_callback(vmm_xactor_callbacks cb);
endclass: vmm_xactor


`define vmm_atomic_gen_(class)           class``_atomic_gen
`define vmm_atomic_gen_callbacks_(class) class``_atomic_gen_callbacks

`define vmm_atomic_gen(class_name, text) \
 \
typedef class `vmm_atomic_gen_(class_name); \
class `vmm_atomic_gen_callbacks_(class_name) extends vmm_xactor_callbacks; \
   virtual task post_inst_gen(`vmm_atomic_gen_(class_name) gen, \
                              class_name                   obj, \
                              ref bit                      drop); \
   endtask \
endclass \
 \
class `vmm_atomic_gen_(class_name) extends vmm_xactor; \
   int unsigned stop_after_n_insts; \
   typedef enum int {GENERATED, \
                     DONE} symbols_e; \
   class_name randomized_obj; \
   `vmm_channel_(class_name) out_chan; \
   extern function new(string                    instance, \
                int                       stream_id = -1, \
                `vmm_channel_(class_name) out_chan  = null); \
   extern virtual task inject(class_name obj, \
                       ref bit    dropped); \
endclass

`define vmm_scenario_(class)                class``_scenario
`define vmm_scenario_constr_basic_(class)   class``_scenario_constr_basic
`define vmm_atomic_scenario_(class)         class``_atomic_scenario
`define vmm_scenario_election_(class)       class``_scenario_election
`define vmm_scenario_election_valid_(class) class``_scenario_election_valid
`define vmm_scenario_gen_(class)            class``_scenario_gen
`define vmm_scenario_gen_callbacks_(class)  class``_scenario_gen_callbacks

`define vmm_scenario_gen(class_name, text) \
class `vmm_scenario_(class_name) extends vmm_data; \
   static vmm_log log; \
   int stream_id; \
   int scenario_id; \
   rand int unsigned scenario_kind; \
   rand int unsigned length; \
   rand class_name items[]; \
   class_name using; \
   rand int unsigned  repeated; \
   static int unsigned repeat_thresh = 100; \
   extern function int unsigned define_scenario(string name, \
                                         int unsigned max_len); \
   extern function void redefine_scenario(int unsigned scenario_kind, \
                                   string       name, \
                                   int unsigned max_len); \
   extern function string scenario_name(int unsigned scenario_kind); \
   extern function void allocate_scenario(class_name using = null); \
   extern function void fill_scenario(class_name using = null); \
   extern virtual task apply(`vmm_channel_(class_name) channel, \
                      ref int unsigned          n_insts); \
endclass \
 \
class `vmm_atomic_scenario_(class_name) extends `vmm_scenario_(class_name); \
   int unsigned ATOMIC; \
   constraint atomic_scenario; \
endclass \
 \
class `vmm_scenario_election_(class_name); \
   int stream_id; \
   int scenario_id; \
   int unsigned n_scenarios; \
   int unsigned last_selected[$]; \
   int unsigned next_in_set; \
   `vmm_scenario_(class_name) scenario_set[$]; \
   rand int select; \
   constraint `vmm_scenario_election_valid_(class_name); \
   constraint round_robin; \
endclass \
 \
typedef class `vmm_scenario_gen_(class_name); \
class `vmm_scenario_gen_callbacks_(class_name) extends vmm_xactor_callbacks; \
   virtual task pre_scenario_randomize(`vmm_scenario_gen_(class_name) gen, \
                                       ref `vmm_scenario_(class_name) scenario); \
   endtask \
   virtual task post_scenario_gen(`vmm_scenario_gen_(class_name) gen, \
                                  `vmm_scenario_(class_name)     scenario, \
                                  ref bit                        dropped); \
   endtask \
endclass \
 \
class `vmm_scenario_gen_(class_name) extends vmm_xactor; \
 \
   int unsigned stop_after_n_insts; \
   int unsigned stop_after_n_scenarios; \
   typedef enum int {GENERATED, \
                     DONE} symbols_e; \
   `vmm_scenario_election_(class_name) select_scenario; \
   `vmm_scenario_(class_name) scenario_set[$]; \
   `vmm_channel_(class_name) out_chan; \
 \
   extern function new(string                    instance, \
                int                       stream_id = -1, \
                `vmm_channel_(class_name) out_chan  = null); \
   extern virtual task inject_obj(class_name obj); \
   extern virtual task inject(`vmm_scenario_(class_name) scenario); \
endclass

class xvc_manager;

   vmm_log    log;
   vmm_log    trace;
   vmm_notify notify;

   protected xvc_xactor xvcQ[$];

   extern function new(string instance = "Main");
   extern function bit add_xvc(xvc_xactor xvc);
   extern function bit remove_xvc(xvc_xactor xvc);
   extern function bit split(string command,
                      ref string argv[$]);

endclass: xvc_manager

class xvc_xactor extends vmm_xactor;

   vmm_log trace;

   xvc_action_channel action_chan;
   xvc_action_channel interrupt_chan;
   
   protected vmm_channel exec_chan;
   protected vmm_xactor  xactors[];

   extern function new(string name,
                string instance,
                int stream_id = -1,
                xvc_action_channel action_chan = null,
                xvc_action_channel interrupt_chan = null);
   extern function void add_action(xvc_action action);
   extern function xvc_action parse(string argv[]);
   extern protected task wait_if_interrupted();
endclass: xvc_xactor

class xvc_action extends vmm_data;

   vmm_xactor_callbacks callbacks[];

   extern function new(string name,
                vmm_log log);
   extern function string get_name();
   extern virtual function xvc_action parse(string argv[]);
   extern virtual task execute(vmm_channel exec_chan,
                        xvc_xactor  xvc);
   extern virtual function int unsigned byte_size(int kind = -1);
   extern virtual function int unsigned byte_pack(ref logic [7:0]    bytes[],
                                           input int unsigned offset = 0,
                                           input int          kind   = -1);
   extern virtual function int unsigned byte_unpack(const ref logic [7:0] bytes[],
                                             input int unsigned    offset = 0,
                                             input int             len    = -1,
                                             input int             kind   = -1);
endclass: xvc_action

class vmm_xvc_manager extends xvc_manager;

   extern function new(string name = "vmm_xvc_manager");
   extern task run(string testfile);

endclass: vmm_xvc_manager

*/


`endif
