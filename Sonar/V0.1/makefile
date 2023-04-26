CC = arm-rpizw-g++
CFLAGS = -Wall -Wextra -pedantic -std=c++11
LDFLAGS = -L/usr/local/lib -I/usr/local/include -lwiringPi -lpthread -Wno-poison-system-directories

TARGET=sonar
 
all: $(TARGET)

$(TARGET): sonar.cpp
	$(CC) $(LDFLAGS) $< -o $@
 
clean:
	rm -f sonar.o sonar
