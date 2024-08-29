#include "AssetLoader.hpp"


glm::vec3 CAssetLoader::Vec3AssimpGLM(aiVector3D Vector3D)
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
    const aiScene* AssimpScene = Importer.ReadFile(
        Filepath,
        aiProcess_Triangulate | aiProcess_SortByPType
    );

    std::string FullPath(Filepath);
    size_t LastBackslash = FullPath.find_last_of('\\') + 1;
    std::string DirectoryPath = FullPath.substr(0, LastBackslash);

    CAsset *Asset = new CAsset();

    if (!AssimpScene) {
        std::cerr << Importer.GetErrorString() << std::endl;
        return Asset;
    }
    
    const aiVector3D Zero3D = aiVector3D(0.0f, 0.0f, 0.0f);

    uint32_t MeshCount = AssimpScene->mNumMeshes;
    uint32_t MaterialCount = AssimpScene->mNumMaterials;
    
    for(uint32_t I = 0; I < MeshCount; ++I) { 
        aiMesh *AssimpMesh = AssimpScene->mMeshes[I];

        int32_t VertexCount = AssimpMesh->mNumVertices;
        CArray<SVertex> *Vertices = new CArray<SVertex>(VertexCount);
        for(int32_t V = 0; V < VertexCount; ++V) {
            glm::vec3 Location = Vec3AssimpGLM(AssimpMesh->mVertices[V]);
            glm::vec3 Normal = Vec3AssimpGLM(AssimpMesh->mNormals[V]);
            glm::vec2 UV = Vec3AssimpGLM(AssimpMesh->HasTextureCoords(0) ? AssimpMesh->mTextureCoords[0][V] : Zero3D);
            Vertices->Set(SVertex(
                Location, Normal, UV
            ), V);
        }

        uint32_t IndicesCount = AssimpMesh->mNumFaces * AssimpMesh->mFaces->mNumIndices;
        uint32_t IndicesCounter = 0;
        CArray<uint32_t> *Indices = new CArray<uint32_t>(IndicesCount);
        for(uint32_t J = 0; J < AssimpMesh->mNumFaces; ++J) {
            aiFace& Face = AssimpMesh->mFaces[J];
            for(uint32_t K = 0; K < Face.mNumIndices; ++K) {
                Indices->Set(Face.mIndices[K], IndicesCounter);
                IndicesCounter++;
            }
        }
        
        CMesh *PrismMesh = new CMesh(Vertices, Indices);
        delete Vertices;
        delete Indices;
        
        CMaterial *PrismMaterial = new CMaterial();

        CShader *MaterialShader = PrismMaterial->GetShader();
        MaterialShader->Create();
        MaterialShader->Load("Engine\\Resource\\Default.vert", EShaderType::VERTEX);
        MaterialShader->Load("Engine\\Resource\\Default.frag", EShaderType::FRAGMENT);

        aiMaterial *AssimpMaterial = AssimpScene->mMaterials[AssimpMesh->mMaterialIndex];
        
        aiString Path;
        if(AssimpMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
            std::string TextureFullPath = DirectoryPath + Path.C_Str();
            std::cout << "Texture: " << TextureFullPath << std::endl;
            PrismMaterial->AddTexture(new CTexture(TextureFullPath.c_str(), "UDiffuse", 0));
        }

        Asset->AssetData.Add(CPair<CMesh *, CMaterial *>(PrismMesh, PrismMaterial));
    }

    std::cout << "Model: " << Filepath << std::endl;
    return Asset;
}