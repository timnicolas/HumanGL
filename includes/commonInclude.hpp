#ifndef COMMONINCLUDE_HPP
# define COMMONINCLUDE_HPP

# define DEBUG false  // type: bool -> enable / disable the debug mode
# define SCREEN_W 800  // [px] type: int ->width of the screen in pixels
# define SCREEN_H 600  // [px] type: int -> height of the screen in pixels
# define FPS 30  // [Hz] type: int -> fps of the main loop
# define LOOP_TIME (1000 / FPS)  // [s] type: float -> duration in s for a loop

// GL_TRUE if we need to reverse the matrix data. else GL_FALSE
# define MAT_SHADER_TRANSPOSE GL_TRUE  // type: bool -> GL_FALSE | GL_TRUE

# define NUM_BONES_PER_VERTEX 4 // type: int -> number of bones per vertex
# define MAX_BONES 100 // maximum bones on the model

# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <string>
# include <iostream>

# include <assimp/scene.h>
# include "Matrix.hpp"
# include "Quaternion.hpp"

/* matrix conversion */
aiMatrix4x4 mat4ToAi(mat::Mat4 mat);
mat::Mat4 aiToMat4(aiMatrix4x4& in_mat);
aiQuaternion quatToAi(mat::Quaternion quat);
mat::Quaternion aiToQuat(aiQuaternion& in_quat);
mat::Vec3 aiToVec3(aiVector3D v);
aiVector3D vec3ToAi(mat::Vec3 v);

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#endif
