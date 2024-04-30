cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

set(CMAKE_CXX_STANDARD 11)

# 添加所有源文件
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})
