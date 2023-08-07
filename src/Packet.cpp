#include "Packet.h"

Packet::Packet(AVPacket* packet, long serial)
  : m_packet { packet },
    m_serial { serial }
{

}

// maybe should unref the packet or free the packet
Packet::~Packet()
{

}