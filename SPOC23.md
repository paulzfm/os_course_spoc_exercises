在ucore里面，没有直接给出磁盘文件复制的接口（在每一层都没有）
所以我们认为，进行磁盘文件复制需要编写一个用户态程序去完成。

而磁盘文件复制在用户态需要完成以下操作：

打开源文件

读取源文件

打开目标文件

写入目标文件

即进行两次open和一次read和一次write（这里不在用户态考虑分段读写的问题）

根据上一次SPOC中我们的答案，磁盘文件复制的流程大概是这样：

用户态：
  打开：open() -> sys_open() -> syscall(SYS_OPEN, ……)
  读写：read/write()-> sys_read/write() -> syscall(SYS_READ/WRITE, ……)

上面的过程主要还是做一个从用户态到内核态的切换(利用中断处理例程)

内核态：
  打开：sys_open()->sysfile_open()->file_open()；
  读写：sys_read/write() -> sysfile_read/write()-> file_read/write()；

抽象层：
  打开：file_open() -> vfs_open()；
  读写：file_read/write() ->　vfs_read/write()；

SFS层：
  打开：sfs_opendir()->sfs_openfile()->sfs_load_inode()；
  读写：sfs_load_inode->sfs_io()->sfs_r/wbuf->sfs_rwblock_nolock;
  分三种情况进行读写：
    读写起始位置所在的block
    读写起始位置到终止位置中间的block
    读写终止位置所在block
  注意到后面就没有open的事情了。open只是做一个磁盘映射

I/O层：
  dop_io();disk0_io() :检验参数 -> disk0_read_blks_nolock()
  调用驱动函数，连续读取若干个block

驱动层：
  ide_read_secs() :读取扇区；
