/**
 * @file conversion.cpp
 * @brief conversion betweent txt and image file.
 * @author chenxilinsidney
 * @version 1.0
 * @date 2014-08-24
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

const char* output_image_name_txt = "conversion.txt";
const char* output_image_name_bmp = "conversion.bmp";
const int MAX_IMAGE_SIZE = 307200;

/**
 * @brief save mat to txt
 *
 * @param[in]      src          src image
 * @param[in]      file_name    file name
 */
void cv_Mat2Txt(const CvMat* src, const char* file_name)
{
    FILE* txt = fopen(file_name, "w+");
    fprintf(txt, "height = %d\n", src->rows);
    fprintf(txt, "width = %d\n", src->cols);
    fprintf(txt, "type = %d\n", src->type);
    fprintf(txt, "data:\n");
    int i, j;
    for (i = 0; i < src->rows; i++) {
        const uchar* p_src = src->data.ptr + i * src->cols;
        for (j = 0; j < src->cols; j++) {
            fprintf(txt, "%d ", *(p_src + j));
        }
        fprintf(txt, "\n");
    }
}

/**
 * @brief read mat from txt
 *
 * @param[in, out] src          src image
 * @param[in]      file_name    file name
 */
void cv_Txt2Mat(CvMat* src, const char* file_name)
{
    FILE* txt = fopen(file_name, "r");
    fscanf(txt, "height = %d\n", &(src->rows));
    fscanf(txt, "width = %d\n", &(src->cols));
    fscanf(txt, "type = %d\n", &(src->type));
    fscanf(txt, "data:\n");
    int i, j;
    for (i = 0; i < src->rows; i++) {
        uchar* p_src = src->data.ptr + i * src->cols;
        int temp = 0;
        for (j = 0; j < src->cols; j++) {
            fscanf(txt, "%d ", &temp);
            *(p_src + j) = (uchar)temp;
        }
        fscanf(txt, "\n");
    }
}

/**
 * @brief main help
 */
void HelpMain(void)
{
    cout << "===============================================================\n";
    cout << "This demo: conversion betweent txt and image file.\n";
    cout << "=========================== Usage =============================\n";
    cout << "Please input the source gray/color image name as first " 
        << "argument of the program.\n";
    cout << "Please input the output txt name as second argument "
        << "of the program.\n";
    cout << "========================== Hot Key ============================\n";
    cout << "warning: when press the key,please make sure the image window "
        << "in foreground,or key would not response\n";
    cout << "Press \"Esc\" key to exit the program.\n";
    cout << "Press \"W\" or \"w\" key to write image to txt.\n";
    cout << "Press \"R\" or \"r\" key to read image from txt.\n";
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
    if(argc <= 2) {
        cout << "========================== Error ==============================\n";
        cout << "please input the image and txt as an arugment of the program." << endl;
        return -1;
    }

    /// Loop
    imshow("temp", Mat(3, 3, CV_8UC1));
    char key;
    for (;;) {
        key = waitKey(0);
        if (key == 27) {
            break;
        }
        if (key == 'w' || key == 'W') {
            /// Load image from bmp file
            Mat src = imread(argv[1], IMREAD_GRAYSCALE);
            if(!src.data) {
                cout << "========================== Error ==============================\n";
                cout << "can't read the image from the argument of program"
                    << " please check it again.\n";
                return -1;
            }
            imshow("src", src);
            /// Print image information
            cout << "image height = " << src.rows << endl;
            cout << "image width = " << src.cols << endl;
            cout << "image channel = " << src.channels() << endl;
            /// save to txt file
            CvMat src_mat = src;
            if(argv[2] != NULL)
                output_image_name_txt = argv[2];
            cv_Mat2Txt(&src_mat, output_image_name_txt);
            cout << "Having saved txt to " << output_image_name_txt << endl;
        }
        if (key == 'r' || key == 'R') {
            /// Load image from txt file
            FILE* txt = fopen(argv[2], "r");
            if(!txt) {
                cout << "========================== Error ==============================\n";
                cout << "can't read the txt from the argument of program"
                    << " please check it again.\n";
                return -1;
            }
            /// save to bmp file
            uchar src_data[MAX_IMAGE_SIZE] = {0};
            CvMat src_mat = cvMat(0, 0, 0, src_data);
            cv_Txt2Mat(&src_mat, argv[2]);
            /// Print image information
            cout << "image height = " << src_mat.rows << endl;
            cout << "image width = " << src_mat.cols << endl;
            Mat src = Mat(src_mat.rows, src_mat.cols, CV_8UC1);
            for (int i = 0; i < src.rows; i++) {
                uchar* p_temp = src.ptr<uchar>(i);
                for (int j = 0; j < src.cols; j++) {
                    *(p_temp + j) = *(src_data + i * src.cols + j);
                }
            }
            if(argv[1] != NULL)
                output_image_name_bmp = argv[1];
            imshow("src", src);
            imwrite(output_image_name_bmp, src);
            cout << "Having saved image to " << output_image_name_bmp << endl;
        }
    }
    return 0;
}
