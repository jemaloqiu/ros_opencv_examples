#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
 
int main( int argc, const char** argv )
{
    CvCapture* capture;
    Mat frame;
     
    // Read the video stream
    capture = cvCaptureFromCAM( -1 );
    namedWindow("Video",CV_WINDOW_AUTOSIZE);
    if( capture )
    {
        while( true )
        {
            frame = cvQueryFrame( capture );
            imshow("Video",frame);
 
            // Press 'c' to escape
            int c = waitKey(10);
            if( (char)c == 'c' ) { break; }
        }
    }
    return 0;
}
