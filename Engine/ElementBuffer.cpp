#include "ElementBuffer.h"

CElementBuffer::CElementBuffer(CArray<uint32_t> *Indices)
{
    glGenBuffers(1, &Id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices->Num() * sizeof(uint32_t), Indices->begin(), GL_STATIC_DRAW);
}

void CElementBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
}

void CElementBuffer::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CElementBuffer::Delete()
{
    glDeleteBuffers(1, &Id);
}