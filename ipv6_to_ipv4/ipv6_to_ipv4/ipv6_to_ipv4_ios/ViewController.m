//
//  ViewController.m
//  ipv6_to_ipv4_ios
//
//  Created by wangyoucao577 on 1/10/17.
//  Copyright © 2017 wangyoucao577. All rights reserved.
//

#import "ViewController.h"
#include "ipv4_ipv6_interface.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *_version_lable;
@property (weak, nonatomic) IBOutlet UILabel *local_network_label;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    // 显示版本号
    NSString * shortVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    NSString * buildVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
 
    NSString *version = @"V";
    version = [version stringByAppendingFormat: @"%@.%@ \n", shortVersion, buildVersion];
    
    NSLog(@"version: %@\n", version);

    self._version_lable.text = version;
    
    // 获取并显示Local Network信息
    self.local_network_label.text = @"lo 127.0.0.1 AF_NET(2)";
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)touchDown:(id)sender {
    exported_test();
}

@end
