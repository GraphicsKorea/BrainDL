cmake_minimum_required(VERSION 3.20)
project(BrainDL)

add_library(Brain STATIC
#    include/brain/tensor.h
    include/brain/handle.h
    include/brain/intrusive_ptr.h
    include/brain/body.h
    include/brain/variable.h
    include/brain/function.h
#    src/tensor.cpp
    src/handle.cpp
    src/body.cpp
    src/variable.cpp
    src/function.cpp
    src/detail/variable.h
    src/detail/variable.cpp
    src/detail/function.h
    src/detail/function.cpp
#    include/BrainML/Device.h
#    include/BrainML/Buffer.h
#    src/Device.cpp
#    src/Buffer.cpp
        )

target_include_directories(Brain
    PUBLIC include)

target_compile_features(Brain
    PUBLIC cxx_std_20)

find_package(Vulkan REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(xtensor CONFIG REQUIRED)
target_link_libraries(Brain
    PUBLIC Vulkan::Vulkan spdlog::spdlog xtensor)

add_executable(Test
#        test/tensor_test.cpp
        test/body_test.cpp
        test/intrusive_ptr_test.cpp
        test/handle_test.cpp
        test/variable_test.cpp
        test/function_test.cpp)

find_package(Catch2 CONFIG REQUIRED)

target_link_libraries(Test
        Brain
        Catch2::Catch2WithMain)
