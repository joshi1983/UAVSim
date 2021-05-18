#ifndef SKY_HEADER_INCLUDED
#define SKY_HEADER_INCLUDED
#include "Texture.hpp"

class Sky
{
	private:
		Texture texture;
	public:
		Sky();
		void draw(int windowid, double cameraYaw, double cameraPitch);
};

#endif
