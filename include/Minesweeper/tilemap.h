#ifndef TILEMAP_H
#define TILEMAP_H

class Tilemap {
public:
    Tilemap(const char* image, const int& tile_width, const int& tile_height);
    ~Tilemap();
    SDL_Surface* operator[](const int& n);
    int getTileWidth() const {return tile.w;}
    int getTileHeight() const {return tile.h;}
private:
    SDL_Surface* map;
    SDL_Rect tile;
};

#endif
