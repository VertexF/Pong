add_library(IMGUI STATIC imgui.cpp imgui.h
                         imgui_demo.cpp
                         imgui_draw.cpp
                         imgui_tables.cpp
                         imgui_internal.h
                         imgui_widgets.cpp
                         imstb_rectpack.h
                         imstb_textedit.h
                         imstb_truetype.h
                         backends/imgui_impl_opengl3.h
                         backends/imgui_impl_opengl3.cpp
                         backends/imgui_impl_glfw.h
                         backends/imgui_impl_glfw.cpp)

if(MSVC)
    set_property(TARGET IMGUI PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(GLEW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}../../glew-2.1.0/include")
set(GLFW_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}../../glfw/include")

find_package(OpenGL REQUIRED)

set_property(
    TARGET IMGUI
    APPEND
    PROPERTY COMPILE_DEFINITIONS GLEW_NO_GLU GLEW_STATIC
)

target_link_libraries(IMGUI OpenGL::GL OpenGL::GLU GLFW GLEW)
include_directories(IMGUI ${CMAKE_CURRENT_SOURCE_DIR} ${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
