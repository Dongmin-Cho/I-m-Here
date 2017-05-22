cmake_minimum_required(VERSION 3.5)
find_package(Caffe)
include_directories(extract_descriptor)

set(SOURCE_FILES extract_descriptor.cpp classification.cpp)
#set(LIBS ./)

add_executable(extract_descriptor ${SOURCE_FILES})
target_link_libraries(extract_descriptor ${Caffe_LINK})
install(TARGETS extract_descriptor DESTINATION ${CMAKE_INSTALL_BINDIR})
