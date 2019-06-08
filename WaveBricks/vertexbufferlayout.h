#pragma once
#include <vector>
#include <GL/glew.h>
#include<iostream>
#include<string>
#include<typeinfo>
struct VertexBufferElement
{
    unsigned int Count;
    unsigned int type;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT:return 4;
            case GL_UNSIGNED_BYTE:return 1;
        }
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout()
        :m_Stride(0){}

    template<typename T>
    void Push(unsigned int Count)
    {
        std::cout << "Error: unsupported type " << typeid(T).name() << std::endl;
    }

    inline const std::vector<VertexBufferElement> GetElements() const& {return m_Elements;}
    inline unsigned int GetStride() const {return m_Stride;}

};
template<>
    inline void VertexBufferLayout::Push<float>(unsigned int Count)
    {
        m_Elements.push_back({GL_FLOAT, Count, GL_FALSE});
        m_Stride+=VertexBufferElement::GetSizeOfType(GL_FLOAT)*Count;
    }
template<>
    inline void VertexBufferLayout::Push<unsigned int>(unsigned int Count)
    {
        m_Elements.push_back({GL_UNSIGNED_INT, Count, GL_FALSE});
        m_Stride+=VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT)*Count;
    }
template<>
    inline void VertexBufferLayout::Push<unsigned char>(unsigned int Count)
    {
        m_Elements.push_back({GL_UNSIGNED_BYTE, Count, GL_TRUE});
        m_Stride+=VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE)*Count;
    }


