# Star-Trail

The aim of this program is to create what we call in astrophotography star trail. Star trail photography are simply successive pictures taken on a excessive length of time so that we can perceived the movement of the stars in the night sky due to rotation of the earth. With DSLR camera, we can take multiple picture succesively instead of one very long picture to get approximately the same effect, then we stack then and get on picture with the star trail. 

To resolve this problem, the issue has been tackled with two differents solution: a first iteration Python, then a highly optimised version in C++. Both of these solution relies on OpenCV to do the images importation and writting. 

### Python solution

On the python program, we import each pictures and consider the first of the list as the referenced pictures on wich we will add the signal of the other. Then to create the star trail we go through each and every pixel of each pictures which is why the python program is highly time inefficient. For this example, each pictures has 24M pixel and we have stacked 25 pictures. To reduce the time inefficiency, we have compared the pixel by group of 4 pixels instead of 1 by 1 pixels. This solution is relatively accurate when we do not need to zoom in. If we search in the detail we can found the stair effect on the edge of the stars. Pixel are only added when the reach more than 10% of the reference pixel (or group of 4 pixels).

### C++ solution

To improve the efficiency of the program, we have implemented it in C++. When we work on the 25 pictures and study pixel by pixel (instead of 4 pixel by 4 pixel on python) we complete the star trail in 12 minutes on a Ryzen 7 4700U using only one thread. This is still not comparable to other software. For example, starstax is only taking 10sec for the same pictures and gives a less important threshold effect when compared in the detail of the pictures. 
