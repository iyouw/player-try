#pragma once

#include "Packet.h"

#include <queue>
#include <memory>

#include <SDL2/SDL.h>

using namespace std;

class PacketQueue
{
public:
  PacketQueue();
  ~PacketQueue();

  void push(shared_ptr<Packet> packet);
  shared_ptr<Packet> pop();

  shared_ptr<Packet> front();
  shared_ptr<Packet> back();

  size_t size() const { return m_queue->size(); }
  bool isEmpty() const  { return size() == 0; }

private:
  long m_serial;
  unique_ptr<queue<shared_ptr<Packet>>> m_queue;

  SDL_mutex* m_mutex;
  SDL_cond* m_cond;
};