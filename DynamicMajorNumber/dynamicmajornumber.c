#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>

dev_t dev = 0;

static int __init dynamic_major_number_init(void)
{
	if (alloc_chrdev_region(&dev, 0, 1, "Dynamic_Major_Number_Dev") < 0)
	{
		printk(KERN_INFO "Can not dynamically allocate major number to Kernel Module \n");
		return -1;
	}
	printk(KERN_INFO "Major: %d | Minor: %d \n", MAJOR(dev), MINOR(dev));
	printk(KERN_INFO "Kernel Module inserted successfully\n");
	return 0;
}

static void __exit dynamic_major_number_exit(void)
{
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "Kernel module removed successfully\n");
}

module_init(dynamic_major_number_init);
module_exit(dynamic_major_number_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hoang Anh");
MODULE_DESCRIPTION("Module for dynamically allocate major number for Kernel Module.");
MODULE_VERSION("1.0");
