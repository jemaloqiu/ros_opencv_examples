/************************************************************************/
/* ros-opencv-examples                                                  */
/*       --   A ROS package containing OpenCV examples                  */
/*                                                                      */
/* learn_mat.cpp                                                        */
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
#include <vector>
#include <string>

using namespace cv;

int main(int argc, char *argv[])
{
    Mat A, C;                                   // creates just the header parts

    std::string img_path = ros::package::getPath("opencv_examples");
    img_path += "/res/image.jpg";

    // here we'll know the method used (allocate matrix), allocate memery for matrix
    A = imread(img_path, CV_LOAD_IMAGE_COLOR);        

    // only copy header and matrix pointer, not matrix itself
    Mat B(A);                                   // Use the copy constructor
    C = A;                                      // Assignment operator

    // if we still want to copy both data matrix, we can use clone() and copyTo()
    Mat F = A.clone();
    Mat G;
    A.copyTo(G);


/////////////////////////////////////////////////
// create a mat, initialize it  
///////////////////////////////////////////////////
    //******** method 1 ******************
    Mat M(2,2, CV_8UC3, Scalar(0,0,255)); // using its constructor
        // format is: CV_[number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
    std::cout << "M = " << std::endl << " " << M << std::endl << std::endl;   

    //******** method 2 ******************
    int sz[3] = {2,2,2};    // using size vector for creating a matrix whose dimension is more than 2
    Mat L(3, sz, CV_8UC(1), Scalar::all(0));


    //******** method 3 ******************
    IplImage* img = cvLoadImage(img_path.c_str(), 1);
    Mat mtx(img);       // convert IplImage* -> Mat


    //******** method 4 ******************
    M.create(4, 4, CV_8UC(2));  // not initializing the matrix, just re-allocate its memory when its dimension changes
    std::cout << "M = "<< std::endl << " "  << M << std::endl << std::endl;



/////////////////////////////////////////////////
// printing a Mat using several formats
///////////////////////////////////////////////////

    Mat R = Mat(3, 2, CV_8UC3);  // using its constructor
        // format is: CV_[number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
    randu(R, Scalar::all(0), Scalar::all(255));  // random using lower and upper bounds
    std::cout << "R (python)  = " << std::endl << format(R,"python") << std::endl << std::endl;
    std::cout << "R (csv)     = " << std::endl << format(R,"csv"   ) << std::endl << std::endl;
    std::cout << "R (numpy)   = " << std::endl << format(R,"numpy" ) << std::endl << std::endl;
    std::cout << "R (c)       = " << std::endl << format(R,"C"     ) << std::endl << std::endl;



/////////////////////////////////////////////////
// printing a 2d/3d point, a vector using Mat
///////////////////////////////////////////////////

    Point2f P(5, 1);
    std::cout << "Point (2D) = " << P << std::endl << std::endl;

    Point3f P3f(2, 6, 7);
    std::cout << "Point (3D) = " << P3f << std::endl << std::endl;


    vector<float> v;
    v.push_back( (float)CV_PI);   v.push_back(2);    v.push_back(3.01f);
    
    std::cout << "Vector of floats via Mat = " << Mat(v) << std::endl << std::endl;
        
    std::vector<Point2f> vPoints(20);
    for (size_t E = 0; E < vPoints.size(); ++E)
        vPoints[E] = Point2f((float)(E * 5), (float)(E % 7));

    std::cout << "A vector of 2D Points = " << vPoints << std::endl << std::endl;

    return 0;

}



