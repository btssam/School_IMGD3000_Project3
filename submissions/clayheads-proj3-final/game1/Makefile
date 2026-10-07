#
# Makefile for game1 using Dragonfly
# Supports both Linux and macOS (Apple Silicon) automatically via uname -s
#

CC= g++
CFLAGS= -std=c++17

# ==============================================================================
# GAME FILES - ADD YOUR NEW .cpp FILES HERE:
# ==============================================================================

# Main game file (contains main()):
GAME= game1.cpp

# List all additional .cpp files here (e.g. Player.cpp \ Dungeon.cpp):
GAMESRC= \
    Hero.cpp\
    UI.cpp\
    Room.cpp\
    Map.cpp \
    GameOver.cpp \
    Enemy.cpp \
    Reticle.cpp \
    Fountain.cpp \
    Clue.cpp \
    ColorClue.cpp \
    Keypad.cpp \
    KeypadButton.cpp \
    GameVictory.cpp \
    GameStart.cpp \

# ==============================================================================
# ENGINE & COMPILER CONFIGURATION (Auto-detects Linux vs macOS)
# ==============================================================================

INCDIR= -I../dragonfly/include
LINKDIR= -L../dragonfly/lib

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

EXECUTABLE= game1
OBJECTS= $(GAMESRC:.cpp=.o)

# ==============================================================================
# BUILD TARGETS
# ==============================================================================

.PHONY: all clean

all: $(EXECUTABLE)

# Linking the final executable
$(EXECUTABLE): $(OBJECTS) $(GAME)
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB)

# Compiling individual .cpp files into .o object files
.cpp.o: 
	$(CC) $(CFLAGS) -c $< -o $@ $(INCDIR)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~