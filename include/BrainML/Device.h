//
// Created by Danny Jang on 2021/11/16.
//

#ifndef BRAIN_DEVICE_H
#define BRAIN_DEVICE_H

#include <memory>
#include <vulkan/vulkan.h>
// #include "BrainML/tensor.h"

namespace brain {

class Buffer;
class tensor;

class Device {
public:
    Device();

    ~Device();

    Device(const Device& other) = delete;

    Device& operator=(const Device& other) = delete;

    std::unique_ptr<Buffer> create_buffer(size_t size);

    [[nodiscard]]
    inline auto physical_device() const;

    [[nodiscard]]
    inline auto device() const;

private:
    void create_instance();

    void find_best_physical_device();

    void create_device();

private:
    VkInstance instance_{VK_NULL_HANDLE};
    VkPhysicalDevice physical_device_{VK_NULL_HANDLE};
    VkDevice device_{VK_NULL_HANDLE};
};

inline auto Device::physical_device() const
{
    return physical_device_;
}

inline auto Device::device() const
{
    return device_;
}

extern std::unique_ptr<Device> gDevice;

} //brain

#endif //BRAIN_DEVICE_H
