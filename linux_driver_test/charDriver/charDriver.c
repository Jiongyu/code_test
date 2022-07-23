#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/device.h>

#include "charDriver.h"

static char readbuf[100];		/* 读缓冲区 */
static char writebuf[100];		/* 写缓冲区 */
static char kerneldata[] = {"kernel data!"};

static dev_t device;
static int major;
static int minor;
struct cdev cdev;
struct class *class;
struct device *device_;

/*
 * @description		: 打开设备
 * @param - inode 	: 传递给驱动的inode
 * @param - filp 	: 设备文件，file结构体有个叫做private_data的成员变量
 * 					  一般在open的时候将private_data指向设备结构体。
 * @return 			: 0 成功;其他 失败
 */
static int chrdevbase_open(struct inode *inode, struct file *filp)
{
	//printk("chrdevbase open!\r\n");
	return 0;
}

/*
 * @description		: 从设备读取数据 
 * @param - filp 	: 要打开的设备文件(文件描述符)
 * @param - buf 	: 返回给用户空间的数据缓冲区
 * @param - cnt 	: 要读取的数据长度
 * @param - offt 	: 相对于文件首地址的偏移
 * @return 			: 读取的字节数，如果为负值，表示读取失败
 */
static ssize_t chrdevbase_read(struct file *filp, char __user *buf, size_t cnt, loff_t *offt)
{
	int retvalue = 0;
	
	/* 向用户空间发送数据 */
	memcpy(readbuf, kerneldata, sizeof(kerneldata));
	retvalue = copy_to_user(buf, readbuf, cnt);
	if(retvalue == 0){
		printk(KERN_DEBUG  "kernel senddata ok!\r\n");
	}else{
		printk(KERN_DEBUG  "kernel senddata failed!\r\n");
	}
	
	//printk("chrdevbase read!\r\n");
	return 0;
}

/*
 * @description		: 向设备写数据 
 * @param - filp 	: 设备文件，表示打开的文件描述符
 * @param - buf 	: 要写给设备写入的数据
 * @param - cnt 	: 要写入的数据长度
 * @param - offt 	: 相对于文件首地址的偏移
 * @return 			: 写入的字节数，如果为负值，表示写入失败
 */
static ssize_t chrdevbase_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt)
{
	int retvalue = 0;
	/* 接收用户空间传递给内核的数据并且打印出来 */
	retvalue = copy_from_user(writebuf, buf, cnt);
	if(retvalue == 0){
		printk(KERN_DEBUG  "kernel recevdata:%s\r\n", writebuf);
	}else{
		printk(KERN_DEBUG  "kernel recevdata failed!\r\n");
	}
	
	//printk("chrdevbase write!\r\n");
	return 0;
}

/*
 * @description		: 关闭/释放设备
 * @param - filp 	: 要关闭的设备文件(文件描述符)
 * @return 			: 0 成功;其他 失败
 */
static int chrdevbase_release(struct inode *inode, struct file *filp)
{
	//printk("chrdevbase release！\r\n");
	return 0;
}

/*
 * 设备操作函数结构体
 */
static struct file_operations chrdevbase_fops = {
	.owner = THIS_MODULE,	
	.open = chrdevbase_open,
	.read = chrdevbase_read,
	.write = chrdevbase_write,
	.release = chrdevbase_release,
};

/*
 * @description	: 驱动入口函数 
 * @param 		: 无
 * @return 		: 0 成功;其他 失败
 */
static int __init chrdevbase_init(void)
{
	int retvalue = 0;

	alloc_chrdev_region(&device, 0, MODULE_CNT, MODULE_NAME);
	major = MAJOR(device);
	minor = MINOR(device);
	PDEBUG("major = %d, minor = %d", major, minor);

	cdev.owner = THIS_MODULE;
	cdev_init(&cdev, &chrdevbase_fops);

	retvalue = cdev_add(&cdev, device, MODULE_CNT);
	if(!retvalue){
		PDEBUG("cdev_add success!\r\n");
	}else{
		PDEBUG("cdev_add error!\r\n");
	}
	class = class_create(THIS_MODULE, MODULE_NAME);
	if(IS_ERR(class)){
		return PTR_ERR(class);
	}

	device_ = device_create(class, NULL, device, NULL, MODULE_NAME);
	if (IS_ERR(device_)) {
		return PTR_ERR(device_);
		PDEBUG("device_create error!\r\n");
	}
	PDEBUG("device_create success!\r\n");


	// printk(  "[%s] chrdevbase init!\r\n", MODULE_NAME);
	PINFO("charDriver init!\r\n");
	return 0;
}

/*
 * @description	: 驱动出口函数
 * @param 		: 无
 * @return 		: 无
 */
static void __exit chrdevbase_exit(void)
{
	cdev_del(&cdev);
	/* 注销字符设备驱动 */
	unregister_chrdev_region(device, MODULE_CNT);
	PDEBUG("unregister_chrdev_region!\r\n");

	device_destroy(class, device);
	PDEBUG("device_destroy!\r\n");

	class_destroy(class);
	PDEBUG("class_destroy!\r\n");

	PINFO("charDriver exit!\r\n");

}

/* 
 * 将上面两个函数指定为驱动的入口和出口函数 
 */
module_init(chrdevbase_init);
module_exit(chrdevbase_exit);

/* 
 * LICENSE和作者信息
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jony");
/*  cat /sys/module/chrdevbase/version */
MODULE_VERSION("2.0"); 
MODULE_FIRMWARE("char_test_firmware");
MODULE_DESCRIPTION("char driver test!");
