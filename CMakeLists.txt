cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(float src/float.cpp)
add_executable(int src/int.cpp)
add_executable(list src/list.cpp)
# add_executable(vector src/vector.cpp)
add_executable(interface_list src/interface_list.cpp)
add_executable(interface_vector src/interface_vector.cpp)

target_include_directories(float PRIVATE include)
target_include_directories(int PRIVATE include)
target_include_directories(list PRIVATE include)
# target_include_directories(vector PRIVATE /include)
target_include_directories(interface_list PRIVATE include)
target_include_directories(interface_vector PRIVATE include)