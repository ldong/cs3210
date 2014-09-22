/**
 * morse.c - morse code translator using read/write to procfs file
 *
 * CS 3210, Georgia Tech, Fall 2014
 *
 * Team 2: Daniel T. Lee
 *         HyunJong (Joseph) Lee
 *         Lin Dong
 *
 * Usage:
 *  Variable, make, load module and redirection commands
 *  in runtest.sh
 *
 *  `chmod +x runtest.sh`
 *  `./runtest.sh`
 *
 */


#include <linux/module.h>       /* module */
#include <linux/kernel.h>       /* kernel stuff */
#include <linux/proc_fs.h>      /* using proc fs */
#include <linux/slab.h>         /* kmalloc() */
#include <asm/uaccess.h>        /* copy_from_user() */


#define PROCFS_NAME         "morse"
#define MORSE_SIZE          64


char translate(char* arr);
char lookup(int index);
static char charbuf[5];         /* For translate() */
static char c;                  /* Translated character */
static char *temp_kspace;

/* Structure holds information about /proc file */
static struct proc_dir_entry *morse_procfs;
static char *procfs_buffer;     /* Buffer to store characters for the module */
static size_t procfs_size = 8;  /* Size of the procfs buffer */
static ssize_t bytes_read;      /* bytes read/written */


/**
 * Function is called and /proc file is read
 *
 */
static ssize_t morse_read(struct file *filep, char __user *buffer,
                size_t length, loff_t *data)
{
  printk(KERN_INFO "/proc/%s: morse_read() called.\n", PROCFS_NAME);
  bytes_read = 0;

  if (*procfs_buffer == 0) return 0; /* end of file, return 0 */
  else
  { /* Fill the buffer, return the buffer size */
    while (length && *procfs_buffer)
    {
      put_user(*(procfs_buffer++), buffer++);
      --length;
      ++bytes_read;
    }

    /* Note:
     * proc_read() functions don't need to use copy_to_user(),
     * memcpy() does the job because the buffer lives in kernel memory
     */
    /* memcpy(buffer, procfs_buffer, procfs_buffer_size); */
    /* copy_to_user(buffer, procfs_buffer, procfs_buffer_size); */
  }
  kfree(procfs_buffer);
  return bytes_read;
}


/**
 * Function is called when /proc file is written
 *
 */
static ssize_t morse_write(struct file *filep, const char __user *buffer,
                size_t length, loff_t *data)
{
  printk(KERN_INFO "/proc/%s: morse_write() called.\n", PROCFS_NAME);
  printk(KERN_INFO "/proc/%s: buffer length: %zu \n", PROCFS_NAME, length);

  /* Allocate kernel memory */
  procfs_buffer = kmalloc(GFP_KERNEL, 8*sizeof(char));
  if (!procfs_buffer)
  {
    printk(KERN_ALERT "/proc/%s: Error: morse_init() kmalloc\n", PROCFS_NAME);
    return -ENOMEM;
  }
  printk(KERN_ALERT "/proc/%s: procfs_buffer allocated %zu bytes.\n", PROCFS_NAME, procfs_size);
  memset(procfs_buffer, 0, procfs_size);


/********************
 * translation logic
 ********************/
  bytes_read = 0;
  int idx = 0, symbol_sz = 0;

  while (idx != length)
  {
    if (bytes_read+2 > procfs_size)
    { /* check for space */
      procfs_size *= 2;     /* Increase size by a factor of 2 */
      temp_kspace = kmalloc(GFP_KERNEL, procfs_size*sizeof(char));
      if (!temp_kspace)
      {
        printk(KERN_ALERT "/proc/%s: Error: morse_write(), kmalloc(), new_kspace \n", PROCFS_NAME);
        return -ENOMEM;
      }
      printk(KERN_ALERT "/proc/%s: temp_kspace allocated %zu bytes.\n", PROCFS_NAME, procfs_size);

      memcpy(temp_kspace, procfs_buffer, strlen(procfs_buffer));
      kfree(procfs_buffer);
      procfs_buffer = temp_kspace;
      printk(KERN_INFO "/proc/%s: resized procfs_buffer from %zu to %zu "
                       "bytes .\n", PROCFS_NAME, procfs_size/2, procfs_size);
    } /* check for space end */

    if (buffer[idx] == '-' || buffer[idx] == '.') ++symbol_sz;
    else if (buffer[idx] == ' ')
    { /* Write 1-byte character */
      memcpy(charbuf, buffer+idx-symbol_sz, symbol_sz);
      c = translate(charbuf);

      memcpy(procfs_buffer+bytes_read, &c, 1);

      ++bytes_read;
      memset(charbuf, 0, 5);
      symbol_sz = 0;
    }
    else if (buffer[idx] == '|')
    { /* Write 2-bytes, character + <space> */
      memcpy(charbuf, buffer+idx-symbol_sz, symbol_sz);
      c = translate(charbuf);

      memcpy(procfs_buffer+bytes_read, &c, 1);
      c = ' ';
      memcpy(procfs_buffer+bytes_read+1, &c, 1);

      bytes_read += 2;
      memset(charbuf, 0, 5);
      symbol_sz = 0;
    }
    else if (buffer[idx] == '\0' || buffer[idx] == '\n') // '\n' fixed it
    /* else if (buffer[idx] == '\n') */
    { /* Write 2-bytes, character and newline */
      memcpy(charbuf, buffer+idx-symbol_sz, symbol_sz);
      c = translate(charbuf);

      memcpy(procfs_buffer+bytes_read, &c, 1);
      c = '\n';
      memcpy(procfs_buffer+bytes_read+1, &c, 1);

      bytes_read += 2;
    }
    else printk(KERN_INFO "/proc/%s: Error,translation\n", PROCFS_NAME);

    ++idx;
  }
  printk(KERN_INFO "/proc/%s: Translation complete\n"
                   "bytes_read: %zu\nprocfs_size: %zu\n",
                   PROCFS_NAME, bytes_read, procfs_size);
/************************
 * translation logic end
 ************************/

  return length;
}


static struct file_operations proc_fops =
{
  .owner = THIS_MODULE,
  .read = morse_read,
  .write = morse_write,
};


/**
 * Called when module is loaded
 *
 */
static int __init morse_init(void)
{
  /* create the proc entry */
  morse_procfs = proc_create(PROCFS_NAME, 0, NULL, &proc_fops);
  if (morse_procfs == NULL)
  {
    kfree(procfs_buffer);
    printk(KERN_ALERT "/proc/%s: Error: morse_init() failed to create proc entry\n", PROCFS_NAME);
    return -ENOMEM;
  }
  printk(KERN_INFO "/proc/%s: module loaded\n", PROCFS_NAME);

  return 0; /* everything is ok */
}


/**
 * Called when module is unloaded
 */
static void __exit morse_cleanup(void)
{
  kfree(procfs_buffer);
  remove_proc_entry(PROCFS_NAME, NULL);
  printk(KERN_INFO "/proc/%s: module unloaded\n", PROCFS_NAME);
}


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Morse code procfs kernel module");
MODULE_AUTHOR("CS3210 - Group 2");
module_init(morse_init);
module_exit(morse_cleanup);


/**
 *
 *
 */
char translate(char* arr){
    int size = 0; // size of arr
    int index = 1;
    char const *ptr = arr;
    while(*ptr =='-' || *ptr =='.'){
        if(*ptr == '.'){
            index = 2 * index;
        } else if(*ptr == '-'){
            index = 2 * index + 1;
        }
        ++size;
        ++ptr;
    }
    return lookup(index);
}

/**
 *
 *
 */
char lookup(int index){
    // index from 1
    char morse[MORSE_SIZE]  = {
       '?'
      ,'?'
      ,'E' ,'T'
      ,'I' ,'A' ,'N' ,'M'
      ,'S' ,'U' ,'R' ,'W' ,'?' ,'K' , 'G', 'O'
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
    return morse[index];
}

