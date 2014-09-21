/**
 * morse.c - morse code procfs
 *
 */


#include <linux/module.h>   /* module */
#include <linux/kernel.h>   /* kernel stuff */
#include <linux/proc_fs.h>  /* using proc fs */
#include <linux/slab.h>     /* kmalloc() */
#include <asm/uaccess.h>    /* copy_from_user() */

#include <linux/string.h>   /* strstr() */
#include <linux/vmalloc.h>   /* strstr() */


/* #include <linux/sched.h> */
/* #include <linux/string.h> */
/* #include <linux/slab.h> */

#define PROCFS_NAME        "morse"

///
#define MORSE_SIZE 64
char translate(char* arr);
char lookup(int index);
char charbuf[5];
char *usr_buffer;
char *new_kspace;
char c;
///

/* Structure holds information about /proc file */
static struct proc_dir_entry *morse_procfs;

/* Buffer used to store characters for the module */
static char *procfs_buffer;

/* Size of the procfs buffer */
static size_t PROCFS_SIZE = 8;
static ssize_t bytes_read;


/* Function is called and /proc file is read */
static ssize_t morse_read(struct file *filep, char __user *buffer,
                size_t length, loff_t *data)
{
  printk(KERN_INFO "/proc/%s: morse_read() called.\n", PROCFS_NAME);
  bytes_read = 0;

  /* end of message, return 0 signifying end of file */
  if (*procfs_buffer == 0) return 0;
  else
  { /* Fill the buffer, return the buffer size */
    while (length && *procfs_buffer)
    {
      put_user(*(procfs_buffer++), buffer++);
      --length;
      ++bytes_read;
    }
    /* memcpy(buffer, procfs_buffer, procfs_buffer_size); */
    /* proc_read functions dont need to use copy_to_user, memcpy does the job
     * b/c buffer lives in kernel memory.*/
    /* copy_to_user(buffer, procfs_buffer, procfs_buffer_size); */
  }
  return bytes_read;
}


/* Function is called when /proc file is written */
static ssize_t morse_write(struct file *filep, const char __user *buffer,
                size_t length, loff_t *data)
{
  bytes_read = 0;
  /* Get buffer size */
  printk(KERN_INFO "/proc/%s: morse_write() called.\n", PROCFS_NAME);

  printk(KERN_INFO "/proc/%s: length: %zu \n", PROCFS_NAME, length);


  // parse for single characters (delimeted by a space)
  /* char charbuf[5]; */
  /* char c; */
  int i = 0; int r = 0;
  /* char *usr_buffer; */
  /* usr_buffer = vmalloc(length*sizeof(char)/5); */
  usr_buffer = vmalloc(length*sizeof(char));
  while (length)
  {
    if (buffer[i] == '-' || buffer[i] == '.')
    {
      ++r;
    }
    else if (buffer[i] == ' ')
    {
      memcpy(charbuf, buffer+i-r, r);
      c = translate(charbuf);
      length -= (++r);

      /* write c to buffer */
  printk(KERN_INFO "%c",c);
      /* usr_buffer[bytes_read] = c; */
      ++bytes_read;
      memset(charbuf, 0, 5);
      r = 0;
    }
    else if (buffer[i] == '|')
    {
      memcpy(charbuf, buffer+i-r, r);
      c = translate(charbuf);
      length -= (++r);

      /* write c+<space> to buffer */
  printk(KERN_INFO "%c ",c);
      /* usr_buffer[bytes_read] = c; */
      /* usr_buffer[bytes_read+1] = ' '; */
      bytes_read += 2;
      memset(charbuf, 0, 5);
      r = 0;
    }
    else if (buffer[i] == '\0' || buffer[i] == '\n') // '\n' fixed it
    {
      memcpy(charbuf, buffer+i-r, r);
      c = translate(charbuf);
      length -= (++r);

      /* write c+\0 to buffer */
  printk(KERN_INFO "%c\n",c);
      /* usr_buffer[bytes_read] = c; */
      /* usr_buffer[bytes_read+1] = '\n'; */
      bytes_read += 2;

      /* could break here... */
      break;
    }
    else if (buffer[i] == '"') ;
    else printk(KERN_INFO "ERROR: /proc/%s: translation\n", PROCFS_NAME);

    ++i;
  }

  while (bytes_read > PROCFS_SIZE)
  {
    PROCFS_SIZE *= 2;
    /* char *new_kspace; */
    new_kspace = kmalloc(GFP_KERNEL, PROCFS_SIZE*sizeof(char));
    kfree(procfs_buffer);
    procfs_buffer = new_kspace;
    printk(KERN_INFO "/proc/%s: resized kmemory from "
                      "%zu to %zu.\n", PROCFS_NAME, PROCFS_SIZE/2, PROCFS_SIZE);
  }


  //////////////////////////////////////
  /* while (length > PROCFS_SIZE) */
  /* { */
  /*   PROCFS_SIZE *= 2; */
  /*   char *new_kspace; */
  /*   new_kspace = kmalloc(GFP_KERNEL, PROCFS_SIZE*sizeof(char)); */
  /*   kfree(procfs_buffer); */
  /*   procfs_buffer = new_kspace; */
  /*   printk(KERN_INFO "/proc/%s: resized kmemory from " */
  /*                     "%zu to %zu.\n", PROCFS_NAME, PROCFS_SIZE/2, PROCFS_SIZE); */
  /* } */
  /* bytes_read = length; */
  //////////////////////////////////////

  /* Write data to the buffer TODO: buffer is the word buffer now */
    /* if (copy_from_user(procfs_buffer, buffer, bytes_read)) */
  /* if (copy_from_user(procfs_buffer, usr_buffer, bytes_read)) */
  if (copy_from_user(procfs_buffer, (const char __user *) usr_buffer, bytes_read))
    return -EFAULT;

  vfree(usr_buffer);

  return bytes_read;
}


static struct file_operations proc_fops =
{
  .owner = THIS_MODULE,
  .read = morse_read,
  .write = morse_write,
};


/* Called when module is loaded */
static int __init morse_init(void)
{
  /* create the proc entry */
  morse_procfs = proc_create(PROCFS_NAME, 0, NULL, &proc_fops);
  procfs_buffer = kmalloc(GFP_KERNEL, PROCFS_SIZE*sizeof(char));

  if (morse_procfs == NULL)
  {
    remove_proc_entry(PROCFS_NAME, NULL);
    printk(KERN_ALERT "Error: Could not initialize /proc/%s\n", PROCFS_NAME);
    return -ENOMEM;
  }

  printk(KERN_INFO "init: /proc/%s loaded\n", PROCFS_NAME);
  return 0; /* everything is ok */
}


/* Called when module is unloaded */
static void __exit morse_cleanup(void)
{
  kfree(procfs_buffer);
  remove_proc_entry(PROCFS_NAME, NULL);
  printk(KERN_INFO "cleanup: /proc/%s unloaded\n", PROCFS_NAME);
}


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Morse code procfs kernel module");
MODULE_AUTHOR("CS3210 - Group 2");
module_init(morse_init);
module_exit(morse_cleanup);


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
