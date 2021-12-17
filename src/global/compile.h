/*
* Copyright (c) 2021-2022 the CyberX authors
* All rights reserved.
*
* The project sponsor and lead author is Xu Rendong.
* E-mail: xrd@ustc.edu, QQ: 277195007, WeChat: xrd_ustc
* See the contributors file for names of other contributors.
*
* Commercial use of this code in source and binary forms is
* governed by a LGPL v3 license. You may get a copy from the
* root directory. Or else you should get a specific written
* permission from the project author.
*
* Individual and educational use of this code in source and
* binary forms is governed by a 3-clause BSD license. You may
* get a copy from the root directory. Certainly welcome you
* to contribute code of all sorts.
*
* Be sure to retain the above copyright notice and conditions.
*/

#ifndef CYBERX_GLOBAL_COMPILE_H
#define CYBERX_GLOBAL_COMPILE_H

#include <common/sysdef.h>

//---------- 基础组件 ----------//

#define CYBERX_GLOBAL_EXP
//#define CYBERX_GLOBAL_IMP

#define CYBERX_SHARES_EXP
//#define CYBERX_SHARES_IMP

//---------- 功能组件 ----------//

#define CYBERX_SYSCFG_EXP
//#define CYBERX_SYSCFG_IMP

#define CYBERX_MASTER_EXP
//#define CYBERX_MASTER_IMP

#define CYBERX_WORKER_EXP
//#define CYBERX_WORKER_IMP

#define CYBERX_CYBERX_JS_EXP
//#define CYBERX_CYBERX_JS_IMP

#define CYBERX_CYBERX_PY_EXP
//#define CYBERX_CYBERX_PY_IMP

#define CYBERX_CYBERX_XL_EXP
//#define CYBERX_CYBERX_XL_IMP

//---------- 设置结束 ----------//

#ifdef __OS_WINDOWS__

#ifdef CYBERX_GLOBAL_EXP
    #define CYBERX_GLOBAL_EXPIMP __declspec(dllexport)
#endif

#ifdef CYBERX_GLOBAL_IMP
    #define CYBERX_GLOBAL_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef CYBERX_SHARES_EXP
    #define CYBERX_SHARES_EXPIMP __declspec(dllexport)
#endif

#ifdef CYBERX_SHARES_IMP
    #define CYBERX_SHARES_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef CYBERX_SYSCFG_EXP
    #define CYBERX_SYSCFG_EXPIMP __declspec(dllexport)
#endif

#ifdef CYBERX_SYSCFG_IMP
    #define CYBERX_SYSCFG_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef CYBERX_MASTER_EXP
    #define CYBERX_MASTER_EXPIMP __declspec(dllexport)
#endif

#ifdef CYBERX_MASTER_IMP
    #define CYBERX_MASTER_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef CYBERX_WORKER_EXP
    #define CYBERX_WORKER_EXPIMP __declspec(dllexport)
#endif

#ifdef CYBERX_WORKER_IMP
    #define CYBERX_WORKER_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef CYBERX_CYBERX_JS_EXP
    #define CYBERX_CYBERX_JS_EXPIMP __declspec(dllexport)
#endif

#ifdef CYBERX_CYBERX_JS_IMP
    #define CYBERX_CYBERX_JS_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef CYBERX_CYBERX_PY_EXP
    #define CYBERX_CYBERX_PY_EXPIMP __declspec(dllexport)
#endif

#ifdef CYBERX_CYBERX_PY_IMP
    #define CYBERX_CYBERX_PY_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef CYBERX_CYBERX_XL_EXP
    #define CYBERX_CYBERX_XL_EXPIMP __declspec(dllexport)
#endif

#ifdef CYBERX_CYBERX_XL_IMP
    #define CYBERX_CYBERX_XL_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#endif

#ifdef __OS_LINUX__

#ifdef CYBERX_GLOBAL_EXP
    #define CYBERX_GLOBAL_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef CYBERX_SHARES_EXP
    #define CYBERX_SHARES_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef CYBERX_SYSCFG_EXP
    #define CYBERX_SYSCFG_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef CYBERX_MASTER_EXP
    #define CYBERX_MASTER_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef CYBERX_WORKER_EXP
    #define CYBERX_WORKER_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef CYBERX_CYBERX_JS_EXP
    #define CYBERX_CYBERX_JS_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef CYBERX_CYBERX_PY_EXP
    #define CYBERX_CYBERX_PY_EXPIMP __attribute__((visibility("default")))
#endif

#ifdef CYBERX_CYBERX_XL_EXP
    #define CYBERX_CYBERX_XL_EXPIMP __attribute__((visibility("default")))
#endif

#endif

#endif // CYBERX_GLOBAL_COMPILE_H
