#!/bin/bash

# Copyright (C) KolibriOS team 2024. All rights reserved.
# Distributed under terms of the GNU General Public License

set -e

TARGET=i586-kolibrios
KOS_SDK=/opt/kolibrios-sdk

./configure --target=$TARGET \
            --prefix=$KOS_SDK/toolchain \
            --with-sysroot=$KOS_SDK/sysroot \
            --disable-werror \
            --disable-nls \
            --disable-intl \
            --disable-sim \
            --disable-gdb \
            --enable-shared

make -j 8
#make install-strip
