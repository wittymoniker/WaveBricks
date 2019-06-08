#include<iostream>
#include<GL/glew.h>
#define ASSERT(x) if(!(x)) raise(SIGINT);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
void GLClearError();
bool GLLogCall(const char* Function, const char* file, int line);

class Renderer
{
private:
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
