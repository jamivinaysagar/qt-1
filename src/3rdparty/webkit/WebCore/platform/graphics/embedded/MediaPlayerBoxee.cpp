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

#include "qjson/parser.h"

extern "C" bool GetBrowserOffsets(int* offsetX, int* offsetY);

using namespace WTF;

namespace WebCore {
extern void print_trace (void);

void MediaPlayerPrivate::printState(const char* label, int line)
{
    fprintf(stderr, "\n\n******************* %s::%s(%d): state:\nm_player = %p, m_element = %p, m_composited = %d\nm_isVisible = %d, m_paintedOnce = %d, \
m_bytesLoaded = %d, m_loadFinished = %d\nm_duration = %f, m_current = %f, m_buffered = %f\nm_networkState = %d\nm_readyState = %d\
                     \nm_paused = %d\nm_isBuffering = %d\nm_isPlaybackEnded = %d\nm_bSentEndedEvent = %d\n*******************\n\n"
              , __FILE__, label, line
              , m_player
              , m_element
              , m_composited
              , m_isVisible
              , m_paintedOnce
              , m_bytesLoaded
              , m_loadFinished
              , m_duration
              , m_current
              , m_buffered
              , m_networkState
              , m_readyState
              , m_paused
              , m_isBuffering
              , m_isPlaybackEnded
              , m_bSentEndedEvent);
    fflush(stderr);
}

QVariant MediaPlayerPrivate::RunCommand(QString command, QVariantMap parameters, bool expectedResult) const
{
    Document* document = m_element->document();
    if (!document)
        document = m_element->ownerDocument();

    Frame* frame = document ? document->frame() : 0;
    FrameLoaderClientQt* frameLoader =  frame ? static_cast<FrameLoaderClientQt*>(frame->loader()->client()) : 0;

    QVariantMap request;
    request.insert(QString::fromAscii("command"), QVariant(command));
    request.insert(QString::fromAscii("parameters"), parameters);

    QByteArray serialized = ((MediaPlayerPrivate*) this)->m_serializer.serialize(request);

    // javascript call for: boxeePlayer.handleRequest()    
    QString js;
    if(expectedResult)
      js = QString::fromAscii("boxee.exec2('boxee.handleBrowserCommandResponse(\\'");
    else
      js = QString::fromAscii("boxee.exec('boxee.handleBrowserCommand(\\'");

    js += QString::fromAscii(serialized);
    js += QString::fromAscii("\\');')");

    //fprintf(stderr, "*** MediaPlayerPrivate::RunCommand: %s\n", js.toLocal8Bit().constData());

    QVariant result;
    if (frameLoader)
    {
        result = frameLoader->webFrame()->evaluateJavaScript(js);
		//fprintf(stderr, "*** MediaPlayerPrivate::RunCommand Done: %s\n", result.toString().toLocal8Bit().constData());
    }

    return result;
}

MediaPlayerPrivateInterface* MediaPlayerPrivate::create(MediaPlayer* player)
{
    return new MediaPlayerPrivate(player);
}

void MediaPlayerPrivate::checkLoadingStatus()
{
//  fprintf(stderr, "\n*** %s::%s(%d)\tcalling RunCommand(MEDIAPLAYER.GetLoadingStatus)...\n", __FILE__, __FUNCTION__, __LINE__);
	QVariantMap parameters;
    QVariant result = RunCommand(QString::fromAscii("MEDIAPLAYER.GetLoadingStatus"), parameters, true);


	m_loadFinished = result.toBool();
//  fprintf(stderr, "\n*** %s::%s(%d)\tsetting m_loadFinished to %d\n", __FILE__, __FUNCTION__, __LINE__, m_loadFinished);
//  fprintf(stderr, "m_paused = %d\n\n", m_paused);
//  fflush(stderr);

	if(m_loadFinished)
	{
//      fprintf(stderr, "\n*** %s::%s(%d)\tloaded = TRUE\n", __FILE__, __FUNCTION__, __LINE__);
		setVisible(true);
//      fprintf(stderr, "\n*** %s::%s(%d)\tcurrent networkState = %d, new networkState = %d\n\n", __FILE__, __FUNCTION__, __LINE__, m_networkState, MediaPlayer::Loading);
		m_networkState = MediaPlayer::Loading;
//      fprintf(stderr, "\n*** %s::%s(%d)\tcalling m_player->networkStateChanged() new networkState = %d\n\n", __FILE__, __FUNCTION__, __LINE__, m_networkState);
		m_player->networkStateChanged();
//      fprintf(stderr, "\n*** %s::%s(%d)\tchanging readyStare from %d to MediaPlayer::HaveMetadata (%d)\n\n", __FILE__, __FUNCTION__, __LINE__, m_readyState, MediaPlayer::HaveMetadata);
		m_readyState = MediaPlayer::HaveMetadata;
//      fprintf(stderr, "\n*** %s::%s(%d)\tcalling m_player->readyStateChanged() new readyState = %d\n\n", __FILE__, __FUNCTION__, __LINE__, m_readyState);
		m_player->readyStateChanged();
//  	MediaPlayerPrivate* tp = (MediaPlayerPrivate*)this;
//  	tp->setloaded(); //fixme: verify it is safe to comment this
	}
//  else
//  {
//      fprintf(stderr, "\n*** %s::%s(%d)\tloaded = FALSE\n", __FILE__, __FUNCTION__, __LINE__);
//  }
}
int timer = 0; //used for selective debug

void MediaPlayerPrivate::updatePlayerStatus()
{
    QVariantMap parameters;
    QVariant result = RunCommand(QString::fromAscii("MEDIAPLAYER.GetStatusUpdate"), parameters, true);

    /**
     * get cumulative status update from the player
     * isBuffering
     * isPlaybackEnded
     * currentTime
     * buffered
     */

	QJson::Parser parser;
	bool ok;
	QVariantMap res = parser.parse(result.toByteArray(), &ok).toMap();

	if(!ok)
	{
		return;
	}

    int isBuffering = res["isBuffering"].toInt();
	bool isPlaybackEnded = res["isPlaybackEnded"].toBool();
	float currentTime = res["currentTime"].toFloat();
	float timeBuffered = res["buffered"].toFloat();
    void* idd = (void*)res["playerID"].toInt();

    if(idd != m_player)
    {
//      fprintf(stderr, "\n*** %s::%s(%d) MEDIAPLAYER.GetStatusUpdate:\tgot response of previous player IGNORING: current playerID = %p, response playerID = %p\n\n"
//                    , __FILE__, __FUNCTION__, __LINE__, m_player, idd);
        return;
    }
//  else
//  {
//      fprintf(stderr, "\n*** %s::%s(%d) MEDIAPLAYER.GetStatusUpdate:\tresponse playerID = current playerID (%p)\n\n"
//                    , __FILE__, __FUNCTION__, __LINE__, idd);
//  }
/*
    if(timer++ %15 == 0 || isBuffering != m_isBuffering || m_duration - currentTime < 15.0)
    {
        printState(__FUNCTION__, __LINE__);

        fprintf(stderr, "\n*** %s::%s(%d) MEDIAPLAYER.GetStatusUpdate:\nisBuffering = %d\nisPlaybackEnded = %d\ncurrentTime = %f\ntimeBuffered = %f\n***\n\n"
                      , __FILE__, __FUNCTION__, __LINE__
                      , isBuffering
                      , isPlaybackEnded
                      , currentTime
                      , timeBuffered);
        fflush(stderr);
    }
    else
    {
        fprintf(stderr, "..");
    }
*/

	MediaPlayerPrivate* tp = (MediaPlayerPrivate*)this;

	/**
	 * currentTime
	 *
	 */
    if(isPlaybackEnded)
      tp->m_current = m_duration;
	else
      tp->m_current = currentTime;

    /**
	 * buffered
	 *
	 */
	tp->m_buffered = timeBuffered; //buffered() returns this value to the browser

	/**
	 * isPlaybackEnded
	 *
	 */
	m_isPlaybackEnded = isPlaybackEnded;

	if(!m_bSentEndedEvent && isPlaybackEnded)
    {
		m_readyState = MediaPlayer::HaveCurrentData; //represents end of media
        //m_isBuffering = 1;
//      fprintf(stderr, "\n*** %s::%s(%d):\nplaybackEnded - setting readyState to %d\ncalling m_player->readyStateChanged()...\nisBuffering = %d\nisPlaybackEnded = %d\ncurrentTime = %f\ntimeBuffered = %f\n"
//                    , __FILE__, __FUNCTION__, __LINE__
//                    , m_readyState
//                    , isBuffering
//                    , isPlaybackEnded
//                    , currentTime
//                    , timeBuffered);
		m_player->readyStateChanged();

        m_bSentEndedEvent = true;
//      fprintf(stderr, "\n*** %s::%s(%d):\tcalling m_player->timeChanged()\n", __FILE__, __FUNCTION__, __LINE__);
        m_player->timeChanged();
//      fprintf(stderr, "\n*** %s::%s(%d):\nstopping timer!!!\n", __FILE__, __FUNCTION__, __LINE__);
        m_stateTimer.stop();
    }
/*
	if(!isBuffering && (currentTime < timeBuffered) && !m_isPlaybackEnded)
	{
		if(m_readyState < MediaPlayer::HaveEnoughData)
		{
            fprintf(stderr, "\n*** %s::%s(%d):\ncurrentTime < timeBuffered && !m_isBuffering && !m_isPlaybackEnded, (isBuffering = %d)readyState = %d, - setting readyState to HaveEnoughData (%d)\n", __FILE__, __FUNCTION__, __LINE__, isBuffering, m_readyState, MediaPlayer::HaveEnoughData);
			m_readyState = MediaPlayer::HaveEnoughData;
            fprintf(stderr, "\n*** %s::%s(%d):\nsetting readyState to %d\ncalling m_player->readyStateChanged()...\nisBuffering = %d\nisPlaybackEnded = %d\ncurrentTime = %f\ntimeBuffered = %f\n"
                          , __FILE__, __FUNCTION__, __LINE__
                          , m_readyState, isBuffering, isPlaybackEnded, currentTime, timeBuffered);
			m_player->readyStateChanged();
		}
	}
*/
#if 0
	else //if(currentTime == timeBuffered)
	{
		/*
		if(!isPlaybackEnded)
		{
			//FIXME...
			//m_isBuffering = 0;
			if(m_readyState > MediaPlayer::HaveCurrentData)
			{
				//fprintf(stderr, "\ncurrentTime >= timeBuffered, readyState = %d, - setting readyState to HaveCurrentData (%d)\n", m_readyState, MediaPlayer::HaveCurrentData);
				m_readyState = MediaPlayer::HaveCurrentData;
				fprintf(stderr, "\n*** %s::%s(%d):\nsetting readyState to %d\ncalling m_player->readyStateChanged()...\nisBuffering = %d\nisPlaybackEnded = %d\ncurrentTime = %f\ntimeBuffered = %f\n" 
							  , __FILE__, __FUNCTION__, __LINE__
							  , m_readyState
							  , isBuffering
							  , isPlaybackEnded
							  , currentTime
							  , timeBuffered);
				m_player->readyStateChanged();
			}
		}
		*/
	}
#endif
	/**
	 * isBuffering
	 *
	 */
    if(isBuffering < 0)
    {
//      fprintf(stderr, "\n*** %s::%s(%d):\tm_isBuffering has invalid value (%d) - IGNORING!!!\n" , __FILE__, __FUNCTION__, __LINE__, isBuffering);
    }
    else if(m_isBuffering < 0) //m_isBuffering is in invalid state - set it
    {
//      fprintf(stderr, "\n*** %s::%s(%d):\tm_isBuffering has invalid value (%d) - setting value to %d\n" , __FILE__, __FUNCTION__, __LINE__, m_isBuffering, isBuffering);
        m_isBuffering = isBuffering;
        //FIXME: maybe need to set ready and notify
    }
    else if(isBuffering != m_isBuffering && !m_isPlaybackEnded) //player entered buffering state
	{
//      fprintf(stderr, "\n*** %s::%s(%d):\tm_isBuffering has changed && !m_isPlaybackEnded:\nprev value = %d, new value = %d\n" , __FILE__, __FUNCTION__, __LINE__, m_isBuffering, isBuffering);
		m_isBuffering = isBuffering; //update internal state

		//update HTML5 according to new internal state
		if(m_isBuffering)
		{
//          fprintf(stderr, "\n*** %s::%s(%d):\tm_isBuffering has changed to %d, - setting readyState to HaveCurrentData (%d)\n" , __FILE__, __FUNCTION__, __LINE__, m_isBuffering, MediaPlayer::HaveCurrentData);
			m_readyState = MediaPlayer::HaveCurrentData;
		}
		else
		{
//          fprintf(stderr, "\n*** %s::%s(%d):\tm_isBuffering has changed to %d, - setting readyState to HaveEnoughData (%d)\n" , __FILE__, __FUNCTION__, __LINE__, m_isBuffering, MediaPlayer::HaveEnoughData);
			m_readyState = MediaPlayer::HaveEnoughData;
		}
		m_player->readyStateChanged();
	}
/*
    if(isPlaybackEnded)
    {
        fprintf(stderr, "\n*** %s::%s(%d):\tipPlaybackEnded = TRUE:\nm_networkState = %d, m_readyState = %d\nm_paused = %d\nm_isBuffering = %d\ncurrentTime = %f\ntimeBuffered = %f\nduration = %f\nm_bSentEndedEvent = %d\n"
              , __FILE__, __FUNCTION__, __LINE__              
              , m_networkState
              , m_readyState
              , m_paused
              , m_isBuffering
              , currentTime
              , timeBuffered
              , m_duration
              , m_bSentEndedEvent);
    }
*/
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
  (void)codec;
    if (!mime.startsWith(QString::fromAscii("audio/")) && !mime.startsWith(QString::fromAscii("video/")))
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
      m_size(0,0),
      m_naturalSize(0,0),
      m_networkState(MediaPlayer::Empty),
      m_readyState(MediaPlayer::HaveNothing),
      m_current(0.0),
      m_buffered(0.0),
      m_isBuffering(-1),
      m_loadFinished(false),
      m_isPlaybackEnded(false)
{
//fprintf(stderr, "\n\n\n\n*** %s::%s(%d):\tnew MediaPlayerBoxee is created!!!\tparent (player) = %p\n\n\n\n" , __FILE__, __FUNCTION__, __LINE__, player);
//print_trace();
  m_stateTimer.start(3.0, 0.5);
}

void MediaPlayerPrivate::stateTimer(Timer<MediaPlayerPrivate>*)
{
//fprintf(stderr, "\n\n/////////////////////////%s::%s(%d)////////////////////////////\n\n" , __FILE__, __FUNCTION__, __LINE__);

//FIXME: move this if() from here to updatePlayerStatus()
//add width & height to the values returned from GetPlayerStatus()
//each sec and check if values have changed call m_player->sizeCHanged
#if 0  /* moved down */
  if(m_naturalSize.isZero())
  {
      fprintf(stderr, "\n\n*** %s::%s(%d):\tm_naturalSize == 0 - need to obtain dims from Player - calling MEDIAPLAYER.GetNaturalSize\n\n" , __FILE__, __FUNCTION__, __LINE__);
	  QVariantMap parameters;
	  QVariant result = RunCommand(QString::fromAscii("MEDIAPLAYER.GetNaturalSize"), parameters, true);
	  QJson::Parser parser;
	  bool ok;
	  QVariantMap res = parser.parse(result.toByteArray(), &ok).toMap();
	  m_naturalSize.setWidth(res["width"].toInt());
	  m_naturalSize.setHeight(res["height"].toInt());

//    if(!m_naturalSize.isZero()) {
//        fprintf(stderr, "\n\n*** %s::%s(%d):\tafter MEDIAPLAYER.GetNaturalSize\nwidth = %d, height = %d\ncalling m_player->sizeChanged()\n\n" , __FILE__, __FUNCTION__, __LINE__, m_naturalSize.width(), m_naturalSize.height());
//  	m_player->sizeChanged();
//    } else {
//        fprintf(stderr, "\n\n*** %s::%s(%d):\tafter MEDIAPLAYER.GetNaturalSize STILL ZERO\n\n"  , __FILE__, __FUNCTION__, __LINE__);
//    }
  }
//else
//{
//    fprintf(stderr, "\n\n*** %s::%s(%d):\tGetNaturalSize != 0 (width = %d, height = %d)\n\n" , __FILE__, __FUNCTION__, __LINE__, m_naturalSize.width(), m_naturalSize.height());
//}
#endif 

  //wait for Player to finish load and then call updatePlayerStatus()
  if(!m_loadFinished) 
  {
    checkLoadingStatus();

    if(m_naturalSize.isZero())
    {
//    fprintf(stderr, "\n\n*** %s::%s(%d):\tm_naturalSize == 0 - need to obtain dims from Player - calling MEDIAPLAYER.GetNaturalSize\n\n" , __FILE__, __FUNCTION__, __LINE__);
      QVariantMap parameters;
      QVariant result = RunCommand(QString::fromAscii("MEDIAPLAYER.GetNaturalSize"), parameters, true);
      QJson::Parser parser;
      bool ok;
      QVariantMap res = parser.parse(result.toByteArray(), &ok).toMap();
      m_naturalSize.setWidth(res["width"].toInt());
      m_naturalSize.setHeight(res["height"].toInt());
    }
//  else
//  {
//      fprintf(stderr, "\n\n*** %s::%s(%d):\tGetNaturalSize != 0 (width = %d, height = %d)\n\n" , __FILE__, __FUNCTION__, __LINE__, m_naturalSize.width(), m_naturalSize.height());
//  }
  } 
  else
  {
    updatePlayerStatus();
  }
}


MediaPlayerPrivate::~MediaPlayerPrivate()
{
    //fprintf(stderr, "being destroyed------------------------\n");
//  fprintf(stderr, "\n\n\n\n*** %s::%s(%d):\tMediaPlayerBoxee (m_player = %p) is destroyed!!!\n\n\n\n" , __FILE__, __FUNCTION__, __LINE__, m_player);
//  printState(__FUNCTION__, __LINE__);
//  print_trace();
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
    //fprintf(stderr, "\n*** %s::%s(%d)\tcurrent readyState = %d, new readyState = %d\n\n", __FILE__, __FUNCTION__, __LINE__, m_readyState, MediaPlayer::HaveEnoughData);
    m_readyState = MediaPlayer::HaveEnoughData;
//  fprintf(stderr, "\n*** %s::%s(%d):\nsetting readyState to %d\ncalling m_player->readyStateChanged()...\n" , __FILE__, __FUNCTION__, __LINE__ , m_readyState);
	m_player->readyStateChanged();
	m_isPlaybackEnded = false;
}

void MediaPlayerPrivate::load(const String& url)
{
//  // We are now loading
//  if (m_networkState != MediaPlayer::Loading) {
//      m_networkState = MediaPlayer::Loading;
//      m_player->networkStateChanged();
//  }
//
//  // And we don't have any data yet
//  if (m_readyState != MediaPlayer::HaveNothing) {
//      m_readyState = MediaPlayer::HaveNothing;
//      m_player->readyStateChanged();
//  }

    m_duration = -1.0f;
    m_current = 0.0;
    m_buffered = 0.0;
    m_paintedOnce = false;
    m_bytesLoaded = 0;
    m_isBuffering = -1; //indicate invalid value - need to get proper value from player
    m_bSentEndedEvent = false;
    m_loadFinished = false;
    m_paused = true;
    m_readyState = MediaPlayer::HaveNothing;
    m_isPlaybackEnded = false;

    /************* / from ctor
      m_isVisible(false),
      m_networkState(MediaPlayer::Empty),
    /*****************/

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
    parameters.insert(QString::fromAscii("playerID"), QVariant((int)m_player)); //send updated player ID to P.M.
    parameters.insert(QString::fromAscii("url"), QVariant(url));
    if (m_element && !m_element->isVideo())
    {
      parameters.insert(QString::fromAscii("IsVideo"), QVariant(false));
    }
    else
	{
      parameters.insert(QString::fromAscii("isVideo"), QVariant(true));
	}

//  fprintf(stderr, "\n*** %s::%s(%d):\tcalling MEDIAPLAYER.Load...\nurl = %s\n\n", __FILE__, __FUNCTION__, __LINE__, url.utf8().data());
//  fflush(stderr);
//  printState(__FUNCTION__, __LINE__);

    RunCommand(QString::fromAscii("MEDIAPLAYER.Load"), parameters, true);
}

void MediaPlayerPrivate::cancelLoad()
{
    notImplemented();
}

void MediaPlayerPrivate::play()
{
//  printState(__FUNCTION__, __LINE__);

	if(m_paused)
	{
//      fprintf(stderr, "***** %s::%s(%d)\tcalling RunCommand(MEDIAPLAYER.Play)\n", __FILE__, __FUNCTION__, __LINE__);
		QVariantMap parameters;
		RunCommand(QString::fromAscii("MEDIAPLAYER.Play"), parameters);	
//      fprintf(stderr, "***** %s::%s(%d)\tsetting m_paused to FALSE (0)   -  prev value was TRUE (1)\n", __FILE__, __FUNCTION__, __LINE__);
		m_paused = false;
	}
//  else
//  {
//      fprintf(stderr, "\n***** %s::%s(%d)\tIGNORING play() (m_paused = %d)\n\n", __FILE__, __FUNCTION__, __LINE__, m_paused);
//  }
//  fflush(stderr);
}

void MediaPlayerPrivate::pause()
{
//  fprintf(stderr, "\n***** %s::%s(%d)\tcalled\n", __FILE__, __FUNCTION__, __LINE__);
//  print_trace();
//  printState(__FUNCTION__, __LINE__);

    if(!m_isPlaybackEnded)
    {
//      fprintf(stderr, "\n***** %s::%s(%d)\tcalling RunCommand(MEDIAPLAYER.Pause)\n", __FILE__, __FUNCTION__, __LINE__);
    	QVariantMap parameters;
    	RunCommand(QString::fromAscii("MEDIAPLAYER.Pause"), parameters);
    }
//  else
//  {
//      fprintf(stderr, "\n***** %s::%s(%d)\tcall to MediaPlayerPrivate::pause() ignored since m_isPlaybackEnded = %d\n", __FILE__, __FUNCTION__, __LINE__, m_isPlaybackEnded);
//      fflush(stderr);
//  }

	if(m_paused)
	{
        if(m_readyState >= MediaPlayer::HaveCurrentData)
        {
            m_paused = false;
//          fprintf(stderr, "\n***** %s::%s(%d)\tsetting m_paused to %d\n\n", __FILE__, __FUNCTION__, __LINE__, m_paused);
        }
//      else
//      {
//          fprintf(stderr, "\n***** %s::%s(%d)\treadyState = %d (< HaveCurrentData = 2) - NOT setting m_paused to false!!!\n\n", __FILE__, __FUNCTION__, __LINE__, m_readyState);
//      }
	}
	else
	{
		m_paused = true;
//      fprintf(stderr, "\n***** %s::%s(%d)\tsetting m_paused to %d\n\n", __FILE__, __FUNCTION__, __LINE__, m_paused);
	}
//  fflush(stderr);
}

bool MediaPlayerPrivate::paused() const
{
    return m_paused;
}

void MediaPlayerPrivate::seek(float position)
{
//  fprintf(stderr, "\n***** %s::%s(%d)\tcalled position = %f\n", __FILE__, __FUNCTION__, __LINE__, position);
#if 1
    if(!m_loadFinished || m_isPlaybackEnded || (m_duration <= 0.0 && position <= 0.0))
    {
        return;
    }
#else
	if(!m_loadFinished)
	{
        fprintf(stderr, "\n***** %s::%s(%d)\tcall to RunCommand(MEDIAPLAYER.Seek) ignored since m_loafFinished = %d\n", __FILE__, __FUNCTION__, __LINE__, m_loadFinished);
        fflush(stderr);
		return;
	}

    if(m_isPlaybackEnded)
    {
        fprintf(stderr, "\n***** %s::%s(%d)\tcall to RunCommand(MEDIAPLAYER.Seek) ignored since m_isPlaybackEnded = %d\n", __FILE__, __FUNCTION__, __LINE__, m_isPlaybackEnded);
        fflush(stderr);
        return;
    }

    if(m_duration <= 0.0 && position <= 0.0)
    {
        fprintf(stderr, "\n***** %s::%s(%d)\tcall to RunCommand(MEDIAPLAYER.Seek) ignored since m_duration = %f && position = %f\n", __FILE__, __FUNCTION__, __LINE__, m_duration, position);
        fflush(stderr);
        return;
    }
#endif

//  fprintf(stderr, "***** %s::%s(%d)\tcalling RunCommand(MEDIAPLAYER.seek) position = %f\n", __FILE__, __FUNCTION__, __LINE__, position);
//  printState(__FUNCTION__, __LINE__);

    QVariantMap parameters;
    parameters.insert(QString::fromAscii("position"), QVariant(100.0 * position / m_player->duration() ));
    QVariant result = RunCommand(QString::fromAscii("MEDIAPLAYER.Seek"), parameters);

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
    return false; //FIXME: is it OK to return false? maybe need to wait for player event "finished seeking" if exists
}

float MediaPlayerPrivate::duration() const
{
//  fprintf(stderr, "*** %s::%s(%d) called\n", __FILE__, __FUNCTION__, __LINE__);
//    if (m_readyState < MediaPlayer::HaveMetadata)
//        return 0.0f;
	if(!m_loadFinished)
	{
//  	fprintf(stderr, "\n*** %s::%s(%d)\tload hasn't finished - returning 0\n", __FILE__, __FUNCTION__, __LINE__);
		return 0.0f;
	}

    if (m_duration >= 0.0f)
        return m_duration;

    QVariantMap parameters;
    QVariant result = RunCommand(QString::fromAscii("MEDIAPLAYER.Duration"), parameters, true);
    float res = result.toFloat();
    if (res != 0.0f)
    {
        MediaPlayerPrivate* tp = (MediaPlayerPrivate*)this;
        tp->m_duration = (res == 0.0 ? std::numeric_limits<float>::infinity() : res);
//      tp->setloaded(); //fixme: verify it is safe to comment this
        fprintf(stderr, "\n*** %s::%s(%d):\tcalling m_player->timeChanged()\n", __FILE__, __FUNCTION__, __LINE__);
        m_player->timeChanged();
    }

    return res;
}

float MediaPlayerPrivate::currentTime() const
{
    return m_current;
}

PassRefPtr<TimeRanges> MediaPlayerPrivate::buffered() const
{
/**
 *  this function is called by the browser's player in order to
 *  update the progress bar indicating the length (in seconds,
 *  float) of the video that has been buffered by the player
 */

  RefPtr<TimeRanges> buffered = TimeRanges::create();
  if(!m_isBuffering)
  {
      if(m_buffered > 1)
          buffered->add(0, m_buffered);
  }
  else
      buffered->add(0, m_current);

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
  (void)rate;
  //fprintf(stderr, "=========== %s %s %f ===========\n", __FILE__, __FUNCTION__, rate);
    notImplemented();
}

void MediaPlayerPrivate::setVolume(float volume)
{
    QVariantMap parameters;
    parameters.insert(QString::fromAscii("volume"), QVariant(QVariant(volume).toString()));
    RunCommand(QString::fromAscii("MEDIAPLAYER.SetVolume"), parameters);
}

bool MediaPlayerPrivate::supportsMuting() const
{
    return true;
}

void MediaPlayerPrivate::setMuted(bool muted)
{
    QVariantMap parameters;
    parameters.insert(QString::fromAscii("muted"), QVariant(muted));
    RunCommand(QString::fromAscii("MEDIAPLAYER.SetMuted"), parameters);
}

MediaPlayer::NetworkState MediaPlayerPrivate::networkState() const
{
  //fprintf(stderr, "=========== %s %s ===========\n", __FILE__, __FUNCTION__);
//fprintf(stderr, "***** %s::%s(%d)\tm_networkState = %d\n", __FILE__, __FUNCTION__, __LINE__, m_networkState);
    return m_networkState;
}

MediaPlayer::ReadyState MediaPlayerPrivate::readyState() const
{
  //fprintf(stderr, "=========== %s %s ===========\n", __FILE__, __FUNCTION__);
    return m_readyState;
}

void MediaPlayerPrivate::setVisible(bool visible)
{
  //fprintf(stderr, "=========== %s %s %d ===========\n", __FILE__, __FUNCTION__, visible);
    m_isVisible = visible;
}

void MediaPlayerPrivate::setSize(const IntSize& size)
{
  //fprintf(stderr, "=========== %s %s %d %d ===========\n", __FILE__, __FUNCTION__, size.width(), size.height());
  m_size = size;
}

IntSize MediaPlayerPrivate::naturalSize() const
{
    return m_naturalSize;
}

void MediaPlayerPrivate::paint(GraphicsContext* context, const IntRect& rect)
{
    if (context->paintingDisabled())
        return;

    if (!m_isVisible && !m_isBuffering)
        return;

    if (!m_paintedOnce || m_videoRect != rect)
    {
        int offsetX = 0;
        int offsetY = 0;
#ifdef XP_EMBEDDED
        ::GetBrowserOffsets(&offsetX, &offsetY);
#endif

        m_videoRect = rect;
        m_videoRect.setX(m_videoRect.x() + offsetX);
        m_videoRect.setY(m_videoRect.y() + offsetY);

		QVariantMap parameters;
		parameters.insert(QString::fromAscii("x"), QVariant(m_videoRect.x()));
		parameters.insert(QString::fromAscii("y"), QVariant(m_videoRect.y()));
		parameters.insert(QString::fromAscii("width"), QVariant(m_videoRect.width()));
		parameters.insert(QString::fromAscii("height"), QVariant(m_videoRect.height()));
		RunCommand(QString::fromAscii("MEDIAPLAYER.Paint"), parameters);
		m_paintedOnce = true;
     }

	FloatRect fr(rect.x(), rect.y(), rect.width(), rect.height());
	context->clearRect(fr);
}

#if USE(ACCELERATED_COMPOSITING)
void MediaPlayerPrivate::acceleratedRenderingStateChanged()
{
  //fprintf(stderr, "=========== %s %s ===========\n", __FILE__, __FUNCTION__);
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
