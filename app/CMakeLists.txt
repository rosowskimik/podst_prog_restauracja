# Main app
add_executable(restauracja)

target_sources(restauracja PRIVATE main.cpp)

target_link_libraries(restauracja PRIVATE restaurant)

# Copy executable to source dir
add_custom_command(
    TARGET restauracja POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:restauracja>"
        "${CMAKE_SOURCE_DIR}/$<TARGET_FILE_NAME:restauracja>"
    VERBATIM
)