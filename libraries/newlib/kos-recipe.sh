#!/bin/bash

source ../../scripts/start-recipe

BUILD()
{
    cd libc
    make -j$NUM_JOBS CC=$TARGET-gcc AR=$TARGET-ar
    msg "Newlib build successful!"
    cd ..
}

INSTALL()
{
    cd libc
    make install INSTALLDIR=$SDK_INSTALL_DIR
    msg "Newlib install successful!"
    cd ..
}

CLEAN()
{
    cd libc
    make clean
    msg "Newlib build artifacts removed!"
    cd ..
}

source ../../scripts/end-recipe
