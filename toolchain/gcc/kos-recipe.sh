#!/bin/bash

source ../../scripts/start-recipe

BUILD()
{
    # FIXME: Perhaps this should be included in the Newlib recipe
    mkdir -p "$SDK_SYSROOT_DIR"
    cp -af ../../libraries/newlib/libc/include/. "$SDK_SYSROOT_DIR/include"
    msg "Newlib headers install successful!"

    mkdir -p build
    cd build

    ../configure --target=$TARGET \
                 --prefix="$SDK_TOOLCHAIN_DIR" \
                 --with-sysroot="$SDK_SYSROOT_DIR" \
                 --disable-nls \
                 --enable-shared \
                 --enable-languages=c,c++ \
                 --enable-threads=kolibrios

    make -j$NUM_JOBS all-gcc
    msg "GCC build successful!"

    make -j$NUM_JOBS all-target-libgcc
    msg "Libgcc build successful!"

    cd ..
}

INSTALL()
{
    cd build
    make install-strip-gcc
    msg "GCC install successful!"

    make install-target-libgcc
    msg "Libgcc install successful!"

    cd ..
}

CLEAN()
{
    rm -rf build
    msg "GCC build artifacts removed!"
}

source ../../scripts/end-recipe
