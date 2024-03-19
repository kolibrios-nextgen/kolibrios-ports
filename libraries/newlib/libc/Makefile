CC = i586-kolibrios-gcc
AR = CC = i586-kolibrios-ar

INSTALLDIR:= /opt/kolibrios-sdk-bin/sysroot

CFLAGS = -c -O2 -fno-builtin -fno-ident -fomit-frame-pointer -Iinclude
CFLAGS+= -D_MB_EXTENDED_CHARSETS_WINDOWS=1
CFLAGS+= -D_IEEE_LIBM -DHAVE_RENAME -DBUILD_LIBC_ -DPACKAGE_NAME=\"newlib\"
CFLAGS+= -DPACKAGE_TARNAME=\"newlib\" -DPACKAGE_VERSION=\"2.4.0\"
CFLAGS+= -DPACKAGE_STRING=\"newlib\ 2.4.0\" -DPACKAGE_BUGREPORT=\"\" -DPACKAGE_URL=\"\"
CFLAGS+= -DMISSING_SYSCALL_NAMES
CFLAGS+= -DSTRING_ONLY -DINTEGER_ONLY

ARFLAGS = crs

LIBC_SRCS = $(shell find . -name '*.c' -or -name '*.S' -or -name '*.asm' )
LIBC_OBJS := $(LIBC_SRCS:.c=.o) 
LIBC_OBJS := $(LIBC_OBJS:.S=.o)
LIBC_OBJS := $(LIBC_OBJS:.asm=.o) 

.PHONY: all install clean 

all: libc.a

libc.a: $(LIBC_OBJS) $(LIBC_SRCS) Makefile
	$(AR) $(ARFLAGS) libc.a $(LIBC_OBJS)

install: libc.a
	install -D libc.a $(INSTALLDIR)/lib/libc.a

%.o : %.asm Makefile
	fasm $< $@

%.o : %.c Makefile
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.S Makefile
	$(CC) $(CFLAGS) -o $@ $<

clean:
	echo $(LIBC_OBJS)
