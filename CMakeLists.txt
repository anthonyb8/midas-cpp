cmake_minimum_required(VERSION 3.14)
project(midas_cpp)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find packages
find_package(CURL REQUIRED)
set(BOOST_ROOT "/Users/anthony/Cpp/boost_1_82_0")
# find_package(Boost 1.82.0 REQUIRED) # Assuming you don't need specific components, otherwise list them

# Set all IBAPI source  files 
file(GLOB IBAPI_SOURCES "lib/ibapi/client/src/*.cpp")

# # FetchContent for external dependencies
# include(FetchContent)
# FetchContent_Declare(
#   databento
#   GIT_REPOSITORY https://github.com/databento/databento-cpp
#   GIT_TAG HEAD
# )
# FetchContent_MakeAvailable(databento)

# Define the executable for your project
add_executable(midas_cpp
    src/main.cpp
    src/MidasClient.cpp
    ${IBAPI_SOURCES}
)

# Include directories for Boost, CURL, and your project
target_include_directories(midas_cpp PRIVATE
  ${CURL_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/lib
  ${CMAKE_SOURCE_DIR}/lib/ibapi/client/include
  ${BOOST_ROOT}
)

# Find and link the TWS Socket Client library and DIB library
find_library(TWS_SOCKET_CLIENT_LIB NAMES libTwsSocketClient.dylib PATHS "${CMAKE_SOURCE_DIR}/lib/ibapi/client")
find_library(DIB_LIB NAMES libbid.a PATHS "${CMAKE_SOURCE_DIR}/lib/ibapi/client/lib")

# Link libraries to your executable
target_link_libraries(midas_cpp PRIVATE 
    ${TWS_SOCKET_CLIENT_LIB}
    ${DIB_LIB}
    ${CURL_LIBRARIES} 
    # ${Boost_LIBRARIES} # Add this if you're using Boost libraries that need to be linked
)

# Set the output directory for the executable
set_target_properties(midas_cpp PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Enable testing functionality in CMake
enable_testing()

# Define a separate executable for tests
add_executable(Tests 
    tests/test_main.cpp
)

target_include_directories(Tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CURL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/ibapi/client/include
    ${BOOST_ROOT}
)

target_link_libraries(Tests PRIVATE 
    ${TWS_SOCKET_CLIENT_LIB}
    ${DIB_LIB}
    ${CURL_LIBRARIES} 
)

# Register the test executable with CTest
add_test(NAME Test COMMAND Tests)

# Set the output directory for the executable
set_target_properties(Tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/tests
)


message(STATUS "Output directory: ${CMAKE_SOURCE_DIR}/bin")

# set_target_properties(midas_cpp PROPERTIES
#   INSTALL_RPATH "/Users/anthony/git-projects/midas_cpp/lib/ibapi/client"
#     # INSTALL_RPATH "@loader_path/../lib/ibapi/client"
# )