
#include <stdio.h>
#include <errno.h>
#include "proc/readproc.h"

#define ST_PRINTF(type, args...) printf(type, ##args)

void simple_top(int want_threads)
{
    int openproc_flags = PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLCOM;
    if (want_threads){
        openproc_flags |= PROC_LOOSE_TASKS;
    }
    //openproc_flags |= PROC_FILL_LXC; //what's the meaning of LXC???
    PROCTAB* new_proc_tab = openproc(openproc_flags);
    if (NULL == new_proc_tab){
        ST_PRINTF("openproc failed, errno %d.\n", errno);
        return;
    }
    
    static proc_t buf, buf2; 
    while (readproc(new_proc_tab, &buf))
    {
            ST_PRINTF("pid:%5d(tgid:%d) cmd:%s cmdline:%s threads:%d state:%c\n", \
                buf.tid, buf.tgid, buf.cmd, ((NULL == buf.cmdline) || (NULL == *(buf.cmdline))) ? "" : *(buf.cmdline), buf.nlwp, buf.state);
            ST_PRINTF("         stat--->{utime:%llu stime:%llu cutime:%llu cstime:%llu vsize:%lukb start_code:0x%x end_code:0x%x start_stack:0x%x}\n", \
                buf.utime, buf.stime, buf.cutime, buf.cstime, buf.vsize, buf.start_code, buf.end_code, buf.start_stack);
            ST_PRINTF("         stat--->{min_flt:%u, maj_flt:%u, cmin_flt:%u, cmaj_flt:%u}\n", \
                buf.min_flt, buf.maj_flt, buf.cmin_flt, buf.cmaj_flt);
            ST_PRINTF("         statm-->{size:%ld, resident:%ld, share:%ld, trs:%ld, lrs:%ld, drs:%ld, dt:%ld}\n", \
                buf.size, buf.resident, buf.share, buf.trs, buf.lrs, buf.drs, buf.dt);
            ST_PRINTF("         status->{vm_size(TOP_VIRT):%ukb, vm_lock:%ukb, vm_rss(TOP_RES):%ukb, vm_data:%ukb, vm_stack:%ukb, vm_swap:%ukb, vm_exe:%ukb, vm_lib:%ukb}\n", \
                buf.vm_size, buf.vm_lock, buf.vm_rss, buf.vm_data, buf.vm_stack, buf.vm_swap, buf.vm_exe, buf.vm_lib);

        if (want_threads){
            while (readtask(new_proc_tab, &buf, &buf2))
            {
                //标示线程的一些信息
                ST_PRINTF("tid:%5d(tgid/pid:%d) cmd:%s state:%c utime:%llu stime:%llu\n", \
                    buf2.tid, buf2.tgid, buf2.cmd, buf2.state, buf2.utime, buf2.stime);                
            }
        }
        
    }
    closeproc(new_proc_tab);
    
}

void simle_top_tab()
{
    int openproc_flags = PROC_FILLMEM | PROC_FILLSTAT | PROC_LOOSE_TASKS;   
    proc_t ** pt = readproctab(openproc_flags);
    if (NULL == pt){
        ST_PRINTF("readproctab failed, errno %d.\n", errno);
        return;
    }
    
    proc_t *t = NULL;
    int i = 0;
    while (t = pt[i++])
    {
        ST_PRINTF("tid:%d(ppid:%d pid:%d) cmd:%s state:%c utime:%llu stime:%llu cutime:%llu cstime:%llu \n", \
            t->tid, t->ppid, t->tgid, t->cmd, t->state, t->utime, t->stime, t->cutime, t->cstime);
    }
}

int main()
{
    simple_top(0);
    ST_PRINTF("\n\n\n");
    simple_top(1);
    //simle_top_tab();
    return 0;
}

