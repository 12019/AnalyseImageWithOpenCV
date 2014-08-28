/**
 * @file floodfill.cpp
 * @brief fills connected component and get sequense images.
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
const char* output_image_name = "floodfill_.bmp";
Mat src;
Mat dst;

const char* window_name = "FloodFillDemo";
const unsigned char fillVal = 0;
const unsigned char bgVal = 255;
const int rectangle_height_max = 300;
const int rectangle_height_min = 50;
const int rectangle_width_max = 300;
const int rectangle_width_min = 50;

/// function declaration
void FloodFillDemo(void);

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "===============================================================\n";
    cout << "This demo: brief fills connected component and get sequense images.\n";
    cout << "Can only get a number of maximum of 255 compnents.\n";
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

    /// Set output name first
    if(argv[2] != NULL)
        output_image_name = argv[2];
    /// Print image information
    cout << "image height = " << src.rows << endl;
    cout << "image width = " << src.cols << endl;
    cout << "image channel = " << src.channels() << endl;

    /// Create a window to display the results
    namedWindow(window_name, WINDOW_AUTOSIZE);

    /// floodFill
    FloodFillDemo();
    /// Loop
    char key;
    for (;;) {
        key = waitKey(20);
        if (key == 27) {
            break;
        }
        if (key == 's' || key == 'S') {
            imwrite(output_image_name, dst);
            cout << "Having saved image to " << output_image_name << endl;
        }
    }
    return 0;
}

/**
 * @brief FloodFillDemo
 *
 * @param int
 */
void FloodFillDemo(void)
{
    dst = src.clone();
    Mat temp = Mat(dst.rows + 2, dst.cols + 2, dst.depth());
    unsigned char temp_count = '0';
    Point seedPoint = Point(0,0);
    Rect domain = Rect(0, 0, 0, 0);
    unsigned char newVal = 1;
    for (int i = 0; i < dst.rows; i++) {
        uchar* p = dst.ptr<uchar>(i);
        for (int j = 0; j < dst.cols; j++) {
            if (p[j] == fillVal) {
                seedPoint = Point(j, i);
                Mat temp = Mat(dst.rows + 2, dst.cols + 2, dst.depth(),
                        Scalar(0));
                floodFill(dst, temp, seedPoint, Scalar::all(newVal),
                        &domain, Scalar(0), Scalar(0), 4);
                if ((rectangle_height_max < domain.height)
                        || (rectangle_height_min > domain.height)
                        || (rectangle_width_max < domain.width)
                        || (rectangle_width_min > domain.width)) {
                    continue;
                }
                cout << "find component value = " << int(newVal) << endl;
                cout << "  component minimum bounding rectangle:\n";
                cout << "  LeftTop position x : " << domain.x << endl;
                cout << "  LeftTop position y : " << domain.y << endl;
                cout << "  Rectangle height   : " << domain.height << endl;
                cout << "  Rectangle width    : " << domain.width << endl;
                newVal++;
                temp_count++;
                threshold(temp, temp, 0, 255, THRESH_BINARY);
                String temp_name = String(output_image_name);
                temp_name.at(temp_name.length() - 5) = temp_count;
                imwrite(temp_name, temp);
                imshow("temp", temp);
                waitKey();
            }
        }
    }
    cout << "total component count: " << int(--newVal);
    waitKey(20);
    imshow(window_name, dst);
}
