#!/bin/bash

# Copyright (C) KolibriOS-NG team 2024. All rights reserved
# Distributed under terms of the GNU General Public License

source scripts/start-recipe

ROOT_DIR="$PWD"

declare -a DIRS=(
    "toolchain/binutils"
    "toolchain/gcc"
    "libraries/newlib"
)

BUILD()
{
    for dir in "${DIRS[@]}" ; do
        cd "$ROOT_DIR/$dir"
        ./kos-recipe.sh
    done
}

INSTALL() 
{
    msg "For root recipes, installation is performed in BUILD"
}

CLEAN()
{
    for dir in "${DIRS[@]}" ; do
        cd "$ROOT_DIR/$dir"
        ./kos-recipe.sh --clean
    done
}

source scripts/end-recipe
