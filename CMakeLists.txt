cmake_minimum_required(VERSION 3.16)
project(heroku_kies)

set(CMAKE_CXX_STANDARD 17)

if(PROD)
    add_link_options(-static)
endif()

add_subdirectory(lib)

add_executable(heroku_kies main.cpp)
target_link_libraries(heroku_kies PRIVATE lib)
install(TARGETS heroku_kies DESTINATION ..)