#ifndef TEXTURE_HEADER_INCLUDED
#define TEXTURE_HEADER_INCLUDED

#include <gl/gl.h>
#include <map>
#include <string>
#include <windows.h>
#include <gdiplus.h>

class Texture
{
    private:
        Gdiplus::Bitmap* bitmap;
        std::map<int, GLuint> contexts;
        GLuint generateTextureForWindow(int windowid);
	public:
	    Texture(const std::string &filename);
	    ~Texture();
		GLuint getOpenGLTextureName(int windowid) const;
		void storeOpenGLTextureName(int windowid);
		unsigned int getWidth() const;
        unsigned int getHeight() const;
        static void init();
};

#endif
