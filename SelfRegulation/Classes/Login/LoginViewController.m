//
//  LoginViewController.m
//  SelfRegulation
//
//  Created by ra on 4/19/16.
//  Copyright © 2016 nill. All rights reserved.
//

#import "LoginViewController.h"
#import "AppDelegate.h"

@interface LoginViewController()

@property (weak, nonatomic) IBOutlet UITextField *userName;
@property (weak, nonatomic) IBOutlet UITextField *userPasswd;

@end

@implementation LoginViewController
{
    AppDelegate *appDelegate;
}


- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
}

// 
- (IBAction)loginButton:(id)sender {
    
    [appDelegate startNatUA2:@"login"];
    
}


@end
