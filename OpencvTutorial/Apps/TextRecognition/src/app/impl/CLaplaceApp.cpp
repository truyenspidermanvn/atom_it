
#include "CLaplaceApp.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int CLaplaceApp::run(int argc, char* argv[])
{
    // Declare the variables we are going to use
    Mat src, src_gray, dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    const char* window_name = "Laplace Demo";
    const char* imageName = argc >=2 ? argv[1] : "../data/lena.jpg";
    src = imread( imageName, IMREAD_COLOR ); // Load an image
    // Check if image is loaded fine
    if(src.empty()) {
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default ../data/lena.jpg] \n");
        return -1;
    }
    // Reduce noise by blurring with a Gaussian filter ( kernel size = 3 )
    GaussianBlur( src, src, Size(15, 15), 0, 0, BORDER_DEFAULT );
    cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to grayscale
    Mat abs_dst;
    Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    // converting back to CV_8U
    convertScaleAbs( dst, abs_dst );
    Mat aa = ~abs_dst;
    imshow( window_name, aa );
    waitKey(0);    

    return 0;
}