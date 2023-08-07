#pragma once

#include "Frame.h"

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

using namespace std;

class FrameQueue
{
public:
  explicit FrameQueue(size_t maxSize);
  ~FrameQueue();


private:
  unique_ptr<vector<Frame>> m_queue;

  int m_readIndex;
  int m_shownIndex;
  int m_writeIndex;

  size_t m_size;
  size_t m_maxSize;

  SDL_mutex* m_mutex;
  SDL_cond* m_cond;
};