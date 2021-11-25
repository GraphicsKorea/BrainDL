//
// Created by Danny Jang on 2021/11/16.
//

#include <catch2/catch.hpp>
#include <BrainML/Device.h>
#include <BrainML/Buffer.h>

using namespace brain;

TEST_CASE("Create Device", "[Device]")
{
    CHECK_NOTHROW([] { Device device; });
}

TEST_CASE("Create Tensor", "[Device]")
{
    auto device = std::make_unique<Device>();
    REQUIRE(device);

    CHECK_NOTHROW([&device] { device->create_buffer(256); });
}