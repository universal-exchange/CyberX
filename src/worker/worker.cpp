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

#include "worker_.h"

#define CFG_WORK_THREAD_NUM 1 // 输入输出服务工作线程数

namespace cyberx {

	Worker_P::Worker_P()
		: m_log_cate( "<WORKER>" ) {
		m_syslog = basicx::SysLog_S::GetInstance();
		m_syscfg = cyberx::SysCfg_S::GetInstance();
		m_plugins = basicx::Plugins::GetInstance();
	}

	Worker_P::~Worker_P() {
	}

	void Worker_P::LogPrint( basicx::syslog_level log_level, std::string& log_info, int32_t log_show/* = 0*/ ) {
		m_syslog->LogWrite( log_level, m_log_cate, log_info );
		if( 0 == log_show ) {
			m_syslog->LogPrint( log_level, m_log_cate, "LOG>: " + log_info ); // 控制台
		}
	}

	void Worker_P::Start() {
		std::string log_info = "Worker - Start";
		LogPrint( basicx::syslog_level::n_debug, log_info );
	}

	void Worker_P::Stop() {
		std::string log_info = "Worker - Stop";
		LogPrint( basicx::syslog_level::n_debug, log_info );
	}

	Worker* Worker::m_instance = nullptr;

	Worker::Worker()
		: m_worker_p( nullptr ) {
		try {
			m_worker_p = new Worker_P();
		}
		catch( ... ) {
		}
		m_instance = this;
	}

	Worker::~Worker() {
		if( m_worker_p != nullptr ) {
			delete m_worker_p;
			m_worker_p = nullptr;
		}
	}

	Worker* Worker::GetInstance() {
		return m_instance;
	}

	void Worker::Start() {
		m_worker_p->Start();
	}

	void Worker::Stop() {
		m_worker_p->Stop();
	}

} // namespace cyberx
