#ifndef DGLIB_PPM_H
#define DGLIB_PPM_H

#include <cstddef> // size_t
#include <cstdint> // uint8_t
#include <fstream> // string, ifstream, ofstream

#include "exception.h" // dglib::exception
#include "image.h" // image

namespace dglib
{
    // http://netpbm.sourceforge.net/doc/ppm.html
    class ppm
    {
        private:
            // exceptions
            struct _exception_ppm_read;
            struct _exception_ppm_write;

            // methods
            static bool _skip_whitespaces   (std::ifstream& stream);
            static bool _skip_comments      (std::ifstream& stream);
            static void _skip_to_data       (std::ifstream& stream);

        public:
            // methods
            static image<uint8_t>   read    (const std::string& file_path);
            static void             write   (image<uint8_t> image, const std::string& file_path);
    };

    // private:
    // exceptions
    struct ppm::_exception_ppm_read : exception
    {
        explicit _exception_ppm_read(std::string error_message) : exception(error_message) {}
    };

    struct ppm::_exception_ppm_write : exception
    {
        explicit _exception_ppm_write(std::string error_message) : exception(error_message) {}
    };

    // methods
    void ppm::_skip_to_data(std::ifstream& stream)
    {
        while (_skip_whitespaces(stream) or _skip_comments(stream)) {} // Skip whitespaces and comments until there are no more
    }

    bool ppm::_skip_whitespaces(std::ifstream& stream)
    {
        char c = char(stream.peek());
        char ref_c = c;
        while (c == ' ' or c == 9 or c == 10 or c == 13) // 9: TAB, 10: LF, 13: CR
        {
            stream.get(c);
            c = char(stream.peek());
        }
        if (c != ref_c) {return true;} else {return false;} // If 'c' and 'ref_c' are different then the stream has been iterated
    }

    bool ppm::_skip_comments(std::ifstream& stream)
    {
        char c = char(stream.peek());
        char ref_c = c;
        while (c == '#') // Peek the first character of the line
        {
            stream.get(c);
            while (c != '\n') // Iterate stream until EOL
            {
                stream.get(c);
            }
        }
        if (c != ref_c) {return true;} else {return false;}
    }

    // public:
    // methods
    image<uint8_t> ppm::read(const std::string& file_path)
    {
        std::ifstream input_file(file_path, std::ifstream::binary);
        std::string magic_number, max_color_value;
        std::size_t width, height;
        uint8_t * uint8_buffer;

        if (input_file.fail())
        {
            throw _exception_ppm_read("Failed to open: " + file_path);
        }

        // Retrieve header
        _skip_to_data(input_file), input_file >> magic_number;
        _skip_to_data(input_file), input_file >> width;
        _skip_to_data(input_file), input_file >> height;
        _skip_to_data(input_file), input_file >> max_color_value;


        if (magic_number != "P3" and magic_number != "P6")
        {
            throw _exception_ppm_read("Invalid magic number: " + magic_number);
        }
        else if ((height * width * 3) / width != height * 3)
        {
            throw _exception_ppm_read("Invalid 'width' and/or 'height', the product 'height * width * 3' exceeds size_t.");
        }
        else if (max_color_value != "255")
        {
            throw _exception_ppm_read("Invalid max_color_value', must be 255, got: " + max_color_value);
        }

        // Retrieve data
        uint8_buffer = new uint8_t[(height * width * 3)];
        _skip_to_data(input_file);
        if (magic_number == "P3")
        {
            for (std::size_t i = 0; i < height * width * 3; i++)
            {
                std::string pixel_str;
                input_file >> pixel_str;
                uint8_buffer[i] = static_cast<uint8_t> (std::stoi(pixel_str));
            }
        }
        else if (magic_number == "P6")
        {
            input_file.read(reinterpret_cast<char *>(uint8_buffer), std::streamsize(height * width * 3));
        }

        input_file.close();
        return {height, width, 3, uint8_buffer};
    }

    void ppm::write(image<uint8_t> image, const std::string& file_path)
    {
        std::ofstream output_file(file_path, std::ofstream::binary);
        const std::string magic_number = "P6";
        const std::string max_color_value = "255";
        const std::size_t width = image.width();
        const std::size_t height = image.height();
        const std::size_t channels = image.channels();

        // Access trough friendship
        uint8_t  * uint8_buffer = &image._data[0]; // vector to array

        if (output_file.fail())
        {
            throw _exception_ppm_write("Failed to open: " + file_path);
        }

        // Check the image compatibility with the .ppm format
        if (channels != 3)
        {
            throw _exception_ppm_write("Can on only write images with 3 channels, but a (" + std::to_string(channels) + ") channel image has been passed.");
        }

        // Write header
        output_file << magic_number << '\n';
        output_file << width << ' ' << height << '\n';
        output_file << max_color_value << '\n';

        // Write data
        output_file.write(reinterpret_cast<char *>(uint8_buffer), std::streamsize(height * width * 3));

        output_file.close();
    }
}

#endif