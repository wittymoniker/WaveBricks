#include "vertexarray.h"
#include "vertexbufferlayout.h"
#include "renderer.h"
VertexArray::VertexArray(){
    glGenVertexArrays(1,&m_RendererID);
    glBindVertexArray(m_RendererID);
}
VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &m_RendererID);
}
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){
    Bind();
    vb.Bind();
    const auto&elements = layout.GetElements();
    unsigned int offset=0;
    for (unsigned int i=0; i<elements.size(); i++){
        const auto& element = elements[i];
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(i,element.Count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
        offset+= element.Count*VertexBufferElement::GetSizeOfType(element.type);
    }

}
void VertexArray::Bind() const{
    glBindVertexArray(m_RendererID);
}
void VertexArray::Unbind() const{
    glBindVertexArray(0);
}
