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
#Add packages
find_package(SDL2)
if (${SDL2_FOUND})
	message("Found SDL2")
else()
	message("Did not find SDL2")
endif()
find_package(PkgConfig)
if (${PkgConfig_FOUND})
	message("Found PkgConfig")
else()
	message("Did not find PkgConfig")
endif()

pkg_check_modules(SDL2_TTF SDL2_ttf)
if (${SDL2_TTF_FOUND})
	message("Found SDL2_TTF")
else()
	message("Did not find SDL2_TTF")
endif()

pkg_check_modules(ZMQ libzmq>=4.2.2)
if (${ZMQ_FOUND})
	message("Found ZMQ")
else()
	message("Did not find ZMQ")
endif()

add_subdirectory(extern/interface_lib)


# add project directories
add_subdirectory(src)
add_subdirectory(app)

# Unit tests tbd
