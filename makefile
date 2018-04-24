SOURCE  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))

TARGET  := exe

CC      := g++
LIBS    :=
LDFLAGS :=
DEFINES :=
INCLUDE :=
CFLAGS  := -g3 $(DEFINES) $(INCLUDE) -std=c++11 -lpthread
CXXFLAGS:= $(CFLAGS)

#no need to change
.PHONY : everything objs clean veryclean rebuild

everything : $(TARGET)

all : $(TARGET)

objs : $(OBJS)

rebuild: veryclean everything

clean :
	rm -fr *.so
	rm -fr *.o

veryclean : clean
	rm -fr $(TARGET)
#compile command
$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LIBS) $(CXXFLAGS) 
