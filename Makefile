OUT=InfectYourCanardLaque
CC=g++
SDL=-lSDLmain -lSDL -lSDL_image -lSDL_ttf

OBJECTS = main.o

all: $(OUT)

InfectYourCanardLaque: main.o canard.o LTimer.o FoodStuff.o  LMouse.o FileManager.o
	$(CC) -o $@ $^ $(SDL)

main.o: 

canard.o: 

LTimer.o: 

FoodStuff.o:  

LMouse.o: 

FileManager.o: Model.o FileManager.cpp FileManager.h
	$(CC) -o $@ $^

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(OUT)