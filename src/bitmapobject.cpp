// SW Falling Blocks
// bitmapobject.cpp

#include "bitmapobject.h"
#include <stdexcept>

BitMapObject::BitMapObject()
{
	texture = nullptr;
	renderer = nullptr;
	iWidth = 0;
	iHeight = 0;
}

BitMapObject::~BitMapObject()
{
	Destroy();
}

void BitMapObject::Load(SDL_Renderer *renderer_, const std::string &filename)
{
	Destroy();
	renderer = renderer_;
	SDL_Surface *surf = SDL_LoadBMP(filename.c_str());
	if (!surf)
	{
		throw std::runtime_error("Failed to load BMP: " + filename);
	}
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	iWidth = surf->w;
	iHeight = surf->h;
	SDL_FreeSurface(surf);
}

void BitMapObject::Create(SDL_Renderer *renderer_, int width, int height)
{
	Destroy();
	renderer = renderer_;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	if (!texture)
	{
		throw std::runtime_error("Failed to create texture");
	}
	iWidth = width;
	iHeight = height;
}

void BitMapObject::Destroy()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	renderer = nullptr;
	iWidth = 0;
	iHeight = 0;
}

int BitMapObject::GetWidth()
{
	return iWidth;
}

int BitMapObject::GetHeight()
{
	return iHeight;
}

SDL_Texture *BitMapObject::GetTexture()
{
	return texture;
}
