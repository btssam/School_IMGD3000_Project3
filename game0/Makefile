#
# Makefile for saucer shoot game using Dragonfly
#
# Copyright Mark Claypool and WPI, 2016-2025
#
# 'make' to build executable
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
#
# Variables of interest:
#   GAMESRC is the source code files for the game
#   GAME is the game main() source
#   EXECUTABLE is the name of the runnable game
#   ENG is the name of the Dragonfly engine
#

# Compiler.
CC= g++ 

# Libraries and includes.
LINKDIR= -L../dragonfly/lib # path to dragonfly library
INCDIR= -I../dragonfly/include # path to dragonfly includes
SFML_VERSION= 3.1.0

### Uncomment and update below if using local SFML installation.
# LOCALSFML= $(HOME)/src/SFML-$(SFML_VERSION)
# LINKDIR:= $(LINKDIR) -L $(LOCALSFML)/lib
# INCDIR:= $(INCDIR) -I$(LOCALSFML)/include

CFLAGS= -std=c++17

### Uncomment either 1) or 2) below! ###

## 1) For Linux:
ENG= dragonfly-x64-linux
CFLAGS:= $(CFLAGS) -Wall
LINKLIB= -l$(ENG) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt

## 2) For Mac:
#ENG= dragonfly-arm64-mac
#LINKLIB= -l$(ENG) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
#CFLAGS:= $(CFLAGS) -Wl,-rpath,$(HOME)/src/SFML/lib # runtime linking
#Note, if using homewbrew install (not local), uncomment:
#LOCALSFML= /opt/homebrew/Cellar/sfml/$(SFML_VERSION)
#LINKDIR:= $(LINKDIR) -L $(LOCALSFML)/lib

######

GAMESRC= \
	Saucer.cpp \
	Hero.cpp \
	Bullet.cpp \
	Reticle.cpp \
	Explosion.cpp \
	EventNuke.cpp \
	Points.cpp \
	Star.cpp \
	GameOver.cpp \
	GameStart.cpp \
	EventSlow.cpp

GAME= game.cpp
EXECUTABLE= game
OBJECTS= $(GAMESRC:.cpp=.o)

.PHONY: all clean

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(OBJECTS) $(GAME) $(GAMESRC) 
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB) 

.cpp.o: 
	$(CC) $(CFLAGS) -c $< -o $@ $(INCDIR)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~
# DO NOT DELETE
