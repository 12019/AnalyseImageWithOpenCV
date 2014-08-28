/**
 * @file edgedetect.cpp
 * @brief detect the edge information from the image
 * @author chenxilinsidney
 * @version 1.0
 * @date 2014-08-27
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global variance
const char* output_image_name = "edgedetect.bmp";
Mat src;
Mat dst;

int edge_value_scale = 0;
int edge_value_delta = 0;
int edge_value_size = 0;
int edge_type = 0;
const int max_edge_value_scale = 255;
const int max_edge_value_delta = 255;
const int max_edge_value_size = 7; 
const int max_edge_type = 3;

const char* window_name = "EdgeDetectDemo";
const char* trackbar_edge_value_scale = "Scale Value/Canny threshold1";
const char* trackbar_edge_value_delta = "Delta Value/Canny threshold2";
const char* trackbar_edge_value_size = "Kernel Size";
const char* trackbar_edge_type = "Type: 0: Sobel\n\
1: Scharr\n\
2: Laplacian\n\
3: Canny";

/// function declaration
void EdgeDetectDemo(int, void*);

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "===============================================================\n";
    cout << "This demo: detect the edge information from the image.\n";
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
    createTrackbar(trackbar_edge_value_scale,
            window_name,
            &edge_value_scale,
            max_edge_value_scale,
            EdgeDetectDemo);
    createTrackbar(trackbar_edge_value_delta,
            window_name,
            &edge_value_delta,
            max_edge_value_delta,
            EdgeDetectDemo);
    createTrackbar(trackbar_edge_type,
            window_name,
            &edge_type,
            max_edge_type,
            EdgeDetectDemo);
    createTrackbar(trackbar_edge_value_size,
            window_name,
            &edge_value_size,
            max_edge_value_size,
            EdgeDetectDemo);

    /// Call the function to initialize
    EdgeDetectDemo(0, NULL);

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
 * @brief EdgeDetectDemo for different type and value
 *
 * @param int
 */
void EdgeDetectDemo(int, void*)
{
    dst = src.clone();
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    double value_scale = 0.0;
    if (edge_value_scale == 0) {
        value_scale = 1;
    } else {
        value_scale = (double)edge_value_scale / max_edge_value_scale;
    }
    int ksize = 0;
    if (edge_value_size <= 2) {
        ksize = 3;
    } else {
        ksize = (edge_value_size % 2 == 0) ?
            edge_value_size + 1 : edge_value_size;
    }
    switch (edge_type) {
        case 0:
            Sobel(src, grad_x, CV_16S, 1, 0, 3,
                    value_scale,
                    edge_value_delta);
            Sobel(src, grad_y, CV_16S, 0, 1, 3,
                    value_scale,
                    edge_value_delta);
            convertScaleAbs(grad_x, abs_grad_x);
            convertScaleAbs(grad_y, abs_grad_y);
            addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
            break;
        case 1:
            Scharr(src, grad_x, CV_16S, 1, 0,
                    value_scale,
                    edge_value_delta);
            Scharr(src, grad_y, CV_16S, 0, 1,
                    value_scale,
                    edge_value_delta);
            convertScaleAbs(grad_x, abs_grad_x);
            convertScaleAbs(grad_y, abs_grad_y);
            addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
            break;
        case 2:
            Laplacian(src , grad_x, CV_16S, ksize,
                    value_scale,
                    edge_value_delta);
            convertScaleAbs(grad_x, dst);
            break;
        case 3:
            if (edge_value_scale < edge_value_delta)
                Canny(src, dst, edge_value_scale, edge_value_delta, ksize);
            break;
    }
    waitKey(20);
    imshow(window_name, dst);
}
