#ifndef DGLIB_KERNEL_H
#define DGLIB_KERNEL_H

#include "kernel_type.h" // kernel_t

namespace dglib::kernel
{
    kernel_t Custom ({
        { 1, 1, 1 },
        { 1, 1, 1 },
        { 1, 1, 1}
    }, 9);

    kernel_t Identity ({
        { 0, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 0 }
    }, 1);

    kernel_t StrongEdgeDetection ({
        { 1, 0,-1 },
        { 0, 0, 0 },
        {-1, 0, 1 }
    }, 1);

    kernel_t MediumEdgeDetection ({
        { 0,-1, 0 },
        {-1, 4,-1 },
        { 0,-1, 0 }
    }, 1);

    kernel_t WeakEdgeDetection ({
        {-1,-1,-1 },
        {-1, 8,-1 },
        {-1,-1,-1 }
    }, 1);

    kernel_t Sharpen ({
        { 0,-1, 0 },
        {-1, 5,-1 },
        { 0,-1, 0 }
    }, 1);

    kernel_t BoxBlur ({
        { 1, 1, 1 },
        { 1, 1, 1 },
        { 1, 1, 1 }
    }, 9);

    kernel_t GaussianBlur_3x3 ({
        { 1, 2, 1 },
        { 2, 4, 2 },
        { 1, 2, 1 }
    }, 16);

    kernel_t GaussianBlur_5x5 ({
        { 1,   4,   6,   4,   1 },
        { 4,  16,  24,   1,   4 },
        { 6,  24,  36,  24,   6 },
        { 4,  16,  24,  16,   4 },
        { 1,   4,   6,   4,   1 }
    }, 256);

    kernel_t UnsharpMasking_5x5 ({
        {-1,  -4,  -6,  -4,  -1 },
        {-4, -16, -24, -16,  -4 },
        {-6, -24, 476, -24,  -6 },
        {-4, -16, -24, -16,  -4 },
        {-1,  -4,  -6,  -4,  -1 }
    }, 256);
}

#endif