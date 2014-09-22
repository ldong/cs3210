/**
 * morse.c - morse code procfs
 *
 */


#include <linux/module.h>   /* module */
#include <linux/kernel.h>   /* kernel stuff */
#include <linux/proc_fs.h>  /* using proc fs */
#include <asm/uaccess.h>    /* copy_from_user() */

/* #include <linux/sched.h> */
/* #include <linux/string.h> */
/* #include <linux/vmalloc.h> */
/* #include <linux/slab.h> */

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Morse code procfs kernel module");
MODULE_AUTHOR("Daniel Lee");

/* #define MAX_COOKIE_LENGTH       PAGE_SIZE */
#define PROCFS_MAX_SIZE    1024
#define PROCFS_NAME        "morse1k"

/* Structure holds information about /proc file */
static struct proc_dir_entry *morse_procfs;

/* Buffer used to store characters for the module */
static char procfs_buffer[PROCFS_MAX_SIZE];

/* Size of the buffer */
static unsigned long procfs_buffer_size = 0;

/* static char *cookie_pot;  // Space for fortune strings */
/* static int cookie_index;  // Index to write next fortune */
/* static int next_fortune;  // Index to read next fortune */

/* Function is called and /proc file is read */
int morse_read(char *buffer, char **buffer_location, off_t offset,
               int buffer_length, int *eof, void *data)
{
  int ret_val;
  printk(KERN_INFO "morse_read (/proc/%s) called\n", PROCFS_NAME);
  if (offset > 0)
  { /* Have finished to read, return 0 */
    *eof = 1;
    ret_val = 0;
  }
  else
  { /* Fill the buffer, return the buffer size */
    memcpy(buffer, procfs_buffer, procfs_buffer_size);

    /* transaltion */


    ret_val = procfs_buffer_size;
  }

  return ret_val;
}


/* int fortune_read(char *page, char **start, off_t off, */
/*                  int count, int *eof, void *data) */
/* { */
/*   int len; */

/*   if (off > 0) */
/*   { */
/*     *eof = 1; */
/*     return 0; */
/*   } */

/*   /1* Wrap-around *1/ */
/*   if (next_fortune >= cookie_index) next_fortune = 0; */

/*   len = sprintf(page, "%s\n", &cookie_pot[next_fortune]); */
/*   next_fortune += len; */
/*   return len; */
/* } */


/* Function is called when /proc file is written */
int morse_write(struct file *filep, const char *buffer,
                unsigned long count, void *data)
{
  /* Get buffer size */
  printk(KERN_INFO "morse_write (/proc/%s) called\n", PROCFS_NAME);
  procfs_buffer_size = (count > PROCFS_MAX_SIZE) ? PROCFS_MAX_SIZE : count;

  /* Write data to the buffer */
    if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size))
      return -EFAULT;

  return procfs_buffer_size;
}

/* ssize_t fortune_write(struct file *filp, const char __user *buff, */
/*                       unsigned long len, void *data) */
/* { */
/*   int space_available = (MAX_COOKIE_LENGTH-cookie_index)+1; */
/*   if (len > space_available) */
/*   { */
/*     printk(KERN_INFO "fortune: cookie pot is full!\n"); */
/*     return -ENOSPC; */
/*   } */
/*   if (copy_from_user(&cookie_pot[cookie_index], buff, len)) */
/*     return -EFAULT; */
/*   cookie_index += len; */
/*   cookie_pot[cookie_index-1] = 0; */
/*   return len; */
/* } */


/* Called when module is loaded */
int init_morse_module(void)
{
  /* create the /proc file */
  morse_procfs = create_proc_entry(PROCFS_NAME, 0644, NULL);

  if (morse_procfs == NULL)
  {
    /* remove_proc_entry(PROCFS_NAME, &proc_root); */
    remove_proc_entry(PROCFS_NAME, NULL);
    printk(KERN_ALERT "Error: Could not initialize /proc/%s\n", PROCFS_NAME);
    return -ENOMEM;
  }
  morse_procfs->read_proc  = morse_read;
  morse_procfs->write_proc = morse_write;
  /* morse_procfs->owner      = THIS_MODULE; */
  morse_procfs->mode       = S_IFREG | S_IRUGO;
  morse_procfs->uid        = 0;
  morse_procfs->gid        = 0;
  morse_procfs->size       = 37;

  printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);
  return 0; /* everything is ok */
}


/* int init_fortune_module(void) */
/* { */
/*   int ret = 0; */
/*   cookie_pot = (char *)vmalloc(MAX_COOKIE_LENGTH); */
/*   if (!cookie_pot) ret = -ENOMEM; */
/*   else */
/*   { */
/*     memset(cookie_pot, 0, MAX_COOKIE_LENGTH); */
/*     proc_entry = create_proc_entry("fortune", 0644, NULL); */
/*     /1* proc_entry = proc_create("fortune", 0644, &proc_fops); *1/ */
/*     if (proc_entry == NULL) */
/*     { */
/*       ret = -ENOMEM; */
/*       vfree(cookie_pot); */
/*       printk(KERN_INFO "fortune: Couldn't create proc entry\n"); */
/*     } */
/*     else */
/*     { */
/*       cookie_index = 0; */
/*       next_fortune = 0; */
/*       proc_entry->read_proc = fortune_read; */
/*       proc_entry->write_proc = fortune_write; */
/*       /1* proc_entry->owner = THIS_MODULE; *1/ */
/*       printk(KERN_INFO "fortune: Module loaded.\n"); */
/*     } */
/*   } */
/*   return ret; */
/* } */

/* Called when module is unloaded */
void cleanup_morse_module(void)
{
  /* remove_proc_entry(PROCFS_NAME, &proc_root); */
  remove_proc_entry(PROCFS_NAME, NULL);
  printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}

/* void cleanup_fortune_module(void) */
/* { */
/*   /1* remove_proc_entry("fortune", &proc_root); *1/ */
/*   remove_proc_entry("fortune", NULL); */
/*   vfree(cookie_pot); */
/*   printk(KERN_INFO "fortune: Module unloaded.\n"); */
/* } */


module_init(init_morse_module);
module_exit(cleanup_morse_module);

