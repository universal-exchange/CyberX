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

#ifndef CYBERX_WORKER_WORKER_H
#define CYBERX_WORKER_WORKER_H

#include "global/compile.h"

namespace cyberx {

	class Worker_P;

	class CYBERX_WORKER_EXPIMP Worker {
	public:
		Worker();
		~Worker();

	public:
		static Worker* GetInstance();

	public:
		void Start();
		void Stop();

	private:
		Worker_P* m_worker_p;
		static Worker* m_instance;
	};

} // namespace cyberx

#endif // CYBERX_WORKER_WORKER_H
