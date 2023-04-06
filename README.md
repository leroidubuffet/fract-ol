
# fract-ol

### 42 Madrid fract'ol project
This is a C program that generates fractals and displays them on a window using the MiniLibX graphics library.

### Fractals

A fractal is created by repeating a specific process or formula over and over again. This formula generates a pattern that repeats itself at different scales, creating the same shape no matter how much you zoom in or out.

  

### Mandelbrot
In the Mandelbrot fractal, you start with a complex number and then perform a calculation on that number. If the result is within a certain range, you color that point black. If it is outside the range, you color it a different color based on how quickly the result grew beyond the range. You then repeat this process for every point on a grid covering the complex plane.
  

`z[n+1] = z[n]^2 + c`

where z[0] is set to 0.

  

For each pixel in the complex plane, the corresponding value of c is calculated as
 
`c = x + yi`

where x is the real component and y is the imaginary component of the pixel's position in the plane.

  

The values of x and yi are calculated based on the pixel coordinates of the image being generated and the minimum and maximum values of the real and imaginary axes of the complex plane.

`x = min_r + x * (max_r - min_r) / (image_width - 1)`

`yi = min_i + y * (max_i - min_i) / (image_height - 1)`

min_r and max_r are the minimum and maximum values of the real axis, min_i and max_i are the minimum and maximum values of the imaginary axis, image_width and image_height are the width and height of the image, and x and i are the pixel coordinates of the image.

  

The iteration continues until either the absolute value of z[n] becomes greater than a certain threshold (indicating that z[n] is "escaping" to infinity) or a maximum number of iterations is reached. If the maximum number of iterations is reached without z[n] escaping, then c is considered to be in the Mandelbrot set.

  

For each point c in the complex plane, we repeatedly square the value of z and add c, then use the result as the new value of z. We keep doing this until either z grows too large or we have iterated a fixed number of times. If z never grows too large, then the point c is considered to be in the Mandelbrot set.

  

By changing the range of numbers used in the calculation, you can zoom in and out of the fractal, revealing new details and patterns. The same process is used for other fractals, but with different formulas and criteria for coloring the points on the grid. Zooming in a fractal means changing the scale of the image by adjusting the boundaries of the complex plane that is being rendered: zooming in and out of the fractal by changing the viewing window.

On each function's comments we will cover the differences with the Julia and Burning ship sets.

### fractals.c
This file holds the core of the program. It contains functions that calculate the different fractal sets.
* ft_mandelbrot

This function implements the Mandelbrot set fractal. It takes two arguments, pr and pi, which represent the real and imaginary parts of the starting point of the iteration (in this case, both are set to 0). The function then performs a series of calculations on this point to determine whether it is part of the Mandelbrot set or not. 
The formula used for this iteration is:

`z = z^2 + c`

where z and c are both complex numbers. In this case, c is set to the value of pr + pi*i. As with the Julia set, the function continues iterating until z exceeds the threshold value or until it reaches the maximum number of iterations allowed. If z exceeds the threshold value, the function determines that the point is not part of the Mandelbrot set and returns false. Otherwise, it returns true.
* ft_julia

This function mplements the Julia set fractal. It takes two arguments, pr and pi, which represent the real and imaginary parts of the starting point of the iteration. The function then performs a series of calculations on this point to determine whether it is part of the Julia set or not. 
The formula used for this iteration is:

`z = z^2 + c`

where z is the complex number being iterated and c is a constant complex number. In this case, c is determined by the values of f->kr and f->ki, which are set by the program. If the point z remains within a certain threshold value (in this case, 4.0), the function continues iterating until it reaches the maximum number of iterations allowed (f->max_iterations). If the point z exceeds the threshold value at any point during the iteration, the function determines that it is not part of the Julia set and returns false (is_in_set = 0). Otherwise, it returns true (is_in_set = 1).

* ft_burning_ship

Burning Ship fractal calculation. It takes two arguments, pr and pi, which represent the real and imaginary parts of the starting point of the iteration (in this case, both are set to 0). The function then performs a series of calculations on this point to determine whether it is part of the Burning Ship fractal or not. 
The formula used for this iteration is:

`z = abs(z)^2 + c`

where z and c are both complex numbers. In this case, c is set to the value of pr + pi*i. As with the other fractals, the function continues iterating until z exceeds the threshold value or until it reaches the maximum number of iterations allowed. If z exceeds the threshold value, the function determines that the point is not part of the Burning Ship fractal and returns false. Otherwise, it returns true.
The abs() function is used to calculate the absolute value of a number: the value of the number without regard to its sign. For example, the absolute value of both 3 and -3 is 3.
In the context of the ft_burning_ship function the abs() function is used to calculate the absolute value of a complex number. The formula used in the iteration step of the Burning Ship fractal involves squaring the real and imaginary parts of the number separately, which means that the result may be a negative number. In order to calculate the correct value for the iteration, it's necessary to take the absolute value of the resulting real and imaginary parts.
