/*
	2017707007 Minjun-KANG
	Kernel Module programming
	Implements of linked list
*/


#include <linux/kernel.h> /*Needed for KERN_IFO*/
#include <linux/module.h> /*Needed by all modules*/
#include <linux/init.h> /* Needed for the macros */
#include <linux/list.h> // Needed for link head
#include <linux/slab.h> 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("BUTTER SHOWER");
MODULE_DESCRIPTION("module programming - hello module");


typedef struct Node{
	int data;
	struct list_head list;
}NODE;


static int list_plus(int);
static void list_print(void);
static NODE* list_search(int);
static int list_minus(int);


LIST_HEAD(Node_head);

static int list_plus(int data)
{
	NODE *new;
	new = (NODE *)kmalloc(sizeof(NODE),GFP_KERNEL);
	new->data = data;
	list_add_tail(&new->list, &Node_head);

	return 0;
}

static void list_print(void)
{
	NODE *p;
	list_for_each_entry(p, &Node_head, list)
	{
		printk("data (%d)", p->data);
		if((p->list).next != &Node_head)
			printk("-> ");
	}
	printk("\n");
}

static NODE* list_search(int index)
{
	int cnt;
	NODE *p;
	NODE *target;

	cnt = 0;
	list_for_each_entry(p, &Node_head, list)
	{
		if(cnt++ == index)
		{
			target = p;	
		}
	}
	return target;
}

static int IS_not_empty(NODE *p)
{
	if(((p->list).next)->next != NULL)
	{
		return 0; //have tail
	}else
	{
		return -1; //emtpy
	}
}
static int list_minus(int index)
{
	NODE *p;
//	int re_num;
//	re_num = 0;

	p = list_search(index);
	
	if((p->list).next == &Node_head) //head case
	{
	
		if(!IS_not_empty(p))
		{
			Node_head.next = ((p->list).next)->next;
		}else 
		{
			printk("All of Linked list, Delete\n");
		}
		printk("Head node Delete Success\n");
	}
	else if(IS_not_empty(p) == -1) //tail case
	{
		((p->list).prev)->next = NULL;	
	}
	else //general case
	{
		printk("%d - data find\n",p->data);
		list_del(&(p->list));
		printk("Node Delete Success\n");
	}
	list_print();
	return 0;
}


static int __init module_begin(void) //init
{
	
	printk("Hello, linux kernel module. \n");
	LIST_HEAD(Node_head);
	
	list_plus(10);
	list_plus(20);
	list_plus(30);
	list_print();
	list_minus(1);
//	list_minus(1);
//	list_print();
	

	return 0;
	// non 0 return means init_module failed; module can't be loaded.i
}

static void __exit module_end(void) //exit
{
	printk("Good Bye!\n");
}

module_init(module_begin);
module_exit(module_end);
