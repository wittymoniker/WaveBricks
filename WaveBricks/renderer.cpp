#include "renderer.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "shader.h"


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{


    //shader.Bind();
    //va.Bind();
    //ib.Bind();


    glDrawElements(GL_TRIANGLES, ib.getCount(),GL_UNSIGNED_INT, nullptr);

}
void Renderer::Clear()const{
    glClear(GL_COLOR_BUFFER_BIT );
}


