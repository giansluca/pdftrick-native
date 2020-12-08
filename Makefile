ifeq ($(OS),Windows_NT) 
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell uname -s)
endif

$(info ************************ Building on $(DETECTED_OS) ******************************)

ifeq ($(DETECTED_OS),Windows)
	CC=gcc
	LFLAGS=-Wl,--kill-at -D_JNI_IMPLEMENTATION -static-libgcc -shared -lm
	PATH_LIB=libs/win
	TARGET_LIB_EXTENSION=dll
	TARGET_EXENSION=exe
endif	
ifeq ($(DETECTED_OS),Darwin)
	CC=clang
	LFLAGS=-Wl,-no_compact_unwind -dynamiclib -lm
	PATH_LIB=libs/mac
	TARGET_LIB_EXTENSION=jnilib
	TARGET_EXENSION=out
endif

CFLAGS=-c -m64 -O2 -fPIC -Wall -I headers/
VERSION=1.0.1

# ----------------------------------------------- RELEASE -----------------------------------------------
release: setup-release \
		compile-release-pdftrick_native \
		compile-release-pdftrick_render \
		compile-release-page_render \
		link-release
setup-release: 
				rm -rf build/release 
				mkdir -p build/release
compile-release-pdftrick_native:
				$(CC) $(CFLAGS) -o build/release/pdftrick_native.o src/pdftrick_native.c
compile-release-pdftrick_render:
				$(CC) $(CFLAGS) -o build/release/pdftrick_render.o src/pdftrick_render.c
compile-release-page_render:
				$(CC) $(CFLAGS) -o build/release/page_render.o src/page_render.c
link-release:
				$(CC) $(LFLAGS) \
				build/release/pdftrick_native.o \
				build/release/pdftrick_render.o \
				build/release/page_render.o \
				$(PATH_LIB)/libmupdf.a \
				$(PATH_LIB)/libfreetype.a \
				$(PATH_LIB)/libjbig2dec.a \
				$(PATH_LIB)/libjpeg.a \
				$(PATH_LIB)/libopenjpeg.a \
				$(PATH_LIB)/libz.a \
				-o build/release/pdftrick-native_$(VERSION).$(TARGET_LIB_EXTENSION)

# ----------------------------------------------- DEBUG -----------------------------------------------
debug: setup-debug \
		compile-debug-pdftrick_native \
		compile-debug-pdftrick_render \
		compile-debug-page_render \
		link-debug
setup-debug:
				rm -rf build/debug
				mkdir -p build/debug
compile-debug-pdftrick_native:
				$(CC) $(CFLAGS) -g -o build/debug/pdftrick_native.o src/pdftrick_native.c
compile-debug-pdftrick_render:
				$(CC) $(CFLAGS) -g -o build/debug/pdftrick_render.o src/pdftrick_render.c
compile-debug-page_render:
				$(CC) $(CFLAGS) -g -o build/debug/page_render.o src/page_render.c
link-debug:
				$(CC) $(LFLAGS) \
				build/debug/pdftrick_native.o \
				build/debug/pdftrick_render.o \
				build/debug/page_render.o \
				$(PATH_LIB)/libmupdf.a \
				$(PATH_LIB)/libfreetype.a \
				$(PATH_LIB)/libjbig2dec.a \
				$(PATH_LIB)/libjpeg.a \
				$(PATH_LIB)/libopenjpeg.a \
				$(PATH_LIB)/libz.a \
				-o build/debug/pdftrick-native_$(VERSION).$(TARGET_LIB_EXTENSION)

# ----------------------------------------------- TEST -----------------------------------------------
test: setup-test \
		compile-test-main \
		compile-test-pdftrick_native \
		compile-test-pdftrick_render \
		compile-test-page_render \
		link-test
setup-test:		
				rm -rf build/test
				mkdir -p build/test
compile-test-main:
				$(CC) $(CFLAGS) -g -o build/test/main.o test/main.c
compile-test-pdftrick_native:
				$(CC) $(CFLAGS) -g -o build/test/pdftrick_native.o src/pdftrick_native.c
compile-test-pdftrick_render:
				$(CC) $(CFLAGS) -g -o build/test/pdftrick_render.o src/pdftrick_render.c
compile-test-page_render:
				$(CC) $(CFLAGS) -g -o build/test/page_render.o src/page_render.c
link-test:
				$(CC) \
				build/test/main.o \
				build/test/pdftrick_native.o \
				build/test/pdftrick_render.o \
				build/test/page_render.o \
				$(PATH_LIB)/libmupdf.a \
				$(PATH_LIB)/libfreetype.a \
				$(PATH_LIB)/libjbig2dec.a \
				$(PATH_LIB)/libjpeg.a \
				$(PATH_LIB)/libopenjpeg.a \
				$(PATH_LIB)/libz.a \
				-o build/test/test.$(TARGET_EXENSION)
