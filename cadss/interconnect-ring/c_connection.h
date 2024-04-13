#ifndef C_CONNECTION_H

#define C_CONNECTION_H

#include "packet.h"

#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

void init_network();

void sendPacket(int src, packet_t *packet);

void tick_network();

void destroy_network();

#ifdef __cplusplus
}
#endif


#endif