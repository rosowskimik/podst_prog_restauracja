# Main app
add_executable(restauracja)

target_sources(restauracja PRIVATE main.cpp)

target_link_libraries(restauracja PRIVATE restaurant)

# Admin app
add_executable(admin)

target_sources(admin PRIVATE admin.cpp)

target_link_libraries(restauracja PRIVATE restaurant)