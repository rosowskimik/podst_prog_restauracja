cmake_minimum_required(VERSION 3.16)

project(
    restaurant
    LANGUAGES CXX
)

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

endif()

# Main library
add_subdirectory(lib)

# Main app
add_subdirectory(app)

# Setup install
install(TARGETS restauracja DESTINATION .)
install(FILES assets/instrukcja.pdf DESTINATION .)
install(DIRECTORY example_data/ DESTINATION ./data)