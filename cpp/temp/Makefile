TAGS=a.out

ifeq ($(TESTMACRO), 1)
	OBJECTS=t1.o
else
	OBJECTS=t2.o
endif

all:$(TAGS)
.PHONY:all clean

$(TAGS):$(OBJECTS)
	g++ -Wall -g -o a.out $(OBJECTS)

clean:
	@rm -f $(OBJECTS) $(TAGS)
