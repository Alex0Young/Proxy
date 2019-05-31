/*lkm.c*/
 

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
 
static char *file_path="/work/lkm/lkm-init";
module_param(file_path,charp,S_IRUGO);
 
static int file_num=8;
module_param(file_num,int,S_IRUGO);
 
static __init int  lkm_init(void)
{
   printk("sq:module loaded");
   printk("file_path:%s\n",file_path);
   printk("file_num:%d\n",file_num);
   return 0;
}
 
 
static __exit void  lkm_exit(void)
{
   printk("sq:module removed");
}
 
module_init(lkm_init);
module_exit(lkm_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SQ");
MODULE_VERSION("1.0");

