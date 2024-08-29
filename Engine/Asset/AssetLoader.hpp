#ifndef PE_ASSET_LOADER_HPP
#define PE_ASSET_LOADER_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Asset.hpp"

class CAssetLoader {
    static CAsset Load(const char *Filepath);
};

#endif