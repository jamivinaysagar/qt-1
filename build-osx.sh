#!/bin/sh

./configure \
  -opensource \
  -confirm-license \
  -release \
  -openssl-linked \
  -reduce-relocations \
  -no-gfx-linuxfb \
  -webkit \
  -no-cups \
  -no-qt3support \
  -no-sql-postgres \
  -no-sql-mysql \
  -no-sql-oracle \
  -no-nis \
  -no-3dnow \
  -nomake "examples demos" \
  -no-dbus \
  -no-phonon \
  -no-phonon-backend \
  -xmlpatterns \
  -exceptions \
&& make -j8 -k

