CC = g++
RM = rm -f

CFLAGS = -Wall -g -O2
LIBS = -lm -lglut -lGLU -lGL

TARGET = main
OBJ = view.o

all: $(TARGET)

$(TARGET): % : $(OBJ) %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
.cpp.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.o $(TARGET) *~ *#*
