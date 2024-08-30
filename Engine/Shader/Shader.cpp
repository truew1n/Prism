#include "Shader.hpp"

uint32_t CShader::MatchShaderType(EShaderType Type)
{
    switch(Type) {
        case EShaderType::VERTEX:                       return GL_VERTEX_SHADER;
        case EShaderType::TESSELLATION_CONTROL:         return GL_TESS_CONTROL_SHADER;
        case EShaderType::TESSELLATION_EVALUATION:      return GL_TESS_EVALUATION_SHADER;
        case EShaderType::GEOMETRY:                     return GL_GEOMETRY_SHADER;
        case EShaderType::FRAGMENT:                     return GL_FRAGMENT_SHADER;
        case EShaderType::COMPUTE:                      return GL_COMPUTE_SHADER;
        default:                                        return GL_VERTEX_SHADER;
    }
}

const char *CShader::GLTypeToString(uint32_t GLType)
{
    switch(GLType) {
        case GL_VERTEX_SHADER:                          return "Vertex Shader";
        case GL_TESS_CONTROL_SHADER:                    return "Tessellation Control Shader";
        case GL_TESS_EVALUATION_SHADER:                 return "Tessellation Evaluation Shader";
        case GL_GEOMETRY_SHADER:                        return "Geometry Shader";
        case GL_FRAGMENT_SHADER:                        return "Fragment Shader";
        case GL_COMPUTE_SHADER:                         return "Compute Shader";
        default:                                        return "Unknown Shader Type";
    }
}

uint8_t CShader::Load(const char *Filepath, EShaderType Type)
{
    char *Content = read_file(Filepath);

    uint32_t ShaderId = Compile(Content, Type);

    if(!ShaderId) {
        free(Content);
        return 0;
    }

    glAttachShader(Id, ShaderId);
    glLinkProgram(Id);
    glValidateProgram(Id);

    glDeleteShader(ShaderId);

    free(Content);
    return 1;
}

uint32_t CShader::Compile(const char *Source, EShaderType Type)
{
    uint32_t GLType = MatchShaderType(Type);
    
    uint32_t ShaderId = glCreateShader(GLType);
    glShaderSource(ShaderId, 1, &Source, nullptr);
    glCompileShader(ShaderId);

    int32_t Result;
    glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &Result);
    if(!Result) {
        int32_t Length;
        glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &Length);
        char *Message = (char *) malloc(Length * sizeof(char));
        glGetShaderInfoLog(ShaderId, Length, &Length, Message);
        printf(
            "Failed to compile %s shader!\n%s\n",
            GLTypeToString(GLType),
            Message
        );
        free(Message);
        glDeleteShader(ShaderId);
        return 0;
    }
    
    return ShaderId;
}

void CShader::Create()
{
    Id = glCreateProgram();
}

void CShader::Activate()
{
    glUseProgram(Id);
}

void CShader::Deactivate()
{
    glUseProgram(0);
}

void CShader::Delete()
{
    glDeleteShader(Id);
}