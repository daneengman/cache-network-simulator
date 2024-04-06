// *********************************************************************
// *              Copyright (c) 2005-2010 Synopsys, Inc.               *
// *                                                                   *
// * This software and the associated documentation are confidential   *
// * and proprietary to Synopsys, Inc. Your use or disclosure of this  *
// * software is subject to the terms and conditions of a written      *
// * license agreement between you, or your company, and Synopsys, Inc.*
// *********************************************************************/


#ifndef _TLI_GLOBALGENERIC_CLASS_INFO_H
#define _TLI_GLOBALGENERIC_CLASS_INFO_H

//  This will be in files provided by VCS
#include <string>
#include <map>

#define TLI_REGISTER_ID(x,y) tli_global_export_id(x, typeid(y).name(), y, __FILE__, __LINE__)
#define TLI_UNREGISTER_ID(x)   tli_global_delete_id(x)

typedef struct tli_global_struct_type_info {
    void        *ptr;
    std::string tName;
    std::string file;
    std::string line;
} tli_global_struct_type_info;

typedef std::map<std::string, tli_global_struct_type_info*> tli_global_struct_type_info_table;

void                          tli_global_export_id(const char*, const char*, void* p,
                                                   const char*, long);
void                          tli_global_delete_id(const char*);
tli_global_struct_type_info* tli_global_get_struct_info(const char*);

const char *demangle(const char *s);

#endif // _TLI_GLOBALGENERIC_CLASS_INFO_H
