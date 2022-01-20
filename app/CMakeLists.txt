# Main app
add_executable(restauracja)

target_sources(restauracja PRIVATE main.cpp)

target_link_libraries(restauracja PRIVATE restaurant)