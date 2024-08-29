#ifndef PE_ASSET_HPP
#define PE_ASSET_HPP

#include "Mesh.hpp"
#include "Material.hpp"
#include "Pair.hpp"
#include "Array.hpp"

class CAsset {
public:
    CArray<CPair<CMesh *, CMaterial *>> AssetData;
};

#endif