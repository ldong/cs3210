#ifndef MORSE_MODULE_H
#define MORSE_MODULE_H


#include <linux/module.h>     /* module */
#include <linux/kernel.h>     /* kernel stuff */
#include <linux/proc_fs.h>    /* procfs stuff */
#include <linux/slab.h>       /* kmalloc() */
#include <asm/uaccess.h>      /* copy_from_user() */


#define PROCFS_NAME         "morse2txt"
#define MORSE_SYMBOL_MAX    5


static char charbuf[MORSE_SYMBOL_MAX];  /* For translate() */
static char c;                          /* Translated character */
static char *temp_kspace;               /* For dynamic resizing */


/* Structure holds information about /proc/ file */
static struct proc_dir_entry *morse_procfs;
static char *procfs_buffer;             /* module buffer */
static size_t procfs_size;              /* Size of the procfs buffer */
static ssize_t bytes_read;              /* bytes read/written */


#endif /* MORSE_MODULE_H */
