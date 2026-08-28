cmake_minimum_required(VERSION 3.15)
project(VoxelGame)

set(CMAKE_CXX_STANDARD 20)

# Add GLFW
add_subdirectory(Libraries/glfw-3.4)
include_directories(glm-master)
include_directories(Libraries)

# Create executable
add_executable(VoxelGame
        Src/main.cpp
        Libraries/glad/src/glad.c
        Src/Abstraction/abstraction.h
        Src/Abstraction/abstraction.cpp
        Src/Game/game.h
        Src/Game/game.cpp
        Src/Texture/texture.h
        Src/Texture/texture.cpp
        Src/Block/block.h
        Src/Block/block.cpp
        Src/Chunk/chunk.h
        Src/Chunk/chunk.cpp
)

# FORCE ABSOLUTE PATHS FOR HEADERS
target_include_directories(VoxelGame PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glfw-3.4/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glad/include"     # Keep this so main.cpp works
        "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glad/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        "${CMAKE_CURRENT_SOURCE_DIR}/Shaders"
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

