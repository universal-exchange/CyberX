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

#ifndef CYBERX_SYSCFG_TESTER_H
#define CYBERX_SYSCFG_TESTER_H

#include <string>
#include <iostream>

#include "syscfg.h"

namespace cyberx {

	void Test_SysCfg() {
		SysCfg_S g_syscfg; // 唯一实例 // 不可用 SysCfg_S g_syscfg(); 会导致构造函数未调用

		SysCfg_S* syscfg = SysCfg_S::GetInstance();
		syscfg->InitGlobalPath();

		std::cout << "AppName：" << syscfg->GetName_AppName() << std::endl;
		std::cout << "AppPath：" << syscfg->GetPath_AppPath() << std::endl;
		std::cout << "CfgBasic：" << syscfg->GetPath_CfgBasic() << std::endl;
		std::cout << "CfgMaster：" << syscfg->GetPath_CfgMaster() << std::endl;
		std::cout << "CfgWorker：" << syscfg->GetPath_CfgWorker() << std::endl;
		std::cout << "AppFolder：" << syscfg->GetPath_AppFolder() << std::endl;
		std::cout << "CfgFolder：" << syscfg->GetPath_CfgFolder() << std::endl;
		std::cout << "PluFolder：" << syscfg->GetPath_PluFolder() << std::endl;
		std::cout << "ExtFolder：" << syscfg->GetPath_ExtFolder() << std::endl;

		if( false == syscfg->ReadCfgBasic( syscfg->GetPath_CfgBasic() ) ) {
			std::cout << "读取 系统参数配置 失败！" << std::endl;
			return;
		}
		cyberx::CfgBasic* cfg_basic = syscfg->GetCfgBasic();
		std::cout << "node_type：" << cfg_basic->m_node_type << std::endl;
	}

} // namespace cyberx

#endif // CYBERX_SYSCFG_TESTER_H
