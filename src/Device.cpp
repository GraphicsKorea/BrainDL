//
// Created by Danny Jang on 2021/11/16.
//

#include "BrainML/Device.h"

#include <vector>
#include "BrainML/Buffer.h"

using namespace brain;

Device::Device()
{
    create_instance();
    find_best_physical_device();
    create_device();
}

Device::~Device()
{
    vkDestroyDevice(device_, nullptr);
    vkDestroyInstance(instance_, nullptr);
}

std::unique_ptr<Buffer> Device::create_buffer(size_t size)
{
    return std::make_unique<Buffer>(this, size);
}

void Device::create_instance()
{
    uint32_t count;
    vkEnumerateInstanceLayerProperties(&count, nullptr);

    std::vector<VkLayerProperties> properties(count);
    vkEnumerateInstanceLayerProperties(&count, properties.data());

    vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);

    std::vector<VkExtensionProperties> extension_properties(count);
    vkEnumerateInstanceExtensionProperties(nullptr, &count, extension_properties.data());

    const VkApplicationInfo application_info{
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pEngineName = "BrainML",
            .engineVersion = VK_MAKE_VERSION(0, 1, 0),
            .apiVersion = VK_MAKE_VERSION(1, 0, 0)
    };

    const VkInstanceCreateInfo create_info{
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &application_info
    };

    vkCreateInstance(&create_info, nullptr, &instance_);
}

void Device::find_best_physical_device()
{
    uint32_t count;
    vkEnumeratePhysicalDevices(instance_, &count, nullptr);

    std::vector<VkPhysicalDevice> physical_devices(count);
    vkEnumeratePhysicalDevices(instance_, &count, physical_devices.data());

    physical_device_ = physical_devices[0];

}

void Device::create_device()
{
    const VkDeviceCreateInfo create_info{
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO
    };

    vkCreateDevice(physical_device_, &create_info, nullptr, &device_);
}

std::unique_ptr<Device> brain::gDevice = std::make_unique<Device>();