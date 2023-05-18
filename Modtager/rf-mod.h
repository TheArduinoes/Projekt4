#include <iostream>
#include "wiringPi.h"
#include "wiringSerial.h"
#include <string>

class SerialReceiver {
public:
    SerialReceiver() {
        if ((serialPort = serialOpen("/dev/ttyS0", 9600)) < 0) {
            std::cout << "Kunne ikke åbne serielporten. Afslutter programmet." << std::endl;
            return;
        }
    }

    ~SerialReceiver() {
        serialClose(serialPort);
    }

    std::string receiveData() {
        std::string receivedData;

        while (true) {
            if (serialDataAvail(serialPort)) {
                char c = serialGetchar(serialPort);

                if (c != '\n' && c != '\r') {
                    receivedData += c;
                } else if (!receivedData.empty()) {
                    processData(receivedData);
                }
            }
        }
        return receivedData;
    }
    void processData(const std::string& data) {
        std::cout << "Modtaget data: " << data << std::endl;
    }

private:
    int serialPort;

    
};

