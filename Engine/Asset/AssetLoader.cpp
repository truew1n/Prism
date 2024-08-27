#include "AssetLoader.hpp"

#include <sstream>

void CAssetLoader::Split(std::string *String, CArray<std::string> *Tokens, char Delimiter)
{
    std::stringstream StringStream(*String);
    std::string Token;
    while (std::getline(StringStream, Token, Delimiter)) {
        if (!Token.empty()) {
            Tokens->Add(Token);
        }
    }
}

CAsset CAssetLoader::LoadOBJ(const char *Filepath)
{
    CAsset NewAsset;


    return NewAsset;
}

CAsset CAssetLoader::LoadFBX(const char *Filepath)
{
    CAsset NewAsset;


    return NewAsset;
}

CAsset CAssetLoader::LoadGLTF(const char *Filepath)
{
    CAsset NewAsset;


    return NewAsset;
}