#include "Frame.h"

Frame::Frame()
  : m_frame { nullptr },
    m_pts { AV_NOPTS_VALUE },
    m_duration { AV_NOPTS_VALUE },
    m_serial { 0 }
{

}


Frame::~Frame()
{
  if (m_frame != nullptr)
  {
    av_frame_unref(m_frame);
    av_frame_free(&m_frame);
  }
}