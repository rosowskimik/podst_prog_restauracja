# Library files
list(APPEND LIB_LIST
    restaurant
)

# Header files
list(TRANSFORM LIB_LIST PREPEND ../include/ OUTPUT_VARIABLE HEADER_LIST)
list(TRANSFORM HEADER_LIST APPEND .h)

# Library source files
list(TRANSFORM LIB_LIST APPEND .cpp OUTPUT_VARIABLE SOURCE_LIST)

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
