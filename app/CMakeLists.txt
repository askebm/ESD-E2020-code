add_executable(gpioExample gpioExample.cpp)
target_link_libraries(gpioExample GPIO)
add_deploy_target(gpioExample)
