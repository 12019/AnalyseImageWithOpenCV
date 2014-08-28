/**
 * @file graylevelhistgramshow.cpp
 * @brief show the gray level histgram for both gray image and color image
 * @author chenxilinsidney
 * @version 1.0
 * @date 2014-08-24
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace cv;

/// Global variance
const char* output_file_name = "graylevelhistgram.txt";
Mat src;
Mat dst;

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "===============================================================\n";
    cout << "This demo: show the gray level histgram for both gray image and color image.\n";
    cout << "=========================== Usage =============================\n";
    cout << "Please input the source gray/color image name as first " 
        << "argument of the program.\n";
    cout << "Please input the output file name as second argument "
        << "of the program, or use default name if it is NULL.\n";
    cout << "Default output file name: " << output_file_name << endl;
    cout << "========================== Hot Key ============================\n";
    cout << "warning: when press the key,please make sure the image window "
        << "in foreground,or key would not response\n";
    cout << "Press \"Esc\" key to exit the program.\n";
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
    src = imread(argv[1]);
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

    /// Separate the image in 3 places ( B, G and R )
    vector<Mat> bgr_planes;
    split( src, bgr_planes );

    /// Establish the number of bins
    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
    float range[] = { 0, 256 } ;
    const float* histRange = { range };

    bool uniform = true; bool accumulate = false;

    Mat b_hist, g_hist, r_hist;

    /// Compute the histograms:
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

    /// Store the data in a file
    if(argv[2] != NULL)
        output_file_name = argv[2];
    ofstream myfile(output_file_name, fstream::out);
    if(!myfile.is_open()) {
        cout << "can open file!\n";
        return -1;
    }
    myfile << "hist data: " << endl;
    myfile << "hist size(h,w): " << b_hist.rows << ", " << b_hist.cols << endl;
    if (imread(argv[1], -1).channels() == 3) {
        for (int i = 0; i < b_hist.rows; i++) {
            float* p = b_hist.ptr<float>(i);
            for (int j = 0; j < b_hist.cols; j++) {
                myfile << "blue count in graylevel " << i << ": " << p[j] << endl;
            }
        }
        for (int i = 0; i < g_hist.rows; i++) {
            float* p = g_hist.ptr<float>(i);
            for (int j = 0; j < g_hist.cols; j++) {
                myfile << "green count in graylevel " << i << ": " << p[j] << endl;
            }
        }
        for (int i = 0; i < r_hist.rows; i++) {
            float* p = r_hist.ptr<float>(i);
            for (int j = 0; j < r_hist.cols; j++) {
                myfile << "red count in graylevel " << i << ": " << p[j] << endl;
            }
        }
    } else {
        for (int i = 0; i < r_hist.rows; i++) {
            float* p = r_hist.ptr<float>(i);
            for (int j = 0; j < r_hist.cols; j++) {
                myfile << "gray count in graylevel " << i << ": " << p[j] << endl;
            }
        }

    }
    myfile.close();

    // Draw the histograms for B, G and R
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    cout << "hist size = " << hist_h << ", " << hist_w << endl;

    /// Normalize the result to [ 0, histImage.rows ]
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    /// Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                Scalar( 0, 0, 255), 2, 8, 0  );
    }

    /// Display
    namedWindow("GrayLevelHistgram", WINDOW_AUTOSIZE );
    imshow("GrayLevelHistgram", histImage );

    waitKey(0);

    return 0;

}
