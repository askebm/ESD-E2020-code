add_subdirectory(driver)
add_library(stationbox stationBox.cpp)
target_include_directories(stationbox PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(Event Event.cpp)
target_include_directories(Event PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(Task Task.cpp)
target_include_directories(Task PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Task Event pthread)

add_library(DisplayDriver DisplayDriver.cpp)
target_include_directories(DisplayDriver PUBLIC ${PROJECT_SOURCE_DIR}/include ${serialib_INCLUDE_DIR})
target_link_libraries(DisplayDriver serialib)

add_library(DisplayDriverTask DisplayDriverTask.cpp)
target_include_directories(DisplayDriverTask PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(DisplayDriverTask Task DisplayDriver)

add_library(USBDriver USBDriver.cpp)
target_include_directories(USBDriver PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(CardScannerTask CardScannerTask.cpp)
target_include_directories(CardScannerTask PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(CardScannerTask Task USBDriver)

add_library(BarCodeScannerTask BarCodeScannerTask.cpp)
target_include_directories(BarCodeScannerTask PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(BarCodeScannerTask Task USBDriver)

add_library(NumpadTask NumpadTask.cpp)
target_include_directories(NumpadTask PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(NumpadTask Task NumpadDriver)


add_subdirectory(gui)
