ifeq ($(OS),Windows_NT)
WORKDIR = `echo %cd%`
else
WORKDIR = `pwd`
endif

EXEC_FILE_NAME = WiseMoleClient

ifeq ($(OS),Windows_NT)
PATH_DELIM = \\

MINGW_BIN_PATH = C:\\MinGW\\MinGW\\bin

SDL3_INC_PARAM = -IC:\Dev\SDL\SDL3\include
SDL3_LIB_PARAM = -LC:\Dev\SDL\SDL3\lib\x64

CC = $(MINGW_BIN_PATH)\\gcc.exe
CXX = $(MINGW_BIN_PATH)\\g++.exe

AR = $(MINGW_BIN_PATH)\\ar.exe
LD = $(MINGW_BIN_PATH)\\g++.exe
else
PATH_DELIM = /
CC = gcc
CXX = g++
AR = ar
LD = g++
endif

INC =
CFLAGS = -Wall -fexceptions
RESINC =
LIBDIR =
LIB =
LDFLAGS =

ifeq ($(OS),Windows_NT)
INC_DEBUG = $(INC) $(SDL3_INC_PARAM)
else
INC_DEBUG = $(INC)
endif
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
ifeq ($(OS),Windows_NT)
LDFLAGS_DEBUG = $(LDFLAGS) $(SDL3_LIB_PARAM) -lmingw32 -lSDL3
else
LDFLAGS_DEBUG = $(LDFLAGS) -lSDL3
endif

ifeq ($(OS),Windows_NT)
OBJDIR_DEBUG = obj\\Debug
DEP_DEBUG =
OUT_DEBUG = bin\\Debug\\$(EXEC_FILE_NAME).exe
else
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG =
OUT_DEBUG = bin/Debug/$(EXEC_FILE_NAME)
endif

ifeq ($(OS),Windows_NT)
INC_RELEASE = $(INC) $(SDL3_INC_PARAM)
else
INC_RELEASE = $(INC)
endif
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
ifeq ($(OS),Windows_NT)
LDFLAGS_RELEASE = $(LDFLAGS) $(SDL3_LIB_PARAM) -lmingw32 -lSDL3
else
LDFLAGS_RELEASE = $(LDFLAGS) -lSDL3
endif

ifeq ($(OS),Windows_NT)
OBJDIR_RELEASE = obj\\Release
DEP_RELEASE =
OUT_RELEASE = bin\\Release\\$(EXEC_FILE_NAME).exe
else
OBJDIR_RELEASE = obj/Release
DEP_RELEASE =
OUT_RELEASE = bin/Release/$(EXEC_FILE_NAME)
endif

VPATH := ui

SOURCE_PATHS := *.cpp
SOURCE_FILES := $(wildcard $(SOURCE_PATHS))
OBJ_FILES := $(patsubst %.cpp, %.o, $(notdir $(SOURCE_FILES)))

OBJ_DEBUG := $(addprefix $(OBJDIR_DEBUG)$(PATH_DELIM), $(OBJ_FILES))

OBJ_RELEASE := $(addprefix $(OBJDIR_RELEASE)$(PATH_DELIM), $(OBJ_FILES))

all: debug release

clean: clean_debug clean_release

before_debug:
ifeq ($(OS),Windows_NT)
	if not exist bin\\Debug\\*.* mkdir bin\\Debug
	if not exist $(OBJDIR_DEBUG)\\*.* mkdir $(OBJDIR_DEBUG)
else
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)
endif

after_debug:
ifeq ($(OS),Windows_NT)
else
endif

debug: print before_debug out_debug after_debug


print:
	@echo $(OBJ_DEBUG)

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)$(PATH_DELIM)%.o: %.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $^ -o $@

clean_debug:
ifeq ($(OS),Windows_NT)
	del /Q /F $(OBJ_DEBUG) $(OUT_DEBUG)
	rmdir /S /Q bin\\Debug
	rmdir /S /Q $(OBJDIR_DEBUG)
else
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)
endif

before_release:
ifeq ($(OS),Windows_NT)
	if not exist bin\\Release\\*.* mkdir bin\\Release
	if not exist $(OBJDIR_RELEASE)\\*.* mkdir $(OBJDIR_RELEASE)
else
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)
endif

after_release:
ifeq ($(OS),Windows_NT)
else
endif

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)$(PATH_DELIM)%.o: %.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $^ -o $@

clean_release:
ifeq ($(OS),Windows_NT)
	del /Q /F $(OBJDIR_RELEASE) $(OBJDIR_RELEASE)
	rmdir /S /Q bin\\Release
	rmdir /S /Q $(OBJDIR_RELEASE)
else
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)
endif

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release
