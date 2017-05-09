include /mnt/winshared/strtserver/Makefile.conf
CXXFLAGS=-Wall -g 
CXXFLAGS+= -I/mnt/winshared/strtserver/library/libaps/include                                 
#CXXFLAGS+= -I/mnt/winshared/strtserver/library/libaps/packages/libMsgCodec.XML/inc            
#CXXFLAGS+= -I/mnt/winshared/strtserver/library/libUppResourceMgr/inc                          
#CXXFLAGS+= -I/mnt/winshared/strtserver/library/libDbEntity.strt/inc                           
#CXXFLAGS+= -I/mnt/winshared/strtserver/library/libDbEntity.upp/inc                            
THIS_LINK+= -L/mnt/winshared/strtserver/product/Linux64/lib -laps.base -laps.db -laps.db.oracle -lpthread
OBJECTS=t2.o

all:a.out
.PHONY:all

a.out:$(OBJECTS)
	$(CC) $(THIS_LINK) $< -o $@

$(OBJECTS):%.o:%.cpp
