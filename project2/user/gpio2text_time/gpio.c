#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "gpio.h"

int openGPIO(int gpio, int direction) {
    char buffer[256];
    int fileHandle;
    int fileMode;

    //Export GPIO
    fileHandle = open("/sys/class/gpio/export", O_WRONLY);   
    if (ERROR == fileHandle) {
        puts("Error: Unable to opening /sys/class/gpio/export");
        return (-1);
    }
    sprintf(buffer, "%d", gpio);
    write(fileHandle, buffer, strlen(buffer));
    close(fileHandle);

    //Direction GPIO
    sprintf(buffer, "/sys/class/gpio/gpio%d/direction", gpio);
    fileHandle = open(buffer, O_WRONLY);
    if (ERROR == fileHandle) {
        puts("Unable to open file:");
        puts(buffer);
        return (-1);
    }

    if (direction == GPIO_DIRECTION_OUT) {
        // Set out direction
        write(fileHandle, "out", 3);
        fileMode = O_WRONLY;
    } else {
        // Set in direction
        write(fileHandle, "in", 2);
        fileMode = O_RDONLY;
    }
    close(fileHandle);

    //Open GPIO for Read / Write
    sprintf(buffer, "/sys/class/gpio/gpio%d/value", gpio);
    fileHandle = open(buffer, fileMode);
    if (ERROR == fileHandle) {
        puts("Unable to open file:");
        puts(buffer);
        return (-1);
    }

    return (fileHandle); //This file handle will be used in read/write and close operations.
}

int writeGPIO(int fHandle, int val) {
    if (val == 0) {
        // Set GPIO low status
        write(fHandle, "0", 1);
    } else {
        // Set GPIO high status
        write(fHandle, "1", 1);
    }

    return (0);
}

int readGPIO(int fileHandle) {
    int value;

    read(fileHandle, &value, 1);

    if ('0' == value) {
        // Current GPIO status low
        value = 0;
    } else {
        // Current GPIO status high
        value = 1;
    }

    return value;
}

int closeGPIO(int gpio, int fileHandle) {
    char buffer[256];

    close(fileHandle); //This is the file handle of opened GPIO for Read / Write earlier.

    fileHandle = open("/sys/class/gpio/unexport", O_WRONLY);
    if (ERROR == fileHandle) {
        puts("Unable to open file:");
        puts(buffer);
        return (-1);
    }
    sprintf(buffer, "%d", gpio);
    write(fileHandle, buffer, strlen(buffer));
    close(fileHandle);

    return (0);
}