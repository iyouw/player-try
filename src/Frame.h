#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#ifdef __cplusplus
}
#endif

class Frame
{
public:
  Frame();
  ~Frame();

  AVFrame*& avFrame() { return m_frame; }
  double& pts() { return m_pts; }
  double& duration() { return m_duration; }

  int width() { return m_frame->width; }
  int height() { return m_frame->height; }

  int format() { return m_frame->format; }
  
  long& serial() { return m_serial; }

private:
  AVFrame* m_frame;

  double m_pts;
  double m_duration;

  long m_serial;
};