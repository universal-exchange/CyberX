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

#include <ctime>

#include <common/sysdef.h>
#include <common/assist.h>
#include <common/PugiXml/pugixml.hpp>

#ifdef __OS_WINDOWS__
#include <windows.h>
#endif

#ifdef __OS_LINUX__
#define MAX_PATH 260
#endif

#include "syscfg_.h"

namespace cyberx {

	SysCfg_S* SysCfg_S::m_instance = nullptr;

	SysCfg_P::SysCfg_P()
		: m_name_app_name( "" )
		, m_path_app_path( "" )
		, m_path_cfg_basic( "" )
		, m_path_cfg_master( "" )
		, m_path_cfg_worker( "" )
		, m_path_app_folder( "" )
		, m_path_cfg_folder( "" )
		, m_path_plu_folder( "" )
		, m_path_ext_folder( "" ) {
	}

	SysCfg_P::~SysCfg_P() {
	}

	SysCfg_S::SysCfg_S()
		: m_syscfg_p( nullptr ) {
		try {
			m_syscfg_p = new SysCfg_P();
		}
		catch( ... ) {
		}
		m_instance = this;
	}

	SysCfg_S::~SysCfg_S() {
		if( m_syscfg_p != nullptr ) {
			delete m_syscfg_p;
			m_syscfg_p = nullptr;
		}
	}

	SysCfg_S* SysCfg_S::GetInstance() {
		return m_instance;
	}

	void SysCfg_S::InitGlobalPath() {
#ifdef __OS_WINDOWS__
		wchar_t char_path[MAX_PATH] = { 0 };
		GetModuleFileName( NULL, char_path, MAX_PATH );
		std::string app_exec_path = basicx::StringToAnsiChar( char_path );
		size_t slash_index = app_exec_path.rfind( '\\' );
		m_syscfg_p->m_name_app_name = app_exec_path.substr( slash_index + 1 );
		m_syscfg_p->m_path_app_path = app_exec_path;
		m_syscfg_p->m_path_app_folder = app_exec_path.substr( 0, slash_index );
		m_syscfg_p->m_path_cfg_basic = m_syscfg_p->m_path_app_folder + "\\config\\cfg_basic.ini";
		m_syscfg_p->m_path_cfg_master = m_syscfg_p->m_path_app_folder + "\\config\\cfg_master.ini";
		m_syscfg_p->m_path_cfg_worker = m_syscfg_p->m_path_app_folder + "\\config\\cfg_worker.ini";
		m_syscfg_p->m_path_cfg_folder = m_syscfg_p->m_path_app_folder + "\\config";
		m_syscfg_p->m_path_plu_folder = m_syscfg_p->m_path_app_folder + "\\plugin";
		m_syscfg_p->m_path_ext_folder = m_syscfg_p->m_path_app_folder + "\\extdll";
#endif
#ifdef __OS_LINUX__
		char char_path[MAX_PATH] = { 0 };
		// 在 linux 中 proc/pid/ 记录了进程号为 pid 的进程的一些临时文件，比如软连接，如要获取当前进程的路径只需将 pid 改为 self 即可
		readlink( "/proc/self/exe", char_path, MAX_PATH - 1 );
		std::string app_exec_path( char_path );
		size_t slash_index = app_exec_path.rfind( '/' );
		m_syscfg_p->m_name_app_name = app_exec_path.substr( slash_index + 1 );
		m_syscfg_p->m_path_app_path = app_exec_path;
		m_syscfg_p->m_path_app_folder = app_exec_path.substr( 0, slash_index );
		m_syscfg_p->m_path_cfg_basic = m_syscfg_p->m_path_app_folder + "/config/cfg_basic.ini";
		m_syscfg_p->m_path_cfg_master = m_syscfg_p->m_path_app_folder + "/config/cfg_master.ini";
		m_syscfg_p->m_path_cfg_worker = m_syscfg_p->m_path_app_folder + "/config/cfg_worker.ini";
		m_syscfg_p->m_path_cfg_folder = m_syscfg_p->m_path_app_folder + "/config";
		m_syscfg_p->m_path_plu_folder = m_syscfg_p->m_path_app_folder + "/plugin";
		m_syscfg_p->m_path_ext_folder = m_syscfg_p->m_path_app_folder + "/extdll";
#endif

#ifdef __OS_WINDOWS__
		wchar_t env_buf[4096] = { 0 };
		unsigned long size = GetEnvironmentVariable( L"path", env_buf, 4096 ); // Windows 环境变量名 不区分 大小写
		std::wstring env_paths = std::wstring( env_buf );
		if( std::wstring::npos == env_paths.find( basicx::StringToWideChar( m_syscfg_p->m_path_ext_folder ) ) ) { // 不存在 // 不判断也可以，添加的环境变量仅存在于程序运行时
			env_paths.append( L";" );
			env_paths.append( basicx::StringToWideChar( m_syscfg_p->m_path_ext_folder ) );
			env_paths.append( L";" );
			bool result = SetEnvironmentVariable( L"path", env_paths.c_str() );
		}
#endif
#ifdef __OS_LINUX__
		std::string env_paths = "";
		char* env_buf = getenv( "PATH" ); // Linux 环境变量名 区分 大小写
		if( env_buf != nullptr ) {
			env_paths = std::string( env_buf );
			env_paths.append( ":" );
		}
		if( std::string::npos == env_paths.find( m_syscfg_p->m_path_ext_folder ) ) { // 不存在 // 不判断也可以，添加的环境变量仅存在于程序运行时
			env_paths.append( m_syscfg_p->m_path_ext_folder );
			int32_t result = setenv( "PATH", env_paths.c_str(), 1 ); // 成功返回0，失败返回-1
		}
#endif
	}

	std::string SysCfg_S::GetName_AppName() {
		return m_syscfg_p->m_name_app_name;
	}

	std::string SysCfg_S::GetPath_AppPath() {
		return m_syscfg_p->m_path_app_path;
	}

	std::string SysCfg_S::GetPath_CfgBasic() {
		return m_syscfg_p->m_path_cfg_basic;
	}

	std::string SysCfg_S::GetPath_CfgMaster() {
		return m_syscfg_p->m_path_cfg_master;
	}

	std::string SysCfg_S::GetPath_CfgWorker() {
		return m_syscfg_p->m_path_cfg_worker;
	}

	std::string SysCfg_S::GetPath_AppFolder() {
		return m_syscfg_p->m_path_app_folder;
	}

	std::string SysCfg_S::GetPath_CfgFolder() {
		return m_syscfg_p->m_path_cfg_folder;
	}

	std::string SysCfg_S::GetPath_PluFolder() {
		return m_syscfg_p->m_path_plu_folder;
	}

	std::string SysCfg_S::GetPath_ExtFolder() {
		return m_syscfg_p->m_path_ext_folder;
	}

	CfgBasic* SysCfg_S::GetCfgBasic() {
		return &( m_syscfg_p->m_cfg_basic );
	}

	CfgMaster* SysCfg_S::GetCfgMaster() {
		return &( m_syscfg_p->m_cfg_master );
	}

	CfgWorker* SysCfg_S::GetCfgWorker() {
		return &( m_syscfg_p->m_cfg_worker );
	}

	bool SysCfg_S::ReadCfgBasic( std::string file_path ) {
		pugi::xml_document document;
		if( !document.load_file( file_path.c_str() ) ) {
			return false;
		}

		pugi::xml_node node_config = document.document_element();
		if( node_config.empty() ) {
			return false;
		}

		m_syscfg_p->m_cfg_basic.m_node_type = atoi( node_config.child_value( "NodeType" ) );

		return true;
	}

	bool SysCfg_S::ReadCfgMaster( std::string file_path ) {
		pugi::xml_document document;
		if( !document.load_file( file_path.c_str() ) ) {
			return false;
		}

		pugi::xml_node node_config = document.document_element();
		if( node_config.empty() ) {
			return false;
		}

		pugi::xml_node node_net_server = node_config.child( "NetServer" );
		if( node_net_server ) {
			m_syscfg_p->m_cfg_master.m_work_thread = atoi( node_net_server.child_value( "WorkThread" ) );
			m_syscfg_p->m_cfg_master.m_data_length = atoi( node_net_server.child_value( "DataLength" ) );
			m_syscfg_p->m_cfg_master.m_con_time_out = atoi( node_net_server.child_value( "ConTimeOut" ) );
			m_syscfg_p->m_cfg_master.m_heart_check = atoi( node_net_server.child_value( "HeartCheck" ) );
			m_syscfg_p->m_cfg_master.m_debug_infos = atoi( node_net_server.child_value( "DebugInfos" ) );
			m_syscfg_p->m_cfg_master.m_max_msg_cache = atoi( node_net_server.child_value( "MaxMsgCache" ) );
			m_syscfg_p->m_cfg_master.m_con_max_server = atoi( node_net_server.child_value( "ConMaxServer" ) );
			for( pugi::xml_node child_node_net_server = node_net_server.first_child(); !child_node_net_server.empty(); child_node_net_server = child_node_net_server.next_sibling() ) {
				if( "Server" == std::string( child_node_net_server.name() ) ) {
					CfgServer cfg_server;
					cfg_server.m_work = child_node_net_server.attribute( "Work" ).as_int();
					cfg_server.m_port = child_node_net_server.attribute( "Port" ).as_int();
					cfg_server.m_flag = child_node_net_server.attribute( "Flag" ).as_int();
					cfg_server.m_type = child_node_net_server.attribute( "Type" ).value();
					m_syscfg_p->m_cfg_master.m_vec_server.push_back( cfg_server );
				}
			}
		}

		return true;
	}

	bool SysCfg_S::ReadCfgWorker( std::string file_path ) {
		pugi::xml_document document;
		if( !document.load_file( file_path.c_str() ) ) {
			return false;
		}

		pugi::xml_node node_config = document.document_element();
		if( node_config.empty() ) {
			return false;
		}

		pugi::xml_node node_net_client = node_config.child( "NetClient" );
		if( node_net_client ) {
			m_syscfg_p->m_cfg_worker.m_work_thread = atoi( node_net_client.child_value( "WorkThread" ) );
			m_syscfg_p->m_cfg_worker.m_data_length = atoi( node_net_client.child_value( "DataLength" ) );
			m_syscfg_p->m_cfg_worker.m_con_time_out = atoi( node_net_client.child_value( "ConTimeOut" ) );
			m_syscfg_p->m_cfg_worker.m_heart_check = atoi( node_net_client.child_value( "HeartCheck" ) );
			m_syscfg_p->m_cfg_worker.m_debug_infos = atoi( node_net_client.child_value( "DebugInfos" ) );
			m_syscfg_p->m_cfg_worker.m_max_msg_cache = atoi( node_net_client.child_value( "MaxMsgCache" ) );
			m_syscfg_p->m_cfg_worker.m_con_max_client = atoi( node_net_client.child_value( "ConMaxClient" ) );
			for( pugi::xml_node child_node_net_client = node_net_client.first_child(); !child_node_net_client.empty(); child_node_net_client = child_node_net_client.next_sibling() ) {
				if( "Client" == std::string( child_node_net_client.name() ) ) {
					CfgClient cfg_client;
					cfg_client.m_work = child_node_net_client.attribute( "Work" ).as_int();
					cfg_client.m_address = child_node_net_client.attribute( "Addr" ).value();
					cfg_client.m_port = child_node_net_client.attribute( "Port" ).as_int();
					cfg_client.m_flag = child_node_net_client.attribute( "Flag" ).as_int();
					cfg_client.m_type = child_node_net_client.attribute( "Type" ).value();
					m_syscfg_p->m_cfg_worker.m_vec_client.push_back( cfg_client );
				}
			}
		}

		pugi::xml_node node_plugins = node_config.child( "Plugins" );
		if( node_plugins ) {
			for( pugi::xml_node child_node_plugins = node_plugins.first_child(); !child_node_plugins.empty(); child_node_plugins = child_node_plugins.next_sibling() ) {
				if( "Plugin" == std::string( child_node_plugins.name() ) ) {
					CfgPlugin cfg_plugin;
					cfg_plugin.m_work = child_node_plugins.attribute( "Work" ).as_int();
					cfg_plugin.m_name = child_node_plugins.attribute( "Name" ).value();
					m_syscfg_p->m_cfg_worker.m_vec_plugin.push_back( cfg_plugin );
				}
			}
		}

		return true;
	}

} // namespace cyberx
