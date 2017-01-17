//
//  xlog_test.cpp
//  xlog_test
//
//  Created by wangyoucao577 on 1/17/17.
//  Copyright © 2017 wangyoucao577. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

#import <mars/xlog/xloggerbase.h>
#import <mars/xlog/xlogger.h>
#import <mars/xlog/appender.h>
#import <mars/comm/time_utils.h>

static void test_case_each_xlog_interface(){
    xverbose2("%s %d %s", "verbose my test", 1, "1");
    xverbose2(TSF"%0 %1 %0", "verbose my test", 2, "2");
    xverbose2(TSF"%_ %_ %_", "verbose my test", 3, "3");
    
    xdebug2(TSF"%_ %_ %_", "debug my test", 3, "3");
    xinfo2(TSF"%_ %_ %_", "info my test", 3, "3");
    xwarn2(TSF"%_ %_ %_", "warn my test", 3, "3");
    xerror2(TSF"%_ %_ %_", "error my test", 3, "3");
    xfatal2(TSF"%_ %_ %_", "fatal my test", 3, "3");

}

static void test_case_loop_xlog(int xlog_count_per_sec){
    
    int loop_index = 0;
    
    int curr_xlog_count = 0;
    
    uint64_t curr_interval_start_ms = timeMs();
    uint64_t curr_ms = 0;
    
    int interval_count = 0;
    
    
    while (1){
        
        curr_ms = timeMs();
        if (curr_ms >= curr_interval_start_ms + 1000){
            ++interval_count;
            
            curr_xlog_count = 0;
            curr_interval_start_ms = curr_ms;
            continue;
        }
        
        if (curr_xlog_count >= xlog_count_per_sec){
            usleep(10 * 1000);
            continue;
        }
            
        xverbose2(TSF"%_ %_ curr_interval_index %_ interval %_", "verbose", loop_index++, curr_xlog_count++, interval_count);
    }
}


void init_xlog_test(const char* log_path)
{
    // init xlog
#if DEBUG
    xlogger_SetLevel(kLevelVerbose);
    appender_set_console_log(true);
#else
    xlogger_SetLevel(kLevelInfo);
    appender_set_console_log(false);
#endif
    
    appender_open(kAppednerAsync, log_path, "myxlogtest");

}

void destory_xlog_test()
{
    appender_flush_sync();
    appender_close();
}

void run_xlog_test_cases()
{
    test_case_each_xlog_interface();
    
    test_case_loop_xlog(1000);
}
