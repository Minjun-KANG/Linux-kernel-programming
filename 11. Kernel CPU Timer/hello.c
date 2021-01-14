/*
	2017707007 Minjun-KANG
	Kernel Module programming

*/


#include <linux/kernel.h> /*Needed for KERN_IFO*/
#include <linux/module.h> /*Needed by all modules*/
#include <linux/init.h> /* Needed for the macros */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("BUTTER SHOWER");
MODULE_DESCRIPTION("module programming - hello module");

static int __init module_begin(void) //init
{
	
	printk("Hello, linux kernel module. \n");
	return 0;
	// non 0 return means init_module failed; module can't be loaded.i
}

static void __exit module_end(void) //exit
{
	printk("Good Bye!\n");
}

module_init(module_begin);
module_exit(module_end);
