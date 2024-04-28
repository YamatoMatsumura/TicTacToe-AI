# THE NAME OF YOUR EXECUTABLE
TARGET = tictactoe.exe
# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = main.cpp board.cpp minimax.cpp display.cpp xShape.cpp oShape.cpp storage.cpp

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors -g
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
	Q =

	INC_PATH = /usr/local/include/
	LIB_PATH = /usr/local/lib/

	ARCH = 
else
	DEL = rm -f
	Q = "

	INC_PATH = /usr/local/include/
	LIB_PATH = /usr/local/lib/

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		TARGET_MAKEFILE = Makefile.osx
		CXXFLAGS += -D OSX
	endif

	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARCH = 
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		ARCH = 
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		ARCH = 
	endif
endif

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(ARCH) -o $@ $^ -L$(LIB_PATH) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(ARCH) -o $@ -c $< -I$(INC_PATH)

clean:
	$(DEL) $(TARGET) $(OBJECTS)
	
depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

# DEPENDENCIES
main.o: main.cpp board.h minimax.h display.h xShape.h oShape.h storage.h
board.o: board.cpp board.h
minimax.o: minimax.cpp minimax.h board.h
display.o: display.cpp display.h xShape.h oShape.h board.h
xShape.o: xShape.cpp xShape.h
oShape.o: oShape.cpp oShape.h
storage.o: storage.cpp storage.h
