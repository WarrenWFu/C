CC=g++
CPPFLAGS=-pg -g -Wall
CPPFLAGS+=-I/mnt/winshared/ylink_optimize/library/libaps/include/
#LDFLAGS=-L/home/spring/project/qhjk/product/Linux64/lib
LDFLAGS=-L/home/spring/project/qhjk/product/Linux64/lib
LIBS=-laps.base -laps.iconv -lpthread
OBJECTS=simulator.o
TARGETS=simulator

all:$(TARGETS)
.PHONY:all

$(TARGETS):$(OBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) -o $@ $^

$(OBJECTS):%.o:%.cpp

clean:
	@rm -f $(OBJECTS) $(TARGETS)
.PHONY:clean



