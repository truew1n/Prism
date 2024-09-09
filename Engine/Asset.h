#ifndef PE_ASSET_H
#define PE_ASSET_H

#include "Mesh.h"
#include "Material.h"
#include "Pair.h"
#include "Array.h"

class CAsset {
public:
    CArray<CPair<CMesh *, CMaterial *>> AssetData;
    CAsset();
    ~CAsset();
};

#endif