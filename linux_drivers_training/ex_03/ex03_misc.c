/*
file name:		ex03_misc.c
purpose:		it's a demo driver, show how to use "misc_register" to create a char driver
author:			guangwei jiang
create time:	Jan12'10

Notes:
	Test Enviroment: Ubuntu9.04 (kernel 2.6.28-17)

modified history:
 */
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/miscdevice.h>

/* open method, nothing to do so sar*/
static int ex03_open(struct inode *inode, struct file *file)
{
	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return 0;
} /*end ex03_open()*/

/* release method, nothing to do so sar*/
static int ex03_release(struct inode *inode, struct file *file)
{
	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return 0;
} /*end ex03_release()*/

/* Read method, nothing to do so far */
static ssize_t ex03_read(struct file *file, char *buf,
			size_t count, loff_t *ppos)
{
	ssize_t retval = 0;

	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return retval;
} /*end ex03_read()*/


/* Write method, nothing to do so far */
static ssize_t ex03_write(struct file *file, char *buf,
			size_t count, loff_t *ppos)
{
	/*Remeber: the default retval must NOT be 0, or it'll cause kernel retry to call it*/
	ssize_t retval = -ENOMEM;	
	printk("%s: ++\n", __func__);

	printk("%s: the count of buf is %d\n", __func__, count);
	retval = count;

	printk("%s: --\n", __func__);

	return retval;
} /*end ex03_write()*/


/* Ioctl method, nothing to do so far */
static int ex03_ioctl(struct inode *inode, struct file *file,
			unsigned int cmd, unsigned long arg)
{
	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return 0;
} /*end ex03_ioctl()*/

/* file operations for ex03 */
struct file_operations ex03_fops	= {
	.owner		=	THIS_MODULE,		/* Owner */
	.open		=	ex03_open,			/* Open method */
	.release	=	ex03_release,		/* Release method */
	.read		=	ex03_read,			/* Read method */
	.write		=	ex03_write,			/* Write method */
	.ioctl		=	ex03_ioctl,			/* Ioctl method */
};

/* Misc structure */
static struct miscdevice ex03_dev = {
	.minor	= MISC_DYNAMIC_MINOR,		/* dynamically assign minor number */
	.name	= "ex03_dev",				/* /dev/ex03_dev */
	.fops	= &ex03_fops				/* file operations for ex03 */
};

static int ex03_init(void)
{
	/* Register a misc type char driver */
	misc_register(&ex03_dev);

	return 0;
} //end ex03_init()

static void ex03_exit(void)
{
	/* de-register the ex03 driver */
	misc_deregister(&ex03_dev);
} //end ex03_exit()

module_init(ex03_init);
module_exit(ex03_exit);

MODULE_LICENSE("GPL");
