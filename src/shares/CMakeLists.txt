
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

INCLUDE_DIRECTORIES ("${SDKDIR_BASICX_INCLUDE}" "${PROJECT_SOURCE_DIR}") # <common/sysdef.h>

FILE (GLOB SHARES_HEADER_FILES "./*.h")
FILE (GLOB SHARES_SOURCE_FILES "./*.cpp")

SOURCE_GROUP ("Header Files" FILES ${SHARES_HEADER_FILES})
SOURCE_GROUP ("Source Files" FILES ${SHARES_SOURCE_FILES})

IF (CMAKE_LINKTYPE_SHARED)
    ADD_LIBRARY ("shares" SHARED ${SHARES_HEADER_FILES} ${SHARES_SOURCE_FILES})
ELSE ()
    ADD_LIBRARY ("shares" ${SHARES_HEADER_FILES} ${SHARES_SOURCE_FILES})
ENDIF ()
