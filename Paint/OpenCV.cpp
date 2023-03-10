#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void webcam()
{
    VideoCapture video(1);
    Mat image;
    while (true)
    {
        video.read(image);
        imshow("Web camera!", image);
        waitKey(1);
    }
}

void main()
{
    webcam();
}