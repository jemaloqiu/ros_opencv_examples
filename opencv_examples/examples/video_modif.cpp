/************************************************************************/
/* ros-opencv-examples                                                  */
/*       --   A ROS package containing OpenCV examples                  */
/*                                                                      */
/*                                                                      */
/* video_modif.cpp                                                       */
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

#include <string>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
 

using namespace std;
using namespace cv;


// rosrun pkg this_node finename 
// e.g: rosrun opencv_examples opencv_ros_video_modif myfile.avi
int main(int argc, char** argv)
{
    Mat src,inter,dst;
    string filename=argv[1];
    string buffer=filename;
    string finalfile=buffer.insert(filename.length()-4,"_improve");
    bool success=0;
    VideoCapture capture(filename);
    if (!capture.isOpened())
    {
        cout<<("Cannot open video streaming !\n"+filename)<<endl;
        return 1;
    }
    success=capture.read(src);
    VideoWriter Video_rec(finalfile, CV_FOURCC('D','I','V','X'), 25,src.size(), false);
    if (!Video_rec.isOpened())
    {
        cout << ("Cannot write to video file!\n"+finalfile)<<endl;
        return 1;
    }
    while(success)
    {
        cvtColor( src, inter, CV_BGR2GRAY );
        equalizeHist( inter, dst );
        Video_rec.write(dst);
        success=capture.read(src);
    }
    Video_rec.release();
    return 0;
}
