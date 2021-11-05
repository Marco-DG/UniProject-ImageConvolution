#include "gtest/gtest.h"
#include "../dglib/image.h"
#include "../dglib/kernel.h"
#include "../dglib/ppm.h"

#include <cstddef> // size_t
#include <cstdint> // uint8_t
#include <vector> // vector

using namespace dglib;

const std::string test_image_path = "test/test_image_beaver.ppm";
const std::string test_image_convolved_path = "test/test_image_beaver_BoxBlurred.ppm";

// test_image.ppm
image<uint8_t> test_image (2, 3, 3,{
    255,   0,   0,  // red
      0, 255,   0,  // green
      0,   0, 255,  // blue
    255, 255,   0,  // yellow
    255, 255, 255,  // white
      0,   0,   0,  // black
});

TEST(image, at)
{
    // image.at(y,x,c) : return _data[c + _channels * x + _channels * _width * y];
    std::size_t img_c, img_x, img_y;

    // We create a mockup image trough iteration and then compare it to the original
    std::vector<uint8_t> mockup_image_data;
    for (std::size_t i = 0; i < test_image.height() * test_image.width() * test_image.channels(); i++)
    {
        img_c = i % test_image.channels(); // 0%3=0; 1%3=1; 2%3=2; 3%3=0; ...
        img_x = ( i / test_image.channels() ) % test_image.width(); // 0/3=0, 0%3=0; 1/3=0, 0%3=0; 2/3=0, 0%3=0; 3/3=1, 1%3=1; ...; 9/3=3, 3%3=0; ...
        img_y = ( i / ( test_image.channels() * test_image.width() ) ) % test_image.height(); // 0/9=0, 0%2=0; 1/9=0, 0%2=0; ...; 9/9=1 1%2=1; ...

        mockup_image_data.push_back(test_image.at(img_y, img_x, img_c));
    }
    image<uint8_t> mockup_image (test_image.height(), test_image.width(), test_image.channels(), mockup_image_data);
    ASSERT_EQ(test_image == mockup_image, true);
}

TEST(image, convolve)
{
    // using kernel::Identity
    image<uint8_t> conv_image = test_image.convolve(kernel::Identity);
    EXPECT_EQ(conv_image == test_image, true);

    // using kernel::BoxBlur
    conv_image = ppm::read(test_image_path).convolve(kernel::BoxBlur);
    test_image = ppm::read(test_image_convolved_path);
    EXPECT_EQ(conv_image == test_image, true);
}

TEST(image, _exception_image_at)
{
    EXPECT_THROW(test_image.at(test_image.height(), 0, 0), image<uint8_t>::_exception_image_at);
    EXPECT_THROW(test_image.at(0, test_image.width(), 0), image<uint8_t>::_exception_image_at);
    EXPECT_THROW(test_image.at(0, 0, test_image.channels()), image<uint8_t>::_exception_image_at);
}

TEST(image, _exception_image_convolve)
{
    kernel_t kernel_even_height ({
        { 1, 1, 1 },
        { 1, 1, 1 }
    }, 1);

    kernel_t kernel_even_width ({
        { 1, 1 },
        { 1, 1 },
        { 1, 1 }
    }, 1);

    kernel_t kernel_mismatched_width_height ({
        { 1 },
        { 1 },
        { 1 }
    }, 1);

    EXPECT_THROW(test_image.convolve(kernel_even_height), image<uint8_t>::_exception_image_convolve);
    EXPECT_THROW(test_image.convolve(kernel_even_width), image<uint8_t>::_exception_image_convolve);
    EXPECT_THROW(test_image.convolve(kernel_mismatched_width_height), image<uint8_t>::_exception_image_convolve);
}