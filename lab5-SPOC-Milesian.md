以lab5_result的代码为例

在__panic函数第一行添加print_stackframe()的调用，前后加上标记

然后在trap_dispatch函数的第一行，先判定其是否在用户态（调用trap_in_kernel函数），然后调用panic

执行make qemu可得如下输出

```
check_swap() succeeded!
++ setup timer interrupts
kernel_execve: pid = 2, name = "exit".
now in panic:
ebp:0xc03adf18 eip:0xc0101f62 args:0xc010d89e 0x0000000a 0xc03adf90 0x00000002
    kern/debug/kdebug.c:350: print_stackframe+21
ebp:0xc03adf48 eip:0xc010226f args:0xc010dc60 0x000000c4 0xc010dc88 0x00000000
    kern/debug/panic.c:15: __panic+22
ebp:0xc03adf78 eip:0xc0103c5b args:0xc03adfb4 0x00000000 0x00800020 0x0000001b
    kern/trap/trap.c:196: trap_dispatch+48
ebp:0xc03adfa8 eip:0xc0103ef6 args:0xc03adfb4 0x00000049 0x00000000 0xaffffe98
    kern/trap/trap.c:291: trap+74
ebp:0xaffffe98 eip:0xc0103f4b args:0x0000001e 0x00000049 0xaffffec8 0x008000d6
    kern/trap/trapentry.S:24: <unknown>+0
ebp:0xaffffea8 eip:0x00800290 args:0x00000049 0x00000000 0x00000000 0x00000000
    user/libs/syscall.c:65: sys_putc+24
ebp:0xaffffec8 eip:0x008000d6 args:0x00000049 0xafffff3c 0x00000000 0x00000000
    user/libs/stdio.c:11: cputch+16
ebp:0xafffff18 eip:0x0080056b args:0x008000c5 0xafffff3c 0x008013e1 0xafffff84
    libs/printfmt.c:131: vprintfmt+33
ebp:0xafffff48 eip:0x00800113 args:0x008013e0 0xafffff84 0x00000000 0x00000000
    user/libs/stdio.c:27: vcprintf+45
ebp:0xafffff78 eip:0x00800136 args:0x008013e0 0x00000000 0x00000000 0x00000000
    user/libs/stdio.c:42: cprintf+29
ebp:0xafffffa8 eip:0x00800fa6 args:0x00000000 0x00000000 0x00000000 0x00000000
    user/exit.c:9: main+20
ebp:0xafffffd8 eip:0x0080034d args:0x00000000 0x00000000 0x00000000 0x00000000
    user/libs/umain.c:7: umain+10
panic stack end
```

可以看出，trap之前的堆栈都是来自于用户态，而用户态触发中断之后会进入内核态执行panic
