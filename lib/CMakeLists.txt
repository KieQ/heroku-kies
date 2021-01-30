cmake_minimum_required(VERSION 3.16)

#Check The OS
if(UNIX AND NOT APPLE)
    message("This is production environment")
    set(PROD TRUE)
    set(PROD TRUE PARENT)
elseif(APPLE)
    message("This is development environment")
    set(DEV TRUE)
    set(DEV TRUE PARENT)
endif()

# 
add_library(lib lib.cpp)

if(PROD)
target_include_directories(lib PUBLIC /usr/local/include
        cinatra/include)

target_link_libraries(lib PUBLIC pthread)
endif()

if(DEV)
    target_include_directories(lib PUBLIC /Users/sunbo/Downloads/FrameWork/boost/include
            cinatra/include)
endif()