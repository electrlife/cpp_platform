cmake_minimum_required(VERSION 3.13)
project(demo VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)

add_executable(demo
    # src/demo.cpp
    # src/forward.cpp
    src/main.cpp
    src/template_specialization.cpp
    src/virtual_inheritance.cpp
    src/iostream.cpp
    src/json/jsoncpp.cpp
 )

 target_include_directories(
     demo
     PRIVATE
     src/json
 )
