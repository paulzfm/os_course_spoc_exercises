esienberg算法模拟

设计方案

给定线程数量n和运行次序表长度m，接下来给出m个0到n-1之间的数，表示当前运行哪个线程的指令
然后将要共享的程序代码设定为输出一句话：RUNNING PROCESS pid

同时进入进程和退出进程都有ENTER PROCESS pid 和 EXIT PROCESS pid

pid这里是指线程编号

如果任何输入给出的输出中都可以保证连续三句话（enter，running，exit）中的pid数字相同，就说明是正确的
