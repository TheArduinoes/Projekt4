#include <stdio.h>
#include <wiringPi.h>

#define PWM_PIN 1  // Use wiringPi pin 1 (GPIO 18) for PWM output
#define HIGH_PINA 0 //Use wiringPi pin 0 (GPIO 17) for high or low signal
#define HIGH_PINB 2 // Use wiringPi pin 2 (GPIO 27) for high or low signal
#define HIGH_PINC 3 // Use wiringPi pin 3 (GPIO  22) for high or low signal
#define HIGH_PIND 4 // Use wiringPi pin 4 (GPIO 23) for high or low signal
#define RANGE   100 // PWM range
#define DUTY_CYCLE 50 // Duty cycle in percentage

int main(void)
{
    if (wiringPiSetup() == -1) {
        printf("Failed to setup wiringPi!\n");
        return 1;
    }

    pinMode(PWM_PIN, PWM_OUTPUT); // Set the pin as PWM output
    pinMode(HIGH_PINA, OUTPUT);
    pinMode(HIGH_PINB, OUTPUT);
    pinMode(HIGH_PINC, OUTPUT);
    pinMode(HIGH_PIND, OUTPUT);

    pwmSetMode(PWM_MODE_MS);      // Set the PWM mode to Mark-Space mode
    pwmSetRange(RANGE);           // Set the PWM range to 100
    pwmSetClock(384);             // Set the PWM clock to 50 kHz

    int duty = (DUTY_CYCLE * RANGE) / 100; // Calculate the duty cycle value
    pwmWrite(PWM_PIN, duty);      // Set the duty cycle

    while (1) {
        int input, pwm;
        printf(" Enter 0: forward \n Enter 1: backward \n Enter 2: ClockWise \n Enter 3: Anti CloclWise \n Enter 4: STOP U DUMB FUCK! \n Enter 5: Change PWM \n");
        scanf("%d \n", &input);

        switch (input) {
            case 0: //forward
                digitalWrite(HIGH_PINA, HIGH);
                digitalWrite(HIGH_PINB, LOW);
                digitalWrite(HIGH_PINC, HIGH);
                digitalWrite(HIGH_PIND, LOW);
                break;
            case 1: //backward
                digitalWrite(HIGH_PINA, LOW);
                digitalWrite(HIGH_PINB, HIGH);
                digitalWrite(HIGH_PINC, LOW);
                digitalWrite(HIGH_PIND, HIGH);
                break;
            case 2: //clockwise
                digitalWrite(HIGH_PINA, HIGH);
                digitalWrite(HIGH_PINB, LOW);
                digitalWrite(HIGH_PINC, LOW);
                digitalWrite(HIGH_PIND, HIGH);
                break;
            case 3: //anti-clockwise
                digitalWrite(HIGH_PINA, LOW);
                digitalWrite(HIGH_PINB, HIGH);
                digitalWrite(HIGH_PINC, HIGH);
                digitalWrite(HIGH_PIND, LOW);
                break;
           case 4: //STOP mOterhfucker
                digitalWrite(HIGH_PINA, LOW);
                digitalWrite(HIGH_PINB, LOW);
                digitalWrite(HIGH_PINC, LOW);
                digitalWrite(HIGH_PIND, LOW);
                break;
          case 5: //stop the pwm
                duty = (0 * RANGE) / 100; // Calculate the duty cycle value
                pwmWrite(PWM_PIN, duty); // Set the duty cycle
                break;
          case 6: //set pwm too 30%
                duty = (30 * RANGE) / 100; // Calculate the duty cycle value
                pwmWrite(PWM_PIN, duty); // Set the duty cycle
                break;
          case 7: // set pwm too 100%
                 duty = (100 * RANGE) / 100; // Calculate the duty cycle value
                 pwmWrite(PWM_PIN, duty); // Set the duty cycle
                 break;
          default:
                printf("Invalid input\n");
                break;
        }
    }

    return 0;
}
