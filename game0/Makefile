CC= g++
CFLAGS= -std=c++17

# Engine paths
INCDIR= -I../dragonfly/include
LINKDIR= -L../dragonfly/lib

# Detect Operating System
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
  # === macOS (Apple Silicon Homebrew) ===
  ENG= dragonfly-arm64-mac
  INCDIR:= $(INCDIR) -I/opt/homebrew/include
  LINKDIR:= $(LINKDIR) -L/opt/homebrew/lib
  CFLAGS:= $(CFLAGS) -Wl,-rpath,/opt/homebrew/lib
  LINKLIB= -l$(ENG) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else
  # === Linux ===
  ENG= dragonfly-x64-linux
  CFLAGS:= $(CFLAGS) -Wall
  LINKLIB= -l$(ENG) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt
endif

# Files to compile
GAMESRC= # list of .cpp files
GAME= game.cpp
EXECUTABLE= game
OBJECTS= $(GAMESRC:.cpp=.o)

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(GAME)
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(INCDIR)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~