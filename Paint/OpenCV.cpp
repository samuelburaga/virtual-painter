#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Mat image, initialImage;

void stream(VideoCapture cap)
{
    Mat frame;
    while (true)
    {
        cap >> frame;
        Mat newFrame = frame.clone();
        if (!image.empty())
        {
            Rect dstRC = Rect(0, 0, 200, 200);
            Mat dstROI = newFrame(dstRC);
            Mat srcRGB;
            cvtColor(image, srcRGB, COLOR_BGRA2BGR);
            Mat srcAlpha;
            std::vector <Mat> channels;
            split(image, channels);
            srcAlpha = channels[3];
            srcRGB.copyTo(dstROI, srcAlpha);
        }

    }
}
void loadImage()
{
    image = imread("Resources/Images/Color wheel.png", IMREAD_UNCHANGED);
    resize(image, image, Size(200, 200));
    initialImage = imread("Resources/Images/Color wheel.png");
    resize(initialImage, initialImage, Size(200, 200));
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
        loadImage();
        stream(cap);
    }
}