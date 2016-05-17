修改了user文件夹下的hello.c文件，令其进行一次打开文件和读文件操作

```
#include <stdio.h>
#include <ulib.h>

int
main(void) {
    cprintf("Hello world!!.\n");
    cprintf("I am process %d.\n", getpid());

    int fdd = open("/Home/test.txt",O_RDWR);
    char buffer[1020];
    int ret = read(fd, buffer, 100);

    cprintf("hello pass.\n");
    return 0;
}


```

由于我不太确定执行的相对路径，因此这里采用绝对路径方式进行。

同样在kern/driver/ide.c文件中修改了函数ide_read_secs:

```
int
ide_read_secs(unsigned short ideno, uint32_t secno, void *dst, size_t nsecs) {
    print_stackframe();
    assert(nsecs <= MAX_NSECS && VALID_IDE(ideno));
    assert(secno < MAX_DISK_NSECS && secno + nsecs <= MAX_DISK_NSECS);
    unsigned short iobase = IO_BASE(ideno), ioctrl = IO_CTRL(ideno);

    ide_wait_ready(iobase, 0);

    // generate interrupt
    outb(ioctrl + ISA_CTRL, 0);
    outb(iobase + ISA_SECCNT, nsecs);
    outb(iobase + ISA_SECTOR, secno & 0xFF);
    outb(iobase + ISA_CYL_LO, (secno >> 8) & 0xFF);
    outb(iobase + ISA_CYL_HI, (secno >> 16) & 0xFF);
    outb(iobase + ISA_SDH, 0xE0 | ((ideno & 1) << 4) | ((secno >> 24) & 0xF));
    outb(iobase + ISA_COMMAND, IDE_CMD_READ);

    int ret = 0;
    for (; nsecs > 0; nsecs --, dst += SECTSIZE) {
        if ((ret = ide_wait_ready(iobase, 1)) != 0) {
            goto out;
        }
        insl(iobase, dst, SECTSIZE / sizeof(uint32_t));
    }

out:
    return ret;
}

```


之后得到部分运行结果如下：

```
ebp:0xc0349bf8 eip:0xc0100bf0 args:0xc0349c9c 0x00001000 0xc0349c48 0xc0109c72
    kern/debug/kdebug.c:351: print_stackframe+21
ebp:0xc0349c58 eip:0xc0101ccd args:0x00000002 0x000002f8 0xc0340000 0x00000008
    kern/driver/ide.c:159: ide_read_secs+19
ebp:0xc0349c98 eip:0xc0110c82 args:0x0000005f 0x00000001 0x80000000 0xc0347008
    kern/fs/devs/dev_disk0.c:44: disk0_read_blks_nolock+58
ebp:0xc0349ce8 eip:0xc0110ea0 args:0xc03362b8 0xc0349d0c 0x00000000 0x0005f000
    kern/fs/devs/dev_disk0.c:96: disk0_io+334
ebp:0xc0349d28 eip:0xc0114651 args:0xc0336340 0xc0344000 0x0000005f 0x00000000
    kern/fs/sfs/sfs_io.c:24: sfs_rwblock_nolock+137
ebp:0xc0349d68 eip:0xc01147a4 args:0xc0336340 0xc034b000 0x0000001b 0x0000005f
    kern/fs/sfs/sfs_io.c:90: sfs_rbuf+126
ebp:0xc0349dc8 eip:0xc0113595 args:0xc0336340 0xc0336730 0xc034b000 0x00000000
    kern/fs/sfs/sfs_inode.c:631: sfs_io_nolock+753
ebp:0xc0349e18 eip:0xc01136c2 args:0xc0336730 0xc0349e5c 0x00000000 0x00000001
    kern/fs/sfs/sfs_inode.c:657: sfs_io+210
ebp:0xc0349e38 eip:0xc011370e args:0xc0336730 0xc0349e5c 0x00000064 0x00000000
    kern/fs/sfs/sfs_inode.c:669: sfs_read+31
ebp:0xc0349e88 eip:0xc010aa5b args:0x00000002 0xc034b000 0x00000064 0xc0349eac
    kern/fs/file.c:230: file_read+238
ebp:0xc0349ec8 eip:0xc010b70d args:0x00000002 0xafffff24 0x00000064 0xc0349fdc
    kern/fs/sysfile.c:80: sysfile_read+176
ebp:0xc0349ef8 eip:0xc010eca5 args:0xc0349f24 0x0000000a 0xc0349f48 0x00000000
    kern/syscall/syscall.c:109: sys_read+58
ebp:0xc0349f48 eip:0xc010ee66 args:0x00000001 0xc0100328 0xc0349fbc 0xc0102c81
    kern/syscall/syscall.c:201: syscall+117
ebp:0xc0349f78 eip:0xc0102a4c args:0xc0349fb4 0x00000000 0x00000000 0x00000023
    kern/trap/trap.c:217: trap_dispatch+299
ebp:0xc0349fa8 eip:0xc0102c2c args:0xc0349fb4 0xafffff08 0x00800144 0xaffffed0
    kern/trap/trap.c:307: trap+74
ebp:0xaffffed0 eip:0xc0102c81 args:0x00000066 0x00000002 0xafffff24 0x00000064
    kern/trap/trapentry.S:24: <unknown>+0
ebp:0xaffffee8 eip:0x008006de args:0x00000002 0xafffff24 0x00000064 0x0000000c
    user/libs/syscall.c:109: sys_read+38
ebp:0xafffff08 eip:0x00800144 args:0x00000002 0xafffff24 0x00000064 0x00050000
    user/libs/file.c:21: read+30
ebp:0xafffff92 eip:0x00801835 args:0x00000001 0xaffffff6 0x00000001 0x00000000
    user/hello.c:14: main+105
ebp:0xafffffc2 eip:0x00800ada args:0x00000001 0xaffffff6 0x00000000 0x00000000
    user/libs/umain.c:31: umain+167

```

这里从栈底到栈顶依次是

```
umain.c
hello.c
file.c
syscall.c
trapentry.S
trap.c
syscall.c
sysfile.c
file.c
sfs_inode.c
dev_disk0.c
ide.c
kdebug.c
```

由此可以知道读文件的大致过程：

首先，操作系统执行用户态程序hello.c，hello.c执行file.c中的read函数
这个read函数通过系统调用接口sys_read,进而形成一个syscall
之后syscall发送了一个软中断进入内核，trap又调用内核态的syscall，进而进行sys_read

ps:实际上上面的过程主要还是一个从用户态到内核态的切换

然后它又执行了以下过程，首先在sysfile_read()中检查参数的合法性，即buffer和100的合法性。
接着file_read在进程列表里寻找指定的文件（之前open的），如果找到了，就检查它的读写权限。
调用vop_read函数，做为VFS的read操作的统一接口，向下接入SFS

到了SFS层，进入了sfs_read()这一层（读入统一接口）
接向sfs_io_nolock函数，根据读写文件（这里是读）的起始和结束位置会分三种情况进行读写：
读写起始位置所在的block
读写起始位置到终止位置中间的block
读写终止位置所在block

之所以分这三个部分，是因为起始为止和终止位置是可能会读写不完整的block，这是一种“分块”处理的思想，加速中间所有block的读写

这些都会调用到dop_io函数

到了I/O通用接口这边，首先disk0_io检查参数是否合法

然后disk0_read_blks_nolock会调用驱动函数，连续读取若干个block

最后在设备驱动层，ide_read_secs会读取硬盘的扇区。
