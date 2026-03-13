#ifndef TILE_RENDER_H
#define TILE_RENDER_H

class Tilemap {
public:
    Tilemap(const char*, const int&, const int&);
    SDL_Surface* getTile(const int&);
private:
    SDL_Surface* map;
    SDL_Rect tile;
    int tiles_per_row;
};

#endif
