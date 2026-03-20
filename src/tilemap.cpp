#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <Minesweeper/tilemap.h>

Tilemap::Tilemap(const char* image, const int& tile_width, const int& tile_height){
    SDL_IOStream* f = SDL_IOFromFile(image, "r");
    if (f == NULL) throw image;
    if (IMG_isPNG(f)) map = IMG_LoadPNG_IO(f);
    else throw true;
    tile.w = tile_width;
    tile.h = tile_height;
}

SDL_Surface* Tilemap::getTile(const int& n){
    SDL_Surface* out = SDL_CreateSurface(tile.w, tile.h, SDL_PIXELFORMAT_RGB24);
    tile.x = tile.y = 0;
    for (int i = 0; i < n; i++){
        tile.x += tile.w;
        if (tile.x >= map->w) {
            tile.x -= map->w;
            tile.y += tile.h;
        }
    }
    if (!SDL_BlitSurface(map, &tile, out, NULL)) throw n;
    
    return out;
}