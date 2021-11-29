#include "SFML/Graphics.hpp"
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>

using namespace std::chrono;
using namespace std;
using namespace sf;

//resolution of the window
const int width = 1280;
const int height = 720;

//used for complex numbers
struct complex_number
{   
    //real denotes the real part of the complex number
    long double real; 

    //imaginary denotes the imaginary part of the complex number
    long double imaginary;
};

//Based on the position in our case iterations,
//It gives the caluates rainblow color

void GiveRainbowColor(double position,int &a, int &b, int &c)
{
    unsigned char nmax=6; /* number of color segments */
    double m=nmax* position;
  
    int n=(int)m; // integer of m
  
    double f=m-n;  // fraction of m

    unsigned char t=(int)(f*255);
    
    // if position > 1 then we have repetition of colors it maybe useful    
      
    if (position>1.0){if (position-(int)position==0.0)position=1.0; else position=position-(int)position;}

    // gradient with 6 segments
    switch( n){

    case 0: { a = 255;     b = t;   c = 0;   break; };
    case 1: { a = 255 -t;  b = 255; c = 0;   break; };
    case 2: { a = 0;       b = 255; c = t;   break; };
    case 3: { a = 0;       b = 255 -t;  c = 255; break; };
    case 4: { a = t;       b = 0;   c = 255; break; };
    case 5: { a = 255;     b = 0;   c = 255 -t;  break; };
    default:{ a = 255;     b = 0;   c = 0;   break; };

    }; // case
}

//It generates the mandelbrot set and color it based on iterations(normal).

void generate_mandelbrot_set_org(sf::VertexArray& vertexarray, int pixel_shift_x, int pixel_shift_y, int maxiter, float zoom)
{

    //pixelshiftx defines how much coordinates shall the position be shifted in x direction

    //pixelshifty defines how much coordinates shall the position be shifted in y direction

    //maxiter is the maximum number of iterations

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //scale the pixel location to the complex plane for calculations
            long double x = ((long double)j - pixel_shift_x) / zoom;
            long double y = ((long double)i - pixel_shift_y) / zoom;

            complex_number c;

            c.real = x;
            c.imaginary = y;
            complex_number z = c;

            int iterations = 0; //keeps the track of the number of iterations

            //Here k is also tracking iterations
            //Every time the loop runs it increment the iterations
            for (int k = 0; k < maxiter; k++)
            {   
                //z2 is the new complex number 
                complex_number z2;

                //z2 is equal to z^2 + c
                // z^2 = (z.real + iz.img)*(z.real + iz.img)
                // z^2  =  (z.real^2 - z.img^2) + i2*z.real*z.img
                // z2 = (z.real^2 - z.img^2) + i2*z.real*z.img + c.real + ic.img
                z2.real = z.real * z.real - z.imaginary * z.imaginary;

                z2.real += c.real;

                z2.imaginary = 2 * z.real * z.imaginary;
                
                z2.imaginary += c.imaginary;

                z = z2;

                //incrementing the iterations
                iterations++;

                //If at any point the mod of z exceeds 2 then break the loop
                if (z.real * z.real + z.imaginary * z.imaginary > 4)
                {
                    break;
                }

            }


            //coloring pixel based on the number of iterations
            if (iterations < maxiter / 4.0f)
            {
                //Vector2f genereates a point/vector at j,i with float values
                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                //setting the color of the point/pixel based on the iterations
                sf::Color color(iterations * 255.0f / (maxiter / 4.0f), 0, 0);

                //assigning the color to the vertex
                vertexarray[i*width + j].color = color;
            }

            else if (iterations < maxiter / 2.0f)
            {
                //Vector2f genereates a point/vector at j,i with float values
                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                //setting the color of the point/pixel based on the iterations
                sf::Color color(0, iterations * 255.0f / (maxiter / 2.0f), 0);

                //assigning the color to the vertex
                vertexarray[i*width + j].color = color;
            }

            else if (iterations < maxiter)
            {
                //Vector2f genereates a point/vector at j,i with float values
                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                //setting the color of the point/pixel based on the iterations
                sf::Color color(0, 0, iterations * 255.0f / maxiter);

                //assigning the color to the vertex
                vertexarray[i*width + j].color = color;
            }
        }
    }
}

//It generates the mandelbrot set and color it based on iterations but here I have colored it with red and golden.

void generate_mandelbrot_set_gold(sf::VertexArray& vertexarray, int pixel_shift_x, int pixel_shift_y, int maxiter, float zoom)
{

    //pixelshiftx defines how much coordinates shall the position be shifted in x direction

    //pixelshifty defines how much coordinates shall the position be shifted in y direction

    //maxiter is the maximum number of iterations

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //scale the pixel location to the complex plane for calculations
            long double x = ((long double)j - pixel_shift_x) / zoom;
            long double y = ((long double)i - pixel_shift_y) / zoom;

            complex_number c;

            c.real = x;
            c.imaginary = y;
            complex_number z = c;

            int iterations = 0; //keeps the track of the number of iterations

            //Here k is also tracking iterations
            //Every time the loop runs it increment the iterations
            for (int k = 0; k < maxiter; k++)
            {   
                //z2 is the new complex number 
                complex_number z2;

                //z2 is equal to z^2 + c
                // z^2 = (z.real + iz.img)*(z.real + iz.img)
                // z^2  =  (z.real^2 - z.img^2) + i2*z.real*z.img
                // z2 = (z.real^2 - z.img^2) + i2*z.real*z.img + c.real + ic.img
                z2.real = z.real * z.real - z.imaginary * z.imaginary;

                z2.real += c.real;

                z2.imaginary = 2 * z.real * z.imaginary;
                
                z2.imaginary += c.imaginary;

                z = z2;

                //incrementing the iterations
                iterations++;

                //If at any point the mod of z exceeds 2 then break the loop
                if (z.real * z.real + z.imaginary * z.imaginary > 4)
                {
                    break;
                }

            }

           
            int r = iterations * 255 / (maxiter);

            //color pixel based on the number of iterations
            if(iterations < maxiter/4){

                sf::Color color(4*r, 0, 0);

                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                vertexarray[i*width + j].color = color;
            }

            else if(iterations < maxiter){

                sf::Color color(r, r, 0);

                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                vertexarray[i*width + j].color = color;
            }
        }
    }
}

//Function to color the pixels black and white
void generate_mandelbrot_set_bnw(sf::VertexArray& vertexarray, int pixel_shift_x, int pixel_shift_y, int maxiter, float zoom)
{

    //pixelshiftx defines how much coordinates shall the position be shifted in x direction

    //pixelshifty defines how much coordinates shall the position be shifted in y direction

    //maxiter is the maximum number of iterations

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //scale the pixel location to the complex plane for calculations
            long double x = ((long double)j - pixel_shift_x) / zoom;
            long double y = ((long double)i - pixel_shift_y) / zoom;

            complex_number c;

            c.real = x;
            c.imaginary = y;
            complex_number z = c;

            int iterations = 0; //keeps the track of the number of iterations

            //Here k is also tracking iterations
            //Every time the loop runs it increment the iterations
            for (int k = 0; k < maxiter; k++)
            {   
                //z2 is the new complex number 
                complex_number z2;

                //z2 is equal to z^2 + c
                // z^2 = (z.real + iz.img)*(z.real + iz.img)
                // z^2  =  (z.real^2 - z.img^2) + i2*z.real*z.img
                // z2 = (z.real^2 - z.img^2) + i2*z.real*z.img + c.real + ic.img
                z2.real = z.real * z.real - z.imaginary * z.imaginary;

                z2.real += c.real;

                z2.imaginary = 2 * z.real * z.imaginary;
                
                z2.imaginary += c.imaginary;

                z = z2;

                //incrementing the iterations
                iterations++;

                //If at any point the mod of z exceeds 2 then break the loop
                if (z.real * z.real + z.imaginary * z.imaginary > 4)
                {
                    break;
                }

            }
            
            //color pixel based on the number of iterations
            if (iterations==maxiter)
            { /* interior of Mandelbrot set = black */
                sf::Color color(0, 0, 0);

                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                vertexarray[i*width + j].color = color;           
            }

            else 
            {   
                //White color
                sf::Color color(255, 255, 255);

                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                vertexarray[i*width + j].color = color;  
            }

        }
    }
}

//LSM is also a Black and White coloring but some more details
void generate_mandelbrot_set_lsm(sf::VertexArray& vertexarray, int pixel_shift_x, int pixel_shift_y, int maxiter, float zoom)
{

    //pixelshiftx defines how much coordinates shall the position be shifted in x direction

    //pixelshifty defines how much coordinates shall the position be shifted in y direction

    //maxiter is the maximum number of iterations

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //scale the pixel location to the complex plane for calculations
            long double x = ((long double)j - pixel_shift_x) / zoom;
            long double y = ((long double)i - pixel_shift_y) / zoom;

            complex_number c;

            c.real = x;
            c.imaginary = y;
            complex_number z = c;

            int iterations = 0; //keeps the track of the number of iterations

            //Here k is also tracking iterations
            //Every time the loop runs it increment the iterations
            for (int k = 0; k < maxiter; k++)
            {   
                //z2 is the new complex number 
                complex_number z2;

                //z2 is equal to z^2 + c
                // z^2 = (z.real + iz.img)*(z.real + iz.img)
                // z^2  =  (z.real^2 - z.img^2) + i2*z.real*z.img
                // z2 = (z.real^2 - z.img^2) + i2*z.real*z.img + c.real + ic.img
                z2.real = z.real * z.real - z.imaginary * z.imaginary;

                z2.real += c.real;

                z2.imaginary = 2 * z.real * z.imaginary;
                
                z2.imaginary += c.imaginary;

                z = z2;

                //incrementing the iterations
                iterations++;

                //If at any point the mod of z exceeds 2 then break the loop
                if (z.real * z.real + z.imaginary * z.imaginary > 4)
                {
                    break;
                }

            }
            

            if (iterations==maxiter)
            { 
                /* interior of Mandelbrot set = black */
                sf::Color color(0, 0, 0);

                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                vertexarray[i*width + j].color = color;                          
            }

            /* exterior of Mandelbrot set = LSM */
            else if ((iterations%2)==0) 
            { 
                /* even number = black */
                sf::Color color(0, 0, 0);

                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                vertexarray[i*width + j].color = color; 
            }
            else 
            {
                /* odd number =  white */
                sf::Color color(255, 255, 255);

                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                vertexarray[i*width + j].color = color;     
            }

        }
    }
}


//Function to color the set in rainbow colors
void generate_mandelbrot_set_rnb(sf::VertexArray& vertexarray, int pixel_shift_x, int pixel_shift_y, int maxiter, float zoom)
{

    //pixelshiftx defines how much coordinates shall the position be shifted in x direction

    //pixelshifty defines how much coordinates shall the position be shifted in y direction

    //maxiter is the maximum number of iterations

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //scale the pixel location to the complex plane for calculations
            long double x = ((long double)j - pixel_shift_x) / zoom;
            long double y = ((long double)i - pixel_shift_y) / zoom;

            complex_number c;

            c.real = x;
            c.imaginary = y;
            complex_number z = c;

            int iterations = 0; //keeps the track of the number of iterations

            //Here k is also tracking iterations
            //Every time the loop runs it increment the iterations
            for (int k = 0; k < maxiter; k++)
            {   
                //z2 is the new complex number 
                complex_number z2;

                //z2 is equal to z^2 + c
                // z^2 = (z.real + iz.img)*(z.real + iz.img)
                // z^2  =  (z.real^2 - z.img^2) + i2*z.real*z.img
                // z2 = (z.real^2 - z.img^2) + i2*z.real*z.img + c.real + ic.img
                z2.real = z.real * z.real - z.imaginary * z.imaginary;

                z2.real += c.real;

                z2.imaginary = 2 * z.real * z.imaginary;
                
                z2.imaginary += c.imaginary;

                z = z2;

                //incrementing the iterations
                iterations++;

                //If at any point the mod of z exceeds 2 then break the loop
                if (z.real * z.real + z.imaginary * z.imaginary > 4)
                {
                    break;
                }

            }
            
            //ismooth smoothly changes color
            double ismooth = iterations + 1 - log(0.5*log(z.real*z.real + z.imaginary*z.imaginary))/log(2);

            if (iterations==maxiter)
            { 
                /*  interior of Mandelbrot set = black */
                sf::Color color(0, 0, 0);

                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                vertexarray[i*width + j].color = color;                          
            }

            //exterior of Mandelbrot set  
            else {

                //a denotes red(R)
                //b denotes green(G)
                //c denotes blue(B)
                int a,b,c;

                //Based on number of iterations,
                //it colors the set in rainbow form
                GiveRainbowColor(ismooth/maxiter*20,a,b,c);

                //a,b,c are derived from the above function
                sf::Color color(a, b, c);

                vertexarray[i*width + j].position = sf::Vector2f(j, i);

                vertexarray[i*width + j].color = color;
            }

        }
    }
}



int main()
{

    sf::String title_string = "Mandelbrot";

    sf::RenderWindow window(sf::VideoMode(width, height), title_string);
    window.setFramerateLimit(30);

    //Creating array of points
    sf::VertexArray pointmap(sf::Points, width * height); 
    
    //Zoom the set
    float zoom = 150.0f;

    //Maximum iterations
    int maxiter = 50;

    //shift in the x coordiante,
    //as the origin in SFML is in the upper left corner
    float x_shift = width / 2;

    //shift in the y coordiante,
    //as the origin in SFML is in the upper left corner
    float y_shift = height / 2;

    //Stores the pointmap vertex array
    stack<VertexArray> pointmapstack;

    //Stores the zoom in stack
    stack<float> zoomstack;

    //Stores the maxiterations in a stack
    stack<int> maxiterstack;

    //Stores the x_shift values in stack
    stack<float> xshiftstack;

    //Stores the y_shift values in stack
    stack<float> yshiftstack;

    //Array storing the time taken for the function to draw at the particular maxiter
    int itertimes[10]={0};

    //Array storing the time taken for the function to draw at the particular zoom    
    int zoomtimes[6]={0};

    //Current color tracks the style of coloring used 
    int currentcolor = 0;

    //Whether to add the plot to stack or not
    bool addtostack = true;

    //Pushing the pointmap inside the stack
    pointmapstack.push(pointmap);

    //Pushing the zoop inside the stack
    zoomstack.push(zoom);

    //Pushing the maxiterations inside the stack
    maxiterstack.push(maxiter);

    //Pushing the x_shift inside the stack
    xshiftstack.push(x_shift);

    //Pushing the y_shift inside the stack
    yshiftstack.push(y_shift);


    //Calling the mandelbrot set to draw
    //current is 0 therefore I have called org fucntion
    generate_mandelbrot_set_org(pointmap, x_shift, y_shift, maxiter, zoom);
    
    while (window.isOpen())
    {   
        //stores the text
        sf::Text text;

        //Font set to arial
        Font font; font.loadFromFile("arial.ttf");

        // select the font
        text.setFont(font); // font is a sf::Font

        // set the character size
        text.setCharacterSize(24); // in pixels, not points!

        // set the color
        text.setFillColor(sf::Color::White);

        // set the text style
        //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

 
        sf::Event event;
        while (window.pollEvent(event))
        {
            //Closes the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
            {
                //Left arrow key shifts the set to left by 10 units
                if (event.key.code == Keyboard::Left) { 
                    x_shift -= 10;
                }

                //Right arrow key shifts the set to right by 10 units
                if (event.key.code == Keyboard::Right) { 
                    x_shift += 10; 
                }

                //Up arrow key shifts the set upwards by 10 units
                if (event.key.code == Keyboard::Up) { 
                    y_shift -= 10; 
                }

                //Down arrow key shifts the set downwards by 10 units
                if (event.key.code == Keyboard::Down) { 
                    y_shift += 10; 
                }

                //Q sets the coloring pattern to 0
                if (event.key.code == Keyboard::Q) { 
                    currentcolor = 0;
                }

                //W sets the coloring pattern to 1
                if (event.key.code == Keyboard::W) { 
                    currentcolor = 1;
                }

                //E sets the coloring pattern to 2
                if (event.key.code == Keyboard::E) { 
                    currentcolor = 2;
                }

                //R sets the coloring pattern to 3
                if (event.key.code == Keyboard::R) { 
                    currentcolor = 3;
                }

                //T sets the coloring pattern to 4
                if (event.key.code == Keyboard::T) { 
                    currentcolor = 4;
                }

                //P Takes to the previous plot,
                //which is stores inside the stacks
                if (event.key.code == Keyboard::P) { 

                    //Top of stack means the latest added term
                    pointmap = pointmapstack.top();
                    zoom = zoomstack.top();
                    maxiter = maxiterstack.top();
                    x_shift = xshiftstack.top();
                    y_shift = yshiftstack.top();

                    //Pop removes the top element in the stack
                    pointmapstack.pop();
                    zoomstack.pop();
                    maxiterstack.pop();
                    xshiftstack.pop();
                    yshiftstack.pop();

                    //I have the set the preivious to default color 0
                    currentcolor = 0;

                    //This previous values need not to be added again in stack,
                    //therefore set the  addtostack bool to false
                    addtostack = false;

                }

                //Resetting every pixel to black color before updating
                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                if(addtostack){
                    //Pushing the pointmap inside the stack
                    pointmapstack.push(pointmap);

                    //Pushing the zoop inside the stack
                    zoomstack.push(zoom);

                    //Pushing the maxiterations inside the stack
                    maxiterstack.push(maxiter);

                    //Pushing the x_shift inside the stack
                    xshiftstack.push(x_shift);

                    //Pushing the y_shift inside the stack
                    yshiftstack.push(y_shift);
                }
            
                if(currentcolor == 0){
                    generate_mandelbrot_set_org(pointmap, x_shift, y_shift, maxiter, zoom);
                }
                else if(currentcolor == 1){
                    generate_mandelbrot_set_bnw(pointmap, x_shift, y_shift, maxiter, zoom);
                }
                else if(currentcolor == 2){
                    generate_mandelbrot_set_lsm(pointmap, x_shift, y_shift, maxiter, zoom);
                }
                else if(currentcolor == 3){
                    generate_mandelbrot_set_rnb(pointmap, x_shift, y_shift, maxiter, zoom);
                }
                else if(currentcolor == 4){
                    generate_mandelbrot_set_gold(pointmap, x_shift, y_shift, maxiter, zoom);
                }

            }

            if (event.type == Event::MouseWheelScrolled)
            {
                if (event.MouseWheelScrolled)
                {
                    if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel)
                    {
                        //Incrementing the maxiter by 50
                        if (event.mouseWheelScroll.delta > 0){
                            maxiter += 50;
                        }

                        //Decrementing the maxiter by 50
                        else{
                            maxiter -= 50;
                        }

                        //Setting the lowerbound for maxiter to 50
                        if (maxiter < 50){
                            maxiter = 50;
                        }

                        //Setting the upperbound for maxiter to 500
                        if(maxiter > 500){
                            maxiter = 500;
                        }
                    }
                }

                for (int i = 0; i < width*height; i++)
                {
                    pointmap[i].color = sf::Color::Black;
                }

                //Pushing the pointmap inside the stack
                pointmapstack.push(pointmap);

                //Pushing the zoop inside the stack
                zoomstack.push(zoom);

                //Pushing the maxiterations inside the stack
                maxiterstack.push(maxiter);

                //Pushing the x_shift inside the stack
                xshiftstack.push(x_shift);

                //Pushing the y_shift inside the stack
                yshiftstack.push(y_shift);

                //Starting virtual time
                auto start1 = high_resolution_clock::now();

                if(currentcolor == 0){
                    generate_mandelbrot_set_org(pointmap, x_shift, y_shift, maxiter, zoom);
                }
                else if(currentcolor == 1){
                    generate_mandelbrot_set_bnw(pointmap, x_shift, y_shift, maxiter, zoom);
                }
                else if(currentcolor == 2){
                    generate_mandelbrot_set_lsm(pointmap, x_shift, y_shift, maxiter, zoom);
                }
                else if(currentcolor == 3){
                    generate_mandelbrot_set_rnb(pointmap, x_shift, y_shift, maxiter, zoom);
                }
                else if(currentcolor == 4){
                    generate_mandelbrot_set_gold(pointmap, x_shift, y_shift, maxiter, zoom);
                }

                //Stoping time
                auto stop1 = high_resolution_clock::now();

                //iter_time tracks the amount of time taken for plotting the set,
                //on changing the maxiter,
                //its in nanoseconds
                auto iter_time = duration_cast<nanoseconds>(stop1 - start1);

                //Only calculating time for the default color case
                if(currentcolor == 0){

                    if(maxiter == 50){
                        itertimes[0]=(itertimes[0]+iter_time.count())/2;
                    }
                    if(maxiter == 100){
                        itertimes[1]=(itertimes[1]+iter_time.count())/2;
                    }
                    if(maxiter == 150){
                        itertimes[2]=(itertimes[2]+iter_time.count())/2;
                    }
                    if(maxiter == 200){
                        itertimes[3]=(itertimes[3]+iter_time.count())/2;
                    }
                    if(maxiter == 250){
                        itertimes[4]=(itertimes[4]+iter_time.count())/2;
                    }
                    if(maxiter == 300){
                        itertimes[5]=(itertimes[5]+iter_time.count())/2;
                    }
                    if(maxiter == 350){
                        itertimes[6]=(itertimes[6]+iter_time.count())/2;
                    }
                    if(maxiter == 400){
                        itertimes[7]=(itertimes[7]+iter_time.count())/2;
                    }
                    if(maxiter == 450){
                        itertimes[8]=(itertimes[8]+iter_time.count())/2;
                    }
                    if(maxiter == 500){
                        itertimes[9]=(itertimes[9]+iter_time.count())/2;
                    }
                }
            }
        }


        //zoom into area that is left clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            x_shift -= position.x - x_shift;
            y_shift -= position.y - y_shift;

            //Doubling the zoom on each left click
            zoom *= 2;

            for (int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }

            //Pushing the pointmap inside the stack
            pointmapstack.push(pointmap);

            //Pushing the zoop inside the stack
            zoomstack.push(zoom);

            //Pushing the maxiterations inside the stack
            maxiterstack.push(maxiter);

            //Pushing the x_shift inside the stack
            xshiftstack.push(x_shift);

            //Pushing the y_shift inside the stack
            yshiftstack.push(y_shift);

            //Starting time
            auto start2 = high_resolution_clock::now();

            if(currentcolor == 0){
                generate_mandelbrot_set_org(pointmap, x_shift, y_shift, maxiter, zoom);
            }
            else if(currentcolor == 1){
                generate_mandelbrot_set_bnw(pointmap, x_shift, y_shift, maxiter, zoom);
            }
            else if(currentcolor == 2){
                generate_mandelbrot_set_lsm(pointmap, x_shift, y_shift, maxiter, zoom);
            }
            else if(currentcolor == 3){
                generate_mandelbrot_set_rnb(pointmap, x_shift, y_shift, maxiter, zoom);
            }
            else if(currentcolor == 4){
                generate_mandelbrot_set_gold(pointmap, x_shift, y_shift, maxiter, zoom);
            }

            //Stopping time
            auto stop2 = high_resolution_clock::now();

            //zoom_time tracks the amount of time taken for plotting the set,
            //on changing the zoom,
            //its in nanoseconds
            auto zoom_time = duration_cast<nanoseconds>(stop2 - start2);

            if(currentcolor == 0){
                if(zoom == 300){
                    zoomtimes[0]=(zoomtimes[0]+zoom_time.count())/2;
                }
                if(zoom == 600){
                    zoomtimes[1]=(zoomtimes[1]+zoom_time.count())/2;
                }
                if(zoom == 1200){
                    zoomtimes[2]=(zoomtimes[2]+zoom_time.count())/2;
                }
                if(zoom == 2400){
                    zoomtimes[3]=(zoomtimes[3]+zoom_time.count())/2;
                }
                if(zoom == 4800){
                    zoomtimes[4]=(zoomtimes[4]+zoom_time.count())/2;
                }
                if(zoom == 9600){
                    zoomtimes[5]=(zoomtimes[5]+zoom_time.count())/2;
                }
                // if(zoom == 19200){zoomtimes[0]=(zoomtimes[0]+zoom_time.count())/2;}
                // if(zoom == 400){zoomtimes[0]=(zoomtimes[0]+zoom_time.count())/2;}
                // if(zoom == 450){zoomtimes[0]=(zoomtimes[0]+zoom_time.count())/2;}
                // if(zoom == 500){zoomtimes[0]=(zoomtimes[0]+zoom_time.count())/2;}
            }
        }

        //Zooming out from origin when right click is pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            //sf::Vector2i position = sf::Mouse::getPosition(window);
            x_shift = width/2;
            y_shift = height/2;
            zoom /= 2;

            for (int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }

            //Pushing the pointmap inside the stack
            pointmapstack.push(pointmap);

            //Pushing the zoop inside the stack
            zoomstack.push(zoom);

            //Pushing the maxiterations inside the stack
            maxiterstack.push(maxiter);

            //Pushing the x_shift inside the stack
            xshiftstack.push(x_shift);

            //Pushing the y_shift inside the stack
            yshiftstack.push(y_shift);

            if(currentcolor == 0){
                generate_mandelbrot_set_org(pointmap, x_shift, y_shift, maxiter, zoom);
            }
            else if(currentcolor == 1){
                generate_mandelbrot_set_bnw(pointmap, x_shift, y_shift, maxiter, zoom);
            }
            else if(currentcolor == 2){
                generate_mandelbrot_set_lsm(pointmap, x_shift, y_shift, maxiter, zoom);
            }
            else if(currentcolor == 3){
                generate_mandelbrot_set_rnb(pointmap, x_shift, y_shift, maxiter, zoom);
            }
            else if(currentcolor == 4){
                generate_mandelbrot_set_gold(pointmap, x_shift, y_shift, maxiter, zoom);
            }
        }
        window.clear();

        char str[100];

        sprintf(str, "max iter:%d\nzoom:x%2.2lf\ncoloring pattern:%d", maxiter, zoom, currentcolor);

        // set the string to display
        text.setString(str);

        window.draw(pointmap);
        window.draw(text);
        window.display();
    }
    
    //Printing the iteration times inside a file itertimes.txt
    ofstream MyFile("itertimes.txt");
    for(int i=0; i<10; i++)
    {
        MyFile << itertimes[i]<<endl;
    }

    //Printing the zoom times inside a file zoomimes.txt
    ofstream MyFile1("zoomtimes.txt");
    for(int i=0; i<6; i++)
    {
        MyFile1 << zoomtimes[i]<<endl;
    }

    return 0;
}

/* 

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

*/