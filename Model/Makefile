CC = g++
RM = rm -f

CFLAGS = -Wall -g -O2
LIBS = -lm -lglut -lGLU -lGL

TARGET = model
OBJ = state.o cell.o common.o minimaxAgent.o utility.o

all: $(TARGET)

$(TARGET): % : $(OBJ) %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
.cpp.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.o $(TARGET) *~ *#*
