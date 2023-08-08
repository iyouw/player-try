#include "FrameQueue.h"

FrameQueue::FrameQueue(size_t maxSize)
  : m_maxSize { FFMIN(maxSize, FRAME_QUEUE_SIZE) },
    m_queue { make_unique<vector<shared_ptr<Frame>>>(m_maxSize) },
    m_readIndex { 0 },
    m_shownIndex { 0 },
    m_writeIndex { 0 },
    m_size { 0 },
    m_mutex { SDL_CreateMutex() },
    m_cond { SDL_CreateCond() }
{
  if (m_queue == nullptr || m_mutex == nullptr || m_cond == nullptr)
  {
    throw new bad_alloc();
  }
  init();
}

FrameQueue::~FrameQueue()
{
  SDL_DestroyMutex(m_mutex);
  SDL_DestroyCond(m_cond);
}

void FrameQueue::signal()
{
  SDL_LockMutex(m_mutex);
  SDL_CondSignal(m_cond);
  SDL_UnlockMutex(m_mutex);
}

shared_ptr<Frame> FrameQueue::peek()
{
  const int index = (m_readIndex + m_shownIndex) % m_maxSize;
  return m_queue->at(index);
}

// private
void FrameQueue::init()
{
  for (size_t i = 0; i < m_maxSize; i++)
  {
    shared_ptr<Frame> frame = make_shared<Frame>();
    if (!(frame->avFrame() = av_frame_alloc()))
    {
      throw new bad_alloc();
    }
    m_queue->push_back(frame);
  }
}