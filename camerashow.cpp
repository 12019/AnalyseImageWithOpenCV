/**
 * @file camerashow.cpp
 * @brief show usb camera image and capture both the gray image and color image.
 * @author chenxilinsidney
 * @version 1.0
 * @date 2014-08-24
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/// camera device index
int camera_device_index = 0;
/// camera image
Mat frame;
Mat capture_color_image;
Mat capture_gray_image;

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "This demo: show usb camera image and capture both the gray image and color image." << endl;
}
/**
 * @brief select camera device
 */
void HelpSelectCamera(void)
{
    cout << "---please choose the camera device on your computer.---\n";
    cout << "warning:if you only one camera device on your computer,\n";
    cout << "please input the number 0 and press enter\n";
    cout << "if you have more than one camera device, you may input \n";
    cout << "other number as index(should smaller than the number of\n";
    cout << "camera devices on your computer).\n";
    cout << endl;
    cout << "Input the index: ";
    cin >> camera_device_index;
    cout << "your choose is: " << camera_device_index << endl;
}

/**
 * @brief help for capture image and exit the program.
 */
void HelpCaptureImage(void)
{
    cout << "-warning: when press the key,please make sure the window named\n";
    cout << "-camera in foreground,or key would not response---------------\n";
    cout << "-----1.Press the \"S\" or \"s\" key to capture the camera. -\n";
    cout << "--------This will show both the captured gray and color images-\n";
    cout << "--------It will save the images named:color.bmp and gray.bmp  -\n";
    cout << "-----2.Press the \"Esc\" key to exit the program. -\n";
}
/**
 * @brief main function
 *
 * @return 0
 */
int main(void)
{
    HelpMain();

    HelpSelectCamera();

    // open camera
    VideoCapture cap(camera_device_index);
    if(!cap.isOpened()) {
        cout << "Can not find the default camera from you computer!\n";
        cin.get();
        return -1;
    }

    // wait for camera to get ready
    waitKey(2000);

    // read a frame to get the camera image state
    cap.read(frame);
    cout << "camera image height = " << frame.rows << endl;
    cout << "camera image width = " << frame.cols << endl;
    cout << "camera image channel = " << frame.channels() << endl;
    imshow("camera", frame);
    cout << "camera open success\n";
    waitKey(30);

    HelpCaptureImage();

    // start show the camera
    char key = -1;
    int num = 1;
    for(;;) {
        Mat frame;
        cap.read(frame);
        imshow("camera", frame);
        key = waitKey(30);
        // exit programe
        if(key == 27) {
            destroyAllWindows();
            break;
        }
        // capture image
        char name_gray[] = "gray_01.bmp";
        char name_color[] = "color_01.bmp";
        name_gray[5] = num / 10 + 0x30;
        name_color[6] = num / 10 + 0x30;
        name_gray[6] = num % 10 + 0x30;
        name_color[7] = num % 10 + 0x30;
        if(key == 'S' || key == 's') {
            capture_color_image = frame.clone();
            cvtColor(capture_color_image, capture_gray_image,
                    cv::COLOR_BGR2GRAY);
            imshow("color", capture_color_image);
            imshow("gray", capture_gray_image);
            imwrite(name_color, capture_color_image);
            imwrite(name_gray, capture_gray_image);
            num++;
        }
    }
    cap.release();
    return 0;
}
