#pragma once
#include "lve_device.hpp"

// std
#include <vector>

// libs
#define GLM_FORCE_RADIANS // This makes sure that no matter what system you're on the glm functions will expect angles to be specified in radians not degrees
#define GLM_FORCE_DEPTH_ZERO_TO_ONE // This tells GLM to expect out depth buffer values to range from 0 to 1
#include "glm/glm.hpp"


namespace lve {
    class LveModel {
    public:

        struct Vertex {
            glm::vec2 position;
            glm::vec3 color;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        LveModel(LveDevice& device, const std::vector<Vertex>& vertices);
        ~LveModel();

        LveModel(const LveModel&) = delete;
        LveModel& operator=(const LveModel&) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

    private:
        void createVertexBuffers(const std::vector<Vertex>& vertices);

        LveDevice& lveDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
    };
}
