
CC = arm-rpizw-g++
CFLAGS = -Wall -Wextra -pedantic -std=c++11
LDFLAGS = -L/home/stud/Desktop/Projekt/wiringPi/wiringPi/build/arm -lwirePiLib -pthread
INCLUDES = -I/home/stud/desktop/wiringPi/wiringPi
SOURCES = sonarTest.cpp libSonar.cpp sonar.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(OBJECTS) -o $(EXECUTABLE)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)