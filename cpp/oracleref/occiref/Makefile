CC=g++
CFLAGS=
CPPFLAGS=-pg -g -Wall -I/mnt/winshared/myyb/product/Linux64/opt/oracle.oci.Linux64/include
LDFLAGS=-L/mnt/winshared/myyb/product/Linux64/opt/oracle.oci.Linux64/lib
LIBS=-lclntsh -locci
OBJECTS=occi.o
TAGS=occi

all:$(TAGS)
.PHONY:all

$(TAGS):$(OBJECTS)
	$(CC) -pg -o $@ $< $(LDFLAGS) $(LIBS)
$(OBJECTS):%.o:%.cpp

clean:
	@rm -f $(OBJECTS) $(TAGS)
.PHONY:clean

