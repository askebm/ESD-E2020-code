
add_executable(stationboxTester stationbox.cpp)
target_link_libraries(stationboxTester stationbox)

add_executable(gpioExample gpioExample.cpp)
add_executable(testPrinterDriver testPrinterDriver.cpp)
target_link_libraries(gpioExample GPIO)
target_link_libraries(testPrinterDriver receiptPrinterDriver -lusb-1.0)

add_deploy_target(gpioExample)

add_executable(EventExample EventExample.cpp)
target_link_libraries(EventExample Event)

add_executable(TaskExample TaskExample.cpp)
target_link_libraries(TaskExample Task)

add_executable(DisplayExample DisplayExample.cpp)
target_link_libraries(DisplayExample DisplayDriver)

add_executable(DisplayTaskExample DisplayTaskExample.cpp)
target_link_libraries(DisplayTaskExample DisplayDriverTask)

add_executable(TouchDisplayExample TouchDisplayExample.cpp)
target_include_directories(TouchDisplayExample PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(TouchDisplayExample TouchDisplay)
