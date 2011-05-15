/*
 * Copyright (C) 2007 Apple Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution. 
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "config.h"
#include "Screen.h"

#include "FloatRect.h"
#include "Frame.h"
#include "FrameView.h"
#include "PlatformScreen.h"
#include "Widget.h"

#ifdef XP_EMBEDDED
#ifdef __cplusplus
extern "C" {
#endif
  extern bool GetBrowserOffsets(int* offsetX, int* offsetY);
  extern bool GetBrowserPluginFullscreen(void** pluginView);
  extern bool SetBrowserPluginFullscreen(void* pluginView, bool isFullScreen);
  extern bool GetBrowserSize(int* width, int* height);
#ifdef __cplusplus
} // extern C
#endif
#endif

namespace WebCore {

Screen::Screen(Frame* frame)
    : m_frame(frame)
{
}

Frame* Screen::frame() const
{
    return m_frame;
}

void Screen::disconnectFrame()
{
    m_frame = 0;
}

unsigned Screen::height() const
{
#ifdef XP_EMBEDDED
    int width,height;
    ::GetBrowserSize(&width,&height);
    return height;
#endif
  return static_cast<unsigned>(screenRect(m_frame->view()).height());
}

unsigned Screen::width() const
{
#ifdef XP_EMBEDDED
  int width,height;
  ::GetBrowserSize(&width,&height);
  return width;
#endif
  return static_cast<unsigned>(screenRect(m_frame->view()).width());
}

unsigned Screen::colorDepth() const
{
    if (!m_frame)
        return 0;
    return static_cast<unsigned>(screenDepth(m_frame->view()));
}

unsigned Screen::pixelDepth() const
{
    if (!m_frame)
        return 0;
    return static_cast<unsigned>(screenDepth(m_frame->view()));
}

unsigned Screen::availLeft() const
{
    if (!m_frame)
        return 0;
    return static_cast<unsigned>(screenAvailableRect(m_frame->view()).x());
}

unsigned Screen::availTop() const
{
    if (!m_frame)
        return 0;
    return static_cast<unsigned>(screenAvailableRect(m_frame->view()).y());
}

unsigned Screen::availHeight() const
{
    if (!m_frame)
        return 0;
    return static_cast<unsigned>(screenAvailableRect(m_frame->view()).height());
}

unsigned Screen::availWidth() const
{
    if (!m_frame)
        return 0;
    return static_cast<unsigned>(screenAvailableRect(m_frame->view()).width());
}

} // namespace WebCore
