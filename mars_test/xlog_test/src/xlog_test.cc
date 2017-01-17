//
//  xlog_test.cpp
//  xlog_test
//
//  Created by wangyoucao577 on 1/17/17.
//  Copyright © 2017 wangyoucao577. All rights reserved.
//

#include <stdio.h>

#import <mars/xlog/xloggerbase.h>
#import <mars/xlog/xlogger.h>
#import <mars/xlog/appender.h>

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
}
