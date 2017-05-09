CC=g++
CPPFLAGS=-pg -g -Wall
CPPFLAGS+=-I/mnt/winshared/ylink_optimize/library/libaps/include/
CPPFLAGS+=-I/mnt/winshared/qhjk/trunk/design_implementation/Server/library/libWSPublic/
LDFLAGS=-L/home/spring/project/qhjk/product/Linux64/lib
LIBS=-laps.base -laps.iconv -lpthread -lwspublic -lssl -lcrypto
ENOBJECTS=en.o
DEOBJECTS=de.o
OBJECTS= $(ENOBJECTS) $(DEOBJECTS)
ENTARGETS=en
DETARGETS=de
TARGETS=$(ENTARGETS) $(DETARGETS)

all:$(TARGETS)
.PHONY:all

#$(TARGETS):$(OBJECTS)
#	$(CC) $(LDFLAGS) $(LIBS) -o $@ $^
#	@rm -f $(OBJECTS)
$(ENTARGETS):$(ENOBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) -o $@ $^
	@rm -f $(ENOBJECTS)
$(DETARGETS):$(DEOBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) -o $@ $^
	@rm -f $(DEOBJECTS)

$(OBJECTS):%.o:%.cpp

clean:
	@rm -f $(OBJECTS) $(TARGETS)
.PHONY:clean



