/*
file name:		ex02_char.c
purpose:		it's a demo drivers, show how to create a char driver.
author:			guangwei jiang
create time:	Jan12'10

Notes:
	Test Enviroment: Ubuntu9.04 (kernel 2.6.28-17)

modify history:
 */
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/init.h>


static struct class *ex02_class;
static struct cdev	*ex02_cdev;

int ex02_major_num	= 179;
int ex02_minor_num	= 0;

/* open method, nothing to do so sar*/
static int ex02_open(struct inode *inode, struct file *file)
{
	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return 0;
} /*end ex02_open()*/

/* release method, nothing to do so sar*/
static int ex02_release(struct inode *inode, struct file *file)
{
	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return 0;
}/*end ex02_release()*/



/* Read method, nothing to do so far */
static ssize_t ex02_read(struct file *file, char *buf,
			size_t count, loff_t *ppos)
{
	ssize_t retval = 0;

	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return retval;
} /*end ex02_read()*/


/* Write method, nothing to do so far */
static ssize_t ex02_write(struct file *file, char *buf,
			size_t count, loff_t *ppos)
{
	/*Remeber: the default retval must NOT be 0, or it'll cause kernel retry to call it*/
	ssize_t retval = -ENOMEM;	
	printk("%s: ++\n", __func__);

	printk("%s: the count of buf is %d\n", __func__, count);
	retval = count;

	printk("%s: --\n", __func__);

	return retval;
} /*end ex02_write()*/


/* Ioctl method, nothing to do so far */
static int ex02_ioctl(struct inode *inode, struct file *file,
			unsigned int cmd, unsigned long arg)
{
	printk("%s: ++\n", __func__);

	printk("%s: --\n", __func__);

	return 0;
} /*end ex02_ioctl()*/

/* File operations on ex02, acturally nothing to do */
static struct file_operations ex02_fops	= {
	.owner		=	THIS_MODULE,		/* Owner */
	.open		=	ex02_open,			/* Open method */
	.release	=	ex02_release,		/* Release method */
	.read		=	ex02_read,			/* Read method */
	.write		=	ex02_write,			/* Write method */
	.ioctl		=	ex02_ioctl,			/* Ioctl method */
};

/* Driver Initializeation */
static int __init
ex02_init(void)
{
	int dev_no = 0;

	printk("%s: ++\n", __func__);

	dev_no = MKDEV(ex02_major_num, ex02_minor_num);

	/* 1st stage, add the char device to kenel */

	/* 1.1 allocate memory for cdev struct */
	ex02_cdev = cdev_alloc();

	/* 1.2 Connect the file operations with the cdev */ 
	cdev_init(ex02_cdev, &ex02_fops);
	ex02_cdev->owner	= THIS_MODULE;

	/* 1.3 Connect the major/minor number to the cdev */
	if (cdev_add(ex02_cdev, dev_no, 1))
	{
		printk("%s: add cdev failed!\n", __func__);
		return 1; 
	}

	/* 2nd stage, create /dev node */
	/* 2.1 create sysfs entries */
	ex02_class = class_create(THIS_MODULE, "ex02_class");

	/* 2.2 Send uevents to udev, so it'll create /dev nodes */
	device_create(ex02_class, NULL, dev_no, NULL, "ex02_dev");
	
	printk("%s: --\n", __func__);
	return 0;
} //end ex02_init()


/* Driver Exit */
static void __exit
ex02_exit(void)
{
	printk("%s: ++\n", __func__);

	/* 1st stage: remove the cdev*/
	cdev_del(ex02_cdev);

	/* 2nd stage: remove the nodes under /dev and destry the class */

	/* 2.1 it will destroy the device node under /dev, anything else?*/
	device_destroy(ex02_class, MKDEV(ex02_major_num, ex02_minor_num));

	/* 2.2 Destroy class */
	class_destroy(ex02_class);

	printk("%s: --\n", __func__);

} //end ex02_exit()


module_init(ex02_init);
module_exit(ex02_exit);

/* Really very strange, if no "MODULE_LICENSE", there will have "symbol not found" errors 
   to call class_create(and other class related APIs) when running*/
MODULE_LICENSE("GPL");
