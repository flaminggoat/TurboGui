#OBJS specifies which files to compile as part of the project
OBJS = Test.c TG.c TG_Button.c

#CC specifies which compiler we're using
CC = gcc

#INCLUDE_PATHS specifies the additional include paths we'll need
#INCLUDE_PATHS = -I/usr/local/include/SDL2
INCLUDE_PATHS = -I/usr/include/SDL2/

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = 

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -std=c99 -g

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2main -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = gui

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
