/******************************************************************
 *   Copyright (c) 2014 by Synopsys Inc. - All Rights Reserved    *
 *                                                                *
 *   CONFIDENTIAL AND PROPRIETARY INFORMATION OF SYNOPSYS INC.    *
 ******************************************************************/
#ifndef __SYNOPSYS_VCS_CSOLVER_DATA_TYPE_HH__
#define __SYNOPSYS_VCS_CSOLVER_DATA_TYPE_HH__

namespace vcs_csolver_api {

// Interface to native representation of constraint data in VCS solver
class CstrDataType {
    //
    // CAUTION: PLEASE DO NOT ADD ANY DATA MEMBER HERE (NOT EVEN ANY VIRTUAL
    //          MEMBER FUNCTION) AS THAT WOULD INCREASE THE SIZE OF
    //          its derived class raceDataType. Currently, this class doesn't
    //          add a single byte to raceDataType.
    //
protected:
    CstrDataType();
};

} // end - namespace vcs_csolver_api

#endif

