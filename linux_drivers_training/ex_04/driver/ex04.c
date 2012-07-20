/*
file name:		ex04.c
purpose:		it's a demo driver, show how to use ioctol to communicate with user space 
author:			guangwei jiang
create time:	Jan13'10

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


#define EX04_IOCTL_MAGIC 'v'

#define EX04_IOCTL_TEST			_IO(EX04_IOCTL_MAGIC, 1000)
#define EX04_IOCTL_GET_VAL		_IOR(EX04_IOCTL_MAGIC , 1001, int)
#define EX04_IOCTL_SET_VAL		_IOW(EX04_IOCTL_MAGIC , 1002, int)

/* open method, nothing to do so sar*/
static int ex04_open(struct inode *inode, struct file *file)
{
	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return 0;
} /*end ex04_open()*/

/* release method, nothing to do so sar*/
static int ex04_release(struct inode *inode, struct file *file)
{
	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return 0;
} /*end ex04_release()*/

/* Read method, nothing to do so far */
static ssize_t ex04_read(struct file *file, char *buf,
			size_t count, loff_t *ppos)
{
	ssize_t retval = 0;

	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return retval;
} /*end ex04_read()*/


/* Write method, nothing to do so far */
static ssize_t ex04_write(struct file *file, char *buf,
			size_t count, loff_t *ppos)
{
	/*Remeber: the default retval must NOT be 0, or it'll cause kernel retry to call it*/
	ssize_t retval = -ENOMEM;	
	printk("%s: ++\n", __func__);

	printk("%s: the count of buf is %d\n", __func__, count);
	retval = count;

	printk("%s: --\n", __func__);

	return retval;
} /*end ex04_write()*/


/* Ioctl method, nothing to do so far */
static int ex04_ioctl(struct inode *inode, struct file *file,
			unsigned int cmd, unsigned long arg)
{
	int retval = 0;
	static int test_val = 888;

	printk("%s: ++\n", __func__);

	switch(cmd) {
		case EX04_IOCTL_TEST:
			printk("%s: EX04_IOCTL_TEST\n", __func__);
			return test_val;

		case EX04_IOCTL_GET_VAL:
			printk("%s: EX04_IOCTL_GET_VAL\n", __func__);
			retval = __put_user(test_val, (int __user *)arg);
			break;

		case EX04_IOCTL_SET_VAL:
			printk("%s: EX04_IOCTL_SET_VAL\n", __func__);
			retval = __get_user(test_val, (int __user *)arg);
			break;

		default:
			printk("%s: no such cmd!\n", __func__);
			return -EIO;
	}

	printk("%s: --, retval=%d\n", __func__, retval);

	return retval;
} /*end ex04_ioctl()*/

/* file operations for ex04 */
struct file_operations ex04_fops	= {
	.owner		=	THIS_MODULE,		/* Owner */
	.open		=	ex04_open,			/* Open method */
	.release	=	ex04_release,		/* Release method */
	.read		=	ex04_read,			/* Read method */
	.write		=	ex04_write,			/* Write method */
	.ioctl		=	ex04_ioctl,			/* Ioctl method */
};

/* Misc structure */
static struct miscdevice ex04_dev = {
	.minor	= MISC_DYNAMIC_MINOR,		/* dynamically assign minor number */
	.name	= "ex04_dev",				/* /dev/ex04_dev */
	.fops	= &ex04_fops				/* file operations for ex04 */
};

static int ex04_init(void)
{
	/* Register a misc type char driver */
	misc_register(&ex04_dev);

	return 0;
} //end ex04_init()

static void ex04_exit(void)
{
	/* de-register the ex04 driver */
	misc_deregister(&ex04_dev);
} //end ex04_exit()

module_init(ex04_init);
module_exit(ex04_exit);

MODULE_LICENSE("GPL");
