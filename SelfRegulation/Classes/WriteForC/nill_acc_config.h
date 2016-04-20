//
//  nill_acc_config.h
//  SelfRegulation
//
//  Created by ra on 4/20/16.
//  Copyright © 2016 nill. All rights reserved.
//

#ifndef nill_acc_config_h
#define nill_acc_config_h

#include <pjsua-lib/pjsua.h>
#include "pjsua_app_common.h"
/*
 * ************************************
 * 函数：app_setId
 * 功能：
 *      设置nat ID参数
 * @param:
 *      char * pj_optarg
 * @return:
 *    0:failur 1:succes
 */
PJ_DECL(int) app_setId(char *pj_optarg);

/*
 * ************************************
 * 函数：app_setRegistrar
 * 功能：
 *      设置nat registrar参数
 * @param:
 *      char * pj_optarg
 * @return:
 *    0:failur 1:succes
 */
PJ_DECL(int) app_setRegistrar(char *pj_optarg);

/*
 * ************************************
 * 函数：app_setProxy
 * 功能：
 *      设置nat proxy参数
 * @param:
 *      char * pj_optarg
 * @return:
 *    0:failur 1:succes
 */
PJ_DECL(int) app_setProxy(char *pj_optarg);

/*
 * ************************************
 * 函数：app_setUserName
 * 功能：
 *      设置nat username参数
 * @param:
 *      char * pj_optarg
 * @return:
 *    0:failur 1:succes
 */
PJ_DECL(int) app_setUserName(char *pj_optarg);

/*
 * ************************************
 * 函数：app_setPassword
 * 功能：
 *      设置nat password参数
 * @param:
 *      char * pj_optarg
 * @return:
 *    0:failur 1:succes
 */
PJ_DECL(int) app_setPassword(char *pj_optarg);

#endif /* nill_acc_config_h */
