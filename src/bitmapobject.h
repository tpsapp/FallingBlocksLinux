// SW Falling Blocks
// bitmapobject.h

#ifndef BITMAPOBJECT_H
#define BITMAPOBJECT_H
#pragma once

#include <SDL2/SDL.h>
#include <string>

class BitMapObject
{
private:
	SDL_Texture *texture;
	SDL_Renderer *renderer;
	int iWidth;
	int iHeight;

public:
	BitMapObject();
	~BitMapObject();
	// load a BMP file into a texture
	void Load(SDL_Renderer *renderer, const std::string &filename);
	// create an empty texture (render target)
	void Create(SDL_Renderer *renderer, int width, int height);
	void Destroy();
	int GetWidth();
	int GetHeight();
	SDL_Texture *GetTexture();
};

#endif
