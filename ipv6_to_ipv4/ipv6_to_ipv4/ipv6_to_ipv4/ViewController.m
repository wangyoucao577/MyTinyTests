//
//  ViewController.m
//  ipv6_to_ipv4
//
//  Created by wangyoucao577 on 8/25/16.
//  Copyright © 2016 wangyoucao577. All rights reserved.
//

#import "ViewController.h"
#include "ipv4_ipv6_interface.h"


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void) ipv6_to_ipv4_test_2 {
    exported_test();
}

- (IBAction)test_run:(id)sender {
    [self ipv6_to_ipv4_test_2];
}

@end
