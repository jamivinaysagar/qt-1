/*
    Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "MediaPlayerBoxee.h"

#include "CString.h"
#include "FrameLoaderClientQt.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "HTMLMediaElement.h"
#include "HTMLVideoElement.h"
#include "TimeRanges.h"
#include "Widget.h"
#include "qwebframe.h"
#include "qwebpage.h"
#include "NotImplemented.h"

#include <limits>
#include <wtf/HashSet.h>
#include <QPainter>

extern "C" bool GetBrowserOffsets(int* offsetX, int* offsetY);

using namespace WTF;

namespace WebCore {
extern void print_trace (void);

QVariant MediaPlayerPrivate::RunCommand(QString command, QVariantMap parameters, bool expectedResult) const
{
    Document* document = m_element->document();
    if (!document)
        document = m_element->ownerDocument();

    Frame* frame = document ? document->frame() : 0;
    FrameLoaderClientQt* frameLoader =  frame ? static_cast<FrameLoaderClientQt*>(frame->loader()->client()) : 0;

    QVariantMap request;
    request.insert("command", QVariant(command));
    request.insert("parameters", parameters);

    QByteArray serialized = ((MediaPlayerPrivate*) this)->m_serializer.serialize(request);

    // javascript call for: boxeePlayer.handleRequest()    
    QString js;
    if(expectedResult)
      js = "boxee.exec2('boxee.handleBrowserCommandResponse(\\'";
    else
      js = "boxee.exec('boxee.handleBrowserCommand(\\'";

    js += QString(serialized);
    js += "\\');')";

//    fprintf(stderr, "********************** MediaPlayerPrivate::RunCommand: %s\n", js.toLocal8Bit().constData());

    QVariant result;
    if (frameLoader)
    {
        result = frameLoader->webFrame()->evaluateJavaScript(js);
        //fprintf(stderr, "********************** MediaPlayerPrivate::RunCommand Done: %s\n", result.toString().toLocal8Bit().constData());
    }

    return result;
}

MediaPlayerPrivateInterface* MediaPlayerPrivate::create(MediaPlayer* player)
{
    return new MediaPlayerPrivate(player);
}

void MediaPlayerPrivate::registerMediaEngine(MediaEngineRegistrar registrar)
{
    registrar(create, getSupportedTypes, supportsType);
}

void MediaPlayerPrivate::getSupportedTypes(HashSet<String> &supported)
{
    supported.add("video/mpeg");
    supported.add("video/quicktime");
    supported.add("video/mp4");
    supported.add("video/wmv");
    supported.add("video/3gpp");
    supported.add("video/3gpp2");
    supported.add("video/x-ms-asf");
    supported.add("video/x-msvideo");
    supported.add("video/x-ms-wmv");
    supported.add("video/ogg");
    supported.add("video/webm");
}

MediaPlayer::SupportsType MediaPlayerPrivate::supportsType(const String& mime, const String& codec)
{
    if (!mime.startsWith("audio/") && !mime.startsWith("video/"))
        return MediaPlayer::IsNotSupported;

    if (mime == "video/x-flv")
      return MediaPlayer::IsNotSupported;

    return MediaPlayer::IsSupported;
}

MediaPlayerPrivate::MediaPlayerPrivate(MediaPlayer* player)
    : m_stateTimer(this, &MediaPlayerPrivate::stateTimer),
      m_player(player),
      m_isVisible(false),
      m_paused(true), 
      m_networkState(MediaPlayer::Empty),
      m_readyState(MediaPlayer::HaveNothing)
{
  m_stateTimer.start(1.0, 1.0);
}

void MediaPlayerPrivate::stateTimer(Timer<MediaPlayerPrivate>*)
{
  QVariantMap parameters;
  QVariant result = RunCommand("MEDIAPLAYER.GetBufferingState", parameters, true);
  //fprintf(stderr, "is buffering ? %d\n", result.toBool());
//  if (result.toBool() != m_isBuffering)
//  {
//    m_isBuffering = result.toBool();
//    if (m_isBuffering)
//      m_readyState = MediaPlayer::HaveCurrentData;
//    else
//      m_readyState = MediaPlayer::HaveEnoughData;
//    m_player->readyStateChanged();
//  }

  parameters.clear();
  result = RunCommand("MEDIAPLAYER.GetPlaybackState", parameters, true);
  //fprintf(stderr, "--------------------------- state timer %x m_current/m_duration %f/%f sent event %d playback ended %d --------------------------\n", (unsigned int)this, m_current, m_duration, m_bSentEndedEvent, result.toBool());
  /*
  http://dev.w3.org/html5/spec/video.html#event-media-timeupdate
  When the current playback position reaches the end of the media resource when the direction of playback is forwards, then the user agent must follow these steps:
  1. If the media element has a loop attribute specified, then seek to the earliest possible position of the media resource and abort these steps.
  2. Stop playback. The ended attribute becomes true.
  3. The user agent must queue a task to fire a simple event named timeupdate at the element.
  4. The user agent must queue a task to fire a simple event named ended at the element.
  */

  if ((result.toBool() == true || (m_duration != 0 &&  m_current == m_duration)) &&
      !m_bSentEndedEvent)
  {
      m_bSentEndedEvent = true;
      m_player->timeChanged();
      m_stateTimer.stop();
  }
}


MediaPlayerPrivate::~MediaPlayerPrivate()
{
    //fprintf(stderr, "being destroyed------------------------\n");
}

bool MediaPlayerPrivate::hasVideo() const
{
    return true;
}

bool MediaPlayerPrivate::hasAudio() const
{
    return true;
}

void MediaPlayerPrivate::setloaded()
{
    //m_networkState = MediaPlayer::Idle;
    //m_player->networkStateChanged();
    m_readyState = MediaPlayer::HaveEnoughData;
    m_player->readyStateChanged();
}

void MediaPlayerPrivate::load(const String& url)
{
    fprintf(stderr, "--------------------- ----------------\n");
    // We are now loading
    if (m_networkState != MediaPlayer::Loading) {
        m_networkState = MediaPlayer::Loading;
        m_player->networkStateChanged();
    }

    // And we don't have any data yet
    if (m_readyState != MediaPlayer::HaveNothing) {
        m_readyState = MediaPlayer::HaveNothing;
        m_player->readyStateChanged();
    }

    m_duration = 0.0f;
    m_paintedOnce = false;
    m_bytesLoaded = 0;
    m_isBuffering = 0;
    m_bSentEndedEvent = false;

    m_element = static_cast<HTMLMediaElement*>(m_player->mediaPlayerClient());
    if (m_element && m_element->parentElement())
    {
      String parentTag = m_element->parentElement()->tagName();
      String parentType = m_element->parentElement()->getAttribute("type");
      if (!parentTag.isNull() && !parentTag.isEmpty() && !parentType.isNull() && !parentType.isEmpty() )
      {
        if (parentTag.lower() == "object" && parentType.lower() == "application/x-shockwave-flash")
        {
          //fprintf(stderr, "not loading video tag since it's surrounded by '%s' tag of type '%s'\n", parentTag.utf8().data(), parentType.utf8().data());
          return;
        }
      }
    }

    QVariantMap parameters;
    parameters.insert("url", QVariant(url));
    RunCommand("MEDIAPLAYER.Load", parameters);
    
    setVisible(true);

    m_networkState = MediaPlayer::Loading;
    m_player->networkStateChanged();
    m_readyState = MediaPlayer::HaveNothing;
    m_player->readyStateChanged();

}

void MediaPlayerPrivate::cancelLoad()
{
    notImplemented();
}

void MediaPlayerPrivate::play()
{
    fprintf(stderr, "MediaPlayerPrivate::play\n");
    QVariantMap parameters;
    RunCommand("MEDIAPLAYER.Play", parameters);
    m_paused = false;
}

void MediaPlayerPrivate::pause()
{
  fprintf(stderr, "MediaPlayerPrivate::pause\n");
  QVariantMap parameters;
  RunCommand("MEDIAPLAYER.Pause", parameters);
  m_paused = true;
}

bool MediaPlayerPrivate::paused() const
{
    return m_paused;
}

void MediaPlayerPrivate::seek(float position)
{
  //  if (!m_mediaPlayer->isSeekable())
  //      return;

  fprintf(stderr, "** SEEKING %f\n", position);
    QVariantMap parameters;
    parameters.insert("position", QVariant(100.0 * position / m_player->duration() ));
    //parameters.insert("duration", QVariant(m_player->duration()));
    QVariant result = RunCommand("MEDIAPLAYER.Seek", parameters);


#if 0


    if (m_mediaPlayerControl && !m_mediaPlayerControl->availablePlaybackRanges().contains(position * 1000))
        return;

    if (m_isSeeking)
        return;

    if (position > duration())
        position = duration();

    // Seeking is most reliable when we're paused.
    // Webkit will try to pause before seeking, but due to the asynchronous nature
    // of the backend, the player may not actually be paused yet.
    // In this case, we should queue the seek and wait until pausing has completed
    // before attempting to seek.
    if (m_mediaPlayer->state() == QMediaPlayer::PlayingState) {
        m_mediaPlayer->pause();
        m_isSeeking = true;
        m_queuedSeek = static_cast<qint64>(position * 1000);

        // Set a timeout, so that in the event that we don't get a state changed
        // signal, we still attempt the seek.
        QTimer::singleShot(1000, this, SLOT(queuedSeekTimeout()));
    } else {
        m_isSeeking = true;
        m_mediaPlayer->setPosition(    QVariantMap parameters;
    RunCommand("MEDIAPLAYER.CancelLoad", parameters);static_cast<qint64>(position * 1000));

        // Set a timeout, in case we don't get a position changed signal
        QTimer::singleShot(10000, this, SLOT(seekTimeout()));
    }
#endif
}

bool MediaPlayerPrivate::seeking() const
{
    //fprintf(stderr, "=========== %s %s ===========\n", __FILE__, __FUNCTION__);
    return false;
}

float MediaPlayerPrivate::duration() const
{
//    if (m_readyState < MediaPlayer::HaveMetadata)
//        return 0.0f;

    //fprintf(stderr, "1 duration is %f\n", m_duration);
    if (m_duration != 0.0f)
      return m_duration;

    QVariantMap parameters;
    QVariant result = RunCommand("MEDIAPLAYER.Duration", parameters, true);
    float res = result.toFloat();
    if (res != 0.0f)
    {
        MediaPlayerPrivate* tp = (MediaPlayerPrivate*)this;
        tp->m_duration = res;
        tp->setloaded();
        m_player->timeChanged();
    }
    //fprintf(stderr, "2 duration is %f\n", m_duration);
    return res;
}

float MediaPlayerPrivate::currentTime() const
{
    MediaPlayerPrivate* tp = (MediaPlayerPrivate*)this;
    if (m_bSentEndedEvent)
    {
      tp->m_current = m_duration;
    }
    else
    {
      QVariantMap parameters;
      QVariant result = RunCommand("MEDIAPLAYER.CurrentTime", parameters, true);
      tp->m_current = result.toFloat();
    }
    //fprintf(stderr, "=========== %s %s %f %d ===========\n", __FILE__, __FUNCTION__, m_current, m_isBuffering);
    return m_current;
}

PassRefPtr<TimeRanges> MediaPlayerPrivate::buffered() const
{
  RefPtr<TimeRanges> buffered = TimeRanges::create();

  if (m_isBuffering)
    buffered->add(0, m_current - 1);
  else
    buffered->add(0, m_duration + 30);
  //fprintf(stderr, "=========== %s %s %f ===========\n", __FILE__, __FUNCTION__, m_duration);
  return buffered.release();
}

float MediaPlayerPrivate::maxTimeSeekable() const
{
  //fprintf(stderr, "=========== %s %s ===========\n", __FILE__, __FUNCTION__);
    notImplemented();
    return m_duration;
}

unsigned MediaPlayerPrivate::bytesLoaded() const
{
    const float dur = duration();

    if (dur == 0.0)
        return 0;

    return (unsigned)((MediaPlayerPrivate*)this)->m_current;
}

unsigned MediaPlayerPrivate::totalBytes() const
{
  //fprintf(stderr, "=========== %s %s ===========\n", __FILE__, __FUNCTION__);
    return 0;
}

void MediaPlayerPrivate::setRate(float rate)
{
  //fprintf(stderr, "=========== %s %s %f ===========\n", __FILE__, __FUNCTION__, rate);
    notImplemented();
}

void MediaPlayerPrivate::setVolume(float volume)
{
    QVariantMap parameters;
    parameters.insert("volume", QVariant(QVariant(volume).toString()));
    RunCommand("MEDIAPLAYER.SetVolume", parameters);
}

bool MediaPlayerPrivate::supportsMuting() const
{
    return true;
}

void MediaPlayerPrivate::setMuted(bool muted)
{
    QVariantMap parameters;
    parameters.insert("muted", QVariant(muted));
    RunCommand("MEDIAPLAYER.SetMuted", parameters);
}

MediaPlayer::NetworkState MediaPlayerPrivate::networkState() const
{
  //fprintf(stderr, "=========== %s %s ===========\n", __FILE__, __FUNCTION__);
    return m_networkState;
}

MediaPlayer::ReadyState MediaPlayerPrivate::readyState() const
{
  //fprintf(stderr, "=========== %s %s ===========\n", __FILE__, __FUNCTION__);
    return m_readyState;
}

void MediaPlayerPrivate::setVisible(bool visible)
{
  //fprintf(stderr, "=========== %s %s ===========\n", __FILE__, __FUNCTION__);
    m_isVisible = visible;
}

void MediaPlayerPrivate::setSize(const IntSize& size)
{
    m_size = size;
}

IntSize MediaPlayerPrivate::naturalSize() const
{
    return m_size;
}

void MediaPlayerPrivate::paint(GraphicsContext* context, const IntRect& rect)
{
    if (context->paintingDisabled())
        return;

    if (!m_isVisible && !m_isBuffering)
        return;

    if (!m_paintedOnce)
    {
        int offsetX = 0;
        int offsetY = 0;
        ::GetBrowserOffsets(&offsetX, &offsetY);

        m_videoRect = rect;
        m_videoRect.setX(m_videoRect.x() + offsetX);
        m_videoRect.setY(m_videoRect.y() + offsetY);

        QVariantMap parameters;
        parameters.insert("x", QVariant(m_videoRect.x()));
        parameters.insert("y", QVariant(m_videoRect.y()));
        parameters.insert("width", QVariant(m_videoRect.width()));
        parameters.insert("height", QVariant(m_videoRect.height()));
        RunCommand("MEDIAPLAYER.Paint", parameters);
    }

    m_paintedOnce = true;

    FloatRect fr(rect.x(), rect.y(), rect.width(), rect.height());
    context->clearRect(fr);
}

#if USE(ACCELERATED_COMPOSITING)
void MediaPlayerPrivate::acceleratedRenderingStateChanged()
{
  fprintf(stderr, "=========== %s %s ===========\n", __FILE__, __FUNCTION__);
    bool composited = m_player->mediaPlayerClient()->mediaPlayerRenderingCanBeAccelerated(m_player);
    if (composited == m_composited)
        return;

    m_composited = composited;
}

PlatformLayer* MediaPlayerPrivate::platformLayer() const
{
    return 0;
}
#endif

} // namespace WebCore

#include "moc_MediaPlayerBoxee.cpp"
