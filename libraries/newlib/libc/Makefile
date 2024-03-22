CFLAGS = -c -Os -fno-builtin -fno-ident -fomit-frame-pointer -Iinclude
CFLAGS+= -D_MB_EXTENDED_CHARSETS_WINDOWS=1
CFLAGS+= -D_IEEE_LIBM -DHAVE_RENAME -DBUILD_LIBC -DPACKAGE_NAME=\"newlib\"
CFLAGS+= -DPACKAGE_TARNAME=\"newlib\" -DPACKAGE_VERSION=\"2.4.0\"
CFLAGS+= -DPACKAGE_STRING=\"newlib\ 2.4.0\" -DPACKAGE_BUGREPORT=\"\" -DPACKAGE_URL=\"\"
CFLAGS+= -DMISSING_SYSCALL_NAMES

ARFLAGS = crs

LIBC_SRCS = $(shell find . -name '*.c' -or -name '*.S' -or -name '*.asm' )
LIBC_OBJS := $(LIBC_SRCS:.c=.o) 
LIBC_OBJS := $(LIBC_OBJS:.S=.o)
LIBC_OBJS := $(LIBC_OBJS:.asm=.o) 

# Objects with special build rules
LIBC_OBJS+= \
	stdio/svfiprintf.o \
	stdio/svfprintf.o \
	stdio/vfiprintf.o \
	stdio/vfprintf.o \
	stdio/svfiwprintf.o \
	stdio/svfwprintf.o \
	stdio/vfiwprintf.o \
	stdio/vfwprintf.o \
	stdio/svfiscanf.o \
	stdio/svscanf.o \
	stdio/vfscanf.o \
	stdio/vfiscanf.o \
	stdio/svfiwscanf.o \
	stdio/svfwscanf.o \
	stdio/vfiwscanf.o \
	time/wcsftime.o

.PHONY: all install clean 

all: libc.a

libc.a: $(LIBC_OBJS) $(LIBC_SRCS) Makefile
	$(AR) $(ARFLAGS) libc.a $(LIBC_OBJS)

install: libc.a
	install -D libc.a $(INSTALLDIR)/lib/libc.a
	install -D ../kos-app.lds $(INSTALLDIR)/lib/kos-app.lds

reent/renamer.o: reent/renamer.c
	$(CC) $(CFLAGS) -D_COMPILING_NEWLIB reent/renamer.c -o $@
 
stdio/svfiprintf.o: stdio/vfprintf.c
	$(CC) $(CFLAGS) -fshort-enums -DINTEGER_ONLY -DSTRING_ONLY stdio/vfprintf.c -o $@
 
stdio/svfprintf.o: stdio/vfprintf.c
	$(CC) $(CFLAGS) -fshort-enums -DSTRING_ONLY stdio/vfprintf.c -o $@
 
stdio/vfiprintf.o: stdio/vfprintf.c
	$(CC) $(CFLAGS) -fshort-enums -DINTEGER_ONLY stdio/vfprintf.c -o $@
 
stdio/vfprintf.o: stdio/vfprintf.c
	$(CC) $(CFLAGS) -fshort-enums stdio/vfprintf.c -o $@
 
stdio/svfiwprintf.o: stdio/vfwprintf.c
	$(CC) $(CFLAGS) -fshort-enums -DINTEGER_ONLY -DSTRING_ONLY stdio/vfwprintf.c -o $@
 
stdio/svfwprintf.o: stdio/vfwprintf.c
	$(CC) $(CFLAGS) -fshort-enums -DSTRING_ONLY stdio/vfwprintf.c -o $@
 
stdio/vfiwprintf.o: stdio/vfwprintf.c
	$(CC) $(CFLAGS) -fshort-enums -DINTEGER_ONLY stdio/vfwprintf.c -o $@
 
stdio/vfwprintf.o: stdio/vfwprintf.c
	$(CC) $(CFLAGS) -fshort-enums stdio/vfwprintf.c -o $@
 
stdio/svfiscanf.o: stdio/vfscanf.c
	$(CC) $(CFLAGS) -DINTEGER_ONLY -DSTRING_ONLY  stdio/vfscanf.c -o $@
 
stdio/svscanf.o: stdio/vfscanf.c
	$(CC) $(CFLAGS) -DSTRING_ONLY  stdio/vfscanf.c -o $@
 
stdio/vfscanf.o: stdio/vfscanf.c
	$(CC) $(CFLAGS) stdio/vfscanf.c -o $@
 
stdio/vfiscanf.o: stdio/vfscanf.c
	$(CC) $(CFLAGS) -DINTEGER_ONLY  stdio/vfscanf.c -o $@
 
stdio/svfiwscanf.o: stdio/vfwscanf.c
	$(CC) $(CFLAGS) -DINTEGER_ONLY -DSTRING_ONLY  stdio/vfwscanf.c -o $@
 
stdio/svfwscanf.o: stdio/vfwscanf.c
	$(CC) $(CFLAGS) -DSTRING_ONLY stdio/vfwscanf.c -o $@
 
stdio/vfiwscanf.o: stdio/vfwscanf.c
	$(CC) $(CFLAGS) -DINTEGER_ONLY stdio/vfwscanf.c -o $@
 
time/wcsftime.o: time/strftime.c
	$(CC) $(CFLAGS) -DMAKE_WCSFTIME time/strftime.c -o $@

%.o : %.asm Makefile
	fasm $< $@

%.o : %.c Makefile
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.S Makefile
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(LIBC_OBJS) libc.a
