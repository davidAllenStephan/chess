cmake_minimum_required(VERSION 3.14)
project(OPENGL_TEST VERSION 1.0.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_definitions(GL_SILENCE_DEPRECATION)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
if(APPLE)
    find_library(GLUT_LIBRARY GLUT)
    set(EXTRA_LIBS ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARY})
else()
    find_package(GLUT REQUIRED)
    set(EXTRA_LIBS ${OPENGL_gl_LIBRARY} ${GLUT_glut_LIBRARY})
endif()

find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating HTML documentation with Doxygen"
        VERBATIM
    )
else()
    message(STATUS "Doxygen not found, 'doc' target will not be available")
endif()

set(SOURCES
	src/ActionMask.cc
	src/BoardState.cc
	src/Display.cc
	src/FenReader.cc
	src/Piece.cc
	src/PositionMap.cc
	src/TextureManager.cc
	src/Mouse.cc
	src/SelectionState.cc
	src/stb_image.cc
)
add_library(lib OBJECT ${SOURCES})
target_include_directories(lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_executable(main app/main.cc)
target_link_libraries(main
    PRIVATE
	lib
	${EXTRA_LIBS}
)
set_target_properties(lib main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED NO
    CXX_EXTENSIONS NO
)

