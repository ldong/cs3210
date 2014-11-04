#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/vmalloc.h>
#include "morse.h"

#define GP_LED (3) // GPIO3 is GP LED
#define GP_5 (17) //GPIO17 corresponds to Arduino PIN5
#define LETTER (1)
#define PAUSE (0)
#define TYPO_SYMBOL ('?')
#define BUFFER_SIZE (1024)

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("gpio2text");
MODULE_AUTHOR("Xinyi Chen, Lin Dong");

typedef enum {DIT, DAH, LETTER_PAUSE, WORD_PAUSE, TYPO, FINISH} signal_t;

signal_t read_signal(int value, int duration_sec);
char text_lookup(char* morse);
void signal_success(void);
int read_proc(struct file *filp, char *buf, size_t count, loff_t *offp);
void receive(void);

char text_buffer[BUFFER_SIZE];
int text_count;

struct file_operations proc_fops = {
    read:  read_proc
};


int read_proc(struct file *filp, char *buf, size_t count, loff_t *offp) {     
    static int finished = 0;

    if (finished) {
        finished = 0;
        return 0;
    }

    copy_to_user(buf, text_buffer, text_count);

    finished = 1;

    return count;
}

void receive(void) {
    signal_t signal;
    char morse_buffer[10];
    int morse_count = 0;
    text_count = 0;
    volatile int dumb = 0;
    struct timeval *start_time = (struct timeval *)vmalloc(sizeof(struct timeval));
    struct timeval *end_time = (struct timeval *)vmalloc(sizeof(struct timeval));

    while (gpio_get_value_cansleep(GP_5) == 0) { // wait for the first button push
        dumb++;
    }


    do {
        dumb = 0;
        int curr_status = gpio_get_value_cansleep(GP_5);

        do_gettimeofday(start_time);

        while(gpio_get_value_cansleep(GP_5) == curr_status) {
            dumb++;
        }

        do_gettimeofday(end_time);

        signal = read_signal(curr_status, (end_time->tv_sec) - (start_time->tv_sec));

        switch(signal) {
            case DIT:
                signal_success();
                morse_buffer[morse_count] = '.';
                morse_count++;
                break;
            case DAH:
                signal_success();
                morse_buffer[morse_count] = '-';
                morse_count++;
                break;
            case LETTER_PAUSE:
                morse_buffer[morse_count] = '\0';
                char next_letter = text_lookup(morse_buffer);               
                
                printk(KERN_INFO "%c\n", next_letter);

                text_buffer[text_count] = next_letter;
                text_count++;
                morse_count = 0;
                break;
            case WORD_PAUSE:
                printk(KERN_INFO " \n");

                text_buffer[text_count] = ' ';
                text_count++;
                morse_count = 0;
                break;
            default:
                break;
        }

        if (text_count >= BUFFER_SIZE) {
            signal = FINISH;
            printk(KERN_INFO "Message too long. Dropping...\n");
        }
    } while (signal != FINISH);

    printk(KERN_INFO "End receiving\n");

    vfree(start_time);
    vfree(end_time);
}

signal_t read_signal(int value, int duration_sec) {
    int duration = duration_sec * 10; // adjusted to avoid double comparison

    if (LETTER == value) {
        if (duration <= 5) {
            return TYPO;
        } else if (duration <= 15) {
            return DIT;
        } else if (duration <= 35) {
            return DAH;
        } else {
            return TYPO;
        }
    } else {
        if (duration <= 15) {
            return TYPO;
        } else if (duration <= 50) {
            return LETTER_PAUSE;
        } else if (duration <= 100) {
            return WORD_PAUSE;
        } else {
            return FINISH;
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
    gpio_set_value_cansleep(GP_LED, 1);
    udelay(200);
    gpio_set_value_cansleep(GP_LED, 0);
}

int init_morse_module(void){
    if (gpio_request_one(GP_5 , GPIOF_DIR_IN, "GP_5")) {
    	printk(KERN_INFO "Failed to get GP 5\n");
    	return -1;
    }

    gpio_set_debounce(GP_5, 500000);

    if (gpio_request_one(GP_LED, GPIOF_DIR_OUT, "GP_LED")) {
        printk(KERN_INFO "Failed to get GP LED\n");
        return -1;
    }

    printk(KERN_INFO "Ready to receive\n");

    receive();

    text_buffer[text_count] = '\0';

    proc_create("text_out", 0, NULL, &proc_fops);

    return 0;
}

void cleanup_morse_module(void){
    printk(KERN_INFO "Shutting down\n");

    remove_proc_entry("text_out", NULL);

    gpio_free(GP_5);
    gpio_free(GP_LED);
}

module_init(init_morse_module);
module_exit(cleanup_morse_module);
