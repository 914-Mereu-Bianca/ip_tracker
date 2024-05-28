cmake_minimum_required(VERSION 3.8)

project(ServerTests)

set(CXX_STANDARD 17)

# GTest
# Fetch latest GTest version as recommended https://google.github.io/googletest/quickstart-cmake.html

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Sets test for ServerTests
set(ServerTests_SOURCES
  main.cpp
  login_test.cpp
)

add_executable(ServerTests
  ${ServerTests_SOURCES}
)

target_link_libraries(ServerTests
  GrpcProtoLib
  GTest::gtest_main
  ${CURL_LIBRARIES}
  mysqlcppconn
)

include(GoogleTest)