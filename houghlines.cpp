/**
 * @file houghlines.cpp
 * @brief detect straight lines.
 * @author chenxilinsidney
 * @version 1.0
 * @date 2014-08-26
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// Global variance
const char* output_image_name = "houghlines.bmp";
Mat src;
Mat dst;

int hough_distance_resolution = 0;
int hough_angle_resolution = 0;
int hough_accumulator_threshold = 0;
const int max_hough_distance_resolution = 640;
const int max_hough_angle_resolution = 90;
const int max_hough_accumulator_threshold = 800;

const char* window_name = "HoughLinesDemo";
const char* trackbar_hough_distance_resolution = "Distance Resolution";
const char* trackbar_hough_angle_resolution = "Angle Resolution";
const char* trackbar_hough_accumulator_threshold = "Accumulator Threshold";

/// function declaration
void HoughLinesDemo(int, void*);

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
    createTrackbar(trackbar_hough_distance_resolution,
            window_name,
            &hough_distance_resolution,
            max_hough_distance_resolution,
            HoughLinesDemo);
    createTrackbar(trackbar_hough_angle_resolution,
            window_name,
            &hough_angle_resolution,
            max_hough_angle_resolution,
            HoughLinesDemo);
    createTrackbar(trackbar_hough_accumulator_threshold,
            window_name,
            &hough_accumulator_threshold,
            max_hough_accumulator_threshold,
            HoughLinesDemo);

    /// Call the function to initialize
    HoughLinesDemo(0, NULL);

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
 * @brief HoughLinesDemo for different type and value
 *
 * @param int
 */
void HoughLinesDemo(int, void*)
{
    dst = src.clone();
    double angle_resolution = 0.0;
    if (hough_angle_resolution == 0)
        angle_resolution = (double)CV_PI / 180;
    else
        angle_resolution = (double)hough_angle_resolution * CV_PI / 180;
    int distance_resolution = 0;
    if (hough_distance_resolution == 0)
        distance_resolution = 1;
    else
        distance_resolution = hough_distance_resolution;
    int accumulator_threshold = 0;
    if (hough_accumulator_threshold == 0)
        accumulator_threshold = 1;
    else
        accumulator_threshold = hough_accumulator_threshold;
    vector<Vec2f> lines;
    HoughLines(dst, lines,
            distance_resolution,
            angle_resolution,
            accumulator_threshold,
            0, 0);
    for (int i = 0; i < lines.size(); i++) {
        float rho = lines[i][0];
        float theta = lines[i][1];
        cout << "line i: " << i + 1 <<
            " dist = " << rho << ", angle = " << theta * 180 / CV_PI << endl;
        Point pt1, pt2;
        double a = cos(theta);
        double b = sin(theta);
        double x0 = a * rho;
        double y0 = b * rho;
        pt1.x = x0 + 1000 * (-b);
        pt1.y = y0 + 1000 * (a);
        pt2.x = x0 - 1000 * (-b);
        pt2.y = y0 - 1000 * (a);
        line(dst, pt1, pt2, Scalar(255), 3, CV_AA);
    }
    waitKey(20);
    imshow(window_name, dst);
}
