#!/bin/bash

source ../../scripts/start-recipe

BUILD()
{
    $TARGET-g++ -std=c++17 tiny_ls.cc -o tiny_ls
    msg "tiny_ls example build successful!"
}

INSTALL()
{
    install -D tiny_ls "$SDK_SYSROOT_DIR/bin/tiny_ls"
    msg "tiny_ls install successful!"
    cd ..
}

CLEAN()
{
    rm -f tiny_ls
    msg "tiny_ls build artifacts removed!"
}

source ../../scripts/end-recipe
