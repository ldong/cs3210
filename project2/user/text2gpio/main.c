#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "gpio.h"
#include "morse.h"

#define DIT (1) // in seconds
#define DAH ((3)*(DIT)) // in seconds
#define LETTER_PAUSE ((3)*(DIT)) //in seconds
#define WORD_PAUSE ((7)*(DIT)) //in seconds
#define WORD_DELIM (' ')

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("must supply a text string for translation\n");

        return 0;
    } 

    int i;
    int fileHandleGPIO_LED;
    char *test_str = argv[1];

    puts("Starting sending morse.");

    fileHandleGPIO_LED = openGPIO(GP_LED, GPIO_DIRECTION_OUT);

    if (ERROR == fileHandleGPIO_LED) {
        return (-1);
    }

    for (i = 0; i < strlen(test_str); i++) {
        char curr_letter = test_str[i];

        if (curr_letter == ' ') {
            writeGPIO(fileHandleGPIO_LED, 0);
            sleep(WORD_PAUSE);
        } else {
            char *curr_morse = MORSE(curr_letter);

            while (*curr_morse) {
                writeGPIO(fileHandleGPIO_LED, 1);

                if (*curr_morse == '.') {
                    sleep(DIT);
                } else {
                    sleep(DAH);
                }

                writeGPIO(fileHandleGPIO_LED, 0);
                sleep(1);
                curr_morse++;
            }
        }

        writeGPIO(fileHandleGPIO_LED, 0);
        sleep(LETTER_PAUSE);
    }

    closeGPIO(GP_LED, fileHandleGPIO_LED);

    puts("Finished");

    return 0;
}
