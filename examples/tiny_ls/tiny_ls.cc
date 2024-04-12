/*
 * Copyright (C) KolibriOS-NG team 2024. All rights reserved.
 * Distributed under terms of the GNU General Public License
 */

/* This is a small demo that displays the contents
   of the current directory (directories are highlighted in blue). */

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace color_console {
constexpr auto blue = "\x1B[34m";
constexpr auto reset = "\x1B[0m";
}

int main()
{
    fs::path cwd = fs::current_path();
    std::cout << "Contents of the " << cwd << " directory:" << std::endl;

    for (const auto& entry : fs::directory_iterator(cwd)) {
        if (entry.is_directory()) {
            std::cout << color_console::blue;
        }

        std::cout << entry.path().filename() << color_console::reset << std::endl;
    }

    return 0;
}
