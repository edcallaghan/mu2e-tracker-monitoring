# Ed Callaghan
# Starter build for RS485 monitoring server
# August 2025

EXE			:= monitoring-server
SRC			:= $(EXE).cpp
CPPFLAGS	:= -g -Og
CPPFLAGS 	:= $(CPPFLAGS) -I$(HOME)/sw/libgpiod/install/include
LDFLAGS		:= -L$(HOME)/sw/libgpiod/install/lib -lgpiodcxx
OBJS		:= RS485Bus.o

all: $(EXE)

$(EXE): $(SRC) $(OBJS)
	g++ -o $@ $(CPPFLAGS) $^ $(LDFLAGS)

.cpp.o:
	g++ -c $(CPPFLAGS) $<

clean:
	rm -f $(EXE) $(OBJS)

.PHONY: clean
