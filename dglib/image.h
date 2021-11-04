#ifndef DGLIB_IMAGE_H
#define DGLIB_IMAGE_H

#include <cstddef> // size_t
#include <vector> // vector
#include <limits> // numeric_limits

#include "exception.h" // dglib::exception, std::move
#include "kernel_type.h" // kernel_t, matrix_t

namespace dglib
{
    template <typename T> class image
    {
        friend class ppm;

        private:
            // members
            std::vector<T> _data;
            std::size_t _width;
            std::size_t _height;
            std::size_t _channels;

            // exceptions
            struct _exception_image_at;
            struct _exception_image_convolve;

            // methods
            void _at_check_params(std::size_t y, std::size_t x, std::size_t c) const;

        public:
            // constructors
            image(std::size_t height, std::size_t width, std::size_t channels, T* data);
            image(std::size_t height, std::size_t width, std::size_t channels, std::vector<T> data);

            // operators
            bool operator == (const image<T>& compare_to_image) const;

            // getters
            T                   at      (std::size_t y, std::size_t x, std::size_t c) const;
            std::size_t         width   ()                                      const { return _width; }
            std::size_t         height  ()                                      const { return _height; }
            std::size_t         channels()                                      const { return _channels; }

            // methods
            image<T> convolve(kernel_t);
    };

    // private:
    // exceptions
    template <typename T> struct image<T>::_exception_image_at : exception
    {
        explicit _exception_image_at(std::string error_message) : exception(error_message) {}
    };

    template <typename T> struct image<T>::_exception_image_convolve : exception
    {
        explicit _exception_image_convolve(std::string error_message) : exception(error_message) {}
    };

    // methods
    template <typename T> void image<T>::_at_check_params(std::size_t y, std::size_t x, std::size_t c) const {
        if (x >= _width )
        {
            throw _exception_image_at("The 'x' coordinate (" + std::to_string(x) + ") is greater then the image width (" + std::to_string(_width) + ")");
        }
        else if (y >= _height)
        {
            throw _exception_image_at("The 'y' coordinate (" + std::to_string(y) + ") is greater then the image height (" + std::to_string(_height) + ")");
        }
        else if (c >= _channels)
        {
            throw _exception_image_at("The 'c' coordinate (" + std::to_string(c) + ") is greater then the image channels (" + std::to_string(_channels) + ")");
        }
    }

    // public:
    // constructors
    template <typename T> image<T>::image(std::size_t height, std::size_t width, std::size_t channels, T* data) : _height(height), _width(width), _channels(channels)
    {
        _data.insert(_data.end(), data, data + width * height * channels);
    }

    template <typename T> image<T>::image(std::size_t height, std::size_t width, std::size_t channels, std::vector<T> data) : _height(height), _width(width), _channels(channels)
    {
        _data = data;
    }

    // operators
    template <typename T> bool image<T>::operator == (const image<T>& compare_to_image) const
    {
        if (_width == compare_to_image._width() and _height == compare_to_image._height and _channels == compare_to_image._channels and _data == compare_to_image._data) return true;
        else return false;
    }

    // getters
    template <typename T> T image<T>::at(std::size_t y, std::size_t x, std::size_t c) const
    {
        _at_check_params(y, x, c);
        return _data[c + _channels * x + _channels * _width * y];
    }

    template <typename T> image<T> image<T>::convolve(kernel_t kernel)
    {
        // Copy and cost kernel data
        const matrix_t  kernel_matrix = kernel.matrix();
        const std::size_t kernel_height = kernel.height();
        const std::size_t kernel_width = kernel.width();
        const float kernel_scale = kernel.scale();

        // Check if kernel has odd height and width
        if (kernel_height % 2 == 0)
        {
            throw _exception_image_convolve("Kernel height has to be odd: 'kernel_height' = " + std::to_string(kernel_height));
        }
        else if (kernel_width % 2 == 0)
        {
            throw _exception_image_convolve("Kernel width has to be odd: 'kernel_width' = " + std::to_string(kernel_width));
        }

        // Check if kernel height is equal to kernel width ( Even though it should be possible to mate it work even if it is not a square matrix )
        if (kernel_height != kernel_width)
        {
            throw _exception_image_convolve("'kernel_width' (" + std::to_string(kernel_width) + ") has to be the same as 'kernel_height' (" + std::to_string(kernel_height));
        }

        // Pre-allocate the output image
        std::vector<T> conv_data; conv_data.resize(_height * _width * _channels, 0);

        // Convolve
        std::size_t kernel_center = kernel_width /2;
        long long sum;

        for (std::size_t img_c = 0; img_c < _channels; img_c++)
        {
            for (std::size_t img_y = 0; img_y < _height; img_y++)
            {
                for (std::size_t img_x = 0; img_x < _width; img_x++)
                {
                    sum = 0;
                    for (std::size_t ker_y = 0; ker_y < kernel_height; ker_y++)
                    {
                        for (std::size_t ker_x = 0; ker_x < kernel_width; ker_x++)
                        {
                            if((img_y + ker_y - kernel_center) < _height && (img_x + ker_x - kernel_center) < _width)
                            {
                                sum += at(img_y + ker_y - kernel_center, img_x + ker_x - kernel_center, img_c) * kernel_matrix[ker_y][ker_x];
                            }
                        }
                    }
                    sum /= kernel_scale;
                    if(sum < 0) sum = 0;
                    if(sum > 255) sum = std::numeric_limits<T>::max();

                    conv_data[img_c + _channels * img_x + _channels * _width * img_y] = sum;
                }
            }
        }
        return {_height, _width, _channels, conv_data};
    }
}

#endif