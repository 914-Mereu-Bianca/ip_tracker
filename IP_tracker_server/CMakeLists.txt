
cmake_minimum_required(VERSION 3.8)

project(Server)

set(CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH "/root/.local")

find_package(Threads REQUIRED)

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

# include protobuf
include_directories(${Protobuf_INCLUDE_DIRS})
 
# Gets the protos file path
get_filename_component(PROTO_FILE "./../IP_tracker_proto/data.proto" ABSOLUTE)
get_filename_component(PROTO_FILE_PATH "${PROTO_FILE}" PATH)

get_filename_component(PROTO_FILE_AUTH "./../IP_tracker_proto/auth.proto" ABSOLUTE)
get_filename_component(PROTO_FILE_AUTH_PATH "${PROTO_FILE_AUTH}" PATH)

# Sets the location for generated files
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/proto_generated/)

set(PROTO_SOURCES "${CMAKE_BINARY_DIR}/proto_generated/data.pb.cc")
set(PROTO_HEADERS "${CMAKE_BINARY_DIR}/proto_generated/data.pb.h")
set(GRPC_SOURCES "${CMAKE_BINARY_DIR}/proto_generated/data.grpc.pb.cc")
set(GRPC_HEADERS "${CMAKE_BINARY_DIR}/proto_generated/data.grpc.pb.h")
set_property(SOURCE ${GRPC_SOURCES} ${PROTO_SOURCES} ${GRPC_HEADERS} ${PROTO_HEADERS} PROPERTY SKIP_AUTOMOC ON)

# Generate *.pb.* and *.qrpc.* files from .proto file
add_custom_command (
  OUTPUT "${PROTO_SOURCES}" "${PROTO_HEADERS}" "${GRPC_SOURCES}" "${GRPC_HEADERS}"
  COMMAND ${_PROTOBUF_PROTOC}
  ARGS --grpc_out "${CMAKE_BINARY_DIR}/proto_generated/"
       --cpp_out "${CMAKE_BINARY_DIR}/proto_generated/"
       -I "${PROTO_FILE_PATH}"
       --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
       "${PROTO_FILE}"
  DEPENDS "${PROTO_FILE}"
)

set(PROTO_SOURCES_AUTH "${CMAKE_BINARY_DIR}/proto_generated/auth.pb.cc")
set(PROTO_HEADERS_AUTH "${CMAKE_BINARY_DIR}/proto_generated/auth.pb.h")
set(GRPC_SOURCES_AUTH "${CMAKE_BINARY_DIR}/proto_generated/auth.grpc.pb.cc")
set(GRPC_HEADERS_AUTH "${CMAKE_BINARY_DIR}/proto_generated/auth.grpc.pb.h")
set_property(SOURCE ${GRPC_SOURCES_AUTH} ${PROTO_SOURCES_AUTH} ${GRPC_HEADERS_AUTH} ${PROTO_HEADERS_AUTH} PROPERTY SKIP_AUTOMOC ON)

add_custom_command (
  OUTPUT "${PROTO_SOURCES_AUTH}" "${PROTO_HEADERS_AUTH}" "${GRPC_SOURCES_AUTH}" "${GRPC_HEADERS_AUTH}"
  COMMAND ${_PROTOBUF_PROTOC}
  ARGS --grpc_out "${CMAKE_BINARY_DIR}/proto_generated/"
       --cpp_out "${CMAKE_BINARY_DIR}/proto_generated/"
       -I "${PROTO_FILE_AUTH_PATH}"
       --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
       "${PROTO_FILE_AUTH}"
  DEPENDS "${PROTO_FILE_AUTH}"
)

# Sets a library with generated files
add_library(GrpcProtoLib
  ${PROTO_SOURCES}
  ${PROTO_HEADERS}
  ${GRPC_SOURCES}
  ${GRPC_HEADERS}
  ${PROTO_SOURCES_AUTH}
  ${PROTO_HEADERS_AUTH}
  ${GRPC_SOURCES_AUTH}
  ${GRPC_HEADERS_AUTH}
)

target_link_libraries(GrpcProtoLib

  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# add executable
set(
  PROJECT_SOURCES
  main.cpp
  src/server_impl.cpp
  src/auth_server_impl.cpp
  src/data_parser.cpp
)

# Sets the project headers file
set(PROJECT_HEADERS
  include/server_impl.h
  include/auth_server_impl.h
  include/data_parser.h
) 

add_executable(
  ${CMAKE_PROJECT_NAME}
  ${PROJECT_SOURCES}
  ${PROJECT_HEADERS}
)

# links against the necessary depdendencies
target_link_libraries(${CMAKE_PROJECT_NAME}
  GrpcProtoLib
  absl::flags
  absl::flags_parse
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}
)

