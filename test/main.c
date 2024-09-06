#include <stdio.h>

#include <adiff/filter/filter.h>

int main() {

    ADIFF_IMAGE image = adiff_load_png("albert-einstein.png");

    adiff_grey_filter(&image);
    adiff_anisotropic_diffusion_filter(&image, 50, 0.20, 10);

    adiff_save_png(&image, "output.png");
    adiff_free_image(&image);

    return 0;
}