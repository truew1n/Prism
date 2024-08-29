#ifndef PE_RENDER_OBJECT_HPP
#define PE_RENDER_OBJECT_HPP

#include <stdint.h>

class RenderObject {
protected:
    uint32_t Id;
public:
    RenderObject() : Id(0) {}
    uint32_t GetId() const;
};

#endif