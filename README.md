# Virtual Painter with Color Wheel using OpenCV
This project is a virtual painter that allows users to draw on their computer screen using a variety of colors selected from a color wheel. The project is built using OpenCV with the C++ language and Visual Studio.

## Installation
To install this project:
* Clone the repository (or download the zip code and extract it)

```bash
git clone https://github.com/samuelburaga/virtual-painter.git
```
* Open the folder called "Paint" in Visual Studio
* Run the file OpenCV.cpp

## Usage
Once the program is running, you can select a color from the color wheel and begin drawing on your computer screen. If you encounter an error it is very likely that your webcam didn't connect. In my code I used my second webcam, wich has the port number 1. Make sure that you have at least one webcam connected. If you only have one, replace 1 with 0 in the following line of code from OpenCV.cpp:
```C plus plus
 int port = 1;
```
Now, this program is created to detect a specific object/brush for painting using its colors. But the colors depend on the webcam, lightning and many other things. I used a black marker for this. To be sure that the program detects your object run the file ColorDetection.cpp and use the sliders until the only thing that appears in the additional window is your object.
Than, copy the values of the sliders and replace them in order in this line of code from the main file:
```C plus plus
std::vector <std::vector<int>> myColors{ {72, 0, 0, 118, 255, 50} };
```
## Tools Used
This project was built using the following tools:

* Visual Studio 
<br clear = "all"><img src = "https://1000logos.net/wp-content/uploads/2020/08/Visual-Studio-Logo.png" width = "20%" height = "20%" style = "margin-top: 10px; margin-left: 10px">
* OpenCV <br clear = "all"><img src = "https://upload.wikimedia.org/wikipedia/commons/thumb/3/32/OpenCV_Logo_with_text_svg_version.svg/1662px-OpenCV_Logo_with_text_svg_version.svg.png" width = "10%" height = "10%" style = "margin-top:20px; margin-left: 43px">


