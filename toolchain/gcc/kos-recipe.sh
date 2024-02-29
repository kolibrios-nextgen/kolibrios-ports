#!/bin/bash

source ../../scripts/start-recipe

BUILD()
{
    # FIXME: Perhaps this should be included in the Newlib recipe
    cp -af ../../libraries/newlib/libc/include/. "$SDK_INSTALL_DIR/sysroot/include"
    msg "Newlib headers install successful!"

    mkdir -p build
    cd build

    ../configure --target=$TARGET \
                 --prefix="$SDK_INSTALL_DIR/toolchain" \
                 --with-sysroot="$SDK_INSTALL_DIR/sysroot" \
                 --disable-nls \
                 --enable-shared \
                 --enable-languages=c,c++ \
                 --disable-threads

    make -j$NUM_JOBS all-gcc
    msg "GCC build successful!"

    # FIXME: libgcc is built, but without thread support (--disable-threads). It needs to be implemented
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
