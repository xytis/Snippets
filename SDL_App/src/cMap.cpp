
#include "cMap.hpp"

cMap::cMap() {
  tileset = NULL;
}

bool cMap::load(char* filename) {
  tile_array.clear();

  FILE* file = fopen(filename, "r");

  if(file == NULL) {
	return false;
  }

  for(int y = 0; y < MAP_HEIGHT; y++) {
	for(int x = 0; x < MAP_WIDTH; x++) {
	  cTile temp_tile;

	  fscanf(file, "%d:%d ", &temp_tile.tileID, &temp_tile.typeID);

	  tile_array.push_back(temp_tile);
	}
	fscanf(file, "\n");
  }

  fclose(file);

  return true;
}

void cMap::render(SDL_Surface* display, int map_x, int map_y) {
  if(tileset == NULL) return;

  int tileset_width  = tileset->w / TILE_SIZE;
  int tileset_height = tileset->h / TILE_SIZE;

  int ID = 0;

  for(int y = 0; y < MAP_HEIGHT; y++) {
	for(int x = 0; x < MAP_WIDTH; x++) {
	  if(tile_array[ID].typeID == TILE_TYPE_NONE) {
		ID++;
		continue;
	  }

	  int tx = map_x + (x * TILE_SIZE);
	  int ty = map_y + (y * TILE_SIZE);

	  int tileset_x = (tile_array[ID].tileID % tileset_width) * TILE_SIZE;
	  int tileset_y = (tile_array[ID].tileID / tileset_height) * TILE_SIZE;

	  cSurface::draw(tileset, tileset_x, tileset_y, TILE_SIZE, TILE_SIZE, display, tx, ty);

	  ID++;
	}
  }
}