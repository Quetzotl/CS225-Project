#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3_image/SDL_image.h>
#include <Minesweeper/tileRender.h>

Tilemap::Tilemap(const char* image){
    SDL_IOStream* f = SDL_IOFromFile(image, "r");
    if (IMG_isPNG(f)) map = IMG_LoadPNG_IO(f);
    else throw "Tilemap only compatible with .png file types";
}