set (source "${CMAKE_SOURCE_DIR}/src/resources")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/resources")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
    DEPENDS ${destination}
    COMMENT "symbolic link resources folder from ${source} => ${destination}"
)
