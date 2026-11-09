cmake_minimum_required(VERSION 3.16)

project(test LANGUAGES CXX C)

#nombre del proyecto?
find_package(backend)

#output
add_executable(test sandbox.cpp) 
target_include_directories(test PRIVATE backend::sonora) #HEADER FILES
target_link_libraries(test PRIVATE winmm)
target_link_libraries(test PRIVATE sonora) 