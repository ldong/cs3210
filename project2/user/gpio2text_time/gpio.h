#ifndef GPIO_H
#define	GPIO_H

#define GP_LED                 (3) // GPIO3 is GP LED
#define GP_5		       (17) //GPIO17 corresponds to Arduino PIN5
#define GP_6                   (24) //GPIO24 corresponds to Arduino PIN6
#define GP_7                   (27) //GPIO27 corresponds to Arduino PIN7
#define BLINK_TIME_SEC         (1) // 1 seconds blink time
#define GPIO_DIRECTION_IN      (1)
#define GPIO_DIRECTION_OUT     (0)
#define ERROR                  (-1)

int openGPIO(int gpio, int direction);
int writeGPIO(int fHandle, int val);
int readGPIO(int fileHandle);
int closeGPIO(int gpio, int fileHandle);

#endif	/* GPIO_H */

