#include "lve_window.hpp"

namespace lve {
    LveWindow::LveWindow(int w, int h, std::string name) : width(w), height(h), windowName(name) {
        initWindow();
    }

    void LveWindow::initWindow() {
        glfwInit(); // initialize glfw lib
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // not to create opengl context

    }
}
