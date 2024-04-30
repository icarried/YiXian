cmake_minimum_required(VERSION 3.10)
project(YiXian)

set(CMAKE_CXX_STANDARD 11)

# 添加所有源文件
# 添加子目录："${CMAKE_SOURCE_DIR}/子目录/*.cpp"
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# 输出 SOURCES 变量的内容
message("SOURCES variable contains:")
foreach(source ${SOURCES})
    message("  ${source}")
endforeach()

# 生成可执行文件放置在build目录中
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 指定生成的可执行文件名称为 main.exe
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")
