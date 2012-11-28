CC = g++
RM = rm -f

CFLAGS = -Wall -g -O2
INCLUDES = -I/home/letrungkien7/Dropbox/git/8puzzle
LIBS = -lm -lglut -lGL -lGLU

TARGET = main
OBJ = state.o common.o minimaxAgent.o utility.o

all: $(TARGET)

$(TARGET): % : $(OBJ) %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
clean:
	$(RM) *.o $(TARGET) *~ *#*
