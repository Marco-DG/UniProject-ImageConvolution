#ifndef DGLIB_KERNEL_TYPE_H
#define DGLIB_KERNEL_TYPE_H

#include <utility> // move
#include <vector>

namespace dglib
{
    typedef std::vector<std::vector<float> > matrix_t;

    class kernel_t
    {
        private:
            matrix_t _matrix;
            float _factor;

        public:
            kernel_t(matrix_t matrix, float factor) : _matrix(std::move(matrix)), _factor(factor) {}

            matrix_t matrix()       { return _matrix; }
            float factor()          { return _factor; }
            std::size_t width()     { return _matrix.size(); }
            std::size_t height()    { return _matrix[0].size(); }
    };
}

#endif