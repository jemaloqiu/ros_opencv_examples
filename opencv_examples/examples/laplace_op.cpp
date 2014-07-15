/************************************************************************/
/* ros-opencv-examples                                                  */
/*       --   A ROS package containing OpenCV examples                  */
/*                                                                      */
/*                                                                      */
/* laplace_op.cpp                                                       */
/*                                                                      */
/* Zhaopeng QIU <qiuzhaopeng@gmail.com>                                 */
/*                                                                      */
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

    std::string img_path = ros::package::getPath("opencv_examples");
    std::cout << "image path is " << img_path << std::endl;
    std::string img1 = img_path +"/res/image.jpg";

    Mat src, src_gray, dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    string window_name = "Laplace Demo";
    string original_window_name = "Original image";

    int c;

 
    src = imread( img1 );

    if( !src.data )
    { return -1; }

    namedWindow( original_window_name, CV_WINDOW_AUTOSIZE );
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    imshow(original_window_name, src);

    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    cvtColor( src, src_gray, CV_RGB2GRAY );

    Mat abs_dst;

    Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( dst, abs_dst );

    imshow( window_name, abs_dst );

    waitKey(0);
    return 0;
}


