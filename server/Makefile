# Ed Callaghan
# Starter build for RS485 monitoring server
# August 2025

EXE				:= monitoring-server
SRC				:= $(EXE).cpp
CPPFLAGS	:= -g -Og
CFLAGS		:=
LDFLAGS		:= -lgpiodcxx -lmu2e-tracker-messaging
OBJS			:= DigitalConversionMap.o Foyer.o Handler.o HardwareLoop.o InitializeServer.o RS485Bus.o StandardQueries.o Task.o

all: $(EXE)

$(EXE): $(SRC) $(OBJS)
	g++ -o $@ $(CPPFLAGS) $^ $(LDFLAGS)

.cpp.o:
	g++ -c $(CPPFLAGS) $<

.c.o:
	gcc -c $(CFLAGS) $<

clean:
	rm -f $(EXE) $(OBJS)

.PHONY: clean
