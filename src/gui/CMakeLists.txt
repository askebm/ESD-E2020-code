add_library(TouchDisplay TouchDisplay.cpp)
target_include_directories(TouchDisplay  PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(TouchDisplay SDL2)
