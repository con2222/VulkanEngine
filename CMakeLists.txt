cmake_minimum_required(VERSION 4.1)
project(VulkanEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

find_program(GLSLC_EXECUTABLE NAMES glslc HINTS $ENV{VULKAN_SDK}/bin)
if(NOT GLSLC_EXECUTABLE)
    message(FATAL_ERROR "Compiler glslc not found!")
endif()

set(SHADER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(SHADER_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

set(SHADERS
    ${SHADER_SRC_DIR}/simple_shader.vert
    ${SHADER_SRC_DIR}/simple_shader.frag
)

set(SPIRV_SHADERS "")

foreach(SHADER ${SHADERS})
    get_filename_component(FILE_NAME ${SHADER} NAME)
    set(SPIRV_FILE ${SHADER_BIN_DIR}/${FILE_NAME}.spv)
    list(APPEND SPIRV_SHADERS ${SPIRV_FILE})

    add_custom_command(
            OUTPUT ${SPIRV_FILE}
            COMMAND ${GLSLC_EXECUTABLE} ${SHADER} -o ${SPIRV_FILE}
            DEPENDS ${SHADER}
            COMMENT "Компилируем шейдер: ${FILE_NAME}"
    )
endforeach()

add_custom_target(CompileShaders DEPENDS ${SPIRV_SHADERS})

add_executable(${PROJECT_NAME} main.cpp lve_window.cpp first_app.cpp lve_pipeline.cpp lve_device.cpp lve_swap_chain.cpp
        lve_model.cpp
        lve_model.hpp
        lve_game_object.cpp
        lve_game_object.h)
add_dependencies(${PROJECT_NAME} CompileShaders)

target_include_directories(${PROJECT_NAME} PRIVATE external)

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)