#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

static int hehe __initdata = 3;

static int __init my_kernel_init(void) {
	pr_info("==================\n");
	pr_info("Hello!!!\n");
	pr_info("Thanks for coming!!\n");
	pr_info("==================\n");
	pr_info("Your number info is %d\n", hehe);
	return 0;
}
static void __exit my_kernel_exit(void) {
	pr_info("Goodbye\n");
	pr_info("Have a good time!!!\n");
	pr_info("==================\n");
}

module_init(my_kernel_init);
module_exit(my_kernel_exit);

MODULE_LICENSE("GPL");
