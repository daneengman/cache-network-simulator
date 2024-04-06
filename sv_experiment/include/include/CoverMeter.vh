//***************************************************************************
// CoverMeter
// Copyright (c) 1999 Synopsys, Inc. All rights reserved
//
// File: Covermeter.vh
//
// Contents: `defines for CoverMeter Real Time Coverage API
//
// Tag: "$Name:  $"
//***************************************************************************


// mode values
`define CM_START 1
`define CM_STOP  2
`define CM_CHECK 3

// coverage type values
`define CM_SOURCE    1
`define CM_CONDITION 2
`define CM_TOGGLE    3
`define CM_FSM       4
`define CM_FSM_TRANS 4
`define CM_FSM_STATE 5
`define CM_UEXPR     6

// scope definition values
`define CM_MODULE 10
`define CM_HIER   11

// return values
`define CM_NOERROR 0
`define CM_ERROR   -1
`define CM_NOCOV   -2
`define CM_PARTIAL -3

// supported types to the system task $cm_post
`define CM_TEST 1 /* Type to add a name to a test run */
`define CM_TEST_STATUS  2 /* Type to set the status of a test */
`define CM_CUSTOM_VALUE 3 /* Type to add/annotate a custom value pair to a test*/
