#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/dma-mapping.h>

#include "dmaMmap.h"

#define DMA_TEST 

static int        dma_mask_bit = 64;
module_param(     dma_mask_bit, int, S_IRUGO);
MODULE_PARM_DESC( dma_mask_bit, "dma mask bit(default=32)");

typedef struct{
	char *buffer;
	char *bufferArea;
	uint8_t useCount;
	dev_t dev;
	int major;
	int minor;
	struct cdev cdev;
	struct class *class;
	struct device *device;
    struct device *dmaDevice;
    dma_addr_t physAddr;
    void *virAddr;
    unsigned int size;
    unsigned int allocSize;

}test_dev_t;

static test_dev_t testDev = {0};

ssize_t test_module_read(struct file *filp, char __user *buf, size_t cnt, loff_t * off)
{
    test_dev_t *dev = (test_dev_t *)filp->private_data;
    if(NULL == dev && NULL == dev->buffer)
    {
        PINFO("device is NULL!\n");
        return -ENXIO;
    }

    if(cnt >= MAX_BUFFER_SZIE)
    {
        PINFO("cnt need < %d\n", MAX_BUFFER_SZIE);
        return -EFAULT;
    }

    if(! access_ok(VERITY_WRITE, buf, cnt));
    {
        PINFO("error access user memory!\n");
        return -EFAULT;  
    }

    if(copy_to_user(buf, dev->buffer, cnt))
    {
        PINFO("copy to user error!\n");
        return -EFAULT;
    }

    return 0;
}

ssize_t test_module_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *off)
{
    test_dev_t *dev = (test_dev_t *)filp->private_data;
    if(NULL == dev && NULL == dev->buffer)
    {
        PINFO("device is NULL!\n");
        return -ENXIO;
    }

    if(cnt >= MAX_BUFFER_SZIE)
    {
        PINFO("cnt need < %d\n", MAX_BUFFER_SZIE);
        return -EFAULT;
    }

    if(! access_ok(VERITY_READ, buf, cnt));
    {
        PINFO("error access user memory!\n");
        return -EFAULT;  
    }

    if(copy_from_user(dev->buffer, buf, cnt))
    {
        PINFO("copy from user error!\n");
        return -EFAULT;
    }
    return 0;
}

#ifndef DMA_TEST
/**
 * @brief 共享内存映射
 * 
 * @param filp 
 * @param vmas 
 * @return int 
 */
int test_module_mmap(struct file *filp, struct vm_area_struct * vmas)
{
    int ret = 0;
    test_dev_t *dev = (test_dev_t *)filp->private_data;
    
    PDEBUG("test_module_mmap\n");

    if(NULL == dev && NULL == dev->bufferArea)
    {
        PINFO("device is NULL!\n");
        return -ENXIO;
    }

    PDEBUG("vmstart:%p, vmend:%p.\n", (void *)vmas->vm_start, (void *)vmas->vm_end);

    ret = remap_pfn_range(vmas, vmas->vm_start,     \
        virt_to_phys((void*)((unsigned long)dev->bufferArea)) >> PAGE_SHIFT,    \
        vmas->vm_end - vmas->vm_start, PAGE_SHARED);
    if(0 != ret)
    {
        PINFO("remap_pfn_range error [%d]!\n", ret);
        return -EAGAIN;
    }

    return 0;
}

#else
int test_module_mmap(struct file *filp, struct vm_area_struct * vmas)
{
    int ret = 0;
    test_dev_t *dev = (test_dev_t *)filp->private_data;
    
    PDEBUG("test_module_mmap\n");

    if(NULL == dev && NULL == dev->bufferArea)
    {
        PINFO("device is NULL!\n");
        return -ENXIO;
    }

    if(vmas->vm_pgoff + vma_pages(vmas) > dev->allocSize >> PAGE_SHIFT)
    {
        return -EINVAL;
    }

    return dma_mmap_coherent(dev->device, vmas, dev->virAddr, dev->physAddr, dev->allocSize);
}
#endif


int test_module_open(struct inode *inode, struct file *filp)
{   
    filp->private_data = &testDev;
    testDev.useCount ++;
    /* 默认 1M dma 空间*/
    testDev.size = (1 * 1024 * 1024);
    return 0;
}

int test_module_release(struct inode *inode, struct file *filp)
{
    testDev.useCount --;
    return 0;
}


static struct file_operations test_module_fops = {
    .owner = THIS_MODULE,	
    .open = test_module_open,
    .read = test_module_read,
    .write = test_module_write,
    .mmap = test_module_mmap,
    .release = test_module_release,
};

/**
 * @brief linux 字符设备初始化
 * 
 * @param device 
 * @return int 
 */
static int device_init(test_dev_t *device)
{
    int ret = 0;

    PDEBUG("device_deinit!\r\n");

    if(NULL == device)
    {
        PINFO("Dev is NULL!\n");
        return -ENOMEM;
    }

    /* 1. 注册设备号 */
    alloc_chrdev_region(&device->dev, 0, MODULE_CNT, MODULE_NAME);
    device->major = MAJOR(device->dev);
    device->minor = MINOR(device->dev);
	PDEBUG("device major = %d, minor = %d.\n", device->major, device->minor);

    /* 2.添加字符设备 */
    device->cdev.owner = THIS_MODULE;
    cdev_init(&device->cdev, &test_module_fops);
    ret = cdev_add(&device->cdev, device->dev, MODULE_CNT);
    if(0 != ret)
    {
        PINFO("cdev_add error %d.\n", ret);
        return -EAGAIN;
    }
    
    /* 3.创建设备类 */
    device->class = class_create(THIS_MODULE, MODULE_NAME);
    if(IS_ERR(device->class))
    {
        PINFO("class_create error.\n");
        return PTR_ERR(device->class);
    }

    /* 4. 创建设备 */
    device->device = device_create(device->class, NULL,     \
        device->dev, NULL, MODULE_NAME);
    if(IS_ERR(device->device))
    {
        PINFO("device_create error.\n");
        return PTR_ERR(device->device);
    }
    return 0;
}

/**
 * @brief linux 字符设备去初始化
 * 
 * @param device 
 */
static void device_deinit(test_dev_t *device)
{
    PDEBUG("device_deinit!\r\n");
    if(NULL == device)
    {
        PINFO("Dev is NULL!\n");
        return;
    }

    cdev_del(&device->cdev);
    unregister_chrdev_region(device->dev, MODULE_CNT);
    device_destroy(device->class, device->dev);
    class_destroy(device->class);
}

/**
 * @brief 设备资源初始化
 * 
 * @param device 
 * @return int 
 */
static int other_source_init(test_dev_t *device)
{
    unsigned long virtualBuffer = 0;
    int iRet = 0;

    PDEBUG("other_source_init!\r\n");
    if(NULL == device)
    {
        PINFO("Dev is NULL!\n");
        return -ENOMEM;
    }
    device->useCount = 0;

    /* 1. 内存初始化 */
    device->buffer = kmalloc(MAX_BUFFER_SZIE, GFP_KERNEL);
    if(NULL == device->buffer)
    {
        PINFO("kmalloc error!\n");
        return -ENOMEM;
    }
    PDEBUG("mamp buffer : %p\n", device->buffer);
    device->bufferArea = (char *)(((unsigned long)device->buffer + PAGE_SIZE - 1 ) & PAGE_SHIFT);
    for(virtualBuffer = (unsigned long)device->bufferArea;  \
        virtualBuffer < (unsigned long)device->bufferArea + MAX_BUFFER_SZIE;    \
        virtualBuffer += PAGE_SIZE)
    {
        /*  随着linux的长时间运行，空闲页面会越来越少，为了防止linux内核进入请求页面的僵局
            中，Linux内核采用页面回收算法(PFRA)从用户进程和内核高速缓存中回收内存页框，并根
            据需要把要回收页框的内容交换到磁盘上的交换区。调用该函数可以使页面不被交换。*/
        SetPageReserved(virt_to_page((char *)virtualBuffer));
        // PDEBUG("address: %p.\n", (char *)virtualBuffer);
    }

    memset(device->buffer, 0, MAX_BUFFER_SZIE);

    /*dma 初始化 */
PINFO("1---------------------------------------------------------");
    device->dmaDevice = get_device(device->device);
    if(NULL == device->dmaDevice)
    {
        PINFO("error get dma device.\n");
        return  -ENOMEM;
    }
    PINFO("2---------------------------------------------------------");
    if(NULL == device->dmaDevice->dma_mask)
    { 
        PINFO("3---------------------------------------------------------");  
        iRet = dma_coerce_mask_and_coherent(device->dmaDevice, DMA_BIT_MASK(dma_mask_bit));
        if(0 != iRet)
        {
            PINFO("dma_set_mask_and_coherent(DMA_BIT_MASK(%d)) failed. return=(%d)\n", dma_mask_bit, iRet);
            *device->dmaDevice->dma_mask         = DMA_BIT_MASK(dma_mask_bit);
            device->dmaDevice->coherent_dma_mask = DMA_BIT_MASK(dma_mask_bit);
        }
    }
PINFO("4---------------------------------------------------------");
    device->allocSize = ((device->size + ((1 << PAGE_SHIFT) - 1)) >> PAGE_SHIFT) << PAGE_SHIFT;
    device->virAddr = dma_alloc_coherent(device->dmaDevice, device->allocSize, &device->physAddr, GFP_KERNEL);
    if(IS_ERR_OR_NULL(device->virAddr))
    {
        iRet = PTR_ERR(device->virAddr);
        PINFO("dma alloc(size : %d) failed. return(%d).\n", device->allocSize, iRet);
        device->virAddr = NULL;
        return (0 == iRet) ? -ENOMEM : iRet;
    }
    PINFO("5---------------------------------------------------------");
    PDEBUG("dma malloc phys addr(%p), virtual addr(%p).\n", (void *)device->physAddr, device->virAddr);
    return 0; 
}

/**
 * @brief 设备资源去初始化
 * 
 * @param device 
 * @return void 
 */
static void other_source_deinit(test_dev_t *device)
{
    if(NULL == device)
    {
        PINFO("Dev is NULL!\n");
        return;
    }
    PDEBUG("other_source_deinit!\r\n");

    device->useCount = 0; 
    if(NULL != device->buffer)
        kfree(device->buffer);

    if(NULL != device->virAddr)
    {
        dma_free_coherent(device->device, device->allocSize, device->virAddr, device->physAddr);
        device->virAddr = NULL;
    }
}

/*
 * @description	: 驱动入口函数 
 * @param 		: 无
 * @return 		: 0 成功;其他 失败
 */
static int __init test_module_init(void)
{
    int ret = 0;

    PDEBUG("test Driver init!\r\n");

    ret = device_init(&testDev);
    if(0 != ret) return ret;

    ret = other_source_init(&testDev);
    if(0 != ret) return ret;

	return 0;
}

/*
 * @description	: 驱动出口函数
 * @param 		: 无
 * @return 		: 无
 */
static void __exit test_module_exit(void)
{
	PDEBUG("test Driver exit!\r\n");
    device_deinit(&testDev);
    other_source_deinit(&testDev);
}

/* 
 * 将上面两个函数指定为驱动的入口和出口函数 
 */
module_init(test_module_init);
module_exit(test_module_exit);

/* 
 * LICENSE和作者信息
 */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jony");
MODULE_VERSION("1.0"); 
MODULE_FIRMWARE("dma mmap");
MODULE_DESCRIPTION("dmp mmap test!");