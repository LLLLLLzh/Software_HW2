cmake_minimum_required(VERSION 3.23)
project(mth9815_hw2_q3)

set(CMAKE_CXX_STANDARD 14)

add_executable(mth9815_hw2_q3 main.cpp soa.h products.h productservice.h test_products.cpp)


include_directories(/Users/zhangqingxu/Downloads/boost_1_65_0)
link_directories(/Users/zhangqingxu/Downloads/boost_1_65_0/libs)