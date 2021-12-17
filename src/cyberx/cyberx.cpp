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

#include <chrono>
#include <thread>
#include <stdlib.h> // system

#include <common/sysdef.h>
#include <common/assist.h>
#include <common/common.h>

#ifdef __OS_WINDOWS__
#endif

#ifdef __OS_LINUX__
#include <iostream> // printf、getchar
#endif

#include <syslog/syslog.h>
#include <plugins/plugins.h>

#include "global/define.h"
#include "syscfg/syscfg.h"
#include "master/master.h"
#include "worker/worker.h"

#include "cyberx.h"

void SystemUninitialize() { // 在控制台事件和单例限制退出时调用会异常
	try {
		basicx::Plugins* plugins = basicx::Plugins::GetInstance(); // 02
		if( plugins != nullptr ) {
			plugins->~Plugins();
		}

		// SysCfg

		basicx::SysLog_S* syslog = basicx::SysLog_S::GetInstance(); // 01
		if( syslog != nullptr ) {
			syslog->~SysLog_S();
		}
	} // try
	catch( ... ) {
	}
}

#ifdef __OS_WINDOWS__
int32_t __stdcall ConsoleHandler( unsigned long event ) { // 控制台事件检测
	std::string log_cate = "<SYSTEM_EVENT>";
	basicx::SysLog_S* syslog = basicx::SysLog_S::GetInstance();

	switch( event ) {
	case CTRL_C_EVENT: // 用户按下 "Ctrl + C" 键
		syslog->LogWrite( basicx::syslog_level::c_info, log_cate, std::string( "用户按下 Ctrl + C 键。" ) );
		break;
	case CTRL_BREAK_EVENT: // 用户按下 "Ctrl + Break" 键
		syslog->LogWrite( basicx::syslog_level::c_info, log_cate, std::string( "用户按下 Ctrl + Break 键。" ) );
		break;
	case CTRL_CLOSE_EVENT: // 关闭控制台窗口 // 可清理延时时间 5 秒
		syslog->LogWrite( basicx::syslog_level::c_warn, log_cate, std::string( "控制台窗口被强制关闭，系统结束运行！\r\n" ) );
		SystemUninitialize(); // 这里一般来不及清理
		break;
	case CTRL_LOGOFF_EVENT: // 用户注销 // 可清理延时时间 20 秒
		syslog->LogWrite( basicx::syslog_level::c_warn, log_cate, std::string( "用户注销，系统结束运行！\r\n" ) );
		break;
	case CTRL_SHUTDOWN_EVENT: // 用户关机 // 可清理延时时间 20 秒
		syslog->LogWrite( basicx::syslog_level::c_warn, log_cate, std::string( "用户关机，系统结束运行！\r\n" ) );
		break;
	}

	return 1;
}
#endif

#ifdef __OS_WINDOWS__
void ConsoleEventsSet() {
	if( !SetConsoleCtrlHandler( (PHANDLER_ROUTINE)ConsoleHandler, TRUE ) ) { // 安装事件处理，用于检测控制台关闭及按键等
		std::string log_cate = "<SYSTEM_MAIN>";
		basicx::SysLog_S* syslog = basicx::SysLog_S::GetInstance();
		syslog->LogWrite( basicx::syslog_level::c_error, log_cate, std::string( "无法安装控制台事件检测句柄！" ) );
	}
}
#endif

bool SystemInitialize() {
	std::string log_info;
	std::string log_cate = "<SYSTEM_INIT>";

	basicx::SysLog_S* syslog = basicx::SysLog_S::GetInstance();

    log_info = "开始系统初始化 ...\r\n";
	syslog->LogWrite( basicx::syslog_level::c_info, log_cate, log_info );
	log_info = "LOG>: 开始系统初始化 ....";
	syslog->LogPrint( basicx::syslog_level::c_info, log_cate, log_info );

	try {
		log_info = "LOG>: 读取 系统参数配置 ....";
		syslog->LogPrint( basicx::syslog_level::c_info, log_cate, log_info );

		std::this_thread::sleep_for( std::chrono::seconds( 1 ) ); // 避免 CMD 输出被打乱

		// TODO：添加更多初始化任务

	} // try
	catch( ... ) {
		log_info = "系统初始化时发生未知错误！\r\n";
		syslog->LogWrite( basicx::syslog_level::c_fatal, log_cate, log_info );
		log_info = "LOG>: 系统初始化时发生未知错误！";
		syslog->LogPrint( basicx::syslog_level::c_info, log_cate, log_info );
	}

    log_info = "系统初始化完成。\r\n";
	syslog->LogWrite( basicx::syslog_level::c_info, log_cate, log_info );
	log_info = "LOG>: 系统初始化完成。";
	syslog->LogPrint( basicx::syslog_level::c_info, log_cate, log_info );

	return true;
}

int main( int32_t argc, char* argv[] ) {
#ifdef __OS_WINDOWS__
    SetConsoleOutputCP( CP_UTF8 ); // 修改控制台为 utf-8 格式 // 使用 system( "chcp 65001" ); 可能导致崩溃
#endif
#ifdef __OS_WINDOWS__
	basicx::SetMinimumTimerResolution();
#endif

	std::string log_info;
	std::string log_cate = "<SYSTEM_MAIN>";

	basicx::SysLog_S syslog_s( DEF_APP_NAME ); // 唯一实例 // 01
	basicx::SysLog_S* syslog = basicx::SysLog_S::GetInstance();
	syslog->SetThreadSafe( true );
	syslog->SetLocalCache( true );
	syslog->SetActiveFlush( false );
	syslog->SetActiveSync( false );
	syslog->SetWorkThreads( 1 );
	syslog->SetFileStreamBuffer( DEF_SYSLOG_FSBM_NONE );
	syslog->InitSysLog( DEF_APP_NAME, DEF_APP_VERSION, DEF_APP_COMPANY, DEF_APP_COPYRIGHT );
	syslog->PrintSysInfo();
	syslog->WriteSysInfo();

	try {
#ifdef __OS_WINDOWS__
		ConsoleEventsSet(); // 01
#endif
		SystemInitialize(); // 02

		while( 1 ) {
			std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
		}
	} // try
	catch( ... ) {
		log_info = "系统主线程发生未知错误！";
		syslog->LogWrite( basicx::syslog_level::c_fatal, log_cate, log_info );
	}

    log_info = "系统主线程退出！";
	syslog->LogWrite( basicx::syslog_level::c_warn, log_cate, log_info );

#ifdef __OS_WINDOWS__
	system( "pause" );
#endif

#ifdef __OS_LINUX__
    printf( "Press any key to continue . . . " );
	system( "stty raw" );
	getchar(); // fgetc( stdin );
	printf( "\r\n" );
	system( "stty cooked" );
#endif

	return 0;
}
