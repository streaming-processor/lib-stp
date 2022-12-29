cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(This stp)

set(Headers 
    deneme.hpp)
set(Sources
    deneme.cpp
    main.cpp
)
add_library(${This} STATIC ${Sources} ${Headers})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(${This} ${Boost_LIBRARIES})
endif()


