
SYS := $(shell gcc -dumpmachine)
UNAME := $(shell uname)

ifneq (, $(findstring linux, $(SYS)))
    MACHINE=-DLINUX
	LIBS =	-lz -lGL -lSDL2 -lSDL2_image    # Do linux things
else
    MACHINE=-DWIN
#    LIBS = -lC:\Users\motey\Downloads\SDL2-devel-2.0.3-VC\SDL2-2.0.3\lib\x64\SDL2.lib -lSDL2 -lws2_32
	LIBS = 
	LIBSA = 
    LIBSB = -lSDL2main -lSDL2   -lSDL2_image  -lopengl32 -lws2_32
    INCL= -L\Users\motey\Downloads\SDL2-2.0.3\lib
    INC= -I\Users\motey\Downloads\SDL2-2.0.3\include
endif
CC=g++
CFLAGS = -g 


PROJECT		=	Ants20116
PROJECTM	=	sdlmain


HOBJECTS := $(wildcard Headers/Ants2016*.h)
#COBJECTS := $(wildcard $(PROJECT)*.cpp)
#OOBJECTS := $(patsubst %.cpp,%.o,$(wildcard $(PROJECT)*.cpp))
OBJS = 
#""$(COBJECTS:.cpp=.o)

CC		=	g++ -std=c++0x -Wall -Werror -g

#Build is dependent on changes to makefile also
OBJECTS = 	$(OBJS)
DEPENDS	= 	$(HOBJECTS) Makefile 

.PHONY: all
all:  $(PROJECTM) 

$(PROJECTM):  $(PROJECTM).cpp $(DEPENDS)
	@echo $(MACHINE)
	@echo $(INC)
	@echo $(SYS)
	 
	$(CC) $(MACHINE) $(INCLUDES) $(PROJECTM).cpp $(INC) $(INCL) -Wl,-Bstatic $(LIBSA) $(LIBSB) -o $(PROJECTM) $(OBJECTS) 

