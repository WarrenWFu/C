CC = g++
#CPPFLAGS = -Wall -I/mnt/winshared/it/cpp/msm/src/include -g
CXXFLAGS = -Wall -I/mnt/winshared/it/cpp/msm/src/include -g
OBJECTS = main.o students.o student.o studentoperation.o
#OBJECTS := $(wildcard *.o)
#Makefile的特殊变量用于查找源文件,多个用:隔开,但是注意如果用到了$(CC)语句,还是要知道include
VPATH = ../src/visual:../src/model:../src/control:../src/include
# 也可以使用vpath方式来指定源文件
#vpath %.h ../src/include
TAGS = msm

all:$(TAGS)
.PHONY:all clean

$(TAGS):$(OBJECTS)
	$(CC) -Wall -g -o msm $(OBJECTS)

$(OBJECTS):%.o:%.cpp

clean:
	@rm -f $(OBJECTS) $(TAGS)

