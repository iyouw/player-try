#include "PacketQueue.h"

PacketQueue::PacketQueue()
  : m_serial {},
    m_queue { make_unique<queue<shared_ptr<Packet>>>() },
    m_mutex { SDL_CreateMutex() },
    m_cond { SDL_CreateCond() }
{
  if (m_queue == nullptr || m_mutex == nullptr || m_cond == nullptr)
  {
    throw new bad_alloc();
  }
}

PacketQueue::~PacketQueue()
{
  SDL_DestroyMutex(m_mutex);
}

void PacketQueue::push(shared_ptr<Packet> packet)
{
  SDL_LockMutex(m_mutex);
  m_queue->push(packet);
  SDL_UnlockMutex(m_mutex); 
}

shared_ptr<Packet> PacketQueue::pop()
{
  if (isEmpty()) return nullptr;

  SDL_LockMutex(m_mutex);
  shared_ptr<Packet> packet = m_queue->front();
  m_queue->pop();
  SDL_UnlockMutex(m_mutex);
  
  return packet;
}


shared_ptr<Packet> PacketQueue::front()
{
  if (isEmpty()) return nullptr;

  SDL_LockMutex(m_mutex);
  shared_ptr<Packet>& res = m_queue->front();
  SDL_UnlockMutex(m_mutex);

  return res;
}

shared_ptr<Packet> PacketQueue::back()
{
  if (isEmpty()) return nullptr;

  SDL_LockMutex(m_mutex);
  shared_ptr<Packet>& res = m_queue->front();
  SDL_UnlockMutex(m_mutex);

  return res;
}