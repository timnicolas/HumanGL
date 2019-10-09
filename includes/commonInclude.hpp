#ifndef COMMONINCLUDE_HPP
# define COMMONINCLUDE_HPP

# define DEBUG true  // type: bool -> enable / disable the debug mode
# define SCREEN_W 800  // [px] type: int ->width of the screen in pixels
# define SCREEN_H 600  // [px] type: int -> height of the screen in pixels
# define FPS 60  // [Hz] type: int -> fps of the main loop
# define LOOP_TIME (1000 / FPS)  // [s] type: float -> duration in s for a loop

// GL_TRUE if we need to reverse the matrix data. else GL_FALSE
# define MAT_SHADER_TRANSPOSE GL_TRUE  // type: bool -> GL_FALSE | GL_TRUE

# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <string>
# include <iostream>

# include "Matrix.hpp"

#endif
