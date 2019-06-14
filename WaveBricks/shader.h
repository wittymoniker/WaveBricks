#pragma once
#include<string>
#include<iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <unordered_map>
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};


class Shader
{
private:

    std::string m_Filepath;
    std::string m_Filepath2;
    unsigned int m_RendererID;


    std::unordered_map<std::string, unsigned int>m_UniformLocationCache;

public:

    Shader(const std::string& filepath,const std::string& filepath2);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
    ShaderProgramSource ParseShader(const std::string& filepath,const std::string& filepath2);
    unsigned int CompileShader(unsigned int type,const std::string& source);
    unsigned int CreateShader(const std::string& Shader1, const std::string& Shader2);
    unsigned int getUniformLocation(const std::string& name);


};
