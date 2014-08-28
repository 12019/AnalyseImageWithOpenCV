/**
 * @file grayvalueshow.cpp
 * @brief get the gray value and point coordinate of the clicked image point.
 * @author chenxilinsidny
 * @version 
 * @date 2014-08-27
 */
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace cv;

/// Global variance
const char* window_name = "GrayImage";
Mat src;

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "===============================================================\n";
    cout << "This demo: get the gray value and point coordinate of the clicked image point.\n";
    cout << "=========================== Usage =============================\n";
    cout << "Please input the source gray/color image name as first " 
        << "argument of the program.\n";
    cout << "========================== Hot Key ============================\n";
    cout << "warning: when press the key,please make sure the image window "
        << "in foreground,or key would not response\n";
    cout << "Press \"Esc\" key to exit the program.\n";
    cout << "===============================================================\n";
}

/**
 * @brief mouse callback
 *
 * @param event mouse event type
 * @param x  point x coordinate value
 * @param y  point y coordinate value
 * @param int
 */
static void onMouse(int event, int x, int y, int, void*)
{
    if(event != EVENT_LBUTTONDOWN) {
        return;
    }
    Point seed = Point(x, y);
    cout << "Clicked point: (" << x << ", " << y << ") gray value"
        << ": " << (int)(src.ptr<uchar>(y))[x] << endl;
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
    imshow(window_name, src);

    /// setMouseCallback
    setMouseCallback(window_name, onMouse, 0);
    
    /// Loop
    char key;
    for (;;) {
        key = waitKey(20);
        if (key == 27) {
            break;
        }
    }
    return 0;
}
