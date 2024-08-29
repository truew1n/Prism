#include "AssetLoader.hpp"


CAsset CAssetLoader::Load(const char *Filepath)
{
    Assimp::Importer Importer;
    const aiScene* AssimpScene = Importer.ReadFile(Filepath,
        aiProcess_Triangulate | aiProcess_JoinIdenticalVertices
    );

    CAsset Asset;

    if (!AssimpScene) {
        std::cerr << Importer.GetErrorString() << std::endl;
        return Asset;
    }

    return Asset;
}