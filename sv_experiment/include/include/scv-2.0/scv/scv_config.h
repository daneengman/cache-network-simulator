/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */

/*
 * The following code is derived, directly or indirectly, from the SystemC
 * source code Copyright (c) 1996-2002 by all Contributors.
 * All Rights reserved.
 *
 * The contents of this file are subject to the restrictions and limitations
 * set forth in the SystemC Open Source License Version 2.3 (the "License");
 * You may not use this file except in compliance with such restrictions and
 * limitations. You may obtain instructions on how to receive a copy of the
 * License at http://www.systemc.org/. Software distributed by Contributors
 * under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
 * ANY KIND, either express or implied. See the License for the specific
 * language governing rights and limitations under the License.
 */

#ifdef VCS64_FLAG
/* Define if we're on Linux/x86_64 */
#define ARCH_IS_X86_64 /**/
#else
/* Define if we're on Linux/i386 */
#define ARCH_IS_X86 /**/
#endif

/* Define to 1 if you have the <a.out.h> header file. */
/* #undef HAVE_A_OUT_H */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* found Dl_info in dlfcn.h */
/* #undef HAVE_DL_INFO */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `dl' library (-ldl). */
#define HAVE_LIBDL 1

/* Define to 1 if you have the `dld' library (-ldld). */
/* #undef HAVE_LIBDLD */

/* Define to 1 if you have the <libgen.h> header file. */
/* #undef HAVE_LIBGEN_H */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stddef.h> header file. */
/* #undef HAVE_STDDEF_H */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/frame.h> header file. */
/* #undef HAVE_SYS_FRAME_H */

/* Define to 1 if you have the <sys/link.h> header file. */
/* #undef HAVE_SYS_LINK_H */

/* Define to 1 if you have the <sys/regset.h> header file. */
/* #undef HAVE_SYS_REGSET_H */

/* Define to 1 if you have the <sys/reg.h> header file. */
/* #undef HAVE_SYS_REG_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <ucontext.h> header file. */
/* #undef HAVE_UCONTEXT_H */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if we're on the HP-UX 11 */
/* #undef HP_THREAD_SAFE */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "scv"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "SCV"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "SCV 2.0.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "scv"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.0.0"

/* Define if we're on the HP-UX 11 */
/* #undef RWSTD_MULTI_THREAD */

/* Define if we're on the HP-UX 11 */
/* #undef RW_MULTI_THREAD */

/* Define version of SystemC linked with: VRRRPPP where
   V=Version,RRR=Pevision,PPP=Patchlevel */
#define SCV_SC_VERSION 2000001

/* Define if <iostream.h> should be included instead of <iostream> */
/* #undef SCV_USE_IOSTREAM_H */

/* A string that contains the shared library extention (e.g. .so or .sl) */
/* #undef SHLIB_EXT */

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#ifdef VCS64_FLAG
#define SIZEOF_LONG 8
#else
#define SIZEOF_LONG 4
#endif

/* The size of `void *', as computed by sizeof. */
#ifdef VCS64_FLAG
#define SIZEOF_VOID_P 8
#else
#define SIZEOF_VOID_P 4
#endif

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* the full canonical system: cpu, vendor, os */
#ifdef VCS64_FLAG
#define TARGET "x86_64-unknown-linux-gnu"
#else
#define TARGET "i686-pc-linux-gnu"
#endif

/* Version number of package */
#define VERSION "2.0.0"

/* Define if we're on the HP-UX 11 */
/* #undef _HPUX_SOURCE */

/* Define if we're on the HP-UX 11 */
/* #undef _POSIX_C_SOURCE */

/* Define if we're on the HP-UX 11 */
/* #undef _REENTRANT */

/* Define if sc_report should be used instead of internal scv_report */
/* #undef _SCV_USE_SC_REPORT */

/* Define if we're on the HP-UX 11 */
/* #undef _THREAD_SAFE */

/* Define if an operator== should be defined for each operator!= */
/* #undef _USE_EXPLICIT_NEQ */

/* Define if we use gcc version = 3.2 */
/* #undef _USE_FMTFLAGS_TYPE */

/* Define if we use gcc version = 3.2 */
#define _USE_FRIEND_FOR_EQUAL /**/

/* Define if we use gcc version < 3.4 */
/* #undef _USE_HASH_MAP */

/* Define if we use gcc */
#define _USE_PADDING_ON_STRUCTS /**/

/* Define if "cout << ull" is correctly supported */
/* #undef _USE_UINT64_WRITE */

/* Define if we're on the HP-UX 11 */
/* #undef __HPACC_THREAD_SAFE_RB_TREE */

/* Define if we're on the HP-UX 11 */
/* #undef hp_hpux11 */


#ifdef __cplusplus

/* cc on HPUX seems to define this automatically so avoid redefinition warnings by */
/* conditionally defining it. */
/* #undef _HPUX_SOURCE */

#if defined (__SUNPRO_CC)
#include <list>
#include <map>
#include <string>
#endif

/* HP-UX's aCC doesn't have std defined until it sees a std lib header file */
/* (unlike g++ and SunWorks CC.) */
/* So define it here empty.  Namespaces are extensible, so this is harmless. */
namespace std {}
using namespace std;

#ifdef DELETE
/* #undef DELETE */
#endif
#ifdef ERROR
/* #undef ERROR */
#endif

#endif // __cplusplus

#if defined (__SUNPRO_CC)
  using std::list;
  using std::pair;
  using std::map;
  using std::less;
  using std::string;
  using std::equal_to;
#endif

#if defined(_MSC_VER)
# define _USE_FMTFLAGS_TYPE
# define _USE_FRIEND_FOR_EQUAL /**/
# define _USE_EXPLICIT_NEQ
# define SCV_SC_VERSION 2000001
# define HAVE_STDDEF_H
#endif

#undef PACKAGE