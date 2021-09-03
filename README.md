# Star-Trail

The aim of this program is to create what we call in astrophotography star trail. Star trail photography are simply successive pictures taken on a excessive length of time so that we can perceived the movement of the stars in the night sky due to rotation of the earth. With DSLR camera, we can take multiple pictures successively instead of one very long picture to get approximately the same effect, then we stack then and get on picture with the star trail.

To resolve this problem, the issue has been tackled with two different solutions: a first iteration Python, then a highly optimised version in C++. Both of these solution relies on OpenCV to do the images importation and writing.

### Python solution

On the python program, we import each picture and consider the first of the list as the referenced pictures on which we will add the signal of the other. Pixels are only added when the reach more than 10% of the reference pixel. Then to create the star trail we go through each and every pixel of each picture which is why the python program is highly time inefficient (The program takes around 24 min to complete the star trail with this small simplification on a Ryzen 7 4700U using only). For this example, each picture has 24M pixel and we have stacked 25 pictures. To reduce the time inefficiency, we have compared the pixel by group of 4 pixels instead of 1 by 1 pixels. This solution is relatively accurate when we do not need to zoom in. If we search in the detail, we can find the stair effect on the edge of the stars. This python solution is also very memory hungry by its design (between 3-4 Go used). Every pictures are stored inside one matrix. This will be optimised by only importing the pictures when need.

####      Python Result
<img src="https://github.com/Nicolas-M-Wong/Star-Trail/blob/main/Result/circum_polaire_1x1-Python.jpg?raw=true" alt="drawing" width="400"/>

   - Python Result 1 by 1 pixel
      
![alt text](https://github.com/Nicolas-M-Wong/Star-Trail/blob/main/Result/circum_polaire_fast2x2-Python.jpg?raw=true)

   - Python Result 2 by 2 pixels
      
### C++ solution

To improve the efficiency of the program, we have implemented it in C++. When we work on the 25 pictures and study pixel by pixel (instead of 4 pixels by 4 pixels on python) we complete the star trail in 12 minutes on a Ryzen 7 4700U using only one thread. This is still not comparable to other software. For example, starstax is only taking 10sec for the same pictures and gives a less important threshold effect when compared in the detail of the pictures.

####      C++ Result

![alt text](https://github.com/Nicolas-M-Wong/Star-Trail/blob/main/Result/circum_polaire_1x1-C++.jpg?raw=true)

      Python Result 1 by 1 pixel
      
