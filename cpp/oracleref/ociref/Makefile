CC=gcc
#CFLAGS=-pg -g -Wall -I/u01/app/oracle/product/12.1.0/dbhome_1/rdbms/public
CFLAGS=-pg -g -Wall -I/mnt/winshared/myyb/product/Linux64/opt/oracle.oci.Linux64/include
CPPFLAGS=
LDFLAGS=-L/mnt/winshared/myyb/product/Linux64/opt/oracle.oci.Linux64/lib
LIBS=-lclntsh
OBJECTS=oci.o oci2.o
TAGS=oci oci2

all:$(TAGS)
.PHONY:all

$(TAGS):$(OBJECTS)
	$(CC) -pg -o oci oci.o   $(LDFLAGS) $(LIBS)
	$(CC) -pg -o oci2 oci2.o $(LDFLAGS) $(LIBS)
$(OBJECTS):%.o:%.c

clean:
	@rm -f $(OBJECTS) $(TAGS)
.PHONY:clean
