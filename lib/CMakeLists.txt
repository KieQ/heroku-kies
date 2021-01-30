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

#Create the library
add_library(lib lib.cpp)

#The common include directory and link library
target_include_directories(lib PUBLIC cinatra/include spdlog/include)

#The online specific include directory and link library because online environment is linux
if(PROD)
    find_package(Boost)

    target_include_directories(lib PUBLIC /usr/local/include)

    target_link_libraries(lib PUBLIC pthread ${Boost_LIBRARIES})
endif()

#The development specific configuration because I use MacOS most time.
if(DEV)
    target_include_directories(lib PUBLIC /Users/sunbo/Downloads/FrameWork/boost/include)
endif()