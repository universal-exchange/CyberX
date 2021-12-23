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

#include "master_.h"

#define CFG_WORK_THREAD_NUM 1 // 输入输出服务工作线程数

namespace cyberx {

	Master_P::Master_P()
		: m_log_cate( "<MASTER>" ) {
		m_syslog = basicx::SysLog_S::GetInstance();
		m_syscfg = cyberx::SysCfg_S::GetInstance();
	}

	Master_P::~Master_P() {
	}

	void Master_P::LogPrint( basicx::syslog_level log_level, std::string& log_info, int32_t log_show/* = 0*/ ) {
		m_syslog->LogWrite( log_level, m_log_cate, log_info );
		if( 0 == log_show ) {
			m_syslog->LogPrint( log_level, m_log_cate, "LOG>: " + log_info ); // 控制台
		}
	}

	void Master_P::Start() {
		std::string log_info = "Master - Start";
		LogPrint( basicx::syslog_level::n_debug, log_info );
	}

	void Master_P::Stop() {
		std::string log_info = "Master - Stop";
		LogPrint( basicx::syslog_level::n_debug, log_info );
	}

	Master* Master::m_instance = nullptr;

	Master::Master()
		: m_master_p( nullptr ) {
		try {
			m_master_p = new Master_P();
		}
		catch( ... ) {
		}
		m_instance = this;
	}

	Master::~Master() {
		if( m_master_p != nullptr ) {
			delete m_master_p;
			m_master_p = nullptr;
		}
	}

	Master* Master::GetInstance() {
		return m_instance;
	}

	void Master::Start() {
		m_master_p->Start();
	}

	void Master::Stop() {
		m_master_p->Stop();
	}

} // namespace cyberx
