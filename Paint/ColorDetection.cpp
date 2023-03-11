#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int hueMinimum = 0, saturationMinimum = 0, valueMinimum = 0;
int hueMaximum = 179, saturationMaximum = 255, valueMaximum = 255;

void Trackbars()
{
    createTrackbar("Hue minimum", "Trackbars", &hueMinimum, 179);
    createTrackbar("Saturation minimum", "Trackbars", &saturationMinimum, 255);
    createTrackbar("Value minimum", "Trackbars", &valueMinimum, 255);
    createTrackbar("Hue maximum", "Trackbars", &hueMaximum, 179);
    createTrackbar("Saturation maximum", "Trackbars", &saturationMaximum, 255);
    createTrackbar("Value maximum", "Trackbars", &valueMaximum, 255);
}

void detectBrush(VideoCapture cap)
{
    Mat image, imageHSV, mask;
    namedWindow("Trackbars", (640, 200));
    Trackbars();
    while (true)
    {
        cap.read(image);
        cvtColor(image, imageHSV, COLOR_BGR2HSV);
        Scalar lowerLimit(hueMinimum, saturationMinimum, valueMinimum), upperLimit(hueMaximum, saturationMaximum, valueMaximum);
        inRange(imageHSV, lowerLimit, upperLimit, mask);
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