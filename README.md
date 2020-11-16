# Embedded System Design Project

An introduction to modern cmake can be found [here](https://cliutils.gitlab.io/modern-cmake/)

By default the system will cross-compile for the zybo, this can be disabled with
`cmake . -Bbuild -DUSE_SYSTEM_COMPILER=ON`.

## Setup
Before compiling please do `cp cmake/host-vars.cmake.example cmake/host-vars.cmake`
and modify as needed

## cmake basics

To configure: `cmake . -Bbuild`. This should be done when a `CMakeLists.txt` file changes.

To compile: `cmake --build build`

## Quick deployment and test

For easy testing of executables a custom target can be added in cmake with
`add_deploy_target(<executable name>)`, and invoked from the command line 
`cmake --build build --target deplay_<executable name>`.