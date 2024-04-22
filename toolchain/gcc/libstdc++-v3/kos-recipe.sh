#!/bin/bash

# Copyright (C) KolibriOS-NG team 2024. All rights reserved
# Distributed under terms of the GNU General Public License

source ../../../scripts/start-recipe

BUILD()
{
    mkdir -p build
    cd build

    ../configure --target=$TARGET \
                 --host=$TARGET \
                 --prefix="$SDK_TOOLCHAIN_DIR/$TARGET" \
                 --disable-nls

    make -j$NUM_JOBS all
    msg "Libstdc++-v3 build successful!"

    cd ..
}

INSTALL()
{
    cd build
    make install
    msg "Libstdc++-v3 install successful!"

    cd ..
}

CLEAN()
{
    rm -rf build
    msg "Libstdc++-v3 build artifacts removed!"
}

source ../../../scripts/end-recipe
