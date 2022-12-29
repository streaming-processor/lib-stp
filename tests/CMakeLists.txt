cmake_minimum_required(VERSION 3.18)
project(test_core LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


find_package(Catch2 3 REQUIRED)


set(Sources 
    boost_opencv_include_test.cpp)
# todo add catch2 lib for testing 
add_executable(
    test_sources
    ${Sources}
)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(test_sources ${Boost_LIBRARIES})
endif()

target_link_libraries(test_sources PRIVATE Catch2::Catch2WithMain ${OpenCV_LIBS} )