#pragma once

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(const void* data, unsigned int Count);
    ~IndexBuffer();
    void Bind() const;
    void Unbind() const;
    inline unsigned int getCount()const{return m_Count;}
};
