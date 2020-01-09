# Silence command output by default
.SILENT:

# We're just using make as a task runner
.PHONY: all build bundle run test

# C compiler
CC := gcc

# Debugger
DB := lldb

# Source files & entry point (main.c)
SRC := $(filter-out %_test.c, $(wildcard *.c **/*.c))

# Source file & test files (*_test.c)
TST := $(filter-out main.c, $(wildcard *.c **/*.c))

# Compiler flags
CFLAGS := \
	-std=c11 \
	-I./parsec-sdk/sdk \
	-I/usr/local/opt/openssl/include

# Linker flags
LDFLAGS = \
	-Wl,-rpath,parsec-sdk/sdk/macos \
	-L./ \
	-L/usr/local/opt/openssl/lib \
	-L./parsec-sdk/sdk/android \
	-L./parsec-sdk/sdk/macos \
	-L./parsec-sdk/sdk/ios \
	-L./parsec-sdk/sdk/linux \
	-L./parsec-sdk/sdk/windows

# System libraries (be sure to have these installed)
LIB := \
	-lraylib \
	-lrequest \
	-lparsecapi \
	-lparsec \
	-ljson-c \
	-lcrypto \
	-lssl

# Executable name
BIN := snek

# Default task
all: build

# Builds the app
build:
	clear
	rm -f $(BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIB) $(SRC) -g -o $(BIN)
	echo "Successfully built $(BIN)"

# Builds and runs the app
run: build
	./$(BIN)

# Runs a new build with the debugger
debug: build
	DYLD_PRINT_LIBRARIES=1 $(DB) ./$(BIN)

# Runs the test suite
test:
	clear
	$(CC) $(CFLAGS) $(LDFLAGS) -lcheck $(LIB) $(TST) -o test && ./test || rm test
	rm test
	
# Bundle app for macOS
bundle:
	clear
	rm -f $(BIN)
	$(CC) -Wno-macro-redefined -DSDK_PATH='"../libs/libparsec.dylib"' $(CFLAGS) $(LDFLAGS) $(LIB) $(SRC) -g -o $(BIN)
	echo "Successfully built $(BIN) for release"
	rm -rf $(BIN).app 
	mkdir -p $(BIN).app/Contents/{MacOS,Resources}
	mv $(BIN) $(BIN).app/Contents/MacOS
	dylibbundler -od -b -x ./$(BIN).app/Contents/MacOS/$(BIN) -d ./$(BIN).app/Contents/libs
	touch $(BIN).app/Contents/Info.plist
	echo '<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd"><plist version="1.0"><dict><key>CFBundleExecutable</key><string>$(BIN)</string></dict></plist>' >> $(BIN).app/Contents/Info.plist
	/System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/LaunchServices.framework/Versions/A/Support/lsregister -f $(BIN).app
	echo "Packaged!"