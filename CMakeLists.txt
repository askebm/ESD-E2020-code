# Current highest available version in the default ubuntu repos
cmake_minimum_required(VERSION 3.10)

#Here we handle build-host specific variables
include(cmake/host-vars.cmake)

#If we want to test the program on computers and not on the zybo 
option(USE_SYSTEM_COMPILER "Enable system compiler instead of toolchain compiler" OFF)
if (NOT USE_SYSTEM_COMPILER)
	set(CMAKE_TOOLCHAIN_FILE cmake/zybo-toolchain.cmake)
endif()

#Include a custom target to deply and run executables
include(cmake/deploy-test.cmake)

#Initialise the project (Checks compiler and stuff)
project(ESD)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add external libraries (must come before project dirs)
add_subdirectory(extern/serialib)

# add project directories
add_subdirectory(src)
add_subdirectory(app)

# Unit tests tbd
