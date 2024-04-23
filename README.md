# KolibriOS-NG C/C++ SDK and ports

This repository contains a GCC cross-compiler specially prepared for 
KolibriOS-NG, as well as ports of libraries and programs

## Build GCC-toolchain
So far this build has only been tested on **Arch Linux**, 
please write to the issue if you have a problem with another **GNU/Linux** distribution.

1. Dependencies need to be installed. For **Arch Linux** it is:
   ```sh
   sudo pacman -S base-devel gmp libmpc mpfr
   ```
   For other distributions, take a look at the [OSDev Wiki](https://wiki.osdev.org/GCC_Cross-Compiler).

2. Prepare the `/opt/kolibrios-sdk` directory for writing. 
   To do this, you can create a symlink to a folder in your home directory.
   Or change the path for `SDK_TOOLCHAIN_DIR` and `SDK_SYSROOT_DIR` in [start-recipe](scripts/start-recipe).

3. Start toolchain build from the repository root (i do not recommend using superuser rights):
   ```sh
   ./build-toolchain.sh
   ```
   At the end of the build, you will have a compiled **GCC** compiler for C and C++, the standard C library and the standard C++ library.

4. You need to add the path to the compiler to the patch `PATH` environment variable. For example, add:
   ```sh
    export PATH=$PATH:/opt/kolibrios-sdk/toolchain/bin
   ``` 
   to your `~/.bashrc` file.

## Usage
You can simply use `i586-kolibrios-gcc` to compile your C program:
```sh
i586-kolibrios-gcc hello.c -o hello
```
There is also a small example in **C++17**: [tiny_ls.cc](examples/tiny_ls/tiny_ls.cc). 
You can build it manually or using the `kos-recipe.sh` script.

## Warning
KolibriOS-NG team comes with ABSOLUTELY NO WARRANTY! You may use this software at your own risk.
This is still far from stable. This may contain a huge number of errors, data races and unimplemented things. 
Therefore, do not hesitate to file a bug report and report problems.

## Authors
- [Maxim Logaev](https://github.com/mxlgv)

## License
Everything that does not relate to ports is distributed under the [GPL 2.0](LICENSE) license.
