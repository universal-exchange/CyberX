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

#ifndef CYBERX_SYSCFG_SYSCFG_H
#define CYBERX_SYSCFG_SYSCFG_H

#include <vector>
#include <stdint.h> // int32_t, int64_t

#include "global/compile.h"

namespace cyberx {

#pragma pack( push )
#pragma pack( 1 )

	struct CfgServer {
		int32_t m_work;
		int32_t m_port;
		int32_t m_flag;
		std::string m_type; // 主要是对 flag 的描述作用
	};

	struct CfgClient {
		int32_t m_work;
		std::string m_address;
		int32_t m_port;
		int32_t m_flag;
		std::string m_type; // 主要是对 flag 的描述作用
	};

	struct CfgPlugin {
		int32_t m_work;
		std::string m_name;
	};

	struct CfgBasic { // 目前未作初始化赋值，使用时请小心
		int32_t m_node_type;
	};

	struct CfgMaster { // 目前未作初始化赋值，使用时请小心
		int32_t m_work_thread;
		int32_t m_data_length;
		int32_t m_con_time_out;
		int32_t m_heart_check;
		int32_t m_debug_infos;
		int32_t m_max_msg_cache;
		int32_t m_con_max_server;
		std::vector<CfgServer> m_vec_server;
	};

	struct CfgWorker { // 目前未作初始化赋值，使用时请小心
		int32_t m_work_thread;
		int32_t m_data_length;
		int32_t m_con_time_out;
		int32_t m_heart_check;
		int32_t m_debug_infos;
		int32_t m_max_msg_cache;
		int32_t m_con_max_client;
		std::vector<CfgClient> m_vec_client;

		std::vector<CfgPlugin> m_vec_plugin;
	};

#pragma pack( pop )

	class SysCfg_P;

	class CYBERX_SYSCFG_EXPIMP SysCfg_S {
	public:
		SysCfg_S();
		~SysCfg_S();

	public:
		static SysCfg_S* GetInstance();

	public:
		void InitGlobalPath();
		std::string GetName_AppName();
		std::string GetPath_AppPath();
		std::string GetPath_CfgBasic();
		std::string GetPath_CfgMaster();
		std::string GetPath_CfgWorker();
		std::string GetPath_AppFolder();
		std::string GetPath_CfgFolder();
		std::string GetPath_PluFolder();
		std::string GetPath_ExtFolder();

		CfgBasic* GetCfgBasic();
		CfgMaster* GetCfgMaster();
		CfgWorker* GetCfgWorker();
		bool ReadCfgBasic( std::string file_path );
		bool ReadCfgMaster( std::string file_path );
		bool ReadCfgWorker( std::string file_path );

	private:
		SysCfg_P* m_syscfg_p;
		static SysCfg_S* m_instance;
	};

} // namespace cyberx

#endif // CYBERX_SYSCFG_SYSCFG_H
