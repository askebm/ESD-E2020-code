add_subdirectory(driver)
add_library(stationbox stationBox.cpp)
target_include_directories(stationbox PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(Event Event.cpp)
target_include_directories(Event PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(Task Task.cpp)
target_include_directories(Task PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Task Event pthread)


