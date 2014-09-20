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
/* #include <linux/slab.h> */

#define PROCFS_MAX_SIZE    64
#define PROCFS_NAME        "morse64"

/* Structure holds information about /proc file */
static struct proc_dir_entry *morse_procfs;

/* Buffer used to store characters for the module */
static char *procfs_buffer;

/* Size of the procfs buffer */
static ssize_t bytes_read;


/* Function is called and /proc file is read */
static ssize_t morse_read(struct file *filep, char __user *buffer,
                size_t length, loff_t *data)
{
  printk(KERN_INFO "(/proc/%s) morse_read() called.\n", PROCFS_NAME);
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
  printk(KERN_INFO "(/proc/%s) morse_write() called.\n", PROCFS_NAME);

  /* TODO: logic here to deal with write larger than PROCFS_MAX_SIZE */
  bytes_read = (length > PROCFS_MAX_SIZE) ? PROCFS_MAX_SIZE : length;

  /* Write data to the buffer */
    if (copy_from_user(procfs_buffer, buffer, bytes_read))
      return -EFAULT;

  return bytes_read;
}


static struct file_operations proc_fops =
{
  .ower = THIS_MODULE,
  .read = morse_read,
  .write = morse_write,
};


/* Called when module is loaded */
static int __init morse_init(void)
{
  /* create the proc entry */
  morse_procfs = proc_create(PROCFS_NAME, 0, NULL, &proc_fops);
  procfs_buffer = kmalloc(GFP_KERNEL, PROCFS_MAX_SIZE*sizeof(char));

  if (morse_procfs == NULL)
  {
    remove_proc_entry(PROCFS_NAME, NULL);
    printk(KERN_ALERT "Error: Could not initialize /proc/%s\n", PROCFS_NAME);
    return -ENOMEM;
  }

  printk(KERN_INFO "kernel modeule /proc/%s loaded.\n", PROCFS_NAME);
  return 0; /* everything is ok */
}


/* Called when module is unloaded */
static void __exit morse_cleanup(void)
{
  kfree(procfs_buffer);
  remove_proc_entry(PROCFS_NAME, NULL);
  printk(KERN_INFO "kernel module /proc/%s unloaded.\n", PROCFS_NAME);
}


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Morse code procfs kernel module");
MODULE_AUTHOR("CS3210 - Group 2");
module_init(morse_init);
module_exit(morse_cleanup);

