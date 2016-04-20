//
//  MyCall.cpp
//  SelfRegulation
//
//  Created by ra on 4/18/16.
//  Copyright © 2016 nill. All rights reserved.
//

#include "MyCall.hpp"

MyCall::~MyCall()
{
    
}

void MyCall::onCallState(OnCallStateParam &prm)
{
    PJ_UNUSED_ARG(prm);
    
    CallInfo ci = getInfo();
    std::cout << "*** Call: " <<  ci.remoteUri << " [" << ci.stateText
    << "]" << std::endl;
    
    if (ci.state == PJSIP_INV_STATE_DISCONNECTED) {
        myAcc->removeCall(this);
        /* Delete the call */
        delete this;
    }
}
