#pragma once

#include "Frame.h"

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

using namespace std;

class FrameQueue
{
public:
  static const int AUDIO_QUEUE_SIZE = 9;
  static const int VIDEO_QUEUE_SIZE = 3;
  static const int SUBTITLE_QUEUE_SIZE = 16;
  static const int FRAME_QUEUE_SIZE = FFMAX(AUDIO_QUEUE_SIZE, FFMAX(VIDEO_QUEUE_SIZE, SUBTITLE_QUEUE_SIZE));

  explicit FrameQueue(size_t maxSize);
  ~FrameQueue();

  void signal();
  shared_ptr<Frame> peek();

private:
  void init();

  unique_ptr<vector<shared_ptr<Frame>>> m_queue;

  int m_readIndex;
  int m_shownIndex;
  int m_writeIndex;

  size_t m_size;
  size_t m_maxSize;

  SDL_mutex* m_mutex;
  SDL_cond* m_cond;
};