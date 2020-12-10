ifeq ($(OS),Windows_NT) 
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell uname -s)
endif

$(info ************************ Building on $(DETECTED_OS) ******************************)

ifeq ($(DETECTED_OS),Windows)
	CC := gcc
	LFLAGS := -Wl,--kill-at -D_JNI_IMPLEMENTATION -static-libgcc -shared -lm
	LIBS := libs/win/libmupdf.a libs/win/libfreetype.a libs/win/libjbig2dec.a \
			libs/win/libjpeg.a libs/win/libopenjpeg.a libs/win/libz.a
	TARGET_LIB_EXTENSION := dll
	TARGET_EXENSION := exe
endif	
ifeq ($(DETECTED_OS),Darwin)
	CC := clang
	LFLAGS := -Wl,-no_compact_unwind -dynamiclib -lm
	LIBS := libs/mac/libmupdf.a libs/mac/libfreetype.a libs/mac/libjbig2dec.a \
			libs/mac/libjpeg.a libs/mac/libopenjpeg.a libs/mac/libz.a
	TARGET_LIB_EXTENSION := jnilib
	TARGET_EXENSION := out
endif

CFLAGS := -c -m64 -O2 -fPIC -Wall -I headers/
OBJECTS := $(wildcard build/release/*.o)
VERSION := 1.0.1

# ----------------------------------------------- RELEASE -----------------------------------------------
release: setup-release compile-release link-release
setup-release: 
				rm -rf build/release 
				mkdir -p build/release
compile-release:
				$(CC) $(CFLAGS) -o build/release/pdftrick_native.o src/pdftrick_native.c
				$(CC) $(CFLAGS) -o build/release/pdftrick_render.o src/pdftrick_render.c
				$(CC) $(CFLAGS) -o build/release/page_render.o src/page_render.c
link-release:
				$(CC) $(LFLAGS) $(wildcard build/release/*.o) $(LIBS)
				-o build/release/pdftrick-native_$(VERSION).$(TARGET_LIB_EXTENSION)

# ----------------------------------------------- TEST -----------------------------------------------
test: setup-test compile-test link-test
setup-test:		
				rm -rf build/test
				mkdir -p build/test
				rm -rf test/out-files
				mkdir -p test/out-files
compile-test:
				$(CC) $(CFLAGS) -g -o build/test/render-test.o test/render-test.c
				$(CC) $(CFLAGS) -g -o build/test/pdftrick_native.o src/pdftrick_native.c
				$(CC) $(CFLAGS) -g -o build/test/pdftrick_render.o src/pdftrick_render.c
				$(CC) $(CFLAGS) -g -o build/test/page_render.o src/page_render.c
link-test:	
				$(CC) $(wildcard build/test/*.o) $(LIBS) \
				-o build/test/test.$(TARGET_EXENSION)

