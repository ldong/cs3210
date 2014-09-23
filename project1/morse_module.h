#ifndef MORSE_MODULE_H
#define MORSE_MODULE_H


#include <linux/module.h>     /* module */
#include <linux/kernel.h>     /* kernel stuff */
#include <linux/proc_fs.h>    /* procfs stuff */
#include <linux/slab.h>       /* kmalloc() */
#include <asm/uaccess.h>      /* copy_from_user() */


#define PROCFS_NAME         "morse2txt"
#define MORSE_SYMBOL_MAX    5


/* Structure holds information about /proc/ file */
static struct proc_dir_entry *morse_procfs;
static char *procfs_buffer;             /* module buffer */
static size_t procfs_size;              /* Size of the procfs buffer */
static ssize_t bytes_read;              /* bytes read/written */
static char charbuf[MORSE_SYMBOL_MAX];  /* For translate() */
static char c;                          /* Translated character */
/* static char *temp_kspace;               /1* For dynamic resizing *1/ */


#define MORSE_SIZE          64

int resize_buffer(void);
char translate(char *arr);
char lookup(int index);

const char morse[MORSE_SIZE] =
{ /* index from 1 */
  '?'
  ,'?'
  ,'E' ,'T'
  ,'I' ,'A' ,'N' ,'M'
  ,'S' ,'U' ,'R' ,'W' ,'D' ,'K' , 'G', 'O'
  ,'H' ,'V' ,'F' ,'?' ,'L' ,'?' , 'P', 'J'
  ,'B' ,'X' ,'C' ,'Y' ,'Z' ,'Q' , '?', '?'
  ,'5' ,'4' ,'?' ,'3'
  ,'?' ,'?' ,'?' ,'2'
  ,'?' ,'?' ,'?' ,'?'
  ,'?' ,'?' ,'?' ,'1'
  ,'6' ,'?' ,'?' ,'?'
  ,'?' ,'?' ,'?' ,'?'
  ,'7' ,'?' ,'?' ,'?'
  ,'8' ,'?' ,'9' ,'0'
};


#endif /* MORSE_MODULE_H */

