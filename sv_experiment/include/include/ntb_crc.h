
/****************************************************************************
 *
 * Copyright (C) 2004 Synopsys, Inc. All Rights Reserved.
 * All Rights Reserved. Used with Permission.
 *
 * Native Testbench support for the Open Vera "vera_crc" function
 *
 * This file contains macros used for vera_crc support
 *
 ****************************************************************************/

#ifndef NTB_CRC_H
#define NTB_CRC_H

#include <svdpi.h>

#ifndef NULL
#define NULL (void*) 0
#endif

extern void vera_crc_dpi(svLogicVec32 *return_stream, int N,
                         svLogicVec32 *stream,
                         int stream_size, svLogicVec32 *index1, svLogicVec32 *index2,
                         svLogicVec32 *init_stream, svLogicVec32 *poly_stream,
                         svLogicVec32 *xor_out_stream, int reflect_out, int reflect_in);


extern void vera_crc_dpi_array(svLogicVec32 *return_stream, int N,
                               svLogicVec32 *stream, int stream_size, int array_size,
                               svLogicVec32 *index1, svLogicVec32 *index2, svLogicVec32 *init_stream,
                               svLogicVec32 *poly_stream, svLogicVec32 *xor_out_stream,
                               int reflect_out, int reflect_in, int *size_array);


extern void vera_crc_dpi_dyn(svLogicVec32 *return_stream, int N,
                             const svOpenArrayHandle hstream, int stream_size, svLogicVec32 *index1,
                             svLogicVec32 *index2, svLogicVec32 *init_stream,
                             svLogicVec32 *poly_stream, svLogicVec32 *xor_out_stream,
                             int reflect_out, int reflect_in);


extern void vera_crc_dpi_mda(svLogicVec32 *return_stream, int N,
                             svLogicVec32 *stream, int stream_size, int array_size,
                             svLogicVec32 *index1, svLogicVec32 *index2, svLogicVec32 *init_stream,
                             svLogicVec32 *poly_stream, svLogicVec32 *xor_out_stream,
                             int reflect_out, int reflect_in, const svOpenArrayHandle h_size_stream);

#define Make_vera_crc(bw) \
    void vera_crc_dpi_##bw(svLogicVec32 *return_stream, int N, svLogicVec32 *stream, svLogicVec32 *index1, svLogicVec32 *index2, svLogicVec32 *init_stream, svLogicVec32 *poly_stream, svLogicVec32 *xor_out_stream, int reflect_out, int reflect_in) \
    { \
        vera_crc_dpi(return_stream, N, stream, bw, index1, index2, init_stream, poly_stream, xor_out_stream, reflect_out, reflect_in); \
    }

#define Make_vera_crc_array(bw, aw) \
    void vera_crc_dpi_array_##bw##_##aw(svLogicVec32 *return_stream, int N, svLogicVec32 *stream, svLogicVec32 *index1, svLogicVec32 *index2, svLogicVec32 *init_stream, svLogicVec32 *poly_stream, svLogicVec32 *xor_out_stream, int reflect_out, int reflect_in) \
    { \
        vera_crc_dpi_array(return_stream, N, stream, bw, aw, index1, index2, init_stream, poly_stream, xor_out_stream, reflect_out, reflect_in, NULL); \
    }

#define Make_vera_crc_dyn(bw) \
    void vera_crc_dpi_dyn_##bw(svLogicVec32 *return_stream, int N, const svOpenArrayHandle hstream, svLogicVec32 *index1, svLogicVec32 *index2, svLogicVec32 *init_stream, svLogicVec32 *poly_stream, svLogicVec32 *xor_out_stream, int reflect_out, int reflect_in) \
    { \
        vera_crc_dpi_dyn(return_stream, N, hstream, bw, index1, index2, init_stream, poly_stream, xor_out_stream, reflect_out, reflect_in); \
    }

#define Make_vera_crc_mda(bw, aw) \
    void vera_crc_dpi_mda_##bw##_##aw(svLogicVec32 *return_stream, int N, svLogicVec32 *stream, svLogicVec32 *index1, svLogicVec32 *index2, svLogicVec32 *init_stream, svLogicVec32 *poly_stream, svLogicVec32 *xor_out_stream, int reflect_out, int reflect_in, const svOpenArrayHandle h_size_stream) \
    { \
        vera_crc_dpi_mda(return_stream, N, stream, bw, aw, index1, index2, init_stream, poly_stream, xor_out_stream, reflect_out, reflect_in, h_size_stream); \
    }

#endif
