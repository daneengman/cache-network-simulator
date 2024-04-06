#ifndef SV_COVG_API_H
#define SV_COVG_API_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    SV_SAMPLE_VAL,
    SV_SAMPLE_REF
} svSampleEnum;

typedef struct svCovgHandle_s *svCovgHandle;

extern svCovgHandle svCovgNew(char *name, char *instName, svSampleEnum sampleType, ...);
extern svCovgHandle svCovgNew2(char *name, char *instName, svSampleEnum sampleType, va_list args);

extern int svCovgDelete(svCovgHandle covgHandle);

extern int svCovgSample(svCovgHandle covgHandle, ...);
extern int svCovgSample2(svCovgHandle covgHandle, va_list args);

#ifdef __cplusplus
}
#endif

#endif
