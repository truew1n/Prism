#ifndef PE_SHADER_STORAGE_BUFFER_HPP
#define PE_SHADER_STORAGE_BUFFER_HPP

#include <GL/glew.h>
#include "Array.h"
#include "RenderObject.h"

template<typename T>
class CShaderStorageBuffer : public CRenderObject {
private:
    uint32_t MBinding;

    void Initialize(CArray<T> *Data, uint32_t Binding = 1)
    {
        glGenBuffers(1, &Id);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, Id);

        size_t DataSize = Data.GetSize() * sizeof(T);
        glBufferData(GL_SHADER_STORAGE_BUFFER, DataSize, Data->begin(), GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, Binding, Id);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        MBinding = Binding;
    }
public:
    CShaderStorageBuffer(CArray<T> *Data)
    {
        Initialize(Data, 1);
    }

    CShaderStorageBuffer(CArray<T> *Data, uint32_t Binding)
    {
        if (Binding <= 0) {
            std::cerr << "ShaderStorageBuffer: Binding smaller or equal to zero. Setting binding to 1!" << std::endl;
            Binding = 1;
        }
        Initialize(Data, Binding);
    }

    void Bind()
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, MBinding, Id);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, Id);
    }

    void Unbind()
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void Delete()
    {
        glDeleteBuffers(1, &Id);
    }

    uint32_t GetBinding() const
    {
        return MBinding;

    }
    void SetBinding(uint32_t Binding)
    {
        MBinding = Binding;
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, MBinding, Id);
    }
};

#endif