#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <Minesweeper/tilemap.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture** tiles;
SDL_Texture* frame;
const int GRID_WIDTH = 30, GRID_HEIGHT = 20;
const int TILE_WIDTH = 32, TILE_HEIGHT = 32, TILE_COUNT = 12;
const int FRAME_SIZE = 24;
const int SCREEN_WIDTH = GRID_WIDTH*TILE_WIDTH + 2*FRAME_SIZE;
const int SCREEN_HEIGHT = GRID_HEIGHT*TILE_HEIGHT + 2*FRAME_SIZE;
const char* TILE_PATH = "assets/MinesweeperTileset.png";
const char* FRAME_PATH = "assets/MinesweeperFrame.png";

// Initialize the application (runs once on startup)
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv);
// The main loop of the app (runs continuously)
SDL_AppResult SDL_AppIterate(void *appstate);
// Event Handling (i.e user input)
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event);
// End the application (runs once on shutdown)
void SDL_AppQuit(void *appstate, SDL_AppResult result);
// Initialize tiles
void makeTiles(SDL_Texture** &out, Tilemap map, const int& count);

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv){
    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Couldn't initialize SDL Library: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Minesweeper", SCREEN_WIDTH, SCREEN_HEIGHT, 
            SDL_WINDOW_RESIZABLE, &window, &renderer)){
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    try {
        makeTiles(tiles, Tilemap(TILE_PATH, TILE_WIDTH, TILE_HEIGHT), TILE_COUNT);
    } catch (const char* image) {
        SDL_Log("Failed to open file %s: %s", image, SDL_GetError());
        return SDL_APP_FAILURE;
    } catch (bool x){
        if (x){
            SDL_Log("Couldn't create tiles: input file is not .png");
            return SDL_APP_FAILURE;
        }
    } catch (int i){
        SDL_Log("Couldn't create tile #%d: %s", i, SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_IOStream* f = SDL_IOFromFile(FRAME_PATH, "r");
    if (f == NULL) {
        SDL_Log("Failed to open %s: %s", FRAME_PATH, SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (IMG_isPNG(f)) {
        frame = SDL_CreateTextureFromSurface(renderer, IMG_LoadPNG_IO(f));
    } else {
        SDL_Log("Invalid frame: frame must be a .png");
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){
    SDL_RenderClear(renderer);
    if (!SDL_RenderTexture9GridTiled(renderer, frame, NULL, 
        FRAME_SIZE, FRAME_SIZE, FRAME_SIZE, FRAME_SIZE, 0.0f, NULL, 1.0f)){
            SDL_Log("Frame failed to render: %s", SDL_GetError());
            return SDL_APP_FAILURE;
        }
    for (int x = 0; x < GRID_WIDTH; x++){
        for (int y = 0; y < GRID_HEIGHT; y++){
            SDL_FRect rect = {
                static_cast<float>(x * TILE_WIDTH + FRAME_SIZE),
                static_cast<float>(y * TILE_HEIGHT + FRAME_SIZE),
                static_cast<float>(TILE_WIDTH),
                static_cast<float>(TILE_HEIGHT)
            };
            if (!SDL_RenderTexture(renderer, tiles[10], NULL, &rect)){
                SDL_Log("Failed to render tiles to screen: %s", SDL_GetError());
                return SDL_APP_FAILURE;
            }
        }
    }
    if (!SDL_RenderPresent(renderer)){
        SDL_Log("Couldn't render screen: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    delete[] tiles;
    return;
}

void makeTiles(SDL_Texture** &out, Tilemap map, const int& count) {
    delete[] out;
    out = new SDL_Texture*[count];
    for (int i = 0; i < count; i++){
        out[i] = SDL_CreateTextureFromSurface(renderer, map.getTile(i));
    }
}