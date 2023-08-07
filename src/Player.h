#pragma once

#include "PacketQueue.h"
#include "FrameQueue.h"

#include <string>
#include <SDL2/SDL.h>

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#ifdef __cplusplus
}
#endif



using namespace std;

class Player
{
public:
  Player(string file);
  ~Player();

  bool play();
  bool pause();

  void stop();

private:
  // static methods for thread entry
  static int demuxing(void* arg);
  static int decodeAudio(void* arg);
  static int decodeVideo(void* arg);

  // private methods
  bool openCodecContext(AVCodecContext** context, AVStream** stream, int* streamIndex, enum AVMediaType type);
  bool startDemuxing();

  // fields
  string m_file;
  bool m_paused;

  // demux decode relative
  AVFormatContext* m_formatContext;
  SDL_Thread* m_demuxThread;
  
  // stream
  int m_audioStreamIndex;
  int m_videoStreamIndex;
  AVStream* m_audioStream;
  AVStream* m_videoStream;
  
  // packet queue
  unique_ptr<PacketQueue> m_audioPacketQueue;
  unique_ptr<PacketQueue> m_videoPacketQueue;

  // decode
  AVCodecContext* m_audioDecodeContext;
  AVCodecContext* m_videoDecodeContext;

  // frame queue
  unique_ptr<FrameQueue> m_audioFrameQueue;
  unique_ptr<FrameQueue> m_videoFrameQueue;

  // clock relative

  // renderer relative
  // video render relative
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
  SDL_Texture* m_videoTexture;
  // audio render relative
  SDL_AudioDeviceID m_audioDevice;
};