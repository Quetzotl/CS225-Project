#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <Minesweeper/tileRender.h>

Tilemap::Tilemap(const char* image, const int& tile_width, const int& tile_height){
    SDL_IOStream* f = SDL_IOFromFile(image, "r");
    if (IMG_isPNG(f)) map = IMG_LoadPNG_IO(f);
    else throw "Tilemap only compatible with .png file types";
    tile.w = tile_width;
    tile.h = tile_height;
}

SDL_Surface* Tilemap::getTile(const int& n){
    SDL_Surface* out;
    tile.x = tile.y = 0;
    for (int i = 0; i < n; i++){
        tile.x += tile.w;
        if (tile.x > map->w) {
            tile.x -= map->w;
            tile.y += tile.h;
        }
    }
    if (!SDL_BlitSurface(map, &tile, out, NULL)) {
        SDL_Log("Tile %d failed to generate: %s", n, SDL_GetError());
    }
    return out;
}