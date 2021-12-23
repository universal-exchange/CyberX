
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

PROJECT (cyberx LANGUAGES CXX)

CMAKE_MINIMUM_REQUIRED (VERSION 3.14)

SET_PROPERTY (GLOBAL PROPERTY USE_FOLDERS ON)

OPTION (CMAKE_PLATFORM_X64 "platform x86 or x64." ON) # 启用则 64 位，禁用则 32 位
OPTION (CMAKE_LINKTYPE_SHARED "link type shared or static." ON) # 启用则动态链接，禁用则静态链接
OPTION (CMAKE_COMPILE_RELEASE "compile release or debug." ON) # 启用则 release 版，禁用则 debug 版
# 在 Windows 下通过 VS Code 的 CMake 插件生成的项目在 build 的 archive、library、runtime 没有 Release 和 Debug 这一层文件夹
# 但 Windows 下通过 cmake-gui.exe 程序生成的项目在 build 的 archive、library、runtime 会有 Release 和 Debug 这一层文件夹
OPTION (CMAKE_VS_CODE_PLUGIN "generate by vs code cmake plugin." OFF) # 启用则 无 Release 和 Debug，禁用则 有 Release 和 Debug，仅对 Windows 有效

# 目前只允许 link=shared runtime-link=shared (DLL MD/MDd) 和 link=static runtime-link=static (LIB MT/MTd) 两种
IF (CMAKE_PLATFORM_X64)
    SET (PATH_FLAG_PLATFORM "x64")
ELSE ()
    SET (PATH_FLAG_PLATFORM "x86")
ENDIF ()
IF (CMAKE_LINKTYPE_SHARED)
    SET (PATH_FLAG_BINORLIB "bin")
    SET (PATH_FLAG_LINKTYPE "shared")
ELSE ()
    SET (PATH_FLAG_BINORLIB "lib")
    SET (PATH_FLAG_LINKTYPE "static")
ENDIF ()
IF (CMAKE_COMPILE_RELEASE)
    SET (PATH_FLAG_COMPILE "release")
ELSE ()
    SET (PATH_FLAG_COMPILE "debug")
ENDIF ()
IF (CMAKE_VS_CODE_PLUGIN)
    SET (PATH_FLAG_MIDFOLDER "")
ELSE ()
    IF (CMAKE_COMPILE_RELEASE)
        SET (PATH_FLAG_MIDFOLDER "Release")
    ELSE ()
        SET (PATH_FLAG_MIDFOLDER "Debug")
    ENDIF ()
ENDIF ()

IF (WIN32)
    SET (SDKDIR_PATH_W "D:/SDK/GitHub/VS2017" CACHE PATH "sdk dir." FORCE)
    SET (SDKDIR_BASICX "${SDKDIR_PATH_W}/BasicX" CACHE PATH "basicx dir." FORCE)
    SET (SDKDIR_BASICX_INCLUDE "${SDKDIR_PATH_W}/BasicX/utf8/${PATH_FLAG_PLATFORM}/include" CACHE PATH "basicx include dir." FORCE)
    SET (SDKDIR_BASICX_LIBRARY_DEBUG "${SDKDIR_PATH_W}/BasicX/utf8/${PATH_FLAG_PLATFORM}/${PATH_FLAG_BINORLIB}/${PATH_FLAG_LINKTYPE}/debug" CACHE PATH "basicx library debug dir." FORCE)
    SET (SDKDIR_BASICX_LIBRARY_RELEASE "${SDKDIR_PATH_W}/BasicX/utf8/${PATH_FLAG_PLATFORM}/${PATH_FLAG_BINORLIB}/${PATH_FLAG_LINKTYPE}/release" CACHE PATH "basicx library release dir." FORCE)
    SET (SDKDIR_FMT_INCLUDE "${SDKDIR_PATH_W}/fmt/8.0.0/include" CACHE PATH "fmt include dir." FORCE)
    SET (SDKDIR_NUMCPP_INCLUDE "${SDKDIR_PATH_W}/NumCpp/2.4.2/include" CACHE PATH "NumCpp include dir." FORCE)
    SET (SDKDIR_EIGEN_INCLUDE "${SDKDIR_PATH_W}/Eigen/3.3.9" CACHE PATH "Eigen include dir." FORCE)
    SET (SDKDIR_EIGEN_UNSUPPORTED_INCLUDE "${SDKDIR_PATH_W}/Eigen/3.3.9/unsupported" CACHE PATH "Eigen unsupported include dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE "D:/Python36/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY "D:/Python36/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE_36 "D:/Python36/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY_36 "D:/Python36/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE_37 "D:/Python37/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY_37 "D:/Python37/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE_38 "D:/Python38/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY_38 "D:/Python38/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE_39 "D:/Python39/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY_39 "D:/Python39/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE_310 "D:/Python310/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY_310 "D:/Python310/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYBIND_INCLUDE "${SDKDIR_PATH_W}/pybind11/2.6.0/include" CACHE PATH "pybind include dir." FORCE)
    SET (SDKDIR_NODE_INCLUDE "${SDKDIR_PATH_W}/Node/14.18.0/include" CACHE PATH "node include dir." FORCE)
    SET (SDKDIR_NODE_LIBRARY_DEBUG "${SDKDIR_PATH_W}/Node/14.18.0/${PATH_FLAG_BINORLIB}/${PATH_FLAG_LINKTYPE}/debug" CACHE PATH "node library debug dir." FORCE)
    SET (SDKDIR_NODE_LIBRARY_RELEASE "${SDKDIR_PATH_W}/Node/14.18.0/${PATH_FLAG_BINORLIB}/${PATH_FLAG_LINKTYPE}/release" CACHE PATH "node library release dir." FORCE)
ELSEIF ((UNIX) OR (APPLE))
    SET (SDKDIR_PATH_L "/usr/local/SDK/GCC_910" CACHE PATH "sdk dir." FORCE)
    SET (SDKDIR_BASICX "${SDKDIR_PATH_L}/BasicX" CACHE PATH "basicx dir." FORCE)
    SET (SDKDIR_BASICX_INCLUDE "${SDKDIR_PATH_L}/BasicX/${PATH_FLAG_PLATFORM}/include" CACHE PATH "basicx include dir." FORCE)
    SET (SDKDIR_BASICX_LIBRARY "${SDKDIR_PATH_L}/BasicX/${PATH_FLAG_PLATFORM}/${PATH_FLAG_BINORLIB}/${PATH_FLAG_LINKTYPE}/release" CACHE PATH "basicx library release dir." FORCE)
    SET (SDKDIR_FMT_INCLUDE "${SDKDIR_PATH_L}/fmt/8.0.0/include" CACHE PATH "fmt include dir." FORCE)
    SET (SDKDIR_NUMCPP_INCLUDE "${SDKDIR_PATH_L}/NumCpp/2.4.2/include" CACHE PATH "NumCpp include dir." FORCE)
    SET (SDKDIR_EIGEN_INCLUDE "${SDKDIR_PATH_L}/Eigen/3.3.9" CACHE PATH "Eigen include dir." FORCE)
    SET (SDKDIR_EIGEN_UNSUPPORTED_INCLUDE "${SDKDIR_PATH_L}/Eigen/3.3.9/unsupported" CACHE PATH "Eigen unsupported include dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE "/usr/local/python36/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY "/usr/local/python36/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE_36 "/usr/local/python36/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY_36 "/usr/local/python36/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE_37 "/usr/local/python37/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY_37 "/usr/local/python37/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE_38 "/usr/local/python38/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY_38 "/usr/local/python38/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE_39 "/usr/local/python39/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY_39 "/usr/local/python39/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYTHON_INCLUDE_310 "/usr/local/python310/include" CACHE PATH "python include dir." FORCE)
    SET (SDKDIR_PYTHON_LIBRARY_310 "/usr/local/python310/libs" CACHE PATH "python library dir." FORCE)
    SET (SDKDIR_PYBIND_INCLUDE "${SDKDIR_PATH_L}/pybind11/2.6.0/include" CACHE PATH "pybind include dir." FORCE)
    SET (SDKDIR_NODE_INCLUDE "${SDKDIR_PATH_L}/Node/14.18.0/include" CACHE PATH "node include dir." FORCE)
    SET (SDKDIR_NODE_LIBRARY_DEBUG "${SDKDIR_PATH_L}/Node/14.18.0/${PATH_FLAG_BINORLIB}/${PATH_FLAG_LINKTYPE}/debug" CACHE PATH "node library debug dir." FORCE)
    SET (SDKDIR_NODE_LIBRARY_RELEASE "${SDKDIR_PATH_L}/Node/14.18.0/${PATH_FLAG_BINORLIB}/${PATH_FLAG_LINKTYPE}/release" CACHE PATH "node library release dir." FORCE)
ENDIF ()

SET (CYBERX_VERSION_MAJOR 0)
SET (CYBERX_VERSION_MINOR 1)
SET (CYBERX_VERSION_PATCH 0)

IF (WIN32)
    # SET (CMAKE_C_COMPILER "D:/VS 2017/VC/bin/x86_amd64")
    # SET (CMAKE_CXX_COMPILER "D:/VS 2017/VC/bin/x86_amd64")
ELSEIF ((UNIX) OR (APPLE))
    # SET (CMAKE_C_COMPILER "/usr/local/gcc-9.1.0/bin/gcc")
    # SET (CMAKE_CXX_COMPILER "/usr/local/gcc-9.1.0/bin/g++")
ENDIF ()

INCLUDE (CheckCXXCompilerFlag)
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC") # VS C++
    # ON by default, if available
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel") # Intel C++
    # ON by default, if available
ELSE () # GCC or Clang
    CHECK_CXX_COMPILER_FLAG ("-std=c++20" COMPILER_SUPPORTS_CXX20)
    CHECK_CXX_COMPILER_FLAG ("-std=c++17" COMPILER_SUPPORTS_CXX17)
    CHECK_CXX_COMPILER_FLAG ("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
    CHECK_CXX_COMPILER_FLAG ("-std=c++14" COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG ("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
    CHECK_CXX_COMPILER_FLAG ("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG ("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    # IF (COMPILER_SUPPORTS_CXX20)
    #     IF (CMAKE_COMPILER_IS_GNUCXX)
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++20")
    #     ELSE ()
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
    #     ENDIF ()
    IF (COMPILER_SUPPORTS_CXX17)
        IF (CMAKE_COMPILER_IS_GNUCXX)
            SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
        ELSE ()
            SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
        ENDIF ()
    # ELSEIF (COMPILER_SUPPORTS_CXX1Z)
    #     IF (CMAKE_COMPILER_IS_GNUCXX)
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z")
    #     ELSE ()
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
    #     ENDIF ()
    # ELSEIF (COMPILER_SUPPORTS_CXX14)
    #     IF (CMAKE_COMPILER_IS_GNUCXX)
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
    #     ELSE ()
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    #     ENDIF ()
    # ELSEIF (COMPILER_SUPPORTS_CXX1Y)
    #     IF (CMAKE_COMPILER_IS_GNUCXX)
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1y")
    #     ELSE ()
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
    #     ENDIF ()
    # ELSEIF (COMPILER_SUPPORTS_CXX11)
    #     IF (CMAKE_COMPILER_IS_GNUCXX)
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    #     ELSE ()
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    #     ENDIF ()
    # ELSEIF (COMPILER_SUPPORTS_CXX0X)
    #     IF (CMAKE_COMPILER_IS_GNUCXX)
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
    #     ELSE ()
    #         SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    #     ENDIF ()
    ELSE () # at least C++17
        MESSAGE (STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
    ENDIF ()
ENDIF ()

MESSAGE (STATUS ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION} " " ${CMAKE_SYSTEM_PROCESSOR})

IF (CMAKE_COMPILE_RELEASE)
    SET (CMAKE_CONFIGURATION_TYPES "Release;" CACHE STRING "project type." FORCE) # Debug、Release、RelWithDebInfo、MinSizeRel
ELSE ()
    SET (CMAKE_CONFIGURATION_TYPES "Debug;" CACHE STRING "project type." FORCE) # Debug、Release、RelWithDebInfo、MinSizeRel
ENDIF ()

IF (WIN32)
    SET (CMAKE_INSTALL_PREFIX "I:/Project/CyberX/bin/windows" CACHE PATH "install prefix." FORCE)
    IF (CMAKE_PLATFORM_X64)
        SET (CMAKE_BOOST_ROOT "${SDKDIR_PATH_W}/Boost/1.70/x64" CACHE PATH "boost root." FORCE)
    ELSE ()
        SET (CMAKE_BOOST_ROOT "${SDKDIR_PATH_W}/Boost/1.70/x86" CACHE PATH "boost root." FORCE)
    ENDIF ()
ELSEIF ((UNIX) OR (APPLE))
    SET (CMAKE_INSTALL_PREFIX "/home/xrd/Project/CyberX/bin/linux" CACHE PATH "install prefix." FORCE)
    IF (CMAKE_PLATFORM_X64)
        SET (CMAKE_BOOST_ROOT "${SDKDIR_PATH_L}/Boost/1.70/x64" CACHE PATH "boost root." FORCE)
    ELSE ()
        SET (CMAKE_BOOST_ROOT "${SDKDIR_PATH_L}/Boost/1.70/x86" CACHE PATH "boost root." FORCE)
    ENDIF ()
ENDIF ()
SET (CMAKE_BOOST_VERSION "1.70.0" CACHE STRING "boost version." FORCE)
SET (BOOST_ROOT ${CMAKE_BOOST_ROOT})

IF (MSVC)
    # https://msdn.microsoft.com/en-us/library/fwkeyyhe.aspx
    IF (CMAKE_LINKTYPE_SHARED)
        SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd") # /MDd、/MTd
    ELSE ()
        SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd") # /MDd、/MTd
    ENDIF ()
    SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Ob0") # /Ob0、Ob1、Ob2
    SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Gm") # /Gm、/Gm-
    SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D \"_DEBUG\"") #
    IF (CMAKE_LINKTYPE_SHARED)
        SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD") # /MD、/MT
    ELSE ()
        SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT") # /MD、/MT
    ENDIF ()
    SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2") # /Od、/O1、/O2、/Ox
    SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ob2") # /Ob0、/Ob1、/Ob2
    SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi") # /Oi
    SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ot") # /Os、/Ot
    SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oy-") # /Oy、/Oy-
    SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL") # /GL
    SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Gy") # /Gy、/Gy-
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3") # /W0、/W1、/W2、/W3、/W4、/Wall
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi") # /Z7、/Zi、/ZI
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /sdl") # /sdl、/sdl-
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa") # /EHa、/EHs、/EHsc
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D \"_LIB\"") #
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D \"_CONSOLE\"") #
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8") # /validate-charset /source-charset:utf-8 /execution-charset:utf-8
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t") # /Zc:wchar_t、/Zc:wchar_t-
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D \"_UNICODE\" /D \"UNICODE\"") #
    # SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t /W3")
    # SET_TARGET_PROPERTIES (${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/Zc:wchar_t /W3")
    # ADD_DEFINITIONS ("/Zc:wchar_t /W3")
    SET (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF")
    SET (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:ICF")
    SET (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
    SET (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCLUDE:\"__tcmalloc\"")
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp") # OpenMP
ELSEIF (CMAKE_CXX_COMPILER_ID MATCHES "GNU") # GCC
    # SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2") # 编译优化 O0、O1、O2、O3、Os
    # SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native") # 基于当前 CPU 自动优化，可用 gcc -march=native -Q --help=target 查询具体项目
    IF (CMAKE_COMPILE_RELEASE)
        SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
        SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    # SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g") # 调试模式，保留代码等方便调试 -g、-ggdb、-gstabs、-gstabs+、-glevel
    ELSE ()
        SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    ENDIF ()
    SET (CMAKE_EXE_LINKER_FLAGS "-ldl") # dlopen 等
    SET (CMAKE_EXE_LINKER_FLAGS "-lrt") # clock_gettime 等
    SET (CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++") # 半静态方式编译
    # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W") # 编译后显示可能发生错误的警告 -w 小写关闭所有警告
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") # 编译后显示所有警告
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra") # 显示 忘记参数类型、指针与整数零的逻辑比较、有歧义的虚基类 等警告
    # SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror") # 将所有警告都当作编译失败
    # SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow") # 显开启则显示警告：局部变量覆盖参数或全局变量
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder") # 开启则不显示警告：类成员变量未按定义顺序初始化
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-char-subscripts") # 开启则不显示警告：使用 char 类作为数组下标(因为 char 可能是有符号数)
    # SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion") # 显开启则显示警告：隐式类型转换可能改变值
    # SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal") # 开启则显示警告：不安全的使用 == 和 != 来比较浮点数
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith") # 开启则显示警告：对函数指针或者 void* 进行算术操作
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings") # 开启则显示警告：修改 const 字符串
    # SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast") # 开启则显示警告：旧式强制类型转换
    # SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual") # 开启则显示警告：虚函数重载
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable") # 开启则不显示警告：未使用的变量
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter") # 开启则不显示警告：未使用的函数参数
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-fallthrough") # 开启则不显示警告：控制流跌落，比如忘记添加 break 语句等
    # SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MMD") # -M -MM -MD -MMD
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCHECK_PTHREAD_RETURN_VALUE") # 添加 #define CHECK_PTHREAD_RETURN_VALUE 宏检测线程返回值
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FILE_OFFSET_BITS=64") # 添加 #define _FILE_OFFSET_BITS=64 宏用于读写 2G 以上大文件
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic") # 通知链接器将所有符号添加到动态符号表中
    # SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps") # 生成 .i 和 .s 中间文件用于查看预处理器结果和汇编指令代码
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free") # tcmalloc 相关
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden") # 默认所有函数隐藏，用于动态链接时指定函数导出
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp") # OpenMP
ELSEIF (CMAKE_CXX_COMPILER_ID MATCHES "Clang") # Clang
    # TODO:
ELSEIF (CMAKE_CXX_COMPILER_ID MATCHES "Intel") # Intel C++
    # TODO:
ENDIF ()

# SEND_ERROR、STATUS、FATAL_ERROR
MESSAGE (STATUS "project binary dir: " ${PROJECT_BINARY_DIR})
MESSAGE (STATUS "project source dir: " ${PROJECT_SOURCE_DIR})

CONFIGURE_FILE (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )

# SET (Boost_DEBUG 1)
IF (WIN32)
    SET (Boost_COMPILER "-vc141")
    IF (CMAKE_PLATFORM_X64)
        # SET (BOOST_ROOT "${SDKDIR_PATH_W}/Boost/1.70/x64") # 1
        # SET (BOOST_INCLUDEDIR "${SDKDIR_PATH_W}/Boost/1.70/x64") # 1
        # SET (BOOST_LIBRARYDIR "${SDKDIR_PATH_W}/Boost/1.70/x64/stage/lib") # 1
    ELSE ()
        # SET (BOOST_ROOT "${SDKDIR_PATH_W}/Boost/1.70/x86") # 1
        # SET (BOOST_INCLUDEDIR "${SDKDIR_PATH_W}/Boost/1.70/x86") # 1
        # SET (BOOST_LIBRARYDIR "${SDKDIR_PATH_W}/Boost/1.70/x86/stage/lib") # 1
    ENDIF ()
ELSEIF ((UNIX) OR (APPLE))
    SET (Boost_COMPILER "-gcc9") # 注意这里根据编译得到的 Boost 库文件名作调整
    IF (CMAKE_PLATFORM_X64)
        # SET (BOOST_ROOT "${SDKDIR_PATH_L}/Boost/1.70/x64") # 1
        # SET (BOOST_INCLUDEDIR "${SDKDIR_PATH_L}/Boost/1.70/x64") # 1
        # SET (BOOST_LIBRARYDIR "${SDKDIR_PATH_L}/Boost/1.70/x64/stage/lib") # 1
    ELSE ()
        # SET (BOOST_ROOT "${SDKDIR_PATH_L}/Boost/1.70/x86") # 1
        # SET (BOOST_INCLUDEDIR "${SDKDIR_PATH_L}/Boost/1.70/x86") # 1
        # SET (BOOST_LIBRARYDIR "${SDKDIR_PATH_L}/Boost/1.70/x86/stage/lib") # 1
    ENDIF ()
ENDIF ()
# 测试显示 Boost 1.69 和 1.70 需要指明 ARCHITECTURE 具体看编译得到的库文件名是否含 -x64 或 -x32
IF (CMAKE_PLATFORM_X64)
    SET (Boost_ARCHITECTURE "-x64") # 2
ELSE ()
    SET (Boost_ARCHITECTURE "-x32") # 2
ENDIF ()
SET (Boost_USE_STATIC_LIBS ON) # 2
SET (Boost_USE_MULTITHREADED ON) # 2
SET (Boost_USE_STATIC_RUNTIME OFF) # 2
SET (Boost_USE_DEBUG_LIBS OFF) # 2
SET (Boost_USE_DEBUG_RUNTIME OFF) # 2
FIND_PACKAGE (Boost ${CMAKE_BOOST_VERSION} REQUIRED system random) # 3
MESSAGE (STATUS "boost include path: " ${Boost_INCLUDE_DIRS})
MESSAGE (STATUS "boost library path: " ${Boost_LIBRARY_DIRS})
# MESSAGE (STATUS "boost library list: " ${Boost_LIBRARIES})
INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES (${Boost_LIBRARY_DIRS})

FILE (MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/archive" "${PROJECT_BINARY_DIR}/library" "${PROJECT_BINARY_DIR}/runtime")
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/archive")
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/library")
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/runtime")

IF (WIN32)
    FILE (COPY "${SDKDIR_BASICX_LIBRARY_RELEASE}/libtcmalloc.lib" DESTINATION ${PROJECT_BINARY_DIR})
ELSEIF ((UNIX) OR (APPLE))
    FILE (COPY "${SDKDIR_BASICX_LIBRARY}/libtcmalloc.a" DESTINATION ${PROJECT_BINARY_DIR})
ENDIF ()

FILE (GLOB CYBERX_HEADER_FILES "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.h")
FILE (GLOB CYBERX_SOURCE_FILES "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/*.cpp")
SOURCE_GROUP ("Header Files" FILES ${CYBERX_HEADER_FILES})
SOURCE_GROUP ("Source Files" FILES ${CYBERX_SOURCE_FILES})

ADD_SUBDIRECTORY ("${PROJECT_SOURCE_DIR}/global")
ADD_SUBDIRECTORY ("${PROJECT_SOURCE_DIR}/master")
ADD_SUBDIRECTORY ("${PROJECT_SOURCE_DIR}/shares")
ADD_SUBDIRECTORY ("${PROJECT_SOURCE_DIR}/syscfg")
ADD_SUBDIRECTORY ("${PROJECT_SOURCE_DIR}/worker")
# ADD_SUBDIRECTORY ("${PROJECT_SOURCE_DIR}/plugin")
# ADD_SUBDIRECTORY ("${PROJECT_SOURCE_DIR}/cyberx_js")
# ADD_SUBDIRECTORY ("${PROJECT_SOURCE_DIR}/cyberx_py")
# ADD_SUBDIRECTORY ("${PROJECT_SOURCE_DIR}/cyberx_xl")

INCLUDE_DIRECTORIES ("${PROJECT_SOURCE_DIR}" "${SDKDIR_BASICX_INCLUDE}")

IF (WIN32)
    # Windows 下貌似会自动把 build 目录添加进查找路径，不添加 "${PROJECT_BINARY_DIR}" 也可以
    LINK_DIRECTORIES ("${PROJECT_BINARY_DIR}/archive")
ELSEIF ((UNIX) OR (APPLE))
    # Linux 下需要添加 "${PROJECT_BINARY_DIR}" 不然找不到 build 目录中的 libtcmalloc.a 库文件，且动态库是生成到 library 目录的
    LINK_DIRECTORIES ("/usr/lib64" "/usr/local/lib" "${PROJECT_BINARY_DIR}" "${PROJECT_BINARY_DIR}/archive" "${PROJECT_BINARY_DIR}/library")
ENDIF ()
IF (CMAKE_CXX_COMPILER_ID MATCHES "MSVC") # VS C++
    SET (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /LIBPATH:\"${SDKDIR_BASICX_LIBRARY_DEBUG}\"")
    SET (CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LIBPATH:\"${SDKDIR_BASICX_LIBRARY_RELEASE}\"")
ELSEIF (CMAKE_CXX_COMPILER_ID MATCHES "GNU") # GCC
    LINK_DIRECTORIES ("${SDKDIR_BASICX_LIBRARY}")
ELSEIF (CMAKE_CXX_COMPILER_ID MATCHES "Clang") # Clang
    # TODO：
ELSEIF (CMAKE_CXX_COMPILER_ID MATCHES "Intel") # Intel C++
    # TODO：
ENDIF ()

ADD_EXECUTABLE (${PROJECT_NAME} ${CYBERX_HEADER_FILES} ${CYBERX_SOURCE_FILES})

IF (WIN32)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} libtcmalloc.lib common.lib syslog.lib plugins.lib global.lib shares.lib syscfg.lib master.lib worker.lib)
ELSEIF ((UNIX) OR (APPLE))
    SET (THREADS_PREFER_PTHREAD_FLAG ON)
    FIND_PACKAGE (Threads REQUIRED)
    TARGET_LINK_LIBRARIES (${PROJECT_NAME} Threads::Threads) # -pthread
    # TARGET_LINK_LIBRARIES (${PROJECT_NAME} ${Boost_LIBRARIES}) # Linux 下显式添加 FIND_PACKAGE 中列出的 Boost 库
    IF (CMAKE_LINKTYPE_SHARED)
        TARGET_LINK_LIBRARIES (${PROJECT_NAME} -lunwind -ltcmalloc libcommon.a -lsyslog -lplugins -lglobal -lshares -lsyscfg -lmaster -lworker)
    ELSE ()
        TARGET_LINK_LIBRARIES (${PROJECT_NAME} libtcmalloc.a libcommon.a libsyslog.a libplugins.a libglobal.a libshares.a libsyscfg.a libmaster.a libworker.a)
    ENDIF ()
ENDIF ()

FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/config")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_36/Lib/site-packages/cyberx")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_37/Lib/site-packages/cyberx")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_38/Lib/site-packages/cyberx")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_39/Lib/site-packages/cyberx")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_310/Lib/site-packages/cyberx")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/cyberx_xl")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/doc")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/etc")
FILE (MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/lib")

IF (WIN32)
    INSTALL (
        TARGETS ${PROJECT_NAME} 
        DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
    )
    INSTALL (
        FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/cyberx.exe" 
        DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
    )
#     INSTALL (
#         FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.bat" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_cyberx.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_stochastic_model.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_barrier_single.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_barrier_double.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_digital_simple.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_vanilla_american.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_vanilla_european.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_autocall_booster.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_autocall_phoenix.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_autocall_snowball.py" 
#         DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py"
#     )
#     INSTALL (
#         FILES "${PROJECT_SOURCE_DIR}/cyberx_js/setup.bat" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/package.json" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_cyberx.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_stochastic_model.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_barrier_single.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_barrier_double.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_digital_simple.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_vanilla_american.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_vanilla_european.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_autocall_booster.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_autocall_phoenix.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_autocall_snowball.js" 
#         DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js"
#     )
    IF (CMAKE_LINKTYPE_SHARED)
        INSTALL (
            FILES "${SDKDIR_BASICX_LIBRARY_RELEASE}/libtcmalloc.dll" 
                  "${SDKDIR_BASICX_LIBRARY_RELEASE}/syslog.dll" 
                  "${SDKDIR_BASICX_LIBRARY_RELEASE}/network.dll" 
                  "${SDKDIR_BASICX_LIBRARY_RELEASE}/plugins.dll" 
                  "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/global.dll" 
                  "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/shares.dll" 
                  "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/syscfg.dll" 
                  "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/master.dll" 
                  "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/worker.dll" 
            DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
        )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/cyberx_js.dll" RENAME "cyberx.node" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js"
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/cyberx_js.dll" RENAME "index.node" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js"
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/kernel.dll" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js"
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/cyberx_py.dll" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py"
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/cyberx_py_36.dll" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_36/Lib/site-packages/cyberx"
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/cyberx_py_37.dll" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_37/Lib/site-packages/cyberx"
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/cyberx_py_38.dll" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_38/Lib/site-packages/cyberx"
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/cyberx_py_39.dll" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_39/Lib/site-packages/cyberx"
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/cyberx_py_310.dll" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_310/Lib/site-packages/cyberx"
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/kernel.dll" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/__init__.py" 
#                   "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/kernel.dll" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_36/Lib/site-packages/cyberx"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/__init__.py" 
#                   "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/kernel.dll" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_37/Lib/site-packages/cyberx"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/__init__.py" 
#                   "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/kernel.dll" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_38/Lib/site-packages/cyberx"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/__init__.py" 
#                   "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/kernel.dll" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_39/Lib/site-packages/cyberx"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/__init__.py" 
#                   "${PROJECT_BINARY_DIR}/runtime/${PATH_FLAG_MIDFOLDER}/kernel.dll" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_310/Lib/site-packages/cyberx"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.py" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/cyberx_36/setup.bat" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_36"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.py" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/cyberx_37/setup.bat" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_37"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.py" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/cyberx_38/setup.bat" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_38"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.py" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/cyberx_39/setup.bat" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_39"
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.py" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/cyberx_310/setup.bat" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_310"
#         )
    ENDIF ()
    INSTALL (
        FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
              "${PROJECT_SOURCE_DIR}/../library.txt" 
              "${PROJECT_SOURCE_DIR}/../license.txt" 
              "${PROJECT_SOURCE_DIR}/../readme.md" 
        DESTINATION "${CMAKE_INSTALL_PREFIX}/doc"
    )
    INSTALL (
        FILES "${PROJECT_SOURCE_DIR}/config/cfg_basic.ini" 
              "${PROJECT_SOURCE_DIR}/config/cfg_master.ini" 
              "${PROJECT_SOURCE_DIR}/config/cfg_worker.ini" 
        DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/config"
    )
ELSEIF ((UNIX) OR (APPLE))
    INSTALL (
        TARGETS ${PROJECT_NAME} 
        DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
    )
    INSTALL ( # 独立安装获取执行权限
        FILES "${PROJECT_BINARY_DIR}/runtime/cyberx" 
        DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" 
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ # 755
    )
#     INSTALL (
#         FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.bat" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_cyberx.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_stochastic_model.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_barrier_single.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_barrier_double.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_digital_simple.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_vanilla_american.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_vanilla_european.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_autocall_booster.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_autocall_phoenix.py" 
#               "${PROJECT_SOURCE_DIR}/cyberx_py/test_autocall_snowball.py" 
#         DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py"
#         # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#     )
#     INSTALL (
#         FILES "${PROJECT_SOURCE_DIR}/cyberx_js/setup.bat" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/package.json" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_cyberx.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_stochastic_model.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_barrier_single.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_barrier_double.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_digital_simple.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_vanilla_american.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_vanilla_european.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_autocall_booster.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_autocall_phoenix.js" 
#               "${PROJECT_SOURCE_DIR}/cyberx_js/test_autocall_snowball.js" 
#         DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js"
#         # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#     )
    IF (CMAKE_LINKTYPE_SHARED)
        INSTALL (
            FILES "${SDKDIR_BASICX_LIBRARY}/libunwind.so.8" 
                  "${SDKDIR_BASICX_LIBRARY}/libtcmalloc.so" 
                  "${SDKDIR_BASICX_LIBRARY}/libsyslog.so" 
                  "${SDKDIR_BASICX_LIBRARY}/libnetwork.so" 
                  "${SDKDIR_BASICX_LIBRARY}/libplugins.so" 
                  "${PROJECT_BINARY_DIR}/library/libglobal.so" 
                  "${PROJECT_BINARY_DIR}/library/libshares.so" 
                  "${PROJECT_BINARY_DIR}/library/libsyscfg.so" 
                  "${PROJECT_BINARY_DIR}/library/libmaster.so" 
                  "${PROJECT_BINARY_DIR}/library/libworker.so" 
            DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
            # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
        )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/library/libcyberx_js.so" RENAME "cyberx.node" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/library/libcyberx_js.so" RENAME "index.node" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/library/libkernel.so" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_js"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/library/libcyberx_py.so" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/library/libcyberx_py_36.so" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_36/Lib/site-packages/cyberx"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/library/libcyberx_py_37.so" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_37/Lib/site-packages/cyberx"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/library/libcyberx_py_38.so" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_38/Lib/site-packages/cyberx"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/library/libcyberx_py_39.so" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_39/Lib/site-packages/cyberx"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/library/libcyberx_py_310.so" RENAME "cyberx.pyd" # RENAME 限单个文件
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_310/Lib/site-packages/cyberx"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_BINARY_DIR}/library/libkernel.so" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/__init__.py" 
#                   "${PROJECT_BINARY_DIR}/library/libkernel.so" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_36/Lib/site-packages/cyberx"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/__init__.py" 
#                   "${PROJECT_BINARY_DIR}/library/libkernel.so" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_37/Lib/site-packages/cyberx"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/__init__.py" 
#                   "${PROJECT_BINARY_DIR}/library/libkernel.so" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_38/Lib/site-packages/cyberx"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/__init__.py" 
#                   "${PROJECT_BINARY_DIR}/library/libkernel.so" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_39/Lib/site-packages/cyberx"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
#                   "${PROJECT_SOURCE_DIR}/../library.txt" 
#                   "${PROJECT_SOURCE_DIR}/../license.txt" 
#                   "${PROJECT_SOURCE_DIR}/../readme.md" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/__init__.py" 
#                   "${PROJECT_BINARY_DIR}/library/libkernel.so" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_310/Lib/site-packages/cyberx"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.py" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/cyberx_36/setup.bat" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_36"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.py" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/cyberx_37/setup.bat" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_37"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.py" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/cyberx_38/setup.bat" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_38"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.py" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/cyberx_39/setup.bat" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_39"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
#         INSTALL (
#             FILES "${PROJECT_SOURCE_DIR}/cyberx_py/setup.py" 
#                   "${PROJECT_SOURCE_DIR}/cyberx_py/cyberx_310/setup.bat" 
#             DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/cyberx_py/cyberx_310"
#             # PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE # 755
#         )
    ENDIF ()
    INSTALL (
        FILES "${PROJECT_SOURCE_DIR}/../changes.txt" 
              "${PROJECT_SOURCE_DIR}/../library.txt" 
              "${PROJECT_SOURCE_DIR}/../license.txt" 
              "${PROJECT_SOURCE_DIR}/../readme.md" 
        DESTINATION "${CMAKE_INSTALL_PREFIX}/doc" 
        # PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ # 644
    )
    INSTALL (
        FILES "${PROJECT_SOURCE_DIR}/config/cfg_basic.ini" 
              "${PROJECT_SOURCE_DIR}/config/cfg_master.ini" 
              "${PROJECT_SOURCE_DIR}/config/cfg_worker.ini" 
        DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/config" 
        # PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ # 644
    )
ENDIF ()
