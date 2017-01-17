//
//  main.m
//  xlog_test
//
//  Created by zhangjie on 1/17/17.
//  Copyright © 2017 wangyoucao577. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import <sys/xattr.h>

#include "xlog_test.h"


int main(int argc, char * argv[]) {
    @autoreleasepool {
        
        NSString* logPath = [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingString:@"/xlog"];
        
        // set do not backup for logpath on iOS
        const char* attrName = "com.apple.MobileBackup";
        u_int8_t attrValue = 1;
        setxattr([logPath UTF8String], attrName, &attrValue, sizeof(attrValue), 0, 0);
        
        // init xlog test
        init_xlog_test([logPath UTF8String]);
        
        // run test cases
        run_xlog_test_cases();
        
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
