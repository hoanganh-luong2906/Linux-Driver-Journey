#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/device.h>

dev_t dev = 0;
static struct class *dev_class;

static int __init file_generation_init(void)
{
	if (alloc_chrdev_region(&dev, 0, 1, "etx_device") < 0) 
	{
		pr_err("Can not create Character Device\n");
		return -1;
	}
	pr_info("Major: %d | Minor: %d", MAJOR(dev), MINOR(dev));

	dev_class = class_create("etx_lass");
	if (IS_ERR(dev_class))
	{
		pr_err("Cannot create struct class for device");
		goto r_class;	
	}
	
	if (IS_ERR(device_create(dev_class, NULL, dev, NULL, "etx_device")))
	{
		pr_err("Can not create device");
		goto r_device;
	}

	pr_info("Create Kernel Module successfully");
	return 0;

	r_device:
        	class_destroy(dev_class);
	r_class:
        	unregister_chrdev_region(dev,1);
        	return -1;
}

static void __exit file_generation_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev, 1);
	pr_info("Module exit sucessfully\n");
}

module_init(file_generation_init);
module_exit(file_generation_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hoang Anh");
MODULE_DESCRIPTION("Auto device file generation project");
MODULE_VERSION("1.0");
