cmake_minimum_required(VERSION 3.15)
project(VoxelGame)

set(CMAKE_CXX_STANDARD 20)

# Add GLFW
add_subdirectory(Libraries/glfw-3.4)
include_directories(glm-master)
include_directories(Libraries)

# Create executable
add_executable(VoxelGame
        src_code/main.cpp
        Libraries/glad/src/glad.c
        src_code/abstraction.h
        src_code/abstraction.cpp
        src_code/game.h
        src_code/game.cpp
        src_code/texture.h
        src_code/texture.cpp
)

# FORCE ABSOLUTE PATHS FOR HEADERS
target_include_directories(VoxelGame PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glfw-3.4/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glad/include"     # Keep this so main.cpp works
        "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glad/src"             # ADD THIS so glad.c works
)
# Link libraries
target_link_libraries(VoxelGame glfw)

if(WIN32)
    target_link_libraries(VoxelGame opengl32)
elseif(APPLE)
    target_link_libraries(VoxelGame "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
else()
    target_link_libraries(VoxelGame GL dl pthread)
endif()

