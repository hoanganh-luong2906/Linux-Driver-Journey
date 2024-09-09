#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

int valueETX, arr_valueETX[4];
char *nameETX;
int cb_valueETX = 0;

int notify_param(const char *val, const struct kernel_param *kp);

module_param(valueETX, int, S_IRUSR | S_IWUSR); //Module param using int value type
module_param(nameETX, charp, S_IRUSR | S_IWUSR); //Module param using char pointer type
module_param_array(arr_valueETX, int, NULL, S_IRUSR | S_IWUSR); //Module param with array of int type

//function notifying new value of params in kernel
int notify_param(const char *val, const struct kernel_param *kp)
{
	int res	= param_set_int(val, kp);
	if (res == 0)
	{
		printk(KERN_INFO "Callback function called\n");
	       	printk(KERN_INFO "New value of cb_valueETX= %d\n", cb_valueETX);
		return 0;
	}
	return -1;
}

//Custom operation using default getter and setter of the system
const struct kernel_param_ops custom_param_ops = 
{
	.set = &notify_param,
	.get = &param_get_int,
};

//Passing value, callback function for module_param_cb to listen to data change
module_param_cb(cb_valueETX, &custom_param_ops, &cb_valueETX, S_IRUGO | S_IWUSR);

static int __init parammacros_init(void)
{
	int i;
	printk(KERN_INFO "ValueETX = %d		\n", valueETX);
	printk(KERN_INFO "cb_valueETX = %d	\n", cb_valueETX);
	printk(KERN_INFO "NameEXT = %s		\n", nameETX);
	for (i = 0; i < (sizeof arr_valueETX / sizeof (int)); i++)
	{
		printk(KERN_INFO "Array int value[%d] = %d	\n", i, arr_valueETX[i]);
	}
	printk(KERN_INFO "Kernel module inserted successfully...\n");
	return 0;
}

static void __exit parammacros_exit(void)
{
	printk(KERN_INFO "Kernel Module removed successfully...\n");
}

module_init(parammacros_init);
module_exit(parammacros_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hoang Anh Luong");
MODULE_DESCRIPTION("Simple Permission params implementation kernel module");
MODULE_VERSION("1.0");

