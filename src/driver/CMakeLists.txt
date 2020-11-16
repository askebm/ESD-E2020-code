add_library(GPIO GPIO.cpp)
add_library(zyboGPIO zyboGPIO.cpp)
target_include_directories(GPIO PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(zyboGPIO PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(GPIO zyboGPIO)
