//
//  NILLPjsua.h
//  SelfRegulation
//
//  Created by ra on 3/25/16.
//  Copyright © 2016 nill. All rights reserved.
//

#ifndef NILLPjsua_h
#define NILLPjsua_h

#include <pjsua-lib/pjsua.h>

/**
 * Initialize and start pjsua.
 *
 * @param sipUser the sip username to be used for register
 * @param sipDomain the domain of the sip register server
 *
 * @return When successful, returns 0.
 */
int startPjsip(char *sipUser, char* sipDomain);

/**
 * Make VoIP call.
 *
 * @param destUri the uri of the receiver, something like "sip:192.168.43.106:5080"
 */
void makeCall(char* destUri);

/**
 * End ongoing VoIP calls
 */
void endCall();


#endif /* NILLPjsua_h */
