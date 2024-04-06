#ifndef VSS_EXTERN_H
#define VSS_EXTERN_H

#ifdef Synopsys_Win32
#define EXPORT_SYMBOL __declspec(dllexport)
#define IMPORT_SYMBOL __declspec(dllimport)
#define EXPORT_SYMBOL_STR "__declspec(dllexport) "
#define IMPORT_SYMBOL_STR "__declspec(dllimport) "
#else
#define EXPORT_SYMBOL /**/
#define IMPORT_SYMBOL extern
#define EXPORT_SYMBOL_STR ""
#define IMPORT_SYMBOL_STR ""
#endif

#endif
