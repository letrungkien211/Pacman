CC = g++
RM = rm -f

CFLAGS = -Wall -g -O2

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGL -lGLU
endif

TARGET = main
OBJ = state.o common.o minimaxAgent.o utility.o alphabetaAgent.o
REPORT = AI_120291_15

all: $(TARGET)

$(TARGET): % : $(OBJ) %.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
.cpp.o:
	$(CC) $(CFLAGS) -c -o $@ $<
$(REPORT): %: %.tex
	pdflatex $<

clean:
	$(RM) *.o $(TARGET) *~ *#*
