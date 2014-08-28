/**
 * @file threshold.cpp
 * @brief get binary image by different threshold value and type.
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

int threshold_value = 0;
int threshold_type = 0;
const int max_value = 255;
const int max_type = 5;
const int MAX_BINARY_VALUE = 255;

const char* window_name = "ThresholdDemo";
const char* trackbar_type = "Type: 0: Binary\n\
1: Binary Inverted 2: Truncate\n\
3: To Zero 4: To Zero Inverted\n\
5: Otsu";
const char* trackbar_value = "Value";

/// function declaration
void ThresholdDemo(int, void*);

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "===============================================================\n";
    cout << "This demo: threshold for the image, help to analyse the image.\n";
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
            ThresholdDemo);
    createTrackbar(trackbar_value,
            window_name,
            &threshold_value,
            max_value,
            ThresholdDemo);

    /// Call the function to initialize
    ThresholdDemo(0, NULL);

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
 * @brief ThresholdDemo for different type and value
 *
 * @param int
 */
void ThresholdDemo(int, void*)
{
    dst = src.clone();
    double otsu_value = 0;
    switch (threshold_type) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            threshold(src, dst, threshold_value, MAX_BINARY_VALUE,
                    threshold_type);
            break;
        case 5:
            otsu_value = threshold(src, dst, threshold_value,
                    MAX_BINARY_VALUE,
                    THRESH_OTSU);
            threshold(src, dst, otsu_value, MAX_BINARY_VALUE,
                    THRESH_BINARY);
            cout << "Otsu value = " << otsu_value << endl;
            break;
        default:
            cout << "unknown filter type.\n";
    }
    waitKey(20);
    imshow(window_name, dst);
}
