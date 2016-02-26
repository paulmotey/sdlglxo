MODULES = mainMenu.o graphics.o SDL_Sound.o
MODULESL = graphics.o
SYS := $(shell gcc -dumpmachine)
UNAME := $(shell uname)

ifneq (, $(findstring linux, $(SYS)))
    MACHINE=-DLINUX
	LIBS =	-lz -lGL -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf    # Do linux things
	LIBSB =
	WINC = 
else
    MACHINE=-DWIN
#    LIBS = -lC:\Users\motey\Downloads\SDL2-devel-2.0.3-VC\SDL2-2.0.3\lib\x64\SDL2.lib -lSDL2 -lws2_32
    WINC = -Wl,-Bstatic
    LIBS = 
    LIBSB = -lSDL2main -lSDL2 -lSDL2_mixer  -lSDL2_image  -lopengl32 -lws2_32
    INCL= -L\Users\motey\Downloads\SDL2-2.0.3\lib
    INC= -I\Users\motey\Downloads\SDL2-2.0.3\include
endif
CC=g++
CFLAGS = -g 


PROJECTM	=	sdlmain


HOBJECTS := $(wildcard headers/*.h)
#COBJECTS := $(wildcard $(PROJECT)*.cpp)
#OOBJECTS := $(patsubst %.cpp,%.o,$(wildcard $(PROJECT)*.cpp))
OBJS = 
#""$(COBJECTS:.cpp=.o)

CC		=	g++ -std=c++0x -Wall -Werror -g

#Build is dependent on changes to makefile also
OBJECTS = 	$(OBJS)
DEPENDS	= 	$(HOBJECTS) Makefile 

.PHONY: all
all:   mainMenu.o graphics.o SDL_Sound.o $(PROJECTM)

graphics.o: graphics.cpp 
	$(CC) -c  $(MACHINE) $<

SDL_Sound.o: SDL_Sound.cpp 
	$(CC) -c  $(MACHINE) $<
	
mainMenu.o: src/mainMenu.cpp
	$(CC) -c  $(MACHINE) $<
	
	
$(PROJECTM):  $(PROJECTM).cpp $(DEPENDS) $(MODULES) 
	@echo $(MACHINE)
	@echo $(INC)
	@echo $(SYS)
	 
	$(CC) $(MACHINE) $(INCLUDES) $(PROJECTM).cpp $(INC) $(MODULES) $(INCL) $(WINC) $(LIBS) $(LIBSB) -o $(PROJECTM) $(OBJECTS) 

