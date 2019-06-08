#include "vertexbuffer.h"
#include "renderer.h"
#include<GL/glew.h>
VertexBuffer::VertexBuffer(const void* data, unsigned int Size)
{
    glGenBuffers(1,&m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, Size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}
void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}
void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
