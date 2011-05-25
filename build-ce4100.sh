#!/bin/sh
export BUILD_DEST=/opt/canmore/IntelCE
export PATH=$PATH:$BUILD_DEST/bin
export QT_CFLAGS_DIRECTFB="-D_REENTRANT -I$BUILD_DEST/usr/local/include/directfb"
export QT_LIBS_DIRECTFB="-L$BUILD_DEST/usr/local/lib -ldirectfb -lfusion -ldirect -lpthread"

./configure \
  -embedded x86 \
  -xplatform qws/linux-x86-intelce-g++ \
  -prefix /opt/canmore/local/qt \
  -opensource \
  -confirm-license \
  -release \
  -openssl-linked \
  -reduce-relocations \
  -plugin-kbd-intelceir \
  -qt-kbd-tty \
  -qt-kbd-linuxinput \
  -no-mouse-pc \
  -no-mouse-linuxtp \
  -plugin-gfx-directfb \
  -plugin-gfx-intelce \
  -no-gfx-linuxfb \
  -no-gfx-multiscreen \
  -system-libpng \
  -no-libjpeg \
  -system-libjpeg \
  -depths 8,12,16,24,32 \
  -qt-freetype \
  -webkit \
  -qt-libmng \
  -qt-libtiff \
  -no-cups \
  -no-qt3support \
  -no-sql-postgres \
  -no-sql-mysql \
  -no-sql-oracle \
  -no-phonon \
  -no-phonon-backend \
  -no-nis \
  -no-3dnow \
  -nomake "examples demos" \
  -qt-zlib \
  -declarative \
  -egl  \
  -opengl \
  -openvg \
  -no-dbus \
  -xmlpatterns \
  -exceptions \

