/*
	2017707007 Minjun-KANG
	Kernel Module programming
	Implements Timer module

*/

#include <linux/timer.h> //Nedded Tiemr.h
#include <linux/kernel.h> /*Needed for KERN_IFO*/
#include <linux/module.h> /*Needed by all modules*/
#include <linux/init.h> /* Needed for the macros */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("2017707007 Minjun-KANG");
MODULE_DESCRIPTION("module programming - Timer module");

static struct timer_list my_timer; // Timer list
void my_timer_callback(unsigned long );

static int __init module_begin(void) //init
{
	int temp;
	
	printk("Timer, linux kernel module. jiffies - (%ld) \n",jiffies);
	
	// non 0 return means init_module failed; module can't be loaded.i
		
	setup_timer(&my_timer, my_timer_callback, 0);
  	printk("Timer module installing \n");
  	printk( "Starting timer to fire in 1000ms (%ld)\n", jiffies );

	temp = mod_timer( &my_timer, jiffies + msecs_to_jiffies(1000) );
	if (temp) printk("Error in mod_timer");

	printk("mod_timer end, jiffies - (%ld)\n",jiffies); 
	return 0;
}


static void __exit module_end(void) //exit
{
	int temp = del_timer(&my_timer);
	if(temp) printk("The timer use. \n");
	
	printk("End timer -(%ld)\n",jiffies);
	printk("remove timer - Good Bye!\n");
}

void my_timer_callback(unsigned long data)
{
	printk("my_timer_callback called (%ld).", jiffies);
}

module_init(module_begin);
module_exit(module_end);
