/************************************************************************/
/* ros-opencv-examples                                                  */
/*       --   A ROS package containing OpenCV examples                  */
/*                                                                      */
/*                                                                      */
/* reduce_color.cpp                                                     */
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

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar * table);


int main(int argc, char *argv[])
{
    std::string img_path = ros::package::getPath("opencv_examples");
    std::cout << "image path is " << img_path << std::endl;
    img_path += "/res/image.jpg";
  
    Mat I, J;
    I = imread(img_path, CV_LOAD_IMAGE_COLOR);        // here we'll know the method used (allocate matrix)

    if(! I.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    int divideWith = 50; // convert our input string to number - C++ style

    
    uchar table[256]; 
    for (int i = 0; i < 256; ++i)
       table[i] = divideWith* (i/divideWith);

    const int times = 10; 
    double t;

    t = (double)getTickCount();    
    
    for (int i = 0; i < times; ++i)
    {
        Mat I_cp = I.clone();
        J = ScanImageAndReduceC(I_cp, table);
    }

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the C operator [] (averaged for " 
         << times << " runs): " << t << " milliseconds."<< endl;  

    t = (double)getTickCount();    

    for (int i = 0; i < times; ++i)
    {
        Mat I_cp = I.clone();
        J = ScanImageAndReduceIterator(I_cp, table);
    }


    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the iterator (averaged for " 
        << times << " runs): " << t << " milliseconds."<< endl;  

    t = (double)getTickCount();    

    for (int i = 0; i < times; ++i)
    {
        Mat I_cp = I.clone();
        J = ScanImageAndReduceRandomAccess(I_cp, table);
    }
     

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the on-the-fly address generation - at function (averaged for " 
        << times << " runs): " << t << " milliseconds."<< endl;  

    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data; 
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];

    t = (double)getTickCount();    
    
    for (int i = 0; i < times; ++i)
        LUT(I, lookUpTable, J);

    t = 1000*((double)getTickCount() - t)/getTickFrequency();
    t /= times;

    cout << "Time of reducing with the LUT function (averaged for " 
        << times << " runs): " << t << " milliseconds."<< endl;  

    namedWindow( "Original image", WINDOW_AUTOSIZE );// Create a window for display.
    namedWindow( "Reduced image", WINDOW_AUTOSIZE );// Create a window for display.


    imshow( "Original image", I);    
    imshow( "Reduced image", J);                   // Show our image inside it.



    waitKey(0);    
    return 0; 
}


// C-style function showing how to scan each element in a Mat
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() != sizeof(uchar));     

    int channels = I.channels();

    int nRows = I.rows * channels; 
    int nCols = I.cols;

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;         
    }

    int i,j;
    uchar* p; 
    for( i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for ( j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];             
        }
    }
    return I; 
}

// The iterator (safe) method function showing how to scan each element in a Mat
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() != sizeof(uchar));     
    
    const int channels = I.channels();
    switch(channels)
    {
    case 1: 
        {
            MatIterator_<uchar> it, end; 
            for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = table[*it];
            break;
        }
    case 3: 
        {
            MatIterator_<Vec3b> it, end; 
            for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
    }
    
    return I; 
}


// On-the-fly address calculation with reference returning
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() != sizeof(uchar));     

    const int channels = I.channels();
    switch(channels)
    {
    case 1: 
        {
            for( int i = 0; i < I.rows; ++i)
                for( int j = 0; j < I.cols; ++j )
                    I.at<uchar>(i,j) = table[I.at<uchar>(i,j)];
            break;
        }
    case 3: 
        {
         Mat_<Vec3b> _I = I;
            
         for( int i = 0; i < I.rows; ++i)
            for( int j = 0; j < I.cols; ++j )
               {
                   _I(i,j)[0] = table[_I(i,j)[0]];
                   _I(i,j)[1] = table[_I(i,j)[1]];
                   _I(i,j)[2] = table[_I(i,j)[2]];
            }
         I = _I;
         break;
        }
    }
    
    return I;
}

// Core Function  LUT() -- LookUp Table

