cmake_minimum_required(VERSION 3.21)
project(Project7_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project7_starter_files
        Customer.h
        CustomerDB.cpp
        CustomerDB.h
        main.cpp
        Project7.cpp
        UTString.h)
