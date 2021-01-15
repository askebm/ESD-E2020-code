add_library(GPIO GPIO.cpp)
add_library(zyboGPIO zyboGPIO.cpp)
add_library(receiptPrinterDriver ReceiptPrinterDriver.cpp )

target_include_directories(GPIO PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(zyboGPIO PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_include_directories(receiptPrinterDriver PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(receiptPrinterDriver -lusb-1.0)

target_link_libraries(GPIO zyboGPIO)


