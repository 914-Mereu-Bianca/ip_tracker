cmake_minimum_required(VERSION 3.2)
project(Client LANGUAGES CXX)
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

# Sets to autogenerate the MOC files
set(CMAKE_AUTOMOC ON)

# Find Qt6 components
set(CMAKE_PREFIX_PATH "~/Qt/6.8.0/gcc_64" ${CMAKE_PREFIX_PATH}) 
find_package(Qt6 COMPONENTS Widgets Core REQUIRED)

# Includes headers directory
include_directories(include/)

# Sets the path to the gRPC and Protobuf headers
list(APPEND CMAKE_PREFIX_PATH "/root/.local")

# Find Protobuf installation
# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
option(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
  find_program(_PROTOBUF_PROTOC protoc)
else()
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

# Gets the protos file path

get_filename_component(PROTO_FILE_IP "./../IP_tracker_proto/ip_tracker.proto" ABSOLUTE)
get_filename_component(PROTO_FILE_IP_PATH "${PROTO_FILE_IP}" PATH)

# Sets the location for generated files
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/proto_generated/)

set(PROTO_SOURCES_IP "${CMAKE_BINARY_DIR}/proto_generated/ip_tracker.pb.cc")
set(PROTO_HEADERS_IP "${CMAKE_BINARY_DIR}/proto_generated/ip_tracker.pb.h")
set(GRPC_SOURCES_IP "${CMAKE_BINARY_DIR}/proto_generated/ip_tracker.grpc.pb.cc")
set(GRPC_HEADERS_IP "${CMAKE_BINARY_DIR}/proto_generated/ip_tracker.grpc.pb.h")
set_property(SOURCE ${GRPC_SOURCES_IP} ${PROTO_SOURCES_IP} ${GRPC_HEADERS_IP} ${PROTO_HEADERS_IP} PROPERTY SKIP_AUTOMOC ON)

add_custom_command (
  OUTPUT "${PROTO_SOURCES_IP}" "${PROTO_HEADERS_IP}" "${GRPC_SOURCES_IP}" "${GRPC_HEADERS_IP}"
  COMMAND ${_PROTOBUF_PROTOC}
  ARGS --grpc_out "${CMAKE_BINARY_DIR}/proto_generated/"
       --cpp_out "${CMAKE_BINARY_DIR}/proto_generated/"
       -I "${PROTO_FILE_IP_PATH}"
       --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
       "${PROTO_FILE_IP}"
  DEPENDS "${PROTO_FILE_IP}"
)

# Sets a library with generated files
add_library(GrpcProtoLib
  ${PROTO_SOURCES_IP}
  ${PROTO_HEADERS_IP}
  ${GRPC_SOURCES_IP}
  ${GRPC_HEADERS_IP}
)

# Links the library against the necessary dependencies
target_link_libraries(GrpcProtoLib
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF} 
)

# Sets the project sources file
set(PROJECT_SOURCES
  main.cpp
  src/client.cpp
  src/client_modelview.cpp
  src/view/main_window.cpp
  src/view/main_widget.cpp
)

# Sets the project headers file
set(PROJECT_HEADERS
  include/client.h
  include/client_modelview.h
  include/view/main_window.h
  include/view/main_widget.h
)

# Sets the executable
add_executable(${CMAKE_PROJECT_NAME}
  ${PROJECT_SOURCES}
  ${PROJECT_HEADERS}
)

# Links the executable against the necessary dependencies
target_link_libraries(${CMAKE_PROJECT_NAME}
  GrpcProtoLib
  Qt6::Widgets
  Qt6::Core
)

# Sets a library with project file for testing
add_library(${CMAKE_PROJECT_NAME}_lib
  ${PROJECT_SOURCES}
  ${PROJECT_HEADERS}
)

# Links the library against the necessary dependencies
target_link_libraries(${CMAKE_PROJECT_NAME}_lib
  GrpcProtoLib
  Qt6::Widgets
  Qt6::Core
)

add_subdirectory(tests)