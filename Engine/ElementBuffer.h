#ifndef PE_ELEMENT_BUFFER_H
#define PE_ELEMENT_BUFFER_H

#include <GL/glew.h>
#include "Array.h"
#include "RenderObject.h"

class CElementBuffer : public CRenderObject {
public:
    CElementBuffer(CArray<uint32_t> *Indices);

    void Bind();
    void Unbind();
    void Delete();
};

#endif