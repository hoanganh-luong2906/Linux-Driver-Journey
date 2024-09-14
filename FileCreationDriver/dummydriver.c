#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

static int __init project_init(void)
{
	return 0;
}

static void __exit project_exit(void)
{
	pr_info("Kernel module removed successfully.\n");
}

module_init(project_init);
module_exit(project_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hoang Anh");
MODULE_DESCRIPTION("CRUD on device's file created by this project.");
MODULE_VERSION("1.0");
