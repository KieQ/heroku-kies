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

add_compile_options("SHELL:--param ggc-min-expand=1" "SHELL:--param ggc-min-heapsize=131072")

add_subdirectory(lib)

aux_source_directory(db db)
aux_source_directory(handler handler)

add_executable(heroku_kies main.cpp ${db} ${handler})
target_link_libraries(heroku_kies PRIVATE lib)
install(TARGETS heroku_kies DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/..)