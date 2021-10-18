#include "gtest/gtest.h"
#include "../dglib/ppm.h"

#include <cstddef> // size_t
#include <cstdint> // uint8_t
#include <string> // string
#include <vector> // vector

using namespace dglib;

const std::string ppm_read_path = "test/test_image.ppm";
const std::string ppm_write_path = "test/test_image_ppm_write.tmp.ppm";

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