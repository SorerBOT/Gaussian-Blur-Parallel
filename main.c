#include "guassonFilter.h"
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define IS_SEQUENTIAL 0

int main()
{
    const char *inputFilename = "assets/windows.png";
    const char *outputFilename = "output_image.png";
    int blurRadius = 5;

    double time_start = omp_get_wtime();
    Image *inputImage = loadImage(inputFilename);
    if (inputImage == NULL)
    {
        printf("Failed to load image\n");
        return -1;
    }

#if IS_SEQUENTIAL
    Image *outputImage = createBlurredImage_sequential(blurRadius, inputImage);
#else
    Image *outputImage = createBlurredImage(blurRadius, inputImage);
#endif


    saveImage(outputFilename, outputImage);

    double time_end = omp_get_wtime();
    printf("Time taken %lf\n", time_end - time_start);

    free(inputImage->pixels);
    free(inputImage);
    free(outputImage->pixels);
    free(outputImage);

    return 0;
}
