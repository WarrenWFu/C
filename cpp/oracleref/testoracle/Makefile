CC=g++
CFLAGS=
CPPFLAGS=-pg -g -Wall -I/u01/app/oracle/product/12.1.0/dbhome_1/rdbms/public/
LDFLAGS=-L/u01/app/oracle/product/12.1.0/dbhome_1/lib/
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

