#include <SDL3/SDL.h>
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

// Initialize the application (runs once on startup)
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv);
// The main loop of the app (runs continuously)
SDL_AppResult SDL_AppIterate(void *appstate);