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

#include "./asynio.h"


char read_buf[20] = "hello,asynio.";

struct asyn_io_device{
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
	struct fasync_struct *async_quene;

}asyn_io_device;

struct asyn_io_device asyn_io;

static void timer_function(struct timer_list *arg)
{
	PINFO("timer_function");
	mod_timer(&asyn_io.timer, jiffies + msecs_to_jiffies(asyn_io.period * 1000));
	atomic_set(&asyn_io.data_value, !atomic_read(&asyn_io.data_value));
	wake_up_interruptible(&asyn_io.read_wait);
	kill_fasync(&asyn_io.async_quene, SIGIO, POLL_IN); 	// 释放SIGIO信号
}

static int other_device_init(void)
{
	atomic_set(&asyn_io.data_value, 0);

    init_timer_key(&asyn_io.timer, &timer_function, TIMER_DEFERRABLE, "my_timer", NULL);
	asyn_io.timer.expires = jiffies + msecs_to_jiffies(DEFAULT_SLEEP_TIME * 1000);
    asyn_io.timer.function = timer_function;
	asyn_io.period = DEFAULT_SLEEP_TIME;
	add_timer(&asyn_io.timer);
    PDEBUG("timer init.\n");

	init_waitqueue_head(&asyn_io.read_wait);
    PDEBUG("waitqueue_head init.\n");

	return SUCCESS_RETURN;
}

static int io_control_open(struct inode *node, struct file *filp)
{
    PDEBUG(" driver open!!!");
	filp->private_data = &asyn_io;
    return SUCCESS_RETURN;
}

static ssize_t io_control_read(struct file *filp, char __user *buff, size_t cnt, loff_t *offt)
{
	int ret;
	DECLARE_WAITQUEUE(wait, current);
	// 非阻塞访问
	if(filp->f_flags & O_NONBLOCK)
	{
		if(atomic_read(&asyn_io.data_value) != 1)
		{
			return -EAGAIN;
		}
	}
	// 阻塞访问	
	else
	{
		// ret = wait_event_interruptible(asyn_io.read_wait, atomic_read(&asyn_io.data_value));
		// if (ret)
		// {
		// 	goto wait_error;
		// } 
	}

	ret = copy_to_user(buff, read_buf, sizeof(read_buf));
	if(ret < 0)
	{
		return -EINVAL;
	}
	return 0;
		
// wait_error:
// 	set_current_state(TASK_RUNNING);
// 	remove_wait_queue(&asyn_io.read_wait, &wait);	
// 	return ret;

}

static	ssize_t io_control_write(struct file *filp, const char __user *buff, size_t cnt, loff_t *offt)
{
	return 0;
}

static long io_control_unlocked_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct asyn_io_device *dev = (struct asyn_io_device*)filp->private_data;
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

// 处理异步通知
static int io_control_fasync(int fd, struct file *filp, int on)
{
	return fasync_helper(fd, filp, on, &asyn_io.async_quene);
}


static int io_control_release(struct inode *node, struct file *filp)
{
    PDEBUG("driver release!!!");
	return io_control_fasync(-1, filp, 0);

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
	.fasync = io_control_fasync,
};

static int __init io_control_init(void)
{
    int retvalue = 0;

	spin_lock_init(&asyn_io.lock);

	alloc_chrdev_region(&asyn_io.dev, 0, MODULE_CNT, MODULE_NAME);
	asyn_io.major = MAJOR(asyn_io.dev);
	asyn_io.minor = MINOR(asyn_io.dev);
	PDEBUG("major = %d, minor = %d", asyn_io.major, asyn_io.minor);

	asyn_io.cdev.owner = THIS_MODULE;
	cdev_init(&asyn_io.cdev, &io_control_fops);

	retvalue = cdev_add(&asyn_io.cdev, asyn_io.dev, MODULE_CNT);
	if(!retvalue){
		PDEBUG("cdev_add success!\r\n");
	}else{
		PDEBUG("cdev_add error!\r\n");
	}
	asyn_io.class = class_create(THIS_MODULE, MODULE_NAME);
	if(IS_ERR(asyn_io.class)){
		return PTR_ERR(asyn_io.class);
	}

	asyn_io.device = device_create(asyn_io.class, NULL, asyn_io.dev, NULL, MODULE_NAME);
	if (IS_ERR(asyn_io.device)) {
		return PTR_ERR(asyn_io.device);
		PDEBUG("device_create error!\r\n");
	}
	PDEBUG("device_create success!\r\n");

	other_device_init();

	PINFO("%s init!\r\n", MODULE_NAME);
	
	return SUCCESS_RETURN;
}


static void __exit io_control_exit(void)
{
    cdev_del(&asyn_io.cdev);
	/* 注销字符设备驱动 */
	unregister_chrdev_region(asyn_io.dev, MODULE_CNT);
	PDEBUG("unregister_chrdev_region!\r\n");

	device_destroy(asyn_io.class, asyn_io.dev);
	PDEBUG("device_destroy!\r\n");

	class_destroy(asyn_io.class);
	PDEBUG("class_destroy!\r\n");

	del_timer_sync(&asyn_io.timer);

	PINFO("%s exit!\r\n", MODULE_NAME);
}

module_init(io_control_init);
module_exit(io_control_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jony");
/*  cat /sys/module/chrdevbase/version */
MODULE_VERSION("2.0"); 
MODULE_DESCRIPTION("asyn io driver test!");

