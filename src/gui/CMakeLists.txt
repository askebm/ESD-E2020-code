
add_library(TouchDisplayInterface TouchDisplayBackend.cpp Layout.cpp Modal.cpp)
target_include_directories(TouchDisplayInterface PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(TouchDisplayInterface PUBLIC Receipt)

add_subdirectory(sdl2)

#add_library(TouchDisplay TouchDisplay.cpp Button.cpp DynamicReceipt.cpp)
#target_include_directories(TouchDisplay  PUBLIC ${PROJECT_SOURCE_DIR}/include)
#target_link_libraries(TouchDisplay SDL2 ${SDL2_TTF_LIBRARIES} Receipt)
