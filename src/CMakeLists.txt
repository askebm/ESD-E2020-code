add_library(stationbox stationBox.cpp)
target_include_directories(stationbox PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(Event Event.cpp)
target_include_directories(Event PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(Task Task.cpp)
target_include_directories(Task PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Task Event pthread)

add_library(receiptPrinterTask ReceiptPrinterTask.cpp ReceiptFormatter.cpp)
target_include_directories(receiptPrinterTask PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(receiptPrinterTask Task receiptPrinterDriver)

add_library(DisplayDriver DisplayDriver.cpp)
target_include_directories(DisplayDriver PUBLIC ${PROJECT_SOURCE_DIR}/include ${serialib_INCLUDE_DIR})
target_link_libraries(DisplayDriver serialib)

add_library(DisplayDriverTask DisplayDriverTask.cpp)
target_include_directories(DisplayDriverTask PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(DisplayDriverTask Task DisplayDriver)


add_subdirectory(gui)
add_subdirectory(driver)
