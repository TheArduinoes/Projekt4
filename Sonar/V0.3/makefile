CXX = arm-rpizw-g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -I /wiringPi/wiringPi/
LDFLAGS = -L /home/stud/wiringPi/wiringPi/build/arm -x -pthread

LIBS = -lwirePiLib

TARGET=sonar

all: $(TARGET)

$(TARGET): sonar.cpp libSonar.cpp
	$(CXX) $(LDFLAGS) $< -o $@ $(LIBS)
 
clean:
	rm -f sonar.o libSonar.o sonar 
