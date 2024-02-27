#!/bin/bash

# Copyright (C) KolibriOS team 2024. All rights reserved.
# Distributed under terms of the GNU General Public License

set -e

TARGET=i586-kolibrios
KOS_SDK=/opt/kolibrios-sdk

mkdir -p kos-build
cd kos-build

../configure --target=$TARGET \
             --prefix=$KOS_SDK/toolchain \
             --with-sysroot=$KOS_SDK/sysroot \
             --disable-nls \
             --enable-shared \
             --enable-languages=c,c++ \
             --disable-threads

make -j8 all-gcc
