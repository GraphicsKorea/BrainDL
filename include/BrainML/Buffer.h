//
// Created by Danny Jang on 2021/11/20.
//

#ifndef BRAIN_BUFFER_H
#define BRAIN_BUFFER_H

#include <vulkan/vulkan.h>

namespace brain {

class Device;

class Buffer {
public:
    Buffer() = default;

    Buffer(Device* device, size_t size);

    Buffer(const Buffer& other) = delete;

    Buffer(Buffer&& other) noexcept;

    Buffer& operator=(const Buffer& other) = delete;

    Buffer& operator=(Buffer&& other) noexcept;

    [[nodiscard]]
    void* map();

    void unmap();

    [[nodiscard]]
    inline auto device() const;

    [[nodiscard]]
    inline auto size() const;

private:
    void create_buffer();

    void allocate_memory();

private:
    Device* device_{nullptr};
    size_t size_{0};
    VkBuffer buffer_{VK_NULL_HANDLE};
    VkDeviceMemory memory_{VK_NULL_HANDLE};
    void* data_{nullptr};
};

auto Buffer::device() const
{
    return device_;
}

auto Buffer::size() const
{
    return size_;
}

} //brain

#endif //BRAIN_BUFFER_H
