cmake_minimum_required(VERSION 3.12)
project(Minesweeper)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>")

# Include SDL libraries
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# Define a variable to hold all source files
set(SOURCES
    src/main.cpp
    src/tilemap.cpp
)

# Add asset files
set(ASSET_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSET_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/assets")

# Create an executable from the specified source files
add_executable(${PROJECT_NAME} ${SOURCES})

# Copy assets on build
add_custom_command(
    TARGET ${PROJECT_NAME}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSET_SOURCE_DIR}"
        "${ASSET_BUILD_DIR}"
    COMMENT "Copying assets to build directory"
)


# Add custom headers
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Link to the actual SDL3 library.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image SDL3::SDL3)