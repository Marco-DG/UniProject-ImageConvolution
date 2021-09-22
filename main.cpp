#include "dglib/ppm.h"
#include "dglib/kernel.h"

int main() {

    using namespace dglib;

    auto im = ppm::read("../lena.ppm");

    ppm::write(im.convolve(kernel::Identity             ), "../output_images/Identity.ppm"              );
    ppm::write(im.convolve(kernel::UnsharpMasking_5x5   ), "../output_images/UnsharpMasking_5x5.ppm"    );
    ppm::write(im.convolve(kernel::WeakEdgeDetection    ), "../output_images/WeakEdgeDetection.ppm"     );
    ppm::write(im.convolve(kernel::MediumEdgeDetection  ), "../output_images/MediumEdgeDetection.ppm"   );
    ppm::write(im.convolve(kernel::StrongEdgeDetection  ), "../output_images/StrongEdgeDetection.ppm"   );
    ppm::write(im.convolve(kernel::Sharpen              ), "../output_images/Sharpen.ppm"               );
    ppm::write(im.convolve(kernel::BoxBlur              ), "../output_images/BoxBlur.ppm"               );
    ppm::write(im.convolve(kernel::GaussianBlur_3x3     ), "../output_images/GaussianBlur_3x3.ppm"      );
    ppm::write(im.convolve(kernel::GaussianBlur_5x5     ), "../output_images/GaussianBlur_5x5.ppm"      );
}

/*
 *
 *         float sum;
        for (std::size_t img_c = 0; img_c < _channels; img_c++)
        {
            for (std::size_t img_y = 0; img_y < _height - kernel_height +1; img_y++)
            {
                for (std::size_t img_x = 0; img_x < _width - kernel_width +1; img_x++)
                {
                    sum = 0;
                    for (std::size_t ker_y = 0; ker_y < kernel_height; ker_y++)
                    {
                        for (std::size_t ker_x = 0; ker_x < kernel_width; ker_x++)
                        {
                            sum += at(img_y + ker_y, img_x + ker_x, img_c) * kernel_matrix[ker_y][ker_x]; //* kernel_factor; // TODO: se divido per /256 ovviamente và tutto a 0, diventando un'immagine nera... proprio non capisco.
                        }
                    }
                    conv_data[img_c + _channels * img_x + _channels * _width * img_y] = sum ;
                }
            }
        }
        return {_height, _width, _channels, conv_data};
    }
}
 */

    /*
    size_t dimensions[2] = {3, 3};
    int data[9] = {1,2,3,4,5,6,7,8,9};

    array<int> arr (9, data);
    std::cout << arr[3] << std::endl;
    //std::cout << arr.size() << std::endl;
    */

    //multidimensional_array<int> arr (2, dimensions, data);






    //


    //printf("%" PRIu8 "\n", im.data[0]);
    //im.convolve();

   // ppm::write(convoved_im, "../lena_convolved.ppm");



/*
 *
            matrix(size_t, size_t);
            matrix(size_t, size_t, T&);
            matrix(matrix&);


 *
        template <typename T> matrix<T>::matrix(std::size_t rows, std::size_t cols) : rows(rows), cols(cols), data(new T[rows * cols]) {}

    template <typename T> matrix<T>::matrix(std::size_t rows, std::size_t cols, T& copy_data) : rows(rows), cols(cols), data(new T[rows * cols])
    {
        std::copy(copy_data, copy_data + rows * cols, data);
    }

    template <typename T> matrix<T>::matrix(matrix& copy_matrix) : rows(copy_matrix.rows), cols(copy_matrix.cols), data(new T[rows * cols])
    {
        std::copy(copy_matrix.data, copy_matrix.data + rows * cols, data);
    }
 */


/*
rgb8_image_t img;
read_image("test.jpg", img, jpeg_tag{});

// Convolve the rows and the columns of the image with a fixed kernel
rgb8_image_t convolved(img);

// radius-1 Gaussian kernel, size 9
float gaussian_1[]={0.00022923296f,0.0059770769f,0.060597949f,0.24173197f,0.38292751f,
                    0.24173197f,0.060597949f,0.0059770769f,0.00022923296f};

kernel_1d_fixed<float,9> kernel(gaussian_1,4);
convolve_rows_fixed<rgb32f_pixel_t>(const_view(convolved),kernel,view(convolved));
convolve_cols_fixed<rgb32f_pixel_t>(const_view(convolved),kernel,view(convolved));
write_view("out-convolution.jpg", view(convolved), jpeg_tag{});

// This is how to use a resizable kernel
kernel_1d<float> kernel2(gaussian_1,9,4);
convolve_rows<rgb32f_pixel_t>(const_view(img),kernel2,view(img));
convolve_cols<rgb32f_pixel_t>(const_view(img),kernel2,view(img));
write_view("out-convolution2.jpg", view(img), jpeg_tag{});
*/

//dglib::matrix<int> mat(3, 3);
//auto im = new dglib::rgb_image();
//im->read_ppm("./lena.ppm");
//dglib::image<dglib::rgb> im = new dglib::image<dglib::rgb>();
//= dglib::rgb_image::read_ppm("./lena.ppm");
/**
 *  Read P3 and P6 .ppm file types.
 *  Does not support comments.
 *  Supports only 8 bit-depth
 */

/*
#include <string>
#include <fstream>
#include "matrix.h"

#include <iostream> //TMP

namespace dglib
{
    typedef matrix<uint8_t> rgb8_t;

    template <typename T> class image : public matrix<T>
    {
    public:
        image() : matrix<T>() {}
        void read_ppm(std::string);
    };


    template <typename T> void image<T>::read_ppm(std::string file_path)
    {
        std::string magic_number, width, height, max_value, tmp;
        std::ifstream input_file(file_path, std::ifstream::binary);

        if (input_file.fail())
        {
            throw std::invalid_argument("Failed to open: " + file_path);
        }

        input_file >> magic_number;
        input_file >> width;
        input_file >> height;
        input_file >> max_value;

        if (magic_number == "P3")
        {

        }
        else if (magic_number == "P6")
        {
            input_file.read(reinterpret_cast<char *>(mBuffer), mW * mH * 3);
        }
        else
        {

        }

        std::cout<<magic_number<<std::endl<<width<<std::endl<<height<<std::endl<<max_value<<std::endl;
    }
}
*/

/*
 *     {
        private:
            std::string error_message;
        public:
            explicit image_io_invalid_file_exception(std::string error_message) : error_message(error_message) {}
            const char* what() const noexcept override { return this->error_message.c_str(); }
    };
 */

/*
 *
 * #ifndef DGLIB_MATRIX_H
#define DGLIB_MATRIX_H

#include <cstddef> // size_t

namespace dglib
{
    template <typename T> class matrix
    {
        protected:
            T* data;
            std::size_t rows;
            std::size_t cols;

        public:
            matrix(std::size_t, std::size_t);
            virtual ~matrix();
    };

    template <typename T> matrix<T>::matrix(std::size_t rows, std::size_t cols) : rows(rows), cols(cols), data(new T[rows * cols]) {}

    template <typename T> matrix<T>::~matrix()
    {
        delete [] data;
    }
}

#endif
 */

/*
 *
 *
 * #ifndef DGLIB_IMAGE_H
#define DGLIB_IMAGE_H

#include "matrix.h"
#include "array.h"

namespace dglib
{
    typedef uint8_t grey8_t;
    typedef uint16_t grey16_t;
    typedef array<uint8_t> rgb8_t;
    typedef array<uint16_t> rgb16_t;

    template <typename T> class image : public matrix<T>
    {
        private:
            std::size_t channels;
        public:
            image();
            image(std::size_t, std::size_t);
    };

    template <typename T> image<T>::image() : matrix<T>() {}

    template <typename T> image<T>::image(std::size_t width, std::size_t height) : matrix<T>(width, height) {}
}

#endif
 */


/*
 *
                skip_to_data(input_file), input_file >> max_color_value;

                if (magic_number == "P3")
                {

                }
                else if (magic_number == "P6")
                {
                    //uint8_t buffer;
                    //infile.read(reinterpret_cast<char *>(buffer), (std::size_t)width * height * 3);
                }
                else
                {
                    throw image_io_invalid_file_exception("Incorrect magic number: " + magic_number);
                }
 */

/*
 * #ifndef DGLIB_IMAGE_H
#define DGLIB_IMAGE_H

#include "matrix_3D.h"

namespace dglib
{
    template <typename T> class image : public matrix_3D<T>
    {
        public:
            image();
            image(std::size_t, std::size_t, std::size_t);
            image(std::size_t, std::size_t, std::size_t, T&);
    };

    template <typename T> image<T>::image() : matrix_3D<T>() {}

    template <typename T> image<T>::image(std::size_t width, std::size_t height, std::size_t channels) : matrix_3D<T>(width, height, channels) {}

    template <typename T> image<T>::image(std::size_t width, std::size_t height, std::size_t channels, T& copy_data) : matrix_3D<T>(width, height, channels, copy_data) {}
}

#endif
 */

/*
 *                 // Restructure the buffer to be a three-dimensional array: https://stackoverflow.com/a/54283119/8411453
                uint8_t (*uint8_image)[height][3] = (uint8_t (*)[height][3]) uint8_buffer;



 */

/*
 *
 * namespace dglib
;
    using std::array, std::size_t;

    template <typename T, array<std::size_t> dimensions> class multidimensional_array
    {
        protected:
            array<T, std::> data;

        public:
            multidimensional_array(&array<T>, &array<size_t>);
    };

    template <typename T> multidimensional_array<T>::multidimensional_array(&array<T> data, &array<size_t>)
}
 */

/*
 *
 * #ifndef DGLIB_ARRAY_H
#define DGLIB_ARRAY_H

namespace dglib
{
    template <typename T> class array
    {
        protected:
            T* data;
            size_t size;

        public:
            array(T*, size_t);
            virtual ~array();


            T sum();
            T sum(size_t);
            T sum(size_t, size_t);
            // T sum(T*, size_t, size_t);
            T prod();
            T prod(size_t);
            T prod(size_t, size_t);
            // T prod(T*, size_t, size_t);
    };

    template <typename T> array<T>::array(T* data, size_t size) : data(new T[size]), size(size) {}

    template <typename T> array<T>::~array()
    {
        delete [] data;
    }

    template <typename T> T array<T>::sum()
    {
        return sum(0, this->size);
    }

    template <typename T> T array<T>::sum(size_t end)
    {
        return sum(0, end);
    }

    template <typename T> T array<T>::sum(size_t beg, size_t end)
    {
        T accum = 0;
        for (size_t i = beg; i < end; i++)
        {
            accum += data[i];
        }
        return accum;
    }

    template <typename T> T sum(T* array, size_t beg, size_t end)
    {

    }

    template <typename T> T array<T>::prod()
    {
        return prod(0, this->size);
    }

    template <typename T> T array<T>::prod(size_t end)
    {
        return prod(0, end);
    }

    template <typename T> T array<T>::prod(size_t beg, size_t end)
    {
        T accum = 0;
        for (size_t i = beg; i < end; i++)
        {
            accum *= data[i];
        }
        return accum;
    }
}

#endif
 */


/*7
 *
 *     template <typename T> T array<T>::sum()
    {
        return sum(0, this->size);
    }

    template <typename T> T array<T>::sum(size_t end)
    {
        return sum(0, end);
    }

    template <typename T> T array<T>::sum(size_t beg, size_t end)
    {
        T accum = 0;
        for (size_t i = beg; i < end; i++)
        {
            accum += data[i];
        }
        return accum;
    }

    template <typename T> T sum(T* array, size_t beg, size_t end)
    {

    }

    template <typename T> T array<T>::prod()
    {
        return prod(this->data, 0, this->size);
    }

    template <typename T> T array<T>::prod(size_t end)
    {
        return prod(this->data, 0, end);
    }

    template <typename T> T array<T>::prod(size_t beg, size_t end)
    {
        return prod(this->data, beg, end);
    }

    static template <typename T> T array<T>::prod(T* array, size_t beg, size_t end)
    {
        T accum = 0;
        for (size_t i = beg; i < end; i++)
        {
            accum *= array[i];
        }
        return accum;
    }

    */




/*
 *
 *
 * #ifndef DGLIB_IMAGE_H
#define DGLIB_IMAGE_H

#include "multidimensional_array.h"

namespace dglib
{
    template <typename T> class image
    {
        public: // TODO: private
        T *data;
        size_t width;
        size_t height;
        size_t channels;

        public:
            image(size_t, size_t, size_t, T*);
            ~image();


            image<T> convolve(std::vector<std::vector<float> >);
    };

    template <typename T> image<T>::image(size_t width, size_t height, size_t channels, T* data) : width(width), height(height), channels(channels), data(data) {}

    template <typename T> image<T>::~image()
    {
        delete [] data;
    }

    template <typename T> image<T> image<T>::convolve(std::vector<std::vector<float> > kernel)
    {
        float sum;
        for (size_t img_y = 0; img_y < height; img_y++)
        {
            for (size_t img_x = 0; img_x < width; img_x++)
            {
                sum = 0;
                for (size_t ker_y = 0; ker_y < kernel.size(); ker_y++)
                {
                    for (size_t ker_x = 0; ker_x < kernel[0].size(); ker_x++)
                    {

                    }
                }
            }
        }



        return image<T> (5, 5, 3, nullptr);
    }
}

#endif
*/
/*
 * def conv2d_slow(img, krn):
    import numpy as np

    is0, is1, ks0, ks1 = *img.shape, *krn.shape
    rs0, rs1 = is0 - ks0 + 1, is1 - ks1 + 1
    res = np.zeros((rs0, rs1), dtype = krn.dtype)

    for i in range(rs0):
        for j in range(rs1):
            res[i, j] = (krn * img[i : i + ks0, j : j + ks1]).sum()

    return res
 */


/*
 *
 *         // I think is possible to implement it even if the kernel is not a square matrix, I never saw it being implemented that way though.
        if (kernel_width != kernel_height)
        {
            throw exception_image_convolve("The kernel is not a square matrix: kernel_width (" + std::to_string(kernel_width) + "), kernel_height (" + std::to_string(kernel_height) + ")");
        }

        // distance between the central element of the kernel and the border
        // mat 3x3: kernel_radius = 1
        // mat 5x5: kernel_radius = 2
        std::size_t kernel_radius = kernel_width /2;

        float sum;
        // Iterate channels
        for (std::size_t img_c = 0; img_c < _channels; img_c++)
        {
            // I have no intention to implement anything for the borders. therefore I'll:
            // leave a number of rows and columns equal to 'kernel_radius' at the top and left
            // leave a number of rows and columns equal to 'kernel_width' and 'kernel_height' (they are equal) at the bottom and right
 *
 */