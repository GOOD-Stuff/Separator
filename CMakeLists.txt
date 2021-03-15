cmake_minimum_required(VERSION 3.8)
project(separator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -std=c++17")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(BOOST_ROOT ${BOOST_ROOT})#/home/vldmr/Projects/Git/boost_1_75_0/build)
set(BOOST_INCLUDEDIR ${BOOST_INCLUDE}) #/home/vldmr/Projects/Git/boost_1_75_0/build/include/)

find_package(Boost 1.75.0 REQUIRED COMPONENTS system filesystem regex)
#link_libraries(/home/vldmr/Projects/Git/boost_1_75_0/build/lib/)

if(Boost_FOUND)
    message("Boost version: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

if(NOT TARGET Boost::filesystem)
    message("Can't find Boost")

    add_library(Boost::filesystem IMPORTED INTERFACE)
    set_property(TARGET Boost::filesystem PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::filesystem PROPERTY
            INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()




add_executable(separator src/main.cpp src/TaskHandler.cpp src/TaskHandler.h
                         src/FileIO.cpp src/FileIO.h src/Parser.cpp src/Parser.h)
target_link_libraries(separator ${Boost_LIBRARIES})
target_link_libraries(separator pthread)

