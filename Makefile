VERSION := 1.0.3
.PHONY: release test version

ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell uname -s)
endif

$(info ************************ Building on $(DETECTED_OS) ******************************)

ifeq ($(DETECTED_OS),Windows)
	CC := gcc
	LDFLAGS := -Wl,--kill-at -D_JNI_IMPLEMENTATION -static-libgcc -shared -lm
	LIBS := libs/win/libmupdf.a libs/win/libfreetype.a libs/win/libjbig2dec.a \
			libs/win/libjpeg.a libs/win/libopenjpeg.a libs/win/libz.a
	TARGET_LIB_EXTENSION := dll
	TARGET_EXENSION := exe
endif	
ifeq ($(DETECTED_OS),Darwin)
	CC := clang
	LDFLAGS := -Wl,-no_compact_unwind -dynamiclib -lm
	LIBS := libs/mac/libmupdf.a libs/mac/libfreetype.a libs/mac/libjbig2dec.a \
			libs/mac/libjpeg.a libs/mac/libopenjpeg.a libs/mac/libz.a
	TARGET_LIB_EXTENSION := jnilib
	TARGET_EXENSION := out
endif

CFLAGS := -c -m64 -O2 -fPIC -Wall -I headers/ $(shell pkg-config --cflags check)
TEST-LDFLAGS := $(shell pkg-config --libs check)

RELEASE_OUT := build/release
SRC := src
RELEASE_OBJECTS := 	$(RELEASE_OUT)/pdftrick_native.o \
					$(RELEASE_OUT)/pdftrick_render.o \
					$(RELEASE_OUT)/page_render.o

TEST_OUT := build/test
TEST := test
TEST_OBJECTS := $(TEST_OUT)/test_runner.o \
				$(TEST_OUT)/check_render_thumbnail.o \
				$(TEST_OUT)/check_pdftrick_render.o

# ----------------------------------------------- VERSION -----------------------------------------------
version:
	@echo v$(VERSION)
# ----------------------------------------------- RELEASE -----------------------------------------------
release: clean-release compile-release link-release

clean-release: 
	rm -rf build/release 
	mkdir -p build/release

compile-release: $(RELEASE_OBJECTS)
$(RELEASE_OBJECTS): $(RELEASE_OUT)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ $< 

link-release:
	$(CC) $(LDFLAGS) $(wildcard build/release/*.o) $(LIBS) \
	-o build/release/pdftrick-native_$(VERSION).$(TARGET_LIB_EXTENSION)

# ----------------------------------------------- TEST -----------------------------------------------
test: clean-test clean-release compile-release compile-test link-test run-test

clean-test:		
	rm -rf build/test
	mkdir -p build/test
	rm -rf test/out-files
	mkdir -p test/out-files

compile-test: $(TEST_OBJECTS)
$(TEST_OBJECTS): $(TEST_OUT)/%.o: $(TEST)/%.c
	$(CC) $(CFLAGS) -o $@ $< 

link-test:	
	$(CC) $(RELEASE_OBJECTS) $(TEST_OBJECTS) $(TEST-LDFLAGS) $(LIBS) \
	-o build/test/all_tests.$(TARGET_EXENSION)

run-test:
	build/test/all_tests.$(TARGET_EXENSION)

