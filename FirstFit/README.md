将main.c注释掉之后使用tests.c得到了如下的结果：
(1024 bytes, @0)
(1023 bytes, @1)
(1021 bytes, @3)
(1017 bytes, @7)
(1009 bytes, @15)
(993 bytes, @31)
(961 bytes, @63)
(897 bytes, @127)
(769 bytes, @255)
(513 bytes, @511)
(1 bytes, @1023)
(1 bytes, @1023) (1 bytes, @0)
(1 bytes, @1023) (2 bytes, @1) (1 bytes, @0)
(1 bytes, @1023) (4 bytes, @3) (2 bytes, @1) (1 bytes, @0)
(1 bytes, @1023) (8 bytes, @7) (4 bytes, @3) (2 bytes, @1) (1 bytes, @0)
(1 bytes, @1023) (16 bytes, @15) (8 bytes, @7) (4 bytes, @3) (2 bytes, @1) (1 bytes, @0)
(1 bytes, @1023) (32 bytes, @31) (16 bytes, @15) (8 bytes, @7) (4 bytes, @3) (2 bytes, @1) (1 bytes, @0)
(1 bytes, @1023) (64 bytes, @63) (32 bytes, @31) (16 bytes, @15) (8 bytes, @7) (4 bytes, @3) (2 bytes, @1) (1 bytes, @0)
(1 bytes, @1023) (128 bytes, @127) (64 bytes, @63) (32 bytes, @31) (16 bytes, @15) (8 bytes, @7) (4 bytes, @3) (2 bytes, @1) (1 bytes, @0)
(1 bytes, @1023) (256 bytes, @255) (128 bytes, @127) (64 bytes, @63) (32 bytes, @31) (16 bytes, @15) (8 bytes, @7) (4 bytes, @3) (2 bytes, @1) (1 bytes, @0)
(1 bytes, @1023) (512 bytes, @511) (256 bytes, @255) (128 bytes, @127) (64 bytes, @63) (32 bytes, @31) (16 bytes, @15) (8 bytes, @7) (4 bytes, @3) (2 bytes, @1) (1 bytes, @0)


首先第一位是该块剩余的字节数。第二个数字意思是用掉了多少
PS:但是这个输出为什么是好几块好几块的？是我对算法理解错了还是对输出理解错了？
我大概的做法就是做了一个循环，把2的次方依次放进去
