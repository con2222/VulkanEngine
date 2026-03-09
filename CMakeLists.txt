cmake_minimum_required(VERSION 4.1)
project(VulkanEngine)

set(CMAKE_CXX_STANDARD 20)

# 1. Находим ядро Vulkan (CMake сам найдет SDK, который мы установили)
find_package(Vulkan REQUIRED)

# 2. Подключаем GLFW из исходников
# Отключаем сборку документации и тестов GLFW, чтобы они не засоряли проект
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

add_executable(${PROJECT_NAME} main.cpp)

# 4. Подключаем заголовочные файлы GLM
# Указываем путь к папке external, чтобы писать в коде #include <glm/glm.hpp>
target_include_directories(${PROJECT_NAME} PRIVATE external)


# 5. Линкуем всё вместе (Твой код + Vulkan + GLFW)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glfw)