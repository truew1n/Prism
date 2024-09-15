#include "AssetLoader.h"
#include "CuboidBoundingVolume.h"

glm::vec3 CAssetLoader::ToGLMVec3(aiVector3D Vector3D)
{
    return glm::vec3(
        Vector3D.x,
        Vector3D.y,
        Vector3D.z
    );
}

CAsset *CAssetLoader::LoadStatic(const char *Filepath)
{
    Assimp::Importer Importer;
    const aiScene *AssimpScene = Importer.ReadFile(Filepath,
        aiProcess_GenNormals |
        aiProcess_Triangulate |
        aiProcess_GenBoundingBoxes |
        aiProcess_SortByPType
    );
    
    std::string FullPath(Filepath);
    size_t LastBackslash = FullPath.find_last_of('\\') + 1;
    std::string DirectoryPath = FullPath.substr(0, LastBackslash);

    CAsset *Asset = new CAsset();

    if (!AssimpScene) {
        std::cerr << Importer.GetErrorString() << std::endl;
        return Asset;
    }

#ifdef LOG_ASSET_LOADING
    std::cout << "Model Load Preparing: " << Filepath << std::endl;
#endif

    const aiVector3D Zero3D = aiVector3D(0.0f, 0.0f, 0.0f);

    uint32_t MeshCount = AssimpScene->mNumMeshes;
    uint32_t MaterialCount = AssimpScene->mNumMaterials;

#ifdef LOG_ASSET_LOADING
    std::cout << "Mesh Count: " << MeshCount << std::endl;
    std::cout << "Material Count: " << MaterialCount << std::endl;
#endif

    for (uint32_t I = 0; I < MeshCount; ++I) {
        aiMesh *AssimpMesh = AssimpScene->mMeshes[I];

        assert(AssimpMesh->HasPositions() == true);
        assert(AssimpMesh->HasNormals() == true);
        assert(AssimpMesh->HasTextureCoords(0) == true);
        assert(AssimpMesh->HasFaces() == true);

        int32_t VertexCount = AssimpMesh->mNumVertices;

        CArray<SVertex> *Vertices = new CArray<SVertex>(VertexCount);
        for (int32_t V = 0; V < VertexCount; ++V) {
            glm::vec3 Location = ToGLMVec3(AssimpMesh->mVertices[V]);
            glm::vec3 Normal = ToGLMVec3(AssimpMesh->mNormals[V]);
            glm::vec2 UV = ToGLMVec3(AssimpMesh->HasTextureCoords(0) ? AssimpMesh->mTextureCoords[0][V] : Zero3D);
            Vertices->Set(SVertex(
                Location, Normal, UV
            ), V);
        }

        assert(AssimpMesh->mFaces->mNumIndices == 3);
        uint32_t IndicesCount = AssimpMesh->mNumFaces * AssimpMesh->mFaces->mNumIndices;
        uint32_t IndicesCounter = 0;
        CArray<uint32_t> *Indices = new CArray<uint32_t>(IndicesCount);
        for (uint32_t J = 0; J < AssimpMesh->mNumFaces; ++J) {
            aiFace &Face = AssimpMesh->mFaces[J];
            for (uint32_t K = 0; K < Face.mNumIndices; ++K) {
                Indices->Set(Face.mIndices[K], IndicesCounter);
                IndicesCounter++;
            }
        }

#ifdef LOG_ASSET_LOADING
        std::cout << "Vertex Count: " << VertexCount << std::endl;
        std::cout << "Index Count: " << IndicesCount << std::endl;

        glm::vec3 Min = ToGLMVec3(AssimpMesh->mAABB.mMin);
        glm::vec3 Max = ToGLMVec3(AssimpMesh->mAABB.mMax);

        std::cout << "AABB Minimum: " << Min.x << " " << Min.y << " " << Min.z << std::endl;
        std::cout << "AABB Maximum: " << Max.x << " " << Max.y << " " << Max.z << std::endl;
#endif
        
        CCuboidBoundingVolume *CuboidBoundingVolume = new CCuboidBoundingVolume(
            ToGLMVec3(AssimpMesh->mAABB.mMin),
            ToGLMVec3(AssimpMesh->mAABB.mMax)
        );

        CMesh *PrismMesh = new CMesh(Vertices, Indices, CuboidBoundingVolume);
        delete Vertices;
        delete Indices;

        CMaterial *PrismMaterial = new CMaterial();

        CShader *MaterialShader = PrismMaterial->GetShader();
        MaterialShader->Create();
        MaterialShader->Load("Assets\\Shaders\\Default.vert", EShaderType::Vertex);
        MaterialShader->Load("Assets\\Shaders\\Default.frag", EShaderType::Fragment);

        aiMaterial *AssimpMaterial = AssimpScene->mMaterials[AssimpMesh->mMaterialIndex];

        aiString Path;
        if (AssimpMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
            std::string TextureFullPath = DirectoryPath + Path.C_Str();
#ifdef LOG_ASSET_LOADING
            std::cout << "Texture: " << TextureFullPath << std::endl;
#endif
            PrismMaterial->AddTexture(new CTexture(TextureFullPath.c_str(), "UDiffuse", 0));
        }

        Asset->AssetData.Add(CPair<CMesh *, CMaterial *>(PrismMesh, PrismMaterial));
    }

#ifdef LOG_ASSET_LOADING
    std::cout << "Model Loaded: " << Filepath << std::endl;
#endif
    return Asset;
}