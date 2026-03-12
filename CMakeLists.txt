cmake_minimum_required(VERSION 3.12)
project(Minesweeper)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Include SDL libraries
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# Define a variable to hold all source files
set(SOURCES
    src/main.cpp
    src/tileRender.cpp
)

# Add extra files
set(EXTRAS
    extras/MinesweeperTileset.png
)
install(FILES ${EXTRAS} 
    DESTINATION "${CMAKE_BINARY_DIR}/$<CONFIGURATION>/extras")

# Create an executable from the specified source files
add_executable(${PROJECT_NAME} ${SOURCES} ${EXTRAS})

# Add custom headers
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Link to the actual SDL3 library.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image SDL3::SDL3)