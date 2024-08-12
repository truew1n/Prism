#ifndef PE_ELEMENT_BUFFER_HPP
#define PE_ELEMENT_BUFFER_HPP

#include <GL/glew.h>
#include "Array.hpp"

class CElementBuffer {
public:
    uint32_t Id;

    CElementBuffer(CArray<uint32_t> &Indices);

    void Bind();
    void Unbind();
    void Delete();
};

#endif