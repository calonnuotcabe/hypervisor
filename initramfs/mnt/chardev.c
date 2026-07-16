#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>

static int __init my_kernel_init(void);
static void __exit my_kernel_exit(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "huhu_dev"
#define BUF_LEN 80

static int Major = 0;
static int Device_Open = 0;
char msg[BUF_LEN];
char *msg_Ptr;

struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};


static int __init my_kernel_init(void) {
    Major = register_chrdev(0, DEVICE_NAME, &fops);
    if (Major < 0) {
        return Major;
    }
    pr_info("Your major number is %d\n", Major);
    pr_info("'mknod /dev/hello c %d 0'.\n", Major);
    return SUCCESS;
}
static void __exit my_kernel_exit(void) {
    unregister_chrdev(Major, DEVICE_NAME);
}

static int device_open(struct inode *inode,struct file *file) {
    static int counter = 0;
    if (Device_Open) 
        return -EBUSY;
    Device_Open++;
    sprintf(msg, "I already told you %d times Hello world!\n", counter++);
    msg_Ptr = msg;
    try_module_get(THIS_MODULE);

    return SUCCESS;
}
static int device_release(struct inode *inode, struct file *file) {
    Device_Open--;
    module_put(THIS_MODULE);
    return 0;
}
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
    int bytes_read = 0;
    if (*msg_Ptr == 0) {
        return 0;
    }
    while (length && *msg_Ptr) {
        put_user(*(msg_Ptr++), buffer++);
        length--;
        bytes_read++;
    }
    return bytes_read;
}
static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
    printk("<1>Sorry, this operation isn't supported.\n");
    return -EINVAL;
}
module_init(my_kernel_init);
module_exit(my_kernel_exit);
MODULE_LICENSE("GPL");
