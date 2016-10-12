
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "proc/readproc.h"

/*
    reference: http://www.linuxhowtos.org/manpages/5/proc.htm

    /proc/stat
    kernel/system statistics. Varies with architecture. Common entries include:
    cpu 3357 0 4313 1362393
    The amount of time, measured in units of USER_HZ (1/100ths of a second on most architectures, use sysconf(_SC_CLK_TCK) to obtain the right value), that the system spent in various states:
    user
    (1) Time spent in user mode.
    nice
    (2) Time spent in user mode with low priority (nice).
    system
    (3) Time spent in system mode.
    idle
    (4) Time spent in the idle task. This value should be USER_HZ times the second entry in the /proc/uptime pseudo-file.
    iowait (since Linux 2.5.41)
    (5) Time waiting for I/O to complete.
    irq (since Linux 2.6.0-test4)
    (6) Time servicing interrupts.
    softirq (since Linux 2.6.0-test4)
    (7) Time servicing softirqs.
    steal (since Linux 2.6.11)
    (8) Stolen time, which is the time spent in other operating systems when running in a virtualized environment
    guest (since Linux 2.6.24)
    (9) Time spent running a virtual CPU for guest operating systems under the control of the Linux kernel.
    guest_nice (since Linux 2.6.33)
    (10) Time spent running a niced guest (virtual CPU for guest operating systems under the control of the Linux kernel).
*/
struct cpu_usage_t
{
    unsigned long long user;
    unsigned long long nice;
    unsigned long long sys;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
    unsigned long long guest;
    unsigned long long guest_nice;
};

//reference: procps-ng-3.3.11 sysinfo.c "void getstat(...)"
//精简了大部分不需要的内容
//return 0 if succeed, otherwise failed.
#define BUFFSIZE (64*1024)
int get_cpu_stat(struct cpu_usage_t* cu)
{
    int ret = -1;
    memset(cu, 0, sizeof(struct cpu_usage_t));
    
    int fd = open("/proc/stat", O_RDONLY, 0);
    if(fd == -1){
        printf("open /proc/stat failed, errno %d.\n", errno);
        return ret;
    }
  
    char buff[BUFFSIZE] = {0};  /* ensure null termination in buffer */
    //buff[BUFFSIZE-1] = 0;  /* ensure null termination in buffer */
    read(fd,buff,BUFFSIZE-1);
    
    const char* b = strstr(buff, "cpu ");
    if(b){ 
        //printf("%s\n", b);
        sscanf(b,  "cpu  %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu", \
            &cu->user, &cu->nice, &cu->sys, &cu->idle, &cu->iowait, &cu->irq, &cu->softirq, &cu->steal);
        ret = 0;
    }
    close(fd);
    return ret;
}

void refresh_cpu()
{
    struct cpu_usage_t last_cu;
    get_cpu_stat(&last_cu);
    printf("cpu user:%llu nice:%llu sys:%llu idle:%llu iowait:%llu irq:%llu softirq:%llu steal:%llu guest:%llu\n", \
        last_cu.user, last_cu.nice, last_cu.sys, last_cu.idle, last_cu.iowait, last_cu.irq, last_cu.softirq, last_cu.steal, last_cu.guest);
    while (1)
    {
        sleep(1);   //sample interval. could adjust
        struct cpu_usage_t new_cu;
        get_cpu_stat(&new_cu);
        
        unsigned long long last_total_cpu = last_cu.user + last_cu.nice + last_cu.sys + last_cu.idle + last_cu.iowait \
            + last_cu.irq + last_cu.softirq + last_cu.steal + last_cu.guest;
        unsigned long long new_total_cpu = new_cu.user + new_cu.nice + new_cu.sys + new_cu.idle + new_cu.iowait \
            + new_cu.irq + new_cu.softirq + new_cu.steal + new_cu.guest;
        unsigned long long pcpu = 100 * ((new_total_cpu - last_total_cpu) - (new_cu.idle - last_cu.idle)) / (new_total_cpu - last_total_cpu);
        printf("cpu usage:%f%%\n", (double)pcpu);
        
        memcpy(&last_cu, &new_cu, sizeof(struct cpu_usage_t));
    }
    
}

void refresh_proc_info(int want_threads)
{
    int openproc_flags = PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLCOM;
    if (want_threads){
        openproc_flags |= PROC_LOOSE_TASKS;
    }
    //openproc_flags |= PROC_FILL_LXC; //what's the meaning of LXC???
    
    //NOTE:若希望仅关注某几个进程，应在此接口中传入pid的list进行预过滤，而不是一次全搞出来再过滤 
    PROCTAB* new_proc_tab = openproc(openproc_flags);
    if (NULL == new_proc_tab){
        printf("openproc failed, errno %d.\n", errno);
        return;
    }
    
    //NOTE: 虽然readproc/readtask接口也可以传入内存，以避免内部分配，但实际上如果需要cmdline参数的话，其始终是
    //      内部分配的，所以还是应由readproc直接全部分配后再调用freeproc即可。否则预分配内存了传入，而又需要cmdline的话，
    //      会造成内存泄露
    //reference: http://stackoverflow.com/questions/17359517/how-can-i-properly-free-memory-when-using-libproc
    //          http://www.cnblogs.com/westfly/p/4230956.html
    
    static proc_t buf, buf2; 
    while (readproc(new_proc_tab, &buf))
    {
            printf("pid:%5d(tgid:%d) cmd:%s cmdline:%s threads:%d state:%c\n", \
                buf.tid, buf.tgid, buf.cmd, ((NULL == buf.cmdline) || (NULL == *(buf.cmdline))) ? "" : *(buf.cmdline), buf.nlwp, buf.state);
            printf("         stat--->{utime:%llu stime:%llu cutime:%llu cstime:%llu vsize:%lukb start_code:0x%x end_code:0x%x start_stack:0x%x}\n", \
                buf.utime, buf.stime, buf.cutime, buf.cstime, buf.vsize, buf.start_code, buf.end_code, buf.start_stack);
            printf("         stat--->{min_flt:%u, maj_flt:%u, cmin_flt:%u, cmaj_flt:%u}\n", \
                buf.min_flt, buf.maj_flt, buf.cmin_flt, buf.cmaj_flt);
            printf("         statm-->{size:%ld, resident:%ld, share:%ld, trs:%ld, lrs:%ld, drs:%ld, dt:%ld}\n", \
                buf.size, buf.resident, buf.share, buf.trs, buf.lrs, buf.drs, buf.dt);
            printf("         status->{vm_size(TOP_VIRT):%ukb, vm_lock:%ukb, vm_rss(TOP_RES):%ukb, vm_data:%ukb, vm_stack:%ukb, vm_swap:%ukb, vm_exe:%ukb, vm_lib:%ukb}\n", \
                buf.vm_size, buf.vm_lock, buf.vm_rss, buf.vm_data, buf.vm_stack, buf.vm_swap, buf.vm_exe, buf.vm_lib);

        if (want_threads){
            while (readtask(new_proc_tab, &buf, &buf2))
            {
                //标示线程的一些信息
                printf("tid:%5d(tgid/pid:%d) cmd:%s state:%c utime:%llu stime:%llu\n", \
                    buf2.tid, buf2.tgid, buf2.cmd, buf2.state, buf2.utime, buf2.stime);                
            }
        }
        
        
    }
    closeproc(new_proc_tab);
    
}

void refresh_proc_info_tab()
{
    int openproc_flags = PROC_FILLMEM | PROC_FILLSTAT | PROC_LOOSE_TASKS;   
    
    //NOTE：readproctab的内存只能通过exit进行释放，故这个接口无法在需要循环调用的程序中使用。
    proc_t ** pt = readproctab(openproc_flags);
    if (NULL == pt){
        printf("readproctab failed, errno %d.\n", errno);
        return;
    }
    
    proc_t *t = NULL;
    int i = 0;
    while (t = pt[i++])
    {
        printf("tid:%d(ppid:%d pid:%d) cmd:%s state:%c utime:%llu stime:%llu cutime:%llu cstime:%llu \n", \
            t->tid, t->ppid, t->tgid, t->cmd, t->state, t->utime, t->stime, t->cutime, t->cstime);
    }
}



int main()
{
    refresh_cpu();
    /* while (1)
    {
        refresh_proc_info(0);
        printf("\n\n\n");
        refresh_proc_info(1);
        //refresh_proc_info_tab();
        
        sleep(1);
    } */
        
    
    return 0;
}

