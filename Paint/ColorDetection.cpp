#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int hue_minimum = 0, saturation_minimum = 0, value_minimum = 0;
int hue_maximum = 179, saturation_maximum = 255, value_maximum = 255;

void Trackbars()
{
    createTrackbar("Hue minimum", "Trackbars", &hue_minimum, 179);
    createTrackbar("Saturation minimum", "Trackbars", &saturation_minimum, 255);
    createTrackbar("Value minimum", "Trackbars", &value_minimum, 255);
    createTrackbar("Hue maximum", "Trackbars", &hue_maximum, 179);
    createTrackbar("Saturation maximum", "Trackbars", &saturation_maximum, 255);
    createTrackbar("Value maximum", "Trackbars", &value_maximum, 255);
}

void detectBrush(VideoCapture cap)
{
    Mat image, image_hsv, mask;
    namedWindow("Trackbars", (640, 200));
    Trackbars();
    while (true)
    {
        cap.read(image);
        cvtColor(image, image_hsv, COLOR_BGR2HSV);
        Scalar lower_limit(hue_minimum, saturation_minimum, value_minimum), upper_limit(hue_maximum, saturation_maximum, value_maximum);
        inRange(image_hsv, lower_limit, upper_limit, mask);
        imshow("Camera web!", image);
        imshow("Camera web mask!", mask);
        waitKey(1);
    }
}

bool webcam(VideoCapture& cap, int port)
{
    cap.open(port);
    try
    {
        if (cap.isOpened())
        {
            return true;
        }
        else
        {
            throw new std::exception("The webcam doesn't work");
        }
    }
    catch (...)
    {
        std::cout << "The webcam doesn't work!\n";
    }
}
void main()
{
    VideoCapture cap;
    int port = 1;
    if (webcam(cap, port))
    {
        detectBrush(cap);
    }
}