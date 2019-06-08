#include <iostream>
#include<GL/glew.h>
#include "renderer.h"
#define ASSERT(x) if(!(x)) raise(SIGINT);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
void GLClearError()
{
    while(glGetError()!=GL_NO_ERROR);
}
bool GLLogCall(const char* Function, const char* file, int line)
{
    while (GLenum error= glGetError()){
        std::cout <<"\nOpenGL Error:"<<error<<Function<<file<<line;
        return false;
    }
    return true;
}
