cmake_minimum_required(VERSION 3.27)
project(SFML_FIve)

set(CMAKE_CXX_STANDARD 20)

add_executable(SFML_FIve src/main.cpp
        include/player.h
        src/player.cpp
        src/AI.cpp
        include/AI.h
        src/check.cpp
        include/check.h)

include_directories(include)

# 找到SFML并包含它的头文件
# 确保已通过Homebrew安装SFML，并替换下面的"2.6.1"为实际安装的版本
set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)

# 链接SFML到你的项目
target_link_libraries(SFML_FIve sfml-system sfml-window sfml-graphics sfml-audio sfml-network)