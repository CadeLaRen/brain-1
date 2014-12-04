# add link directories (-L)
link_directories(${PROJECT_SOURCE_DIR}/lib)

#if(${PLATFORM} MATCHES "Arduino")
#  generate_arduino_firmware(test_bloc_ino
#      SRCS test_arduino.cpp
#      LIBS blob_perception
#      PORT /dev/ttyACM0
#      BOARD leonardo)
#else(${PLATFORM} MATCHES "Arduino")
#  add_executable(test_bcomms_lnx test_linux) # build executable
#  target_link_libraries(test_bloc_lnx blob_perception) # link libraries
#endif(${PLATFORM} MATCHES "Arduino")

