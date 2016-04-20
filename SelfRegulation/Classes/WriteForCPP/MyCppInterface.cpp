//
//  MyCppInterface.cpp
//  SelfRegulation
//
//  Created by ra on 4/18/16.
//  Copyright © 2016 nill. All rights reserved.
//

#include "MyCppInterface.hpp"

MyCppinterface::MyCppinterface()
{
    
}

MyCppinterface::~MyCppinterface()
{
    
}

void MyCppinterface::handleEndpoint()
{
    int ret = 0;
    Endpoint ep;
    
    // create
    try {
        ep.libCreate();
    } catch (Error & err) {
        cout << "Exception: " << err.info() << endl;
        ret = 1;
    }
    
    // init
    EpConfig ep_cfg;
    ep_cfg.logConfig.level = 5;
    ep_cfg.uaConfig.maxCalls = 4;
//  ep_cfg.mediaConfig.sndClockRate = 16000;
    
    try {
        ep.libInit(ep_cfg);
    } catch (Error &err) {
        cout << "Initialization error: " << err.info() << endl;
    }

    // config
    try {
        TransportConfig tcfg;
        tcfg.port = 5060;
        TransportId tid = ep.transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
        cout << "tid is----" << tid << endl;
    } catch(Error& err) {
        cout << "Transport creation error: " << err.info() << endl;
    }

    // start
    try {
        ep.libStart();
    } catch(Error& err) {
        cout << "Startup error: " << err.info() << endl;
    }
    
}
