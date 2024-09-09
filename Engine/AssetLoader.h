#ifndef PE_ASSET_LOADER_H
#define PE_ASSET_LOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Asset.h"

#define LOG_ASSET_LOADING

class CAssetLoader {
private:
    static glm::vec3 Vec3AssimpGLM(aiVector3D Vector3D);
public:
    static CAsset *LoadStatic(const char *Filepath);
};

#endif