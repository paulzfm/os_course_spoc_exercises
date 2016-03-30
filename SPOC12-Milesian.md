以lab8_result的代码为例

ucore的sleep系统调用接口在kern/syscall/syscall.c中

```
static int
sys_sleep(uint32_t arg[]) {
    unsigned int time = (unsigned int)arg[0];
    return do_sleep(time);
}

```

这一接口主要是提取出sleep的时间，并调用do_sleep接口
do_sleep在kern/process/proc.c中

```
int
do_sleep(unsigned int time) {
    if (time == 0) {
        return 0;
    }
    bool intr_flag;
    local_intr_save(intr_flag);
    timer_t __timer, *timer = timer_init(&__timer, current, time);
    current->state = PROC_SLEEPING;
    current->wait_state = WT_TIMER;
    add_timer(timer);
    local_intr_restore(intr_flag);

    schedule();

    del_timer(timer);
    return 0;
}


```

其中timer设置了计时器，sleep对应的等待队列在current中，add_timer和del_timer是将计时器加入／退出队列，唤醒操作应该是在schedule中

schedule函数在kern/shedule/sched.c中

```
void
schedule(void) {
    bool intr_flag;
    struct proc_struct *next;
    local_intr_save(intr_flag);
    {
        current->need_resched = 0;
        if (current->state == PROC_RUNNABLE) {
            sched_class_enqueue(current);
        }
        if ((next = sched_class_pick_next()) != NULL) {
            sched_class_dequeue(next);
        }
        if (next == NULL) {
            next = idleproc;
        }
        next->runs ++;
        if (next != current) {
            proc_run(next);
        }
    }
    local_intr_restore(intr_flag);
}
```

这一段做的就是先将当前运行的进程加入队列中变为暂停，等待队列中找出来一个进程变为运行状态
