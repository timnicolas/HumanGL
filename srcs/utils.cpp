#include "humanGL.hpp"

GLenum checkError_(const char *file, int line)
{
    GLenum errorCode;
    GLenum lastError = GL_NO_ERROR;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM: error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE: error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: error = "INVALID_OPERATION"; break;
            case 1283: error = "STACK_OVERFLOW"; break;  // GL_STACK_OVERFLOW
            case 1284:  error = "STACK_UNDERFLOW"; break;  // GL_STACK_UNDERFLOW
            case GL_OUT_OF_MEMORY: error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << "OpenGL error: " << error << " > " << file << " (" << line << ")" << std::endl;
        lastError = errorCode;
    }
    return lastError;
}

void checkErrorExit_(const char *file, int line)
{
    GLenum ret = checkError_(file, line);
    if (ret != GL_NO_ERROR)
        exit(1);
}

aiMatrix4x4 mat4ToAi(mat::Mat4 mat)
{
    return aiMatrix4x4(mat[0][0],mat[0][1],mat[0][2],mat[0][3],
                       mat[1][0],mat[1][1],mat[1][2],mat[1][3],
                       mat[2][0],mat[2][1],mat[2][2],mat[2][3],
                       mat[3][0],mat[3][1],mat[3][2],mat[3][3]);
}

mat::Mat4 aiToMat4(aiMatrix4x4& in_mat)
{
    mat::Mat4 tmp;
    tmp[0][0] = in_mat.a1;
    tmp[1][0] = in_mat.b1;
    tmp[2][0] = in_mat.c1;
    tmp[3][0] = in_mat.d1;

    tmp[0][1] = in_mat.a2;
    tmp[1][1] = in_mat.b2;
    tmp[2][1] = in_mat.c2;
    tmp[3][1] = in_mat.d2;

    tmp[0][2] = in_mat.a3;
    tmp[1][2] = in_mat.b3;
    tmp[2][2] = in_mat.c3;
    tmp[3][2] = in_mat.d3;

    tmp[0][3] = in_mat.a4;
    tmp[1][3] = in_mat.b4;
    tmp[2][3] = in_mat.c4;
    tmp[3][3] = in_mat.d4;
    return tmp;
}


aiQuaternion quatToAi(mat::Quaternion quat) {
    return aiQuaternion(quat.w, quat.vec.x, quat.vec.y, quat.vec.z);
}
mat::Quaternion aiToQuat(aiQuaternion& in_quat) {
    mat::Quaternion q = mat::Quaternion();
    q.w = in_quat.w;
    q.vec.x = in_quat.x;
    q.vec.y = in_quat.y;
    q.vec.z = in_quat.z;
    return q;
}

mat::Vec3 aiToVec3(aiVector3D v) {
    return mat::Vec3(v.x, v.y, v.z);
}
aiVector3D vec3ToAi(mat::Vec3 v) {
    return aiVector3D(v.x, v.y, v.z);
}