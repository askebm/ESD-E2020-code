add_library(GPIO GPIO.cpp)
add_library(zyboGPIO zyboGPIO.cpp)
add_library(receiptPrinterDriver receiptPrinterDriver.cpp)

target_include_directories(GPIO PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(zyboGPIO PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(receiptPrinterDriver PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(GPIO zyboGPIO)
