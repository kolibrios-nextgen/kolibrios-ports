#!/bin/bash

source ../../scripts/start-recipe

BUILD()
{
    cd src
    make -j$NUM_JOBS CC=$TARGET-gcc AR=$TARGET-ar NASM=nasm
    msg "SDL-1.2.2 build successful!"
    cd ..
}

INSTALL()
{
    cd src
    make install INSTALLDIR=$SDK_SYSROOT_DIR
    msg "SDL-1.2.2 install successful!"
    cd ..
}

CLEAN()
{
    cd src
    make clean
    msg "SDL-1.2.2 build artifacts removed!"
    cd ..
}

source ../../scripts/end-recipe
