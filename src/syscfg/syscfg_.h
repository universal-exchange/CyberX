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

#ifndef CYBERX_SYSCFG_SYSCFG_P_H
#define CYBERX_SYSCFG_SYSCFG_P_H

#include "syscfg.h"

namespace cyberx {

	class SysCfg_P {
	public:
		SysCfg_P();
		~SysCfg_P();

	public:
		std::string m_name_app_name;
		std::string m_path_app_path;
		std::string m_path_cfg_basic;
		std::string m_path_cfg_master;
		std::string m_path_cfg_worker;
		std::string m_path_app_folder;
		std::string m_path_cfg_folder;
		std::string m_path_plu_folder;
		std::string m_path_ext_folder;

		CfgBasic m_cfg_basic;
		CfgMaster m_cfg_master;
		CfgWorker m_cfg_worker;
	};

} // namespace cyberx

#endif // CYBERX_SYSCFG_SYSCFG_P_H
