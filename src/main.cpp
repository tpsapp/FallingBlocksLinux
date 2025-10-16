// SW Falling Blocks
// main.cpp (SDL2 port)

#include "main.h"
#include <SDL2/SDL.h>
#include <iostream>

static bool SaveTextureToBMP(SDL_Renderer *renderer, SDL_Texture *tex, const char *filename)
{
	if (!renderer || !tex)
		return false;

	// get texture info
	Uint32 format;
	int access, w, h;
	if (SDL_QueryTexture(tex, &format, &access, &w, &h) != 0)
		return false;

	// create target surface
	SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format);
	if (!surf)
		return false;

	// set render target to texture and read pixels
	SDL_Texture *prev = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, tex);

	if (SDL_RenderReadPixels(renderer, nullptr, format, surf->pixels, surf->pitch) != 0)
	{
		SDL_SetRenderTarget(renderer, prev);
		SDL_FreeSurface(surf);
		return false;
	}

	SDL_SetRenderTarget(renderer, prev);

	if (SDL_SaveBMP(surf, filename) != 0)
	{
		SDL_FreeSurface(surf);
		return false;
	}

	SDL_FreeSurface(surf);
	return true;
}

int main(int argc, char **argv)
{
	bool screenshotMode = false;
	for (int i = 1; i < argc; ++i)
	{
		if (std::string(argv[i]) == "--screenshot")
			screenshotMode = true;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	Uint32 windowFlags = SDL_WINDOW_SHOWN;
	if (screenshotMode)
	{
		// when running offscreen, the caller should set SDL_VIDEODRIVER=offscreen in env
		windowFlags = SDL_WINDOW_HIDDEN;
	}

	SDL_Window *window = SDL_CreateWindow(WINDOWTITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
										  gFB.GetMapWidth(), gFB.GetMapHeight(), windowFlags);
	if (!window)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (!renderer)
	{
		SDL_DestroyWindow(window);
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	try
	{
		if (!gFB.Init(window, renderer))
		{
			throw std::runtime_error("Game init failed");
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Init error: " << e.what() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	gFB.NewGame();

	bool running = true;
	SDL_Event ev;

	int frames = 0;
	while (running)
	{
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
			{
				running = false;
			}
			else if (ev.type == SDL_KEYDOWN)
			{
				SDL_Keycode k = ev.key.keysym.sym;
				if (k == SDLK_ESCAPE)
				{
					running = false;
				}
				else if (k == SDLK_PAUSE)
				{
					gFB.Pause();
				}
				else if (gFB.GetPaused())
				{
					// ignore other keys while paused
				}
				else if (k == SDLK_DOWN)
				{
					gFB.Move(0, 1);
				}
				else if (k == SDLK_UP)
				{
					gFB.RotateBlock(true);
				}
				else if (k == SDLK_SPACE)
				{
					gFB.RotateBlock(false);
				}
				else if (k == SDLK_LEFT)
				{
					gFB.Move(-1, 0);
				}
				else if (k == SDLK_RIGHT)
				{
					gFB.Move(1, 0);
				}
				else if (k == SDLK_TAB)
				{
					gFB.Cheat();
				}
				else if (k == SDLK_RSHIFT || k == SDLK_LSHIFT)
				{
					if (gFB.GetCheat() || gFB.GetDebug())
					{
						gFB.Move(0, -1);
					}
				}
				else if (k == SDLK_F1)
				{
					if (gFB.GetCheat() || gFB.GetDebug())
						gFB.NewBlock(8);
				}
				else if (k == SDLK_F12)
				{
					gFB.Debug();
				}
				else if (k >= SDLK_F2 && k <= SDLK_F9)
				{
					int idx = (k - SDLK_F2);
					if (gFB.GetDebug())
						gFB.NewBlock(idx);
				}
				else if (k == SDLK_PAGEUP)
				{
					if (gFB.GetDebug())
						gFB.IncLevel();
				}
				else if (k == SDLK_PAGEDOWN)
				{
					if (gFB.GetDebug())
						gFB.DecLevel();
				}
				else if (k == SDLK_HOME)
				{
					if (gFB.GetDebug())
						gFB.IncRows();
				}
				else if (k == SDLK_END)
				{
					if (gFB.GetDebug())
						gFB.DecRows();
				}
			}
		}

		gFB.Loop();

		// Render bmoMap texture to the window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_Texture *tex = gFB.bmoMap.GetTexture();
		if (tex)
		{
			SDL_Rect dst = {0, 0, gFB.GetMapWidth(), gFB.GetMapHeight()};
			SDL_RenderCopy(renderer, tex, nullptr, &dst);
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(16); // ~60fps
		frames++;

		// exit if game requested quit (e.g., user selected No on GameOver)
		if (gFB.ShouldQuit())
		{
			running = false;
		}

		// if screenshot mode, capture after a few frames then exit
		if (screenshotMode && frames >= 2)
		{
			if (gFB.bmoMap.GetTexture())
			{
				if (SaveTextureToBMP(renderer, gFB.bmoMap.GetTexture(), "screenshot.bmp"))
				{
					std::cout << "Wrote screenshot.bmp\n";
				}
				else
				{
					std::cerr << "Failed to write screenshot.bmp\n";
				}
			}
			running = false;
		}
	}

	gFB.Done();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
