#include "Player.h"

Player::Player(string file)
  : m_file{ file }
{

}

Player::~Player()
{

}

// play
bool Player::play()
{
  // open input
  // when open with wasm
  // 1 alloc the avformat context
  // 2 alloc the avio context to load media data from everywhere
  // 3 bind the avio context to avformat context
  if (avformat_open_input(&m_formatContext, m_file.c_str(), nullptr, nullptr) < 0)
  {
    // maybe throw play exception here
    return false;
  }
  // find stream information
  if (avformat_find_stream_info(m_formatContext, nullptr) < 0)
  {
    return false;
  }
  // open codec context for audio stream
  if (!openCodecContext(&m_audioDecodeContext, &m_audioStream, &m_audioStreamIndex, AVMEDIA_TYPE_AUDIO))
  {
    return false;
  }
  // open codec context for video stream
  if (!openCodecContext(&m_videoDecodeContext, &m_videoStream, &m_videoStreamIndex, AVMEDIA_TYPE_VIDEO))
  {
    return false;
  }
  // start demuxing
  startDemuxing();
  return true;
}

// pause
bool Player::pause()
{
  return true;
}

// stop
void Player::stop()
{

}


// private methods
bool Player::openCodecContext(AVCodecContext** context, AVStream** stream, int* streamIndex, enum AVMediaType type)
{
  const AVCodec* decoder;
  // find best stream for specific media type
  if ((*streamIndex = av_find_best_stream(m_formatContext, type, -1, -1, nullptr, 0)) < 0)
  {
    return false;
  }
  *stream = m_formatContext->streams[*streamIndex];
  // find decoder by stream
  if ((decoder = avcodec_find_decoder((*stream)->codecpar->codec_id)) == nullptr)
  {
    // can not find decoder for this stream
    return false;
  }
  // alloc codec context
  *context = avcodec_alloc_context3(decoder);
  if ((*context) == nullptr)
  {
    // no memory
    return false;
  }
  // copy codec parameters to context
  if (avcodec_parameters_to_context(*context, (*stream)->codecpar) < 0)
  {
    return false;
  }
  // init decoder
  if (avcodec_open2(*context, decoder, nullptr) < 0)
  {
    return false;
  }
  return true;
}

bool Player::startDemuxing()
{
  if ((m_demuxThread = SDL_CreateThread(Player::demuxing, "demuxing threading", this)) < 0)
  {
    return false;
  }
  return true;
}


// thread entry

int Player::demuxing(void* arg)
{
  Player* player = static_cast<Player*>(arg);

  AVPacket* packet;

  return 0;
}

int Player::decodeAudio(void* arg)
{
  return 0;
}

int Player::decodeVideo(void* arg)
{
  return 0;
}