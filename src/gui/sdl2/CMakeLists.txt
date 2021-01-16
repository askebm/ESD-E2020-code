add_library(TouchDisplaySDL2 TouchDisplaySDL2.cpp Button.cpp DynamicReceipt.cpp)
target_include_directories(TouchDisplaySDL2 PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(TouchDisplaySDL2 SDL2 ${SDL2_TTF_LIBRARIES} TouchDisplayInterface)
