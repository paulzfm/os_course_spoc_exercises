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
(1 bytes, @0) (1 bytes, @1023)
(3 bytes, @0) (1 bytes, @1023)
(7 bytes, @0) (1 bytes, @1023)
(15 bytes, @0) (1 bytes, @1023)
(31 bytes, @0) (1 bytes, @1023)
(63 bytes, @0) (1 bytes, @1023)
(127 bytes, @0) (1 bytes, @1023)
(255 bytes, @0) (1 bytes, @1023)
(511 bytes, @0) (1 bytes, @1023)
Segmentation fault: 11

现在这个样例最后有个segmentation fault是什么情况？目测我哪里没处理好
