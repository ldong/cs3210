#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "morse.h"
#include "gpio.h"

#define LETTER (1)
#define PAUSE (0)
#define TYPO_SYMBOL ('?')

typedef enum {DIT, DAH, LETTER_PAUSE, WORD_PAUSE, TYPO} signal_t;

int poll(void);
signal_t read_signal(int value, double duration);
char text_lookup(char* morse);
void signal_success(void);

int main(void) {
	char buffer[10];
	int buff_tail = 0;

	while(1) {
		int curr_status = poll();
		time_t start_time = time(NULL);
		volatile int dumb = 0;

		while(poll() == curr_status) {
			dumb++;
		}

		time_t end_time = time(NULL);

		signal_t signal = read_signal(curr_status, difftime(end_time, start_time));

		switch(signal) {
			case DIT:
				signal_success();
				buffer[buff_tail] = '.';
				buff_tail++;
				break;
			case DAH:
				signal_success();
				buffer[buff_tail] = '-';
				buff_tail++;
				break;
			case LETTER_PAUSE:
				buffer[buff_tail] = '\0';
				printf("%c", text_lookup(buffer));
				fflush(stdout);
				buff_tail = 0;
				break;
			case WORD_PAUSE:
				printf(" ");
				fflush(stdout);
				buff_tail = 0;
				break;
		}
	}
}

int poll(void) {
	int fileHandleGPIO_5 = openGPIO(GP_5, GPIO_DIRECTION_IN);
	int status = readGPIO(fileHandleGPIO_5);
	closeGPIO(GP_5, fileHandleGPIO_5);

	return status;
}

signal_t read_signal(int value, double duration) {
	if (LETTER == value) {
		if (duration <= 0.5) {
			return TYPO;
		} else if (duration <= 1.5) {
			return DIT;
		} else if (duration <= 3.5) {
			return DAH;
		} else {
			return TYPO;
		}
	} else {
		if (duration <= 1.5) {
			return TYPO;
		} else if (duration <= 5) {
			return LETTER_PAUSE;
		} else {
			return WORD_PAUSE;
		}
	}
}

char text_lookup(char* morse) {
	int i;

	for (i = 0; i < 26; i++) {
		if (strcmp(morse, morse_table[i]) == 0) {
			return alphabet_table[i];
		}
	}

	return TYPO_SYMBOL;
}

void signal_success(void) {
	int fileHandleGPIO_LED = openGPIO(GP_LED, GPIO_DIRECTION_OUT);
	writeGPIO(fileHandleGPIO_LED, 1);
	usleep(200);
	writeGPIO(fileHandleGPIO_LED, 0);
	closeGPIO(GP_LED, fileHandleGPIO_LED);
}
