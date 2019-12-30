cmake_minimum_required (VERSION 3.1)

project (registerer)

##################################
# Download and install GoogleTest

include(ExternalProject)
ExternalProject_Add(gtest
  URL https://github.com/google/googletest/archive/release-1.8.0.zip
  # Comment above line, and uncomment line below to use subversion.
  # SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/ 
  # Uncomment line below to freeze a revision (here the one for 1.7.0)
  # SVN_REVISION -r700

  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest source_dir binary_dir)

################
# Define a test
add_executable(gtest_test gtest_test.cpp)

######################################
# Configure the test to use GoogleTest
#
# If used often, could be made a macro.

add_dependencies(gtest_test gtest)
message( ${binary_dir} )
include_directories(${source_dir}/googletest/include)
target_link_libraries(gtest_test ${binary_dir}/googlemock/gtest/libgtest.a)
target_link_libraries(gtest_test pthread ${binary_dir}/googlemock/gtest/libgtest_main.a)

##################################
# Just make the test runnable with
#   $ make test

enable_testing()
add_test(NAME    gtest_test 
         COMMAND gtest_test)
