#include "gtest/gtest.h"
#include "../dglib/image.h"
#include "../dglib/kernel.h"

#include <cstddef> // size_t
#include <cstdint> // uint8_t
#include <vector> // vector

using namespace dglib;

// test_image.ppm
const image<uint8_t> test_image (2, 3, 3,{
    255,   0,   0,  // red
      0, 255,   0,  // green
      0,   0, 255,  // blue
    255, 255,   0,  // yellow
    255, 255, 255,  // white
      0,   0,   0,  // black
});

TEST(image, at)
{
    // copy test_image._data
    // ( we copy to avoid a possible pointer misuse, given that the test_image is small)
    std::vector<uint8_t> test_image_data = test_image.data();

    // image.at(y,x,c) : return _data[c + _channels * x + _channels * _width * y];
    std::size_t img_c, img_x, img_y;
    for (std::size_t i = 0; i < test_image_data.size(); i++)
    {
        img_c = i % test_image.channels(); // 0%3=0; 1%3=1; 2%3=2; 3%3=0; ...
        img_x = ( i / test_image.channels() ) % test_image.width(); // 0/3=0, 0%3=0; 1/3=0, 0%3=0; 2/3=0, 0%3=0; 3/3=1, 1%3=1; ...; 9/3=3, 3%3=0; ...
        img_y = ( i / ( test_image.channels() * test_image.width() ) ) % test_image.height(); // 0/9=0, 0%2=0; 1/9=0, 0%2=0; ...; 9/9=1 1%2=1; ...

        // function to test
        ASSERT_EQ(test_image_data[i], test_image.at(img_y, img_x, img_c));
    }
}

TEST(image, convolve)
{
    // copy test_image and test_image._data
    // ( we copy to avoid a possible pointer misuse, given that the test_image is small)
    image<uint8_t> test_image_copy(test_image);
    std::vector<uint8_t> test_image_data = test_image.data();

    // function to test
    // using kernel::Identity
    image<uint8_t> conv_image = test_image_copy.convolve(kernel::Identity);
    std::vector<uint8_t> conv_image_data = conv_image.data();

    // we only expect the equality to hold, since in a convolution algorithm the edge processing is ill-defined
    for (std::size_t i = 0; i < test_image_data.size(); i++)
    {
        EXPECT_EQ(test_image_data[i], conv_image_data[i]);
    }
}
