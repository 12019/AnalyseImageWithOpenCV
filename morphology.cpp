/**
 * @file morphology.cpp
 * @brief morphology process for the input image.
 * @author chenxilinsidney
 * @version 1.0
 * @date 2014-08-24
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global variance
const char* output_image_name = "morphology.bmp";
Mat src;
Mat dst;

int morph_value_kernel_size = 0;
int morph_value_kernel_shape = 0;
int morph_value_iteration = 0;
int morph_type = 0;
const int max_morph_value_kernel_size = 30;
const int max_morph_value_kernel_shape = 2;
const int max_morph_value_iteration = 10;
const int max_morph_type = 6;

const char* window_name = "MorphologyDemo";
const char* trackbar_morph_value_kernel_size = "Kernel Size";
const char* trackbar_morph_value_kernel_shape = "Kernel Shape: 0:MORPH_RECT\n\
1:MORPH_ELLIPSE 2:MORPH_CROSS";
const char* trackbar_morph_value_iteration = "Iteration";
const char* trackbar_morph_type = "Type: 0: Dilate\n\
1: Erode 2: Open\n\
3: Close 4: Gradient\n\
5: Top Hat 6: Black Hat";

/// function declaration
void MorphologyDemo(int, void*);

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "===============================================================\n";
    cout << "This demo: morphology process for the input image.\n";
    cout << "=========================== Usage =============================\n";
    cout << "Please input the source gray/color image name as first " 
        << "argument of the program.\n";
    cout << "Please input the output image name as second argument "
        << "of the program, or use default name if it is NULL.\n";
    cout << "Default output image name: " << output_image_name << endl;
    cout << "========================== Hot Key ============================\n";
    cout << "warning: when press the key,please make sure the image window "
        << "in foreground,or key would not response\n";
    cout << "Press \"Esc\" key to exit the program.\n";
    cout << "Press \"S\" or \"s\" key to save the output image.\n";
    cout << "===============================================================\n";
}

/**
 * @brief main function
 *
 * @param int
 * @param argv
 *
 * @return 
 */
int main(int argc, char* argv[])
{
    /// Help Show
    HelpMain();

    /// Input argument detect
    if(argc < 2) {
        cout << "========================== Error ==============================\n";
        cout << "please input the image as an arugment of the program." << endl;
        return -1;
    }

    /// Load image
    src = imread(argv[1], IMREAD_GRAYSCALE);
    if(!src.data) {
        cout << "========================== Error ==============================\n";
        cout << "can't read the image from the argument of program"
            << " please check it again.\n";
        return -1;
    }

    /// Print image information
    cout << "image height = " << src.rows << endl;
    cout << "image width = " << src.cols << endl;
    cout << "image channel = " << src.channels() << endl;

    /// Create a window to display the results
    namedWindow(window_name, WINDOW_AUTOSIZE);

    /// Create Trackbar
    createTrackbar(trackbar_morph_value_kernel_size,
            window_name,
            &morph_value_kernel_size,
            max_morph_value_kernel_size,
            MorphologyDemo);
    createTrackbar(trackbar_morph_value_kernel_shape,
            window_name,
            &morph_value_kernel_shape,
            max_morph_value_kernel_shape,
            MorphologyDemo);
    createTrackbar(trackbar_morph_value_iteration,
            window_name,
            &morph_value_iteration,
            max_morph_value_iteration,
            MorphologyDemo);
    createTrackbar(trackbar_morph_type,
            window_name,
            &morph_type,
            max_morph_type,
            MorphologyDemo);

    /// Call the function to initialize
    MorphologyDemo(0, NULL);

    /// Loop
    char key;
    for (;;) {
        key = waitKey(20);
        if (key == 27) {
            break;
        }
        if (key == 's' || key == 'S') {
            if(argv[2] != NULL)
                output_image_name = argv[2];
            imwrite(output_image_name, dst);
            cout << "Having saved image to " << output_image_name << endl;
        }
    }
    return 0;
}

/**
 * @brief MorphologyDemo for different type and value
 *
 * @param int
 */
void MorphologyDemo(int, void*)
{
    dst = src.clone();
    int kernel_shape;
    switch (morph_value_kernel_shape) {
        case 0:
            kernel_shape = MORPH_RECT;
            break;
        case 1:
            kernel_shape = MORPH_ELLIPSE;
            break;
        case 2:
            kernel_shape = MORPH_CROSS;
            break;
    }
    Mat element = getStructuringElement(kernel_shape,
            Size(2 * morph_value_kernel_size + 1,
                2 * morph_value_kernel_size + 1),
            Point(morph_value_kernel_size, morph_value_kernel_size));
    switch (morph_type) {
        case 0:
            dilate(src, dst, element, Point(-1, -1), morph_value_iteration);
            break;
        case 1:
            erode(src, dst, element, Point(-1, -1), morph_value_iteration);
            break;
        case 2:
            morphologyEx(src, dst, MORPH_OPEN, element,
                    Point(-1, -1), morph_value_iteration); 
            break;
        case 3:
            morphologyEx(src, dst, MORPH_CLOSE, element,
                    Point(-1, -1), morph_value_iteration); 
            break;
        case 4:
            morphologyEx(src, dst, MORPH_GRADIENT, element,
                    Point(-1, -1), morph_value_iteration); 
            break;
        case 5:
            morphologyEx(src, dst, MORPH_TOPHAT, element,
                    Point(-1, -1), morph_value_iteration); 
            break;
        case 6:
            morphologyEx(src, dst, MORPH_BLACKHAT, element,
                    Point(-1, -1), morph_value_iteration); 
            break;
    }
    waitKey(20);
    imshow(window_name, dst);
}
