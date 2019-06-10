#include"shader.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "renderer.h"
#include<iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

Shader::Shader(const std::string& filepath)
    :m_Filepath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader("shade.shader");
    m_RendererID= CreateShader(source.VertexSource, source.FragmentSource);
}
Shader::~Shader(){
    glDeleteProgram(m_RendererID);
}



ShaderProgramSource Shader::ParseShader(const std::string& filepath){
    std::ifstream stream(filepath);

    enum class ShaderType{
        NONE=-1,VERTEX=0,FRAGMENT=1
    };

    std::string line;

    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)){
        if(line.find("#shader")!=std::string::npos){
            if(line.find("vertex")!= std::string::npos){
                type= ShaderType::VERTEX;
            }else if (line.find("fragment")!= std::string::npos){
                type=ShaderType::FRAGMENT;
            }
        }else{
            ss[(int) type] << line << '\n';
        }
    }

    return{ ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type,const std::string& source){
    unsigned int id=glCreateShader(type);
    const char* src=source.c_str();
    glShaderSource(id, 1,&src,nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS,&result );
    if(result==GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char infoLog[length];
        glGetShaderInfoLog(id, length, &length, &infoLog[0]);
        glDeleteShader(id);
        std::cout<<"Shader compile failed: "<<infoLog<<std::endl;
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program= glCreateProgram();
    unsigned int vs=CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs=CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}
void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(getUniformLocation(name), v0,v1,v2,v3);
}

unsigned int Shader::getUniformLocation(const std::string& name)
{
    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) return m_UniformLocationCache[name];
    unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
    if(location ==-1){
        std::cout<<"\nuni doesn't exist\n";
    }else
    m_UniformLocationCache[name]=location;
    return location;
}
