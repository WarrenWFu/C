CC=g++
CFLAGS=
#为了使用原有的库必须使用优化前端头文件和库,库我拷贝到了myyb的lib下
#CPPFLAGS=-pg -g -Wall -I/mnt/winshared/myyb/library/libaps/include \
		 #-I/mnt/winshared/strtserver/library/libDbEntity.strt/inc
CPPFLAGS=-pg -g -Wall -I/mnt/winshared/myyb/library/libaps/include 
LDFLAGS=-L/mnt/winshared/myyb/product/Linux64/lib
LIBS=-laps.db -laps.base  -laps.db.oracle 
OBJECTS=upporacle.o
TAGS=upp

all:$(TAGS)
.PHONY:all

$(TAGS):$(OBJECTS)
	$(CC) -pg -o $@ $< $(LDFLAGS) $(LIBS)
$(OBJECTS):%.o:%.cpp

clean:
	@rm -f $(OBJECTS) $(TAGS)
.PHONY:clean

