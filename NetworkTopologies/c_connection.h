#ifndef C_CONNECTION_H

#define C_CONNECTION_H

#include "packet.h"

#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

void init();

void sendPacket(int src, packet_t *packet);

void tick();

void destroy();

#ifdef __cplusplus
}
#endif


#endif