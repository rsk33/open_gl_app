#pragma once

#include <string>

#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture
{
    public:
        Texture();
        Texture(const std::string& fileLocation);

        void LoadTexture();
        void UseTexture();
        void ClearTexture();

        ~Texture();

    private:
        GLuint mTextureID;
        int mWidth;
        int mHeight;
        int mBitDepth;
        std::string mFileLocation;
};
