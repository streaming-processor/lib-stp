cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(This stp)



include_directories(.
    /logger
)
#add_library(${This} STATIC ${HEADERS})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(${This} ${Boost_LIBRARIES})
endif()

add_definitions(-DBOOST_ALL_NO_LIB)
