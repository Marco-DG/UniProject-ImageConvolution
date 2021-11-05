#include "gtest/gtest.h"
#include "../dglib/ppm.h"

#include <cstddef> // size_t
#include <cstdint> // uint8_t
#include <string> // string
#include <vector> // vector

using namespace dglib;

const std::string ppm_read_path = "test/test_image.ppm";
const std::string ppm_write_path = "test/test_image_ppm_write.tmp.ppm";
const std::string test_image_invalid_path = "";
const std::string test_image_invalid_magic_number_path = "test/test_image_invalid_magic_number.ppm";
const std::string test_image_invalid_max_color_value_path = "test/test_image_invalid_max_color_value.ppm";

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
    image<uint8_t> ppm_read_image = ppm::read(ppm_read_path);
    ASSERT_EQ(ppm_read_image == test_image, true);
}

TEST(ppm, write)
{
    ppm::write(test_image, ppm_write_path);
    image<uint8_t> ppm_write_image = ppm::read(ppm_write_path);
    ASSERT_EQ(ppm_write_image == test_image, true);
}

TEST(ppm, _exception_ppm_read)
{
    EXPECT_THROW(ppm::read(test_image_invalid_path), ppm::_exception_ppm_read);
    EXPECT_THROW(ppm::read(test_image_invalid_magic_number_path), ppm::_exception_ppm_read);
    EXPECT_THROW(ppm::read(test_image_invalid_max_color_value_path), ppm::_exception_ppm_read);
}

TEST(ppm, _exception_ppm_write)
{
    image<uint8_t> invalid_channels_number_image (1000, 5000, 4, nullptr);
    EXPECT_THROW(ppm::write(invalid_channels_number_image, ppm_write_path), ppm::_exception_ppm_write);
}