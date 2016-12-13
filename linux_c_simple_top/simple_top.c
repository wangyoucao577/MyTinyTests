
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include "proc/readproc.h"

#define VNAME(name) (#name)

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

//Reference: http://man7.org/linux/man-pages/man5/proc.5.html
//NOTE: Capture a process info from /proc/[pid]/stat
struct process_usage_t
{
    int pid;
    char comm[256];
    char state;
    int ppid;
    int pgrp;
    int session;
    int tty_nr;
    int tpgid;
    unsigned int flags;
    unsigned long minflt;
    unsigned long cminflt;
    unsigned long majflt;
    unsigned long cmajflt;
    unsigned long utime;
    unsigned long stime;
    long int cutime;
    long int cstime;
    long int priority;
    long int nice;
    long int num_threads;
    long int itreadvalue;
    unsigned long long starttime;
    //TODO: 补齐...
};

// get_proc_info via libprocps.so (top from procps-ng)
//   pid[in]: 0 if all processes, otherwise the indicated process
//   want_threads[in]: 0 if don't want threads info, 1 if want
//   b_print[in]: 0 if not want to printf, 1 if to printf
//   proc_buf[in/out]: input memory, output indicated process's info, for process
//   proc_buf_len[in/out]: how many proc_t bytes can be use, for process
//TODO: add output for threads
void get_proc_info(int pid, int want_threads, int b_print, proc_t* proc_buf, int * proc_buf_len)
{
    //printf("%d %d %d %p %p(value:%d)\n", pid, want_threads, b_print, proc_buf, proc_buf_len, NULL == proc_buf_len ? 0 : *proc_buf_len);
    
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
    
    int stored_procs = 0;
    proc_t buf, buf2; 
    memset(&buf, 0, sizeof(proc_t));
    memset(&buf2, 0, sizeof(proc_t));
    
    while (readproc(new_proc_tab, &buf))
    {
        if (0 != pid && buf.tid != pid){
            //不关心的pid, 忽略掉
            continue;
        }
        
        if (want_threads){
            while (readtask(new_proc_tab, &buf, &buf2))
            {
                //标示线程的一些信息. 主要是cpu时间，可区分usr和sys层的占用
                if (b_print){
                    printf("tid:%5d(tgid/pid:%d) cmd:%s state:%c utime:%llu stime:%llu\n", \
                        buf2.tid, buf2.tgid, buf2.cmd, buf2.state, buf2.utime, buf2.stime);                
                }
            }
        }
        else{
            if (NULL != proc_buf && NULL != proc_buf_len){
                
                //保存进程的proc信息以输出
                if (stored_procs < *proc_buf_len){
                    memcpy(proc_buf + sizeof(proc_t) * stored_procs, &buf, sizeof(proc_t));
                    ++stored_procs;
                }
            }
            if (b_print){
                printf("pid:%5d(tgid:%d) cmd:%s cmdline:%s threads:%d state:%c\n", \
                    buf.tid, buf.tgid, buf.cmd, ((NULL == buf.cmdline) || (NULL == *(buf.cmdline))) ? "" : *(buf.cmdline), buf.nlwp, buf.state);
                printf("         stat--->{utime:%llu stime:%llu cutime:%llu cstime:%llu vsize:%lukb start_code:0x%x end_code:0x%x start_stack:0x%x}\n", \
                    buf.utime, buf.stime, buf.cutime, buf.cstime, buf.vsize, buf.start_code, buf.end_code, buf.start_stack);
                printf("         stat--->{min_flt:%u, maj_flt:%u, cmin_flt:%u, cmaj_flt:%u}\n", \
                    buf.min_flt, buf.maj_flt, buf.cmin_flt, buf.cmaj_flt);
                    
                //仅用于标注进程的信息
                printf("         statm-->{size:%ld, resident:%ld, share:%ld, trs:%ld, lrs:%ld, drs:%ld, dt:%ld}\n", \
                    buf.size, buf.resident, buf.share, buf.trs, buf.lrs, buf.drs, buf.dt);
                printf("         status->{vm_size(TOP_VIRT):%ukb, vm_lock:%ukb, vm_rss(TOP_RES):%ukb, vm_data:%ukb, vm_stack:%ukb, vm_swap:%ukb, vm_exe:%ukb, vm_lib:%ukb}\n", \
                    buf.vm_size, buf.vm_lock, buf.vm_rss, buf.vm_data, buf.vm_stack, buf.vm_swap, buf.vm_exe, buf.vm_lib);
            }
        }
        
    }

    closeproc(new_proc_tab);
    
    if (NULL != proc_buf_len){
        *proc_buf_len = stored_procs;
    }
}

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

// get system up time via /proc/uptime
// return 0 if succeed, otherwise failed
int get_uptime(double *sys_uptime_seconds, double* idle_uptime_seconds)
{
    char *file_name = "/proc/uptime";
    FILE* fp = fopen(file_name, "r");  
    if(fp == NULL)  
    {  
        printf("Open %s failed, errno %d.\n", file_name, errno);
        return -3;
    }
    
    char buf[512] = {0};
    fgets(buf, sizeof(buf), fp);
    //printf("%s\n", buf);
    float up1 = 0.0, up2 = 0.0;
    sscanf(buf, "%f %f", &up1, &up2);
    //printf("%f %f\n", up1, up2);

    if (NULL != sys_uptime_seconds){
        *sys_uptime_seconds = up1;
    }
    if (NULL != idle_uptime_seconds){
        *idle_uptime_seconds = up2;
    }

    return 0;
}

// get proc info via /proc/[pid]/stat
//return 0 if succeed, otherwise failed
int get_process_stat(int pid, struct process_usage_t* usage)
{
    if (pid <= 0){
        return -1;
    }
    if (NULL == usage){
        return -2;
    }
    
    char file_name[128];
    sprintf(file_name, "/proc/%d/stat", pid);
    FILE* fp = fopen(file_name, "r");  
    if(fp == NULL)  
    {  
        printf("Open %s failed, pid %d may not exist, errno %d.\n", file_name, pid, errno);
        return -3;
    }
    
    char buf[512] = {0};
    fgets(buf, sizeof(buf), fp);
    //printf("%s\n", buf);
    memset(usage, 0, sizeof(struct process_usage_t));
    int sscanfed = sscanf(buf, "%d%s %c%d%d%d%d%d%u%lu%lu%lu%lu%lu%lu%ld%ld%ld%ld%ld%ld%llu", \
        &usage->pid, usage->comm, &usage->state, &usage->ppid, &usage->pgrp, &usage->session, &usage->tty_nr, &usage->tpgid, &usage->flags, \
        &usage->minflt, &usage->cminflt, &usage->majflt, &usage->cmajflt, &usage->utime, &usage->stime, &usage->cutime, &usage->cstime, \
        &usage->priority, &usage->nice, &usage->num_threads, &usage->itreadvalue, &usage->starttime);
    
#if 0
    printf("sscanf get: %d\n", sscanfed);
    printf("%s:%d\n", VNAME(usage->pid), usage->pid);
    printf("%s:%s\n", VNAME(usage->comm), usage->comm);
    printf("%s:%c\n", VNAME(usage->state), usage->state);
    printf("%s:%d\n", VNAME(usage->ppid), usage->ppid);
    printf("%s:%d\n", VNAME(usage->pgrp), usage->pgrp);
    printf("%s:%d\n", VNAME(usage->session), usage->session);
    printf("%s:%d\n", VNAME(usage->tty_nr), usage->tty_nr);
    printf("%s:%d\n", VNAME(usage->tpgid), usage->tpgid);
    printf("%s:%u\n", VNAME(usage->flags), usage->flags);
    printf("%s:%lu\n", VNAME(usage->minflt), usage->minflt);
    printf("%s:%lu\n", VNAME(usage->cminflt), usage->cminflt);
    printf("%s:%lu\n", VNAME(usage->majflt), usage->majflt);
    printf("%s:%lu\n", VNAME(usage->cmajflt), usage->cmajflt);
    printf("%s:%lu\n", VNAME(usage->utime), usage->utime);
    printf("%s:%lu\n", VNAME(usage->stime), usage->stime);
    printf("%s:%ld\n", VNAME(usage->cutime), usage->cutime);
    printf("%s:%ld\n", VNAME(usage->cstime), usage->cstime);
    printf("%s:%ld\n", VNAME(usage->priority), usage->priority);
    printf("%s:%ld\n", VNAME(usage->nice), usage->nice);
    printf("%s:%ld\n", VNAME(usage->num_threads), usage->num_threads);
    printf("%s:%ld\n", VNAME(usage->itreadvalue), usage->itreadvalue);
    printf("%s:%llu\n", VNAME(usage->starttime), usage->starttime);

    //TODO: 补齐..
#endif

    fclose(fp);
    
    return 0;
}

// pid[in]: < 0 means only monitor total 
//          == 0 means also monitor all processes
//          > 0 means monitor one indicated process too
void refresh_cpu(int pid)
{
    struct cpu_usage_t last_cu;
    get_cpu_stat(&last_cu);
    //printf("cpu user:%llu nice:%llu sys:%llu idle:%llu iowait:%llu irq:%llu softirq:%llu steal:%llu guest:%llu\n", \
        last_cu.user, last_cu.nice, last_cu.sys, last_cu.idle, last_cu.iowait, last_cu.irq, last_cu.softirq, last_cu.steal, last_cu.guest);
        
    //get process info from libprocps.so
    const static int MAX_PROCESS_COUNT = 512;
    proc_t last_proc_buf[MAX_PROCESS_COUNT];
    memset(last_proc_buf, 0, sizeof(proc_t) * MAX_PROCESS_COUNT);
    proc_t new_proc_buf[MAX_PROCESS_COUNT];
    memset(new_proc_buf, 0, sizeof(proc_t) * MAX_PROCESS_COUNT);
    
    int last_out_proc_count, new_out_proc_count;
    if (pid >= 0){
        last_out_proc_count = MAX_PROCESS_COUNT;
        get_proc_info(pid, 0, 0, last_proc_buf, &last_out_proc_count);
        assert((pid == 0) || (pid > 0 && last_out_proc_count <= 1));
    }

    //get process info from /proc/[pid]/stat
    int last_proc_usage_valid = 0, new_proc_usage_valid = 0;
    struct process_usage_t last_proc_usage, new_proc_usage;
    memset(&last_proc_usage, 0, sizeof(struct process_usage_t));
    memset(&new_proc_usage, 0, sizeof(struct process_usage_t));
        
    if (pid > 0){
        if (0 == get_process_stat(pid, &last_proc_usage)){
            last_proc_usage_valid = 1;
        }
    }
        
    while (1)
    {
        sleep(1);   //sample interval. could adjust
        struct cpu_usage_t new_cu;
        get_cpu_stat(&new_cu);
        double new_sysuptime, new_idleuptime;
        get_uptime(&new_sysuptime, &new_idleuptime);
        
        if (pid >= 0){
            new_out_proc_count = MAX_PROCESS_COUNT;
            get_proc_info(pid, 0, 0, new_proc_buf, &new_out_proc_count);
            assert((pid == 0) || (pid > 0 && new_out_proc_count <= 1));
            
            new_proc_usage_valid = 0;
            if (0 == get_process_stat(pid, &new_proc_usage)){
                new_proc_usage_valid = 1;
            }
        }
        
        //计算总的CPU占用
        unsigned long long last_total_cpu = last_cu.user + last_cu.nice + last_cu.sys + last_cu.idle + last_cu.iowait \
            + last_cu.irq + last_cu.softirq + last_cu.steal + last_cu.guest;
        unsigned long long new_total_cpu = new_cu.user + new_cu.nice + new_cu.sys + new_cu.idle + new_cu.iowait \
            + new_cu.irq + new_cu.softirq + new_cu.steal + new_cu.guest;
        unsigned long long total_cpu_delta = new_total_cpu - last_total_cpu;
        
        unsigned long long pcpu = 100 * ((new_total_cpu - last_total_cpu) - (new_cu.idle - last_cu.idle)) / total_cpu_delta;
        
        //打印总的cpu占用
        printf("<cpu usage> total:%.2f%% user:%.2f%% sys:%.2f%% nice:%.2f%% idle:%.2f%% iowait:%.2f%% irq:%.2f%% sirq:%.2f%% steal:%0.2f%% guest:%0.2f%%\n", \
            (double)pcpu, \
            (double)100 * (new_cu.user - last_cu.user) / total_cpu_delta, \
            (double)100 * (new_cu.sys - last_cu.sys) / total_cpu_delta, \
            (double)100 * (new_cu.nice - last_cu.nice) / total_cpu_delta, \
            (double)100 * (new_cu.idle - last_cu.idle) / total_cpu_delta, \
            (double)100 * (new_cu.iowait - last_cu.iowait) / total_cpu_delta, \
            (double)100 * (new_cu.irq - last_cu.irq) / total_cpu_delta, \
            (double)100 * (new_cu.softirq - last_cu.softirq) / total_cpu_delta, \
            (double)100 * (new_cu.steal - last_cu.steal) / total_cpu_delta, \
            (double)100 * (new_cu.guest - last_cu.guest) / total_cpu_delta); 
            
        //计算指定线程的cpu占用
        //TODO: 待完善。 先简化下, 假设只有一个进程
        if (pid >= 0 && new_out_proc_count == 1 && last_out_proc_count == 1){
            assert(new_proc_buf[0].tid == last_proc_buf[0].tid && new_proc_buf[0].tid == pid);
            
            unsigned long long pid_last_total_cpu = last_proc_buf[0].utime + last_proc_buf[0].stime + last_proc_buf[0].cutime + last_proc_buf[0].cstime;
            unsigned long long pid_new_total_cpu = new_proc_buf[0].utime + new_proc_buf[0].stime + new_proc_buf[0].cutime + new_proc_buf[0].cstime;
            
            printf(" <libprocps>        pid %05d  total:%.2f%% user:%.2f%% sys:%.2f%% cuser:%.2f%% csys:%.2f%%\n", pid, \
                (double)100 * (pid_new_total_cpu - pid_last_total_cpu) / total_cpu_delta, \
                (double)100 * (new_proc_buf[0].utime - last_proc_buf[0].utime) / total_cpu_delta, \
                (double)100 * (new_proc_buf[0].stime - last_proc_buf[0].stime) / total_cpu_delta, \
                (double)100 * (new_proc_buf[0].cutime - last_proc_buf[0].cutime) / total_cpu_delta, \
                (double)100 * (new_proc_buf[0].cstime - last_proc_buf[0].cstime) / total_cpu_delta);
        }
        
        if (pid > 0 && new_proc_usage_valid && last_proc_usage_valid){
            unsigned long long pid_last_total_cpu = last_proc_usage.utime + last_proc_usage.stime + last_proc_usage.cutime + last_proc_usage.cstime;
            unsigned long long pid_new_total_cpu = new_proc_usage.utime + new_proc_usage.stime + new_proc_usage.cutime + new_proc_usage.cstime;
            
            printf(" </proc/[pid]/stat> pid %05d  total:%.2f%% user:%.2f%% sys:%.2f%% cuser:%.2f%% csys:%.2f%%\n", pid, \
                (double)100 * (pid_new_total_cpu - pid_last_total_cpu) / total_cpu_delta, \
                (double)100 * (new_proc_usage.utime - last_proc_usage.utime) / total_cpu_delta, \
                (double)100 * (new_proc_usage.stime - last_proc_usage.stime) / total_cpu_delta, \
                (double)100 * (new_proc_usage.cutime - last_proc_usage.cutime) / total_cpu_delta, \
                (double)100 * (new_proc_usage.cstime - last_proc_usage.cstime) / total_cpu_delta);

            double total_process_uptime_seconds = new_sysuptime - (double)new_proc_usage.starttime / sysconf(_SC_CLK_TCK);
            printf(" </proc/[pid]/stat with uptime(ps)> pid %05d  total:%.2f%% user:%.2f%% sys:%.2f%% cuser:%.2f%% csys:%.2f%%\n", pid, \
                (double)100 * ((double)pid_new_total_cpu / sysconf(_SC_CLK_TCK)) / total_process_uptime_seconds, \
                (double)100 * ((double)new_proc_usage.utime / sysconf(_SC_CLK_TCK)) / total_process_uptime_seconds, \
                (double)100 * ((double)new_proc_usage.stime / sysconf(_SC_CLK_TCK)) / total_process_uptime_seconds, \
                (double)100 * ((double)new_proc_usage.cutime / sysconf(_SC_CLK_TCK)) / total_process_uptime_seconds, \
                (double)100 * ((double)new_proc_usage.cstime / sysconf(_SC_CLK_TCK)) / total_process_uptime_seconds);
        }
        
        //保存回last
        memcpy(&last_cu, &new_cu, sizeof(struct cpu_usage_t));
        if (pid >= 0){
            memcpy(last_proc_buf, new_proc_buf, sizeof(struct proc_t) * MAX_PROCESS_COUNT);
            last_out_proc_count = new_out_proc_count;
            
            memcpy(&last_proc_usage, &new_proc_usage, sizeof(struct process_usage_t));
            last_proc_usage_valid = new_proc_usage_valid;
        }
        printf("\n");
    }
    
}



void get_proc_info_tab()
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



int main(int argc, char* argv[])
{
    printf("clock_per_second:%d\n", sysconf(_SC_CLK_TCK));

    if (argc <= 1){
        refresh_cpu(-1);
        goto End;
    }
    else if (argc == 2){
        if (*(argv[1]) == 'H'){
            get_proc_info(0, 1, 1, NULL, NULL);
            goto End;
        }else if (*(argv[1]) == 'p'){
            get_proc_info(0, 0, 1, NULL, NULL);
            goto End;
        }
    }
    else if(argc == 3){
        if (NULL != strstr(argv[1], "-p")){ //want to monitor one process
            int pid = atoi(argv[2]);
            if (0 != pid){  //valid pid
                printf("monitor process %d\n", pid);
                refresh_cpu(pid);
                goto End;
            }
            else {  //TODO: monitor all processes
                printf("TODO: monitor all processes\n");
                goto End;
            }
        }
    }
    
    printf("Usage: \n");
    printf("     1, refresh system cpu info:  simple_top\n");
    printf("     2, refresh cpu info include system and one process:  simple_top -p pid\n");
    printf("     3, capture one snapshot of processes: simple_top p\n");
    printf("     4, capture one snapshot of threads: simple_top H\n");
        
    //get_proc_info_tab();
End:
    return 0;
}

