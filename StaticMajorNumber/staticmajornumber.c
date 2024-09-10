#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

dev_t dev = MKDEV(235, 0);

static int __init static_major_number_demo (void)
{
	register_chrdev_region(dev, 1, "StaticMNumber_Dev");
	printk(KERN_INFO "Major = %d | Minor = %d \n", MAJOR(dev), MINOR(dev));
	printk(KERN_INFO "Kernel Module inserted successfully");
	return 0;
}

static void __exit static_major_number_exit (void)
{
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "Kernel Module removed successfully");
}

module_init(static_major_number_demo);
module_exit(static_major_number_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hoang Anh");
MODULE_DESCRIPTION("Demo for statically allocate major number for Kernel Module");
MODULE_VERSION("1.0");
