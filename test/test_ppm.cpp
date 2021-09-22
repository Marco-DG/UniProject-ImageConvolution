#include "gtest/gtest.h"
#include "../dglib/ppm.h"

#include <cstddef> // size_t
#include <cstdint> // uint8_t
#include <string> // string
#include <vector> // vector

using namespace dglib;

const std::string ppm_read_path = "../../test/test_image.ppm";
const std::string ppm_write_path = "../../test/test_image_ppm_write.tmp.ppm";

// test_image.ppm
const image<uint8_t> test_image (2, 3, 3,{
    255,   0,   0,  // red
      0, 255,   0,  // green
      0,   0, 255,  // blue
    255, 255,   0,  // yellow
    255, 255, 255,  // white
      0,   0,   0,  // black
});

TEST(ppm, read)
{
    // function to test
    image<uint8_t> im = ppm::read(ppm_read_path);
    std::vector<uint8_t> ppm_read_image_data = im.data();

    // copy test_image._data
    // ( we copy to avoid a possible pointer misuse, given that the test_image is small)
    std::vector<uint8_t> test_image_data = test_image.data();

    for (std::size_t i = 0; i < test_image_data.size(); i++)
    {
        ASSERT_EQ(test_image_data[i], ppm_read_image_data[i]);
    }
}

TEST(ppm, write)
{
    // function to test
    ppm::write(test_image, ppm_write_path);

    // read the written image to be confronted with the reference image
    image<uint8_t> ppm_write_image = ppm::read(ppm_write_path);

    // copy test_image._data and ppm_write_image._data
    // ( we copy to avoid a possible pointer misuse, given that the test_image is small)
    std::vector<uint8_t> ppm_write_image_data = ppm_write_image.data();
    std::vector<uint8_t> test_image_data = test_image.data();

    for (char i = 0; i < 18; i++)
    {
        ASSERT_EQ(test_image_data[i], ppm_write_image_data[i]);
    }
}