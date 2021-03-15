cmake_minimum_required(VERSION 3.16)
project(heroku_kies)

set(CMAKE_CXX_STANDARD 17)

#Check The OS
if(UNIX AND NOT APPLE)
    message("This is production environment")
    set(PROD TRUE)
elseif(APPLE)
    message("This is development environment")
    set(DEV TRUE)
endif()

add_subdirectory(lib)


add_executable(heroku_kies main.cpp)
target_link_libraries(heroku_kies PRIVATE lib)
install(TARGETS heroku_kies DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/..)