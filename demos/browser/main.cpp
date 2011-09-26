/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "browserapplication.h"

#ifdef __cplusplus

#ifdef _WIN32
#define visibility(dummy)
#define __attribute__(dummy)
#endif

extern "C" {
#endif
  __attribute__ ((visibility("default"))) void SetOverrideScreen(bool override)
  {
  }

  __attribute__ ((visibility("default"))) bool IsOverrideScreen()
  {
    return true;
  }

  __attribute__ ((visibility("default"))) bool GetScreenRect(int *x, int *y, int* width, int* height)
  {
    *x = *y = 0;
    *width = 1280;
    *height = 720;
    return true;
  }

  __attribute__ ((visibility("default"))) bool GetBrowserSize(int* width, int* height)
  {
    *width = 1280;
    *height = 720;
    return true;
  }

  __attribute__ ((visibility("default"))) bool GetBrowserOffsets(int* offsetX, int* offsetY)
  {
    *offsetX = *offsetY = 0;
    return true;
  }

  __attribute__ ((visibility("default"))) bool GetBrowserPluginFullscreen(void** pluginView)
  {
    *pluginView = 0;
    return false;
  }

  __attribute__ ((visibility("default"))) bool SetBrowserPluginFullscreen(void* pluginView, bool isFullScreen)
  {
    return true;
  }

  __attribute__ ((visibility("default"))) double GetScaleX()
  {
    return 1.0f;
  }

  __attribute__ ((visibility("default"))) double GetScaleY()
  {
    return 1.0f;
  }

#ifdef __cplusplus
} // extern C
#endif

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(data);
    BrowserApplication application(argc, argv);
    if (!application.isTheOnlyBrowser())
        return 0;
    application.newMainWindow();
    return application.exec();
}

