#include <SDL3/SDL.h>
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_image.h>

SDL_Window* window;
SDL_Renderer* renderer;

// Initialize the application (runs once on startup)
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv);
// The main loop of the app (runs continuously)
SDL_AppResult SDL_AppIterate(void *appstate);
// Event Handling (i.e user input)
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event);
// End the application (runs once on shutdown)
void SDL_AppQuit(void *appstate, SDL_AppResult result);

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv){
    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Couldn't initialize SDL Library: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Minesweeper", 800, 600, 
            SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate){
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    return;
}