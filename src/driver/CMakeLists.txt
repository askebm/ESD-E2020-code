add_library(GPIO GPIO.cpp)
add_library(zyboGPIO zyboGPIO.cpp)
target_include_directories(GPIO PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(zyboGPIO PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(GPIO zyboGPIO)

add_library(NumpadDriver NumpadDriver/NumpadDriver.cpp)
target_include_directories(NumpadDriver PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(NumpadDriver GPIO)
