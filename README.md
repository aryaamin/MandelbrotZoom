# MandelbrotZoom
Creating a MandelbrotZoom using SFML library.

To compile: g++ mandelbrot.cpp -lsfml-graphics -lsfml-window -lsfml-system
To run: ./a.out

Coloring pattern code
Original - 0
Black&White - 1
LSM - 2
Rainbow - 3
Red&Gold - 4
*/

/*
Keys
Left arrow -> shift left
Right arrow -> shift right
Up arrow -> shift upward
Down arrow ->shift downward
Q -> colorcode = 0
W -> colorcode = 1
E -> colorcode = 2
R -> colorcode = 3
T -> colorcode = 4
P -> Previous plot
Left Click -> Zoom In on clicked point
Right Click -> Zoom Out on center
Scroll Up -> Increase Maxiter
Scroll Down -> Decrease Maxiter
*/

/*
Since in the above code the for loop stops at maxiter and
therefore its linearly dependent on maxiter so as maxiter increase
the time also linearly increase.
Whereas, the zoom only changes the values of variables and thus 
its done in constant time, therefore as zoom is increase the time
to run the code does not change it remains consant
