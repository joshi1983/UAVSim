#include "Texture.hpp"
#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <gdiplus.h>
#include <fstream>
using namespace std;

void Texture::init()
{
    ULONG_PTR token;
	Gdiplus::GdiplusStartupInput gsi = { 0 };

	gsi.GdiplusVersion = 1;
	Gdiplus::GdiplusStartup(&token, &gsi, nullptr);
}

Texture::Texture(const string & filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "File not found: " << filename << endl;
        throw exception();
    }
    Gdiplus::Bitmap gpBitmap(wstring(filename.begin(), filename.end()).c_str());
    if (gpBitmap.GetWidth() == 0 || gpBitmap.GetHeight() == 0)
    {
        cerr << "Unable to load " << filename << ". Did you forget to call Texture::init()?" << endl;
        throw exception();
    }
    bitmap = gpBitmap.Clone( 0, 0, gpBitmap.GetWidth(), gpBitmap.GetHeight(), PixelFormat24bppRGB);
}

Texture::~Texture()
{
    for (map<int, GLuint>::iterator it=contexts.begin();it!=contexts.end();it++)
    {
        glDeleteTextures( 1, &it->second );
    }
    if (bitmap != nullptr)
        delete bitmap;
}

void Texture::storeOpenGLTextureName(int windowid)
{
    if (contexts.find(windowid) != contexts.end())
        return; // nothing to do.  Already stored.
    GLuint result = generateTextureForWindow(windowid);
    contexts[windowid] = result;
}

GLuint Texture::getOpenGLTextureName(int windowid) const
{
    return contexts.at(windowid);
}

unsigned int Texture::getWidth() const
{
  return bitmap->GetWidth();
}

unsigned int Texture::getHeight() const
{
  return bitmap->GetHeight();
}


GLuint Texture::generateTextureForWindow(int windowid)
{
    GLuint  openGLName=0;
    glutSetWindow(windowid);

    // allocate a texture name
    glGenTextures( 1, &openGLName);
    // select our current texture
    glBindTexture( GL_TEXTURE_2D, openGLName);

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest MIP map
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first MIP map
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int byteCount = 3;
    int widthStep = getWidth() * byteCount;

    if (widthStep%4 != 0)
        widthStep = (1+widthStep/4)*4;
    uint8_t* data = new uint8_t[widthStep*getHeight()];
    if (data==NULL)
    {
        cerr << "Texture::init unable to allocate required memory."<<endl;
        return -1;
    }
    for (unsigned int y=0;y<getHeight();y++)
    {
        for (unsigned int x=0;x<getWidth();x++)
        {
            Gdiplus::Color c;
            bitmap->GetPixel(x,y, &c);

            int index=(x*byteCount+y*widthStep);
            data[index]=c.GetRed();
            data[index+1]=c.GetGreen();
            data[index+2]=c.GetBlue();
        }
    }
    // build our texture MIP maps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, getWidth(), getHeight(), GL_RGB, GL_UNSIGNED_BYTE, data);
    delete [] data;
    return openGLName;
}
