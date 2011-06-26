#!/bin/sh

./configure \
  -arch "x86" \
  -opensource \
  -confirm-license \
  -debug \
  -openssl-linked \
  -reduce-relocations \
  -no-gfx-linuxfb \
  -webkit \
  -qt-libtiff \
  -qt-libmng \
  -no-libjpeg \
  -qt-libjpeg \
  -qt-libpng \
  -qt-gif  \
  -no-cups \
  -no-qt3support \
  -no-sql-postgres \
  -no-sql-mysql \
  -no-sql-oracle \
  -no-nis \
  -no-dbus \
  -nomake "examples demos" \
  -xmlpatterns \
  -exceptions \
&& make -j8 -k

