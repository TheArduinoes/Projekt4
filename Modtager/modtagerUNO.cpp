#include <iostream>
#include "wiringPi.h"

#define BUFFER_SIZE 8  // Antal bits i hver byte/gruppe
#define THRESHOLD 500  // Tærskelværdi for amplitudedetektering

// Funktionerklæringer
void shiftBuffer(int buffer[], int bit);
int isBufferFull(int buffer[]);
int convertBufferToByte(int buffer[]);
void resetBuffer(int buffer[]);

int main() {

    std::cout << "Starter" << std::endl;
    
    // Initialiser modtager og GPIO-forbindelse
    wiringPiSetup();  // Initialiserer WiringPi-biblioteket
    pinMode(0, INPUT);

    // Opret en buffer til at gemme de modtagne bits
    int buffer[BUFFER_SIZE];
    
    // Modtag og behandle binære data
    while (1) {
        // Demoduler signalet ved at sammenligne med tærskelværdien
        int bit = digitalRead(0) > THRESHOLD ? 1 : 0;
        
        // Gem bit i bufferet
        shiftBuffer(buffer, bit);
        
        // Check om bufferen er fyldt med BITSIZE bits
        if (isBufferFull(buffer)) {
            // Konverter bufferen til en byte
            int byte = convertBufferToByte(buffer);
            
            // Konverter byte til tegn ved hjælp af ASCII-kodning
            char character = static_cast<char>(byte);
            
            // Udskriv tegnet
            std::cout << character;
            
            // Nulstil bufferen for næste gruppe af bits
            resetBuffer(buffer);
        }
    }
    
    return 0;
}

// Funktion til at skubbe et nyt bit ind i bufferet
void shiftBuffer(int buffer[], int bit) {
    for (int i = BUFFER_SIZE - 1; i > 0; i--) {
        buffer[i] = buffer[i - 1];
    }
    buffer[0] = bit;
}

// Funktion til at kontrollere om bufferen er fyldt med BITSIZE bits
int isBufferFull(int buffer[]) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (buffer[i] == -1) {
            return 0;
        }
    }
    return 1;
}

// Funktion til at konvertere bufferen til en byte
int convertBufferToByte(int buffer[]) {
    int byte = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        byte = (byte << 1) | buffer[i];
    }
    return byte;
}

// Funktion til at nulstille bufferen
void resetBuffer(int buffer[]) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }
}
