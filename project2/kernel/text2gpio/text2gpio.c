#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/string.h>
#include "morse.h"

#define DIT (1000) // in ms
#define DAH ((3)*(DIT)) // in ms
#define LETTER_PAUSE ((3)*(DIT)) //in ms
#define WORD_PAUSE ((7)*(DIT)) //in ms
#define WORD_DELIM (' ')
#define GP_LED (3) // GPIO3 is GP LED
#define BUFFER_SIZE (1024)

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Text2Morse");
MODULE_AUTHOR("Xinyi Chen, Lin Dong");

int text2gpio(const char *text, size_t count);
int write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp);

char text_buffer[BUFFER_SIZE];
int text_count;

struct file_operations proc_fops = {
    write:  write_proc
};

int write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp) {
    text_count = count;
    
    if (text_count > BUFFER_SIZE) {
         printk(KERN_INFO "Text length too long. Only %d bytes copied\n", BUFFER_SIZE);
         
         text_count = BUFFER_SIZE;       
    }

    if (copy_from_user(text_buffer, buf, text_count)) {
        printk(KERN_INFO "copy from user failed.\n");

        return -ENOSPC;
    }

    text2gpio(text_buffer, text_count - 1);

    return count;
}

int text2gpio(const char *text, size_t count) {
    int i;

    printk(KERN_INFO "Starting sending morse.\n");

    for (i = 0; i < count; i++) {
        char curr_letter = text[i];

        if (curr_letter == ' ') {
            gpio_set_value_cansleep(GP_LED, 0);
            mdelay(WORD_PAUSE);
        } else {
            char *curr_morse = MORSE(curr_letter);

            while (*curr_morse) {
                gpio_set_value_cansleep(GP_LED, 1);

                if (*curr_morse == '.') {
                    mdelay(DIT);
                } else {
                    mdelay(DAH);
                }

                gpio_set_value_cansleep(GP_LED, 0);
                mdelay(DIT);
                curr_morse++;
            }
        }

        gpio_set_value_cansleep(GP_LED, 0);
        mdelay(LETTER_PAUSE);
    }

    printk(KERN_INFO "Finished\n");

    return 0;
}

int init_morse_module(void) {
    if (gpio_request_one(GP_LED, GPIOF_DIR_OUT, "GP_LED")) {
        printk(KERN_INFO "Failed to get on-board LED\n");
        return -1;
    }

    proc_create("text_in", 0, NULL, &proc_fops);

    return 0;
}

void cleanup_morse_module(void) {
    remove_proc_entry("text_in", NULL);
    gpio_free(GP_LED);
}

module_init(init_morse_module);
module_exit(cleanup_morse_module);