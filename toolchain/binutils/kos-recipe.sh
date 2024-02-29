#!/bin/bash

source ../../scripts/start-recipe

BUILD()
{
    mkdir -p build
    cd build
    ../configure --target=$TARGET \
                 --prefix="$SDK_INSTALL_DIR/toolchain" \
                 --with-sysroot="$SDK_INSTALL_DIR/sysroot" \
                 --disable-werror \
                 --disable-nls \
                 --disable-intl \
                 --disable-sim \
                 --disable-gdb \
                 --enable-shared

    make -j$NUM_JOBS
    msg "Binutils build successful!"
    cd ..
}

INSTALL()
{
    cd build
    make install-strip
    msg "Binutils install successful!"
    cd ..
}

CLEAN()
{
    rm -rf build
    msg "Binutils build artifacts removed!"
}

source ../../scripts/end-recipe
