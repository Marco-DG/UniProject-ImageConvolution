#include "dglib/ppm.h"
#include "dglib/kernel.h"

int main() {

    using namespace dglib;

    auto im = ppm::read("./lena.ppm");

    ppm::write(im.convolve(kernel::Identity             ), "./output_images/Identity.ppm"              );
    ppm::write(im.convolve(kernel::UnsharpMasking_5x5   ), "./output_images/UnsharpMasking_5x5.ppm"    );
    ppm::write(im.convolve(kernel::WeakEdgeDetection    ), "./output_images/WeakEdgeDetection.ppm"     );
    ppm::write(im.convolve(kernel::MediumEdgeDetection  ), "./output_images/MediumEdgeDetection.ppm"   );
    ppm::write(im.convolve(kernel::StrongEdgeDetection  ), "./output_images/StrongEdgeDetection.ppm"   );
    ppm::write(im.convolve(kernel::Sharpen              ), "./output_images/Sharpen.ppm"               );
    ppm::write(im.convolve(kernel::BoxBlur              ), "./output_images/BoxBlur.ppm"               );
    ppm::write(im.convolve(kernel::GaussianBlur_3x3     ), "./output_images/GaussianBlur_3x3.ppm"      );
    ppm::write(im.convolve(kernel::GaussianBlur_5x5     ), "./output_images/GaussianBlur_5x5.ppm"      );
}