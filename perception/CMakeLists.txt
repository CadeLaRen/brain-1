if(${PLATFORM} MATCHES "Arduino")
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_ROOT}/Modules/ArduinoToolchain.cmake) # Arduino Toolchain
  set(ARDUINO_AVRDUDE_PROGRAM avrdude.py) # override arvdude for upload to micro and leonardo
endif(${PLATFORM} MATCHES "Arduino")

cmake_minimum_required (VERSION 2.8.5)
cmake_policy(VERSION 2.8.5)
project(perception)

# flags for debug version: "-DCMAKE_BUILD_TYPE=Debug/Release"
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  message("-- Configuring ${PROJECT_NAME} for Debug")
  add_definitions(-D__DEBUG__)
  set(CMAKE_CC_FLAGS "${CMAKE_CC_CFLAGS} -Wall -Werror -g -O0 -fPIC")
else(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  set(CMAKE_CC_FLAGS "${CMAKE_CC_CFLAGS} -Wall -Werror -O2 -fPIC")
endif(${CMAKE_BUILD_TYPE} MATCHES "Debug")

# output files path: libs at /lib and executables at bin/
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# define dependencies path
set(BLOB_LIBS_DIR ${PROJECT_SOURCE_DIR}/../../libs)
set(BLOB_TYPE_DIR ${BLOB_LIBS_DIR}/types)
set(BLOB_6DOF_DIR ${BLOB_LIBS_DIR}/6dof)
set(BLOB_RT_DIR ${BLOB_LIBS_DIR}/rt)
set(BLOB_BODY_DIR ${PROJECT_SOURCE_DIR}/../../body)
set(BLOB_SENSOR_DIR ${BLOB_BODY_DIR}/sensors)

# include directories (-I)
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${BLOB_TYPE_DIR}/include
                    ${BLOB_6DOF_DIR}/include
                    ${BLOB_RT_DIR}/include
                    ${BLOB_SENSOR_DIR}/include)

# link include directories (-L)
link_directories(${BLOB_RT_DIR}/lib)

# sources
set(LIB_SRC src/loc.cpp)

# libs to link
set(LIB_LIBS blob_rt)

# build the shared and static libraries
if(${PLATFORM} MATCHES "Arduino")
  set(ARDUINO_DEFAULT_BOARD leonardo) # Default Board ID, when not specified
  set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified
  generate_arduino_library(blob_perception
    SRCS ${LIB_SRC}
    LIBS ${LIB_LIBS}
    BOARD leonardo)
else(${PLATFORM} MATCHES "Arduino")
  add_library(blob_perception SHARED ${LIB_SRC})
  target_link_libraries(blob_perception ${LIB_LIBS})
  add_library(blob_perception_static STATIC ${LIB_SRC})
  target_link_libraries(blob_perception_static ${LIB_LIBS})
endif(${PLATFORM} MATCHES "Arduino")

# compile tests and dependencies only if standalone compilation
string(FIND ${CMAKE_BINARY_DIR} ${PROJECT_NAME} IS_PROJECT) 
if("${IS_PROJECT}" GREATER -1)
  # compile tests
#  add_subdirectory(test) 
  # dependencies
  add_subdirectory(${BLOB_RT_DIR} "${CMAKE_CURRENT_BINARY_DIR}/rt")
endif("${IS_PROJECT}" GREATER -1)


