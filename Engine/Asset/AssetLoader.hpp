#ifndef PE_ASSET_LOADER_HPP
#define PE_ASSET_LOADER_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Asset.hpp"

class CAssetLoader {
private:
    static glm::vec3 Vec3AssimpGLM(aiVector3D Vector3D);
public:
    static CAsset *LoadStatic(const char *Filepath);
};

#endif