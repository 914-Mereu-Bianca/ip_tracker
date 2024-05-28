
cmake_minimum_required(VERSION 3.8)

project(Server)

set(CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH "/root/.local")

find_package(Threads REQUIRED)

find_package(CURL REQUIRED)

find_package(SQLite3 REQUIRED)

#find_package(MySQL REQUIRED)


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
include_directories(${CURL_INCLUDE_DIRS})
include_directories("/usr/include/cppconn")
#include_directories(${MySQL_INCLUDE_DIRS})
 
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

target_link_libraries(GrpcProtoLib
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}
)

# add executable
set(
  PROJECT_SOURCES
  main.cpp
  parser/src/data_parser.cpp
  server/src/server.cpp
  server/src/server_controller.cpp
  server/src/admin.cpp
  router_communication/src/router.cpp
  router_communication/src/router_controller.cpp
  mail_communication/src/send_mail.cpp
  database/src/sql_connector.cpp
)

# Sets the project headers file
set(PROJECT_HEADERS
  parser/include/data_parser.h
  server/include/server.h
  server/include/admin.h
  server/include/server_controller.h
  router_communication/include/router.h
  router_communication/include/router_controller.h
  mail_communication/include/send_mail.h
  database/include/sql_connector.h
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
  ${CURL_LIBRARIES}
  #${MySQL_LIBRARIES}
  mysqlcppconn
)

add_subdirectory(tests)