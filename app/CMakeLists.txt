
add_executable(stationboxTester stationbox.cpp)
target_link_libraries(stationboxTester stationbox)

add_executable(gpioExample gpioExample.cpp)
target_link_libraries(gpioExample GPIO)
add_deploy_target(gpioExample)

# event_example.cpp
add_executable(event_example event_example.cpp)
target_link_libraries(event_example Event)

# task_example.cpp
add_executable(task_example task_example.cpp)
target_link_libraries(task_example Task)

add_executable(display_example display_example.cpp)
target_link_libraries(display_example DisplayDriver)

add_executable(display_task_example display_task_example.cpp)
target_link_libraries(display_task_example DisplayDriverTask)


add_executable(TouchDisplayExample TouchDisplayExample.cpp)
target_include_directories(TouchDisplayExample  PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(TouchDisplayExample TouchDisplaySDL2)
