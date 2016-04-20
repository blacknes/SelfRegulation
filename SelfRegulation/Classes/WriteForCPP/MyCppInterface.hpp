//
//  MyCppInterface.hpp
//  SelfRegulation
//
//  Created by ra on 4/18/16.
//  Copyright © 2016 nill. All rights reserved.
//

#ifndef MyCppInterface_hpp
#define MyCppInterface_hpp

#include "MyAccount.hpp"
#include "MyCall.hpp"
#include "CommonHeader.h"

#define THIS_FILE = "MyCppInterface.cpp"

class MyCppinterface {
    
    
public:
    MyCppinterface();
    ~MyCppinterface();
    
    void handleEndpoint();
    
};

#endif /* MyCppInterface_hpp */
