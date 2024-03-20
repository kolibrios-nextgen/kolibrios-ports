/* Operating system specific defines to be used when targeting
   GCC for KolibriOS
   Copyright (C) 1997-2023 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.

Copyright (C) KolibriOS team 2024. All rights reserved.
Distributed under terms of the GNU General Public License */

/* Additional predefined macros. */
#define EXTRA_OS_CPP_BUILTINS() \
  do  \
    { \
      builtin_define ("__KOS__");           \
      builtin_define ("__KOLIBRIOS__");     \
      builtin_define ("_KOLIBRI");          \
      builtin_define ("KOLIBRI");           \
    }                                       \
  while (0)

/* Always link libgcc */
#undef LIBGCC_SPEC
#define LIBGCC_SPEC "-lgcc"

#undef REAL_LIBGCC_SPEC
#define REAL_LIBGCC_SPEC LIBGCC_SPEC

/* For KolibriOS applications always link libc.a */
#undef LIB_SPEC
#define LIB_SPEC "%{!shared: %{!mdll: -Tkos-app.lds}} -lc"

#define LINK_SPEC "%{mwindows:--subsystem windows} \
  %{mconsole:--subsystem console} \
  %{shared: %{mdll: %eshared and mdll are not compatible}} \
  %{shared: --shared} %{mdll: --dll} \
  %{shared|mdll: --image-base=0} \
  %{!shared: %{!mdll: -Bstatic --image-base=0}} --file-alignment=16 --section-alignment=16"

/* Stub! Start file not used. */
#undef STARTFILE_SPEC
#define STARTFILE_SPEC ""

/* Stub! End file not used. */
#undef ENDFILE_SPEC
#define ENDFILE_SPEC ""

/* Running objcopy for KolibriOS applications */
#undef POST_LINK_SPEC
#define POST_LINK_SPEC "%{!shared: %{!mdll: i586-kolibrios-objcopy -Obinary %{o*:%*} %{!o*:a.exe} }}"

/* Native header directory */
#undef NATIVE_SYSTEM_HEADER_DIR
#define NATIVE_SYSTEM_HEADER_DIR "/include"

/* Don't use ".exe" suffix by default for KolibriOS */
#undef TARGET_EXECUTABLE_SUFFIX
#define TARGET_EXECUTABLE_SUFFIX ""

/* Stub! "-pthread" is not supported for KolibriOS. */
#undef GOMP_SELF_SPECS
#define GOMP_SELF_SPECS ""
#undef GTM_SELF_SPECS
#define GTM_SELF_SPECS ""
