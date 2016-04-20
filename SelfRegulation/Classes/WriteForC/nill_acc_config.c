//
//  nill_acc_config.c
//  SelfRegulation
//
//  Created by ra on 4/20/16.
//  Copyright © 2016 nill. All rights reserved.
//

#include "nill_acc_config.h"


#define THIS_FILE "nill_acc_config.h"

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
PJ_DECL(int) app_setId(char *pj_optarg)
{
    pjsua_app_config *cfg = &app_config;
    pjsua_acc_config *cur_acc;
    //cfg->acc_cnt = 0;
    //cur_acc = &cfg->acc_cfg[0];
    cur_acc = &cfg->acc_cfg[cfg->acc_cnt];
//    if (pjsua_verify_url(pj_optarg) != 0) {
//        PJ_LOG(1,(THIS_FILE,"Error: invalid SIP URL '%s' " "in local id argument", pj_optarg));
//        return 0;
//    }
    
    cur_acc->id = pj_str(pj_optarg);
    return 1;
}

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
PJ_DECL(int) app_setRegistrar(char *pj_optarg)
{
    pjsua_app_config *cfg = &app_config;
    pjsua_acc_config *cur_acc;
    //cfg->acc_cnt = 0;
    //cur_acc = &cfg->acc_cfg[0];
    cur_acc = &cfg->acc_cfg[cfg->acc_cnt];
//    if (pjsua_verify_sip_url(pj_optarg) != 0) {
//        PJ_LOG(1,(THIS_FILE,
//                  "Error: invalid SIP URL '%s' in "
//                  "registrar argument", pj_optarg));
//        return 0;
//    }
    cur_acc->reg_uri = pj_str(pj_optarg);
    return 1;
}

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
PJ_DECL(int) app_setProxy(char *pj_optarg)
{
    pjsua_app_config *cfg = &app_config;
    pjsua_acc_config *cur_acc;
    //cfg->acc_cnt = 0;
    //cur_acc = &cfg->acc_cfg[0];
    cur_acc = &cfg->acc_cfg[cfg->acc_cnt];
//    if (pjsua_verify_sip_url(pj_optarg) != 0) {
//        PJ_LOG(1,(THIS_FILE,
//                  "Error: invalid SIP URL '%s' "
//                  "in proxy argument", pj_optarg));
//        return 0;
//    }
    cur_acc->proxy[cur_acc->proxy_cnt++] = pj_str(pj_optarg);
    return 1;
}

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
PJ_DECL(int) app_setUserName(char *pj_optarg)
{
    pjsua_app_config *cfg = &app_config;
    pjsua_acc_config *cur_acc;
    //cfg->acc_cnt = 0;
    //cur_acc = &cfg->acc_cfg[0];
    cur_acc = &cfg->acc_cfg[cfg->acc_cnt];
    //cur_acc->cred_info[cur_acc->cred_count].username = pj_str(pj_optarg);
    pj_strdup2_with_null(app_config.pool, &cur_acc->cred_info[cur_acc->cred_count].username, pj_optarg);
    //cur_acc->cred_info[cur_acc->cred_count].scheme = pj_str("Digest");
    pj_strdup2_with_null(app_config.pool, &cur_acc->cred_info[cur_acc->cred_count].scheme, "Digest");
    return 1;
}

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
PJ_DECL(int) app_setPassword(char *pj_optarg)
{
    pjsua_app_config *cfg = &app_config;
    pjsua_acc_config *cur_acc;
    //cfg->acc_cnt = 0;
    //cur_acc = &cfg->acc_cfg[0];
    cur_acc = &cfg->acc_cfg[cfg->acc_cnt];
    cur_acc->cred_info[cur_acc->cred_count].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
    //cur_acc->cred_info[cur_acc->cred_count].data = pj_str(pj_optarg);
    pj_strdup2_with_null(app_config.pool, &cur_acc->cred_info[cur_acc->cred_count].data, pj_optarg);
#if PJSIP_HAS_DIGEST_AKA_AUTH
    cur_acc->cred_info[cur_acc->cred_count].data_type |= PJSIP_CRED_DATA_EXT_AKA;
    cur_acc->cred_info[cur_acc->cred_count].ext.aka.k = pj_str(pj_optarg);
    cur_acc->cred_info[cur_acc->cred_count].ext.aka.cb = &pjsip_auth_create_aka_response;
#endif
    
    return 1;
}

