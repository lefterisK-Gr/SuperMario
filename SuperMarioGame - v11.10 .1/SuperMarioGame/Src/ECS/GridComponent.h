#pragma once

#include "Components.h"

#define GRID_EMPTY_TILE 0x0000
#define GRID_SOLID_TILE 0x0001
#define GRID_ROWS 4
#define GRID_COLUMNS 4
#define GRID_ELEMENT_WIDTH 8
#define GRID_ELEMENT_HEIGHT 8
#define TILE_NUM_GRID_ELEMENTS (GRID_ROWS * GRID_COLUMNS) //16
#define MAX_MAP_TILE_HEIGHT 20
#define MAX_MAP_WIDTH_TILES 100
#define MAX_MAP_GRID_HEIGHT (MAX_MAP_TILE_HEIGHT * GRID_ROWS) //80
#define MAX_MAP_GRID_WIDTH (MAX_MAP_TILE_HEIGHT * GRID_COLUMNS) //100

using GridIndex = unsigned char;
typedef GridIndex GridMap[20 * 4 * 100 * 4];
static GridMap grid;
static GridIndex* grida = grid;

class GridComponent : public Component //GridComp --> ColliderComp
{
public:
	bool fullSolid;
	Vector2D position;
	int scaledTile;
	ColliderComponent* collider;

	GridComponent() = default;

	~GridComponent()
	{

	}

	GridComponent(int xpos, int ypos, int tscaled, bool isSolid)
	{
		position.x = xpos;
		position.y = ypos;

		fullSolid = isSolid;

		scaledTile = tscaled;
	}

	void init() override
	{
		Vector2D gridPos;
		ComputeTileGridBlocks();

		if (fullSolid)
		{
			for (auto gridindex = 0; gridindex < TILE_NUM_GRID_ELEMENTS; gridindex++)
			{ //SetGridTileBlock
				gridPos.x = (gridindex % GRID_COLUMNS) * GRID_ELEMENT_WIDTH;
				gridPos.y = (int)(gridindex / GRID_ROWS) * GRID_ELEMENT_HEIGHT;
				if (gridPos.y)
				{
					entity->addComponent<ColliderComponent>("terrain", (position.x + gridPos.x), (position.y + gridPos.y), GRID_ELEMENT_WIDTH, true);
				}
				else
				{
					entity->addComponent<ColliderComponent>("terrain", position.x + gridPos.x, position.y + gridPos.y, GRID_ELEMENT_WIDTH, false);
				}
			}
		}
	}

	void update() override
	{

	}

	void ComputeTileGridBlocks()
	{
		memset(grida,
			fullSolid ?
			GRID_SOLID_TILE :
			GRID_EMPTY_TILE,
			TILE_NUM_GRID_ELEMENTS
		);
		grida += TILE_NUM_GRID_ELEMENTS;
	}
};
