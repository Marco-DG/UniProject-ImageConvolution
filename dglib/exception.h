#ifndef DGLIB_EXCEPTION_H
#define DGLIB_EXCEPTION_H

#include <exception> // exception

namespace dglib
{
    struct exception : std::exception
    {
        protected:
            std::string _error_message;
        public:
            explicit exception(std::string & error_message) : _error_message(error_message) {}
            const char* what() const noexcept override { return _error_message.c_str(); }
    };
}

#endif