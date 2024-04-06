#ifndef SCSCOMM_H
#define SCSCOMM_H
#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>
typedef struct scsim_communication_data_s
{
    /* design unit info, as resolved from [worklib].config or */
    /* [worklib].entity__arch from command line               */
    char    *worklibPath;        /* where partition & monsigs files are saved */
    char    *entityName;         /* no double underscores, may be config */
    char    *architectureName;   /* is null if&only if entityName is a config */
    int      designUnitType;     /* as returned from dl_qdu */
    char    *topSimFileName;     /* as returned from dl_qdu */

    /* timebase */
    int      timebase;           /* STI_xx values defined in vtimeElab.h */
    char    *timebase_str;       /* string form */
    int      ignorelowres;   /* ignore time in design if lower than timebase */
    int      textio_timebase_unit; /* xgli added */

    /* tres */
    char *tres_str;
    int  tres_time; /* xgli */
    int  tres_timebase;

    /* for simprofile */
    unsigned int fProfileNew;
    char* newProfArgs;

    /* For MX boundary performance */
    unsigned mhdl_root_net_opt;
    unsigned mhdl_alias_highconn;

    /* isMixedHDL */
    unsigned isMixedHDL;         /* whether this is a mixed model or not */

    /* In MixedHDL was internal file .mhdlinst.dat.verilog created at
     * elaboration time or not.
     */
    unsigned mhdlDatVerilog;

    /*
     * If we are running in the Qualcomm / AMD COVG master slave flow.
     * Master is compiled with +simmaster
     * Slave is compiled with +simslave
     * Simulation run with +slave_load / -master_standalone.
     */
    unsigned qcomMasterSlaveFlow;

    /* partition file */
    char    *partitionFileName;  /* prepend worklibPath to get complete path */

    /* generics file */
    char    *genericsFileName;   /* prepend worklibPath to get complete path */

    /* monsigs files.  If no monsigs files then int is 0 and char ** is NULL */
    unsigned monsigsFileCount;   /* num members in the monsigsFileNames array  */
    char   **monsigsFileNames;   /* array of file name strings */

    char   *cmDirName;             /* Option to override the default coverage directory name*/
    char   *cmReportName;          /* Option to override the default coverage report name*/
    char   *cmLogName;             /* Option to override the default coverage log name*/
    unsigned isCovXmlDb;           /* Option to specify if new db was specified */

    /* vhpi lib strings.  If no vhpi libs then int is 0 and char ** is NULL. */
    unsigned vhpiLibStringCount; /* number of members in vhpiLibStringArray[]. */
    char   **vhpiLibStrings;     /* array of strings of the form "lib:func:app"*/
    /* additional signature strings - uses some of the above */
    char  *UserName;
    char  *CreationDate;
    char  *Hostname;
    char  *SciroccoVersion;
    char  *CompilerName;
    char  *CompilerVersion;
    char  *CompilerOptions;
    char  *LoaderName;
    char  *LoaderVersion;
    char  *LoaderOptions;
    char  *ElaborationOptions;
    char  *VhdlOptions;
    char  *VerilogOptions;
    char  *verWork;
    int    PartitionCount;
    char **Partitions;
    int    twoState;
    int    perf;
    int    db;
    char  *platform;
    char  *platformVersion;
    int    hasOvaDummyTop;

    int    m_total_processes;

    /* isSlave */
    unsigned isSlave;         /* whether this is a slave or not */

    /* Scirocco-i : 0 for scs, 1 for scsi, 3 for scs -lic_scsi */
    int lic_scsi;
    int mtvh;
    int pvmx;
    int popt;
    int sigp;
    int vhdlthreads;

    int singleSim;

    /* scsim compile dir */
    char *scsimCompileDirName;
    char* sn_option;
    int event_perf_mode;

    /* Hanging Verilog tops to simulate */
    unsigned MhdlVerilogTopCount;
    char   **MhdlVerilogTopNames;

    /* Support for multiple VHDL Configs */
    unsigned MhdlVhdlTopCount;
    char   **MhdlVhdlTopNames;

    /* for Unified use model*/
    unsigned unifiedUseMod;
    unsigned svaBindEnable;

    /* Env. Var. setting */
    char *vcsHome;

    unsigned isUCLI;            /* -ucli */
    unsigned isGUI;             /* -gui */
    int smart_analysis;         /* -smart_analysis */
    unsigned debugLevel;        /* -debug {level} */
    int vdbgWatch;      /* -vdbg_watch */
    unsigned isFsdbSet;         /* -fsdb */
    unsigned isFsdbOldSet;         /* -fsdb_old */

    char* ScsWorkDir;
    int sp_mem_size;
    int proc_split_num;
    int LcaLicenseEnabled;

    int upf_enabled; /* VHDL UPF */

    int jitter_enabled; /*CDC JITTER*/

    char* dataBaseDirName;      /* datbase dir name set in scs stage,for star 9*207423 */

    unsigned accessCheck;
    int withcheck;  /* check enabled */
    int checkrelax;  
    int isInterpreted;
    unsigned int    mxunielab;      /* Signifies uni-elab flow at run-time */
    int relocExe; /* relocatable executable  mode (-Xreloc_exe)
                     (compiling and running with different Vcs builds locations).*/
    unsigned partCompFlow;  /* partition compilation flow */
    char *partCompDir; /* partition data directory */

    /* if scsim.db.file is in VFS format */
    int vfs_db;

    /* to disable warning msg : FILE_OPENED_WARN */
    int no_file_opened_warn;

    /* Flag for the runtime to communicate that the design has hdl_xmr
     * calls so that certain optimization like ishare can be turned off
     */
    int designHasHdlXmrCalls;

    /* XProp flags */
    int xprop_global_merge_mode;
    /* for -xprop, -xprop=t/x/vmerge (not -xprop=cfg) */
    int xprop_globally_enabled;
    /* indicates in -xprop=<cfgfile> is provided on compile time command line */
    int xprop_config_file_used;
    /* for -xprop, -xprop=t/x/vmerge and -xprop=cfg */
    int xprop_enabled;

    int xprop_index_enabled;
    int xprop_index_enabled_explicit;   // enabled using -xprop=enableIndexRelaxation
    int xprop_integer;
    int xprop_enum;
    int xprop_report_tmerge;
    int xprop_conv_xint_t0_disabled;
    int xprop_conv_xint_disabled;
    int xprop_merge_t0_disabled;
    int xprop_start_with_merge_disabled;
}
scsim_communication_data_t;

extern void *sc_mem_malloc(size_t);
#ifdef __cplusplus
}
#endif
#endif
