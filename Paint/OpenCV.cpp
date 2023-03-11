#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

Mat image, initialImage;

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
    }
}