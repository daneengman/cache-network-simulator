/*******************************************************************************************
 * Copyright (C) 2013 Synopsys Inc. All Rights Reserved.
 *
 * Interface for Unified Configuration Format (Unified Compile Flow)
 *******************************************************************************************/

#ifndef UFE_TCL_PARSER_HH
#define UFE_TCL_PARSER_HH
#include <sstream>

typedef enum {
    UTF_OK,
    UTF_ERROR
}UTF_RETURN_CODE;


///This function is the interface function for Unified Configuration Framework.
///inputs:
/// 1. generatedConfigRootDir - generated configuration files stated in Mappings.tcl are assumed to be relative to this directory.
/// 2. errorStringStream - in case an evaluation error occured this stream will contain the error report.
/// 3. ucfFileName: Unified configuration tcl file (modified by the user)
/// 4. emptyFileName: contains empty definitions for tcl command procedures
/// 5. mappingsFileName - this file maps between the tool translation script and the output generated configuration file for that tool.
/// 6. isCciEnabled - used to switch between tcl interp and cci interp
/// 7. printVerbose - Verbose flag,currently used in cci
///
/// returned value:
///     UTF_RETURN_CODE (see above definition)
///         errorStringStream.str() will contain the error text in case returnedCode!=UTF_OK
extern "C" {
    UTF_RETURN_CODE parseZebuTclUnifiedConfiguration(const char* generatedConfigRootDir,
                                                     std::ostringstream& errorStringStream,
                                                     const char* ucfFileName = "UCF.tcl",
                                                     const char* emptyFileName = "Empty.tcl",
                                                     const char* mappingsFileName = "Mappings.tcl",
                                                     bool isCciEnabled = false,
                                                     bool printVerbose = false);
}


#endif /* UFE_TCL_PARSER_HH */
