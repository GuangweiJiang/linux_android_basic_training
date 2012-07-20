/*
file name:		hello.c
purpose:		it's a demo driver, show how the basic conception of module.
author:			guangwei jiang
create date:	Jan11'10

Notes:
	Test Enviroment: Ubuntu9.04 (kernel 2.6.28-17)

Modified history:
 */

#include <linux/init.h>
#include <linux/module.h>


static int hello_init(void)
{
	printk("Hello, world\n");
	return 0;
}

static void hello_exit(void)
{
	printk("Goodbye, world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");

