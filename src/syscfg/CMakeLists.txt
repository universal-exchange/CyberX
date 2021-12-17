
# Copyright (c) 2021-2022 the CyberX authors
# All rights reserved.
#
# The project sponsor and lead author is Xu Rendong.
# E-mail: xrd@ustc.edu, QQ: 277195007, WeChat: xrd_ustc
# See the contributors file for names of other contributors.
#
# Commercial use of this code in source and binary forms is
# governed by a LGPL v3 license. You may get a copy from the
# root directory. Or else you should get a specific written 
# permission from the project author.
#
# Individual and educational use of this code in source and
# binary forms is governed by a 3-clause BSD license. You may
# get a copy from the root directory. Certainly welcome you
# to contribute code of all sorts.
#
# Be sure to retain the above copyright notice and conditions.

INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS} "${SDKDIR_BASICX_INCLUDE}" "${PROJECT_SOURCE_DIR}")

# Boost 的附加库目录会自动添加
IF (CMAKE_LINKTYPE_SHARED)
    IF (MSVC)
		SET (CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /LIBPATH:\"${PROJECT_BINARY_DIR}/archive/${PATH_FLAG_MIDFOLDER}\"")
		SET (CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LIBPATH:\"${PROJECT_BINARY_DIR}/archive/${PATH_FLAG_MIDFOLDER}\"")
		SET (CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /LIBPATH:\"${SDKDIR_BASICX_LIBRARY_DEBUG}\"")
        SET (CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LIBPATH:\"${SDKDIR_BASICX_LIBRARY_RELEASE}\"")
    ELSE ()
	    # Linux 下需要添加 "${PROJECT_BINARY_DIR}" 不然找不到 build 目录中的 libtcmalloc.a 库文件，且动态库是生成到 library 目录的
		LINK_DIRECTORIES ("${PROJECT_BINARY_DIR}" "${SDKDIR_BASICX_LIBRARY}" "${PROJECT_BINARY_DIR}/archive" "${PROJECT_BINARY_DIR}/library")
    ENDIF ()
ENDIF ()

FILE (GLOB SYSCFG_HEADER_FILES "./*.h")
FILE (GLOB SYSCFG_SOURCE_FILES "./*.cpp")

SOURCE_GROUP ("Header Files" FILES ${SYSCFG_HEADER_FILES})
SOURCE_GROUP ("Source Files" FILES ${SYSCFG_SOURCE_FILES})

IF (CMAKE_LINKTYPE_SHARED)
    ADD_LIBRARY ("syscfg" SHARED ${SYSCFG_HEADER_FILES} ${SYSCFG_SOURCE_FILES})
    IF (WIN32)
        TARGET_LINK_LIBRARIES ("syscfg" common.lib)
    ELSEIF ((UNIX) OR (APPLE))
        TARGET_LINK_LIBRARIES ("syscfg" libcommon.a)
    ENDIF ()
ELSE ()
    ADD_LIBRARY ("syscfg" ${SYSCFG_HEADER_FILES} ${SYSCFG_SOURCE_FILES})
ENDIF ()
