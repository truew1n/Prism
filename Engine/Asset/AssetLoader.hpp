#ifndef PE_ASSET_LOADER_HPP
#define PE_ASSET_LOADER_HPP

#include "Asset.hpp"

class CAssetLoader {
// OBJ
private:
    void Split(std::string *String, CArray<std::string> *Tokens, char Delimiter);
public:
    static CAsset LoadOBJ(const char *Filepath);

// FBX
private:
    //
public:
    static CAsset LoadFBX(const char *Filepath);

// GLTF
private:
    //
public:
    static CAsset LoadGLTF(const char *Filepath);
};

#endif