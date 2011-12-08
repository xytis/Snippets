
#include "cArea.hpp"

cArea cArea::current_area;

cArea::cArea() {
  m_area_size = 0;
}

bool cArea::load(char* filename) {
  map_array.clear();

  FILE* file = fopen(filename, "r");

  if(file == NULL) {
	return false;
  }

  char tileset_filename[255];

  fscanf(file, "%s\n", tileset_filename);

  if((m_tileset = cSurface::load(tileset_filename)) == false) {
	fclose(file);

	return false;
  }

  fscanf(file, "%d\n", &m_area_size);

  for(int X = 0;X < m_area_size;X++) {
	for(int Y = 0;Y < m_area_size;Y++) {
	  char map_filename[255];

	  fscanf(file, "%s ", map_filename);

	  cMap tempMap;
	  if(tempMap.load(map_filename) == false) {
		fclose(file);

		return false;
	  }

	  tempMap.tileset = m_tileset;

	  map_array.push_back(tempMap);
	}
	fscanf(file, "\n");
  }

  fclose(file);

  return true;
}

void cArea::render(SDL_Surface* display, int camera_x, int camera_y) {
  int map_width  = MAP_WIDTH * TILE_SIZE;
  int map_height = MAP_HEIGHT * TILE_SIZE;

  int FirstID = -camera_x / map_width;
  FirstID = FirstID + ((-camera_y / map_height) * m_area_size);

  for(int i = 0;i < 4;i++) {
	int ID = FirstID + ((i / 2) * m_area_size) + (i % 2);

	if(ID < 0 || ID >= map_array.size()) continue;

	int x = ((ID % m_area_size) * map_width) + camera_x;
	int y = ((ID / m_area_size) * map_height) + camera_y;

	map_array[ID].render(display, x, y);
  }
}

void cArea::cleanup() {
  if(m_tileset) {
	SDL_FreeSurface(m_tileset);
  }

  map_array.clear();
}