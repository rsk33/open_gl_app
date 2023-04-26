#include "texture.h"
#include <iostream>

Texture::Texture() : mTextureID{0}, mWidth{0}, mHeight{0}, mBitDepth{0}
{
};

Texture::Texture(const std::string& fileLocation)
    : mTextureID{0}
    , mWidth{0}
    , mHeight{0}
    , mBitDepth{0}
    , mFileLocation{fileLocation}
{
};

void Texture::LoadTexture()
{
    unsigned char* texData = stbi_load(mFileLocation.c_str(), &mWidth, &mHeight, &mBitDepth, 0);
    if(!texData)
    {
        std::cout << "Failed to find: " << mFileLocation << '\n';
    }
    else
    {
        glGenTextures(1, &mTextureID);
        glBindTexture(GL_TEXTURE_2D, mTextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(texData);
    }
}

void Texture::UseTexture()
{
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture::ClearTexture()
{
    glDeleteTextures(1, &mTextureID);
    mTextureID = 0;
    mWidth = 0;
    mHeight = 0;
    mBitDepth = 0;
    mFileLocation.erase();
}

Texture::~Texture()
{
    ClearTexture();
}
