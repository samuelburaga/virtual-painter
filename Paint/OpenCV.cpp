#include <iostream>
#include <math.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Mat image, initialImage;
int b = 255, g = 255, r = 0;
std::vector <std::vector<int>> myColors{ {72, 0, 0, 118, 255, 50} };
std::vector <std::vector<int>> newPoints;
std::vector <Scalar> selectedColors;

void drawOnCanvas(Mat image)
{
    for (int index = 0; index < newPoints.size(); index++)
    {
        circle(image, Point(newPoints[index][0], newPoints[index][1]), 7, selectedColors[index], FILLED);
    }
}
Point getContours(Mat imageMask, Mat image)
{
    std::vector <std::vector<Point>> contours;
    std::vector <Vec4i> hierarchy;
    findContours(imageMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    std::vector <std::vector<Point>> contoursPoly(contours.size());
    std::vector <Rect> bounding_rect(contours.size());
    Point brushTip(0, 0);
    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        if (area > 1000)
        {
            float perimeter = arcLength(contours[i], true);
            approxPolyDP(contours[i], contoursPoly[i], 0.02 * perimeter, true);
            bounding_rect[i] = boundingRect(contoursPoly[i]);
            brushTip.x = bounding_rect[i].x + bounding_rect[i].width / 2;
            brushTip.y = bounding_rect[i].y;
            drawContours(image, contoursPoly, i, Scalar(255, 0, 255), 2);
            rectangle(image, bounding_rect[i].tl(), bounding_rect[i].br(), Scalar(0, 255, 0), 5);
            bounding_rect[i] = boundingRect(contoursPoly[i]);
        }
    }
    return brushTip;
}
void detectColors(Mat image)
{
    Mat imageHSV, mask;
    cvtColor(image, imageHSV, COLOR_BGR2HSV);
    for (int index = 0; index < myColors.size(); index++)
    {
        Scalar lowerLimit(myColors[index][0], myColors[index][1], myColors[index][2]);
        Scalar upperLimit(myColors[index][3], myColors[index][4], myColors[index][5]);
        inRange(imageHSV, lowerLimit, upperLimit, mask);
        Point brushTip = getContours(mask, image);
        if (brushTip.x != 0 && brushTip.y != 0)
        {
            newPoints.push_back({ brushTip.x, brushTip.y, index });
            selectedColors.push_back(Scalar(b, g, r));
        }
    }
}
bool additionalConditions(int x, int y)
{
    return pow(x - initialImage.size().width / 2, 2) + pow(y - initialImage.size().width / 2, 2) <= pow(initialImage.size().width / 2, 2);
}
void onMouse(int event, int x, int y, int flags, void* userdata)
{
    static bool leftButtonPressed = false;
    if (event == EVENT_LBUTTONDOWN)
    {
        leftButtonPressed = true;
    }
    else
    if (event == EVENT_LBUTTONUP)
    {
        leftButtonPressed = false;
    }
    if (leftButtonPressed)
    {
        if (x <= initialImage.size().width && y <= initialImage.size().height && additionalConditions(x, y))
        {
            Vec3b pixel = initialImage.at<Vec3b>(y, x);
            b = pixel[0];
            g = pixel[1];
            r = pixel[2];
            std::cout << "You picked the color: rgb(" << r << ", " << g << ", " << b << ")\n";
        }
    }
}
void stream(VideoCapture cap)
{
    namedWindow("Virtual painter");
    setMouseCallback("Virtual painter", onMouse, NULL);
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
        detectColors(newFrame);
        drawOnCanvas(newFrame);
        imshow("Virtual painter", newFrame);
        setMouseCallback("Virtual painter", onMouse, NULL);
        char key = (char)waitKey(30);
        if (key == 27)
        {
            break;
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