/************************************************************************/
/* ros-opencv-examples                                                  */
/*       --   A ROS package containing OpenCV examples                  */
/*                                                                      */
/*                                                                      */
/* cam_record.cpp                                                       */
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

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <iostream>
 
using namespace std;
int main()
{
    CvCapture* capture = cvCaptureFromCAM(-1);
    // CvVideoWriter* video = NULL;
    // IplImage* frame = NULL;
    cv::Mat frame;
    int n;
    if(!capture)
    {
       cout << "Can not open the camera." << endl;
       return -1;
    }
    else
    {
        frame = cvQueryFrame(capture);
        int rows = frame.rows;
        int cols = frame.cols;

        cv::Size s = frame.size();
        rows = s.height;
        cols = s.width;

        // video = cvCreateVideoWriter("camera_record.avi", CV_FOURCC('X', 'V', 'I', 'D'), 25, s); 
        cv::VideoWriter video("camera_record.avi", CV_FOURCC('X', 'V', 'I', 'D'), 25, s);
        // VideoWriter Video_rec(finalfile, CV_FOURCC('D','I','V','X'), 25,src.size(), false);

        if(video.isOpened())
        {
            cout << "VideoWriter has been created." << endl;
        }

        // cvNamedWindow("Camera Video", 1);
        cv::namedWindow("Camera Video", 1);
        int i = 0;
        while(i <= 200) 
        {
            frame = cvQueryFrame(capture); 
            if(!frame.data)
            {
                cout << "Cannot get frame from the capture."<<endl;
                break;
            }
            // n = cvWriteFrame(video, frame);
            video << frame;
            // cvShowImage("Camera Video", frame);
            imshow("Camera Video", frame);
            i++;
            if(cvWaitKey(2)>0) 
                break;
        }

        // cvReleaseVideoWriter(&video);
        cvReleaseCapture(&capture);
        cvDestroyWindow("Camera Video");
    }
    return 0;
}
