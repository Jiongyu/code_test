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
#include <linux/wait.h>
#include <linux/atomic.h>
#include <linux/uaccess.h>
#include <linux/fcntl.h>
#include <linux/poll.h>

#include "./noblockIo.h"

char read_buf[20] = "hello,blockIo.";

struct no_block_io_device{
    dev_t dev;
    int major;
    int minor;
    struct cdev cdev;
    struct class *class;
    struct device *device;
    struct timer_list timer;
	unsigned long period;
	spinlock_t lock;
	wait_queue_head_t read_wait;
	atomic_t data_value;

}no_block_io_device;

struct no_block_io_device no_block_io;


void timer_function(struct timer_list *arg)
{
	PINFO("timer_function");
	mod_timer(&no_block_io.timer, jiffies + msecs_to_jiffies(no_block_io.period * 1000));
	atomic_set(&no_block_io.data_value, !atomic_read(&no_block_io.data_value));
	wake_up_interruptible(&no_block_io.read_wait);
}

static int other_device_init(void)
{
	atomic_set(&no_block_io.data_value, 0);

    init_timer_key(&no_block_io.timer, &timer_function, TIMER_DEFERRABLE, "my_timer", NULL);
	no_block_io.timer.expires = jiffies + msecs_to_jiffies(DEFAULT_SLEEP_TIME * 1000);
    no_block_io.timer.function = timer_function;
	no_block_io.period = DEFAULT_SLEEP_TIME;
	add_timer(&no_block_io.timer);
    PDEBUG("timer init.\n");

	init_waitqueue_head(&no_block_io.read_wait);
    PDEBUG("waitqueue_head init.\n");

	return SUCCESS_RETURN;
}

static int io_control_open(struct inode *node, struct file *filp)
{
    PDEBUG(" driver open!!!");
	filp->private_data = &no_block_io;
    return SUCCESS_RETURN;
}

static int io_control_release(struct inode *node, struct file *filp)
{
    PDEBUG("driver release!!!");
    return SUCCESS_RETURN;
}

static ssize_t io_control_read(struct file *filp, char __user *buff, size_t cnt, loff_t *offt)
{
	int ret;
	DECLARE_WAITQUEUE(wait, current);
	if(filp->f_flags & O_NONBLOCK)
	{
		if(atomic_read(&no_block_io.data_value) != 1)
		{
			return -EAGAIN;
		}
	}
	else
	{
		ret = wait_event_interruptible(no_block_io.read_wait, atomic_read(&no_block_io.data_value));
		if (ret)
		{
			goto wait_error;
		} 
		
	}

	if(atomic_read(&no_block_io.data_value) == 1)
	{
		ret = copy_to_user(buff, read_buf, sizeof(read_buf));
		if(ret < 0)
		{
			return -EINVAL;
		}
	}else{
		return -EAGAIN;
	}

	return 0;

wait_error:
	set_current_state(TASK_RUNNING);
	remove_wait_queue(&no_block_io.read_wait, &wait);	
	return ret;

}

static	ssize_t io_control_write(struct file *filp, const char __user *buff, size_t cnt, loff_t *offt)
{
	return 0;
}

static long io_control_unlocked_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct no_block_io_device *dev = (struct no_block_io_device*)filp->private_data;
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

__poll_t io_control_poll (struct file *filp, struct poll_table_struct *poll_table)
{
	unsigned int mask = 0;
	poll_wait(filp, &no_block_io.read_wait, poll_table);

	if(atomic_read(&no_block_io.data_value) == 1)
	{
		mask = POLLIN | POLLRDNORM;
	}
	return mask;
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
	.poll = io_control_poll,
};

static int __init io_control_init(void)
{
    int retvalue = 0;

	spin_lock_init(&no_block_io.lock);

	alloc_chrdev_region(&no_block_io.dev, 0, MODULE_CNT, MODULE_NAME);
	no_block_io.major = MAJOR(no_block_io.dev);
	no_block_io.minor = MINOR(no_block_io.dev);
	PDEBUG("major = %d, minor = %d", no_block_io.major, no_block_io.minor);

	no_block_io.cdev.owner = THIS_MODULE;
	cdev_init(&no_block_io.cdev, &io_control_fops);

	retvalue = cdev_add(&no_block_io.cdev, no_block_io.dev, MODULE_CNT);
	if(!retvalue){
		PDEBUG("cdev_add success!\r\n");
	}else{
		PDEBUG("cdev_add error!\r\n");
	}
	no_block_io.class = class_create(THIS_MODULE, MODULE_NAME);
	if(IS_ERR(no_block_io.class)){
		return PTR_ERR(no_block_io.class);
	}

	no_block_io.device = device_create(no_block_io.class, NULL, no_block_io.dev, NULL, MODULE_NAME);
	if (IS_ERR(no_block_io.device)) {
		return PTR_ERR(no_block_io.device);
		PDEBUG("device_create error!\r\n");
	}
	PDEBUG("device_create success!\r\n");

	other_device_init();

	PINFO("%s init!\r\n", MODULE_NAME);
	
	return SUCCESS_RETURN;
}

static void __exit io_control_exit(void)
{
    cdev_del(&no_block_io.cdev);
	/* 注销字符设备驱动 */
	unregister_chrdev_region(no_block_io.dev, MODULE_CNT);
	PDEBUG("unregister_chrdev_region!\r\n");

	device_destroy(no_block_io.class, no_block_io.dev);
	PDEBUG("device_destroy!\r\n");

	class_destroy(no_block_io.class);
	PDEBUG("class_destroy!\r\n");

	del_timer_sync(&no_block_io.timer);

	PINFO("%s exit!\r\n", MODULE_NAME);
}

module_init(io_control_init);
module_exit(io_control_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jony");
/*  cat /sys/module/chrdevbase/version */
MODULE_VERSION("2.0"); 
MODULE_DESCRIPTION("block io driver test!");
