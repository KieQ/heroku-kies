cmake_minimum_required(VERSION 3.16)

add_subdirectory(fmt)

#Create the library
add_library(lib lib.cpp)

#The common part
target_include_directories(lib PUBLIC cinatra/include spdlog/include json/simple_include fmt/include inja/include)
target_link_libraries(lib PUBLIC fmt)

#The online part
if(PROD)
    target_include_directories(lib PUBLIC /usr/local/include)
    target_link_libraries(lib PUBLIC boost_system pthread)
endif()

#The development part
if(DEV)
    target_include_directories(lib PUBLIC /Users/sunbo/Downloads/FrameWork/boost/include)
endif()
