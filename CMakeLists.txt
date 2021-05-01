cmake_minimum_required(VERSION 3.19)
project(sintoth_web_server CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(sintoth_web_server main.cpp httpd.cpp httpd.h request/Request.cpp request/Request.h request/RequestMethod.h response/Response.cpp response/Response.h)