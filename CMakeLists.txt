cmake_minimum_required(VERSION 3.10)

project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 8.1.1
)
FetchContent_MakeAvailable(fmt)

# 查找 Boost 库
find_package(Boost REQUIRED COMPONENTS filesystem)

# include_directories(
#     ${CMAKE_SOURCE_DIR}/include/log.h
# )

add_executable(test ${CMAKE_SOURCE_DIR}/test/main.cpp ${CMAKE_SOURCE_DIR}/src/log.cpp)

target_link_libraries(test PRIVATE fmt::fmt stdc++fs)