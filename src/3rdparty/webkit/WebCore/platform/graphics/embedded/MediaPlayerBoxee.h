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

#ifndef MediaPlayerPrivateBoxee_h
#define MediaPlayerPrivateBoxee_h

#include "MediaPlayerPrivate.h"
#include "qjson/serializer.h"
#include "qjson/parser.h"
#include "HTMLMediaElement.h"

#include <QObject>
#include <QVariant>

namespace WebCore {

class MediaPlayerPrivate : public QObject, public MediaPlayerPrivateInterface {

    Q_OBJECT

public:
    static MediaPlayerPrivateInterface* create(MediaPlayer* player);
    ~MediaPlayerPrivate();

    static void registerMediaEngine(MediaEngineRegistrar);
    static void getSupportedTypes(HashSet<String>&);
    static MediaPlayer::SupportsType supportsType(const String&, const String&);
    static bool isAvailable() { return true; }

    bool hasVideo() const;
    bool hasAudio() const;

    void load(const String &url);
    void cancelLoad();

    void play();
    void pause();

    bool paused() const;
    bool seeking() const;

    float duration() const;
    float currentTime() const;
    void seek(float);

    void setRate(float);
    void setVolume(float);

    bool supportsMuting() const;
    void setMuted(bool);

    MediaPlayer::NetworkState networkState() const;
    MediaPlayer::ReadyState readyState() const;

    PassRefPtr<TimeRanges> buffered() const;
    float maxTimeSeekable() const;
    unsigned bytesLoaded() const;
    unsigned totalBytes() const;

    void setVisible(bool);

    IntSize naturalSize() const;
    void setSize(const IntSize&);

    void paint(GraphicsContext*, const IntRect&);

    bool supportsFullscreen() const { return false; }

#if USE(ACCELERATED_COMPOSITING)
    // whether accelerated rendering is supported by the media engine for the current media.
    virtual bool supportsAcceleratedRendering() const { return true; }
    // called when the rendering system flips the into or out of accelerated rendering mode.
    virtual void acceleratedRenderingStateChanged();
    // returns an object that can be directly composited via GraphicsLayerQt (essentially a QGraphicsItem*)
    virtual PlatformLayer* platformLayer() const;
#endif

private:

    Timer<MediaPlayerPrivate> m_stateTimer;
    void stateTimer(Timer<MediaPlayerPrivate>*);
    void checkLoadingStatus();
    void updatePlayerStatus();
    void setloaded();
    MediaPlayerPrivate(MediaPlayer*);
    QVariant RunCommand(QString command, QVariantMap parameters, bool expectedResult = false) const;
    void printState(const char* label, int line);
    void restartPlayback();

    QJson::Serializer m_serializer;
    MediaPlayer* m_player;
    HTMLMediaElement* m_element;
    bool m_composited;
    bool m_isVisible;
    IntRect m_videoRect;
    bool m_paused;
    IntSize m_size, m_naturalSize;
    MediaPlayer::NetworkState m_networkState;
    MediaPlayer::ReadyState m_readyState;
    float m_duration;
    float m_current;
    float m_buffered;
    bool m_paintedOnce;
    int m_isBuffering;
    unsigned m_bytesLoaded;
    bool m_bSentEndedEvent;
    bool m_loadFinished;
    bool m_isPlaybackEnded;
    String m_url;
    bool m_isVideo;

};
}

#endif // MediaPlayerPrivateQt_h
