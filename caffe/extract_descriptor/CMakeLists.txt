cmake_minimum_required(VERSION 3.5)
find_package(Caffe)
include_directories(extract_descriptor)
include(../../face_recognition/dlib/cmake)

set(SOURCE_FILES extract_descriptor.cpp classification.cpp crop_face_img)

add_executable(extract_descriptor ${SOURCE_FILES})
target_link_libraries(extract_descriptor ${Caffe_LINK} dlib::dlib)
install(TARGETS extract_descriptor DESTINATION ${CMAKE_INSTALL_BINDIR})
