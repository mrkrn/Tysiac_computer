CC = g++
CFLAGS = -Wall
OBJECTS = tysiac.o averagescore.o experiments.o

all: tysiac averagescore experiments

tysiac: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ tysiac.o

averagescore: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ averagescore.o

experiments: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ experiments.o
	
tysiac.o: tysiac.cc
	g++ $(CFLAGS) -c tysiac.cc

averagescore.o: averagescore.cc
	g++ $(CFLAGS) -c averagescore.cc

experiments.o: experiments.cc
	g++ $(CFLAGS) -c experiments.cc
		
clean:
	-rm *.o tysiac averagescore experiments *.txt