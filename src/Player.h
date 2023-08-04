#pragma once

#include <string>

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#ifdef __cplusplus
}
#endif

#include <SDL2/SDL.h>

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
  string m_file;

  bool m_paused;

  // demux decode relative
  AVFormatContext* m_formatContext;
  
  // stream
  AVStream* m_videoStream;
  AVStream* m_audioStream;

  // decode
  AVCodecContext* m_videoDecodeContext;
  AVCodecContext* m_audioDecodeContext;

  // packet queue
  // frame queue


  // clock relative

  // renderer relative
  // video render relative
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
  SDL_Texture* m_videoTexture;
  // audio render relative
  SDL_AudioDeviceID m_audioDevice;
};