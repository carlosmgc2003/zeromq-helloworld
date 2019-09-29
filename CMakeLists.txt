cmake_minimum_required(VERSION 3.15)
project(zeromq-helloworld)

set(CMAKE_CXX_STANDARD 11)

find_package(nlohmann_json 3.7.0 REQUIRED)

add_executable(client client.cpp)
target_link_libraries(client zmq)
target_link_libraries(client nlohmann_json::nlohmann_json)
add_executable(server server.cpp)
target_link_libraries(server zmq)
target_link_libraries(server nlohmann_json::nlohmann_json)




