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

- (IBAction)touchDown:(id)sender {
    exported_test();
}

@end
