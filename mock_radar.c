#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mock_radar"
#define RADAR_DATA "Mock radar data\n"

static int major;
static char msg[] = RADAR_DATA;

static ssize_t dev_read(struct file *filp, char *buffer, size_t len, loff_t *offset) {
    int bytes_read = 0;
    if (*offset == 0) {
        bytes_read = strlen(msg);
        if (copy_to_user(buffer, msg, bytes_read)) return -EFAULT;
        *offset += bytes_read;
    }
    return bytes_read;
}

static struct file_operations fops = {
    .read = dev_read,
};

static int __init mock_radar_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) return major;
    printk(KERN_INFO "Mock radar module loaded with device major number %d\n", major);
    return 0;
}

static void __exit mock_radar_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Mock radar module unloaded\n");
}

module_init(mock_radar_init);
module_exit(mock_radar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Future Farzad");
MODULE_DESCRIPTION("Mock Radar Kernel Module for ADAS Testing");