
//----------------------------------------------
// C++ file
//----------------------------------------------
#include "stdio.h"
#include "svdpi.h"

extern void sv_method();
extern void c_method() {

  printf("  [C-Prog]   Hello World...!\n");
  sv_method();
}