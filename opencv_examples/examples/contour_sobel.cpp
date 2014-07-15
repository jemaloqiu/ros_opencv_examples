/************************************************************************/
/* ros-intellihome-vision                                               */
/*       --   A ROS package for robot vision using the Qt and OpenCV    */
/*                                                                      */
/* contour_sobel.cpp                                                    */
/*                                                                      */
/* Zhaopeng QIU <qiuzhaopeng@gmail.com>                                 */
/*                                                                      */
/*  Copyright (c) 2014, IntelliHome Team, IntelliHome co. ltd., France. */
/*  All rights reserved.                                                */
/*                                                                      */
/* Permission is hereby granted, free of charge, to any person          */
/* obtaining a copy of this software and associated documentation       */
/* files (the "Software"), to deal in the Software without restriction, */
/* including without limitation the rights to use, copy, modify, merge, */
/* publish, distribute, sublicense, and/or sell copies of the Software, */
/* and to permit persons to whom the Software is furnished to do so,    */
/* subject to the following conditions:                                 */
/*                                                                      */
/* The above copyright notice and this permission notice shall be       */
/* included in all copies or substantial portions of the Software.      */
/*                                                                      */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                */
/* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  */
/* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN   */
/* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    */
/* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     */
/* SOFTWARE.                                                            */
/*                                                                      */
/************************************************************************/

#include "ros/ros.h"
#include <ros/package.h> //for ros::package::getPath 
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <opencv/cv.h>
#include <map>
#include <string>

using namespace cv;
using namespace std;


int main( int argc, char** argv )
{

    std::string img_path = ros::package::getPath("intellihome_vision");
    std::cout << "image path is " << img_path << std::endl;
    std::string img1 = img_path +"/res/image.jpg";


    Mat src, src_gray;
    Mat grad;
    string window_name = "Sobel Demo - Simple Edge Detector";
    string original_window_name = "Original image";
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    int c;

    /// 装载图像
    src = imread( img1 );

    if( !src.data )
    { return -1; }

    /// 创建显示窗口
    namedWindow( original_window_name, CV_WINDOW_AUTOSIZE );
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    imshow(original_window_name, src);


    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    /// 转换为灰度图
    cvtColor( src, src_gray, CV_RGB2GRAY );


    /// 创建 grad_x 和 grad_y 矩阵
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    /// 求 X方向梯度
    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    /// 求Y方向梯度
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    /// 合并梯度(近似)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );


    imshow( window_name, grad );

    waitKey(0);

    return 0;
}


