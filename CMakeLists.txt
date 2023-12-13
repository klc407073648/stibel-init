cmake_minimum_required(VERSION 3.5)
project(stibel-init CXX)

# drogon的find_package特殊处理
set(CMAKE_PREFIX_PATH   "${PROJECT_SOURCE_DIR}/lib/3partlib/lib64/cmake")
include(${PROJECT_SOURCE_DIR}/cmake/SpecialDeal.cmake)
# drogon的find_package特殊处理

# 是否使用函数统计
option(USE_FUN_STAT "Use function statistics" ON)
if(USE_FUN_STAT)
    message("USE_FUN_STAT:" ${USE_FUN_STAT})
    add_definitions(-DUSE_FUN_STAT)
    include(${PROJECT_SOURCE_DIR}/cmake/FunStat.cmake)
endif()
# 是否使用函数统计

# 依赖StiBel库的内容
## 选项
include(${PROJECT_SOURCE_DIR}/cmake/options.cmake)

## 3partlib和comlib
SET(3PART_PATH  ${PROJECT_SOURCE_DIR}/include/3partlib)
include(${PROJECT_SOURCE_DIR}/cmake/3partlib.cmake)

SET(COMM_PATH   ${PROJECT_SOURCE_DIR}/include/comlib)
include(${PROJECT_SOURCE_DIR}/cmake/comlib.cmake)

## 链接头文件和库
include(${PROJECT_SOURCE_DIR}/cmake/linklib.cmake)

# 依赖StiBel库的内容

#EXECUTABLE_OUTPUT_PATH为生成可执行文件路径，LIBRARY_OUTPUT_PATH为生成库文件路径，BUILD_LIB_DIR生成库的路径
SET(EXECUTABLE_OUTPUT_PATH      ${PROJECT_SOURCE_DIR}/deploy/)
SET(BUILD_LIB_DIR               ${PROJECT_SOURCE_DIR}/deploy/lib)
SET(LIBRARY_OUTPUT_PATH         ${BUILD_LIB_DIR})

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 头文件目录
INCLUDE_DIRECTORIES( 
${PROJECT_SOURCE_DIR}/core/common/include  
${PROJECT_SOURCE_DIR}/core/constants/include 
${PROJECT_SOURCE_DIR}/core/controllers/include
${PROJECT_SOURCE_DIR}/core/exception/include 
${PROJECT_SOURCE_DIR}/core/filters/include 
${PROJECT_SOURCE_DIR}/core/models/include
${PROJECT_SOURCE_DIR}/core/plugins/include 
${PROJECT_SOURCE_DIR}/core/services/include
${PROJECT_SOURCE_DIR}/core/utils/include
${STIBEL_COMMON_CONFIG_INCLUDE}
${STIBEL_DATA_REDIS_INCLUDE}
${3PART_INCLUDE_PATH}
${COMM_INCLUDE_PATH} )

#代码列表
FILE (GLOB PROJECT_DROGON_FILES 
${PROJECT_SOURCE_DIR}/core/common/source/*.*  
${PROJECT_SOURCE_DIR}/core/constants/source/*.* 
${PROJECT_SOURCE_DIR}/core/controllers/source/*.*
${PROJECT_SOURCE_DIR}/core/exception/source/*.* 
${PROJECT_SOURCE_DIR}/core/filters/source/*.* 
${PROJECT_SOURCE_DIR}/core/models/source/*.*
${PROJECT_SOURCE_DIR}/core/plugins/source/*.* 
${PROJECT_SOURCE_DIR}/core/services/source/*.* 
${PROJECT_SOURCE_DIR}/core/services/source/inner/*.*
${PROJECT_SOURCE_DIR}/core/utils/source/*.*  )

#drogon_create_views(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/views
#                    ${CMAKE_CURRENT_BINARY_DIR} TRUE)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/core/main/main.cc ${PROJECT_DROGON_FILES})                    

# 链接drogon库
find_package(Drogon CONFIG REQUIRED)
#target_link_libraries(${PROJECT_NAME} Drogon::Drogon ${3PART_LIB_LIST} ${COMM_LIB_LIST})
#target_link_libraries(${PROJECT_NAME} Drogon::Drogon ${LIB_STIBEL_COMMON_FOUNDATION} ${LIB_STIBEL_DATA_REDIS} ${LIB_YAMLCPP})
target_link_libraries(${PROJECT_NAME} Drogon::Drogon ${LIB_STIBEL_COMMON_FOUNDATION} ${LIB_STIBEL_DATA_REDIS} ${LIB_STIBEL_COMMON_CONFIG} ${LIB_STIBEL_UTIL} ${LIB_HIREDIS} ${LIB_YAMLCPP} ${LIB_JSONCPP} ${LIB_TINYXML} ${LIB_POCO})

# boost 和 C++ 版本
if (CMAKE_CXX_STANDARD LESS 17)
    # With C++14, use boost to support any, string_view and filesystem
    message(STATUS "use c++14")
    find_package(Boost 1.61.0 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++20")
endif ()

if(BUILD_TESTS)
    add_subdirectory(testcase)
endif ()
