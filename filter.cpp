/**
 * @file filter.cpp
 * @brief simple filter for the image, help to anlyse the image.
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
const char* output_image_name = "filter.bmp";
Mat src;
Mat dst;

int filter_value;
int filter_value2;
int filter_type;
int max_value = 30;
int max_value2 = 100;
int max_type = 3;

const char* window_name = "Filter Demo";
const char* trackbar_type = "Type:\n 0:Normal Blur\n 1:Median Blur\n 2:Gaussian Blur\n 3:Bilateral Blur";
const char* trackbar_value = "Value";
const char* trackbar_value2 = "Value: \nFor Gaussian and Bilateral";

/// function declaration
void FilterDemo(int, void*);

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "===============================================================\n";
    cout << "This demo: filter the image, help to anlyse the image.\n";
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
            &filter_type,
            max_type,
            FilterDemo);
    createTrackbar(trackbar_value,
            window_name,
            &filter_value,
            max_value,
            FilterDemo);
    createTrackbar(trackbar_value2,
            window_name,
            &filter_value2,
            max_value2,
            FilterDemo);

    /// Call the function to initialize
    FilterDemo(0, NULL);

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
 * @brief filter demo for different type and value
 *
 * @param int
 */
void FilterDemo(int, void*)
{
    dst = src.clone();
    switch (filter_type) {
        case 0:
            if(filter_value == 0)
                filter_value = 1;
            blur(src, dst, Size(filter_value, filter_value));
            break;
        case 1:
            if(filter_value % 2 == 0)
                filter_value += 1;
            medianBlur(src, dst, filter_value);
            break;
        case 2:
            if(filter_value % 2 == 0)
                filter_value += 1;
            GaussianBlur(src, dst, Size(filter_value, filter_value),
                    filter_value2);
            break;
        case 3:
            if(filter_value == 0)
                filter_value = 1;
            bilateralFilter(src, dst, filter_value,
                    filter_value2, filter_value2);
            break;
        default:
            cout << "unknown filter type.\n";
    }
    waitKey(20);
    imshow(window_name, dst);
}

