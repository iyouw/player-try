#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#ifdef __cplusplus
}
#endif

using namespace std;

class Packet
{
public:
  Packet()=default;
  Packet(AVPacket* packet, long serial);
  ~Packet();
  
private:
  AVPacket* m_packet; 
  long m_serial;
};