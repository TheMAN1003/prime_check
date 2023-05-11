cmake_minimum_required(VERSION 3.24)
project(NTA_lab_1)

set(CMAKE_CXX_STANDARD 20)


set(GMP_DIR /opt/homebrew/Cellar/gmp/6.2.1_1/)


include_directories(${GMP_DIR}/include)
link_directories(${GMP_DIR}/lib)


add_executable(NTA_lab_1 main.cpp algorithms.cpp algorithms.h)

target_link_libraries(NTA_lab_1 gmp)
