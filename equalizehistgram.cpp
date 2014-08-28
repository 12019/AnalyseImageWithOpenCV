/**
 * @file equalizehistgram.cpp
 * @brief equalize the histograme of a grayscale image
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
const char* output_image_name = "equalizehist.bmp";
Mat src;
Mat dst;

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "===============================================================\n";
    cout << "This demo: equalize the histograme of a grayscale image.\n";
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

    /// EqualizHistDemo
    equalizeHist(src, dst);

    /// Display
    namedWindow("GrayScaleImage", WINDOW_AUTOSIZE);
    imshow("GrayScaleImage", src);
    namedWindow("EqualizeHistImage", WINDOW_AUTOSIZE);
    imshow("EqualizeHistImage", dst);

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
