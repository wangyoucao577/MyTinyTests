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

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    NSString * shortVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    NSString * buildVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
    NSLog(@"version: %@.%@\n", shortVersion, buildVersion);
 
    NSString *version = @"version: ";
    version = [version stringByAppendingFormat: @"%@.%@ \n", shortVersion, buildVersion] ;
    self._version_lable.text = version;
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)touchDown:(id)sender {
    exported_test();
}

@end
