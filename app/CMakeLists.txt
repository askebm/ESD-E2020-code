add_executable(gpioExample gpioExample.cpp)
add_executable(testPrinterDriver testPrinterDriver.cpp)
target_link_libraries(gpioExample GPIO)
target_link_libraries(testPrinterDriver receiptPrinterDriver -lusb-1.0)

add_deploy_target(gpioExample)
