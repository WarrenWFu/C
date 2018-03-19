CC=g++
CPPFLAGS=-pg -g -Wall
CPPFLAGS+=-I/mnt/winshared/ylink_optimize/library/libaps/include/
CPPFLAGS+=-I/mnt/winshared/strt/trunk/design_implementation/02-Server/library/libWSPublic/
LDFLAGS=-L/home/spring/projects/bobqf/product/Linux64/lib
LIBS=-laps.base -laps.iconv -lpthread -lwspublic -lssl -lcrypto
ENOBJECTS=en.o
DEOBJECTS=de.o
DSOBJECTS=ds.o
OBJECTS= $(ENOBJECTS) $(DEOBJECTS) $(DSOBJECTS)
ENTARGETS=en
DETARGETS=de
DSTARGETS=ds
TARGETS=$(ENTARGETS) $(DETARGETS) $(DSTARGETS)

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
$(DSTARGETS):$(DSOBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) -o $@ $^
	@rm -f $(DSOBJECTS)

$(OBJECTS):%.o:%.cpp

clean:
	@rm -f $(OBJECTS) $(TARGETS)
.PHONY:clean



