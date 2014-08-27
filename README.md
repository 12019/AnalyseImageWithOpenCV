AnalyseImageWithOpenCV
======================

OpenCV Demos that help to analyse the image with various of digital image processing technique using OpenCV.

It is provided for analysing the digital image by using [OpenCV](http://opencv.org/) computer vision library with the C++ program language.
<hr>
##Description
**Simple but Powerful GUI to analyse the images and algorithms more fast.**

It is convenient of the digital image processing algorithm research to get analyse and set the argument or get wanted information from the output with simple but powerful graphic user interface([GUI](http://docs.opencv.org/doc/tutorials/highgui/table_of_content_highgui/table_of_content_highgui.html#table-of-content-highgui)), which is also provided by the OpenCV
library.

It also attempts to provide convenient wrappers for common OpenCV functions that are friendly to beginners.It can help beginners to use the OpenCV Library with C++ programm language.
<hr>
##Install

###Install OpenCV library to computer:
If do not have installed it.please download and install from:http://opencv.org/

###Clone the repository:
* $ git clone git://github.com/chenxilinsidney/AnalyseImageWithOpenCV.git
* another choice:download the zip package from the right bottom of the [website](https://github.com/chenxilinsidney/AnalyseImageWithOpenCV)

###Run the shell script to build all the demos:
* $ cd AnalyseImageWithOpenCV
* $ chmod +x build_demo.sh
* $ ./build_demo.sh

<hr>
##Example

Using the camerashow demo to show the camera and capture both the gray and color images.
* $ ./camerashow

Using the equalizehistgram demo to equalizehist the input image name "lena.bmp" and save as "output.bmp" while showing the source image and result image on the window.
* $ ./equalizehistgram lena.bmp output.bmp

##ScreenShot
* **Using the edgedetect demo to analyse what kind of edge detect methods is suitable for the input images.**
![alt tag](https://github.com/chenxilinsidney/AnalyseImageWithOpenCV/blob/master/EdgeDetectDemoScreenshot.png)
* **Using the filter demo to analyse what kind of filter methods and arguments' value is suitable for the input images.**
![alt tag](https://github.com/chenxilinsidney/AnalyseImageWithOpenCV/blob/master/FilterDemoScreenshot.png)
* **Simple print the gray value of the point clicked by left mouse to the stdout.**
![alt tag](https://github.com/chenxilinsidney/AnalyseImageWithOpenCV/blob/master/GrayValueShowDemoScreenshot.png)
* **Using the threshold demo to anlayse kind of threshold methods and get the best threshold value while running the demo.**
![alt tag](https://github.com/chenxilinsidney/AnalyseImageWithOpenCV/blob/master/ThresholdDemoScreenshot.png)

<hr>
##Licensing
[GNU GPL v2.0](http://choosealicense.com/licenses/gpl-v2)

<hr>
##Contributors
[Sidney Chen](https://github.com/chenxilinsidney)
contact way: E-mail:chenxilinsidney@gmail.com
