//
//  MyCall.hpp
//  SelfRegulation
//
//  Created by ra on 4/18/16.
//  Copyright © 2016 nill. All rights reserved.
//

#ifndef MyCall_hpp
#define MyCall_hpp

#include "CommonHeader.h"
#include "MyAccount.hpp"

class MyAccount;

class MyCall : public Call {
    
private:
    MyAccount *myAcc;
    
public:
    MyCall(Account &acc, int call_id = PJSUA_INVALID_ID)
    : Call(acc, call_id)
    {
        myAcc = (MyAccount *)&acc;
    }
    
    ~MyCall();
    
    // Notification when call's state has changed.
    void onCallState(OnCallStateParam &prm);
    
    // Notification when call's media state has changed.
//    void onCallMediaState(OnCallMediaStateParam &prm);
    
    
};

#endif /* MyCall_hpp */
