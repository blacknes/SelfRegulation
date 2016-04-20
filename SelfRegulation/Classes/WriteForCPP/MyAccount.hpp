//
//  MyAccount.hpp
//  SelfRegulation
//
//  Created by ra on 4/8/16.
//  Copyright © 2016 nill. All rights reserved.
//

#ifndef MyAccount_hpp
#define MyAccount_hpp

#include "CommonHeader.h"
#include "MyCall.hpp"


class MyAccount : public Account
{
public:
    vector<Call *> calls;
    
public:
    MyAccount();
    ~MyAccount();
    
    void onRegState(OnRegStateParam &prm);
    
    void removeCall(Call *call);
    
    void onIncomingCall(OnIncomingCallParam &iprm);
};

#endif /* MyAccount_hpp */
