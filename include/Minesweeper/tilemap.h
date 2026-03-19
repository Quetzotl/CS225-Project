#ifndef TILEMAP_H
#define TILEMAP_H

class Tilemap {
public:
    Tilemap(const char* image, const int& tile_width, const int& tile_height);
    SDL_Surface* getTile(const int& n);
    const int getTileWidth() {return tile.w;}
    const int getTileHeight() {return tile.h;}
private:
    SDL_Surface* map;
    SDL_Rect tile;
};

#endif
