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

#ifndef CYBERX_MASTER_MASTER_P_H
#define CYBERX_MASTER_MASTER_P_H

#include "struct.h"
#include "master.h"

namespace cyberx {

	class Master_P {
	public:
		Master_P();
		~Master_P();

	public:
		void LogPrint( basicx::syslog_level log_level, std::string& log_info, int32_t log_show = 0 );

	public:
		void Start();
		void Stop();

	private:
		std::string m_log_cate;
		basicx::SysLog_S* m_syslog;
		cyberx::SysCfg_S* m_syscfg;
	};

} // namespace cyberx

#endif // CYBERX_MASTER_MASTER_P_H
