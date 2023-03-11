<h1 align = "center">Virtual Painter with Color Wheel using OpenCV</h1>
This project is a virtual painter that allows users to draw on their computer screen using a variety of colors selected from a color wheel. The project is built using OpenCV with the C++ language and Visual Studio.

>## Installation
To install this project:
* Clone the repository (or download the zip file and extract it)
```bash
git clone https://github.com/samuelburaga/virtual-painter.git
```
* Open the folder called "Paint" in Visual Studio
* Run the file called "OpenCV.cpp"

>## Usage
Once the program is running, you can select a color from the color wheel and start drawing on your computer screen. If you're getting an error, it's very likely that your webcam hasn't connected. In my code I used my second webcam which has port number 1. Make sure you have at least one webcam connected. If you only have one, replace 1 with 0 in the following line of code in OpenCV.cpp:
```C plus plus
 int port = 1;
```
This program is created to detect a specific object/painting pen using its color. But the colors depend on the webcam, room lighting and many other things. I used a black marker for this. To detect your own specific object, run the file called "ColorDetection.cpp". Note that it is excluded from the project by default because the OpenCV.cpp file already has the main function implemented. After running the file, use the sliders until the only thing that appears in the additional window is your object.
Next, copy the values of the sliders and replace them in order in this line of code in the main file:
```C plus plus
std::vector <std::vector<int>> myColors{ {72, 0, 0, 118, 255, 50} };
```
>## Tools Used
This project was built using the following tools:

* Visual Studio 
<br clear = "all"><img src = "https://1000logos.net/wp-content/uploads/2020/08/Visual-Studio-Logo.png" width = "20%" height = "20%" style = "margin-top: 10px; margin-left: 10px">
* OpenCV <br clear = "all"><img src = "https://upload.wikimedia.org/wikipedia/commons/thumb/3/32/OpenCV_Logo_with_text_svg_version.svg/1662px-OpenCV_Logo_with_text_svg_version.svg.png" width = "10%" height = "10%" style = "margin-top:20px; margin-left: 43px">

## License
This project is licensed under the **MIT** license. See the **LICENSE** file for more details.