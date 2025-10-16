// SW Falling Blocks
// game.h

#ifndef GAME_H
#define GAME_H
#pragma once

#include <SDL2/SDL.h>
#include "bitmapobject.h"

class Game
{
private:
	typedef enum
	{
		TILENODRAW = -1,
		TILEBLACK = 0,
		TILEGREY,
		TILEBLUE,
		TILERED,
		TILEGREEN,
		TILEYELLOW,
		TILEWHITE,
		TILESTEEL,
		TILEPURPLE,
		TILEORANGE
	} Blocks;

	typedef enum
	{
		TILEL = 0,
		TILEE,
		TILEV,
		TILER,
		TILEO,
		TILEW,
		TILES,
		TILEC
	} Letters;

	static const int TILESIZE = 16;
	static const int MAPWIDTH = 10;
	static const int MAPHEIGHT = 30;
	static const int GREY = 8;

	struct Piece
	{
		int size[4][4];
		int x;
		int y;
	};

	Piece sPrePiece;
	Piece sPiece;

	Uint32 start_time;

	bool GAMESTARTED;
	bool cheat;
	bool debug;
	bool paused;

	BitMapObject bmoBlocks;
	BitMapObject bmoScore;
	BitMapObject bmoLetters;

	int Map[MAPWIDTH][MAPHEIGHT + 1];
	int score;
	int level;
	int rows;
	int fourrows;
	int speed;

	SDL_Window *hWndMain;
	SDL_Renderer *renderer;

	bool quitRequested;

public:
	BitMapObject bmoMap;

	// helper to blit between BitMapObjects
	void Blit(BitMapObject &dest, int dx, int dy, int w, int h, BitMapObject &src, int sx, int sy);

	Game();
	~Game();
	void Cheat();
	int CollisionTest(int x, int y);
	void Debug();
	void DecLevel();
	void DecRows();
	void Done();
	void DrawLevel();
	void DrawMap();
	void DrawRows();
	void DrawScore();
	void DrawStatus();
	void DrawTile(int x, int y, int tile);
	bool GameOver();
	bool GetCheat();
	bool GetDebug();
	int GetMapHeight();
	int GetMapWidth();
	bool GetPaused();
	void IncLevel();
	void IncRows();
	bool Init(SDL_Window *wnd, SDL_Renderer *renderer);
	void Loop();
	void Move(int x, int y);
	void NewBlock(int block);
	void NewGame();
	void Pause();
	void RemoveRow(int row);
	void RotateBlock(bool direction);
	void SetBlock(Piece *piece, int block);

	bool ShouldQuit();
};

#endif
