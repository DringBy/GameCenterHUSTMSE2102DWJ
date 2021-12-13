cmake_minimum_required(VERSION 3.0.0)
project(GameCenter)

include_directories(include)
aux_source_directory(src dir)

include(CTest)
enable_testing()

add_executable(GameCenter ${dir})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
