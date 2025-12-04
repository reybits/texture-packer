add_library(StbLib INTERFACE)

target_include_directories(StbLib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
