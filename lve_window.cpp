#include "lve_window.hpp"

#include <stdexcept>

namespace lve {
    LveWindow::LveWindow(int w, int h, std::string name) : width(w), height(h), windowName(name) {
        initWindow();
    }

    LveWindow::~LveWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void LveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR*surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void LveWindow::initWindow() {
        glfwInit(); // initialize glfw lib
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // not to create opengl context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    }
}
