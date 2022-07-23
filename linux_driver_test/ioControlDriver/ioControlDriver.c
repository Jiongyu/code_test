#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/timer.h>
#include <linux/ide.h>
#include <linux/delay.h>
#include <linux/time.h>

#include "./ioControlDriver.h"

struct io_control_device{
    dev_t dev;
    int major;
    int minor;
    struct cdev cdev;
    struct class *class;
    struct device *device;
    struct timer_list timer;
	unsigned long period;
	spinlock_t lock;

}io_control_device;

struct io_control_device io_control_;


void timer_function(struct timer_list *arg)
{
	struct timer_list *timer = (struct timer_list *)arg;
	PINFO("timer_function");
	mod_timer(timer, jiffies + msecs_to_jiffies(io_control_.period * 1000));
}

static int other_device_init(void)
{
    init_timer_key(&io_control_.timer, &timer_function, TIMER_DEFERRABLE, "my_timer", NULL);
	io_control_.timer.expires = jiffies + msecs_to_jiffies(DEFAULT_SLEEP_TIME * 1000);
    io_control_.timer.function = timer_function;
	io_control_.period = DEFAULT_SLEEP_TIME;
	add_timer(&io_control_.timer);
    PDEBUG("my_timer init.\n");

	return SUCCESS_RETURN;
}

static int io_control_open(struct inode *node, struct file *filp)
{
    PDEBUG(" driver open!!!");
	filp->private_data = &io_control_;
    return SUCCESS_RETURN;
}

static int io_control_release(struct inode *node, struct file *filp)
{
    PDEBUG("driver release!!!");
    return SUCCESS_RETURN;
}

static ssize_t io_control_read(struct file *filp, char __user *buff, size_t cnt, loff_t *offt)
{
	return 0;
}

static	ssize_t io_control_write(struct file *filp, const char __user *buff, size_t cnt, loff_t *offt)
{
	return 0;
}

static long io_control_unlocked_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct io_control_device *dev = (struct io_control_device*)filp->private_data;
	unsigned long flags;


	switch (cmd)
	{
		case OPEN_CMD:
		    PDEBUG("OPEN COMMAND.");
			mod_timer(&dev->timer, jiffies + msecs_to_jiffies(DEFAULT_SLEEP_TIME * 1000));
			break;
			
		case CLOSE_CMD:
		    PDEBUG("CLOSE COMMAND.");
			del_timer_sync(&dev->timer);
			break;
		case SETPERIOD_CMD:
		    PDEBUG("SET CLOCK PERIOD COMMAND.");
			spin_lock_irqsave(&dev->lock, flags);
			dev->period = arg;
			spin_unlock_irqrestore(&dev->lock, flags);
			mod_timer(&dev->timer, jiffies + msecs_to_jiffies(arg * 1000));

			break;
		default:
		    PDEBUG("DEFAULT COMMAND.");
			break;
	}
	return 0;
}

/*
 * 设备操作函数结构体
 */
static struct file_operations io_control_fops = {
	.owner = THIS_MODULE,	
	.open = io_control_open,
	.read = io_control_read,
	.write = io_control_write,
	.release = io_control_release,
    .unlocked_ioctl = io_control_unlocked_ioctl,
};

static int __init io_control_init(void)
{
    int retvalue = 0;

	spin_lock_init(&io_control_.lock);

	alloc_chrdev_region(&io_control_.dev, 0, MODULE_CNT, MODULE_NAME);
	io_control_.major = MAJOR(io_control_.dev);
	io_control_.minor = MINOR(io_control_.dev);
	PDEBUG("major = %d, minor = %d", io_control_.major, io_control_.minor);

	io_control_.cdev.owner = THIS_MODULE;
	cdev_init(&io_control_.cdev, &io_control_fops);

	retvalue = cdev_add(&io_control_.cdev, io_control_.dev, MODULE_CNT);
	if(!retvalue){
		PDEBUG("cdev_add success!\r\n");
	}else{
		PDEBUG("cdev_add error!\r\n");
	}
	io_control_.class = class_create(THIS_MODULE, MODULE_NAME);
	if(IS_ERR(io_control_.class)){
		return PTR_ERR(io_control_.class);
	}

	io_control_.device = device_create(io_control_.class, NULL, io_control_.dev, NULL, MODULE_NAME);
	if (IS_ERR(io_control_.device)) {
		return PTR_ERR(io_control_.device);
		PDEBUG("device_create error!\r\n");
	}
	PDEBUG("device_create success!\r\n");

	other_device_init();

	PINFO("%s init!\r\n", MODULE_NAME);
	
	return SUCCESS_RETURN;
}


static void __exit io_control_exit(void)
{
    cdev_del(&io_control_.cdev);
	/* 注销字符设备驱动 */
	unregister_chrdev_region(io_control_.dev, MODULE_CNT);
	PDEBUG("unregister_chrdev_region!\r\n");

	device_destroy(io_control_.class, io_control_.dev);
	PDEBUG("device_destroy!\r\n");

	class_destroy(io_control_.class);
	PDEBUG("class_destroy!\r\n");

	del_timer_sync(&io_control_.timer);

	PINFO("%s exit!\r\n", MODULE_NAME);
}

module_init(io_control_init);
module_exit(io_control_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jony");
/*  cat /sys/module/chrdevbase/version */
MODULE_VERSION("2.0"); 
MODULE_DESCRIPTION("io control driver test!");

