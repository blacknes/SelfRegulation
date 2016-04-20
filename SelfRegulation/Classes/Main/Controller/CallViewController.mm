//
//  CallViewController.m
//  SelfRegulation
//
//  Created by ra on 4/5/16.
//  Copyright © 2016 nill. All rights reserved.
//

#import "CallViewController.h"
#include "MyCppInterface.hpp"

@interface CallViewController ()

@end

@implementation CallViewController
{
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/
- (IBAction)createAccount:(id)sender {
    
    MyCppinterface *interface;
    interface->handleEndpoint();
    
    //configure an AccountConfig
    AccountConfig acfg;
    acfg.idUri = "sip:10004@192.168.12.122";
    acfg.regConfig.registrarUri = "sip:192.168.12.122";
    AuthCredInfo cred("digest", "*", "test", 0, "secret");
    acfg.sipConfig.authCreds.push_back( cred );
    
    
    pj_thread_desc rtpdesc;
    pj_thread_t *thread = 0;
    if( !pj_thread_is_registered())
    {
        if (pj_thread_register(NULL,rtpdesc,&thread) == PJ_SUCCESS)
        {
            //create the account
            MyAccount *acc = new MyAccount;
            acc->create(acfg);
        }
    }
    
}

@end
