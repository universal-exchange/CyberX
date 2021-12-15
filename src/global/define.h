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

#ifndef CYBERX_GLOBAL_DEFINE_H
#define CYBERX_GLOBAL_DEFINE_H

namespace cyberx {

	// 软件信息
	#define DEF_APP_NAME "CyberX" // 系统英文名称
	#define DEF_APP_NAME_CN "分 布 式 计 算 框 架" // 系统中文名称
	#define DEF_APP_VERSION "V0.1.0-Beta Build 20211215" // 系统版本号
	#define DEF_APP_DEVELOPER "Developed by the X-Lab." // 开发者声明
	#define DEF_APP_COMPANY "X-Lab (Shanghai) Co., Ltd." // 公司声明
	#define DEF_APP_COPYRIGHT "Copyright 2021-2022 X-Lab All Rights Reserved." // 版权声明
	#define DEF_APP_HOMEURL "http://www.xlab.com" // 主页链接

	// 网络数据包类型定义
	#define NW_MSG_ATOM_TYPE_MIN    0 // 网络通信 元操作 类型起始
	#define NW_MSG_TYPE_HEART_CHECK 0 // 连接心跳检测消息
	#define NW_MSG_ATOM_TYPE_MAX    7 // 网络通信 元操作 类型终止

	#define NW_MSG_USER_TYPE_MIN    8 // 网络通信 自定义 类型起始
	#define NW_MSG_TYPE_USER_DATA   8 // 用户数据处理消息
	#define NW_MSG_USER_TYPE_MAX   15 // 网络通信 自定义 类型终止

	// 网络数据包编码定义
	#define NW_MSG_CODE_TYPE_MIN  0 // 网络通信 编码 类型起始
	#define NW_MSG_CODE_NONE      0 // 适用于元操作
	#define NW_MSG_CODE_STRING    1 // 直接字符串
	#define NW_MSG_CODE_JSON      2 // Json格式
	#define NW_MSG_CODE_BASE64    3 // Base64格式
	#define NW_MSG_CODE_PROTOBUF  4 // ProtoBuf格式
	#define NW_MSG_CODE_ZLIB      5 // ZLib格式
	#define NW_MSG_CODE_MSGPACK   6 // MsgPack格式
	#define NW_MSG_CODE_TYPE_MAX 15 // 网络通信 编码 类型终止

	// 网络数据包功能定义
	#define NW_MSG_FUNC_TYPE_MIN               0 // 网络通信 功能 类型起始
	#define NW_MSG_FUNC_NONE                   0 // 无任何功能
	#define NW_MSG_FUNC_T_USER_LOGIN       11001 // 用户登录(交易)
	#define NW_MSG_FUNC_T_USER_LOGOUT      11002 // 用户登出(交易)
    #define NW_MSG_FUNC_T_USER_SUBSCRIBE   11003 // 用户订阅(交易)
    #define NW_MSG_FUNC_T_USER_UNSUBSCRIBE 11004 // 用户退订(交易)
	#define NW_MSG_FUNC_Q_USER_LOGIN       12001 // 用户登录(行情)
	#define NW_MSG_FUNC_Q_USER_LOGOUT      12002 // 用户登出(行情)
	#define NW_MSG_FUNC_Q_USER_SUBSCRIBE   12003 // 用户订阅(行情)
	#define NW_MSG_FUNC_Q_USER_UNSUBSCRIBE 12004 // 用户退订(行情)
	#define NW_MSG_FUNC_R_USER_LOGIN       13001 // 用户登录(风控)
	#define NW_MSG_FUNC_R_USER_LOGOUT      13002 // 用户登出(风控)
	#define NW_MSG_FUNC_R_USER_SUBSCRIBE   13003 // 用户订阅(风控)
	#define NW_MSG_FUNC_R_USER_UNSUBSCRIBE 13004 // 用户退订(风控)
    #define NW_MSG_FUNC_T_ORDER_SYSTEM_STK 21000 // 系统指令(股票)
	#define NW_MSG_FUNC_T_ORDER_INSERT_STK 21001 // 交易委托(股票)
    #define NW_MSG_FUNC_T_ORDER_CANCEL_STK 21002 // 交易撤单(股票)
	#define NW_MSG_FUNC_T_REPLY_ORDER_STK  31001 // 报单回报(股票)
	#define NW_MSG_FUNC_T_REPLY_TRADE_STK  31002 // 成交回报(股票)
	#define NW_MSG_FUNC_Q_STOCK_SNAPS      41001 // 个股快照(股票)
	#define NW_MSG_FUNC_Q_STOCK_ORDER      41002 // 逐笔委托(股票)
	#define NW_MSG_FUNC_Q_STOCK_TRADE      41003 // 逐笔成交(股票)
	#define NW_MSG_FUNC_TYPE_MAX           65535 // 网络通信 功能 类型终止

    #define DEF_TYPE_AUTOCALL_BOOSTER         "booster" // Booster
    #define DEF_TYPE_AUTOCALL_PHOENIX         "phoenix" // Phoenix
    #define DEF_TYPE_AUTOCALL_SNOWBALL        "snowball" // Snowball
    #define DEF_TYPE_VANILLA_AMERICAN         "american" // American
    #define DEF_TYPE_VANILLA_EUROPEAN         "european" // European
    #define DEF_TYPE_DIGITAL_GAP              "gap" // Gap
    #define DEF_TYPE_DIGITAL_CASH_OR_NOTHING  "cashornothing" // CashOrNothing
    #define DEF_TYPE_DIGITAL_ASSET_OR_NOTHING "assetornothing" // AssetOrNothing
    #define DEF_TYPE_DIGITAL_SUPER_SHARE      "supershare" // SuperShare
    #define DEF_TYPE_BARRIER_SINGLE           "single" // Single
    #define DEF_TYPE_BARRIER_DOUBLE           "double" // Double
    #define DEF_TYPE_STOCHASTIC_MODEL_GBM     "gbm" // GBM
    #define DEF_TYPE_STOCHASTIC_MODEL_CIR     "cir" // CIR
    #define DEF_TYPE_STOCHASTIC_MODEL_JDP     "jdp" // JDP
    #define DEF_TYPE_STOCHASTIC_MODEL_HEST    "hest" // HEST
    #define DEF_TYPE_STOCHASTIC_MODEL_SABR    "sabr" // SABR
    #define DEF_TYPE_STOCHASTIC_MODEL_USER    "user" // USER

    #define DEF_BARRIER_UP_IN    1 // 向上敲入
    #define DEF_BARRIER_DOWN_IN  2 // 向下敲入
    #define DEF_BARRIER_UP_OUT   3 // 向上敲出
    #define DEF_BARRIER_DOWN_OUT 4 // 向下敲出

    #define DEF_BARRIER_UOC_DOP  1 // 向上敲出看涨，向下敲出看跌，双鲨

} // namespace cyberx

#endif // CYBERX_GLOBAL_DEFINE_H
