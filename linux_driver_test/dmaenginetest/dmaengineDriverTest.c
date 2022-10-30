#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/miscdevice.h>
#include <linux/irq.h>
#include <linux/delay.h>
 
#include <linux/device.h>
#include <linux/string.h>
#include <linux/errno.h>
 
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/dmaengine.h>
#include <linux/dma-mapping.h>
 
#include <asm/io.h>
#include <asm/uaccess.h>

#define BUF_SIZE        4*1024*1024
#define MEM_CPY_NO_DMA	_IOW('L', 0x1210, int)
#define MEM_CPY_DMA	_IOW('L', 0x1211, int)
/*环形dma拷贝*/
#define MEM_CYC_CPY_DMA	_IOW('L', 0x1212, int)
 
char *src = NULL;
char *dst = NULL;
dma_addr_t dma_src;
dma_addr_t dma_dst;
enum dma_ctrl_flags flags;
dma_cookie_t cookie;
static struct dma_chan *chan = NULL;
struct dma_device *dev = NULL;
struct dma_async_tx_descriptor *tx = NULL;
 
void dma_callback_func(void* args)
{
    if(0 == memcmp(src, dst, BUF_SIZE))
        printk("MEM_CPY_DMA OK\n");
    else
        printk("MEM_CPY_DMA ERROR\n");
}
 
int 
dma_open(struct inode *inode, struct file *filp)
{
    return 0;
}
 
long 
dma_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int i = 0;
	ktime_t ktime;
	s64 runtime = 0;

    memset(src, 0xAA, BUF_SIZE);
    memset(dst, 0xBB, BUF_SIZE);

    switch (cmd)
    {
        case MEM_CPY_NO_DMA:
            for(i = 0; i < BUF_SIZE; i++)
                dst[i] = src[i];
 
            if(0 == memcmp(src, dst, BUF_SIZE))
                printk("MEM_CPY_NO_DMA OK\n");
            else
                printk("MEM_CPY_DMA ERROR\n");
 
            break;
 
        case MEM_CPY_DMA:
	        flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	        dev = chan->device;
            tx = dev->device_prep_dma_memcpy(chan, dma_dst, dma_src, BUF_SIZE, flags);
            if(!tx)
                printk("%s failed to prepare DMA memcpy\n", __func__);
 
            tx->callback = dma_callback_func;      // set call back function
            tx->callback_param = NULL;
            cookie = tx->tx_submit(tx);   // submit the desc
            if(dma_submit_error(cookie)) {
                printk("failed to do DMA tx_submit");
            }
 
            dma_async_issue_pending(chan);         // begin dma transfer
            break;

        case MEM_CYC_CPY_DMA:
            break;
 
        default:
            break;
    }
    return 0;
}
 
int 
dma_release(struct inode *inode, struct file *filp)
{
    return 0;
}
 
const struct file_operations dma_fops = {
    .open   = dma_open,
    .unlocked_ioctl = dma_ioctl,
    .release = dma_release,
};
 
struct miscdevice dma_misc = {
    .minor  = MISC_DYNAMIC_MINOR,
    .name   = "dma_m2m_test",
    .fops   = &dma_fops,
};

static void __exit dma_exit(void)
{
    dma_release_channel(chan);

    dma_free_coherent(NULL, BUF_SIZE, src, dma_src);
    dma_free_coherent(NULL, BUF_SIZE, dst, dma_dst);
 
    misc_deregister(&dma_misc);
}

static int __init dma_init(void)
{
    dma_cap_mask_t mask;

    int ret = misc_register(&dma_misc);
    if(ret < 0){
        printk("%s misc register failed !\n", __func__);
        return -EINVAL;
    }

    /* 
        一致性DMA: 物理地址连续，内存不可cache, 可认为DMA和CPU之间看到的物理内存是一致的。
        场景：CPU和DMA需要频繁的操作一块内存区域

        dma_alloc_writecombine 只禁止cache缓冲,保持写缓冲区,也就是对注册的物理区写入数据,也会更新到对应的虚拟缓存区上
     */
    src = dma_alloc_coherent(NULL, BUF_SIZE, &dma_src, GFP_KERNEL);
    printk("src = 0x%x, dma_src = 0x%x\n", src, dma_src);
 
    dst = dma_alloc_coherent(NULL, BUF_SIZE, &dma_dst, GFP_KERNEL);
    printk("dst = 0x%x, dma_src = 0x%x\n", dst, dma_dst);
    
    dma_cap_zero(mask); 
    //dma_cap_set(DMA_MEMCPY, mask);                          // direction: m2m
    dma_cap_set(DMA_SLAVE, mask);                          // direction: m2m
    
	chan = dma_request_channel(mask, NULL, NULL);  // request to dma channel
    if(NULL == chan)
	printk("chan request failed !\n");
    else
	printk("chan OK!\n");

    return 0;
}
 
module_init(dma_init);
module_exit(dma_exit);
 
MODULE_LICENSE("GPL");