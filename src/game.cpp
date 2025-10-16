// SW Falling Blocks
// game.cpp

#include "game.h"
#include <stdexcept>
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
	Done();
}

void Game::Cheat()
{
	cheat = !cheat;
}

int Game::CollisionTest(int nx, int ny)
{
	int newx = sPiece.x + nx;
	int newy = sPiece.y + ny;
	int x, y;

	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 4; y++)
		{
			if (sPiece.size[x][y] != TILENODRAW)
			{
				if (newx + x < 0 || newx + x > MAPWIDTH - 1 || newy + y < 0 || newy + y > MAPHEIGHT - 1)
				{
					return 1;
				}
			}
		}
	}

	for (x = 0; x < MAPWIDTH; x++)
	{
		for (y = 0; y < MAPHEIGHT; y++)
		{
			if (x >= newx && x < newx + 4)
			{
				if (y >= newy && y < newy + 4)
				{
					if (Map[x][y] != TILEBLACK)
					{
						if (sPiece.size[x - newx][y - newy] != TILENODRAW)
						{
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

void Game::Debug()
{
	debug = !debug;
}

void Game::DecLevel()
{
	if (level > 1)
	{
		level--;
	}
}

void Game::DecRows()
{
	if (rows > 0)
	{
		rows--;
	}
}

void Game::Done()
{
	bmoMap.Destroy();
	bmoBlocks.Destroy();
	bmoScore.Destroy();
	bmoLetters.Destroy();
}

void Game::DrawLevel()
{
	int tmpLevel = level;
	int x;

	Blit(bmoMap, 11 * TILESIZE, 25 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEL * TILESIZE, 0);
	Blit(bmoMap, 12 * TILESIZE, 25 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEE * TILESIZE, 0);
	Blit(bmoMap, 13 * TILESIZE, 25 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEV * TILESIZE, 0);
	Blit(bmoMap, 14 * TILESIZE, 25 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEE * TILESIZE, 0);
	Blit(bmoMap, 15 * TILESIZE, 25 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEL * TILESIZE, 0);

	for (x = 6; x > 0; x--)
	{
		int temp = tmpLevel % 10;
		Blit(bmoMap, (x + 10) * TILESIZE, 26 * TILESIZE, TILESIZE, TILESIZE, bmoScore, temp * TILESIZE, 0);
		tmpLevel = tmpLevel / 10;
		if (tmpLevel <= 0)
		{
			break;
		}
	}
}

void Game::DrawMap()
{
	int xmy, ymx;

	for (xmy = MAPWIDTH; xmy < MAPWIDTH + GREY; xmy++)
	{
		for (ymx = 0; ymx < MAPHEIGHT; ymx++)
		{
			DrawTile(xmy, ymx, TILEGREY);
		}
	}

	for (xmy = 0; xmy < 4; xmy++)
	{
		for (ymx = 0; ymx < 4; ymx++)
		{
			if (sPrePiece.size[xmy][ymx] != TILENODRAW)
			{
				DrawTile(sPrePiece.x + xmy, sPrePiece.y + ymx, sPrePiece.size[xmy][ymx]);
			}
		}
	}

	for (xmy = 0; xmy < MAPWIDTH; xmy++)
	{
		for (ymx = 0; ymx < MAPHEIGHT; ymx++)
		{
			DrawTile(xmy, ymx, Map[xmy][ymx]);
		}
	}

	for (xmy = 0; xmy < 4; xmy++)
	{
		for (ymx = 0; ymx < 4; ymx++)
		{
			if (sPiece.size[xmy][ymx] != TILENODRAW)
			{
				DrawTile(sPiece.x + xmy, sPiece.y + ymx, sPiece.size[xmy][ymx]);
			}
		}
	}

	// with SDL we render the map texture each frame; no need to invalidate a window

	DrawRows();
	DrawLevel();
	DrawScore();
	DrawStatus();
}

void Game::DrawRows()
{
	int tmpRows = rows;
	int x;

	Blit(bmoMap, 11 * TILESIZE, 23 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILER * TILESIZE, 0);
	Blit(bmoMap, 12 * TILESIZE, 23 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEO * TILESIZE, 0);
	Blit(bmoMap, 13 * TILESIZE, 23 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEW * TILESIZE, 0);
	Blit(bmoMap, 14 * TILESIZE, 23 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILES * TILESIZE, 0);

	for (x = 6; x > 0; x--)
	{
		int temp = tmpRows % 10;
		Blit(bmoMap, (x + 10) * TILESIZE, 24 * TILESIZE, TILESIZE, TILESIZE, bmoScore, temp * TILESIZE, 0);
		tmpRows = tmpRows / 10;
		if (tmpRows <= 0)
		{
			break;
		}
	}
}

void Game::DrawScore()
{
	int tmpScore = score;
	int x;

	Blit(bmoMap, 11 * TILESIZE, 27 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILES * TILESIZE, 0);
	Blit(bmoMap, 12 * TILESIZE, 27 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEC * TILESIZE, 0);
	Blit(bmoMap, 13 * TILESIZE, 27 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEO * TILESIZE, 0);
	Blit(bmoMap, 14 * TILESIZE, 27 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILER * TILESIZE, 0);
	Blit(bmoMap, 15 * TILESIZE, 27 * TILESIZE, TILESIZE, TILESIZE, bmoLetters, TILEE * TILESIZE, 0);

	for (x = 6; x > 0; x--)
	{
		int temp = tmpScore % 10;
		Blit(bmoMap, (x + 10) * TILESIZE, 28 * TILESIZE, TILESIZE, TILESIZE, bmoScore, temp * TILESIZE, 0);
		tmpScore = tmpScore / 10;
		if (tmpScore <= 0)
		{
			break;
		}
	}
}

void Game::DrawStatus()
{
	int tile;
	if (cheat)
	{
		tile = TILEORANGE;
	}
	else
	{
		tile = TILEGREY;
	}

	Blit(bmoMap, 16 * TILESIZE, 0, TILESIZE, TILESIZE, bmoBlocks, tile * TILESIZE, 0);

	if (debug)
	{
		tile = TILERED;
	}
	else
	{
		tile = TILEGREY;
	}

	Blit(bmoMap, 17 * TILESIZE, 0, TILESIZE, TILESIZE, bmoBlocks, tile * TILESIZE, 0);
}

void Game::DrawTile(int x, int y, int tile)
{
	Blit(bmoMap, x * TILESIZE, y * TILESIZE, TILESIZE, TILESIZE, bmoBlocks, tile * TILESIZE, TILESIZE);
	Blit(bmoMap, x * TILESIZE, y * TILESIZE, TILESIZE, TILESIZE, bmoBlocks, tile * TILESIZE, 0);
}

// Shows a native SDL message box for Game Over prompt.
// Returns true if user selects Yes, false for No.
bool Game::GameOver()
{
	SDL_MessageBoxButtonData buttons[] = {
		{SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes"},
		{SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "No"}};
	SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION,
		hWndMain,
		"Game Over",
		"Play again?",
		2,
		buttons,
		NULL};
	int buttonid = 0;
	SDL_ShowMessageBox(&messageboxdata, &buttonid);
	return buttonid == 1;
}

bool Game::GetCheat()
{
	return cheat;
}

bool Game::GetDebug()
{
	return debug;
}

int Game::GetMapHeight()
{
	return TILESIZE * MAPHEIGHT;
}

int Game::GetMapWidth()
{
	return TILESIZE * MAPWIDTH + TILESIZE * GREY;
}

bool Game::GetPaused()
{
	return paused;
}

bool Game::Init(SDL_Window *wnd, SDL_Renderer *renderer_)
{
	GAMESTARTED = false;
	cheat = false;
	debug = false;
	paused = false;

	if (!wnd || !renderer_)
		return false;

	hWndMain = wnd;
	renderer = renderer_;

	bmoMap.Create(renderer, GetMapWidth(), GetMapHeight());

	bmoBlocks.Load(renderer, "blocks.bmp");
	bmoScore.Load(renderer, "numbers.bmp");
	bmoLetters.Load(renderer, "letters.bmp");

	SDL_Texture *prev = SDL_GetRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, bmoMap.GetTexture());
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, prev);

	quitRequested = false;

	return true;
}

void Game::IncLevel()
{
	level++;
}

void Game::IncRows()
{
	rows++;
}

void Game::Loop()
{
	speed = level / 3;

	if (paused)
	{
		return;
	}

	if (speed > 5)
	{
		speed = 5;
	}

	if ((SDL_GetTicks() - start_time) > 1000)
	{
		if (cheat)
		{
			Move(0, 0);
		}
		else
		{
			if (speed == 0)
			{
				Move(0, 1);
			}
			else
			{
				Move(0, speed);
			}
		}

		start_time = SDL_GetTicks();
	}

	DrawMap();
}

void Game::Move(int x, int y)
{
	if (CollisionTest(x, y))
	{
		if (y >= 1)
		{
			if (y > 1)
			{
				Move(x, y - 1);
			}
			else if (sPiece.y < 1)
			{
				if (GameOver())
				{
					NewGame();
				}
				else
				{
					quitRequested = true;
				}
			}
			else
			{
				int i, j;

				for (i = 0; i < 4; i++)
				{
					for (j = 0; j < 4; j++)
					{
						if (sPiece.size[i][j] != TILENODRAW)
						{
							Map[sPiece.x + i][sPiece.y + j] = sPiece.size[i][j];
						}
					}
				}

				for (j = 0; j < MAPHEIGHT; j++)
				{
					bool filled = true;

					for (i = 0; i < MAPWIDTH; i++)
					{
						if (Map[i][j] == TILEBLACK)
						{
							filled = false;
							fourrows = 0;
						}
					}

					if (filled)
					{
						RemoveRow(j);
					}
				}

				NewBlock(8);
			}
		}
	}
	else
	{
		sPiece.x += x;
		sPiece.y += y;
	}
}

void Game::NewBlock(int block)
{
	srand(SDL_GetTicks());

	sPrePiece.x = MAPWIDTH + GREY / 4;
	sPrePiece.y = GREY / 4;

	if (!GAMESTARTED)
	{
		GAMESTARTED = true;

		sPiece.x = MAPWIDTH / 2 - 2;
		sPiece.y = -1;

		SetBlock(&sPiece, rand() % 8);
		SetBlock(&sPrePiece, rand() % 8);
	}
	else
	{
		if (block > 7)
		{
			sPiece = sPrePiece;
			sPiece.x = MAPWIDTH / 2 - 2;
			sPiece.y = -1;

			SetBlock(&sPrePiece, rand() % 8);
		}
		else
		{
			SetBlock(&sPiece, block);
		}
	}
}

void Game::NewGame()
{
	score = 0;
	level = 1;
	rows = 0;
	fourrows = 0;
	speed = 0;

	start_time = SDL_GetTicks();
	GAMESTARTED = false;

	for (int x = 0; x < MAPWIDTH; x++)
	{
		for (int y = 0; y < MAPHEIGHT + 1; y++)
		{
			if (y == MAPHEIGHT)
			{
				Map[x][y] = TILEGREY;
			}
			else
			{
				Map[x][y] = TILEBLACK;
			}
		}
	}

	NewBlock(8);
}

void Game::Pause()
{
	paused = !paused;
}

void Game::RemoveRow(int row)
{
	int x, y;
	int counter = 0;

	for (x = 0; x < MAPWIDTH; x++)
	{
		for (y = row; y > 0; y--)
		{
			Map[x][y] = Map[x][y - 1];
		}
	}

	score++;
	rows++;
	fourrows++;

	if (rows > 10 * level)
	{
		level++;
		rows = 0;
	}

	if (fourrows == 4)
	{
		score++;
		fourrows = 0;
	}
}

void Game::RotateBlock(bool direction)
{
	int i, j, temp[4][4];

	if (direction)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				temp[3 - j][i] = sPiece.size[i][j];
			}
		}
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				temp[j][3 - i] = sPiece.size[i][j];
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (temp[i][j] != TILENODRAW)
			{
				if (sPiece.x + i < 0 || sPiece.x + i > MAPWIDTH - 1 || sPiece.y + j < 0 || sPiece.y + j > MAPHEIGHT - 1)
				{
					return;
				}
			}
		}
	}

	for (int x = 0; x < MAPWIDTH; x++)
	{
		for (int y = 0; y < MAPHEIGHT; y++)
		{
			if (x >= sPiece.x && x < sPiece.x + 4)
			{
				if (y >= sPiece.y && y < sPiece.y + 4)
				{
					if (Map[x][y] != TILEBLACK)
					{
						if (temp[x - sPiece.x][y - sPiece.y] != TILENODRAW)
						{
							return;
						}
					}
				}
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			sPiece.size[i][j] = temp[i][j];
		}
	}
}

void Game::SetBlock(Piece *piece, int block)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			piece->size[i][j] = TILENODRAW;
		}
	}

	switch (block)
	{
	case 0:
	{
		piece->size[1][0] = TILERED;
		piece->size[1][1] = TILERED;
		piece->size[1][2] = TILERED;
		piece->size[1][3] = TILERED;
		if (block > 7)
			piece->y = 0;
	}
	break;
	case 1:
	{
		piece->size[1][1] = TILEBLUE;
		piece->size[1][2] = TILEBLUE;
		piece->size[2][1] = TILEBLUE;
		piece->size[2][2] = TILEBLUE;
	}
	break;
	case 2:
	{
		piece->size[1][1] = TILESTEEL;
		piece->size[0][2] = TILESTEEL;
		piece->size[1][2] = TILESTEEL;
		piece->size[2][2] = TILESTEEL;
	}
	break;
	case 3:
	{
		piece->size[0][1] = TILEYELLOW;
		piece->size[1][1] = TILEYELLOW;
		piece->size[1][2] = TILEYELLOW;
		piece->size[2][2] = TILEYELLOW;
	}
	break;
	case 4:
	{
		piece->size[2][1] = TILEGREEN;
		piece->size[1][1] = TILEGREEN;
		piece->size[1][2] = TILEGREEN;
		piece->size[0][2] = TILEGREEN;
	}
	break;
	case 5:
	{
		piece->size[1][1] = TILEWHITE;
		piece->size[2][1] = TILEWHITE;
		piece->size[2][2] = TILEWHITE;
		piece->size[2][3] = TILEWHITE;
	}
	break;
	case 6:
	{
		piece->size[2][1] = TILEPURPLE;
		piece->size[1][1] = TILEPURPLE;
		piece->size[1][2] = TILEPURPLE;
		piece->size[1][3] = TILEPURPLE;
	}
	break;
	case 7:
	{
		piece->size[1][1] = TILEORANGE;
		piece->size[2][0] = TILEORANGE;
		piece->size[2][1] = TILEORANGE;
		piece->size[2][2] = TILEORANGE;
		piece->size[3][1] = TILEORANGE;
	}
	break;
	}
}

void Game::Blit(BitMapObject &dest, int dx, int dy, int w, int h, BitMapObject &src, int sx, int sy)
{
	if (!renderer)
		return;

	SDL_Texture *prevTarget = SDL_GetRenderTarget(renderer);

	SDL_SetRenderTarget(renderer, dest.GetTexture());

	SDL_Rect srcRect = {sx, sy, w, h};
	SDL_Rect dstRect = {dx, dy, w, h};

	SDL_RenderCopy(renderer, src.GetTexture(), &srcRect, &dstRect);

	SDL_SetRenderTarget(renderer, prevTarget);
}

bool Game::ShouldQuit()
{
	return quitRequested;
}
