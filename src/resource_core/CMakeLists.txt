add_library(resource_core STATIC
        FileHandle.cpp
        ResourceError.cpp
        ResourceManager.cpp
)

target_include_directories(resource_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(resource_core PUBLIC project_warnings project_sanitizers)