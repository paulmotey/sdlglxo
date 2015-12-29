LIBS =	-lGL

PROJECT		=	Ants2016
PROJECTM	=	sdlmain.c


HOBJECTS := $(wildcard Headers/Ants2016*.h)
COBJECTS := $(wildcard $(PROJECT)*.cpp)
OOBJECTS := $(patsubst %.cpp,%.o,$(wildcard $(PROJECT)*.cpp))
OBJS = $(COBJECTS:.cpp=.o)

CC		=	gcc -Wall -Werror -g

#Build is dependent on changes to makefile also
OBJECTS = 	$(OBJS)
DEPENDS	= 	$(HOBJECTS) makefile $(COBJECTS) Ants2016.cpp

.PHONY: all
all:  $(PROJECTM) 

$(PROJECTM): $(OBJECTS) $(DEPENDS)  
	$(CC) $(PROJECTM).c -o $(PROJECTM) $(OBJECTS) $(LIBS)

