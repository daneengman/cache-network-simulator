
/*
 * runtime.h
 *
 * Copyright (c) 1990-1993 by Synopsys, Inc.
 *      ALL RIGHTS RESERVED
 * This program is proprietary and confidential information of
 * Synopsys, Inc. and may be used and disclosed only as authorized
 * in a license agreement controlling such use and disclosure.
 */

#include <math.h>
#include <sys/types.h>
#define M9U 0
#define M9X 1
#define M90 2
#define M91 3
#define M9Z 4
#define M9W 5
#define M9L 6
#define M9H 7
#define M9D 8
#define M9_flag 9
#define M7_flag 7

#define MASTER_TID 0

#include "vss_extern.h"

#undef Proto
#if defined(__STDC__)
#define Proto(args) args
#else
#define Proto(args) ()
#endif

#if (defined(__GNUC__)) && (__GNUC__ > 2)
#define SYNOPSYS_UNUSED __attribute__  ((__unused__))
#else
#define SYNOPSYS_UNUSED
#endif

static int E2CData[] SYNOPSYS_UNUSED = {0,0,0,1,1,0,0,1,0};
static int E2CCntl[] SYNOPSYS_UNUSED = {1,1,0,1,0,1,0,1,1};
static int C2Etab[]  SYNOPSYS_UNUSED = {2,4,1,3};

IMPORT_SYMBOL int nottab[],  buftab[],
                  andtab[], nandtab[],
                   ortab[],  nortab[],
                  xortab[], nxortab[];
IMPORT_SYMBOL int notm9tab[],
                  andm9tab[], nandm9tab[],
                   orm9tab[],  norm9tab[],
                  xorm9tab[], nxorm9tab[];
IMPORT_SYMBOL int resolutionm9tab[], bufm9tab[], isxm9tab[],
                  bit_to_m9tab[],  m9_to_x01tab[],
                  m9_to_bit_tab[], m9_to_x01ztab[];
IMPORT_SYMBOL int strn_map_m9tab[], strn_map_z_m9tab[];

IMPORT_SYMBOL int  fast_memcmp(void*, void*, int);
IMPORT_SYMBOL void fast_memcpy(void*, void*, int);

IMPORT_SYMBOL char* sx_root(void*);
long long llabs(long long);
void  gc_rt_file_line(char*, char*, int, int);
void  gc_rt_ext_ips(void*, int);
char* gc_rt_ip_name(int*, void*, int);
void  gc_rt_dbs_ctl(int, void*, int, int, int, int);
void  gc_rt_dbs_dat(int, void*, int, int, int);
void  gc_rt_dbs_sch(int);

extern char *g_rt_STANDARD, *g_rt_TEXTIO;
extern long *g_ip_STANDARD, *g_ip_TEXTIO;
extern char *g_rt_STD_LOGIC_1164, *g_rt_STD_LOGIC_ARITH, *g_rt_STD_LOGIC_MISC;
extern long *g_ip_STD_LOGIC_1164, *g_ip_STD_LOGIC_ARITH, *g_ip_STD_LOGIC_MISC;

typedef int drl;

IMPORT_SYMBOL int *driverBuf, *cur_ip, *vh_map(), *cgAccessErr();
IMPORT_SYMBOL long *cg_cur_ip(int,int/*int level*/);
IMPORT_SYMBOL int** vh_values;
IMPORT_SYMBOL int stopflags;
IMPORT_SYMBOL int g_runtime_check;

#ifndef SIMTIME_T_DEFINED
#define SIMTIME_T_DEFINED
typedef struct simtime_s
{
    unsigned int ls;
    unsigned int ms;
}
simtime_t;
#endif

typedef simtime_t vint64;
IMPORT_SYMBOL void dvac Proto((vint64 *base, vint64 *r, int e));
IMPORT_SYMBOL void cgFltAdd Proto((vint64 *a, vint64 *b, vint64 *r, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL void cgFltSub Proto((vint64 *a, vint64 *b, vint64 *r, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL void cgFltMul Proto((vint64 *a, vint64 *b, vint64 *r, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL void cgFltDiv Proto((vint64 *a, vint64 *b, vint64 *r, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL void cgFltExp Proto((vint64 *a, int b, vint64 *r, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL void cgFltNeg Proto((vint64 *a, vint64 *r, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL void cgFltAbs Proto((vint64 *a, vint64 *r, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL double cgFltRz Proto((vint64 *a));
IMPORT_SYMBOL void cgFltAb Proto((double a, vint64 *r));
IMPORT_SYMBOL void cgFltFlt Proto((int a, vint64 *r, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL int cgFltFix Proto((vint64 *a, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL int cgFltEq Proto((vint64 *a, vint64 *b, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL int cgFltNe Proto((vint64 *a, vint64 *b, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL int cgFltLt Proto((vint64 *a, vint64 *b, int line, char* file, char* fullpath_file));
IMPORT_SYMBOL int cgFltLe Proto((vint64 *a, vint64 *b, int line, char* file, char* fullpath_file));

IMPORT_SYMBOL int cgCompactLen(int length);
IMPORT_SYMBOL char *cgDuRoot();
IMPORT_SYMBOL void vh_access_assign();
IMPORT_SYMBOL void vh_access_check();
IMPORT_SYMBOL void vh_access_release();
IMPORT_SYMBOL void vh_line_free();
IMPORT_SYMBOL long vh_alloc();
IMPORT_SYMBOL long vh_alloc_check_il();
IMPORT_SYMBOL void cgconvCmp2Exp4State();
IMPORT_SYMBOL void cgconvExp2Cmp4State();
IMPORT_SYMBOL void cgconvExp2Cmp2State();
IMPORT_SYMBOL void cgconvCmp2Exp2State();

IMPORT_SYMBOL void vn_WriteOther(), vn_WriteScalarZerodelay(),
              vn_WriteCompositeZerodelay(), vn_th_WriteCompositeZerodelaySubprogram(),
              vn_WriteCompositeZerodelayOthers(),
              vn_WriteCompositeZerodelayOthersOpt(),
              vn_th_WriteCompositeZerodelayOthersOpt(),
              vn_WriteCompositeZerodelayOthersOptVec(),
              vn_WriteScalarZerodelayOpt(),
              vn_WriteCompositeZerodelayOpt(),
              vn_WriteCompositeZerodelayOptVec(),
              vn_WriteScalar(), vn_WriteComposite(), vn_WriteCompositeSubprogram();

IMPORT_SYMBOL int *get_defnode_from_offset();
IMPORT_SYMBOL int get_code_tick_value();
IMPORT_SYMBOL void get_code_float_tick_value();
IMPORT_SYMBOL int *get_code_time_tick_value();
IMPORT_SYMBOL int *get_code_tick_image(void*, int, int*);
IMPORT_SYMBOL int *get_code_float_tick_image(void*, int*, int*);
IMPORT_SYMBOL int *get_code_time_tick_image(int*, int*);
IMPORT_SYMBOL int *get_code_ip_name();

typedef char byte;
IMPORT_SYMBOL void *wt_CreateWait Proto((int, int, int, int));
IMPORT_SYMBOL void wt_AddWait Proto((int, int *, int, int, int, int));
IMPORT_SYMBOL void wt_EndWait Proto((int));
IMPORT_SYMBOL void wt_AddWaitStmtDbs Proto((int, int *, int, int, int));
IMPORT_SYMBOL long tio_write(), tio_wline(), tio_rline();
IMPORT_SYMBOL int *vital_timing_CalcDelay01Z();
IMPORT_SYMBOL int *vital_timing_ExtendToFillDelay();
IMPORT_SYMBOL int *vital_timing_ExtendToFillDelay01();
IMPORT_SYMBOL int *vital_timing_ExtendToFillDelay01Z();
IMPORT_SYMBOL int *vital_timing_CalcDelay();
IMPORT_SYMBOL int *vital_timing_CalcDelay01();
IMPORT_SYMBOL int *vital_timing_CalcDelay01Z();
IMPORT_SYMBOL int vital_timing_ReportGlitch();
IMPORT_SYMBOL int vital_timing_ReportGlitchNeg();
IMPORT_SYMBOL int vital_timing_PathDelay();
IMPORT_SYMBOL int vital_timing_PathDelay01();
IMPORT_SYMBOL int vital_timing_PathDelay01Z();
IMPORT_SYMBOL int vital_timing_PathDelay_2k();
IMPORT_SYMBOL int vital_timing_PathDelay01_2k();
IMPORT_SYMBOL int vital_timing_PathDelay01Z_2k();
IMPORT_SYMBOL int vital_timing_WireDelay();
IMPORT_SYMBOL int vital_timing_WireDelay01();
IMPORT_SYMBOL int vital_timing_WireDelay01Z();
IMPORT_SYMBOL int vital_timing_SignalDelay();
IMPORT_SYMBOL int vital_timing_ReportViolation();
IMPORT_SYMBOL int vital_timing_TimingDataInit();
IMPORT_SYMBOL int vital_timing_SetupHoldCheck_Scalar();
IMPORT_SYMBOL int vital_timing_SetupHoldCheck_Vector();
IMPORT_SYMBOL int vital_timing_SetupHoldCheck_Scalar_2k();
IMPORT_SYMBOL int vital_timing_SetupHoldCheck_Vector_2k();
IMPORT_SYMBOL int vital_timing_RecoveryRemovalCheck();
IMPORT_SYMBOL int vital_timing_RecoveryRemovalCheck_2k();
IMPORT_SYMBOL int vital_timing_PeriodPulseCheck();
IMPORT_SYMBOL int vital_timing_InPhaseSkewCheck();
IMPORT_SYMBOL int vital_timing_OutPhaseSkewCheck();
IMPORT_SYMBOL int vital_timing_SynopsysTimingOptimization();
IMPORT_SYMBOL int vital_timing_SynopsysPathDelay();
IMPORT_SYMBOL int vital_timing_SynopsysPathDelay01();
IMPORT_SYMBOL int vital_timing_SynopsysPathDelay01Z();
IMPORT_SYMBOL int vital_timing_SynopsysDoPathDelay();

byte vital_primitives_VitalIDENT_Func(int tid, byte Data);
byte vital_primitives_VitalIDENT_FuncM(int tid, byte Data, byte* map);
byte vital_primitives_VitalBUF_Func(int tid, byte Data);
byte vital_primitives_VitalBUF_FuncM(int tid, byte Data, byte* map);
byte vital_primitives_VitalBUFIF0_Func(int tid, byte Data, byte Enable);
byte vital_primitives_VitalBUFIF0_FuncM(int tid, byte Data, byte Enable, byte* map);
byte vital_primitives_VitalBUFIF1_Func(int tid, byte Data, byte Enable);
byte vital_primitives_VitalBUFIF1_FuncM(int tid, byte Data, byte Enable, byte* map);
byte vital_primitives_VitalINV_Func(int tid, byte Data);
byte vital_primitives_VitalINV_FuncM(int tid, byte Data, byte* map);
byte vital_primitives_VitalINVIF0_Func(int tid, byte Data, byte Enable);
byte vital_primitives_VitalINVIF0_FuncM(int tid, byte Data, byte Enable, byte* map);
byte vital_primitives_VitalINVIF1_Func(int tid, byte Data, byte Enable);
byte vital_primitives_VitalINVIF1_FuncM(int tid, byte Data, byte Enable, byte* map);

byte vital_primitives_VitalAND_Func(int tid, byte* D, int* D_drl);
byte vital_primitives_VitalAND_FuncM(int tid, byte* D, int* D_drl, byte* map);
byte vital_primitives_VitalAND4_Func(int tid, byte A, byte B, byte C, byte D);
byte vital_primitives_VitalAND4_FuncM(int tid, byte A, byte B, byte C, byte D, byte* map);
byte vital_primitives_VitalAND3_Func(int tid, byte A, byte B, byte C);
byte vital_primitives_VitalAND3_FuncM(int tid, byte A, byte B, byte C, byte* map);
byte vital_primitives_VitalAND2_Func(int tid, byte A, byte B);
byte vital_primitives_VitalAND2_FuncM(int tid, byte A, byte B, byte* map);
byte vital_primitives_VitalNAND_Func(int tid, byte* D, int* D_drl);
byte vital_primitives_VitalNAND_FuncM(int tid, byte* D, int* D_drl, byte* map); 
byte vital_primitives_VitalNAND4_Func(int tid, byte A, byte B, byte C, byte D); 
byte vital_primitives_VitalNAND4_FuncM(int tid, byte A, byte B, byte C, byte D, byte* map);
byte vital_primitives_VitalNAND3_Func(int tid, byte A, byte B, byte C);
byte vital_primitives_VitalNAND3_FuncM(int tid, byte A, byte B, byte C, byte* map);
byte vital_primitives_VitalNAND2_Func(int tid, byte A, byte B);
byte vital_primitives_VitalNAND2_FuncM(int tid, byte A, byte B, byte* map);
byte vital_primitives_VitalNOR_Func(int tid, byte* D, int* D_drl);
byte vital_primitives_VitalNOR_FuncM(int tid, byte* D, int* D_drl, byte* map);
byte vital_primitives_VitalNOR4_Func(int tid, byte A, byte B, byte C, byte D);
byte vital_primitives_VitalNOR4_FuncM(int tid, byte A, byte B, byte C, byte D, byte* map);
byte vital_primitives_VitalNOR3_Func(int tid, byte A, byte B, byte C);
byte vital_primitives_VitalNOR3_FuncM(int tid, byte A, byte B, byte C, byte* map);
byte vital_primitives_VitalNOR2_Func(int tid, byte A, byte B);
byte vital_primitives_VitalNOR2_FuncM(int tid, byte A, byte B, byte* map);
byte vital_primitives_VitalOR_Func(int tid, byte* D, int* D_drl);
byte vital_primitives_VitalOR_FuncM(int tid, byte* D, int* D_drl, byte* map);
byte vital_primitives_VitalOR4_Func(int tid, byte A, byte B, byte C, byte D);
byte vital_primitives_VitalOR4_FuncM(int tid, byte A, byte B, byte C, byte D, byte* map);
byte vital_primitives_VitalOR3_Func(int tid, byte A, byte B, byte C);
byte vital_primitives_VitalOR3_FuncM(int tid, byte A, byte B, byte C, byte* map);
byte vital_primitives_VitalOR2_Func(int tid, byte A, byte B);
byte vital_primitives_VitalOR2_FuncM(int tid, byte A, byte B, byte* map);
byte vital_primitives_VitalXNOR_Func(int tid, byte* D, int* D_drl);
byte vital_primitives_VitalXNOR_FuncM(int tid, byte* D, int* D_drl, byte* map);                                 
byte vital_primitives_VitalXNOR4_Func(int tid, byte A, byte B, byte C, byte D); 
byte vital_primitives_VitalXNOR4_FuncM(int tid, byte A, byte B, byte C, byte D, byte* map);                     
byte vital_primitives_VitalXNOR3_Func(int tid, byte A, byte B, byte C);
byte vital_primitives_VitalXNOR3_FuncM(int tid, byte A, byte B, byte C, byte* map);
byte vital_primitives_VitalXNOR2_Func(int tid, byte A, byte B);
byte vital_primitives_VitalXNOR2_FuncM(int tid, byte A, byte B, byte* map);
byte vital_primitives_VitalXOR_Func(int tid, byte* D, int* D_drl);
byte vital_primitives_VitalXOR_FuncM(int tid, byte* D, int* D_drl, byte* map);
byte vital_primitives_VitalXOR4_Func(int tid, byte A, byte B, byte C, byte D);
byte vital_primitives_VitalXOR4_FuncM(int tid, byte A, byte B, byte C, byte D, byte* map);
byte vital_primitives_VitalXOR3_Func(int tid, byte A, byte B, byte C);
byte vital_primitives_VitalXOR3_FuncM(int tid, byte A, byte B, byte C, byte* map);
byte vital_primitives_VitalXOR2_Func(int tid, byte A, byte B);
byte vital_primitives_VitalXOR2_FuncM(int tid, byte A, byte B, byte* map);

byte* vital_primitives_VitalDECODER2_Func(int tid, byte* Ret, byte Data, byte Enable);
byte* vital_primitives_VitalDECODER2_FuncM(int tid, byte* Ret, byte Data, byte Enable, byte* map);
byte* vital_primitives_VitalDECODER4_Func(int tid, byte* Ret, byte* Data, byte Enable);
byte* vital_primitives_VitalDECODER4_FuncM(int tid, byte* Ret, byte* Data, byte Enable, byte* map);
byte* vital_primitives_VitalDECODER8_Func(int tid, byte* Ret, byte* Data, byte Enable);
byte* vital_primitives_VitalDECODER8_FuncM(int tid, byte* Ret, byte* Data, byte Enable, byte* map);
byte* vital_primitives_VitalDECODER_Func(int tid, byte* Ret, int* Ret_drl, byte* Data, int* Data_drl, byte Enable);
byte* vital_primitives_VitalDECODER_FuncM(int tid, byte* Ret, int* Ret_drl, byte* Data, int* Data_drl, byte Enable, byte* map);
byte vital_primitives_VitalMUX2_Func(int tid, byte D1, byte D0, byte Sel);
byte vital_primitives_VitalMUX2_FuncM(int tid, byte D1, byte D0, byte Sel, byte* map);
byte vital_primitives_VitalMUX4_Func(int tid, byte* D, byte* Sel);
byte vital_primitives_VitalMUX4_FuncM(int tid, byte* D, byte* Sel, byte* map);
byte vital_primitives_VitalMUX8_Func(int tid, byte* D, byte* Sel);
byte vital_primitives_VitalMUX8_FuncM(int tid, byte* D, byte* Sel, byte* map);
byte vital_primitives_VitalMUX_Func(int tid, byte* Dat, int* Dat_drl, byte* Sel, int* Sel_drl);
byte vital_primitives_VitalMUX_FuncM(int tid, byte* Dat, int* Dat_drl, byte* Sel, int* Sel_drl, byte* map);

byte vital_primitives_VitalStateTableV_Seq(int tid, int* resume, byte* Res, int* Res_drl, byte* Lin, int* Lin_drl, byte* Tab, int* Tab_drl, byte* Din, int* Din_drl, int slen);
byte vital_primitives_VitalStateTableS_Seq(int tid, int* resume, byte* Res, byte* Lin, int* Lin_drl, byte* Tab, int* Tab_drl, byte* Din, int* Din_drl); 
byte* vital_primitives_VitalTruthTableV_Func(int tid, byte* Ret, int* Ret_drl, byte* Tab, int* Tab_drl, byte* Din, int* Din_drl);
byte vital_primitives_VitalTruthTableS_Func(int tid, byte* Tab, int* Tab_drl, byte* Din, int* Din_drl);


#define comma       ,

IMPORT_SYMBOL int cgEndFile Proto((int vfd, int line, char *file, char* fullpath_file));

IMPORT_SYMBOL int cgErr Proto((char *file, char *fullpath_file, int line,
                               char *errcode));
IMPORT_SYMBOL int cgErr_param Proto((char *file, char *fullpath_file,
                                     int fileline, char *errcode, ...));

IMPORT_SYMBOL void vf_read Proto((int vfd, int len, char *addr));
IMPORT_SYMBOL void vf_close93 Proto((int* fileObj));
IMPORT_SYMBOL int vf_read3 Proto((int vfd, int esize, int len, int bo,
                                  char *addr));
IMPORT_SYMBOL void vf_write Proto((int vfd, int len, char *addr));

IMPORT_SYMBOL void vh_line_free_opt Proto((long vhindex));
IMPORT_SYMBOL void vh_forced_free Proto((long vhindex));

IMPORT_SYMBOL int tio_read Proto((long av, int type, int len, int *addr,
                                  int eflag, int thId));

#define cgMap(i,l,f)    ((i == 0) ? (int *)(long)cgErr(f,f,l,"SIMERR_NULLDEREF") : (int *)(i))
#define cgFree(i,l,f)   { vh_free(*(i)); *(i) = 0; }
#define cgForcedFree(i,l,f) { vh_forced_free(*(i)); *(i) = 0; }
#define cgLineFree(i)   (vh_line_free(i),i=0)
#define cgLineFreeOpt(i)    (vh_line_free_opt(i),i=0)
#define cgRead(f,v,l)   vf_read((f),l,v)
#define cgRead3(f,v,l,s,li) *(l)=vf_read3((f),s,li,0,v)
#define cgWriteS(f,v,l) vf_write((f),l,(ti=(v),&ti))
#define cgWriteC(f,v,l) vf_write((f),l,v)
#define cgEndLine(L,l,f) !cgClctSize(cgMap(L,l,f)-1,1,1,l,f)
#define cgReadLine(f,L) *(L)=tio_rline((f),*((long *)(L)),0,0)
#define cgWriteLine(f,L) *(L)=tio_wline((f),*(L))
#define cgTRead(L,v,g,t,l,a,b)    *(g?g:&ti)=tio_read(*(L),t,l,v,!!(g))
#define cgTWriteS(L,v,j,f,x,t,l) *(L)=tio_write(*(L),t,l,(ti=(v),&ti),j,f,x)
#define cgTWriteC(L,v,j,f,x,t,l) *(L)=tio_write(*(L),t,l,v,j,f,x)

#define cgFixF(a)   ((int)((td=cgFltRz(a))<0.0?ceil(td-0.5):floor(td+0.5)))
#define cgFixD(a)   ((int)((td=a)<0.0?ceil(td-0.5):floor(td+0.5)))

/* VHDL93 additions */
#define cgFileOpen(f,n,nic,fok,dtype,fpl) \
    vf_open93(fok, dtype, ip, prc_GetIpLevel(cur_proc),    \
              0, fpl, (nic)[0], n, (int*)0, &(f))
#define cgFileOpenStatus(fos,f,n,nic,fok,dtype,fpl) \
    vf_open93(fok, dtype, ip, prc_GetIpLevel(cur_proc), \
              0, fpl, (nic)[0], n, fos, &(f))

/* By default, FILE objects that are declared without file name and mode
   specification are initialized to VHDLFILE_NULLHANDLE (which should be -1).
   We check that the file handle is valid and then close the file and set the
   handle to null handle so that future calls will error out. */
#define cgFileClose(f) vf_close93(&(f))

#define cg_m9_strn_map(i,s,op)  (strn_map_m9tab[((i)<<4)|(s)])
#define cg_m9_strn_map_z(i,s,op)(strn_map_z_m9tab[((i)<<4)|(s)])

/* CAF: contains the struct _faultContext_s.  This struct was defined both here
        and in verr.h. Putting this struct in scMsg leads to dup def errors
        in those places that didn't use verr for error messages but used the
        other definition of _faultContext_s
*/
#include "faultContext.h"

IMPORT_SYMBOL struct _faultContext_s gFaultContext;
IMPORT_SYMBOL char *filename;

void sp_store(int tid, long* var);
void sp_load(int tid, long* var);
void sp_push(int tid, long* var);
void sp_pop(int tid, long* var);

/* wait stack functions */
int * ws_alloc Proto((unsigned size, int thread_id));
void  ws_free Proto((int* blk));
void  ws_save_wait_stk Proto((int thread_id));

typedef struct
{
    int* rp_next;   /* rp_next */
    int* data1; /* rp_back_link */
    int* data2; /* fexec */
    int* data3; /* rp_actions_on_active */
    int* rp_value;  /* rp_value */
    int* data4; /* rp_new_value */
    int* data5; /* rp_actions_on_event */
    int  data6; /* rp_flags */
    int* data8; /* rp_unscheduled_waveform */
    int* data9; /* compact_data */
    char *data10;   /* rp_u */
} repnode;

typedef struct
{
    struct {
        unsigned    bf1     : 8;
        unsigned    bf2     : 4;
        unsigned    bf3     : 1;
        unsigned    bf4 : 1;
        unsigned    bf5     : 1;
        unsigned    bf6     : 1;
        unsigned    bf7     : 1;
        unsigned    bf8     : 1;
        unsigned    bf9     : 1;
        unsigned    bf10    : 1;
    } ar_flags;
    int         *ar_next;
    int         *ar_patch;
    int         *ar_link;
    int         ar_time[2];
} actrec_rt;

typedef struct {
    int         *next;
    int         *prev;
    int         *func;
    char        type;
    char        ps_ip_level;
    char        ps_lockwait;
    char        data7;
    int         *data;
} proc_header;

typedef struct
{
    proc_header         data1;
    int*        data2;
    int*        ps_resume;
    int*        ps_ip;
    int*        ps_hook;
    unsigned int        data6;
} proc_state;

typedef struct
{
    int*          next;
    int*          prev;
    int*          func;
    char          type;
    char          ps_ip_level;
    char          ps_lockwait;
    char          flags;
} proc_state_reduced;

IMPORT_SYMBOL int g_process_reduced_regr;
#define prc_GetIpLevel(p) (g_process_reduced_regr ? ((proc_state_reduced *)p)->ps_ip_level : p->data1.ps_ip_level)
#define prc_SetIpLevel(p, l) if (g_process_reduced_regr) {((proc_state_reduced *)p)->ps_ip_level = l;} \
    else { p->data1.ps_ip_level = l; }
#define prc_GetIP(ps) (g_process_reduced_regr ? ((proc_state_reduced *)ps)->ps_ip : ps->ps_ip)
#define prc_GetResume(ps) (g_process_reduced_regr ? ((proc_state_reduced *)ps)->ps_resume : ps->ps_resume)
IMPORT_SYMBOL unsigned int g_psip_offset_diff;
IMPORT_SYMBOL unsigned int g_psresume_offset_diff;

/* TBD_PVHDL __thread attribute is problematic for porting */
/*IMPORT_SYMBOL __thread proc_state *cur_proc;*/
/*IMPORT_SYMBOL void set_cur_proc Proto((int tid, proc_state* cp));*/
IMPORT_SYMBOL proc_state *cur_proc;
IMPORT_SYMBOL int* ws_wait_stk;

IMPORT_SYMBOL void wt_TimeWait Proto((int thId, void *time));
IMPORT_SYMBOL int wt_TimedOut Proto((void));

/* The following section is VHPI related. We have here an enum type
   for the types of the parameters to foreign subprograms as well as
   the definition of a structure which will be populated by the
   generated C code to be used by VHPI to handle foreign subprograms */

typedef enum
{
    vhpiSigParam,
    vhpiVarParam,
    vhpiConstParam,
    vhpiFuncDecl,
    vhpiProcDecl

} vhpiParamTypesT;

typedef enum
{
    vhpiIn,
    vhpiOut,
    vhpiInout

} vhpiModeT;

typedef struct vhpiParam_s
{
    vhpiParamTypesT paramType;    /* parameter type */
    vhpiModeT paramMode;          /* parameter mode */
    int* inParamAddress;          /* parameter value address or repnode */
    int* outParamAddress;         /* parameter value address or repnode */

    /* parameters could be multi dimensional arrays. Therefore, we keep
     direction and bounds in an array of integer pointers */

    int** constraints;            /* parameter constraints */
    union
    {
        char* duName;             /* primary design unit to access defnode */
        void* defNode;            /* the subprogram or parameter defnode */
    } u;                          /* data value union */

    int offset;                   /* offset into the symbol table */
    int isPackage;                /* packages require special processing */

} vhpiParamT;

IMPORT_SYMBOL int vhpiInitializeSubprogram(int nParams,
                                           vhpiParamT* pParams, int subprogramId, char* attribute);
IMPORT_SYMBOL int vhpiCallSubprogram(int nParams,
                                     vhpiParamT* pParams, int subprogramId);
IMPORT_SYMBOL int vhpiInitializeAndCallSubprogram(int nParams,
                                                  vhpiParamT* pParams);

IMPORT_SYMBOL void (*cgInitCSubp(char const *foreign))();

typedef simtime_t vtime;
#define mk_ConvVtime(t) (*(vtime*)(t))

IMPORT_SYMBOL simtime_t *pvTimeMIN, *pvTimeMAX, *pvTimeZero;
IMPORT_SYMBOL int cgT64_IsOvf Proto((simtime_t *value));
IMPORT_SYMBOL int cgT64_IsNeg Proto((simtime_t *value));
IMPORT_SYMBOL int cgT64_IsZero Proto((simtime_t *value));
IMPORT_SYMBOL int cgT64_IsInt Proto((simtime_t *value));
IMPORT_SYMBOL int cgT64_DWToSigInt Proto((simtime_t *value));
IMPORT_SYMBOL void cgT64_SigIntToDW Proto((int ival, simtime_t *result));
IMPORT_SYMBOL void cgT64_Copy Proto((simtime_t *dest, simtime_t *src));
IMPORT_SYMBOL void cgT64_MakeNeg Proto((simtime_t *value));
IMPORT_SYMBOL void cgT64_MakePos Proto((simtime_t *value));
IMPORT_SYMBOL void cgT64_InvSig Proto((simtime_t *value));
IMPORT_SYMBOL void cgT64_Inc Proto((simtime_t *val));
IMPORT_SYMBOL void cgT64_Dec Proto((simtime_t *val));
IMPORT_SYMBOL void cgT64_SigAdd Proto((simtime_t *left, simtime_t *right, simtime_t *result));
IMPORT_SYMBOL void cgT64_SigSub Proto((simtime_t *left, simtime_t *right, simtime_t *result));
IMPORT_SYMBOL void cgT64_SigIntMul Proto((simtime_t *val, int ival, simtime_t *result));
IMPORT_SYMBOL void cgT64_SigIntDiv Proto((simtime_t *val, int ival, simtime_t *result));
IMPORT_SYMBOL void cgT64_RealConv Proto((vint64 *fval, simtime_t *result));
IMPORT_SYMBOL void cgT64_SigRealMul Proto((simtime_t *val, vint64 *fval, simtime_t *result));
IMPORT_SYMBOL void cgT64_SigRealDiv Proto((simtime_t *val, vint64 *fval, simtime_t *result));
IMPORT_SYMBOL void cgT64_SigDiv Proto((simtime_t *left, simtime_t *right, simtime_t *result));
IMPORT_SYMBOL int cgT64_EQ Proto((simtime_t *left, simtime_t *right));
IMPORT_SYMBOL int cgT64_NEQ Proto((simtime_t *left, simtime_t *right));
IMPORT_SYMBOL int cgT64_LT Proto((simtime_t *left, simtime_t *right));
IMPORT_SYMBOL int cgT64_LE Proto((simtime_t *left, simtime_t *right));

IMPORT_SYMBOL void cgT64_InitMIN Proto((simtime_t *value));
IMPORT_SYMBOL void cgT64_InitMAX Proto((simtime_t *value));

IMPORT_SYMBOL int *cg_m9_uu_add(), *cg_m9_ss_add(), *cg_m9_us_add(),
              *cg_m9_su_add(), *cg_m9_ui_add(), *cg_m9_iu_add(), *cg_m9_si_add(),
              *cg_m9_is_add(), *cg_m9_ub_add(), *cg_m9_bu_add(), *cg_m9_sb_add(),
              *cg_m9_bs_add(), *cg_m9_uu_sub(), *cg_m9_ss_sub(), *cg_m9_us_sub(),
              *cg_m9_su_sub(), *cg_m9_ui_sub(), *cg_m9_iu_sub(), *cg_m9_si_sub(),
              *cg_m9_is_sub(), *cg_m9_ub_sub(), *cg_m9_bu_sub(), *cg_m9_sb_sub(),
              *cg_m9_bs_sub(), *cg_m9_u_pos(), *cg_m9_s_neg(), *cg_m9_s_abs(),
              *cg_m9_uu_mul(), *cg_m9_ss_mul(), *cg_m9_us_mul(), *cg_m9_su_mul(),
              *cg_m9_u_shl(), *cg_m9_u_shr(), *cg_m9_s_shr(), *cg_m9_iu_cnv(),
              *cg_m9_uu_cnv(), *cg_m9_ss_cnv(), *cg_m9_bs_cnv(), *cg_m9_is_cnv(),
              *cg_m9_lv_to_bv(), *cg_m9_sen_ulv2lv(), *cg_bv_add(), *cg_bv_sub(),
              *cg_bv_itobv(), *cg_bv_neg(), *cg_bv_abs(), *cg_bv_ext(),
              *cg_bv_sxt(), *cg_m7_uu_add(), *cg_m7_ss_add(), *cg_m7_us_add(),
              *cg_m7_su_add(), *cg_m7_ui_add(), *cg_m7_iu_add(), *cg_m7_si_add(),
              *cg_m7_is_add(), *cg_m7_ub_add(), *cg_m7_bu_add(), *cg_m7_sb_add(),
              *cg_m7_bs_add(), *cg_m7_uu_sub(), *cg_m7_ss_sub(), *cg_m7_us_sub(),
              *cg_m7_su_sub(), *cg_m7_ui_sub(), *cg_m7_iu_sub(), *cg_m7_si_sub(),
              *cg_m7_is_sub(), *cg_m7_ub_sub(), *cg_m7_bu_sub(), *cg_m7_sb_sub(),
              *cg_m7_bs_sub(), *cg_m7_pos(), *cg_m7_s_neg(), *cg_m7_s_abs(),
              *cg_uu_mul(), *cg_ss_mul(), *cg_su_mul(), *cg_us_mul(),
              *cg_m7_iu_cnv(), *cg_m7_uu_cnv(), *cg_ss_cnv(), *cg_bs_cnv(),
              *cg_is_cnv(), *cg_m7_pos(), *cg_m7_s_neg(), *cg_m7_s_abs(),
              *cg_m7_uu_mul(), *cg_m7_ss_mul(), *cg_m7_su_mul(), *cg_m7_us_mul(),
              *cg_m7_u_shl(), *cg_m7_u_shr(), *cg_m7_s_shr(), *cg_m7_iu_cnv(),
              *cg_m7_uu_cnv(), *cg_m7_ss_cnv(), *cg_m7_bs_cnv(), *cg_m7_is_cnv(),
              *cg_m7_ii_cnv(),
              *cg_m7_bvtom7v(), *cg_m7_m7vtobv(), *cg_m7_m7v2busx(),
              *cg_m7_sen_m7v(), *cg_m9_u_pos(), *cg_m2_uu_gt(), *cg_m2_uu_ge(), *cg_m2_uu_lt(),
              *cg_m2_uu_le();

IMPORT_SYMBOL vint64 *cg_math_cmplx(), *cg_math_neg(), *cg_math_csqrt(),
              *cg_math_cc_add(), *cg_math_rc_add(), *cg_math_cr_add(), *cg_math_ir_exp(),
              *cg_math_fmax(),
              *cg_math_sign(), *cg_math_cabs(), *math_time_to_real_cnv(),
              *math_trunc(), *math_mod(), *math_realmax(), *math_realmin(),
              *math_log2(), *math_log10(), *math_log(),
              *math_arcsin(), *math_arccos(), *math_arctan(), *math_arctan2(),
              *math_arcsinh(), *math_arccosh(), *math_arctanh(),
              *math_get_principal_value(), *math_complex_abs(), *math_complex_polar_abs(),
              *math_complex_arg(), *math_complex_polar_arg(), *math_complex_polar_minus(),
              *math_complex_polar_conj(), *math_complex_sqrt(), *math_complex_polar_sqrt(),
              *math_complex_exp(), *math_complex_polar_exp(), *math_complex_log(),
              *math_complex_log2(), *math_complex_log10(), *math_complex_polar_log(),
              *math_complex_polar_log2(), *math_complex_polar_log10(), *math_complex_log_2(),
              *math_complex_polar_log_2(), *math_complex_sin(), *math_complex_polar_sin(),
              *math_complex_cos(), *math_complex_polar_cos(), *math_complex_sinh(),
              *math_complex_polar_sinh(), *math_complex_cosh(), *math_complex_polar_cosh(),
              *math_add_cp_cp(), *math_add_real_cp(), *math_add_cp_real(),
              *math_sub_cp_cp(), *math_sub_real_cp(), *math_sub_cp_real(),
              *math_mul_cp_cp(), *math_mul_real_cp(), *math_mul_cp_real(),
              *math_div_cp_cp(), *math_div_real_cp(), *math_div_cp_real();

IMPORT_SYMBOL byte *cg_m9_bs_add_byte  Proto((byte * v0, int *c0, byte v1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_bs_cnv_byte  Proto((byte * v0, int *c0, byte v1, int size, int thread_id));
IMPORT_SYMBOL int cg_m9_bsi_cnv_byte  Proto((byte i1, int thread_id));
IMPORT_SYMBOL byte *cg_m9_bs_sub_byte  Proto((byte * v0, int *c0, byte v1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_bu_add_byte  Proto((byte * v0, int *c0, byte v1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_bu_sub_byte  Proto((byte * v0, int *c0, byte v1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL int cg_m9_fun_buf3s_byte  Proto((byte strn, byte enable, byte v1, int thread_id));
IMPORT_SYMBOL int cg_m9_fun_buf3sl_byte  Proto((byte strn, byte enable, byte v1, int thread_id));
IMPORT_SYMBOL int cg_m9_fun_maj23_byte  Proto((byte v2, byte v1, byte v0, int thread_id));
IMPORT_SYMBOL int cg_m9_fun_mux2x1_byte  Proto((byte v1, byte sel, byte v0, int thread_id));
IMPORT_SYMBOL int cg_m9_fun_wiredx_byte  Proto((byte v1, byte v2, int thread_id));
IMPORT_SYMBOL int cg_m9_ii_cnv_byte  Proto((int v1, int thread_id));
IMPORT_SYMBOL byte *cg_m9_is_add_byte  Proto((byte * v0, int *c0, int v1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_is_cnv_byte  Proto((byte * v0, int *c0, int v1, int size, int thread_id));
IMPORT_SYMBOL int cg_m9_is_sml_byte  Proto((int v1, byte * v2, int *c2, int opcode, int thread_id));
IMPORT_SYMBOL byte *cg_m9_is_sub_byte  Proto((byte * v0, int *c0, int v1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_iu_add_byte  Proto((byte * v0, int *c0, int v1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_iu_cnv_byte  Proto((byte * v0, int *c0, int v1, int size, int thread_id));
IMPORT_SYMBOL int cg_m9_iu_sml_byte  Proto((int v1, byte * v2, int *c2, int opcode, int thread_id));
IMPORT_SYMBOL byte *cg_m9_iu_sub_byte  Proto((byte * v0, int *c0, int v1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL int cg_m9_lv_and_rdc_byte  Proto((byte * v1, int *c1, int opcode, int thread_id));
IMPORT_SYMBOL byte *cg_m9_lv_to_bv_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte vx, byte vz, byte vu, byte vdc, int xflag, int zflag, int uflag, int dcflag, int thread_id));
IMPORT_SYMBOL int cg_m9_m92bit_byte  Proto((byte v, byte vx, byte vz, byte vu, byte vdc, int xflag, int zflag, int uflag, int dcflag, int thread_id));
IMPORT_SYMBOL byte *cg_m9_s_abs_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int thread_id));
IMPORT_SYMBOL byte *cg_m9_sb_add_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte v2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_sb_sub_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte v2, int thread_id));
IMPORT_SYMBOL int cg_m9_sen_m9_byte  Proto((byte v, byte vz, byte vu, byte vdc, int thread_id));
IMPORT_SYMBOL byte *cg_m9_sen_ulv2lv_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte vz, byte vu, byte vdc, int thread_id));
IMPORT_SYMBOL byte *cg_m9_si_add_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int v2, int thread_id));
IMPORT_SYMBOL int cg_m9_si_cnv_byte  Proto((byte * v1, int *c1, int thread_id));
IMPORT_SYMBOL int cg_m9_si_sml_byte  Proto((byte * v1, int *c1, int v2, int opcode, int thread_id));
IMPORT_SYMBOL byte *cg_m9_si_sub_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int v2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_s_neg_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int thread_id));
IMPORT_SYMBOL byte *cg_m9_ss_add_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_ss_cnv_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int size, int thread_id));
IMPORT_SYMBOL byte *cg_m9_ss_cnv_il_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int size, int thread_id));
IMPORT_SYMBOL byte *cg_m9_s_shr_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_ss_mul_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL int cg_m9_ss_sml_byte  Proto((byte * v1, int *c1, byte * v2, int *c2, int opcode, int thread_id));
IMPORT_SYMBOL byte *cg_m9_ss_sub_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL int cg_m9_strn_map_byte  Proto((byte v1, int strn, int thread_id));
IMPORT_SYMBOL int cg_m9_strn_map_z_byte  Proto((byte v1, int strn, int thread_id));
IMPORT_SYMBOL byte *cg_m9_su_add_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_su_mul_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL int cg_m9_su_sml_byte  Proto((byte * v1, int *c1, byte * v2, int *c2, int opcode, int thread_id));
IMPORT_SYMBOL byte *cg_m9_su_sub_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_ub_add_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int v2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_ub_sub_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int v2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_ui_add_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int v2, int thread_id));
IMPORT_SYMBOL int cg_m9_ui_cnv_byte  Proto((byte * v1, int *c1, int thread_id));
IMPORT_SYMBOL int cg_m9_ui_sml_byte  Proto((register byte * v1, int *c1, register int v2, int opcode, int thread_id));
IMPORT_SYMBOL byte *cg_m9_ui_sub_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int v2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_u_pos_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int thread_id));
IMPORT_SYMBOL byte *cg_m9_us_add_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_u_shl_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_u_shr_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_us_mul_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL int cg_m9_us_sml_byte  Proto((byte * v1, int *c1, byte * v2, int *c2, int opcode, int thread_id));
IMPORT_SYMBOL byte *cg_m9_us_sub_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_uu_add_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_m9_uu_cnv_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int size, int thread_id));
IMPORT_SYMBOL byte *cg_m9_uu_cnv_il_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int size, int thread_id));
IMPORT_SYMBOL byte *cg_m9_uu_mul_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL int cg_m9_uu_sml_byte  Proto((byte * v1, int *c1, byte * v2, int *c2, int opcode, int thread_id));
IMPORT_SYMBOL byte *cg_m9_uu_sub_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL int cg_m9_ui_cnv_size_byte  Proto((byte * v1, register int size, int thread_id));
IMPORT_SYMBOL int cg_bv_bvtoi_byte  Proto((byte * v1, int *c1, int thread_id));
IMPORT_SYMBOL int cg_bv_sbvtoi_byte  Proto((byte * v1, int *c1, int thread_id));
IMPORT_SYMBOL byte *cg_bv_itobv_byte  Proto((byte * v0, int *c0, int v1, int size, int thread_id));
IMPORT_SYMBOL byte *cg_bv_add_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_bv_sub_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, byte * v2, int *c2, int thread_id));
IMPORT_SYMBOL byte *cg_bv_neg_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int thread_id));
IMPORT_SYMBOL byte *cg_bv_abs_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int thread_id));
IMPORT_SYMBOL byte *cg_bv_ext_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int size, int thread_id));
IMPORT_SYMBOL byte *cg_bv_sxt_byte  Proto((byte * v0, int *c0, byte * v1, int *c1, int size, int thread_id));
IMPORT_SYMBOL void vsim_bv_extend_byte  Proto((register byte * src, register byte * dest, register int ssize, register int dsize, int op));
IMPORT_SYMBOL void vsim_i2bv_sxt_byte  Proto((register int ival, register byte * dest, register int dsize));
IMPORT_SYMBOL void vsim_bv_arith_byte  Proto((register byte * src1, register byte * src2, register byte * dest, register int size, int op));
IMPORT_SYMBOL void vsim_bv_2scmpl_byte  Proto((register byte * src, register byte * dest, register int dsize));
IMPORT_SYMBOL void vsim_bv_cmpl_sxt_byte  Proto((register byte * src, register byte * dest, register int ssize, register int dsize));
IMPORT_SYMBOL void vsim_bv_abs_byte  Proto((register byte * src, register byte * dest, register int dsize));
IMPORT_SYMBOL int get_encoded_str_val_byte Proto((byte *src, int log_cardinality, int len));
IMPORT_SYMBOL void cgShift_byte Proto((byte *dst, byte const *src, int len, int v, int lf, int as, int rs));

IMPORT_SYMBOL void math_uniform();
IMPORT_SYMBOL int math_pol_eq(), math_pol_neq();

IMPORT_SYMBOL int *cg_m4_uu_add(), *cg_m4_ss_add(), *cg_m4_us_add(),
              *cg_m4_su_add(), *cg_m4_ui_add(), *cg_m4_iu_add(), *cg_m4_si_add(),
              *cg_m4_is_add(), *cg_m4_ub_add(), *cg_m4_bu_add(), *cg_m4_sb_add(),
              *cg_m4_bs_add(), *cg_m4_uu_sub(), *cg_m4_ss_sub(), *cg_m4_us_sub(),
              *cg_m4_su_sub(), *cg_m4_ui_sub(), *cg_m4_iu_sub(), *cg_m4_si_sub(),
              *cg_m4_is_sub(), *cg_m4_ub_sub(), *cg_m4_bu_sub(), *cg_m4_sb_sub(),
              *cg_m4_bs_sub(), *cg_m4_u_pos(), *cg_m4_s_neg(), *cg_m4_s_abs(),
              *cg_m4_uu_mul(), *cg_m4_ss_mul(), *cg_m4_us_mul(), *cg_m4_su_mul(),
              *cg_m4_u_shl(), *cg_m4_u_shr(), *cg_m4_s_shr(), *cg_m4_iu_cnv(),
              *cg_m4_uu_cnv(), *cg_m4_ss_cnv(), *cg_m4_bs_cnv(), *cg_m4_is_cnv(),
              *cg_m4_lv_to_bv(), *cg_m4_sen_ulv2lv(), *cg_bv_add(), *cg_bv_sub(),
              *cg_bv_itobv(), *cg_bv_neg(), *cg_bv_abs(), *cg_bv_ext(),
              *cg_bv_sxt(), *cg_uu_mul(), *cg_ss_mul(), *cg_su_mul(), *cg_us_mul(),
              *cg_ss_cnv(), *cg_bs_cnv(),
              *cg_is_cnv();

IMPORT_SYMBOL byte *numeric_nn_to_u_cnv_byte();
IMPORT_SYMBOL byte *numeric_uu_sub_byte();
IMPORT_SYMBOL byte *numeric_sl_to_01_byte();
IMPORT_SYMBOL byte *numeric_usl_to_01_byte();
IMPORT_SYMBOL byte *numeric_s_abs_byte();
IMPORT_SYMBOL byte *numeric_s_neg_byte();
IMPORT_SYMBOL byte *numeric_sn_resize_byte();
IMPORT_SYMBOL byte *numeric_un_resize_byte();
IMPORT_SYMBOL byte *numeric_in_to_s_cnv_byte();
IMPORT_SYMBOL byte *numeric_nn_to_u_cnv_byte();
IMPORT_SYMBOL byte *numeric_uu_add_byte();
IMPORT_SYMBOL byte *numeric_ss_add_byte();
IMPORT_SYMBOL byte *numeric_un_add_byte();
IMPORT_SYMBOL byte *numeric_nu_add_byte();
IMPORT_SYMBOL byte *numeric_is_add_byte();
IMPORT_SYMBOL byte *numeric_si_add_byte();
IMPORT_SYMBOL byte *numeric_uu_sub_byte();
IMPORT_SYMBOL byte *numeric_ss_sub_byte();
IMPORT_SYMBOL byte *numeric_un_sub_byte();
IMPORT_SYMBOL byte *numeric_nu_sub_byte();
IMPORT_SYMBOL byte *numeric_si_sub_byte();
IMPORT_SYMBOL byte *numeric_is_sub_byte();
IMPORT_SYMBOL byte *numeric_ss_mul_byte();
IMPORT_SYMBOL byte *numeric_uu_mul_byte();
IMPORT_SYMBOL byte *numeric_un_mul_byte();
IMPORT_SYMBOL byte *numeric_nu_mul_byte();
IMPORT_SYMBOL byte *numeric_si_mul_byte();
IMPORT_SYMBOL byte *numeric_is_mul_byte();
IMPORT_SYMBOL byte *numeric_un_shl_byte();
IMPORT_SYMBOL byte *numeric_un_shr_byte();
IMPORT_SYMBOL byte *numeric_sn_shl_byte();
IMPORT_SYMBOL byte *numeric_sn_shr_byte();
IMPORT_SYMBOL byte *numeric_un_rtl_byte();
IMPORT_SYMBOL byte *numeric_un_rtr_byte();
IMPORT_SYMBOL byte *numeric_sn_rtl_byte();
IMPORT_SYMBOL byte *numeric_sn_rtr_byte();
IMPORT_SYMBOL byte *numeric_ui_shl_byte();
IMPORT_SYMBOL byte *numeric_ui_shr_byte();
IMPORT_SYMBOL byte *numeric_si_shl_byte();
IMPORT_SYMBOL byte *numeric_si_shr_byte();
IMPORT_SYMBOL byte *numeric_ui_rtl_byte();
IMPORT_SYMBOL byte *numeric_ui_rtr_byte();
IMPORT_SYMBOL byte *numeric_si_rtl_byte();
IMPORT_SYMBOL byte *numeric_si_rtr_byte();
IMPORT_SYMBOL byte *numeric_uu_div_byte();
IMPORT_SYMBOL byte *numeric_ss_div_byte();
IMPORT_SYMBOL byte *numeric_un_div_byte();
IMPORT_SYMBOL byte *numeric_nu_div_byte();
IMPORT_SYMBOL byte *numeric_si_div_byte();
IMPORT_SYMBOL byte *numeric_is_div_byte();
IMPORT_SYMBOL byte *numeric_uu_rem_byte();
IMPORT_SYMBOL byte *numeric_ss_rem_byte();
IMPORT_SYMBOL byte *numeric_un_rem_byte();
IMPORT_SYMBOL byte *numeric_nu_rem_byte();
IMPORT_SYMBOL byte *numeric_si_rem_byte();
IMPORT_SYMBOL byte *numeric_is_rem_byte();
IMPORT_SYMBOL byte *numeric_uu_mod_byte();
IMPORT_SYMBOL byte *numeric_ss_mod_byte();
IMPORT_SYMBOL byte *numeric_un_mod_byte();
IMPORT_SYMBOL byte *numeric_nu_mod_byte();
IMPORT_SYMBOL byte *numeric_si_mod_byte();
IMPORT_SYMBOL byte *numeric_is_mod_byte();

IMPORT_SYMBOL int *numeric_s_abs(), *numeric_s_neg(), *numeric_uu_add(),
              *numeric_ss_add(),*numeric_un_add(),*numeric_nu_add(),*numeric_si_add(),
              *numeric_is_add(),*numeric_uu_sub(),*numeric_ss_sub(),*numeric_un_sub(),
              *numeric_nu_sub(),*numeric_si_sub(),*numeric_is_sub(),*numeric_uu_div(),
              *numeric_ss_div(),*numeric_un_div(),*numeric_nu_div(),*numeric_si_div(),
              *numeric_is_div(),*numeric_uu_rem(),*numeric_ss_rem(),*numeric_un_rem(),
              *numeric_nu_rem(),*numeric_si_rem(),*numeric_is_rem(),*numeric_uu_mod(),
              *numeric_ss_mod(),*numeric_un_mod(),*numeric_nu_mod(),*numeric_si_mod(),
              *numeric_is_mod(),numeric_uu_gt(),numeric_ss_gt(),numeric_un_gt(),
              numeric_nu_gt(),numeric_si_gt(),numeric_is_gt(),numeric_uu_lt(),
              numeric_ss_lt(),numeric_un_lt(),numeric_nu_lt(),numeric_si_lt(),
              numeric_is_lt(),numeric_uu_le(),numeric_ss_le(),numeric_un_le(),
              numeric_nu_le(),numeric_si_le(),numeric_is_le(),numeric_uu_ge(),
              numeric_ss_ge(),numeric_un_ge(),numeric_nu_ge(),numeric_si_ge(),
              numeric_is_ge(),numeric_uu_eq(),numeric_ss_eq(),numeric_un_eq(),
              numeric_nu_eq(),numeric_si_eq(),numeric_is_eq(),numeric_uu_neq(),
              numeric_ss_neq(),numeric_un_neq(),numeric_nu_neq(),numeric_si_neq(),
              numeric_is_neq(),*numeric_un_shl(),*numeric_un_shr(),*numeric_sn_shl(),
              *numeric_sn_shr(),*numeric_un_rtl(),*numeric_un_rtr(),*numeric_sn_rtl(),
              *numeric_sn_rtr(),*numeric_ui_shl(),*numeric_ui_shr(),*numeric_si_shl(),
              *numeric_si_shr(),*numeric_ui_rtl(),*numeric_ui_rtr(),*numeric_si_rtl(),
              *numeric_si_rtr(),*numeric_sn_resize(),*numeric_un_resize(),
              numeric_u_to_i_cnv(),
              numeric_s_to_i_cnv(),*numeric_nn_to_u_cnv(),*numeric_in_to_s_cnv(),
              *numeric_u_not(),*numeric_uu_and(),*numeric_uu_or(),*numeric_uu_nand(),
              *numeric_uu_nor(),*numeric_uu_xor(),*numeric_uu_xnor(),     *numeric_s_not(),
              *numeric_ss_and(),*numeric_ss_or(),*numeric_ss_nand(),*numeric_ss_nor(),
              *numeric_ss_xor(),*numeric_ss_xnor(),numeric_uu_std_match(),
              numeric_ss_std_match(),numeric_lvlv_std_match(),numeric_ulvulv_std_match(),
              numeric_ulul_std_match(),*numeric_uu_mul(),
              *numeric_ss_mul(),*numeric_un_mul(),*numeric_nu_mul(),*numeric_si_mul(),
              *numeric_is_mul(),*numeric_usl_to_01(), *numeric_sl_to_01();

IMPORT_SYMBOL int *numeric_4state_s_abs(), *numeric_4state_s_neg(),
              *numeric_4state_uu_add(),
              *numeric_4state_ss_add(),*numeric_4state_un_add(),*numeric_4state_nu_add(),
              *numeric_4state_si_add(),*numeric_4state_is_add(),*numeric_4state_uu_sub(),
              *numeric_4state_ss_sub(),*numeric_4state_un_sub(),*numeric_4state_nu_sub(),
              *numeric_4state_si_sub(),*numeric_4state_is_sub(),*numeric_4state_uu_div(),
              *numeric_4state_ss_div(),*numeric_4state_un_div(),*numeric_4state_nu_div(),
              *numeric_4state_si_div(),*numeric_4state_is_div(),*numeric_4state_uu_rem(),
              *numeric_4state_ss_rem(),*numeric_4state_un_rem(),*numeric_4state_nu_rem(),
              *numeric_4state_si_rem(),*numeric_4state_is_rem(),*numeric_4state_uu_mod(),
              *numeric_4state_ss_mod(),*numeric_4state_un_mod(),*numeric_4state_nu_mod(),
              *numeric_4state_si_mod(),*numeric_4state_is_mod(),numeric_4state_uu_gt(),
              numeric_4state_ss_gt(),numeric_4state_un_gt(),numeric_4state_nu_gt(),
              numeric_4state_si_gt(),numeric_4state_is_gt(),numeric_4state_uu_lt(),
              numeric_4state_ss_lt(),numeric_4state_un_lt(),numeric_4state_nu_lt(),
              numeric_4state_si_lt(),numeric_4state_is_lt(),numeric_4state_uu_le(),
              numeric_4state_ss_le(),numeric_4state_un_le(),
              numeric_4state_nu_le(),numeric_4state_si_le(),
              numeric_4state_is_le(),numeric_4state_uu_ge(),
              numeric_4state_ss_ge(),numeric_4state_un_ge(),numeric_4state_nu_ge(),
              numeric_4state_si_ge(),numeric_4state_is_ge(),numeric_4state_uu_eq(),
              numeric_4state_ss_eq(),numeric_4state_un_eq(),
              numeric_4state_nu_eq(),numeric_4state_si_eq(),numeric_4state_is_eq(),
              numeric_4state_uu_neq(),numeric_4state_ss_neq(),numeric_4state_un_neq(),
              numeric_4state_nu_neq(),numeric_4state_si_neq(),
              numeric_4state_is_neq(),*numeric_4state_un_shl(),*numeric_4state_un_shr(),
              *numeric_4state_sn_shl(),*numeric_4state_sn_shr(),
              *numeric_4state_un_rtl(),*numeric_4state_un_rtr(),*numeric_4state_sn_rtl(),
              *numeric_4state_sn_rtr(),*numeric_4state_ui_shl(),*numeric_4state_ui_shr(),
              *numeric_4state_si_shl(),*numeric_4state_si_shr(),*numeric_4state_ui_rtl(),
              *numeric_4state_ui_rtr(),*numeric_4state_si_rtl(),
              *numeric_4state_si_rtr(),*numeric_4state_sn_resize(),
              *numeric_4state_un_resize(),numeric_4state_u_to_i_cnv(),
              numeric_4state_s_to_i_cnv(),*numeric_4state_nn_to_u_cnv(),
              *numeric_4state_in_to_s_cnv(),
              *numeric_4state_u_not(),*numeric_4state_uu_and(),*numeric_4state_uu_or(),
              *numeric_4state_uu_nand(),*numeric_4state_uu_nor(),*numeric_4state_uu_xor(),
              *numeric_4state_uu_xnor(),*numeric_4state_s_not(),
              *numeric_4state_ss_and(),*numeric_4state_ss_or(),
              *numeric_4state_ss_nand(),*numeric_4state_ss_nor(),
              *numeric_4state_ss_xor(),*numeric_4state_ss_xnor(),
              numeric_4state_uu_std_match(),numeric_4state_ss_std_match(),
              numeric_4state_lvlv_std_match(),numeric_4state_ulvulv_std_match(),
              numeric_4state_ulul_std_match(),*numeric_4state_uu_mul(),
              *numeric_4state_ss_mul(),*numeric_4state_un_mul(),
              *numeric_4state_nu_mul(),*numeric_4state_si_mul(),
              *numeric_4state_is_mul(),*numeric_4state_usl_to_01(),
              *numeric_4state_sl_to_01();


IMPORT_SYMBOL void   cg_pc_link    Proto((void *, void *,       void *           ));
IMPORT_SYMBOL void   cg_pc_grab_i0 Proto((void *, int,          int              ));
IMPORT_SYMBOL void   cg_pc_grab_i1 Proto((void *, int *,        int,          int));
IMPORT_SYMBOL void   cg_pc_grab_t0 Proto((void *, simtime_t *, int              ));
IMPORT_SYMBOL void   cg_pc_grab_t1 Proto((void *, simtime_t *, simtime_t *, int));
IMPORT_SYMBOL void   cg_pc_grab_c  Proto((void *, int *,        int *,        int, int));
IMPORT_SYMBOL void   cg_pc_grab_si Proto((void *, long *, int, int, int, int, int, int));
IMPORT_SYMBOL void   cg_pc_grab_sc Proto((void *, long *, int, int, int*, int, int));
IMPORT_SYMBOL int    cg_pc_jam_i0  Proto((void *, int));
IMPORT_SYMBOL void   cg_pc_unlink  Proto((void *));
IMPORT_SYMBOL int    cg_pc_call    Proto((void *,void *,int *,int *));
IMPORT_SYMBOL int    cg_pc_callf_s Proto((void *,void *));
IMPORT_SYMBOL int   *cg_pc_callf_c Proto((void *,void *,int *,int *, int, int));

IMPORT_SYMBOL void   *wt_AddClockAction Proto((int *, int, int));
IMPORT_SYMBOL void    wt_AddDBSAction Proto((int *, int, void *, int));

IMPORT_SYMBOL int cg_contflag;
IMPORT_SYMBOL void   cg_unimplemented Proto((char *));

IMPORT_SYMBOL int* ctl_CurrentEventManager;
#define vn_GetCurrentEventManager() (ctl_CurrentEventManager)
#define simtime (*(simtime_t*)ctl_CurrentEventManager)

/* Copied from vsui/shvar.[ch] */
typedef struct { char * filename; char * fullpathfilename; int linenum; } cgFileInfo_t;
IMPORT_SYMBOL cgFileInfo_t cgFileInfo;
#define cgSetLocn(file, fullpath_file, line) { cgFileInfo.filename=(file); cgFileInfo.fullpathfilename=(fullpath_file); cgFileInfo.linenum=(line); }
#define RG_TO 1
#define cg_st_clen(l,r,d) \
    (((d)==RG_TO) ? (((r)-(l)) < 0) ? 0: ((r)-(l))+1 : (((l)-(r)) < 0) ? 0 : ((l)-(r))+1)
#define cg_st_clen1(l,r) \
    ((((r)-(l)) < 0) ? 0 : ((r)-(l))+1)
#define cgClctSize1Dim(drl,nsize) ( nsize*cg_st_clen(drl[3], drl[2], drl[1]) )
#define cgClctSize1Dim1(drl) ( cg_st_clen(drl[3], drl[2], drl[1]) )
#define cgCompactLen(size) (((size) + 31) >> 5)
typedef unsigned long Bn;
typedef unsigned long *Bnp;
typedef long SBn;
IMPORT_SYMBOL int afterElabGlobal;
IMPORT_SYMBOL void *sc_mem_malloc(size_t);
IMPORT_SYMBOL int* dbs_ClockActionRef();
IMPORT_SYMBOL int* dbs_AddClockAction();
IMPORT_SYMBOL int* dbs_AddResetFlopAction();
IMPORT_SYMBOL int* dbs_AddResetLatchAction();
IMPORT_SYMBOL int* dbs_AddInvResetLatchAction();
IMPORT_SYMBOL int* dbs_AddInvResetFlopAction();
IMPORT_SYMBOL int* dbs_AddInvSetResetFlopAction();
IMPORT_SYMBOL int* dbs_AddSetResetFlopAction();
IMPORT_SYMBOL int* dbs_AddInvSetResetLatchAction();
IMPORT_SYMBOL int* dbs_AddSetResetLatchAction();
IMPORT_SYMBOL void sp_mem_write_element_index();
IMPORT_SYMBOL void sp_mem_read_element_index();
IMPORT_SYMBOL void icpy_spmem_lhs();
IMPORT_SYMBOL void icpy_spmem_rhs();
IMPORT_SYMBOL void icpy_spmem_lhs_rhs();
IMPORT_SYMBOL void sp_mem_read_write_elements();
IMPORT_SYMBOL int sp_mem_read_scalar();
IMPORT_SYMBOL void sp_mem_write_element_index_index();
IMPORT_SYMBOL void SPCopyFromVirtualMem();
IMPORT_SYMBOL void line_buffer_list_insert(void **, long *);
IMPORT_SYMBOL void line_buffer_list_delete(void **, long);
IMPORT_SYMBOL void line_buffer_list_delete_free(void **, long);
IMPORT_SYMBOL void line_buffer_list_free(void **);
IMPORT_SYMBOL int* spalloc(int, int);
IMPORT_SYMBOL int* sqalloc(int, int);
IMPORT_SYMBOL int *cg_m9_ss_cnv_il(int *, int *, int *, int *, int, int);
IMPORT_SYMBOL int *cg_m9_uu_cnv_il(int *, int *, int *, int *, int, int);
IMPORT_SYMBOL void vsr_m9_ui_cnv(void*, int);
IMPORT_SYMBOL void vsr_m9_si_cnv(void*, int);
IMPORT_SYMBOL void vsr_patch_defnode_type(void*);
IMPORT_SYMBOL  long tio_write_int(long* av, int *addr, int j, int f, int thId);
IMPORT_SYMBOL  long tio_write_real(long* av, int *addr, int j, int f, long x, int thId);
IMPORT_SYMBOL  long tio_write_time_shell(long* av, int *addr, int j, int f, long x, int thId);
IMPORT_SYMBOL  long tio_write_boolean(long* av, int *addr, int j, int f, int thId);
IMPORT_SYMBOL  long tio_write_bit(long* av, int *addr, int j, int f, int thId);
IMPORT_SYMBOL  long tio_write_bit_vec(long* av, int len, int *addr, int j, int f, int thId);
IMPORT_SYMBOL  long tio_write_bit_vec_2state(long av, int len, int *addr, int j, int f, int
                                             thId);
IMPORT_SYMBOL  long tio_write_char(long* av, int *addr, int j, int f, int thId);
IMPORT_SYMBOL  long tio_write_string(long* av, int len, int *addr, int j, int f, int thId);
IMPORT_SYMBOL  long  tio_rline_il(int* vfd, long* av, int thId);
IMPORT_SYMBOL  long  tio_wline_il(int* vfd, long* av, int thId);
IMPORT_SYMBOL  void *wt_CreateDynamicWait Proto((int, int));
IMPORT_SYMBOL  long sp_mem_read_value_il(long *s_ip, long src_index, long length);
IMPORT_SYMBOL  long sp_mem_read_gs_value_il(long *s_ip, long s_index, long s_size, long length, long sp_mem, int is_array);
IMPORT_SYMBOL  long mathbi_complex_sqrt_il(int nouse, int* vec_info,int op, long aVint1, long rVint);
int ilcg_idx_check(int is_constraint_check, int is_subtype_check, int idx, int dir, int lb, int rb, char *file, char *full_file, int line);
#ifdef VCS_64BIT
IMPORT_SYMBOL long g_minus_one;
#endif
IMPORT_SYMBOL unsigned* gEventBitVec;
IMPORT_SYMBOL unsigned* gBitVecForNextCycleEvent;
IMPORT_SYMBOL unsigned int gIsEventForNextCycle;
#define GBV_UNIT_SIZE 5  /*  32 bit */
#define GBV_UNIT_MASK (0x1F)  /*  32 bit */

IMPORT_SYMBOL void MOP_cgFltAb Proto((double *pd, vint64 *v));
IMPORT_SYMBOL void MOP_cgFltRz Proto((vint64 *v, double *pd));
IMPORT_SYMBOL void MOP_cgTWriteC Proto((long *L, long v, long j, long f,
                                        long x, long t, long l));
IMPORT_SYMBOL void MOP_cgTWriteS Proto((long *L, long v, long j, long f,
                                        long x, long t, long l));
IMPORT_SYMBOL void MOP_cgTRead Proto((long *L, long v, int* g, int t, int l,
                                      long a, long b));
IMPORT_SYMBOL void MOP_cgWriteLine Proto((long f, long *L));
IMPORT_SYMBOL void MOP_cgReadLine Proto((long f, long *L));
IMPORT_SYMBOL int MOP_cg_st_clen Proto((int l, int r, int d));
IMPORT_SYMBOL int MOP_cgClctSize1Dim Proto((int *drl, int nsize));
IMPORT_SYMBOL void MOP_cgWriteC Proto((int f, char * v, int l));
IMPORT_SYMBOL void MOP_cgRead3 Proto((int f, char *v, int *l, int s, int li));
IMPORT_SYMBOL void MOP_cgForcedFree Proto((long *i,int l, char *f));
IMPORT_SYMBOL void MOP_cgLineFreeOpt Proto((int *i));
IMPORT_SYMBOL void MOP_cgFileClose Proto((int *f));
IMPORT_SYMBOL void MOP_cgRead Proto((long f,long v,long l));
IMPORT_SYMBOL int *MOP_cgMap Proto((int *i, int l, char *f));
IMPORT_SYMBOL void MOP_cgSetLocn Proto((char *file, char *fullpath_file,
                                        int line));
IMPORT_SYMBOL int MOP_cg_m9_strn_map Proto((int i, int s, int op));
IMPORT_SYMBOL int MOP_cg_m9_strn_map_z Proto((int i, int s, int op));
IMPORT_SYMBOL int MOP_cgErr_param1 Proto((char* s1, char* s2, int i1, char* s3,
                                          int i2, int i3));

/*sn runtime header*/
IMPORT_SYMBOL void sn_Subp_ind_node Proto((void*, int, int, void*, void*, int));
IMPORT_SYMBOL void sn_Subp_ind_value Proto((void*, void*, int));
IMPORT_SYMBOL void sn_Subp_wait_add Proto((int, void*, int, int, int, int));
IMPORT_SYMBOL void sn_Subp_wait_del Proto((int, void*));
IMPORT_SYMBOL void sn_Subp_write_0_c1 Proto((int, void*, char, void*, int));
IMPORT_SYMBOL void sn_Subp_write_0_c4 Proto((int, void*, int, void*, int));
IMPORT_SYMBOL void sn_Subp_write_0_c8 Proto((int, void*, void*, void*, int));
IMPORT_SYMBOL void sn_Subp_write_0_cc Proto((int, void*, void*, void*, int, int));
IMPORT_SYMBOL void sn_Subp_write_0_o1 Proto((int, void*, char, void*, int, int));
IMPORT_SYMBOL void sn_Subp_write_0_o4 Proto((int, void*, int, void*, int, int));
IMPORT_SYMBOL void sn_Subp_write_d_s1 Proto((int, void*, void*, int, char));
IMPORT_SYMBOL void sn_Subp_write_d_s4 Proto((int, void*, void*, int, int));
IMPORT_SYMBOL void sn_Subp_write_D_s1 Proto((int, void*, void*, int, char, int, int, int));
IMPORT_SYMBOL void sn_Subp_write_D_s4 Proto((int, void*, void*, int, int, int, int, int));
IMPORT_SYMBOL void sn_Subp_write_D_cc Proto((int, void*, void*, int, int, char*, int, int, int));
IMPORT_SYMBOL void sn_Subp_write_D_o1 Proto((int, void*, void*, int, int, char, int, int, int));
IMPORT_SYMBOL void sn_Subp_write_D_o4 Proto((int, void*, void*, int, int, int,  int, int, int));
IMPORT_SYMBOL void sn_Driver_write_0_s1 Proto((int, void*, char, void*));
IMPORT_SYMBOL void sn_Driver_write_0_s4 Proto((int, void*, int, void*));
IMPORT_SYMBOL void sn_Driver_write_0_s8 Proto((int, void*, void*, void*));
IMPORT_SYMBOL void sn_Driver_write_0_fc Proto((int, void*, void*, void*, int));
IMPORT_SYMBOL void sn_Driver_write_0_fo1 Proto((int, void*, char, void*, int));
IMPORT_SYMBOL void sn_Driver_write_0_fo4 Proto((int, void*, int , void*, int));
IMPORT_SYMBOL void sn_Driver_write_0_c1 Proto((int, void*, char, void*, int));
IMPORT_SYMBOL void sn_Driver_write_0_c4 Proto((int, void*, int, void*, int));
IMPORT_SYMBOL void sn_Driver_write_0_c8 Proto((int, void*, void*, void*, int));
IMPORT_SYMBOL void sn_Driver_write_0_cc Proto((int, void*, void*, void*, int, int));
IMPORT_SYMBOL void sn_Driver_write_0_co1 Proto((int, void*, char, void*, int, int));
IMPORT_SYMBOL void sn_Driver_write_0_co4 Proto((int, void*, int,  void*, int, int));
IMPORT_SYMBOL void sn_Driver_write_d_s1 Proto((int, void*, void*, int, char));
IMPORT_SYMBOL void sn_Driver_write_d_s4 Proto((int, void*, void*, int, int));
IMPORT_SYMBOL void sn_Driver_write_D_s1 Proto((int, void*, void*, int, char, int, int, int));
IMPORT_SYMBOL void sn_Driver_write_D_s4 Proto((int, void*, void*, int, int, int, int, int));
IMPORT_SYMBOL void sn_Driver_write_D_cc Proto((int, void*, void*, int ,int, char*, int, int, int));
IMPORT_SYMBOL void sn_Driver_write_D_o1 Proto((int, void*, void*, int, int, char, int, int, int));
IMPORT_SYMBOL void sn_Driver_write_D_o4 Proto((int, void*, void*, int, int, int, int, int, int));
IMPORT_SYMBOL void sn_Driver_sched_0_cc Proto((int, void*, void*, int, int));
IMPORT_SYMBOL void sn_Driver_sched_0_fc Proto((int, void*, void*, int));
IMPORT_SYMBOL void sn_Wait_add Proto((int, void*, int, int, int, int));
IMPORT_SYMBOL void sn_Wait_begin Proto((int, int, int, int));
IMPORT_SYMBOL void* sn_Wait_end Proto((int));
IMPORT_SYMBOL void sn_Wait_enable Proto((int, void*));
IMPORT_SYMBOL void sn_Wait_disable Proto((int, void*));
IMPORT_SYMBOL int sn_aread_event_s Proto((void*));
IMPORT_SYMBOL int sn_aread_edge_s Proto((void*, int));
IMPORT_SYMBOL int sn_aread_edge_cs Proto((void*, int, int));
IMPORT_SYMBOL int sn_aread_rf_s Proto((void*, int));
IMPORT_SYMBOL int sn_aread_rf_cs Proto((void*, int, int));
IMPORT_SYMBOL int sn_aread_active_s Proto((void*));
IMPORT_SYMBOL int sn_aread_last_active_s Proto((void*, void*));
IMPORT_SYMBOL int sn_aread_last_event_s Proto((void*, void*));
IMPORT_SYMBOL int sn_aread_last_value_s Proto((void*, void*, int));
IMPORT_SYMBOL int sn_aread_cs Proto((void*, void*, int, int, int));
IMPORT_SYMBOL int sn_aread_cs_lv Proto((void*, void*, int, int));
IMPORT_SYMBOL int sn_aread_cs_sv Proto((void*, void*, int, int));
IMPORT_SYMBOL int sn_aread_cs_pv Proto((void*, void*, void*, int, int));
IMPORT_SYMBOL int sn_aread_cc Proto((int, void*, void*, void*, int, int, int));
IMPORT_SYMBOL int sn_Subp_aread_cs Proto((void*, void*, int, int, int));
IMPORT_SYMBOL int sn_Subp_aread_edge_cs Proto((void*, int, int));
IMPORT_SYMBOL int sn_Subp_aread_rf_cs Proto((void*, int, int));
IMPORT_SYMBOL int sn_Subp_aread_cs_lv Proto((void*, void*, int, int));
IMPORT_SYMBOL int sn_Subp_aread_cs_sv Proto((void*, void*, int, int));
IMPORT_SYMBOL int sn_Subp_aread_cs_pv Proto((void*, void*, void*, int, int));
IMPORT_SYMBOL int sn_Subp_aread_cc Proto((int, void*, void*, void*, int, int, int));
IMPORT_SYMBOL int sn_disconnect Proto((void*, void*, int, int));

IMPORT_SYMBOL int get_xprop_on(int, int, int);
IMPORT_SYMBOL int is_xprop_on(int);
IMPORT_SYMBOL int is_xprop_ffdatacheck_on(int);
IMPORT_SYMBOL int xbool_is_true(int, int);
IMPORT_SYMBOL int xbool_is_false(int, int);
IMPORT_SYMBOL int xbool_is_x(int, int);
IMPORT_SYMBOL int merge_integer(int, int, int);
IMPORT_SYMBOL int merge_xboolean(int, int, int, int);
IMPORT_SYMBOL int merge_std_logic(int, int, int);
IMPORT_SYMBOL void* merge_std_logic_vector(int, void*, void*, void*, void*, void*, void*);
IMPORT_SYMBOL int merge_enum(int, int, int);
IMPORT_SYMBOL int xprop_case_match_stdl_v(int, void*, void*, void*, void*, void*, void*, void*, int, void*, void*, void*, int);
IMPORT_SYMBOL int xprop_case_match_enum_v(int, void*, void*, void*, void*, void*, void*, void*, int, void*, void*, void*, int);
IMPORT_SYMBOL int xprop_case_match_bool_s(int, void*, char, void*, void*, void*, void*, int, void*, void*, void*, int);
IMPORT_SYMBOL int xprop_case_match_stdl_s(int, void*, char, void*, void*, void*, void*, int, void*, void*, void*, int);
IMPORT_SYMBOL int xprop_case_match_enum_s(int, void*, char, void*, void*, void*, void*, int, void*, void*, void*, int);
IMPORT_SYMBOL int xprop_case_match_int_s(int, void*, int, void*, void*, void*, void*, int, void*, void*, void*, int);
IMPORT_SYMBOL int xeq_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xeq_num_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xeq_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xeq_num_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xeq_unsigned_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xeq_signed_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xeq_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xeq_num_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xeq_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xeq_num_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xeq_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xeq_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xeq_num_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xne_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xne_num_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xne_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xne_num_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xne_unsigned_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xne_signed_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xne_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xne_num_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xne_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xne_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xne_num_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xne_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xne_num_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xlt_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xlt_num_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xlt_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xlt_num_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xlt_unsigned_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xlt_signed_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xlt_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xlt_num_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xlt_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xlt_num_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xlt_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xlt_num_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xlt_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xlt_num_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xle_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xle_num_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xle_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xle_num_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xle_unsigned_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xle_signed_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xle_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xle_num_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xle_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xle_num_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xle_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xle_num_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xle_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xle_num_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xgt_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xgt_num_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xgt_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xgt_num_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xgt_unsigned_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xgt_signed_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xgt_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xgt_num_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xgt_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xgt_num_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xgt_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xgt_num_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xgt_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xgt_num_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xge_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xge_num_unsigned_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xge_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xge_num_signed_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xge_unsigned_signed(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xge_signed_unsigned(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xge_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xge_num_unsigned_int(int, void*, void*, int);
IMPORT_SYMBOL int xge_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xge_num_int_unsigned(int, int, void*, void*);
IMPORT_SYMBOL int xge_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xge_num_signed_int(int, void*, void*, int);
IMPORT_SYMBOL int xge_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xge_num_int_signed(int, int, void*, void*);
IMPORT_SYMBOL int xprop_eq_enum_enum(int, int, int);
IMPORT_SYMBOL int xprop_ne_enum_enum(int, int, int);
IMPORT_SYMBOL int xprop_lt_enum_enum(int, int, int);
IMPORT_SYMBOL int xprop_le_enum_enum(int, int, int);
IMPORT_SYMBOL int xprop_gt_enum_enum(int, int, int);
IMPORT_SYMBOL int xprop_ge_enum_enum(int, int, int);
IMPORT_SYMBOL int xprop_eq_int_int(int, int, int);
IMPORT_SYMBOL int xprop_ne_int_int(int, int, int);
IMPORT_SYMBOL int xprop_lt_int_int(int, int, int);
IMPORT_SYMBOL int xprop_le_int_int(int, int, int);
IMPORT_SYMBOL int xprop_gt_int_int(int, int, int);
IMPORT_SYMBOL int xprop_ge_int_int(int, int, int);
IMPORT_SYMBOL int xprop_abs_int(int, int);
IMPORT_SYMBOL int xprop_sub_int(int, int);
IMPORT_SYMBOL int xprop_add_int_int(int, int, int);
IMPORT_SYMBOL int xprop_sub_int_int(int, int, int);
IMPORT_SYMBOL int xprop_mul_int_int(int, int, int);
IMPORT_SYMBOL int xprop_div_int_int(int, int, int);
IMPORT_SYMBOL int xprop_rem_int_int(int, int, int);
IMPORT_SYMBOL int xprop_mod_int_int(int, int, int);
IMPORT_SYMBOL int xprop_exp_int_int(int, int, int);
IMPORT_SYMBOL int xprop_num_s_to_i(int, void*, void*);
IMPORT_SYMBOL int xprop_num_u_to_i(int, void*, void*);
IMPORT_SYMBOL void* xprop_num_i_to_u(int, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_num_i_to_s(int, void*, void*, int, int);
IMPORT_SYMBOL int xprop_arith_u_to_i(int, void*, void*);
IMPORT_SYMBOL int xprop_arith_s_to_i(int, void*, void*);
IMPORT_SYMBOL int xprop_arith_stdul_to_i(int, void*, void*);
IMPORT_SYMBOL void* xprop_arith_i_to_u(int, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_arith_i_to_s(int, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_arith_i_to_slv(int, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_cg_m9_iu_cnv_byte(byte *, void*, int, int, int);
IMPORT_SYMBOL void* xprop_cg_m9_is_cnv_byte(byte *, void*, int, int, int);
IMPORT_SYMBOL void* xprop_cg_m9_iu_cnv(void*, void*, int, int, int);
IMPORT_SYMBOL void* xprop_cg_m9_is_cnv(void*, void*, int, int, int);
IMPORT_SYMBOL void* xprop_arith_add_ui(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_arith_add_iu(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_arith_add_si(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_arith_add_is(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_arith_sub_ui(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_arith_sub_iu(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_arith_sub_si(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_arith_sub_is(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_add_un(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_add_nu(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_add_is(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_add_si(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_sub_un(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_sub_nu(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_sub_is(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_sub_si(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_div_un(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_div_nu(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_div_is(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_div_si(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_mul_un(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_mul_nu(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_mul_is(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_mul_si(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_rem_un(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_rem_nu(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_rem_is(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_rem_si(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_mod_un(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_num_mod_nu(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_mod_is(int, void*, void*, int, void*, void*);
IMPORT_SYMBOL void* xprop_num_mod_si(int, void*, void*, void*, void*, int);
IMPORT_SYMBOL void* xprop_numeric_un_shl_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_un_shr_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_sn_shl_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_sn_shr_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_un_rtl_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_un_rtr_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_sn_rtl_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_sn_rtr_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_ui_shl_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_ui_shr_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_si_shl_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_si_shr_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_ui_rtl_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_ui_rtr_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_si_rtl_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_si_rtr_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_sn_resize_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL void* xprop_numeric_un_resize_byte(void*, void*, void*, void*, int, int);
IMPORT_SYMBOL int xeq_stdlv_stdlv(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xne_stdlv_stdlv(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xlt_stdlv_stdlv(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xle_stdlv_stdlv(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xgt_stdlv_stdlv(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xgt_stdlv_stdlv(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xge_stdlv_stdlv(int, void*, void*, void*, void*);
IMPORT_SYMBOL int xpropRisingEdge(int, void*, void*, int, int);
IMPORT_SYMBOL int xpropPosEdge(int, void*, void*, int, int);
IMPORT_SYMBOL int xpropFallingEdge(int, void*, void*, int, int);
IMPORT_SYMBOL int xpropNegEdge(int, void*, void*, int, int);
IMPORT_SYMBOL int xORsubst(int, int, int);
IMPORT_SYMBOL int xANDsubst(int, int, int);
IMPORT_SYMBOL int set_x_prop(int, void*, int);
IMPORT_SYMBOL int is_xprop_active(int);
IMPORT_SYMBOL int report_enum_cast(int, void*);
IMPORT_SYMBOL int report_ffdatacheck_severity(int, void*);
IMPORT_SYMBOL int report_ffdatacheck(int, void*, int);
IMPORT_SYMBOL int xprop_assert_on(int, void*, int);
IMPORT_SYMBOL int xprop_assert_off(int, void*, int);
IMPORT_SYMBOL int xprop_assert_warn(int, void*, int);
IMPORT_SYMBOL int xprop_assert_fatal(int, void*, int);
