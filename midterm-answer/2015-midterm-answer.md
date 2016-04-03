# 2015 操作系统期中考试参考答案

WARNING: 仅供参考！

### 第一题

4次。由于可以不对齐访问，那么在访问某个数据时，就可能该数据横跨两个页表的情况，即最多缺失2次。而指令和数据访问都有可能缺失，故一共最多缺失4次。

### 第二题

### 第三题

(1)

- Clock：把页组织成环形链表，从指针当前位置遍历，当某页未被访问（访问位为0）时，置换该页；否则，置该页访问位为0，继续查找。
- FIFO：把页组织成队列，替换掉最先进入队列的页（对首），新的页加在队尾。

(2)

(3) Belady现象：分配的物理页面数增加，缺页次数反而升高的异常现象。FIFO和Clock都存在。例子请参见[Lecture 9.4](http://166.111.68.197:11123/oscourse/OS2015autumn/lecture09?action=AttachFile&do=get&target=20151117-lecture-09-4.mp4)。

### 第四题

(1) 切换前的进程`prev`

(2) 在刚进入`switch_to`时，`prev`的上下文起始地址为`esp + 4`，`next`的上下文起始地址为`esp + 8`。

(3) `lcr3(next->cr3);`

(4) `load_esp0(next->kstack + KSTACKSIZE);`

### 第五题

(1) 和普通二级页表的工作原理一致。

(2) 8KB虚拟地址：13位。页大小32B：5位。一级页表索引和二级页表索引各4位。

(2.1)

```c
pde_index = (vaddr >> 9);
```

(2.2)

```c
pte_index = (vaddr >> 5) & 0xF;
```

(2.3)

```c
pde = page[pdbr + pde_index];
if (pde >> 7 == 0) // throw page fault
pte_start = (pde & 0x7F) >> 5;
pte = page[pte_start + pte_index];
paddr = (pte << 5) + (vaddr & 0x1F);
```

(2.4)

### 第六题

```
Parent Process: Global variable: 21 Stack variable: 19
Child Process:  Global variable: 22 Stack variable: 18
```

程序见：
