# .h + .cpp files
list(APPEND LIB_LIST
    check
    meal
    category
    menu
    order
    history
    restaurant
)

# Header files
list(TRANSFORM LIB_LIST APPEND .h OUTPUT_VARIABLE HEADER_LIST)

# .h only
list(APPEND HEADER_LIST)

list(TRANSFORM HEADER_LIST PREPEND ../include/ )

# Library source files
list(TRANSFORM LIB_LIST APPEND .cpp OUTPUT_VARIABLE SOURCE_LIST)

# .cpp only
list(APPEND SOURCE_LIST)

add_library(restaurant)

target_compile_features(restaurant PUBLIC cxx_std_17)

target_include_directories(restaurant PUBLIC ../include)

target_sources(restaurant
  PUBLIC
    ${SOURCE_LIST}
    ${HEADER_LIST}
)

# Nice IDEs display
source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES "${HEADER_LIST}"
)
