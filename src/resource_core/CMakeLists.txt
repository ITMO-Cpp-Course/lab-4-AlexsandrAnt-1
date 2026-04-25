add_library(resource_core STATIC
        resource_core.cpp
        resource_core.hpp
        ReourceError.hpp
        FileHandle.hpp
        ResourceManager.hpp
        FileHandle.cpp
        ResourceError.cpp
        ResourceManager.cpp
)

target_include_directories(resource_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(resource_core PUBLIC project_warnings project_sanitizers)