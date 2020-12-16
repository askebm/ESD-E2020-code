add_library(Receipt item.cpp receipt.cpp simple_item.cpp)
target_include_directories(Receipt PUBLIC ${PROJECT_SOURCE_DIR}/extern/interface_lib )

#add_library(DB_Interface db_interface.cpp)
#target_include_directories(DB_Interface PUBLIC
#	${PROJECT_SOURCE_DIR}/extern/interface_lib
#	${ZMQ_INCLUDE_DIRECTORIES} )
#target_link_libraries(DB_Interface PUBLIC Receipt ${ZMQ_LIBRARIES})
