//
// Created by Danny Jang on 2021/11/20.
//

#include "BrainML/Buffer.h"

#include "BrainML/Device.h"

using namespace brain;

Buffer::Buffer(Device* device, size_t size)
        :device_{device}, size_{size}
{
    create_buffer();
    allocate_memory();
    vkBindBufferMemory(device_->device(), buffer_, memory_, 0);
}

Buffer::Buffer(Buffer&& other) noexcept
        :device_{other.device_}, size_{other.size_}, buffer_{other.buffer_}, memory_{other.memory_},
         data_{other.data_}
{
    other.device_ = nullptr;
    other.size_ = 0;
    other.buffer_ = VK_NULL_HANDLE;
    other.memory_ = VK_NULL_HANDLE;
    other.data_ = nullptr;
}

Buffer& Buffer::operator=(Buffer&& other) noexcept
{
    if (this!=&other) {
        device_ = other.device_;
        size_ = other.size_;
        buffer_ = other.buffer_;
        memory_ = other.memory_;
        data_ = other.data_;

        other.device_ = nullptr;
        other.size_ = 0;
        other.buffer_ = VK_NULL_HANDLE;
        other.memory_ = VK_NULL_HANDLE;
        other.data_ = nullptr;
    }

    return *this;
}

void* Buffer::map()
{
    if (!data_) {
        vkMapMemory(device_->device(), memory_, 0, sizeof(float), 0, &data_);
    }

    return data_;
}

void Buffer::unmap()
{
    if (data_) {
        vkUnmapMemory(device_->device(), memory_);
        data_ = nullptr;
    }
}

void Buffer::create_buffer()
{
    VkBufferCreateInfo create_info = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .size = size_,
            .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
    };

    vkCreateBuffer(device_->device(), &create_info, nullptr, &buffer_);
}

void Buffer::allocate_memory()
{
    VkMemoryRequirements requirements;
    vkGetBufferMemoryRequirements(device_->device(), buffer_, &requirements);

    VkPhysicalDeviceMemoryProperties properties;
    vkGetPhysicalDeviceMemoryProperties(device_->physical_device(), &properties);

    uint32_t index;
    for (int i = 0; i!=properties.memoryTypeCount; ++i) {
        if ((properties.memoryTypes[i].propertyFlags & requirements.memoryTypeBits)==0)
            continue;
        if (properties.memoryTypes[i].propertyFlags &
                (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) {
            index = i;
            break;
        }
    }

    VkMemoryAllocateInfo info{
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .allocationSize = requirements.size,
            .memoryTypeIndex = index
    };

    vkAllocateMemory(device_->device(), &info, nullptr, &memory_);
}