LIBS =	-lopengl32  -lSDL2main -lSDL2

PROJECT		=	Ants2016z
PROJECTM	=	Ants2016


HOBJECTS := $(wildcard Headers/Ants2016*.h)
COBJECTS := $(wildcard $(PROJECT)*.cpp)
OOBJECTS := $(patsubst %.cpp,%.o,$(wildcard $(PROJECT)*.cpp))
OBJS = $(COBJECTS:.cpp=.o)

CC		=	g++ -Wall -Werror -g

#Build is dependent on changes to makefile also
OBJECTS = 	$(OBJS)
DEPENDS	= 	$(HOBJECTS) makefile $(COBJECTS) Ants2016.cpp

.PHONY: all
all:  $(PROJECTM) 

$(PROJECTM): $(OBJECTS) $(DEPENDS)  
	$(CC) $(PROJECTM).c -o $(PROJECTM) $(OBJECTS) $(LIBS)

