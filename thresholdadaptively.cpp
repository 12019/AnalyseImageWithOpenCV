/**
 * @file threshold.cpp
 * @brief get binary image by adaptive threshold.
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
const char* output_image_name = "threshold.bmp";
Mat src;
Mat dst;

int threshold_size = 0;
int threshold_type = 0;
int threshold_shift = 0;
const int max_size = 33;
const int max_type = 1;
const int max_shift = 255;
const int MAX_BINARY_VALUE = 255;

const char* window_name = "AdaptiveThresholdDemo";
const char* trackbar_type = "0: MEAN\n1: GAUSSIAN";
const char* trackbar_size = "Size";
const char* trackbar_shift = "Shift";

/// function declaration
void AdaptiveThresholdDemo(int, void*);

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "===============================================================\n";
    cout << "This demo: adaptive threshold for the image, help to analyse the image.\n";
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
    createTrackbar(trackbar_type,
            window_name,
            &threshold_type,
            max_type,
            AdaptiveThresholdDemo);
    createTrackbar(trackbar_size,
            window_name,
            &threshold_size,
            max_size,
            AdaptiveThresholdDemo);
    createTrackbar(trackbar_shift,
            window_name,
            &threshold_shift,
            max_shift,
            AdaptiveThresholdDemo);

    /// Call the function to initialize
    AdaptiveThresholdDemo(0, NULL);

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
 * @brief AdaptiveThresholdDemo for different type and size
 *
 * @param int
 */
void AdaptiveThresholdDemo(int, void*)
{
    dst = src.clone();
    double otsu_value = 0;
    int block_size = threshold_size;
    if (block_size % 2 == 0)
        block_size += 1;
    if (block_size == 1)
        block_size += 2;
    switch (threshold_type) {
        case 0:
            adaptiveThreshold(src, dst, MAX_BINARY_VALUE,
                    ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,
                    block_size, threshold_shift); 
            break;
        case 1:
            adaptiveThreshold(src, dst, MAX_BINARY_VALUE,
                    ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,
                    block_size, threshold_shift); 
            break;
        default:
            cout << "unknown type.\n";
    }
    waitKey(20);
    imshow(window_name, dst);
}
